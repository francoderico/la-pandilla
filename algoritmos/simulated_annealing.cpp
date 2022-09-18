#include <algorithm>
#include <chrono>
#include <functional>
#include <random>

class random_number_generator{
  std::mt19937 _mt;
public:
  random_number_generator():_mt(
    static_cast<std::mt19937::result_type>(
      std::chrono::steady_clock::now().time_since_epoch().count()
    )
  ){}
  int random_int(int n){return random_int(0,n);}
  int random_int(int a,int b){
    return std::uniform_int_distribution<int>(a,b-1)(_mt);
  }
  double random_real(double n){return random_real(0.0,n);}
  double random_real(double a,double b){
    return std::uniform_real_distribution<double>(a,b)(_mt);
  }
  template<typename RandomIt>
  void shuffle(RandomIt first,RandomIt last){
    std::shuffle(first,last,_mt);
  }
}rng;

class time_keeper{
  std::chrono::steady_clock::time_point _t0;
public:
  time_keeper():_t0(std::chrono::steady_clock::now()){}
  double elapsed_time(){
    std::chrono::steady_clock::time_point t1=std::chrono::steady_clock::now();
    return std::chrono::duration<double,std::milli>(t1-_t0).count();
  }
}timer;

template<typename Object,typename Change,typename Energy>
class simulated_annealing{
  typedef std::function<Energy(Object&)>InitializationFunction;
  typedef std::function<const Change(const Object&)>NeighborFunction;
  typedef std::function<void(Object&,const Change&)>ApplicationFunction;
  typedef std::function<Energy(const Object&,const Change&)>EnergyFunction;
  typedef std::function<double(double)>TemperatureFunction;
  typedef std::function<double(Energy,Energy,double)>AcceptanceFunction;
  Object _obj;
  Energy _curr_energy,_lowest_energy;
  NeighborFunction _neighbor;
  ApplicationFunction _apply;
  EnergyFunction _energy;
  TemperatureFunction _temperature;
  AcceptanceFunction _accept;
public:
  simulated_annealing(
    Object&&obj,
    InitializationFunction&&initialize,
    NeighborFunction&&neighbor,
    ApplicationFunction&&apply,
    EnergyFunction&&energy,
    TemperatureFunction&&temperature=[](double percentage_left)->double{
      return percentage_left;
    },
    AcceptanceFunction&&accept=[](
      Energy old_energy,Energy new_energy,double temp
    )->double{
      return (
        new_energy<old_energy?
        1.0:
        exp(static_cast<double>(old_energy-new_energy)/temp)
      );
    }
  ):
    _obj(std::forward<Object>(obj)),
    _curr_energy(initialize(_obj)),
    _lowest_energy(_curr_energy),
    _neighbor(std::forward<NeighborFunction>(neighbor)),
    _apply(std::forward<ApplicationFunction>(apply)),
    _energy(std::forward<EnergyFunction>(energy)),
    _temperature(std::forward<TemperatureFunction>(temperature)),
    _accept(std::forward<AcceptanceFunction>(accept))
  {}
  simulated_annealing&simulate(const double duration_limit=500){
    const double initial_time=timer.elapsed_time();
    for(
      double elapsed_time=timer.elapsed_time()-initial_time;
      elapsed_time<duration_limit;
      elapsed_time=timer.elapsed_time()-initial_time
    ){
      double temp=_temperature(1-elapsed_time/duration_limit);
      Change new_change=_neighbor(_obj);
      Energy new_energy=_energy(_obj,new_change);
      _lowest_energy=min(_lowest_energy,new_energy);
      if(_accept(_curr_energy,new_energy,temp)>=rng.random_real(1)){
        _apply(_obj,new_change);
        _curr_energy=new_energy;
      }
    }
    return *this;
  }
  const Object&last_state()const&{return _obj;}
  const Energy lowest_energy()const&{return _lowest_energy;}
};

#include <algorithm>
#include <chrono>
#include <functional>
#include <random>

using namespace std;
using my_clock = chrono::steady_clock;

class random_number_generator {

	mt19937 mt;

public:

	random_number_generator():
		mt(my_clock::now().time_since_epoch().count())
	{}

	int random_int(int n) {
		return random_int(0, n);
	}

	int random_int(int a, int b) {
		return uniform_int_distribution<>(a, b-1)(mt);
	}

	double random_real(double n) {
		return random_real(0.0, n);
	}

	double random_real(double a, double b) {
		return uniform_real_distribution<>(a, b)(mt);
	}

	template<typename RandomIt>
	void shuffle(RandomIt first, RandomIt last) {
		std::shuffle(first, last, mt);
	}
}
rng;

class time_keeper {

	my_clock::time_point t0;

public:

	time_keeper():
		t0(my_clock::now())
	{}

	double elapsed_time() {
		my_clock::time_point t1 = my_clock::now();
		return chrono::duration<double, milli>(t1 - t0).count();
	}
}
timer;

template<typename Object,typename Change,typename Energy>
class simulated_annealing{
	typedef function<Energy(Object&)>InitializationFunction;
	typedef function<const Change(const Object&)>NeighborFunction;
	typedef function<void(Object&,const Change&)>ApplicationFunction;
	typedef function<Energy(const Object&,const Change&)>EnergyFunction;
	typedef function<double(double)>TemperatureFunction;
	typedef function<double(Energy,Energy,double)>AcceptanceFunction;
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
		_obj(forward<Object>(obj)),
		_curr_energy(initialize(_obj)),
		_lowest_energy(_curr_energy),
		_neighbor(forward<NeighborFunction>(neighbor)),
		_apply(forward<ApplicationFunction>(apply)),
		_energy(forward<EnergyFunction>(energy)),
		_temperature(forward<TemperatureFunction>(temperature)),
		_accept(forward<AcceptanceFunction>(accept))
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

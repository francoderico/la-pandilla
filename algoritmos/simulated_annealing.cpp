#include <algorithm>
#include <chrono>
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

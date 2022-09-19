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

	Object obj;
	Energy curr_energy, lowest_energy;
	NeighborFunction neighbor;
	ApplicationFunction apply;
	EnergyFunction energy;
	TemperatureFunction temperature;
	AcceptanceFunction accept;

public:

	simulated_annealing(
		Object&& _obj,
		InitializationFunction&& _initialize,
		NeighborFunction&& _neighbor,
		ApplicationFunction&& _apply,
		EnergyFunction&& _energy,
		TemperatureFunction&& _temperature=[](double percentage_left) -> double {
			return percentage_left;
		},
		AcceptanceFunction&& _accept=[](
			Energy old_energy, Energy new_energy, double temp
		) -> double {
			return (
				new_energy < old_energy ?
				1.0 :
				exp(static_cast<double>(old_energy - new_energy) / temp)
			);
		}
	):
		obj(forward<Object>(_obj)),
		curr_energy(_initialize(obj)),
		lowest_energy(curr_energy),
		neighbor(forward<NeighborFunction>(_neighbor)),
		apply(forward<ApplicationFunction>(_apply)),
		energy(forward<EnergyFunction>(_energy)),
		temperature(forward<TemperatureFunction>(_temperature)),
		accept(forward<AcceptanceFunction>(_accept))
	{}

	simulated_annealing& simulate(const double duration_limit=500) {
		const double initial_time=timer.elapsed_time();
		for(
			double elapsed_time = timer.elapsed_time() - initial_time;
			elapsed_time < duration_limit;
			elapsed_time = timer.elapsed_time() - initial_time
		) {
			double temp = temperature(1 - elapsed_time / duration_limit);
			Change new_change = neighbor(obj);
			Energy new_energy = energy(obj, new_change);
			lowest_energy = min(lowest_energy, new_energy);
			if(accept(curr_energy, new_energy, temp) >= rng.random_real(1)) {
				apply(obj, new_change);
				curr_energy = new_energy;
			}
		}
		return *this;
	}

	const Object& get_last_state() const& {
		return obj;
	}

	const Energy get_lowest_energy() const& {
		return lowest_energy;
	}
};

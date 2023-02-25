#include <algorithm>
#include <chrono>
#include <functional>
#include <random>

using namespace std;
using my_clock = chrono::steady_clock;

class random_number_generator {
	mt19937 engine;
public:
	random_number_generator():
		engine(my_clock::now().time_since_epoch().count()) {}
	/// Return random integer in [0,n).
	template<typename Int=int>
	Int random_int(Int n) {return random_int<Int>(0, n);}
	/// Return random integer in [a,b).
	template<typename Int=int>
	Int random_int(Int a, Int b) {
		return uniform_int_distribution<Int>(a, b-1)(engine);
	}
	/// Return random real in [0,r).
	template<typename Real=double>
	Real random_real(Real r=1.) {return random_real<Real>(0., r);}
	/// Return random real in [a,b).
	template<typename Real=double>
	Real random_real(Real a, Real b) {
		return uniform_real_distribution<Real>(a, b)(engine);
	}
	/// Shuffle range [first,last) randomly.
	template<typename RandomIt>
	void shuffle(RandomIt first, RandomIt last) {
		std::shuffle(first, last, engine);
	}
} rng;

class time_keeper {
	using time_point = my_clock::time_point;
	time_point start = my_clock::now();
public:
	/// Reset the timer.
	void reset() {start = my_clock::now();}
	/// Return the current time in the specified period, seconds by default.
	template<typename Rep=double, class Period=ratio<1>>
	Rep elapsed() {
		const time_point now = my_clock::now();
		return chrono::duration<Rep, Period>(now - start).count();
	}
} timer;

template<typename Energy>
class simulated_annealing{
	using stir_function = function<const Energy()>;
	using save_function = function<void()>;
	const stir_function stir;
	const save_function save;
	Energy curr_energy, coldest;
	/// Initialize the state of the system and return the corresponding energy.
	const Energy initialize_state() const {
		const Energy energy = stir();
		return (save(), energy);
	}
	/// Return the current temperature of the system.
	///
	/// Usually one will want to modify this definition, depending on the problem
	/// being solved, so that the temperature is not as small in the beginning, so
	/// long as it's decreasing and tending to zero.
	double measure_temp(const double percentage_left) const {
		return percentage_left;
	}
	/// Return the probability of accepting the new state corresponding to the
	/// given energy.
	double accept_prob(const Energy new_energy, const double temp) const {
		const double delta = static_cast<double>(curr_energy - new_energy);
		if (delta >= 0.) {return 1.;}
		return exp(delta/temp);
	}
public:
	simulated_annealing(const stir_function _stir, const save_function _save):
		stir(move(_stir)),
		save(move(_save)),
		curr_energy(initialize_state()),
		coldest(curr_energy){}
	/// Execute the simulation until the time limit is reached.
	simulated_annealing& simulate(const double time_limit=1.) {
		const double initial_time = timer.elapsed();
		for (
			double elapsed_time = timer.elapsed() - initial_time;
			elapsed_time < time_limit;
			elapsed_time = timer.elapsed() - initial_time
		) {
			const Energy new_energy = stir();
			coldest = min(coldest, new_energy);
			const double temp = measure_temp(1-elapsed_time/time_limit);
			if (accept_prob(new_energy, temp) >= rng.random_real()) {
				curr_energy = (save(), new_energy);
			}
		}
		return *this;
	}
	/// Return the last energy saved by the system.
	///
	/// This may or may not be the lowest energy of the simulation, although in
	/// most problems it is. Useful for when one needs to now the energy
	/// corresponding to the last state of the system, since storing the best
	/// state can be inefficient.
	const Energy peek_last_energy() const {return curr_energy;}
	/// Return the lowest energy reached by the simulation at any point in time.
	const Energy peek_lowest_energy() const {return coldest;}
};

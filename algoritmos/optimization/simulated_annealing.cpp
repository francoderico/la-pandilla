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
		engine(my_clock::now().time_since_epoch().count()){}
	/// Return random integer in [0,n).
	template<typename Int=int>
	Int random_int(Int n) {
		return random_int<Int>(0, n);
	}
	/// Return random integer in [a,b).
	template<typename Int=int>
	Int random_int(Int a, Int b) {
		return uniform_int_distribution<Int>(a, b-1)(engine);
	}
	/// Return random real in [0,r).
	template<typename Real=double>
	Real random_real(Real r=1.) {
		return random_real<Real>(0., n);
	}
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
	void reset() {
		start = my_clock::now();
	}
	/// Return the current time in the specified period, seconds by default.
	template<typename Rep=double, class Period=ratio<1>>
	Rep elapsed() {
		const time_point now = my_clock::now();
		return chrono::duration<Rep, Period>(now - start).count();
	}
} timer;

template<typename Object,typename Change,typename Energy>
class simulated_annealing{

	typedef function<Energy(Object&)>InitializationFunction;

	Object obj;
	Energy curr_energy, lowest_energy;

	void set_initial_state() {
		// TODO
		// Debe initializar a `obj` con un nuevo estado válido (si es que no se hizo antes),
		// y setear a `curr_energy` y `lowest_energy` en base al nuevo estado del objeto
		// (originalmente deben ser iguales)
	}

	const Change neighbor() const& {
		// TODO
		// Usa a `obj` para obtener un nuevo cambio de estado, pero no debe modificar a `obj`.
	}

	void apply(const Change& change) {
		// TODO
		// Aplica el cambio `change` al estado `obj`.
	}

	Energy energy(const Change& change) const& {
		// TODO
		// Retorna la energía asociada al cambio de estado dado. No modifica nada.
	}

	double temperature(const double percentage_left) {
		// TODO
		// Se puede dejar así o cambiar (por ejemplo, retornando una constante por el
		// valor `percentage_left`) dependiendo del problema.
		return percentage_left;
	}

	double accept(
		const Energy old_energy,
		const Energy new_energy,
		const double temp
	) {
		return (
			new_energy < old_energy ?
			1.0 :
			exp(static_cast<double>(old_energy - new_energy) / temp)
		);
	}

public:

	simulated_annealing(const Object& _obj):
		obj(_obj)
	{
		set_initial_state();
	}

	simulated_annealing& simulate(const double duration_limit=500) {
		const double initial_time=timer.elapsed_time();
		for(
			double elapsed_time = timer.elapsed_time() - initial_time;
			elapsed_time < duration_limit;
			elapsed_time = timer.elapsed_time() - initial_time
		) {
			const double temp = temperature(1 - elapsed_time / duration_limit);
			const Change new_change = neighbor();
			const Energy new_energy = energy(new_change);
			lowest_energy = min(lowest_energy, new_energy);
			if(accept(curr_energy, new_energy, temp) >= rng.random_real(1)) {
				apply(new_change);
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

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

	simulated_annealing(Object&& _obj):
		obj(forward<Object>(_obj))
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

using my_clock = chrono::steady_clock;

struct Random {
	mt19937_64 engine;
	Random(): engine(my_clock::now().time_since_epoch().count()) {}
	template<class Int>Int integer(Int n) {return integer<Int>(0, n);} // `[0,n)`
	template<class Int>Int integer(Int l, Int r)
		{return uniform_int_distribution{l, r-1}(engine);} // `[l,r)`
	double real() {return uniform_real_distribution{}(engine);} // `[0,1)`
} rng;

struct Timer {
	using time = my_clock::time_point;
	time start = my_clock::now();
	double elapsed() { // Segundos desde el inicio.
		time now = my_clock::now();
		return chrono::duration<double>(now - start).count();
	}
} timer;

template<class See,class Upd>struct Annealing {
	using energy = invoke_result_t<See>;
	energy curr, low;
	See see;
	Upd upd;
	Annealing(See _see, Upd _upd): see{_see}, upd{_upd}
		{curr = low = see(), upd();}
	void simulate(double s, double mult=1) { // Simula por `s` segundos.
		double t0 = timer.elapsed();
		for (double t = t0; t-t0 < s; t = timer.elapsed()) {
			energy near = see();
			auto delta = double(curr - near);
			if (delta >= 0) upd(), curr = near, low = min(low, curr);
			else {
				double temp = mult * (1 - (t-t0)/s);
				if (exp(delta/temp) > rng.real()) upd(), curr = near;
			}
		}
	}
};

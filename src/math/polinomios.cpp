typedef int tp; /*type of polynomial*/    template<class T=tp>
struct poly {  // poly<> : 1 variable, poly<poly<>>: 2 variables, etc.
	vector<T> c;
	T& operator[](int k){return c[k];}
	poly(vector<T>& c):c(c){}    poly(initializer_list<T> c):c(c){}
	poly(int k):c(k){}           poly(){}
	poly operator+(poly<T> o){ int m = sz(c), n = sz(o.c);
		poly res(max(m,n)); forn(i, m) res[i] = res[i]+c[i]; 
		forn(i, n) res[i] = res[i]+o.c[i];      return res;
	}
	poly operator*(tp k){ poly res(sz(c)); forn(i, sz(c)) res[i] = c[i]*k;
		return res;
	}
	poly operator*(poly o){ int m=sz(c), n=sz(o.c);     poly res(m+n-1);
		forn(i, m) forn(j, n) res[i+j] = res[i+j]+c[i]*o.c[j];
		return res;
	}
	poly operator-(poly<T> o){ return *this+(o*-1); }
	T operator()(tp v){ T sum(0);
		for(int i=sz(c)-1; i>=0; --i) sum = sum*v+c[i];    return sum;
	}
};
// ejemplo: p(x,y)=2*x^2+3*x*y-y+4 -> poly<poly<>> p={{4,-1},{0,3},{2}}
// p(2)(3) == 27
set<tp> roots(poly<> p){ // only for integer polynomials
	set<tp> r;
	while(not p.c.empty() and not p.c.back()) p.c.pp();
	if(not p(0)) r.insert(0);
	if(p.c.empty()) return r;
	tp a0 = 0, an = abs(p[sz(p.c)-1]);     vector<tp> ps, qs;
	for(int k=0; not a0; a0=abs(p[k++])) {}
	forr(i,1,sqrt(a0)+1) if(a0%i==0) ps.pb(i), ps.pb(a0/i);
	forr(i,1,sqrt(an)+1) if(an%i==0) qs.pb(i), qs.pb(an/i);
	for(auto pt:ps)for(auto qt:qs) if(pt%qt == 0){
		tp x=pt/qt;    if(!p(x))r.insert(x);   if(!p(-x))r.insert(-x);
	}
	return r;
}
pair<poly<>,tp> ruffini(poly<> p, tp r){ // returns pair (result,rem)
	int n=sz(p.c)-1;    vector<tp> b(n);     b[n-1]=p[n];
	for(int k=n-2; k>=0; --k) b[k] = p[k+1]+r*b[k+1];
	return {poly<>(b), p[0]+r*b[0]};
}
// only for double polynomials // returns pair (result, resto)
pair<poly<>,poly<>> polydiv(poly<> p, poly<> q){
	int n=sz(p.c)-sz(1.c)+1;
	vector<tp> b(n);
	for(int k=n-1;k>=0;--k){
		b[k]=p.c.back()/q.c.back();
		forn(i, q.sz(c)) p[i+k] -= b[k]*q[i];
		p.c.pp();
	}
	while(not p.c.empty() and abs(p.c.back())<EPS) p.c.pp();
	return {poly<>(b), p};
}
poly<> interpolate(vector<tp> x, vector<tp> y){
	poly<> q={1}, S={0};
	for(auto a : x) q = poly<>({-a,1})*q;
	forn(i, sz(x)){
		poly<> Li = ruffini(q, x[i]).fst;
		Li = Li*(1.0/Li(x[i])); // change for int polynomials
		S = S+Li*y[i];
	}
	return S;
}
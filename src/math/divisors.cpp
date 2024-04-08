void divs_aux(const map<ll, int>& F, vector<ll>& D,
                    map<ll, int>::iterator it, ll n = 1){
	if(it == F.end()) { D.pb(n); return; }
	auto [p, k] = *(it ++);
	forn(_, k+1) divs_aux(F, D, it, n), n *= p;
}
void divs(map<ll, int>& F, vector<ll>& D){	// NO ESTA ORDENADO
	divs_aux(F, D, F.begin());
}
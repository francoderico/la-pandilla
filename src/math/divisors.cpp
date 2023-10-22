// Auxiliar, no llamar
void divisores_aux(const map<ll, int> &F, vector<ll> &divs, map<ll, int>::iterator it, ll n = 1){
	if(it == F.begin()) divs.clear();
	if(it == F.end()) { divs.pb(n); return; }
	ll p = it->fst, k = it->snd; ++it;
	forn(_, k+1) divisores_aux(F, divs, it, n), n *= p;
}

// Obtiene los divisores a partir de la factorizacion. NO ESTA ORDENADO
void divisores(map<ll, int> &F, vector<ll> &divs){
	divisores_aux(F, divs, F.begin());
}
// Permite hacer CTRL+Z hasta el estado en que se toma el snapshot
// Uso: int tiempo = snapshot(); ...; restore(tiempo);
vector<pair<int&, int>> changes;
int snapshot() { return sz(changes); }
void restore(int snap){
	while (sz(changes) > snap) {
		auto [l, r] = changes.back(); changes.pp(); l = r;
	}
}
int assign(int& l, int r){ //Reemplazar los a=b de la struct por assign(a,b)
	changes.pb({l, l});
	return l = r;
}
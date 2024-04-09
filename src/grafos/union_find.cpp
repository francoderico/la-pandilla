vector<int> uf(MAXN, -1);
int uf_find(int x) { return uf[x]<0 ? x : uf[x] = uf_find(uf[x]); }
bool uf_join(int x, int y){ // True sii x e y estan en != componentes
	x = uf_find(x); y = uf_find(y);
	if(x == y) return false;
	if(uf[x] > uf[y]) swap(x, y);
	uf[x] += uf[y]; uf[y] = x; return true;
}
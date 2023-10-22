const ll MAXP = 3e3+10; //68 MB, con 1e4 int son 380 MB
ll P;				//inicializar con el primo del input < MAXP
ll C[MAXP][MAXP];
void llenar_C(){
	forr(i, 0, MAXP) C[i][0] = 1;
	forr(i, 1, MAXP) forr(j, 1, i+1) C[i][j] = addmod(C[i-1][j-1], C[i-1][j], P);
}
// Para calcular nCk (mod p) con n, k arbitrariamente grandes y p primo <= 3000
// Requiere tener precalculados todos los combinatorios al menos hasta C[p][p]
ll lucas(ll N, ll K){
	ll ret = 1;
	while(N+K){
		ret = ret * C[N%P][K%P] % P;
		N /= P, K /= P;
	}
	return ret;
}
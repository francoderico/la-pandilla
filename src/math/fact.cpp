// O(sqrt n)
void fact(ll n, map<ll, int> &F){
	for(ll p = 2; p*p <= n; p ++) while(n%p == 0) F[p] ++, n /= p;
	if(n > 1) F[n] ++;
}
//------------------------------------------------------
const int MAXP = 1e7+100;
int criba[MAXP];
void crear_criba(){ // 0 si es primo (o si es 1), algun primo que lo divide si no.
	for(int i = 2; i*i < MAXP; i ++) if(! criba[i])
		for(int j = i*i; j < MAXP; j += i) criba[j] = i;
}
// O(log n) - n <= sz(criba) (1e7) 
void fact(ll n, map<ll, int> &F){
	while(criba[n]) F[criba[n]] ++, n /= criba[n];
	if(n > 1) F[n] ++;
}
//------------------------------------------------------
vector<int> primos;
void buscar_primos(){	//crear_criba() primero!!
	forr(i, 2, MAXP) if(! criba[i]) primos.pb(i);
}
// O(sz(p)) (cantidad de primos) - n <= MAXP^2
void fact(ll n, map<ll, int> &F){
	for(auto &p : primos) while(n%p == 0) F[p] ++, n /= p;
	if(n > 1) F[n] ++;
}
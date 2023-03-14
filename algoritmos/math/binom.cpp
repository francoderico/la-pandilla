// Tambien contiene el precalculo de los inversos modulares
ll fact[MAXN], invfact[MAXN], inv[MAXN];

void calc()
{
	inv[1] = 1;
	fact[0] = fact[1] = 1;
	invfact[0] = invfact[1] = 1;
	forr(i, 2, MAXN)
	{
		inv[i] = MOD - (MOD/i) * inv[MOD%i] % MOD;
		fact[i] = fact[i-1] * i % MOD;
		invfact[i] = invfact[i-1] * inv[i] % MOD;
	}
}
 
ll binom(ll n, ll k)
{
	if(k > n) return 0;
	return fact[n] * invfact[k] % MOD * invfact[n-k] % MOD;
}



//------------------------------------------------------



// Triangulo de Pascal
const ll MAXN = 3e3+10; //68 MB, con 1e4 int son 380 MB

ll C[MAXN][MAXN];

void llenar_C()
{
	forr(i, 0, MAXN) C[i][0] = 1;
	
	forr(i, 1, MAXN-1) forr(j, 1, i+1) C[i][j] = addmod(C[i-1][j-1], C[i-1][j]);
}
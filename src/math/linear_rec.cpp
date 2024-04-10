//init O(n^2log) query(n^2 logk)
//input: terms: first n term; trans: transition func; MOD; LOG=max log of k
//output calc(k): kth term mod MOD
//example: {1,1} {2,1} a_n=2*a_(n-1)+a_(n-2); calc(3)=3 calc(10007)=71480733
struct LinearRec{
	typedef vector<int> vi;
	nt n; vi terms, trans; vector<vi> bin;
	vi add(vi &a, vi &b){
		vi res(n*2+1);
		forn(i, n+1) forn(j, n+1) res[i+j] = (res[i+j]+ll(a[i])*b[j])%MOD;
		for(int i=2*n; i>n; --i){
			forn(j, n) res[i-1-j] = (res[i-1-j]+ll(res[i])*trans[j])%MOD;
			res[i] = 0;
		}
		res.erase(res.begin()+n+1, res.end());
		return res;
	}
	LinearRec(vi &terms, vi &trans): terms(terms), trans(trans){
		n=sz(trans); vi a(n+1); a[1]=1;
		bin.pb(a);
		forr(i,1,LOG) bin.pb(add(bin[i-1], bin[i-1]));
	}
	int calc(int k){
		vi a(n+1); a[0]=1;
		forn(i, LOG) if((k>>i)&1) a=add(a, bin[i]);
		int ret=0;
		forn(i, n) ret = (ret+ll(a[i+1])*terms[i])%MOD;
		return ret;
	}
};
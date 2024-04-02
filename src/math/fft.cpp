// MAXN must be power of 2 !!
// MOD-1 needs to be a multiple of MAXN !!
typedef ll tf;
typedef vector<tf> poly;
// big mod and primitive root for NTT:
//const tf MOD = 2305843009255636993, RT = 5;
const tf MOD = 998244353, RT = 3;
/* FFT */ struct CD {
	double r, i;
	CD(double r_ = 0, double i_ = 0) : r(r_), i(i_) {}
	double real() const { return r; }
	void operator/=(const int c) { r/=c, i/=c; }
};
CD operator*(const CD& a, const CD& b){
	return CD(a.r*b.r-a.i*b.i, a.r*b.i+a.i*b.r);}
CD operator+(const CD& a, const CD& b) { return CD(a.r+b.r, a.i+b.i); }
CD operator-(const CD& a, const CD& b) { return CD(a.r-b.r, a.i-b.i); }
const double pi = acos(-1.0);
/* NTT */ struct CD { tf x;     CD(tf x_) : x(x_) {}     CD() {}    };
CD operator+(const CD& a, const CD& b) { return CD(addmod(a.x, b.x)); }//ETC
vector<tf> rts(MAXN+9,-1);
CD root(int n, bool inv){
	tf r = rts[n]<0 ? rts[n] = expmod(RT,(MOD-1)/n) : rts[n];
	return CD(inv ? expmod(r, MOD-2) : r);
}
/* AMBOS */ CD cp1[MAXN+9], cp2[MAXN+9];
int R[MAXN+9];
void dft(CD* a, int n, bool inv){
	forn(i, n) if(R[i] < i) swap(a[R[i]], a[i]);
	for(int m = 2; m <= n; m *= 2){
		/* FFT */ double z = 2*pi/m * (inv?-1:1);
		/* FFT */ CD wi = CD(cos(z), sin(z));
		/* NTT */ CD wi = root(m, inv);
		for(int j = 0; j < n; j += m){
			CD w(1);
			for(int k = j, k2 = j+m/2; k2 < j+m; k++, k2++){
				CD u = a[k]; CD v = a[k2]*w; a[k] = u+v; a[k2] = u-v; w = w*wi;
			}
		}
	}
	/* FFT */ if(inv) forn(i, n) a[i] /= n;
	/* NTT */ if(inv){
		CD z(expmod(n, MOD-2));
		forn(i, n) a[i] = a[i]*z;
	}
}
poly multiply(poly& p1, poly& p2){
	int n = sz(p1)+sz(p2)+1;
	int m = 1, cnt = 0;
	while(m <= n) m *= 2, cnt ++;
	forn(i, m) { R[i] = 0; forn(j, cnt) R[i] = (R[i]<<1)|((i>>j)&1); }
	forn(i, m) cp1[i] = 0, cp2[i] = 0;
	forn(i, sz(p1)) cp1[i] = p1[i];
	forn(i, sz(p2)) cp2[i] = p2[i];
	dft(cp1, m, false); dft(cp2, m, false);
	// fast eval: forn(i, sz(p1)) p1(expmod(RT, (MOD-1)/m*i)) == cp1[i].x
	forn(i, m) cp1[i] = cp1[i]*cp2[i];
	dft(cp1, m, true);
	poly res;
	n -= 2;
	/* FFT */ forn(i, n) res.pb((tf)floor(cp1[i].real()+0.5));
	/* NTT */ forn(i, n)res.pb(cp1[i].x);
	return res;
}
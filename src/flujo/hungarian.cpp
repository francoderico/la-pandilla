// Minima asignacion en O(n^3)
// Lado izquierdo [0..n), lado derecho [0..m). OJO: n <= m
typedef long double td; typedef vector<int> vi; typedef vector<td> vd;
const td INF = 1e100;	   // Para max asignacion, INF = 0, y negar costos
bool zero(td x) {return fabs(x) < 1e-9;}	// Para int/ll: return x==0;
vector<pii> ans; // Guarda las aristas usadas en el matching: [0..n)x[0..m)
struct Hungarian{
	int n; vector<vd> cs; vi L, R;
	Hungarian(int N, int M) : n(max(N,M)), cs(n,vd(n)), L(n), R(n){
		forn(x, N) forn(y, M) cs[x][y] = INF;
	}
	void set(int x, int y, td c) { cs[x][y] = c; }
	td assign(){
		int mat = 0; vd ds(n), u(n), v(n); vi dad(n), sn(n);
		forn(i, n) u[i] = *min_element(all(cs[i]));
		forn(j, n){
			v[j] = cs[0][j]-u[0];
			forr(i, 1, n) v[j] = min(v[j], cs[i][j] - u[i]);
		}
		L = R = vi(n, -1);
		forn(i, n) forn(j, n) if(R[j] == -1 and zero(cs[i][j] - u[i] - v[j])){
			L[i] = j; R[j] = i; mat++; break;
		}
		for(; mat < n; mat ++){
			int s = 0, j = 0, i;
			while(L[s] != -1) s++;
			fill(all(dad), -1); fill(all(sn), 0);
			forn(k, n) ds[k] = cs[s][k]-u[s]-v[k];
			while(true){
				j = -1;
				forn(k, n) if(!sn[k] and (j == -1 or ds[k] < ds[j])) j = k;
				sn[j] = 1; i = R[j];
				if(i == -1) break;
				forn(k, n) if(!sn[k]){
					auto new_ds = ds[j] + cs[i][k] - u[i]-v[k];
					if(ds[k] > new_ds) ds[k]=new_ds, dad[k]=j;
				}
			}
			forn(k, n) if(k!=j and sn[k]){
				auto w = ds[k]-ds[j]; v[k] += w, u[R[k]] -= w;
			}			
			u[s] += ds[j];
			while(dad[j] >= 0){ int d = dad[j]; R[j] = R[d]; L[R[j]] = j; j = d; }
			R[j] = s; L[s] = j;
		}
		td value = 0; forn(i, n) value += cs[i][L[i]], ans.pb({i, L[i]});
		return value;
	}
};
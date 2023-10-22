double reduce(vector<vector<double>> &a){  // returns determinant (solo tiene sentido si m == n)
	int m = sz(a), n = sz(a[0]);
	int i = 0, j = 0;
	double r = 1.0;
	while(i < m and j < n){
		int h = i;
		forr(k, i+1, m) if(abs(a[k][j]) > abs(a[h][j])) h = k;
		if(abs(a[h][j]) < EPS){
			j ++;
			r = 0.0;
			continue;
		}
		if(h != i){
			r = -r;
			swap(a[i], a[h]);
		}
		r *= a[i][j];
		dforr(k, j, n) a[i][k] /= a[i][j];
		forr(k, 0, m){
			if(k == i) continue;
			dforr(l_, j, n) a[k][l_] -= a[k][j] * a[i][l_];
		}
		i ++; j ++;
	}
	return r;
}

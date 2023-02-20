// IMPORTANTE
const double EPS = 1e-4;

// Matriz m x n (m filas, n columnas)
double reduce(vector<vector<double>> &a)  // returns determinant (solo tiene sentido si m == n)
{
	int m = sz(a), n = sz(a[0]);
	int i = 0, j = 0;
    double r = 1.;

	while(i < m and j < n)
    {
		int h = i;

		forr(k, i+1, m) if(abs(a[k][j]) > abs(a[h][j])) h = k;
		
        if(abs(a[h][j]) < EPS)
        {
            j ++;
            r = 0.;
            continue;
        }

		if(h != i)
        {
            r = -r;
            swap(a[i], a[h]);
        }

		r *= a[i][j];

		dforr(k, j, n) a[i][k] /= a[i][j];
        
		forr(k, 0, m)
        {
			if(k == i) continue;
			dforr(l_, j, n) a[k][l_] -= a[k][j] * a[i][l_];
		}

		i ++; j ++;
	}

	return r;
}

// Vector de variables dependientes DESPUÉS DE REDUCIR
// if(ret.back() == n-1) -> es inconsistente
// if(ret == {0..n-2})   -> tiene solución única
// else                  -> tiene infinitas soluciones
vector<int> dep_variables(vector<vector<double>> &a)
{
	vector<int> ret;
	int m = sz(a), n = sz(a[0]);

	forn(i, m)
	{
		forn(j, n) if(abs(a[i][j]) > EPS) {ret.pb(j); break;}
	}

	return ret;
}
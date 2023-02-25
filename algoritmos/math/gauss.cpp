// IMPORTANTE
const double EPS = 1e-4;

// Matriz m x n (m filas, n columnas)
double reduce(vector<vector<double>> &a)  // returns determinant (solo tiene sentido si m == n)
{
	int m = sz(a), n = sz(a[0]);
	int i = 0, j = 0;
	double r = 1.0;

	while(i < m and j < n)
	{
		int h = i;

		forr(k, i+1, m) if(abs(a[k][j]) > abs(a[h][j])) h = k;
		
		if(abs(a[h][j]) < EPS)
		{
			j ++;
			r = 0.0;
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
// else				     -> tiene infinitas soluciones
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


//Dada una matriz de Markov A (todas las columnas suman 1) de nxn,
//encuentra un vector estocástico v tal que Av = v (un autovector estocástico de autovalor 1).
//Para esto resuelve (A-I)v = 0 y de las infinitas soluciones posibles agarra el estocástico.
vector<ld> markov(vector<vector<ld>> &a)
{
	//assert(sz(a) > 0 and sz(a) == sz(a[0]));
	int m = sz(a);
	forn(i, m) a[i][i] += -1., a[i].pb(0.);	//Restamos I y agregamos el ti al que queremos llegar (0)

	reduce(a);

	ld escala = 1.;

    forn(i, m-1) escala += -a[i][m-1];

	vector<ld> v(m);
    v[m-1] = 1/escala;

    dforn(i, m-1) v[i] = -a[i][m-1] * v[m-1];

	return v;
}
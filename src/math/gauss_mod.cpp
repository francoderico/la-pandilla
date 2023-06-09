ll expmod(ll b, ll e)
{
	if(b <= 1) return b;
	if(e == 0) return 1;
	ll q = expmod(b, e/2), p = q*q % MOD;
	return e%2 == 0 ? p : p*b % MOD;
}

ll inv(ll b)
{
	return expmod(b, MOD-2);
}

ll addmod(ll a, ll b)
{
	ll r = a+b;
	return r < MOD ? r : r-MOD;
}

ll submod(ll a, ll b)
{
	ll r = a-b;
	return r >= 0 ? r : r+MOD;
}

// Reduce la matriz mod MOD
ll reduce(vector<vector<ll>> &a)    // returns determinant (solo tiene sentido si m == n)
{
	int m = sz(a), n = sz(a[0]);
	int i = 0, j = 0;
	ll r = 1;

	while(i < m and j < n)
	{
		int h = i;

		forr(k, i+1, m) if(a[k][j] > a[h][j]) h = k;
		
		if(a[h][j] == 0)
		{
			j ++;
			r = 0;
			continue;
		}

		if(h != i)
		{
			r = submod(0, r);
			swap(a[i], a[h]);
		}

		r = r * a[i][j] % MOD;

		dforr(k, j, n) a[i][k] = a[i][k] * inv(a[i][j]) % MOD;
		
		forr(k, 0, m)
		{
			if(k == i) continue;
			dforr(l_, j, n) a[k][l_] = submod(a[k][l_], a[k][j]*a[i][l_]%MOD);
		}

		i ++; j ++;
	}

	return r;
}


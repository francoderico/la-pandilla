ll expmod(ll b, ll e)
{
    if(e == 0) return 1;
    ll q = expmod(b, e/2), p = q*q % MOD;
    return e%2 == 0 ? p : p*b % MOD;
}

ll inv(ll b)
{
    return expmod(b, MOD-2);
}

ll mod(ll a)
{
	return (a % MOD + MOD) % MOD;
}

// Reduce la matriz mod MOD
void reduce(vector<vector<ll>> &a)
{
	int m = sz(a), n = sz(a[0]);
	int i = 0, j = 0;

	while(i < m and j < n)
    {
		int h = i;

		forr(k, i+1, m) if(a[k][j] > a[h][j]) h = k;
		
        if(a[h][j] == 0)
        {
            j ++;
            continue;
        }

		if(h != i)
        {
            swap(a[i], a[h]);
        }

		dforr(k, j, n) a[i][k] = a[i][k] * inv(a[i][j]) % MOD;
        
		forr(k, 0, m)
        {
			if(k == i) continue;
            dforr(l_, j, n) a[k][l_] = mod(a[k][l_] - a[k][j]*a[i][l_]);
		}

		i ++; j ++;
	}
}


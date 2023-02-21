const int N = 64;	//Tamaño del bitset, puede ser cualquier cosa

// Reduce la matriz mod 2
void reduce(vector<bitset<N>> &a)
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
        
		forr(k, 0, m)
        {
			if(k == i or a[k][j] == 0) continue;
            dforr(l_, j, n) a[k][l_] = a[k][l_]^a[i][l_];
		}

		i ++; j ++;
	}
}


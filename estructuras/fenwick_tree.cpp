struct Fenwick  //0-indexed
{
    int n;
    vector<int> tree;
    Fenwick(int n_) : n(n_), tree(n_+1, 0) {}

    void upd(int i, int x)  //Le sumo x al elemento en posicion i
    {
        for(i += 1; i <= n; i += i & -i) tree[i] += x;
    }

    int query(int b)        //Devuelve la suma de los elementos en [0..b)
    {
        int s = 0;
        
        for(int i = b; i; i -= i & -i) s += tree[i];
        
        return s;
    }
};

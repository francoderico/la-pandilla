ll num_prime_factors(map<ll, int> &F)
{
    ll ret = 0;
    for(auto &it : F) ret += it.snd;
    return ret;
}

ll num_dif_prime_factors(map<ll, int> &F)
{
    ll ret = 0;
    for(auto &it : F) ret += 1;
    return ret;
}

ll sum_prime_factors(map<ll, int> &F)
{
    ll ret = 0;
    for(auto &it : F) ret += it.fst;
    return ret;
}

ll num_divs(map<ll, int> &F)
{
    ll ret = 1;
    for(auto &it : F) ret *= it.snd + 1;
    return ret;
}

ll sum_divs(map<ll, int> &F)
{
    ll ret = 1;
    
    for(auto &it : F)
    {
        ll pot = 1, aux = 0;
        forn(i, it.snd + 1) aux += pot, pot *= it.fst;
        ret *= aux;
    }
    
    return ret;
}

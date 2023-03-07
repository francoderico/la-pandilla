// Cantidad de numeros coprimos y menores a n, dada su factorizacion
ll phi(ll n, map<ll, int> &F)
{
    ll ret = n;
    for(auto &it : F) ret -= ret / it.fst;
    return ret;
}

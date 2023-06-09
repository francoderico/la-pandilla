// Mas rapido que el de phi.
// Si phi ya esta codeada y entra, o si pide exponente, usar esa.
// Si no, USAR ESTA.
ll inv(ll a, ll m){
    //assert(gcd(a, m) == 1);
    ll x = extended_euclid(a, m).fst;   //a*x + m*y = 1 => a*x=1(mod m)
    return ((x % m) + m) % m;
}

// Usar solo si MAXN es muy grande y no puedo calcular todos en O(n)
ll inv(ll a, ll m)
{
    return expmod(a, phi(m)-1, m);  //Si m NO es primo (sacar a mano)
    return expmod(a, m-2, m);       //Si m es primo
}

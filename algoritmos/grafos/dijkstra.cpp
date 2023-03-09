
// struct edge { int v, w; };    vector<edge> g[MAXN];
 
struct path { int u; ll d; };
bool operator<(path a, path b) { return a.d > b.d; }
 
vector<ll> dijkstra(int s) {
    vector<ll> D(n, INF); // vector<int> P(n, -1);
    priority_queue<path> pq;
    pq.push({s, 0}); D[s] = 0; // P[s] = s;
    while (not pq.empty()) {
        auto [u, du] = pq.top(); pq.pop();
        if (du > D[u]) continue;
        for (auto e : g[u]) {
            int v = e.v; ll dv = du + e.w;
            if (dv >= D[v]) continue;
            pq.push({v, dv}); D[v] = dv; // P[v] = u;
        }
    }
    return D; // return P;
}
 
vector<int> camino(vector<int>const& P, int d) {
    vector<int> res; res.pb(d);
    while (d != P[d]) { d = P[d]; res.pb(d); }
    reverse(all(res)); return res;
}

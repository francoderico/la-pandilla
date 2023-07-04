#include <ext/pb_ds/assoc_container.hpp> 
using namespace __gnu_pbds;
template<typename T>
using indexed_set = tree<T,null_type,less<T>,rb_tree_tag, tree_order_statistics_node_update>;

#define val find_by_order //[]
#define idx order_of_key 


//Uso:
indexed_set<ll> s;
s.insert(5);
s.erase(5);
ll x = s.val(0); //x = s[0]
int i = s.idx(5) //s[i] == 5

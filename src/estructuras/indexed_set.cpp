#include <ext/pb_ds/assoc_container.hpp> 
using namespace __gnu_pbds;
template<typename Key, typename Val=null_type>
using indexed_set = tree<Key, Val, less<Key>, rb_tree_tag,
                         tree_order_statistics_node_update>;
// indexed_set<char> s;
// char val = s.find_by_order(0); // acceso por indice
// int idx = s.order_of_key('a'); // busca indice del valor

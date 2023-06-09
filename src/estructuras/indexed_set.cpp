#include <ext/pb_ds/assoc_container.hpp> 
using namespace __gnu_pbds;
typedef ll tipo;
typedef tree<tipo,null_type,less<tipo>,rb_tree_tag, tree_order_statistics_node_update> indexed_set;

#define val find_by_order //[]
#define idx order_of_key 


//Uso:
indexed_set s;
s.insert(5);
s.erase(5);
ll x = s.val(0); //x = s[0]
int i = s.idx(5) //s[i] == 5

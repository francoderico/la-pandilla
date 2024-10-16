vector<int> g[MAXN]; int n; bool tk[MAXN];
int fat[MAXN]; // father in centroid decomposition
int szt[MAXN]; // size of subtree
int calcsz(int x, int f){
	szt[x]=1;
	for(auto y:g[x])if(y!=f&&!tk[y])szt[x]+=calcsz(y,x);
	return szt[x];
}
void cdfs(int x=0, int f=-1, int sze=-1){ // O(nlogn)
	if(sze<0)sze=calcsz(x,-1);
	for(auto y:g[x])if(!tk[y]&&szt[y]*2>=sze){
		szt[x]=0;cdfs(y,f,sze);return;
	}
	tk[x]=true;fat[x]=f;
	for(auto y:g[x])if(!tk[y])cdfs(y,x);
}
void centroid() { memset(tk,false,sizeof(tk)); cdfs(); }
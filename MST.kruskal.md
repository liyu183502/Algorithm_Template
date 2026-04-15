## kruskal
结构：1.结构体存边，2.并查集，3.从小到大加边
```cpp
int fa[N];
struct edge{
	int u, v, w;
	bool operator<(const edge &o) const{
		return w < o.w;
	}
};

int find(int x){
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void solve(){
    int n, m;
    cin >> n >> m;

	iota(fa, fa + n + 1, 0);
    for (int i = 1; i <= m; i ++ ){
		int u, v, w;
        cin >> u >> v >> w;
        e.pb{u, v, w};
    }
    sort(all(e));

    int sum = 0;
    for (auto [u, v, w] : e){
		int x = find(u), y = find(v);
		if(x != y){
			fa[x] = y;
			sum += w;
		}
	}
}
```
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

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void solve(){
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i ++ ){
		int u, v, w;
        cin >> u >> v >> w;
        e.push_back({u, v, w});
    }

	iota(fa, fa + n + 1, 0);
    sort(e.begin(), e.end());

    int sum = 0;
    for (auto [u, v, w] : e) {
		int x = find(u), y = find(v);
		if(x != y){
			fa[x] = y;
			sum += w;
		}
	}
}
```

```cpp
struct DSU {
	vector<int> fa, sz;
	DSU() {}
	DSU(int n) {
		init(n);
	}
	void init(int n) {
		fa.resize(n + 1);
		sz.assign(n + 1, 1);

		for (int i = 1; i <= n; i++) {
			fa[i] = i;
		}
	}

	int find(int x) {
		if (fa[x] == x) return x;
		return fa[x] = find(fa[x]);
	}

	bool same(int x, int y) {
		return find(x) == find(y);
	}

	bool merge(int x, int y) {
		x = find(x);
		y = find(y);

		if (x == y) return false;

		if (sz[x] < sz[y]) swap(x, y);

		fa[y] = x;
		sz[x] += sz[y];

		return true;
	}

	int size(int x) {
		return sz[find(x)];
	}
};

struct edge {
	int u, v, w;

	bool operator<(const edge &t) const {
		return w < t.w;
	}
};

void solve() {
	int n, m;
	cin >> n >> m;

	vector<edge> e(m);
	for (auto &[u, v, w] : e) {
		cin >> u >> v >> w;
	}

	sort(e.begin(), e.end());

	DSU dsu(n);

	int ans = 0;
	int cnt = 0;

	for (auto [u, v, w] : e) {
		if(dsu.merge(u, v)) {
			ans += w;
			cnt++;

			if(cnt == n - 1) break;
		}
	}

	if(cnt != n - 1) {
		cout << -1 << endl;  // 图不连通
	}
	else {
		cout << ans << endl;
	}
}
```
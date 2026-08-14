#### prim
```cpp
void solve() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> g(n + 1, vector<int>(n + 1, inf));
	for (int i = 1; i <= n; i++) g[i][i] = 0;

	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u][v] = g[v][u] = min(g[u][v], w);
	}

	vector<int> d(n + 1, inf), vis(n + 1);
	d[1] = 0;

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int u = 0;
		for (int j = 1; j <= n; j++) {
			if(!vis[j] && (!u || d[j] < d[u])) u = j;
		}

        // 不连通
		if(d[u] == inf) {
			cout << -1 << endl;
			return;
		}

		vis[u] = 1;
		ans += d[u];

		for (int v = 1; v <= n; v++)
			d[v] = min(d[v], g[u][v]);
	}

	cout << ans << endl;
}
```
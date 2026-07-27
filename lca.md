先dfs求深度和父节点，然后先把两个点跳到同一高度，然后一起往上跳  
```cpp
	const int LOG = 20;
	vector<vector<int>> g(n + 1), fa(n + 1, vector<int>(LOG + 1));
	vector<int> dep(n + 1);

	for (int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	auto dfs = [&](auto &&self, int u, int father) -> void {
		dep[u] = dep[father] + 1;
		fa[u][0] = father;

		for (int j = 1; j <= LOG; j++) {
			fa[u][j] = fa[fa[u][j - 1]][j - 1];
		}

		for (auto v : g[u]) {
			if(v == father) continue;
			self(self, v, u);
		}
	};

	dfs(dfs, root, 0);

	auto lca = [&](int u, int v) -> int {
		if(dep[u] < dep[v]) swap(u, v);

		for (int j = LOG; j >= 0; j--) {
			if(dep[fa[u][j]] >= dep[v]) {
				u = fa[u][j];
			}
		}

		if(u == v) return u;

		for (int j = LOG; j >= 0; j--) {
			if(fa[u][j] != fa[v][j]) {
				u = fa[u][j];
				v = fa[v][j];
			}
		}

		return fa[u][0];
	};
```
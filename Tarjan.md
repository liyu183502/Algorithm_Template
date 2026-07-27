### 有向图
dfn：dfs序  
low[u] 表示：从 u 以及 u 的 DFS 子树出发，通过当前还没有确定 SCC 的节点，最早能够到达的节点的 dfn  
vis：是否在stack里面（未分配scc）  
bel：属于哪个scc  

### 注意点：
复杂度(n + m)  
scc的顺序是逆拓扑序  
```cpp
void solve(){
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n + 1);
	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
	}

	vector<int> dfn(n + 1), low(n + 1), bel(n + 1), sz(n + 1);
	vector<int> stk;
	vector<bool> vis(n + 1);
	int tim = 0, scc = 0;
	auto tarjan = [&](auto &&self, int u) -> void {
		dfn[u] = low[u] = ++tim;
		stk.push_back(u);
		vis[u] = true;

		for (int v : g[u]) {
			if (!dfn[v]) {
				self(self, v);
				low[u] = min(low[u], low[v]);
			}
			else if (vis[v]) {
				low[u] = min(low[u], dfn[v]);
			}
		}

		if (dfn[u] == low[u]) {
			scc++;

			while(true) {
				int v = stk.back();
				stk.pop_back();

				vis[v] = false;
				bel[v] = scc;
				sz[scc]++;

				if(v == u) break;
			}
		}
	};

	for (int i = 1; i <= n; i++) {
		if(!dfn[i]) {
			tarjan(tarjan, i);
		}
	}

	cout << scc << endl;

	for (int i = 1; i <= n; i++) {
		cout << bel[i] << " \n"[i == n];
	}
}
```

## 定义
强连通：在一个有向图中，如果点 u 能到达点 v，并且点 v 也能到达点 u，那么称 u,v 强连通。
强连通分量：一个强连通分量 SCC，就是一个尽可能大的点集，其中任意两个点都能互相到达。

## 为什么要找强连通分量
作用：把有向图中的环压缩成一个点，使原图变成 DAG（有向无环图）。
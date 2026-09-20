## Tarjan
### 有向图强连通分量
dfn：dfs序  
low[u] 表示：从 u 以及 u 的 DFS 子树出发，通过当前还没有确定 SCC 的节点，最早能够到达的节点的 dfn  
vis：是否在stack里面（未分配scc）  
bel：属于哪个scc  

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

**定义**:
强连通：在一个有向图中，如果点 u 能到达点 v，并且点 v 也能到达点 u，那么称 u,v 强连通。
强连通分量：一个强连通分量 SCC，就是一个尽可能大的点集，其中任意两个点都能互相到达。

**为什么要找强连通分量**
作用：把有向图中的环压缩成一个点，使原图变成 DAG（有向无环图）。


## 无向图边双连通分量（EBCC）
bridge[id]:表示第 id 条边是否为桥
bel[u]表示点 u 属于哪个边双
sz[id]表示第 id 个边双的点数
cnt表示边双数量。
```cpp
void solve() {
	int n, m;
	cin >> n >> m;

	vector<vector<pii>> g(n + 1);
	vector<pii> e(m + 1);

	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		e[i] = {u, v};
		g[u].push_back({v, i});
		g[v].push_back({u, i});
	}

	vector<int> dfn(n + 1), low(n + 1);
	vector<int> bridge(m + 1);
	int tim = 0;

	auto tarjan = [&](auto &&self, int u, int id) -> void {
		dfn[u] = low[u] = ++tim;

		for (auto [v, eid] : g[u]) {
			if(eid == id) continue;

			if(!dfn[v]) {
				self(self, v, eid);
				low[u] = min(low[u], low[v]);

				if(low[v] > dfn[u]) {
					bridge[eid] = 1;
				}
			}
			else {
				low[u] = min(low[u], dfn[v]);
			}
		}
	};

	for (int i = 1; i <= n; i++) {
		if(!dfn[i]) {
			tarjan(tarjan, i, -1);
		}
	}

	vector<int> bel(n + 1), sz(n + 1);
	int cnt = 0;

	auto dfs = [&](auto &&self, int u) -> void {
		bel[u] = cnt;
		sz[cnt]++;

		for (auto [v, id] : g[u]) {
			if(bridge[id] || bel[v]) continue;
			self(self, v);
		}
	};

	for (int i = 1; i <= n; i++) {
		if(!bel[i]) {
			cnt++;
			dfs(dfs, i);
		}
	}

	cout << cnt << endl;
	for (int i = 1; i <= n; i++) {
		cout << bel[i] << " \n"[i == n];
	}
}
```
---

## 相关
### 割点

对于无向图中的一个点 \(u\)，如果删除 \(u\) 以及与 \(u\) 相连的所有边后，图的连通块数量增加，那么 \(u\) 称为 **割点**。

对于非 DFS 根节点 \(u\)，如果存在儿子 \(v\) 满足：

\[
\boxed{low_v\ge dfn_u}
\]

则 \(u\) 是割点。

DFS 根节点需要特殊判断：

\[
\boxed{\text{根节点有至少两个 DFS 儿子}\Rightarrow\text{根是割点}}
\]

---

### 边双连通分量

\[
\boxed{\text{删掉所有桥以后，每一个连通块就是一个边双}}
\]

**单点也可以是边双**


#### 性质

无向图中：

\[
\boxed{\text{一条边不是桥}\iff\text{这条边处于某个环中}}
\]

所以大小大于 \(1\) 的边双中，任意一条边都可以通过其他路径绕开。

---


### 边双缩点
把每一个边双缩成一个点。
原图中的非桥边都在边双内部，所以缩点以后，只需要保留桥。

```cpp
vector<vector<int>> ng(cnt + 1);

for (int i = 1; i <= m; i++) {
	if(!bridge[i]) continue;

	auto [u, v] = e[i];

	int x = bel[u];
	int y = bel[v];

	ng[x].push_back(y);
	ng[y].push_back(x);
}
```

如果原图连通，那么：

\[
\boxed{\text{边双缩点后一定是一棵树}}
\]

如果原图不连通，则得到森林。

因此很多题的经典套路是：

\[
\boxed{\text{Tarjan 求边双}\rightarrow\text{缩点成树}\rightarrow\text{树上 DP}}
\]

---
## 最大流
复杂度O(n*n * m)
```cpp
struct Dinic {
	struct Edge {
		int v, c;
	};

	int n;
	vector<vector<int>> g;
	vector<Edge> e;
	vector<int> dep, cur;

	Dinic(int n) {
		this->n = n;
		g.resize(n + 1);
		dep.resize(n + 1);
		cur.resize(n + 1);
	}

	void add(int u, int v, int c) {
		g[u].push_back(e.size());
		e.push_back({v, c});

		g[v].push_back(e.size());
		e.push_back({u, 0});
	}

	bool bfs(int s, int t) {
		fill(dep.begin(), dep.end(), -1);

		queue<int> q;
		q.push(s);
		dep[s] = 0;

		while(q.size()) {
			int u = q.front();
			q.pop();

			for(auto id : g[u]) {
				auto [v, c] = e[id];

				if(c && dep[v] == -1) {
					dep[v] = dep[u] + 1;
					q.push(v);
				}
			}
		}

		return dep[t] != -1;
	}

	int dfs(int u, int t, int flow) {
		if(u == t) {
			return flow;
		}

		for(int &i = cur[u]; i < g[u].size(); i++) {
			int id = g[u][i];

			auto &[v, c] = e[id];

			if(c && dep[v] == dep[u] + 1) {
				int x = dfs(v, t, min(flow, c));

				if(x) {
					c -= x;
					e[id ^ 1].c += x;
					return x;
				}
			}
		}

		return 0;
	}

	int maxflow(int s, int t) {
		int ans = 0;

		while(bfs(s, t)) {
			fill(cur.begin(), cur.end(), 0);

			while(int x = dfs(s, t, inf)) {
				ans += x;
			}
		}

		return ans;
	}
};
```
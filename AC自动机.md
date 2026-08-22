## AC自动机
Tire + KMP

复杂度O(n + L)
```cpp
struct AC {
	struct Node {
		int ch[26] = {};
		int fail = 0;
		int cnt = 0;
	};

	vector<Node> tr{{}};
	vector<vector<int>> g;

	int insert(string s) {
		int u = 0;
		for(auto c : s) {
			int x = c - 'a';
			if(!tr[u].ch[x]) {
				tr[u].ch[x] = tr.size();
				tr.push_back({});
			}
			u = tr[u].ch[x];
		}
		tr[u].cnt++;
		return u;
	}

	void build() {
		queue<int> q;
		for(int i = 0; i < 26; i++) {
			if(tr[0].ch[i]) {
				q.push(tr[0].ch[i]);
			}
		}

		while(q.size()) {
			int u = q.front();
			q.pop();

			for(int i = 0; i < 26; i++) {
				int v = tr[u].ch[i];
				if(v) {
					tr[v].fail = tr[tr[u].fail].ch[i];
					q.push(v);
				}
				else {
					tr[u].ch[i] = tr[tr[u].fail].ch[i];
				}
			}
		}

		g.assign(tr.size(), {});
		for(int i = 1; i < tr.size(); i++) {
			g[tr[i].fail].push_back(i);
		}
	}

	vector<int> query(string s) {
		vector<int> ans(tr.size());
		int u = 0;

		for(auto c : s) {
			u = tr[u].ch[c - 'a'];
			ans[u]++;
		}

		auto dfs = [&](auto &&self, int u) -> void {
			for(auto v : g[u]) {
				self(self, v);
				ans[u] += ans[v];
			}
		};

		dfs(dfs, 0);
		return ans;
	}
};
```
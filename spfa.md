## spfa  
用途：
1.带负边的单源最短路

2.判断负环

3.求解差分约束
```cpp
    vector<vector<pii>> g(n + 1);
	vector<int> d(n + 1, inf), cnt(n + 1), vis(n + 1);
	queue<int> q;
	d[s] = 0;
	q.push(s);
	vis[s] = 1;
	while(q.size()) {
		int u = q.front();
		q.pop();
		vis[u] = 0;

		for (auto [v, w] : g[u]) {
			if(d[v] > d[u] + w) {
				d[v] = d[u] + w;
				cnt[v] = cnt[u] + 1;

				if(cnt[v] >= n) {
					// 存在负环
				}

				if(!vis[v]) {
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	}
```
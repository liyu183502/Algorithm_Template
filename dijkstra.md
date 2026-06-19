## dijkstra  
## 区别：1.优先队列q存pii
```cpp
	vector<vector<pii>> g(n + 1);
	vector<int> d(n + 1, inf);
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		f[a].pb({b, c});
		g[b].pb({a, c});
	}

	priority_queue<pii, vector<pii>, greater<pii>> q;
	q.push({0, 1});
	d[1] = 0;
	while(q.size()){
		auto t = q.top();  //top
		int u = t.second;
		q.pop();
		for (auto [v, w] : g[u]){
			if(d[v] > d[u] + w){
				d[v] = d[u] + w;
				q.push({d[v], v});
			}
		}
	}
```
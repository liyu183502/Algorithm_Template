## dijkstra  
区别：1.优先队列q存pii
```cpp
	vector<vector<pii>> g(n + 1);
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		f[a].push_back({b, c});
		g[b].push_back({a, c});
	}
	
	vector<int> d(n + 1, INF);
	priority_queue<pii, vector<pii>, greater<pii>> q;
	q.push({0, 1});
	d[1] = 0;
	while(q.size()){
		auto [dis, u] = q.top();
		q.pop();
		if(dis != d[u]) continue; // 丢弃同一个点较大的旧距离
		for (auto [v, w] : g[u]){
			if(d[v] > d[u] + w){
				d[v] = d[u] + w;
				q.push({d[v], v});
			}
		}
	}
```
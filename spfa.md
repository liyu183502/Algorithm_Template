## spfa  
### 作用：处理负权，判负环  
### 区别：1.不用优先队列，2.要标记数组vis（dj不用，因为每个点只入队一次，3.计数数组cnt
```cpp
    vector<vector<pii>> g(n + 1);  //最短路都是pii，bfs是vvi
	queue<int> q;
	q.push(s);
	vi ds(n + 1, -inf), cnt(n + 1), vis(n + 1);  //定义数组
	ds[s] = d;  //初始化数组，每个数组都考虑一次
    vis[s] = 1;
	while(q.size()){
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for (auto [v, w] : g[u]){
			if(ds[v] < ds[u] + w){
				ds[v] = ds[u] + w;
				if(!vis[v]){
					cnt[v] ++;  //统计入队次数 
					if(cnt[v] >= n){
						cout << -1 << endl;
						return;
					}
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	} 
```
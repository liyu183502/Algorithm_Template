## TSP旅行商问题
dp[s][i] : s记录目前经过所有点，i表示当前位置

w 为 1 下标
```cpp
int tsp(vector<vector<int>> &w) {
	int n = w.size() - 1;
	int m = 1 << n;
	vector<vector<int>> dp(m, vector<int>(n + 1, inf));
	dp[1][1] = 0;

	for (int s = 0; s < m; s++) {
		if(!(s & 1)) continue;
		for (int i = 1; i <= n; i++) {
			if(!(s >> (i - 1) & 1)) continue;
			if(dp[s][i] == inf) continue;
			for (int j = 1; j <= n; j++) {
				if(s >> (j - 1) & 1) continue;
				int ns = s | (1 << (j - 1));
				dp[ns][j] = min(dp[ns][j], dp[s][i] + w[i][j]);
			}
		}
	}

	int ans = inf;
	int full = m - 1;
	for (int i = 1; i <= n; i++) {
		ans = min(ans, dp[full][i] + w[i][1]);
	}
	return ans;
}
```
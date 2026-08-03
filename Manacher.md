## 用处
Manacher（马拉车）算法用于在线性时间内求：

最长回文子串；  
以每个位置为中心的最长回文半径；  
回文子串数量；  
判断某个子串是否为回文串  

```cpp
int manacher(string s) {
	string t = "$";
	for (auto c : s) {
		t += '#';
		t += c;
	}
	t += "#@";

	int n = t.size() - 1;
	vector<int> p(n + 1);

	int c = 0, r = 0;
	int ans = 0;

	for (int i = 1; i < n; i++) {
		if(i < r) {
			int j = 2 * c - i;
			p[i] = min(p[j], r - i);
		}

		while(t[i - p[i] - 1] == t[i + p[i] + 1]) {
			p[i]++;
		}

		if(i + p[i] > r) {
			c = i;
			r = i + p[i];
		}

		ans = max(ans, p[i]);
	}

	return ans;
}
```
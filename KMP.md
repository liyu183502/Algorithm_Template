## KMP
复杂度 O(n + m)

s 主串， t 子串

0 下标

KMP 的 fail：当前位置结尾，最长的相同前后缀
```cpp
vector<int> get_nxt(string s) {
	int n = s.size();
	vector<int> nxt(n);

	for (int i = 1, j = 0; i < n; i++) {
		while(j && s[i] != s[j]) {
			j = nxt[j - 1];
		}
		if(s[i] == s[j]) j++;
		nxt[i] = j;
	}

	return nxt;
}

vector<int> kmp(string s, string t) {
	int n = s.size(), m = t.size();
	auto nxt = get_nxt(t);

	vector<int> ans;
	for (int i = 0, j = 0; i < n; i++) {
		while(j && s[i] != t[j]) {
			j = nxt[j - 1];
		}
		if(s[i] == t[j]) j++;

		if(j == m) {
			ans.push_back(i - m + 1);
			j = nxt[j - 1];
		}
	}

	return ans;
}
```


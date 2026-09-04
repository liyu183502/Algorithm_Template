## 拓展KMP
Z 函数：当前位置开头，和整个字符串开头最长能匹配多少

z[i] 表示字符串 s 从第 i 个位置开始的后缀，和整个字符串 s 的LCP长度

LCP：最长公共前缀

Z函数：
```cpp
vector<int> z_function(string s) {
	s = " " + s;
	int n = s.size() - 1;
	vector<int> z(n + 1);
	z[1] = n;
	int l = 1, r = 1;

	for (int i = 2; i <= n; i++) {
		if(i <= r) {
			z[i] = min(z[i - l + 1], r - i + 1);
		}
		while(i + z[i] <= n && s[1 + z[i]] == s[i + z[i]]) {
			z[i]++;
		}
		if(i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	return z;
}
```

p[i] 表示字符串 a 从第 i 个位置开始的后缀，和字符串 b 的LCP长度
```cpp
vector<int> exkmp(string a, string b, vector<int> &z) {
	a = " " + a;
	b = " " + b;
	int n = a.size() - 1;
	int m = b.size() - 1;
	vector<int> p(n + 1);
	int l = 1, r = 0;

	for (int i = 1; i <= n; i++) {
		if(i <= r) {
			p[i] = min(z[i - l + 1], r - i + 1);
		}
		while(i + p[i] <= n && p[i] + 1 <= m && a[i + p[i]] == b[p[i] + 1]) {
			p[i]++;
		}
		if(i + p[i] - 1 > r) {
			l = i;
			r = i + p[i] - 1;
		}
	}
	return p;
}
```
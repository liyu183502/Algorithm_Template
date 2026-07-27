## 01Trie
字典树是一种按照前缀组织数据的树结构。字符串 Trie 的边表示字符，01 Trie 的边表示二进制位。查询最大异或时，从高位到低位处理，当前位应优先选择与查询数相反的分支，从而让异或结果的高位尽量为 1。01 Trie 是竞赛中处理异或最大值、最小值、阈值查询和动态异或问题的常用数据结构。

Node：维护节点
```cpp
struct Trie {
	struct Node {
		int ch[2] = {};
	};

	vector<Node> tr{{}};

	void add(int x) {
		int u = 0;
		for (int i = 30; i >= 0; i--) {
			int c = x >> i & 1;
			if(!tr[u].ch[c]) {
				tr[u].ch[c] = tr.size();
				tr.push_back({});
			}
			u = tr[u].ch[c];
		}
	}

	int query(int x) {
		int u = 0, ans = 0;
		for (int i = 30; i >= 0; i--) {
			int c = x >> i & 1;
			if(tr[u].ch[c ^ 1]) {
				ans |= 1ll << i;
				u = tr[u].ch[c ^ 1];
			}
			else u = tr[u].ch[c];
		}
		return ans;
	}
};
```
<br><br>


## 字符串Trie
```cpp
struct Trie {
	struct Node {
		int ch[26] = {};
		int cnt = 0;
	};

	vector<Node> tr{{}};

	void add(string s) {
		int u = 0;
		for (char c : s) {
			int x = c - 'a';
			if(!tr[u].ch[x]) {
				tr[u].ch[x] = tr.size();
				tr.push_back({});
			}
			u = tr[u].ch[x];
		}
		tr[u].cnt++;
	}

	int query(string s) {
		int u = 0;
		for (char c : s) {
			int x = c - 'a';
			if(!tr[u].ch[x]) return 0;
			u = tr[u].ch[x];
		}
		return tr[u].cnt;
	}
};
```
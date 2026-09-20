## 珂朵莉树
```cpp
struct ODT {
	struct Node {
        int l, r;
		mutable int v;

		bool operator < (const Node &o) const {
			return l < o.l;
		}
	};

	set<Node> s;

	auto split(int x) {
		auto it = s.lower_bound({x, 0, 0});

		if(it != s.end() && it->l == x) {
			return it;
		}

		--it;

		int l = it->l;
		int r = it->r;
		int v = it->v;

		s.erase(it);
		s.insert({l, x - 1, v});

		return s.insert({x, r, v}).first;
	}

	void assign(int l, int r, int x) {
		auto itr = split(r + 1);
		auto itl = split(l);

		s.erase(itl, itr);
		s.insert({l, r, x});
	}

	void add(int l, int r, int x) {
		auto itr = split(r + 1);
		auto itl = split(l);

		for (auto it = itl; it != itr; it++) {
			it->v += x;
		}
	}

	int kth(int l, int r, int k) {
		auto itr = split(r + 1);
		auto itl = split(l);

		vector<pii> a;

		for (auto it = itl; it != itr; it++) {
			a.push_back({it->v, it->r - it->l + 1});
		}

		sort(a.begin(), a.end());

		for (auto [v, cnt] : a) {
			if(k <= cnt) {
				return v;
			}
			k -= cnt;
		}

		return -1;
	}

	int power(int a, int b, int mod) {
		int res = 1 % mod;
		a %= mod;

		while(b) {
			if(b & 1) {
				res = res * a % mod;
			}
			a = a * a % mod;
			b >>= 1;
		}

		return res;
	}

	int sum(int l, int r, int x, int mod) {
		auto itr = split(r + 1);
		auto itl = split(l);

		int ans = 0;

		for (auto it = itl; it != itr; it++) {
			int len = it->r - it->l + 1;
			ans = (ans + len * power(it->v, x, mod)) % mod;
		}

		return ans;
	}
};
```
## 符合条件的前缀和
```cpp
struct Fenwick {
	int n;
	vector<int> bit;

	Fenwick(int n = 0) {
		init(n);
	}

	void init(int n_) {
		n = n_;
		bit.assign(n + 1, 0);
	}

	int lowbit(int x) {
		return x & -x;
	}

	void add(int idx, int val) {
		for (; idx <= n; idx += lowbit(idx)) {
			bit[idx] += val;
		}
	}

	int query(int idx) {
		int res = 0;
		for (; idx > 0; idx -= lowbit(idx)) {
			res += bit[idx];
		}
		return res;
	}

	int query(int l, int r) {
		if(l > r) return 0;
		return query(r) - query(l - 1);
	}
};
```

## 前缀最大值
```cpp
struct BITMax {
	int n;
	vector<int> bit;

	BITMax(int n_) {
		init(n_);
	}

	void init(int n_) {
		n = n_;
		bit.assign(n + 1, -inf);
	}

	void update(int x, int v) {
		for (int i = x; i <= n; i += i & -i) {
			bit[i] = max(bit[i], v);
		}
	}

	int query(int x) {
		int res = -inf;
		for (int i = x; i; i -= i & -i) {
			res = max(res, bit[i]);
		}
		return res;
	}
};
```

```cpp
int s[N];
int lowbit(int x){
    return x & -x;
}
//树状数组
void change(int x, int k){
    while(x <= n) {
        s[x] += k;
        x += lowbit(x);
    }
}

int query(int x){
    int sum = 0;
    while(x){
        sum += s[x];
        x -= lowbit(x);
    }
    return sum;
}
```
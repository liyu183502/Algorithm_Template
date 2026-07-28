## segment（优化算法，用于暴力很简单，但是复杂度高的题目）
应用场景：1.多次查询，单点或区间修改，2.判断能否使用：关键在于区间能否状态转移  
```cpp
template<class Info>
struct SegmentTree {
	int n;
	vector<Info> info;

	template<class T>
	SegmentTree(vector<T> a) {
		init(a);
	}

	void init(int n_, Info v = Info()) {
		vector<Info> a(n_ + 1, v);
		init(a);
	}

	template<class T>
	void init(vector<T> a) {
		n = (int)a.size() - 1;
		info.assign(n * 4 + 5, Info());
		build(1, 1, n, a);
	}

	template<class T>
	void build(int i, int l, int r, vector<T> &a) {
		if (l == r) {
			info[i] = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(i << 1, l, mid, a);
		build(i << 1 | 1, mid + 1, r, a);
		pull(i);
	}

	void pull(int i) {
		info[i] = info[i << 1] + info[i << 1 | 1];
	}

	void modify(int pos, const Info &v) {
		modify(1, 1, n, pos, v);
	}

	void modify(int i, int l, int r, int pos, const Info &v) {
		if (l == r) {
			info[i] = v;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) modify(i << 1, l, mid, pos, v);
		else modify(i << 1 | 1, mid + 1, r, pos, v);

		pull(i);
	}

	Info query(int l, int r) {
		return query(1, 1, n, l, r);
	}

	Info query(int i, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) {
			return info[i];
		}
		int mid = (l + r) >> 1;
		if (qr <= mid) return query(i << 1, l, mid, ql, qr);
		if (ql > mid) return query(i << 1 | 1, mid + 1, r, ql, qr);
		return query(i << 1, l, mid, ql, qr)
			 + query(i << 1 | 1, mid + 1, r, ql, qr);
	}
};
struct Info {
	int mn = inf;
};

Info operator+(const Info &a, const Info & b) {
	return {min(a.mn, b.mn)};
}
```


```cpp
int add[N << 2], sum[N << 2], a[N];
#define lc i << 1
#define rc i << 1 | 1

void up(int i){
	sum[i] = sum[lc] + sum[rc]; 
}

void lazy(int i, int v, int n){
	sum[i] += v * n;
	add[i] += v;
}

void down(int i, int ln, int rn){
	if(add[i] != 0){
		lazy(lc, add[i], ln);
		lazy(rc, add[i], rn);
		add[i] = 0;
	}
}

void build(int l, int r, int i){
	if(l == r){
		sum[i] = a[l];
	}
	else {
		int mid = (l + r) >> 1;
		build(l, mid, lc);
		build(mid + 1, r, rc);
		up(i);
	}
	add[i] = 0;
}

void ad(int fl, int fr, int fv, int l, int r, int i){
	if(fl <= l && r <= fr){
		lazy(i, fv, r - l + 1);
	}
	else {
		int mid = (l + r) >> 1;
		down(i, mid - l + 1, r - mid);
		if(fl <= mid){
			ad(fl, fr, fv, l, mid, lc);
		}
		if(fr > mid){
			ad(fl, fr, fv, mid + 1, r, rc);
		}
		up(i);
	}
}

int query(int fl, int fr, int l, int r, int i){
	if(fl <= l && r <= fr){
		return sum[i];
	}
	else {
		int mid = (l + r) >> 1;
		down(i, mid - l + 1, r - mid);
		int ans = 0;
		if(fl <= mid){
			ans += query(fl, fr, l, mid, lc);
		}
		if(fr > mid){
			ans += query(fl, fr, mid + 1, r, rc);
		}
		return ans;
	}
}
```
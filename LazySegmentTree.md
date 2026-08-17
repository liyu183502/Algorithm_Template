Info = 线段树节点存什么
Tag = 懒标记存什么修改
operator+ = 左右儿子怎么合并
apply = 这个修改怎么作用到节点上
tag apply = 把新标记t叠加到当前标记上
Info apply = 将懒标记作用到当前区间（发挥作用，相当于下传了）

```cpp

template<class Info, class Tag>
struct LazySegmentTree {
	int n;
	vector<Info> info;
	vector<Tag> tag;

	LazySegmentTree() {}
	LazySegmentTree(int n_, Info v = Info()) {
		init(n_, v);
	}
	template<class T>
	LazySegmentTree(vector<T> a) {
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
		tag.assign(n * 4 + 5, Tag());
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

	void apply(int i, const Tag &v) {
		info[i].apply(v);
		tag[i].apply(v);
	}

	void push(int i) {
		apply(i << 1, tag[i]);
		apply(i << 1 | 1, tag[i]);
		tag[i] = Tag();
	}

	void modify(int pos, const Info &v) {
		modify(1, 1, n, pos, v);
	}

	void modify(int i, int l, int r, int pos, const Info &v) {
		if (l == r) {
			info[i] = v;
			tag[i] = Tag();
			return;
		}

		push(i);

		int mid = (l + r) >> 1;
		if (pos <= mid) modify(i << 1, l, mid, pos, v);
		else modify(i << 1 | 1, mid + 1, r, pos, v);

		pull(i);
	}

	void rangeApply(int l, int r, const Tag &v) {
		rangeApply(1, 1, n, l, r, v);
	}

	void rangeApply(int i, int l, int r, int ql, int qr, const Tag &v) {
		if (ql <= l && r <= qr) {
			apply(i, v);
			return;
		}

		push(i);

		int mid = (l + r) >> 1;
		if (ql <= mid) rangeApply(i << 1, l, mid, ql, qr, v);
		if (qr > mid) rangeApply(i << 1 | 1, mid + 1, r, ql, qr, v);

		pull(i);
	}

	Info query(int l, int r) {
		return query(1, 1, n, l, r);
	}

	Info query(int i, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return info[i];

		push(i);

		int mid = (l + r) >> 1;

		if (qr <= mid) return query(i << 1, l, mid, ql, qr);
		if (ql > mid) return query(i << 1 | 1, mid + 1, r, ql, qr);

		return query(i << 1, l, mid, ql, qr)
			 + query(i << 1 | 1, mid + 1, r, ql, qr);
	}
};

struct Tag {
	int add = 0;

	void apply(const Tag &t) {
		add += t.add;
	}
};

struct Info {
	int sum = 0;
	int len = 0;

	void apply(const Tag &t) {
		sum += t.add * len;
	}
};

Info operator+(const Info &a, const Info &b) {
	return {a.sum + b.sum, a.len + b.len};
}
```

```cpp
struct Tag {
	// 修改信息

	void apply(const Tag &v) {
		// 原来的 tag，再执行 v
	}
};

struct Info {
	// 查询信息

	void apply(const Tag &v) {
		// 整个区间执行 v 后
		// Info 怎么变化
	}

};
Info operator+(const Info &a, const Info &b) {
	Info c;

	// 左右区间合并

	return c;
}
```
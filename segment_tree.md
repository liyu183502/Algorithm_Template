## segment（优化算法，用于暴力很简单，但是复杂度高的题目）
应用场景：1.多次查询，单点或区间修改，2.判断能否使用：关键在于区间能否状态转移  
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
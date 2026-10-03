
## 区间筛
区间小于1e6，r小于1e14
```cpp
int spf[N], primes[N], cnt;

void init() {
	for (int i = 2; i < N; i++) {
		if(!spf[i]) {
			spf[i] = i;
			primes[++cnt] = i;
		}

		for (int j = 1; j <= cnt && i * primes[j] < N; j++) {
			int p = primes[j];
			spf[i * p] = p;
			if(i % p == 0) break;
		}
	}
}

vector<vector<pii>> segment_factor(int l, int r) {
	int n = r - l + 1;
	vector<int> a(n);
	vector<vector<pii>> fac(n);

	for (int i = 0; i < n; i++) {
		a[i] = l + i;
	}

	for (int i = 1; i <= cnt; i++) {
		int p = primes[i];
		if(p * p > r) break;
		int st = (l + p - 1) / p * p;

		for (int x = st; x <= r; x += p) {
			int id = x - l;
			int c = 0;

			while(a[id] % p == 0) {
				a[id] /= p;
				c++;
			}

			if(c) {
				fac[id].push_back({p, c});
			}
		}
	}

	for (int i = 0; i < n; i++) {
		if(a[i] > 1) {
			fac[i].push_back({a[i], 1});
		}
	}

	return fac;
}
```
---

## 常用函数
```cpp
logl(x)    // ln(x)，以 e 为底
log2l(x)   // log_2(x)
log10l(x)  // log_10(x)

floorl(x) // 下取整
ceill(x) // 上取整
roundl(x) // 四舍五入
truncl(x) // 直接去掉小数部分

sinl(x)
cosl(x)
tanl(x)
asinl(x)
acosl(x)
atanl(x) // 没办法区分象限
atan2l(y, x) //四个象限
```
---
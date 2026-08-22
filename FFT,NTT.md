## NTT
数组 0 位存的是常数项
```cpp
const int g = 3;

int ksm(int a, int n) {
	a %= p;
	int res = 1;
	while(n) {
		if(n & 1) {
			res = res * a % p;
		}
		a = a * a % p;
		n >>= 1;
	}
	return res;
}

void ntt(vector<int> &a, int op) {
	int n = a.size();

	for(int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for(; j & bit; bit >>= 1) {
			j ^= bit;
		}
		j ^= bit;
		if(i < j) {
			swap(a[i], a[j]);
		}
	}

	for(int len = 2; len <= n; len <<= 1) {
		int wlen = ksm(g, (p - 1) / len);
		if(op == -1) {
			wlen = ksm(wlen, p - 2);
		}

		for(int i = 0; i < n; i += len) {
			int w = 1;
			for(int j = 0; j < len / 2; j++) {
				int u = a[i + j];
				int v = a[i + j + len / 2] * w % p;
				a[i + j] = (u + v) % p;
				a[i + j + len / 2] = (u - v + p) % p;
				w = w * wlen % p;
			}
		}
	}

	if(op == -1) {
		int inv = ksm(n, p - 2);
		for(auto &x : a) {
			x = x * inv % p;
		}
	}
}

vector<int> mul(vector<int> a, vector<int> b) {
	int sz = a.size() + b.size() - 1;
	int n = 1;
	while(n < sz) {
		n <<= 1;
	}
	a.resize(n);
	b.resize(n);

	ntt(a, 1);
	ntt(b, 1);
	for(int i = 0; i < n; i++) {
		a[i] = a[i] * b[i] % p;
	}
	ntt(a, -1);
	a.resize(sz);

	return a;
}
```

## FFT
```cpp
const double pi = acos(-1);
using cd = complex<double>;

void fft(vector<cd> &a, int op) {
	int n = a.size();
	for(int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for(; j & bit; bit >>= 1) {
			j ^= bit;
		}
		j ^= bit;
		if(i < j) {
			swap(a[i], a[j]);
		}
	}

	for(int len = 2; len <= n; len <<= 1) {
		double ang = 2 * pi / len * op;
		cd wlen(cos(ang), sin(ang));
		for(int i = 0; i < n; i += len) {
			cd w(1);
			for(int j = 0; j < len / 2; j++) {
				cd u = a[i + j];
				cd v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}

	if(op == -1) {
		for(auto &x : a) {
			x /= n;
		}
	}
}

vector<int> mul(vector<int> a, vector<int> b) {
	int sz = a.size() + b.size() - 1;
	int n = 1;
	while(n < sz) {
		n <<= 1;
	}

	vector<cd> fa(n), fb(n);
	for(int i = 0; i < a.size(); i++) {
		fa[i] = a[i];
	}
	for(int i = 0; i < b.size(); i++) {
		fb[i] = b[i];
	}
	fft(fa, 1);
	fft(fb, 1);
	for(int i = 0; i < n; i++) {
		fa[i] *= fb[i];
	}
	fft(fa, -1);

	vector<int> c(sz);
	for(int i = 0; i < sz; i++) {
		c[i] = (long long)(fa[i].real() + 0.5);
	}
	return c;
}
```
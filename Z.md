
template<class T>
T power(T a, int b) {
	T res = 1;
	for (; b; b >>= 1, a *= a)
		if(b & 1) res *= a;
	return res;
}

template<int P>
struct MInt {
	int x;

	MInt(int x = 0) : x((x % P + P) % P) {}

	int val() const {
		return x;
	}

	MInt inv() const {
		return power(*this, P - 2);
	}

	MInt operator-() const {
		return MInt(-x);
	}

	MInt &operator+=(const MInt &t) {
		x += t.x;
		if(x >= P) x -= P;
		return *this;
	}

	MInt &operator-=(const MInt &t) {
		x -= t.x;
		if(x < 0) x += P;
		return *this;
	}

	MInt &operator*=(const MInt &t) {
		x = (i128)x * t.x % P;
		return *this;
	}

	MInt &operator/=(const MInt &t) {
		return *this *= t.inv();
	}

	friend MInt operator+(MInt a, const MInt &b) {
		return a += b;
	}

	friend MInt operator-(MInt a, const MInt &b) {
		return a -= b;
	}

	friend MInt operator*(MInt a, const MInt &b) {
		return a *= b;
	}

	friend MInt operator/(MInt a, const MInt &b) {
		return a /= b;
	}

	friend bool operator==(const MInt &a, const MInt &b) {
		return a.x == b.x;
	}

	friend bool operator!=(const MInt &a, const MInt &b) {
		return a.x != b.x;
	}

	friend bool operator<(const MInt &a, const MInt &b) {
		return a.x < b.x;
	}

	friend istream &operator>>(istream &in, MInt &a) {
		int x;
		in >> x;
		a = x;
		return in;
	}

	friend ostream &operator<<(ostream &out, const MInt &a) {
		return out << a.x;
	}
};

using Z = MInt<998244353>;
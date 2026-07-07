template<class T>
constexpr T power(T a, unsigned long long b, T res = 1) {
	for (; b != 0; b /= 2, a *= a) {
		if (b & 1) res *= a;
	}
	return res;
}

template<class U, U P>
struct ModIntBase {
public:
	U x;
	constexpr ModIntBase() : x(0) {}
	constexpr ModIntBase(long long x_) {
		long long v = x_ % (long long)P;
		if (v < 0) v += (long long)P;
		x = (U)v;
	}
	constexpr static U mod() { return P; }
	constexpr U val() const { return x; }
	constexpr ModIntBase operator-() const {
		return ModIntBase(x == 0 ? 0 : P - x);
	}
	constexpr ModIntBase inv() const {
		return power(*this, P - 2);
	}
	constexpr ModIntBase &operator*=(const ModIntBase &rhs) & {
		x = (unsigned long long)x * rhs.x % P;
		return *this;
	}
	constexpr ModIntBase &operator+=(const ModIntBase &rhs) & {
		x += rhs.x;
		if (x >= P) x -= P;
		return *this;
	}
	constexpr ModIntBase &operator-=(const ModIntBase &rhs) & {
		if (x < rhs.x) x += P;
		x -= rhs.x;
		return *this;
	}
	constexpr ModIntBase &operator/=(const ModIntBase &rhs) & {
		return *this *= rhs.inv();
	}
	friend constexpr ModIntBase operator*(ModIntBase lhs, const ModIntBase &rhs) {
		return lhs *= rhs;
	}
	friend constexpr ModIntBase operator+(ModIntBase lhs, const ModIntBase &rhs) {
		return lhs += rhs;
	}
	friend constexpr ModIntBase operator-(ModIntBase lhs, const ModIntBase &rhs) {
		return lhs -= rhs;
	}
	friend constexpr ModIntBase operator/(ModIntBase lhs, const ModIntBase &rhs) {
		return lhs /= rhs;
	}
	friend istream &operator>>(istream &is, ModIntBase &a) {
		long long v;
		is >> v;
		a = ModIntBase(v);
		return is;
	}
	friend ostream &operator<<(ostream &os, const ModIntBase &a) {
		return os << a.val();
	}
	friend bool operator==(const ModIntBase &lhs, const ModIntBase &rhs) {
		return lhs.val() == rhs.val();
	}
	friend bool operator!=(const ModIntBase &lhs, const ModIntBase &rhs) {
		return lhs.val() != rhs.val();
	}
};

using Z = ModIntBase<unsigned int, (unsigned int)p>;
template<class T, class Opt>
struct RMQ {
    int n;
    vector<vector<T>> a;
    Opt opt;

    RMQ(const vector<T> &v, Opt f) : opt(f) {
        init(v);
    }

    void init(const vector<T> &v) {
        n = (int)v.size() - 1;
        int K = __lg(n);
        a.assign(K + 1, vector<T>(n + 1));

        for (int i = 1; i <= n; i++) {
            a[0][i] = v[i];
        }

        for (int k = 1; k <= K; k++) {
            for (int i = 1; i + (1 << k) - 1 <= n; i++) {
                a[k][i] = opt(a[k - 1][i], a[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    T query(int l, int r) {
        int k = __lg(r - l + 1);
        return opt(a[k][l], a[k][r - (1 << k) + 1]);
    }
};

```cpp
int s[N]; // 区间和
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

    void change(int idx, int val) {
        while (idx <= n) {
            bit[idx] = max(bit[idx], val);
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        int res = 0;
        while (idx > 0) {
            res = max(res, bit[idx]);
            idx -= idx & -idx;
        }
        return res;
    }
};
```
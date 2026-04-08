```cpp
int s[N]; // 区间和
int lowbit(int x){
    return x & -x;
}

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
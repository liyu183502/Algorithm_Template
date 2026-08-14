```cpp
int ksm(int a, int n) {
    a %= p;
    int res = 1;
    while(n){
        if(n & 1) res = a * res % p;
        a = a * a % p;
        n >>= 1;
    }
    return res % p;
}
```
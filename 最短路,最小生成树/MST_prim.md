#### prim
```cpp
const int N = 110;
int g[N][N], d[N], vis[N], cnt, ans;

bool prim(int s) {
    memset(g, 0x3f, sizeof g);
    memset(d, 0x3f, sizeof d);
    d[s] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if(!vis[j] && (u == -1 || d[j] < d[u])) {
                u = j;
            }
        }
        vis[u] = 1;
        ans += d[u];
        cnt ++;

        if(d[u] == inf) return 0;
        for (int j = 1; j <= n; j++) {
            if(d[j] > g[j][u]){
                d[j] = g[j][u];
            }
        }
    }
    return cnt == n;
}
```
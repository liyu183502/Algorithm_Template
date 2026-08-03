## floyd 
应用：求多源最短路  
思想：1.动态规划，2.对于**每一个点**进行一次当前全部点路径更新  
组成：1.vvi d，2.三重循环  
```cpp
    vector<vector<int>> g(n + 1, vector<int>(n + 1, inf));
    for (int i = 1; i <= n; i++) g[i][i] = 0; //有时需要
    for (int k = 1; k <= n; k ++ ){
        for (int i = 1; i <= n; i ++ ){
            for (int j = 1; j <= n; j ++ ){
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
```
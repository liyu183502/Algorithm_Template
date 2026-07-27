## dfs序 （树和数组数据结构之间的桥梁）
### 作用
#### 作用一：把子树变成连续区间
范围：[dfn[u], dfn[u] + sz[u] - 1]
#### 作用二：判断祖先关系
```cpp
    auto isAncestor = [&](int u, int v) -> bool {
        return dfn[u] <= dfn[v] && dfn[v] <= dfn[u] + sz[u] - 1;
    };
```

### 命名
两者互为逆映射:  
dfn[u] = id;  
rev[id] = u;  
rev 是 reverse 的缩写，表示“反向映射”  
sz[u] 为子树大小

```cpp
    int time = 0;
    vector<int> dfn(n + 1);
    vector<int> rev(n + 1);
    vector<int> sz(n + 1);

    auto dfs = [&](auto &&self, int u, int fa) -> void {
        dfn[u] = ++time;
        rev[time] = u;
        sz[u] = 1;

        for (auto v : g[u]) {
            if (v == fa) continue;

            self(self, v, u);
            sz[u] += sz[v];
        }
    };
```
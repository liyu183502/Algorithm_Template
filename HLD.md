## HLD (Heavy-Light Decomposition)
### 作用
把树上的一条路径，拆成至多 O(logn) 段连续区间，然后交给线段树或树状数组处理。  
1.修改路径 u→v 上所有点；  
2.查询路径 u→v 的点权和、最大值；  
3.修改某棵子树；  
4.查询某棵子树的信息；  
5.求 LCA。

### 复杂度：
1.整棵树的重链数等于叶子数，可能达到 O(n)；但任意一条树上路径只会经过 O(logn) 条重链。  
2.任意一个节点到根的路径，最多经过 O(logn) 条重链

## 细节
top：所在重链顶部  
rev：映射  
son：重儿子

path：负责拆链  
work：对拆出来的每条链的操作  
build：从根开始dfs  
substree：返回子树的dfs序范围  
lca：求两个点的lca  
```cpp
struct HLD {
    int n, time;
    vector<vector<int>> g;
    vector<int> fa, dep, sz, son;
    vector<int> top, dfn, rev;

    HLD(int n) {
        this->n = n;
        time = 0;

        g.resize(n + 1);
        fa.resize(n + 1);
        dep.resize(n + 1);
        sz.resize(n + 1);
        son.resize(n + 1);
        top.resize(n + 1);
        dfn.resize(n + 1);
        rev.resize(n + 1);
    }

    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs1(int u, int f) {
        fa[u] = f;
        dep[u] = dep[f] + 1;
        sz[u] = 1;

        for (auto v : g[u]) {
            if (v == f) continue;

            dfs1(v, u);
            sz[u] += sz[v];

            if (sz[v] > sz[son[u]]) {
                son[u] = v;
            }
        }
    }

    void dfs2(int u, int t) {
        top[u] = t;
        dfn[u] = ++time;
        rev[time] = u;

        if (son[u]) {
            dfs2(son[u], t);
        }

        for (auto v : g[u]) {
            if (v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
        }
    }

    void build(int root = 1) {
        dfs1(root, 0);
        dfs2(root, root);
    }

    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) {
                swap(u, v);
            }
            u = fa[top[u]];
        }

        return dep[u] < dep[v] ? u : v;
    }

    template<class T>
    void path(int u, int v, T work) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) {
                swap(u, v);
            }

            work(dfn[top[u]], dfn[u]);
            u = fa[top[u]];
        }

        if (dep[u] > dep[v]) {
            swap(u, v);
        }

        work(dfn[u], dfn[v]);
    }

    pair<int, int> subtree(int u) {
        return {
            dfn[u],
            dfn[u] + sz[u] - 1
        };
    }
};
```

## path 解释
先找当两个点不在同一条重链上的时候，先处理较深的那个点（那条链），然后处理完之后 u ，跳到他重链的父亲，然后继续一直操作，知道两个点在同一条重链上面的时候，依旧选择那个深的点  
## 数位dp
pos 当前在哪一位

state 根据每道题目修改

lim 前面的数位是否是上界

lead 前面的数位是不是都是前导 0
## 不含前导零且相邻两个数字之差至少为 2 的正整数。windy 想知道，在 l 和 r 之间有多少
```cpp
//num == 10表示前面没有数
int cal(int x) {
	string s = " " + to_string(x);
	int n = s.size() - 1;
	int dp[20][11][2][2]{}, vis[20][11][2][2]{};

	auto dfs = [&](auto &&self, int pos, int num, int lim, int lead) -> int {
		if(pos == n + 1) {
			return !lead;
		}

		if(vis[pos][num][lim][lead]) {
			return dp[pos][num][lim][lead];
		}
		vis[pos][num][lim][lead] = 1;

		int up = lim ? s[pos] - '0' : 9;
		for (int d = 0; d <= up; d++) {
			int nlim = lim && d == up;
			int nlead = lead && d == 0;

			int t = 0;
			if(nlead) {
				t = self(self, pos + 1, 10, nlim, nlead);
			}
			else if(num == 10 || abs(d - num) >= 2) {
				t = self(self, pos + 1, d, nlim, nlead);
			}
			
			dp[pos][num][lim][lead] += t;
		}
		
		return dp[pos][num][lim][lead];
	};
	return dfs(dfs, 1, 10, 1, 1);
};
```
<br><br>


## 给定两个正整数 a 和 b，求在 [a,b] 中的所有整数中，每个数码（digit）各出现了多少次
```cpp
struct Node {
	int sum = 0;
	array<int, 10> cnt;
};

array<int, 10> cal(int x) {
	int vis[20][2][2] = {};
	Node dp[20][2][2];
	
	string s = " " + to_string(x);
	int n = s.size() - 1;

	auto dfs = [&](auto &&self, int pos, int lim, int lead) -> Node {
		if(pos == n + 1) {
			Node t = {};
			t.sum = !lead;
			return t;		
		}

		if(vis[pos][lim][lead]) {
			return dp[pos][lim][lead];
		}

		Node res = {};
		int up = lim ? s[pos] - '0' : 9;
		for (int d = 0; d <= up; d++) {
			int nlim = lim && d == up;
			int nlead = lead && d == 0;

			Node t = self(self, pos + 1, nlim, nlead);

			res.sum += t.sum;
			for (int j = 0; j <= 9; j++) {
				res.cnt[j] += t.cnt[j];
			}	

			if(!nlead) {
				res.cnt[d] += t.sum;
			}
		}

		vis[pos][lim][lead] = 1;
		dp[pos][lim][lead] = res;
		
		return res;
	};
	return dfs(dfs, 1, 1, 1).cnt;
};

void solve() {
	int l, r;
	cin >> l >> r;
	
	auto x = cal(r), y = cal(l - 1);
	int ans = 0;
	for (int i = 0; i <= 9; i++) {
		int cnt = x[i] - y[i];
		ans = (ans + cnt % p * i % p) % p;
	}
	cout << ans << endl;
}
```
<br><br>


## 通用模板
```cpp
const int S = 105; // 状态数量，根据题目修改

int cal(int x) {
	if(x <= 0) return 0;

	string s = " " + to_string(x);
	int n = s.size() - 1;

	int dp[20][S][2][2]{};
	bool vis[20][S][2][2]{};

	auto dfs = [&](auto &&self, int pos, int state, int lim, int lead) -> int {
		// 所有数位都填完
		if(pos == n + 1) {
			// 修改1：判断最终状态是否合法
			return !lead && state合法;
		}

		if(vis[pos][state][lim][lead]) {
			return dp[pos][state][lim][lead];
		}
        vis[pos][state][lim][lead] = 1;

		int up = lim ? s[pos] - '0' : 9;

		for (int d = 0; d <= up; d++) {
			int nlim = lim && d == s[pos] - '0';
			int nlead = lead && d == 0;

			int nstate = state;

			// 前导零通常不参与状态转移
			if(!nlead) {
				// 修改2：判断当前数字 d 能否填写
				if(当前填写d不合法) continue;

				// 修改3：计算新的状态
				nstate = 状态转移;
			}

			dp[pos][state][lim][lead] += self(self, pos + 1, nstate, nlim, nlead);
		}

		return dp[pos][state][lim][lead];
	};

	return dfs(dfs, 1, 初始状态, 1, 1);
}
```
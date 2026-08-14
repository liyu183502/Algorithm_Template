## 复杂度O(n * 2^n)
SOS DP 本质不是求和，而是批量维护所有子集的信息

## 子集
```cpp
for (int i = 0; i < n; i++) {
	for (int mask = 0; mask < (1 << n); mask++) {
		if(mask >> i & 1) {
			dp[mask] += dp[mask ^ (1 << i)];
        }
    }
}
```
<br><br>

## 超集
```cpp
for (int i = 0; i < n; i++) {
	for (int mask = 0; mask < (1 << n); mask++) {
		if(!(mask >> i & 1)) {
			dp[mask] += dp[mask | (1 << i)];
        }
    }
}
```
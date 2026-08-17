## 拓展欧几里得算法
普通欧几里得算法用于求：gcd(a,b)  

扩展欧几里得不仅求 gcd，还能找到一组整数 x, y，使得：ax+by=gcd(a,b)	​（裴蜀等式）

也可用于求逆元

#### 求exgcd
ax + by = d  
d = gcd(a, b)
```cpp
int exgcd(int a, int b, int &x, int &y){
	if(!b) {
		x = 1;
		y = 0;
		return a;
	}
	int d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}
```
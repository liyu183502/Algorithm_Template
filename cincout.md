## 输出
### 前对齐，后对齐
只对第一个输出的变量有效

```cpp
cout << setw(2) << setfill('0') << ans << endl; //默认前面补
cout << right << setw(2) << setfill('0') << ans << endl; // 前面补
cout << left << setw(2) << setfill('0') << ans << endl; // 后面补
```
## 控制小数
```cpp
double x = 3.1415926;

cout << fixed << setprecision(2) << x << endl;
```

## 输入
读入一行的字符串，然后分别取出

```cpp
    cin.ignore();
	string s;
	getline(cin, s);

	stringstream ss(s);

	string t;
	while(ss >> t) {
		cout << t << endl;
	}
```

如果一行里分隔符不是空格，比如 abc,def,ghi，那就要用 getline(ss, t, ',')
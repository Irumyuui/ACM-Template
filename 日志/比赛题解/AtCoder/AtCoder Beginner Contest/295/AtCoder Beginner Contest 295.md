# AtCoder Beginner Contest 295

## G. Minimum Reachable City

思路：由于单项边没法使用并查集，于是我们可以先将原先的边保存起来。由于原图的边是指向更大的节点，因此我们保存后查询答案并不会影响结果。

考虑加边：`u -> v` ，题目给出条件**加的边保证`v`能够在原图中到达`u`**，那么也就意味着我们加的边相对于原图来说是一条反向的边。因此，这部分的节点在局部上构成一个强连通分量，也意味着可以直接使用并查集合并。

因此，我们只需要在加边的时候将对应的节点合并完即可（包括原图中的节点）。

```cpp
auto Main() -> void {
	int n;
	cin >> n;
	vector<int> fa(n + 1);
	for (int i = 2; i <= n; i ++) {
		cin >> fa[i];
	}

	std::vector<int> dad(n + 1, -1);
	auto Find = [Find{[&](auto &&Find, int x) -> int { if (dad[x] == -1) return x; return dad[x] = Find(Find, dad[x]); }}](int x) -> int {
		return Find(Find, x);
	};
	auto Merge = [&](int a, int b) -> bool {
		a = Find(a); b = Find(b);
		if (a == b) return false;
		if (a > b) swap(a, b);
		dad[b] = a;
		return true;
	};
	auto Is_Same = [&](int a, int b) -> bool {
		return Find(a) == Find(b);
	};
	
	auto Work = [&](int a, int b) {
		a = Find(a); b = Find(b);
		while (a != b) {
			Merge(a, b);
			a = Find(fa[a]);
		}
	};
	
	int q;
	cin >> q;
	for (int _ = 1; _ <= q; _ ++) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int u, v;
			cin >> u >> v;
			Work(u, v);
		} else {
			int x;
			cin >> x;
			cout << Find(x) << '\n';
		}
	}
}
```
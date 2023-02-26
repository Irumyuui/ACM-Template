#include <bits/stdc++.h>

template <typename Node>
concept __Node = requires(Node x, int d) {
	{Node()};
	{x.next[d]} -> std::same_as<int>;
};
template <typename RA>
concept __RA = requires(RA arr, int i) {
	
};

template <__Node Node>
struct Trie {
	std::vector<Node> trie;

	Trie(int __init_size__ = int(1e6 + 10))
		: trie(1, Node{}) {}
	

};
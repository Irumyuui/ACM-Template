#include <bits/stdc++.h>

class DisjointSetUnion {
	public:
		explicit DisjointSetUnion(int size) 
			: dad(size, -1) {}

		int Find(int x) {
			if (dad[x] <= -1) {
				return x;
			}
			return dad[x] = Find(dad[x]);
		}

		int operator [] (int x) {
			return Find(x);
		}

		bool Merge(int a, int b) {
			a = Find(a); b = Find(b);
			if (a == b)
				return false;
			if (a > b)
				std::swap(a, b); 
			dad[a] += dad[b];
			dad[b] = a;
			return true;
		}

		// Merge a to b.
		bool MergeTo(int a, int b) {
			a = Find(a); b = Find(b);
			if (a == b) 
				return false;
			dad[a] += dad[b];
			dad[b] = a;
			return true;
		}

		bool IsSame(int a, int b) {
			return Find(a) == Find(b);
		}

		void Assign(int size, int value) {
			dad.assign(size, value);
		}

		void Fill(int value = -1) {
			std::fill(dad.begin(), dad.end(), value);
		}

		int GetSetSize(int x) {
			return -dad[Find(x)];
		}

		int GetSetCount() const {
			return std::count_if(dad.begin(), dad.end(), [](auto &&size) -> bool {
				return size <= -1;
			});
		}

		int GetVertexCount() const {
			return dad.size();
		}

	private:
		std::vector<int> dad;
};
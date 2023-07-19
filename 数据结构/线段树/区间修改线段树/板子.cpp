#include <bits/stdc++.h>

template <typename SemiGroup, typename LazyTag, std::relation<SemiGroup,SemiGroup> Relation, std::relation<SemiG Down>
class LazyTagSegmentTree {
public:

private:
	std::vector<SemiGroup> seg;
	std::vector<LazyTag> lazyTag;
	const int size;
	Relation relation;
	Down down;
};
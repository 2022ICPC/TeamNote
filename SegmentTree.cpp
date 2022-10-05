template<typename T, T (*merge)(T, T), T e>
struct Seg {
	int n;
	vector<T> seg;
	void init(int _n) {
		n = _n;
		seg.resize(2 * n);
	}
	void upt(int i, T p) {
		for (seg[i += n] += p; i >>= 1; ) seg[i] = merge(seg[i << 1], seg[i << 1 | 1]);
	}
	T get(int i) { return seg[i + n]; }
	T query(int l, int r) {
		T nl = e, nr = e;
		for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) nl = merge(nl, seg[l++]);
			if (r & 1) nr = merge(seg[--r], nr);
		}
		return merge(nl, nr);
	}
};
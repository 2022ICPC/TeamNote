#include <bits/stdc++.h>
using namespace std;
struct Lazy {
	int n;
	vector<int> seg, lazy;
	void init(int _n) {
		n = _n;
		seg.resize(4*n);
		lazy.resize(4*n);
	}
	void updatelazy(int num, int s, int e) {
		seg[num] = (e - s + 1) * lazy[num];
		if (s ^ e) {
			lazy[2 * num] += lazy[num];
			lazy[2 * num+1] += lazy[num];
		}
		lazy[num] = 0;
	}
	int update(int num, int s, int e, int l, int r, int p) {
		updatelazy(num, s, e);
		if (r < s || e < l) return seg[num];
		if (l <= s && e <= r) {
			lazy[num] += p;
			updatelazy(num, s, e);
			return seg[num];
		}
		int mid = s + e >> 1;
		return seg[num] = update(2 * num, s, mid, l, r, p) + update(2 * num + 1, mid + 1, e, l, r, p);
	}
	void update(int l, int r, int p) { update(1, 0, n - 1, l, r, p); }
	int query(int num, int s, int e, int l, int r) {
		updatelazy(num, s, e);
		if (r < s || e < l) return 0;
		if (l <= s && e <= r) return seg[num];
		int mid = s + e >> 1;
		return query(2 * num, s, mid, l, r) + query(2 * num + 1, mid + 1, e, l, r);
	}
	int query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
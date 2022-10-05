struct MergeSortTree {
	int n;
	vector<int> arr;
	vector<vector<int>> seg;
	void Init(vector<int>& vec) {
		n = vec.size();
		arr.assign(vec.begin(), vec.end());
		seg.resize(4 * n);
		SetTree(1, 0, n - 1);
	}
	void SetTree(int num, int s, int e) {
		if (s == e) {
			seg[num].push_back(arr[s]);
			return;
		}
		int mid = s + e >> 1;
		SetTree(2 * num, s, mid);
		SetTree(2 * num + 1, mid + 1, e);
		vector<int>& now = seg[num];
		vector<int>& l = seg[2 * num], r = seg[2 * num + 1];
		int pl = 0, pr = 0;
		for (int i = 0; i < l.size() + r.size(); i++) {
			if (pl < l.size() && pr < r.size()) {
				if (l[pl] < r[pr]) now.push_back(l[pl]), pl++;
				else now.push_back(r[pr]), pr++;
			}
			else if (pl < l.size())
				now.push_back(l[pl]), pl++;
			else if (pr < r.size())
				now.push_back(r[pr]), pr++;
		}
	}
	int query(int num, int s, int e, int l, int r, int k) {
		if (r < s || e < l) return 0;
		if (l <= s && e <= r) {
			int idx = upper_bound(seg[num].begin(), seg[num].end(), k) - seg[num].begin();
			return seg[num].size() - idx;
		}
		int mid = s + e >> 1;
		return query(2 * num, s, mid, l, r, k) + query(2 * num + 1, mid + 1, e, l, r, k);
	}
	int query(int l, int r, int k) { return query(1, 0, n - 1, l, r, k); }
}tree;
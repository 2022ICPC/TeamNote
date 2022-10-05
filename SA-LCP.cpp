vector<int> buildSA(string& str) {
	int n = str.size();
	vector<int> sa(n), r(n + 1), nr(n + 1);
	for (int i = 0; i < n; i++) sa[i] = i, r[i] = str[i];
	for (int d = 1; d < n; d <<= 1) {
		auto cmp = [&](int i, int j) -> bool {
			return r[i] < r[j] || (r[i] == r[j] && r[i + d] < r[j + d]);
		};
		sort(sa.begin(), sa.end(), cmp);

		nr[sa[0]] = 1;
		for (int i = 1; i < n; i++)
			nr[sa[i]] = nr[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
		r = nr;
	}
	return sa;
}
vector<int> buildLCP(string& str, vector<int>& sa) {
	int n = str.size();
	vector<int> lcp(n + 1), isa(n + 1);
	for (int i = 0; i < n; i++) isa[sa[i]] = i;
	for (int i = 0, k = 0; i < n; i++) {
		if (isa[i]) {
			for (int j = sa[isa[i] - 1]; str[i + k] == str[j + k]; k++);
			lcp[isa[i]] = (k ? k-- : 0);
		}
	}
	return lcp;
}
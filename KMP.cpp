vector<int> KMP(string from, string to) {
	int n = from.size(), m = to.size();
	vector<int> fail(m + 1);
	for (int i = 1, j = 0; i < m; i++) {
		while (j && to[i] != to[j]) j = fail[j];
		if (to[i] == to[j]) j++;
		fail[i + 1] = j;
	}
	vector<int> ans;
	for (int i = 0, j = 0; i < n; i++) {
		while (j && from[i] != to[j]) j = fail[j];
		if (from[i] == to[j]) j++;
		if (j == m) ans.push_back(i - m + 1), j = fail[j];
	}
	return ans;
}
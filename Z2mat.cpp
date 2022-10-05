namespace Z2mat {
	const int MAX = 501;
	int n;
	bitset<2 * MAX> mat[MAX];
	void init() { for (int i = 0; i < MAX; i++) mat[i].reset(); }
	void input(vector<vector<bool>> arr) {
		assert(arr.size() == arr[0].size());
		init();
		n = arr.size();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				mat[i][j] = arr[i][j];
				if (i == j) mat[i][j + n] = true;
			}
	}
	vector<vector<bool>> rev() {
		for (int i = 0; i < n; i++) {
			if (!mat[i][i])
				for (int j = i + 1; j < n; j++)
					if (mat[j][i]) swap(mat[i], mat[j]);
			assert(mat[i][i]);
			for (int j = 0; j < n; j++)
				if (i != j && mat[j][i]) mat[j] ^= mat[i];
		}
		vector ans(n, vector<bool>(n));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) ans[i][j] = mat[i][j + n];
		return ans;
	}
}
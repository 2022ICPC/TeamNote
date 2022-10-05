const int MAX = 30001;
const int LV = 17;
int dep[MAX], dp[LV + 1][MAX];
vector<int> V[MAX];
void dfs(int pos, int d = 0, int p = 0) {
	dep[pos] = d;
	dp[0][pos] = p;
	for (int i = 1; i <= LV; i++)
		dp[i][pos] = dp[i - 1][dp[i - 1][pos]];

	for (int w : V[pos]) {
		if (w == p) continue;
		dfs(w, d + 1, pos);
	}
}
int lca(int a, int b) {
	if (dep[a] < dep[b]) swap(a, b);
	int d = dep[a] - dep[b];
	for (int i = 0; d; i++, d >>= 1)
		if (d & 1) a = dp[i][a];
	if (a == b) return a;
	for (int i = LV; ~i; i--)
		if (dp[i][a] != dp[i][b]) a = dp[i][a], b = dp[i][b];
	return dp[0][a];
}
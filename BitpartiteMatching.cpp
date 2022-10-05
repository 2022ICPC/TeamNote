const int MAX = 501;
vector<int> V[MAX];
int ma[MAX], mb[MAX];
bool vit[MAX];
bool dfs(int pos) {
	vit[pos] = true;
	for (int w : V[pos]) {
		if (mb[w] == -1 || !vit[mb[w]] && dfs(mb[w])) {
			ma[pos] = w;
			mb[w] = pos;
			return true;
		}
	}
	return false;
}
int match(int n) {
	memset(ma, -1, sizeof(ma));
	memset(mb, -1, sizeof(mb));
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (ma[i] == -1) {
			memset(vit, false, sizeof(vit));
			ans += dfs(i);
		}
	}
	return ans;
}
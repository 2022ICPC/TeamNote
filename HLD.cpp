const int MAX = 300001;
vector<int> V[MAX], g[MAX];
int sz[MAX], dep[MAX], top[MAX], par[MAX], in[MAX], out[MAX];

bitset<MAX> vit;
void dfs(int pos) {
	vit[pos] = true;
	for (int& w : V[pos]) {
		if (vit[w]) continue;
		g[pos].push_back(w);
		dfs(w);
	}
}
void dfs1(int pos) {
	sz[pos] = 1;
	for (int& w : g[pos]) {
		dep[w] = dep[pos] + 1, par[w] = pos;
		dfs1(w);
		sz[pos] += sz[w];
		if (sz[w] > sz[g[pos][0]]) swap(w, g[pos][0]);
	}
}
int pv;
void dfs2(int pos) {
	in[pos] = ++pv;
	for (int& w : g[pos]) {
		top[w] = w == g[pos][0] ? top[pos] : w;
		dfs2(w);
	}
	out[pos] = pv;
}

void update(int a, int b, int diff) {
	int ans = 0;
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) swap(a, b);
		int x = top[a];
		tree.update(in[x], in[a], diff);
		a = par[x];
	}
	if (dep[a] > dep[b]) swap(a, b);
	tree.update(in[a], in[b], diff);
}

int query(int a, int b) {
	int ans = 0;
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) swap(a, b);
		int x = top[a];
		ans += tree.query(in[x], in[a]);
		a = par[x];
	}
	if (dep[a] > dep[b]) swap(a, b);
	ans += tree.query(in[a], in[b]);
	return ans;
}
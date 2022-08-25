struct HopcroftKarp {
	int n;
	vector<vector<int>> V;
	vector<int> ma, mb, lv;
	vector<bool> vit;
	void init(int _n) {
		n = _n;
		ma.resize(n); mb.resize(n);
		lv.resize(n); V.resize(n);
		vit.resize(n);
	}
	void add_edge(int u, int v) { V[u].push_back(v); }
	bool bfs() {
		queue<int> q;
		fill(lv.begin(), lv.end(), 0);
		for (int i = 0; i < n; i++)
			if (ma[i] == -1 && !lv[i])
				q.push(i), lv[i] = 1;
		bool ok = false;
		while (q.size()) {
			int top = q.front(); q.pop();
			for (int w : V[top]) {
				if (mb[w] == -1) ok = true;
				else if (!lv[mb[w]]) {
					lv[mb[w]] = lv[top] + 1;
					q.push(mb[w]);
				}
			}
		}
		return ok;
	}
	bool dfs(int a) {
		if (vit[a]) return false;
		vit[a] = true;
		for (int w : V[a]) {
			if (mb[w] == -1 || (!vit[mb[w]] && lv[mb[w]] == lv[a] + 1 && dfs(mb[w]))) {
				ma[a] = w;
				mb[w] = a;
				return true;
			}
		}
		return false;
	}
	int match() {
		fill(ma.begin(), ma.end(), -1);
		fill(mb.begin(), mb.end(), -1);
		int ans = 0;
		while (bfs()) {
			fill(vit.begin(), vit.end(), false);
			for (int i = 0; i < n; i++)
				if (ma[i] == -1 && dfs(i)) ans++;
		}
		return ans;
	}
};
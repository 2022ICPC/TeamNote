template<typename T>
struct Dinic {
	struct Edge {
		int to;
		T cap, f;
		int dual;
		T spare() { return cap - f; }
	};
	int n;
	T ans;
	vector<vector<Edge>> E;
	vector<int> lv, work;
	void init(int _n) {
		n = _n;
		E.clear();  E.resize(n);
		lv.resize(n); work.resize(n);
	}
	void add_edge(int u, int v, T cap) {
		E[u].push_back({ v,cap, 0 });
		E[v].push_back({ u, 0, 0 });
		E[u].back().dual = E[v].size() - 1;
		E[v].back().dual = E[u].size() - 1;;
	}
	bool bfs(int s, int t) {
		fill(lv.begin(), lv.end(), -1);
		lv[s] = 0;
		queue<int> q; q.push(s);
		while (q.size()) {
			int top = q.front(); q.pop();
			for (auto& l : E[top]) {
				if (lv[l.to] == -1 && l.spare()) {
					lv[l.to] = lv[top] + 1;
					q.push(l.to);
				}
			}
		}
		return lv[t] != -1;
	}
	T dfs(int pos, int t, T flow) {
		if (pos == t) return flow;
		for (int& i = work[pos]; i < E[pos].size(); i++) {
			auto& l = E[pos][i];
			if (lv[l.to] == lv[pos] + 1 && l.spare()) {
				T df = dfs(l.to, t, min(flow, l.spare()));
				if (df) {
					l.f += df;
					E[l.to][l.dual].f -= df;
					return df;
				}
			}
		}
		return 0;
	}
	T flow(int s, int t) {
		ans = 0;
		while (bfs(s, t)) {
			fill(work.begin(), work.end(), 0);
			while (1) {
				T flow = dfs(s, t, 1e9);
				if (!flow) break;
				ans += flow;
			}
		}
		return ans;
	}
};
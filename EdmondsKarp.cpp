template<typename T>
struct EdmondsKarp {
	struct Edge {
		int to;
		T cap, f;
		int dual;
		T spare() { return cap - f; }
	};
	int n;
	T ans;
	vector<vector<Edge>> E;
	void init(int _n) {
		n = _n;
		E.clear();  E.resize(n);
	}
	void add_edge(int u, int v, T cap) {
		E[u].push_back({ v,cap, 0 });
		E[v].push_back({ u, 0, 0 });
		E[u].back().dual = E[v].size() - 1;
		E[v].back().dual = E[u].size() - 1;;
	}
	bool bfs(int s, int t, bool apply = true) {
		vector<int> prv(n, -1);
		vector<Edge*> sel(n);
		queue<int> q; q.push(s);
		while (q.size()) {
			int top = q.front(); q.pop();
			for (auto& l : E[top]) {
				if (prv[l.to] == -1 && l.spare() > 0) {
					q.push(l.to);
					prv[l.to] = top;
					sel[l.to] = &l;
					if (l.to == t) break;
				}
			}
		}
		if (prv[t] == -1) return false;
		if (apply) {
			T flow = 1e9;
			for (int i = t; i != s; i = prv[i]) flow = min(flow, sel[i]->spare());
			for (int i = t; i != s; i = prv[i]) {
				sel[i]->f += flow;
				E[sel[i]->to][sel[i]->dual].f -= flow;
			}
			ans += flow;
		}
		return true;
	}
	T flow(int s, int t) {
		ans = 0;
		while (bfs(s, t));
		return ans;
	}
};
template<typename T>
struct LRFlow { //by sgc109
	Dinic<T> dinic;
	int n, src, sink, fsrc, fsink;
	vector<T> inSum, outSum;
	void init(int _n, int _src, int _sink) {
		n = _n, src = _src, sink = _sink;
		fsrc = n, fsink = n + 1;
		inSum = vector<T>(n);
		outSum = vector<T>(n);
	}
	void add_edge(int u, int v, int l, int r) {
		dinic.add_edge(u, v, r);
		inSum[v] += l;
		outSum[u] += l;
	}
	int flow() {
		for (int i = 0; i < n; i++)
			if (inSum[i]) dinic.add_edge(fsrc, i, inSum[i]);
		for (int i = 0; i < n; i++)
			if (outSum[i]) dinic.add_edge(i, fsink, outSum[i]);
		dinic.add_edge(sink, src, 1e9);
		return dinic.flow();
	}
};
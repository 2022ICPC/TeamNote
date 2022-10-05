struct TwoSat{
	int n;
    SCC scc;
	void init(int _n) {
		n = _n;
        scc.init(2*n);
	}
	int inv(int i) { return i + n; }
    void add_clause(int a, int b, bool arev = false, bool brev = false) {
        int u1 = (arev) ? inv(a) : a, v1 = (brev) ? b : inv(b);
        int u2 = (brev) ? inv(b) : b, v2 = (arev) ? a : inv(a);

        scc.adj[u1].push_back(v1);
        scc.adj[u2].push_back(v2);
    }

    bool correct() {
        for (int i = 0; i < n; i++)
            if (scc.scc_id[i] == scc.scc_id[inv(i)]) return false;
        return true;
    }
}
struct SCC {
    vector<int> visited, scc_id;
    int scc_cnt, n;
    vector<vector<int>> adj;
    vector<vector<int>> scc;
    stack<int> st;
    void init(int _n) {
        n = _n;
        scc_cnt = 0;
        adj.clear(); adj.resize(n);
        visited.clear();  visited.resize(n, -1);
        scc_id.clear();  scc_id.resize(n, -1);
        scc.clear();
    }
    int dfs(int cur) {
        int ret = visited[cur] = scc_cnt++;
        st.push(cur);

        for (auto nxt : adj[cur]) {
            if (visited[nxt] == -1) ret = min(ret, dfs(nxt));
            else if (scc_id[nxt] == -1) ret = min(ret, visited[nxt]);
        }

        if (ret == visited[cur]) {
            vector<int> v;
            while (true) {
                int t = st.top(); st.pop();
                scc_id[t] = scc.size() + 1;
                v.push_back(t);
                if (t == cur) break;
            }
            scc.push_back(v);
            scc_cnt++;
        }
        return ret;
    }

    void get_scc() {
        for (int i = 1; i <= n; i++) {
            if (visited[i] == -1) dfs(i);
        }
    }
};
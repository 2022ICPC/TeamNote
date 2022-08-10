#include <bits/stdc++.h>
using namespace std;

namespace tarzan {
    constexpr int N = 1003;
    int visited[N], scc_id[N], scc_cnt, n;
    vector<int> adj[N];
    vector<vector<int>> scc;
    stack<int> st;
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
        memset(scc_id, -1, sizeof(scc_id));
        memset(visited, -1, sizeof(visited));
        for (int i = 1; i <= n; i++) {
            if (visited[i] == -1) dfs(i);
        }
    }
}

using namespace tarzan;
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b); 
    }
    tarzan::get_scc();
}
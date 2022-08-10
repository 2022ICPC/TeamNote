namespace string {
	vector<int> KMP(string from, string to) {
		int n = from.size(), m = to.size();
		vector<int> fail(m + 1);
		for (int i = 1, j = 0; i < m; i++) {
			while (j && to[i] != to[j]) j = fail[j];
			if (to[i] == to[j]) j++;
			fail[i + 1] = j;
		}
		vector<int> ans;
		for (int i = 0, j = 0; i < n; i++) {
			while (j && from[i] != to[j]) j = fail[j];
			if (from[i] == to[j]) j++;
			if (j == m) ans.push_back(i - m + 1), j = fail[j];
		}
		return ans;
	}
	struct Trie {
		map<char, Trie*> to;
		Trie* fail;
		bool end;
		void insert(int idx, string& vec) {
			if (idx == vec.size()) {
				end = true;
				return;
			}
			if (to.find(vec[idx]) == to.end())
				to[vec[idx]] = new Trie();
			to[vec[idx]]->insert(idx + 1, vec);
		}
	};
	Trie* CreateTrie(vector<string> str) {
		Trie* trie = new Trie();
		for (auto& s : str) trie->insert(0, s);
		queue<Trie*> q;
		q.push(trie->fail = trie);
		while (q.size()) {
			Trie* top = q.front(); q.pop();
			for (auto& p : top->to) {
				char c = p.first; Trie* nxt = p.second;
				if (top == trie) nxt->fail = trie;
				else {
					Trie* f = top->fail;
					while (f != trie && f->to.find(c) == f->to.end())
						f = f->fail;
					if (f->to.find(c) != f->to.end())
						f = f->to[c];
					nxt->fail = f;
				}
				if (nxt->fail->end) top->end = true;
				q.push(nxt);
			}
		}
		return trie;
	}
	bool AhoCorasick(string str, Trie* root) {
		bool ans = false;
		Trie* curr = root;
		for (char c : str) {
			while (curr != root && curr->to.find(c) == curr->to.end())
				curr = curr->fail;
			if (curr->to[c])
				curr = curr->to[c];
			if (curr->end) {
				ans = true;
				break;
			}
		}
		return ans;
	}
}
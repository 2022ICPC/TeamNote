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
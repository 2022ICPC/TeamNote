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
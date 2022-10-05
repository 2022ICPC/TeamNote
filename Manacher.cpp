int manacher(string str) {
	string arr;
	for (char c : str) {
		arr.push_back('#');
		arr.push_back(c);
	}
	arr.push_back('#');
	swap(str, arr);
	int n = str.size();
	vector<int> vec(n);
	int r = 0, p = 0;
	for (int i = 0; i < n; i++) {
		if (i > r) vec[i] = 0;
		else vec[i] = min(r - i, vec[2 * p - i]);

		while (i - vec[i] - 1 >= 0 && i + vec[i] + 1 < n && str[i - vec[i] - 1] == str[vec[i] + i + 1])
			vec[i]++;

		if (r < i + vec[i]) {
			r = i + vec[i];
			p = i;
		}
	}
	return *max_element(vec.begin(), vec.end());
}
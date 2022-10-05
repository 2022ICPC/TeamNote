pi operator-(pi a, pi b) {
	return { a.x - b.x, a.y - b.y };
}
ll get(vector<pi>& arr) {
	vector<pi> cv = hull(arr);
	int l = 0, r = 0;
	for (int i = 0; i < cv.size(); i++) {
		if (cv[l].x > cv[i].x) l = i;
		if (cv[r].x < cv[i].x) r = i;
	}

	pi line = { 0, 1 };

	ll ans = dst(cv[l], cv[r]);
	int sz = cv.size();
	for (int i = 0; i < sz; i++) {
		if (ccw(cv[(l + 1) % sz] - cv[l], cv[r] - cv[(r + 1) % sz]) > 0)
			l = (l + 1) % sz;
		else
			r = (r + 1) % sz;

		ans = max(ans, dst(cv[l], cv[r]));
	}

	return ans;
}
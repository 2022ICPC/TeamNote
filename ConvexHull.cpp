typedef long long ll;
typedef pair<ll, ll> pi;
#define x first
#define y second
ll ccw(pi a, pi b, pi c, bool area = false) {
	ll _ = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	if (area) return _;

	if (_ < 0) return -1;
	else if (_ > 0) return 1;
	return 0;
}
ll pw(ll x) { return x * x; }
ll dst(pi a, pi b) { return pw(a.x - b.x) + pw(a.y - b.y); }
vector<pi> hull(vector<pi>& vec) {
	swap(vec[0], *min_element(vec.begin(), vec.end()));
	sort(vec.begin() + 1, vec.end(), [&](auto& a, auto& b) -> bool {
		ll cw = ccw(vec[0], a, b);
		if (cw != 0) return cw > 0;
		return dst(vec[0], a) < dst(vec[0], b);
		});

	vector<pi> ans;
	for (auto& p : vec) {
		while (ans.size() > 1 && ccw(ans[ans.size() - 2], ans.back(), p) <= 0)
			ans.pop_back();
		ans.push_back(p);
	}
	return ans;
}
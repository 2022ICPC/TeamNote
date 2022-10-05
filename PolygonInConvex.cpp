typedef long long ll;
typedef pair<ll, ll> pi;
#define x first
#define y second
bool f(vector<pi>& cv, pi p) {
	int n = cv.size();
	if (ccw(cv[0], cv[1], p) < 0 ||
		ccw(cv[0], cv.back(), p) > 0) return false;
	int lo = 1, hi = n - 1, ans = 1;
	while (lo <= hi) {
		int mid = lo + hi >> 1;
		if (ccw(cv[0], cv[mid], p) > 0)
			lo = mid + 1, ans = mid;
		else hi = mid - 1;
	}
	return ccw(cv[ans], cv[(ans + 1) % n], p) >= 0;
}
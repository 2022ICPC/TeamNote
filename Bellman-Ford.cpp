const ll inf = 1e18;
struct Line { ll u, v, c; };
vector<ll> bellman(int n, vector<Line>& e) {
	vector<ll> dst(n, inf);
	dst[1] = 0;
	for (int i = 0; i < n; i++) for (auto& l : e) {
		if (dst[l.u] != inf && dst[l.v] > dst[l.u] + l.c) {
			dst[l.v] = dst[l.u] + l.c;
			if (i == n - 1) return vector<ll>(n, -1);
		}
	}
	return dst;
}
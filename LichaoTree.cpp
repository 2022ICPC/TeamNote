//Minimum
typedef long long ll;
const ll inf = 1e18;
struct Line {
	ll a, b;
	ll f(ll x) { return a * x + b; }
};
struct Lichao {
	struct Node {
		ll l, r;
		Line line;
	};
	ll n, psum, ns, ne;
	vector<Node> seg;
	vector<Line> lines;
	void init(int s, int e) {
		ns = s, ne = e;
		seg.push_back({ -1, -1, {0, inf} });
	}
	int size() { return lines.size(); }
	void insert(int num, int s, int e, Line l) {
		Line lo = seg[num].line, hi = l;
		if (lo.f(s) > hi.f(s)) swap(lo, hi);
		if (lo.f(e) <= hi.f(e)) {
			seg[num].line = lo;
			return;
		}
		int mid = s + e >> 1;
		if (lo.f(mid) < hi.f(mid)) {
			seg[num].line = lo;
			if (seg[num].r == -1) {
				seg[num].r = seg.size();
				seg.push_back({ -1, -1, {0, inf} });
			}
			insert(seg[num].r, mid + 1, e, hi);
		}
		else {
			seg[num].line = hi;
			if (seg[num].l == -1) {
				seg[num].l = seg.size();
				seg.push_back({ -1, -1, {0, inf} });
			}
			insert(seg[num].l, s, mid, lo);
		}
	}
	void insert(Line l) {
		l.b -= psum;
		lines.push_back(l);
		insert(0, ns, ne, l);
	}
	void apply() {
		for (auto& l : lines) l.b += psum;
		for (auto& l : seg) l.line.b += psum;
		psum = 0;
	}
	ll query(int num, int s, int e, ll x) {
		if (num == -1) return inf;
		int mid = s + e >> 1;
		ll d = seg[num].line.f(x) + psum;
		if (x <= mid) return min(d, query(seg[num].l, s, mid, x));
		else return min(d, query(seg[num].r, mid + 1, e, x));
	}
	ll query(ll x) { return query(0, ns, ne, x); }
};
//https://www.secmem.org/blog/2019/09/17/Half-Plane-Intersection/
#define sz(x) ((int)x.size())
typedef long long ll;
typedef long double ld;
struct point {
	ld x, y;
	point() {}
	point(ld x, ld y) :x(x), y(y) {}
};
struct line {
	point s, t;
	line() {}
	line(point s, point t) : s(s), t(t) {}
};
inline bool equals(ld a, ld b) { return abs(a - b) < 1e-9; }
bool line_intersect(point& s1, point& e1, point& s2, point& e2, point& v) {
	ld vx1 = e1.x - s1.x, vy1 = e1.y - s1.y;
	ld vx2 = e2.x - s2.x, vy2 = e2.y - s2.y;
	ld det = vx1 * (-vy2) - (-vx2) * vy1;
	if (equals(det, 0)) return 0;
	ld s = (ld)((s2.x - s1.x) * (-vy2) + (s2.y - s1.y) * vx2) / det;
	v.x = s1.x + vx1 * s;
	v.y = s1.y + vy1 * s;
	return 1;
}
bool bad(line& a, line& b, line& c) {
	point v;
	if (!line_intersect(a.s, a.t, b.s, b.t, v)) return 0;
	ld crs = (c.t.x - c.s.x) * (v.y - c.s.y) - (c.t.y - c.s.y) * (v.x - c.s.x);
	return crs < 0 || equals(crs, 0);
}
vector<point> HPI(vector<line>& ln) {
	auto lsgn = [&](const line& a) {
		if (a.s.y == a.t.y) return a.s.x > a.t.x;
		return a.s.y > a.t.y;
	};
	sort(ln.begin(), ln.end(), [&](const line& a, const line& b) {
		if (lsgn(a) != lsgn(b)) return lsgn(a) < lsgn(b);
		return (a.t.x - a.s.x) * (b.t.y - b.s.y) - (a.t.y - a.s.y) * (b.t.x - b.s.x) > 0;
		});
	deque<line> dq;
	for (int i = 0; i < sz(ln); i++) {
		while (dq.size() >= 2 && bad(dq[dq.size() - 2], dq.back(), ln[i]))
			dq.pop_back();
		while (dq.size() >= 2 && bad(dq[0], dq[1], ln[i]))
			dq.pop_front();
		if (dq.size() < 2 || !bad(dq.back(), ln[i], dq[0]))
			dq.push_back(ln[i]);
	}
	vector<point> res;
	if (dq.size() >= 3) for (int i = 0; i < sz(dq); i++) {
		int j = (i + 1) % sz(dq);
		point v;
		if (!line_intersect(dq[i].s, dq[i].t, dq[j].s, dq[j].t, v)) continue;
		res.push_back(v);
	}
	return res;
}
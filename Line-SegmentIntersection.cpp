//BOJ 12555, by shwldus067
typedef pair<int, int> pi;
#define x first
#define y second
struct Line { pi s, e; };
int ccw(pi a, pi b, pi c) {
	int ret = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	if (ret > 0) return 1;
	else if (ret == 0) return 0;
	return -1;
}
int cross(pi a, pi b, Line l) {
	int p = ccw(a, b, l.s), q = ccw(a, b, l.e);
	int r = ccw(l.s, l.e, a), s = ccw(l.s, l.e, b);
	if (p == 0 && q == 0 && r == 0 && s == 0) {
		if (a > b)	swap(a, b);
		if (l.s > l.e)	swap(l.s, l.e);
		if (l.s == b || a == l.e)	return 1;
		return (a < l.e&& l.s < b) << 3;
	}
	return p * q <= 0 && r * s <= 0;
}
int rectCross(pi s, pi e, Line l) {
	vector<pi> sq = { {s.x, s.y}, {s.x, e.y}, {e.x, e.y}, {e.x, s.y}, {s.x, s.y} };
	int res = 0;
	for (int i = 0; i < 4; i++) {
		res += cross(sq[i], sq[i + 1], l);
		if (cross(sq[i], sq[i], l))	res--;
	}
	return min(res, 4);
}
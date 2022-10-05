typedef long long ll;
typedef pair<ll, ll> pi;
#define x first
#define y second
bool pointInRect(pi& p, vector<pi>& pos) {
	int cnt = 0;

	for (int i = 0; i < pos.size(); i++) {
		int nxt = (i + 1) % pos.size();
		double sx = pos[i].x, sy = pos[i].y;
		double ex = pos[nxt].x, ey = pos[nxt].y;

		if ((sy > p.y) != (ey > p.y)) {
			double x = (ex - sx) * (p.y - sy) / (ey - sy) + sx;
			if (p.x < x) cnt++;
		}
	}

	return cnt % 2;
}
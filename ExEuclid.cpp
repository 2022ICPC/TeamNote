typedef long long ll;
struct Euclid {
	ll g, x, y;
};
//ax+by=1, get a, b
Euclid egcd(ll a, ll b) {
	if (b == 0) return { a, 1, 0 };
	Euclid ret = egcd(b, a % b);
	return { ret.g, ret.y, ret.x - (a / b) * ret.y };
}
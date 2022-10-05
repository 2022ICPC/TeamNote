typedef long long ll;
const int MAX = 100001;
ll phi[MAX], low[MAX];
//phi(n) is equal to the number of integers from 1 to n that are prime to n.
ll f(ll n) {
	ll i; ll ret = n;
	for (i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			ret -= ret / i;
			while (n % i == 0) n /= i;
		}
	}
	if (n != 1) ret -= ret / n;
	return ret;
}
void fillPhi(int n) {
	phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = i; j <= n; j += i) {
			if (!low[j]) low[j] = i;
		}
		phi[i] = i;
		for (int j = i; j != 1; ) {
			int p = low[j];
			while (j % p == 0) {
				j /= p;
			}
			phi[i] = (1ll * phi[i] * (p - 1)) / p;
		}
	}
}
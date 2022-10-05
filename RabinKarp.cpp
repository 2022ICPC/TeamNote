typedef long long ll;
template<ll key = 29, ll mod = 1'000'000'007>
struct RabinKarp {
	int n;
	vector<ll> p;
	void init(int n) {
		this->n = n;
		p.resize(n);
		p[0] = 1;
		for (int i = 1; i < n; i++) p[i] = (p[i - 1] * key) % mod;
	}
	vector<Q> hashing(string& arr, int gap) {
		assert(arr.size() <= n);
		vector<Q> ans;
		ll now = 0, idx = 0;
		for (int i = 0; i < arr.size(); i++) {
			if (i >= gap) {
				ans.push_back({ now, idx++ });
				now = (now - p[gap - 1] * arr[i - gap] % mod + mod) % mod;
			}
			now = (now * key) % mod;
			now = (now + arr[i]) % mod;
		}
		ans.push_back({ now, idx });
		return ans;
	}
};
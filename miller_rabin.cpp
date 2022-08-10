namespace miller {
	typedef unsigned long long ull;

	vector<int> test = { 2, 7, 61 };

	ull mypow(ull x, ull cnt, ull mod) {
		x %= mod;
		ull ans = 1LL;
		for (; cnt; ans = (ans * ans) % mod, cnt >>= 1LL)
			if (cnt & 1) ans = (ans * x) % mod;
		return ans;
	}

	bool miller_rabin(ull n, int  a) {
		if (a % n == 0) return true;
		ull d = n - 1;
		while (d) {
			ull k = mypow(a, d, n);
			if (k == n - 1) return true;
			if (d & 1) return k == n - 1 || k == 1;
			d >>= 1;
		}
	}

	bool prime(ull x) {
		for (auto& l : test)
			if (!miller_rabin(x, l)) return false;
		return true;
	}
}
typedef long long ll;
const ll MAX = 1000000;
ll u[MAX + 1];
//find the number of square-free numbers less than or eqaul to num
ll func(ll num) {
	ll cnt = 0;
	for (ll i = 1; i * i <= num; i++)
		cnt += u[i] * (num / (i * i));
	return cnt;
}
void init() {
	u[1] = 1;
	for (int i = 1; i <= MAX; i++)
		for (int j = 2 * i; j <= MAX; j += i)
			u[j] -= u[i];
}
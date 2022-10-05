typedef long long ll;
const int MAX = 300001;
//[l..r] find k-th minimum number in O(logN)
struct PST {
	struct Node {
		ll cnt;
		Node* l, * r;
	};
	int n;
	Node* root[MAX];
	void func(int _n) {
		n = _n;
		root[0] = new Node();
		init(root[0], 0, n - 1);
	}
	void init(Node* node, int s, int e) {
		if (s == e) return;
		int mid = s + e >> 1;
		node->l = new Node();
		node->r = new Node();
		init(node->l, s, mid); init(node->r, mid + 1, e);
	}
	void update(Node* prv, Node* now, int s, int e, int idx, ll a) {
		if (s == e) {
			now->cnt += a;
			return;
		}
		int mid = s + e >> 1;
		if (idx <= mid) {
			now->l = new Node(); now->r = prv->r;
			now->l->cnt += prv->l->cnt;
			update(prv->l, now->l, s, mid, idx, a);
		}
		else {
			now->l = prv->l; now->r = new Node();
			now->r->cnt += prv->r->cnt;
			update(prv->r, now->r, mid + 1, e, idx, a);
		}
		now->cnt = now->l->cnt + now->r->cnt;
	}
	void update(int num, int idx, ll a) {
		root[num] = new Node();
		update(root[num - 1], root[num], 0, n - 1, idx, a);
	}

	ll query(Node* nl, Node* nr, int s, int e, int k) {
		if (s == e) return s;
		int mid = s + e >> 1;
		int cnt = nr->l->cnt - nl->l->cnt;
		if (k <= cnt)
			return query(nl->l, nr->l, s, mid, k);
		else
			return query(nl->r, nr->r, mid + 1, e, k - cnt);
	}
	ll query(int il, int ir, int k) { return query(root[il - 1], root[ir], 0, n - 1, k); }
};
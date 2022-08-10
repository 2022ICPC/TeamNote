//#include <bits/stdc++.h>
//using namespace std;
//namespace dp_opt {
//	typedef long long ll;
//	struct Line {
//		bool inf;
//		double x;
//		ll a, b;
//	};
//	bool operator<(const Line& l1, const Line& l2) {
//		if (l1.inf || l2.inf) return l1.x < l2.x;
//		return l1.a > l2.a;
//	}
//	struct CHT : set<Line> {
//		typedef set<Line>::iterator ITR;
//
//		double cross(Line l1, Line l2) {
//			return (double)(l2.b - l1.b) / (l1.a - l2.a);
//		}
//		bool hasPrev(ITR itr) { return itr != begin(); }
//		bool hasNext(ITR itr) { return itr != end() && next(itr) != end(); }
//
//		bool bad(ITR itr) {
//			if (hasNext(itr) && next(itr)->b <= itr->b) return true;
//
//			return hasPrev(itr) && hasNext(itr) &&
//				cross(*prev(itr), *next(itr)) <= cross(*prev(itr), *itr);
//		}
//		void SetX(ITR itr) {
//			if (!hasPrev(itr)) return;
//			Line now = *itr;
//			now.x = cross(*prev(itr), *itr);
//			insert(erase(itr), now);
//		}
//		void add(ll a, ll b) {
//			auto itr = lower_bound({ 0, 0, a, b });
//
//			if (itr != end() && itr->a == a) {
//				if (itr->b <= b) return;
//				erase(itr);
//			}
//
//			itr = insert({ 0, 0, a, b }).first;
//			if (bad(itr)) erase(itr);
//			else {
//				while (hasPrev(itr) && bad(prev(itr))) erase(prev(itr));
//				while (hasNext(itr) && bad(next(itr))) erase(next(itr));
//
//				if (hasNext(itr)) SetX(next(itr));
//				SetX(itr);
//			}
//		}
//
//		ll query(ll x) {
//			Line now = *prev(upper_bound({ 1, (double)x, 0, 0 }));
//			return now.a * x + now.b;
//		}
//	};
//}
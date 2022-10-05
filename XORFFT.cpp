#include <bits/stdc++.h>
using namespace std;
namespace XORFFT {
    using ll = long long;
    using cpx = complex<double>;
    const double PI = acos(-1);
    void XORFFT(vector<ll>& v, bool inv) {
        ll S = v.size();
        for (ll i = 1, j = 0; i < S; i++) {
            ll bit = S / 2;
            while (j >= bit) {
                j -= bit;
                bit /= 2;
            }
            j += bit;
            if (i < j) swap(v[i], v[j]);
        }
        for (ll k = 1; k < S; k *= 2) {
            for (ll i = 0; i < S; i += k * 2) {
                for (ll j = 0; j < k; j++) {
                    ll even = v[i + j];
                    ll odd = v[i + j + k];
                    v[i + j] = even + odd;
                    v[i + j + k] = even - odd;
                }
            }
        }
        if (inv)
            for (ll i = 0; i < S; i++) v[i] /= S;
    }
    vector<ll> XORmultiply(std::vector<ll>& v, std::vector<ll>& u) {
        vector<ll> vc(v.begin(), v.end());
        vector<ll> uc(u.begin(), u.end());
        ll S = 2;
        while (S < v.size() + u.size()) S *= 2;
        vc.resize(S); XORFFT(vc, false);
        uc.resize(S); XORFFT(uc, false);
        for (ll i = 0; i < S; i++) vc[i] *= uc[i];
        XORFFT(vc, true);
        vector<ll> w(S);
        for (ll i = 0; i < S; i++) w[i] = vc[i];
        return w;
    }
}
namespace FFT {
    using ll = long long;
    using cpx = complex<double>;
    const double PI = acos(-1);
    void FFT(vector<cpx>& v, bool inv) {
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
            double angle = (inv ? PI / k : -PI / k);
            cpx w(cos(angle), sin(angle));
            for (ll i = 0; i < S; i += k * 2) {
                cpx z(1, 0);
                for (ll j = 0; j < k; j++) {
                    cpx even = v[i + j];
                    cpx odd = v[i + j + k];
                    v[i + j] = even + z * odd;
                    v[i + j + k] = even - z * odd;
                    z *= w;
                }
            }
        }
        if (inv)
            for (ll i = 0; i < S; i++) v[i] /= S;
    }

    vector<ll> multiply(vector<ll>& v, vector<ll>& u) {
        vector<cpx> vc(v.begin(), v.end());
        vector<cpx> uc(u.begin(), u.end());
        ll S = 2;
        while (S < v.size() + u.size()) S *= 2;
        vc.resize(S); FFT(vc, false);
        uc.resize(S); FFT(uc, false);
        for (ll i = 0; i < S; i++) vc[i] *= uc[i];
        FFT(vc, true);
        vector<ll> w(S);
        for (ll i = 0; i < S; i++) w[i] = round(vc[i].real());
        return w;
    }
}
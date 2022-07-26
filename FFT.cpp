#include <bits/stdc++.h>
using ll=long long;
using cpx=std::complex<double>;
const double PI = acos(-1);
void FFT(std::vector<cpx> &v, bool inv) {
    ll S = v.size();
    for(ll i=1, j=0; i<S; i++) {
        ll bit = S/2;
        while(j >= bit) {
            j -= bit;
            bit /= 2;
        }
        j += bit;
        if(i < j) swap(v[i], v[j]);
    }
    for(ll k=1; k<S; k*=2) {
        double angle = (inv ? PI/k : -PI/k);
        cpx w(cos(angle), sin(angle));
        for(ll i=0; i<S; i+=k*2) {
            cpx z(1, 0);
            for(ll j=0; j<k; j++) {
                cpx even = v[i+j];
                cpx odd = v[i+j+k];
                v[i+j] = even + z*odd;
                v[i+j+k] = even - z*odd;
                z *= w;
            }
        }
    }
    if(inv)
        for(ll i=0; i<S; i++) v[i] /= S;
}

void XORFFT(std::vector<ll> &v, bool inv) {
    ll S = v.size();
    for(ll i=1, j=0; i<S; i++) {
        ll bit = S/2;
        while(j >= bit) {
            j -= bit;
            bit /= 2;
        }
        j += bit;
        if(i < j) std::swap(v[i], v[j]);
    }
    for(ll k=1; k<S; k*=2) {
        for(ll i=0; i<S; i+=k*2) {
            for(ll j=0; j<k; j++) {
                ll even = v[i+j];
                ll odd = v[i+j+k];
                v[i+j] = even + odd;
                v[i+j+k] = even - odd;
            }
        }
    }
    if(inv)
        for(ll i=0; i<S; i++) v[i] /= S;
}

std::vector<ll> multiply(std::vector<ll> &v, std::vector<ll> &u) {
    std::vector<cpx> vc(v.begin(), v.end());
    std::vector<cpx> uc(u.begin(), u.end());
    ll S = 2;
    while(S < v.size() + u.size()) S *= 2;
    vc.resize(S); FFT(vc, false);
    uc.resize(S); FFT(uc, false);
    for(ll i=0; i<S; i++) vc[i] *= uc[i];
    FFT(vc, true);
    std::vector<ll> w(S);
    for(ll i=0; i<S; i++) w[i] = round(vc[i].real());
    return w;
}

std::vector<ll> XORmultiply(std::vector<ll> &v, std::vector<ll> &u) {
    std::vector<ll> vc(v.begin(), v.end());
    std::vector<ll> uc(u.begin(), u.end());
    ll S = 2;
    while(S < v.size() + u.size()) S *= 2;
    vc.resize(S); XORFFT(vc, false);
    uc.resize(S); XORFFT(uc, false);
    for(ll i=0; i<S; i++) vc[i] *= uc[i];
    XORFFT(vc, true);
    std::vector<ll> w(S);
    for(ll i=0; i<S; i++) w[i] = vc[i];
    return w;
}

int main() {
    // FFT
    int N,M; std::cin>>N>>M;
    std::vector<ll> v1(N), v2(M);
    for(int i=0; i<N; ++i){
        std::cin>>v1[i];
    }
    for(int i=0; i<M; ++i){
        std::cin>>v2[i];
    }
    // 1. FFT convolution
    std::vector<ll> v3 = multiply(v1,v2);

    // 2. xor convolution
    std::vector<ll> v4 = XORmultiply(v1,v2);
}
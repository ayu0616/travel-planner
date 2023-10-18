#include "../lib.hpp"

// const int MOD = 998244353;
// const int MOD = 1000000007;
// const int MOD = 1000000009;

// using mint = static_modint<MOD>;

int main()
{
    ll N;
    cin >> N;
    vvl A(N, vl(N));
    rep(i, N) rep(j, N) cin >> A[i][j];

    vvl dp(1 << N, vl(N, LLONG_MAX / 2)), prev(1 << N, vl(N, -1));
    dp[0][0] = 0;
    rep(S, 1 << N)
    {
        rep(i, N)
        {
            rep(j, N)
            {
                if (S >> j & 1)
                    continue;
                if (dp[S | 1 << j][j] > dp[S][i] + A[i][j])
                {
                    dp[S | 1 << j][j] = dp[S][i] + A[i][j];
                    prev[S | 1 << j][j] = i;
                }
            }
        }
    }

    cout << dp[(1 << N) - 1][0] << endl;

    vl ans;
    ll S = (1 << N) - 1, i = 0;
    while (S)
    {
        ans.push_back(i);
        ll j = prev[S][i];
        S ^= 1 << i;
        i = j;
    }
    ans.push_back(0);
    reverse(all(ans));
    cout<<ans<<endl;
}

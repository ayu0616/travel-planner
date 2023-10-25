// 時間制約を加えてみる

#include "../lib.hpp"

// const int MOD = 998244353;
// const int MOD = 1000000007;
// const int MOD = 1000000009;

// using mint = static_modint<MOD>;

struct Place // TODO: DPの要素にする
{
    ll id;
    ll arrive_at;
    Place *prev;
};

int main()
{
    ll N;
    cin >> N;
    vvl A(N, vl(N));
    rep(i, N) rep(j, N)
    {
        cin >> A[i][j];
        A[i][j] /= 60;
    }

    // 制約
    vl condition(N, 24 * 60 - 1);
    condition[9] = 15;
    condition[5] = 25;

    vector<vvl> dp(1 << N, vvl(N, vl(24 * 60, LLONG_MAX / 2)));
    vector<vector<vector<Place *>>> states(1 << N, vector<vector<Place *>>(N, vector<Place *>(24 * 60)));
    rep(S, 1 << N) rep(i, N) rep(t, 24 * 60)
    {
        states[S][i][t] = new Place{i, t, nullptr};
    }
    dp[0][0][0] = 0;
    rep(S, 1 << N) rep(i, N) rep(j, N)
    {
        if ((S >> j) & 1)
            continue;
        rep(t, 24 * 60)
        {
            if (t + A[i][j] > condition[j])
                break;
            if (dp[S | 1 << j][j][t + A[i][j]] > dp[S][i][t] + A[i][j])
            {
                dp[S | 1 << j][j][t + A[i][j]] = dp[S][i][t] + A[i][j];
                states[S | 1 << j][j][t + A[i][j]]->prev = states[S][i][t];
            }
        }
    }

    ll min_ans = LLONG_MAX / 2, min_time = -1;
    rep(t, 24 * 60)
    {
        if (min_ans > dp[(1 << N) - 1][0][t])
        {
            min_ans = dp[(1 << N) - 1][0][t];
            min_time = t;
        }
    }
    cout << min_ans << endl;

    vpll ans;
    ll S = (1 << N) - 1, i = 0;
    Place *p = states[S][i][min_time];
    while (p)
    {
        ans.push_back({p->id, p->arrive_at});
        p = p->prev;
    }
    reverse(all(ans));
    for (auto p : ans)
    {
        cout << p << endl;
    }
}

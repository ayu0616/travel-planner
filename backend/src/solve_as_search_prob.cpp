#include "../tp-lib.hpp"

struct State : StateBase
{
    ll visited;

    State()
    {
        visited = 0;
    };

    int visited_len() const
    {
        return popcount((unsigned ll)visited);
    }

    double score() const
    {
        return arrive_at / visited_len();
    }

    bool operator<(const State &s) const
    {
        return score() < s.score();
    }

    bool operator>(const State &s) const
    {
        return score() > s.score();
    }
};

int main()
{
    int N;
    cin >> N;
    vector<vector<double>> A(N, vector<double>(N));
    rep(i, N) rep(j, N) cin >> A[i][j];

    vector<Place> places(N);
    rep(i, N)
    {
        places[i].id = i;
        int ab;
        cin >> ab;
        if (ab != -1)
            places[i].arrive_before = ab;
    }

    // 初期状態
    State *init = new State();
    init->place = &places[0];
    init->prev = nullptr;
    init->arrive_at = 0;
    init->visited = 0;

    // ゴール判定
    auto is_goal = [&](State *s)
    {
        return s->visited == (1 << N) - 1;
    };

    greater_heap<State *> que;
    que.push(init);

    State *ans = nullptr;
    while (!que.empty())
    {
        State *s = que.top();
        que.pop();
        Place cp = *s->place;
        if (is_goal(s) && (ans == nullptr || s->arrive_at < ans->arrive_at))
            ans = s;

        rep(i, N)
        {
            if (s->visited & (1 << i) || (i == 0 && s->visited_len() != N - 1))
                continue;
            double arrive_at = s->arrive_at + A[cp.id][i] + cp.stay_time;
            if (!places[i].is_visitable(arrive_at))
                continue;
            State *next = new State();
            next->place = &places[i];
            next->prev = s;
            next->arrive_at = arrive_at;
            next->visited = s->visited | (1 << i);
            que.push(next);
        }
    }

    auto visited_places = trace_back(ans);

    cout << ans->arrive_at << endl;
    cout << visited_places << endl;
}

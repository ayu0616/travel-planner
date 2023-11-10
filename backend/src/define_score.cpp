// スコアの定義を指定してみる

#include "../tp-lib.hpp"

int N;
vector<Place> places;

struct State : public StateBase
{
    // スコアは高いほうが良い
    int score() const override
    {
        int s = 0;
        rep(i, N)
        {
            if (visited >> i & 1)
                s += places[i].priority;
        }
        return s;
    }
};

int main()
{
    time_t start = time(nullptr);
    cin >> N;
    vector<vector<int>> A(N, vector<int>(N));
    rep(i, N) rep(j, N) cin >> A[i][j];

    places.resize(N);
    rep(i, N)
    {
        places[i].id = i;
        int ab, aa, st, pr;
        cin >> ab >> aa >> st >> pr;
        if (ab != -1)
            places[i].arrive_before = ab;
        if (aa != -1)
            places[i].arrive_after = aa;
        places[i].stay_time = st;
        places[i].priority = pr;
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

    priority_queue<State *,
                   vector<State *>,
                   function<bool(State *, State *)>>
        que([](State *s, State *t)
            { return *s < *t; }); // スコアが高い順に取り出す
    que.push(init);

    State *ans = nullptr;
    while (!que.empty())
    {
        State *s = que.top();
        que.pop();
        Place cp = *s->place;
        if (is_goal(s) && (ans == nullptr || *s > *ans)) // スコアが高ければ解を更新
        {
            ans = s;
            continue;
        }
        if (s->arrive_at + cp.stay_time + A[cp.id][0] > places[0].arrive_before)
        {
            auto tmp = new State();
            auto prev = s->prev;
            tmp->place = &places[0];
            tmp->prev = prev;
            tmp->arrive_at = prev->arrive_at + prev->place->stay_time + A[prev->place->id][0];
            tmp->visited = (s->visited ^ (1 << cp.id)) | (1 << 0);
            if (ans == nullptr || *tmp > *ans)
            {
                ans = tmp;
            }
            continue;
        }

        rep(i, N)
        {
            if (s->visited >> i & 1 || (i == 0 && s->visited_len() != N - 1))
                continue;
            int arrive_at = s->arrive_at + cp.stay_time + A[cp.id][i];
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

    if (ans)
    {
        auto visited_places = ans->trace_back();

        cout << ans->arrive_at << endl;
        cout << visited_places << endl;
        cerr << "time: " << time(nullptr) - start << "s" << endl;
    }
    else
    {
        cout << "-1" << endl;
    }
}

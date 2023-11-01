// 旅行プラン立て機用のライブラリ

#include "./lib.hpp"

// 営業時間を表す構造体
struct BusinessHours
{
    int start;
    int end;

    BusinessHours()
    {
        start = 0;
        end = 24 * 60 - 1;
    };

    BusinessHours(int start, int end) : start(start), end(end){};
};

// 観光スポットを表す構造体
struct Place
{
    ll id;
    // 営業時間（なければ0時00分〜23時59分）
    BusinessHours business_hours;
    // 到着したい時間の上限
    ll arrive_before;
    // 到着したい時間の下限
    ll arrive_after;
    // 滞在時間（分）
    ll stay_time;
    // 行きたい度
    int priority;

    // @brief idで初期化
    // @param id 観光スポットのid
    Place()
    {
        id = -1;
        arrive_before = 24 * 60 - 1;
        arrive_after = 0;
        stay_time = 0;
        priority = 1;
    };

    // @brief 訪問可能かどうかを判定する
    // @param arrive_at 到着時刻
    // @return 訪問可能ならtrue
    bool is_visitable(ll arrive_at) const
    {
        return max(business_hours.start, arrive_after) <= arrive_at && arrive_at + stay_time <= min(arrive_before + stay_time, business_hours.end);
    };
};

struct StateBase;

template <typename T>
concept StateBaseType = is_base_of<StateBase, T>::value;

/**
 * 状態を管理する構造体
 * それぞれの実装で継承して使う
 */
struct StateBase
{
    Place *place;
    StateBase *prev;
    double arrive_at;
    ll visited;

    StateBase()
    {
        place = nullptr;
        prev = nullptr;
        arrive_at = 0;
        visited = 0;
    };

    // 前に訪れたスポットを辿っていく関数
    vector<StateBase *> trace_back()
    {
        vector<StateBase *> visited_places;
        auto current_place = this;
        while (current_place->prev != nullptr)
        {
            visited_places.push_back(current_place);
            current_place = current_place->prev;
        }
        visited_places.push_back(current_place);
        reverse(all(visited_places));
        return visited_places;
    }

    int visited_len() const
    {
        return popcount((unsigned ll)visited);
    }

    // スコア関数
    virtual double score() const = 0;
};

template <StateBaseType T>
bool operator<(const T &l, const T &r)
{
    return l.score() < r.score();
};
template <StateBaseType T>
bool operator>(const T &l, const T &r)
{
    return r < l;
};
template <StateBaseType T>
bool operator<=(const T &l, const T &r)
{
    return !(l > r);
};
template <StateBaseType T>
bool operator>=(const T &l, const T &r)
{
    return !(l < r);
};

template <StateBaseType T>
vector<T *> trace_back(T *current_place)
{
    vector<T *> visited_places;
    while (current_place->prev != nullptr)
    {
        visited_places.push_back(current_place);
        current_place = current_place->prev;
    }
    visited_places.push_back(current_place);
    reverse(all(visited_places));
    return visited_places;
}

template <StateBaseType T>
ostream &operator<<(ostream &os, const vector<T *> &vp)
{
    rep(i, vp.size())
    {
        cout << vp[i]->place->id << " " << vp[i]->arrive_at;
        if (i != vp.size() - 1)
        {
            cout << endl;
        }
    }
    return os;
}
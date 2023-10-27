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
    // 到着したい時間
    ll arrive_before;
    // 滞在時間（分）
    ll stay_time;

    // @brief idで初期化
    // @param id 観光スポットのid
    Place()
    {
        id = -1;
        arrive_before = 24 * 60 - 1;
        stay_time = 0;
    };

    // @brief 訪問可能かどうかを判定する
    // @param arrive_at 到着時刻
    // @return 訪問可能ならtrue
    bool is_visitable(ll arrive_at) const
    {
        return business_hours.start <= arrive_at && arrive_at + stay_time <= min(arrive_before + stay_time, business_hours.end);
    };
};

/**
 * 状態を管理する構造体
 * それぞれの実装で継承して使う
 */
struct StateBase
{
    Place *place;
    StateBase *prev;
    double arrive_at;

    StateBase()
    {
        place = nullptr;
        prev = nullptr;
        arrive_at = 0;
    };
};

// 前に訪れたスポットを辿っていく関数
vector<StateBase *> trace_back(StateBase *current_place)
{
    vector<StateBase *> visited_places;
    while (current_place->prev != nullptr)
    {
        visited_places.push_back(current_place);
        current_place = current_place->prev;
    }
    visited_places.push_back(current_place);
    reverse(all(visited_places));
    return visited_places;
}

ostream &operator<<(ostream &os, const vector<StateBase *> &vp)
{
    for (auto p : vp)
        os << p->place->id << " " << p->arrive_at << endl;
    return os;
}
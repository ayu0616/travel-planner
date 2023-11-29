// 旅行プラン立て機用のライブラリ

#include <bits/stdc++.h>
using namespace std;

// マクロの定義

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) (v).begin(), (v).end()

// 型の定義

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;

// 便利な関数

template <class T>
bool chmin(T &a, T &b) {
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}

// 出力のオーバーロード

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    rep(i, v.size()) {
        cout << v[i];
        if (i != v.size() - 1) {
            cout << " ";
        }
    }
    return os;
}

// 営業時間を表す構造体
struct BusinessHours {
    int start;
    int end;

    BusinessHours() {
        start = 0;
        end = 24 * 60 * 60 - 1;
    };

    BusinessHours(int start, int end) : start(start), end(end){};
};

// 緯度を表す構造体
struct Latitude {
    double latitude;

    Latitude() { latitude = 0; };

    void is_valid() {
        if (latitude < -90 || 90 < latitude) throw invalid_argument("latitude must be in [-90, 90]");
    };

    Latitude(double latitude) : latitude(latitude) { is_valid(); };

    double operator=(double latitude) {
        double res = (this->latitude = latitude);
        is_valid();
        return res;
    }
    double operator+=(double latitude) {
        this->latitude += latitude;
        if (this->latitude > 90) this->latitude -= 180;
        return this->latitude;
    }
    double operator-=(double latitude) {
        this->latitude -= latitude;
        if (this->latitude < -90) this->latitude += 180;
        return this->latitude;
    }
};

// 経度を表す構造体
struct Longitude {
    double longitude;

    Longitude() { longitude = 0; };

    void is_valid() {
        if (longitude < -180 || 180 < longitude) throw invalid_argument("longitude must be in [-180, 180]");
    };

    Longitude(double longitude) : longitude(longitude) { is_valid(); };

    double operator=(double longitude) {
        double res = (this->longitude = longitude);
        is_valid();
        return res;
    }
    double operator+=(double longitude) {
        this->longitude += longitude;
        if (this->longitude > 180) this->longitude -= 360;
        return this->longitude;
    }
    double operator-=(double longitude) {
        this->longitude -= longitude;
        if (this->longitude < -180) this->longitude += 360;
        return this->longitude;
    }
};

// 観光スポットを表す構造体
struct Place {
    int id;
    BusinessHours business_hours;  // 営業時間（なければ0時00分〜23時59分）
    int arrive_before;             // 到着したい時間の上限
    int arrive_after;              // 到着したい時間の下限
    int stay_time;                 // 滞在時間（分）
    int priority;                  // 行きたい度
    double longitude;              // 経度
    double latitude;               // 緯度

    // @brief idで初期化
    // @param id 観光スポットのid
    Place() {
        id = -1;
        arrive_before = 24 * 60 * 60 - 1;
        arrive_after = 0;
        stay_time = 0;
        priority = 1;
    };

    // @brief 訪問可能かどうかを判定する
    // @param arrive_at 到着時刻
    // @return 訪問可能ならtrue
    bool is_visitable(ll arrive_at) const {
        return max(business_hours.start, arrive_after) <= arrive_at && arrive_at + stay_time <= min(arrive_before + stay_time, business_hours.end);
    };
};

// @brief 2つの観光スポット間の距離を計算する
// @return 距離（メートル）
// @param p1 1つ目の観光スポット
// @param p2 2つ目の観光スポット
double calc_dist(Place &p1, Place &p2) {
    double lat1 = p1.latitude * M_PI / 180;
    double lat2 = p2.latitude * M_PI / 180;
    double lon1 = p1.longitude * M_PI / 180;
    double lon2 = p2.longitude * M_PI / 180;
    double R = 6378137;
    double d = R * acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon2 - lon1));
    return d;
}

struct StateBase;

template <typename T>
concept StateBaseType = is_base_of<StateBase, T>::value;

/**
 * 状態を管理する構造体
 * それぞれの実装で継承して使う
 */
struct StateBase {
    Place *place;
    StateBase *prev;
    int arrive_at;
    ll visited;
    bool is_end = false;

    StateBase() {
        place = nullptr;
        prev = nullptr;
        arrive_at = 0;
        visited = 0;
    };

    // 前に訪れたスポットを辿っていく関数
    vector<StateBase *> trace_back() {
        vector<StateBase *> visited_places;
        auto current_place = this;
        while (current_place->prev != nullptr) {
            visited_places.push_back(current_place);
            current_place = current_place->prev;
        }
        visited_places.push_back(current_place);
        reverse(all(visited_places));
        return visited_places;
    }

    int visited_len() const { return popcount((unsigned ll)visited); }

    // スコア関数
    virtual float score() const = 0;
};

template <StateBaseType T>
vector<T *> trace_back(T *current_place) {
    vector<T *> visited_places;
    while (current_place->prev != nullptr) {
        visited_places.push_back(current_place);
        current_place = current_place->prev;
    }
    visited_places.push_back(current_place);
    reverse(all(visited_places));
    return visited_places;
}

template <StateBaseType T>
ostream &operator<<(ostream &os, const vector<T *> &vp) {
    rep(i, vp.size()) {
        cout << vp[i]->place->id << " " << vp[i]->arrive_at;
        if (i != vp.size() - 1) {
            cout << endl;
        }
    }
    return os;
}
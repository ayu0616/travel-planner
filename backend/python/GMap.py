from datetime import datetime, timedelta
from typing import Optional, TypedDict
from zoneinfo import ZoneInfo

import googlemaps


class Location(TypedDict):
    """
    位置情報を表す辞書型

    Attributes:
        - lat (float): 緯度
        - lng (float): 経度
    """

    lat: float
    lng: float


class GMap(googlemaps.Client):
    """Google Maps APIを利用するクラス"""

    def __init__(self, key=None):
        super().__init__(key=key)

    def distance_matrix(
        self,
        origins: list[str],
        destinations: list[str],
        departure_time: Optional[datetime] = None,
    ):
        """距離行列を取得する

        Args:
            - origins (list[str]): 出発地点のリスト
            - destinations (list[str]): 到着地点のリスト
            - departure_time (datetime, optional): 出発時刻. Defaults to None.

        Returns:
            - list[list[int]]: 距離行列（単位は秒）
        """
        res = super().distance_matrix(origins, destinations, departure_time=departure_time, mode="walking", language="ja-JP", region="jp")
        dist: list[list[int]] = []
        for row in res["rows"]:
            dist.append([])
            for i in range(len(row["elements"])):
                dist[-1].append(row["elements"][i]["duration"]["value"])
        return dist

    def geocode(self, spot: str):
        res = super().geocode(spot, language="ja-JP", region="jp")
        return res

    def get_location(self, spot: str) -> Location:
        """
        指定された場所の緯度経度を取得する。

        Args:
            spot (str): 場所の名前。

        Returns:
            Location: 場所の緯度経度情報。
        """
        res = self.geocode(spot)
        return res[0]["geometry"]["location"]


if __name__ == "__main__":
    import os

    from dotenv import load_dotenv

    load_dotenv()
    gmap = GMap(os.getenv("GOOGLE_MAPS_API_KEY"))
    origins = ["京都駅"]
    destinations = [
        "下鴨神社",
        "金閣寺",
        "清水寺",
        "伏見稲荷大社",
        "嵐山",
        "二条城",
        "平等院鳳凰堂",
        "八坂神社",
        "祇園",
        "三十三間堂",
        "東寺",
        "京都御所",
        "京都タワー",
        "南禅寺",
        "永観堂",
        "東福寺",
        "平安神宮",
        "渡月橋",
        "銀閣寺",
        "上賀茂神社",
        "貴船神社",
        "鞍馬寺",
        "京都国立博物館",
        "京都水族館",
        "京都鉄道博物館",
    ]
    print("destinations:", len(destinations))
    res = gmap.distance_matrix(origins, destinations, departure_time=datetime.now(ZoneInfo("Asia/Tokyo")) + timedelta(hours=10))
    print(*res, sep="\n")

    # res = gmap.get_location("京都駅")
    # print(res)

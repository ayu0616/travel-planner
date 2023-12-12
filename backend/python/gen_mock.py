#! /opt/homebrew/bin/python

import os
import random

import yaml

# コンフィグファイルの読み込み
with open(os.path.join(os.path.dirname(__file__), "mock.config.yaml"), "r") as f:
    config = yaml.safe_load(f)

n = config["n"]
p = config["p"]
max_time = config["max_time"]
# max_time = 8 * 60 * 60


def generate():
    d_matrix: list[list[int]] = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(i + 1, n):
            d_matrix[i][j] = d_matrix[j][i] = random.randint(60, 45 * 60)

    lines: list[list[int]] = []
    for _ in range(n):
        lines.append([])
        ab = random.randint(15, max_time) if random.random() < p else -1
        lines[-1].append(ab)
        if ab == -1:
            ab = max_time
        aa = max(-1, ab - 30 * 60 - random.randint(0, max_time)) if random.random() < p else -1
        lines[-1].append(aa)
        lines[-1].append(random.randint(15 // 5, 90 // 5) * 5 * 60)
        lines[-1].append(random.randint(1, 3))

    lines[0][0] = max_time  # 最初の地点に最大の制限時間以内に到着するようにする
    lines[0][2] = 0  # 最初の地点の滞在時間は0にする
    return d_matrix, lines


def write_mock(d_matrix: list[list[int]], lines: list[list[int]], f):
    print(n, file=f)
    for row in d_matrix:
        print(*row, file=f)
    for line in lines:
        print(*line, file=f)


if __name__ == "__main__":
    d_matrix, lines = generate()
    with open("./in.txt", "w") as f:
        write_mock(d_matrix, lines, f)

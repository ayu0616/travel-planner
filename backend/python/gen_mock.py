#! /opt/homebrew/bin/python

import random

n = 50

d_matrix: list[list[int]] = [[0] * n for _ in range(n)]
for i in range(n):
    for j in range(i + 1, n):
        d_matrix[i][j] = d_matrix[j][i] = random.randint(60, 45 * 60)

lines: list[list[int]] = []
for _ in range(n):
    lines.append([])
    ab = -1 if random.random() < 0.85 else random.randint(15, 8 * 60 * 60)
    lines[-1].append(ab)
    if ab == -1:
        ab = 8 * 60 * 60
    aa = -1 if random.random() < 0.85 else max(-1, ab - 30 * 60 - random.randint(0, 8 * 60 * 60))
    lines[-1].append(aa)
    lines[-1].append(random.randint(15 // 5, 90 // 5) * 5 * 60)
    lines[-1].append(random.randint(1, 3))

lines[0][0] = 8 * 60 * 60  # 最初の地点に8時間以内に到着するようにする
lines[0][2] = 0  # 最初の地点の滞在時間は0にする

with open("./in.txt", "w") as f:
    print(n, file=f)
    for row in d_matrix:
        print(*row, file=f)
    for line in lines:
        print(*line, file=f)

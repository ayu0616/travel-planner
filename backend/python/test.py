# cpp標準エラー出力の最後の行を取得してスコア計算する


import glob
import os
import subprocess
from concurrent.futures import ThreadPoolExecutor
from multiprocessing import freeze_support

os.chdir(os.path.dirname(__file__))

in_files = glob.glob(os.path.join("../in", "*.txt"))
EXEC_FILE = "../dist/sa"

score = 0.0


def exec_cpp(in_file: str):
    res = subprocess.run(f"{EXEC_FILE} < {in_file}", shell=True, stdout=subprocess.PIPE)
    s = float(res.stdout.decode().split("\n")[0])
    global score
    score += s
    # print(os.path.basename(in_file), s)


if __name__ == "__main__":
    freeze_support()
    with ThreadPoolExecutor(max_workers=50) as executor:
        executor.map(exec_cpp, in_files)

    print(EXEC_FILE, score)

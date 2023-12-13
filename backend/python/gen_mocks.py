import os
import shutil

from gen_mock import generate, write_mock

os.chdir(os.path.dirname(__file__))

shutil.rmtree("../in", ignore_errors=True)
os.mkdir("../in")

for i in range(100):
    d_matrix, lines = generate()
    with open(f"../in/{i:03}.txt", "w") as f:
        write_mock(d_matrix, lines, f)

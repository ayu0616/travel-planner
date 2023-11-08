import subprocess

p1 = subprocess.Popen("dist/test_interactive", stdin=subprocess.PIPE, stdout=subprocess.PIPE)

if p1.stdin is None or p1.stdout is None:
    print("Failed to open pipe")
    exit(1)

while True:
    line = p1.stdout.readline().decode("utf-8")
    if line.startswith("ans"):
        break
    n = int(line)
    p1.stdin.write(f"{n * n}\n".encode("utf-8"))
    p1.stdin.flush()

print(line, end="")

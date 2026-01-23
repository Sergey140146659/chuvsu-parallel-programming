import matplotlib.pyplot as plt

data = [
    (10,   1,  0.000032),
    (10,   2,  0.000063),
    (10,   4,  0.000059),
    (10,   6,  0.000090),
    (10,   8,  0.000120),
    (10,  10,  0.000110),
    (10,  12,  0.000116),
    (1000, 1,  9.170669),
    (1000, 2,  4.646437),
    (1000, 4,  2.359196),
    (1000, 6,  1.602464),
    (1000, 8,  1.443928),
    (1000,10,  1.312690),
    (1000,12,  1.264909),
]

byN = {}
for N, th, t in data:
    byN.setdefault(N, []).append((th, t))

for N in byN:
    byN[N].sort()

plt.figure(figsize=(7, 5))

for N, pts in sorted(byN.items()):
    threads = [th for th, _ in pts]
    times = [t for _, t in pts]
    plt.plot(threads, times, marker='o', label=f"N={N}")

plt.xlabel("Number of threads")
plt.ylabel("Execution time (seconds)")
plt.title("Matrix multiplication: Time vs Threads")
plt.grid(True)
plt.legend()
plt.tight_layout()

plt.savefig("time_vs_threads.png", dpi=150)
plt.close()

print("Saved: time_vs_threads.png")

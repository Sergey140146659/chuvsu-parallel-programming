import matplotlib.pyplot as plt

data = [
    (100, 1, 0.000029),
    (100, 2, 0.000041),
    (100, 4, 0.000049),
    (100, 6, 0.000067),
    (100, 8, 0.000070),
    (100, 10, 0.000075),
    (100, 12, 0.000123),

    (10_000_000, 1, 0.020333),
    (10_000_000, 2, 0.009216),
    (10_000_000, 4, 0.004548),
    (10_000_000, 6, 0.004092),
    (10_000_000, 8, 0.003630),
    (10_000_000, 10, 0.002925),
    (10_000_000, 12, 0.002736),

    (4_000_000_000, 1, 6.084428),
    (4_000_000_000, 2, 3.160360),
    (4_000_000_000, 4, 1.636168),
    (4_000_000_000, 6, 1.100253),
    (4_000_000_000, 8, 1.014625),
    (4_000_000_000, 10, 0.941359),
    (4_000_000_000, 12, 0.939507),
]

byN = {}
for N, th, t in data:
    byN.setdefault(N, []).append((th, t))

for N in byN:
    byN[N].sort()

plt.figure(figsize=(8, 5))

for N, pts in sorted(byN.items()):
    threads = [th for th, _ in pts]
    times = [t for _, t in pts]
    plt.plot(threads, times, marker='o', label=f"N = {N}")

plt.xlabel("Number of threads")
plt.ylabel("Execution time (seconds)")
plt.title("Pi computation: Execution time vs Threads")
plt.grid(True)
plt.legend()
plt.tight_layout()

plt.savefig("pi_time_vs_threads.png", dpi=150)
plt.close()

print("Saved: pi_time_vs_threads.png")

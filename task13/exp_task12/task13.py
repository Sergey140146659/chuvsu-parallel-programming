import matplotlib.pyplot as plt

data = [
    (100, 1, 0.000010),
    (100, 2, 0.000068),
    (100, 4, 0.000111),
    (100, 6, 0.000125),
    (100, 8, 0.000139),
    (100, 10, 0.000158),
    (100, 12, 0.000177),

    (10_000_000, 1, 0.022720),
    (10_000_000, 2, 0.009984),
    (10_000_000, 4, 0.004708),
    (10_000_000, 6, 0.006077),
    (10_000_000, 8, 0.004481),
    (10_000_000, 10, 0.003012),
    (10_000_000, 12, 0.003080),

    (4_000_000_000, 1, 6.253731),
    (4_000_000_000, 2, 3.214039),
    (4_000_000_000, 4, 1.617580),
    (4_000_000_000, 6, 1.229651),
    (4_000_000_000, 8, 1.523549),
    (4_000_000_000, 10, 1.211419),
    (4_000_000_000, 12, 1.107876),
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
plt.title("Pi (critical): Execution time vs Threads")
plt.grid(True)
plt.legend()
plt.tight_layout()

plt.savefig("pi_critical_time_vs_threads.png", dpi=150)
plt.close()

print("Saved: pi_critical_time_vs_threads.png")

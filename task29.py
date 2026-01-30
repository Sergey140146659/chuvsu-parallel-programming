import matplotlib.pyplot as plt

data = {
    100: {
        1: 0.000004,
        2: 0.001394,
        4: 0.000812,
        6: 0.000774,
        8: 0.001074,
        10: 0.001236,
        12: 0.001696,
    },
    10_000_000: {
        1: 0.015938,
        2: 0.008609,
        4: 0.004271,
        6: 0.003347,
        8: 0.005193,
        10: 0.003158,
        12: 0.003373,
    },
    4_000_000_000: {
        1: 6.043668,
        2: 3.108078,
        4: 1.716508,
        6: 1.562226,
        8: 1.667727,
        10: 1.471476,
        12: 1.464194,
    },
}

plt.figure(figsize=(8, 5))

for N, times in data.items():
    ps = sorted(times.keys())
    ts = [times[p] for p in ps]

    plt.plot(ps, ts, marker='o', label=f"N = {N}")

plt.xlabel("Number of processes")
plt.ylabel("Execution time (seconds)")
plt.title("MPI Scalability (Execution Time)")
plt.grid(True)
plt.legend()

plt.savefig("mpi_time_scalability.png", dpi=300, bbox_inches="tight")

plt.show()

print("Saved to mpi_time_scalability.png")

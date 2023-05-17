import matplotlib.pyplot as plt

# Plotting the execution time of the algorithm on the board with no forced check mate
# It is important because we know that 

# plot #1 compare the algorithms with fixed number of threads on different number of N
N = [1, 2, 3, 4, 5, 6]

sequential = [0.000016196, 0.000184048, 0.00390236, 0.0725135, 1.21189, 17.6819]
modified = [0.000023001, 0.00036079, 0.00849935, 0.172657, 3.15166, 48.4764]
concurrent_bfs = [0.00027215, 0.00140542, 0.0312002, 0.687003, 12.9125, 210.178]
concurrent_dfs = [0.00112347, 0.000600531, 0.00661808, 0.129037, 1.198241, 32.0686]
concurrent_dfs_atomic = [0.00314768, 0.000567349, 0.00608291, 0.0972588, 1.99642, 31.6194]
concurrent_dfs_atomic_hashmap = [0.000279687, 0.000757293, 0.00739638, 0.0749987, 0.733426, 5.08612]

# plot #2 compare the concurrent algorithms with different number of threads on fixed N

threads = [2, 4, 8, 16]

concurrent_dfs = [70.1096, 68.2218, 30.0439, 36.8449]
concurrent_dfs_atomic = [70.1815, 68.1354, 31.0736, 37.8147]
concurrent_dfs_atomic_hashmap = [11.5452, 11.1826, 5.11179, 6.06095]

# plot #3: comparing the final best version of concurrent algorithm with 8 threads on N = 7
concurrent_final = 70.0566
sequential_initial = 242.603



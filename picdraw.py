dictx = { 7:
{
    "STL next_permutation": 0.019999999999999997,
    "recursive": 0.09499999999999999,
    "increase_base": 0.295,
    "optimized_increase_base": 0.029000000000000005,
    "decrease_base": 0.3,
    "optimized_decrease_base": 0.026000000000000002,
    "neighbour_exchange": 0.623,
    "optimized_neighbour_exchange": 0.011,
    "dictionary": 0.017999999999999995,
    "Heap's algorithm": 0.03699999999999999,
    "new_recursive": 0.087
},
8:
{
    "STL next_permutation": 0.192,
    "recursive": 0.8719999999999999,
    "increase_base": 3.3049999999999997,
    "optimized_increase_base": 0.251,
    "decrease_base": 3.032,
    "optimized_decrease_base": 0.187,
    "neighbour_exchange": 4.409,
    "optimized_neighbour_exchange": 0.07400000000000002,
    "dictionary": 0.09499999999999999,
    "Heap's algorithm": 0.21200000000000002,
    "new_recursive": 0.4979999999999999
},
9:
{
    "STL next_permutation": 1.7739999999999998,
    "recursive": 7.9590000000000005,
    "increase_base": 22.720000000000002,
    "optimized_increase_base": 1.498,
    "decrease_base": 21.151,
    "optimized_decrease_base": 1.135,
    "neighbour_exchange": 33.746,
    "optimized_neighbour_exchange": 0.575,
    "dictionary": 0.7840000000000001,
    "Heap's algorithm": 1.7709999999999997,
    "new_recursive": 4.2170000000000005
},
10:
{
    "STL next_permutation": 16.119,
    "recursive": 60.763999999999996,
    "increase_base": 255.41400000000004,
    "optimized_increase_base": 14.894,
    "decrease_base": 241.34499999999997,
    "optimized_decrease_base": 10.951,
    "neighbour_exchange": 352.101,
    "optimized_neighbour_exchange": 5.892,
    "dictionary": 7.771000000000001,
    "Heap's algorithm": 17.679000000000002,
    "new_recursive": 42.08
},
11:
{
    "STL next_permutation": 143.124,
    "recursive": 711.1290000000001,
    "increase_base": 3292.487,
    "optimized_increase_base": 161.793,
    "decrease_base": 3213.002,
    "optimized_decrease_base": 118.16400000000002,
    "neighbour_exchange": 4054.5809999999997,
    "optimized_neighbour_exchange": 63.149,
    "dictionary": 85.58000000000001,
    "Heap's algorithm": 194.49200000000002,
    "new_recursive": 462.477
},
12:
{
    "STL next_permutation": 1710.9060000000002,
    "recursive": 9090.338,
    "increase_base": 43855.909999999996,
    "optimized_increase_base": 1965.4030000000002,
    "decrease_base": 42827.44300000001,
    "optimized_decrease_base": 1383.253,
    "neighbour_exchange": 50748.598999999995,
    "optimized_neighbour_exchange": 750.845,
    "dictionary": 1021.6610000000001,
    "Heap's algorithm": 2310.796,
    "new_recursive": 5507.317999999999
}
}
print(dictx)

import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator

plt.gca().xaxis.set_major_locator(MaxNLocator(integer=True))
plt.ylim(0.0,10000.0)

for key in dictx[7].keys():
    x = []
    y = []
    for i in range(7,13):
        x.append(i)
        y.append(dictx[i][key])
    plt.plot(x, y, label = key)

plt.xlabel("Permutaion Length")
plt.ylabel("Time(ms)")
plt.legend()
plt.savefig("test.jpg")
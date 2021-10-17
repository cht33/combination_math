import os
import json
import matplotlib.pyplot as plt
from math import factorial
from matplotlib.ticker import MaxNLocator
from collections import defaultdict

plt.gca().xaxis.set_major_locator(MaxNLocator(integer=True))

target_length = range(8,14)
test_times = 10

result_maps = {}
for i in target_length:
    r_map = defaultdict(int)
    for _ in range(test_times):
        lines = os.popen('sudo sh run.sh ' + str(i)).read().split("\n")
        for line in lines[:-1]:
            line = line.split(": ")
            r_map[line[0]] += eval(line[1][:-2])
    for key in r_map.keys():
        r_map[key] /= test_times
    result_maps[i] = r_map
    print(json.dumps(result_maps[i], indent = 4))

for key in result_maps[target_length[0]].keys():
    x = []
    y = []
    for i in target_length:
        x.append(i)
        y.append(result_maps[i][key]/factorial(i))
    plt.plot(x, y, label = key)

plt.xlabel("Permutaion Length")
plt.ylabel("Time(ms)")
plt.legend()
plt.savefig("test.jpg")
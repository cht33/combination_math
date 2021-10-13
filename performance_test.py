import os
import json
import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator

plt.gca().xaxis.set_major_locator(MaxNLocator(integer=True))

target_length = range(8,16)
test_times = 10

result_maps = {}
for i in target_length:
    result_maps[i] = {}
    for _ in range(test_times):
        lines = os.popen('sudo sh run.sh ' + str(i)).read().split("\n")
        for j in range(len(lines) - 1):
            line = lines[j].split(": ")
            if line[0] not in result_maps[i]:
                result_maps[i][line[0]] = 0
            result_maps[i][line[0]] += eval(line[1][:-2])
    for key in result_maps[i].keys():
        result_maps[i][key] /= test_times
    print(json.dumps(result_maps[i], indent = 4))

for key in result_maps[target_length[0]].keys():
    x = []
    y = []
    for i in target_length:
        x.append(i)
        y.append(result_maps[i][key])
    plt.plot(x, y, label = key)

plt.xlabel("Permutaion Length")
plt.ylabel("Time(ms)")
plt.legend()
plt.savefig("test.jpg")
import os
import json
import matplotlib.pyplot as plt
from math import factorial
from matplotlib.ticker import MaxNLocator
from collections import defaultdict

def test(test_name, target_length, target_algorithm, test_times):
    result_maps = {}
    for i in target_length:
        r_map = defaultdict(int)
        for j in target_algorithm:
            for _ in range(test_times):
                lines = os.popen('sudo sh run.sh ' + str(i) + ' ' + j).read().split("\n")
                for line in lines[:-1]:
                    line = line.split(": ")
                    r_map[line[0]] += eval(line[1][:-2])
        for key in r_map.keys():
            r_map[key] /= test_times
        result_maps[i] = r_map

    f = open("result/" + test_name + ".txt", 'w+')
    print(json.dumps(result_maps, indent = 4), file = f)

    plt.gca().yaxis.set_major_locator(MaxNLocator(integer=True))
    for key in result_maps[target_length[0]].keys():
        x = []
        y = []
        for i in target_length:
            x.append(i)
            y.append(result_maps[i][key]/factorial(i))
        plt.plot(x, y, label = key)

    plt.xlabel("Permutaion Length")
    plt.legend(loc = "upper right")
    plt.savefig("fig/" + test_name + ".jpg")
    plt.close()

if __name__ == "__main__":

    target_length = range(8,14)
    target_algorithm = [
        "recursive",
        "increase_base",
        "decrease_base",
        "neighbour_exchange",
        "new_recursive"
    ]
    test_times = 10
    test('result1', target_length, target_algorithm, test_times)
    
    target_length = range(8,15)
    target_algorithm = [
        "next_permutation",
        "optimized_increase_base",
        "optimized_decrease_base",
        "optimized_neighbour_exchange",
        "dictionary",
        "heap"
    ]
    test_times = 10
    test('result2', target_length, target_algorithm, test_times)
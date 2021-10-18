import os
import json
import numpy as np
import matplotlib.pyplot as plt
from math import factorial
from matplotlib.ticker import MaxNLocator
from collections import defaultdict

TEST_TIMES = 10
plt.gca().xaxis.set_major_locator(MaxNLocator(integer=True))
def draw(file_name, target_length):
    result_maps = {}
    with open(f'result/{file_name}.txt', 'r', encoding='utf8') as fin:
        while True:
            line = fin.readline().strip()
            if line == '': break
            t, i = line.split('=')
            assert(t == 'n')
            i = int(i)
            r_map = defaultdict(list)
            for _ in range(TEST_TIMES):
                for _ in range(6):
                    name, time = fin.readline().strip().split(': ')
                    r_map[name].append(eval(time[:-2]))
            result_maps[i] = r_map

            print(i)
            for n, v in r_map.items():
                print(f'{n}: mean-{np.mean(v):.3f}, std-{np.std(v):.3f}')

    plt.clf()
    for key in result_maps[target_length[0]].keys():
        x, y = [], []
        for i in target_length:
            x.append(i)
            y.append(np.mean(result_maps[i][key])/factorial(i))
        plt.plot(x, y, label=key)
    plt.xlabel("Permutaion Length")
    plt.ylabel("Time(ms)")
    plt.legend()
    plt.savefig(f"fig/{file_name}.jpg")

if __name__ == "__main__":
    draw('output', range(8,15))
    draw('output1', range(8,14))

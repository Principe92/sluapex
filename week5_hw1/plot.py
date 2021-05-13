import matplotlib.pyplot as plt
import numpy as np
from datetime import datetime
import scipy.stats as st

def speed_up(times):

    speedups = []

    for time in times:
        s = 3.3269 / time
        speedups.append(s)
    
    return speedups

def plot():

    name = 'week5_hw1/hmw_5'

    x = [1, 2, 4, 6, 8, 10]
    y1 = np.around(speed_up([7.37923, 32.2018, 28.6271, 31.8416, 28.4773, 33.3339]), 2)
    y2 = np.around([3.3269 * i for i in x], 2)
    y3 = np.around(speed_up([3.14177, 1.59397, 0.835898, 0.627596, 0.484353, 0.464415]), 2)

    fig, ax = plt.subplots(figsize=(10, 5))
    plt.rc('font', family='serif')
    plt.rc('xtick', labelsize='small')
    plt.rc('ytick', labelsize='small')

    ax.plot(x, y1, label='atomic', marker='o')
    ax.plot(x, y2, label='ideal', marker='o')
    ax.plot(x, y3, label='reduction', marker='o')
    plt.ylabel('speedup')
    plt.xlabel('nproc')
    

    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    plt.xlim([0, 11])
    

    plt.tight_layout()
    plt.legend(loc="upper center", ncol=3)

    fig = "{0}.png".format(name)
    plt.savefig(fig, bbox_inches='tight')

if __name__ == '__main__':
    plot()


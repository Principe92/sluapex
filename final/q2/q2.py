import matplotlib.pyplot as plt
import numpy as np
from datetime import datetime
import scipy.stats as st

def speed_up(times, base):

    speedups = []

    for time in times:
        s = base / time
        speedups.append(s)
    
    return speedups

def plot2():

    name = 'final/q2/fig_speedup'

    x = [1, 4, 9, 16]
    y1 = np.around(speed_up([27.6812, 7.41568, 3.61818, 3.27409], 27.6812), 2)
    y2 = np.around(speed_up([302.238, 76.2813, 34.2698, 25.5591], 302.238), 2)

    fig, ax = plt.subplots(figsize=(10, 5))
    plt.rc('font', family='serif')
    plt.rc('xtick', labelsize='small')
    plt.rc('ytick', labelsize='small')

    ax.plot(x, y1, label='n = 1440', marker='o')
    ax.plot(x, y2, label='n = 2880', marker='o')
    plt.ylabel('speedup')
    plt.xlabel('processors')
    plt.title('Speedup vs Number of processors')
    

    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)    

    plt.tight_layout()
    plt.legend(loc="upper center", ncol=2)

    fig = "{0}.png".format(name)
    plt.savefig(fig, bbox_inches='tight')

def plot():

    name = 'final/q2/fig_cpu'

    x = [1, 4, 9, 16]
    y1 = np.around([27.6812, 7.41568, 3.61818, 3.27409], 2)
    y2 = np.around([302.238, 76.2813, 34.2698, 25.5591], 2)

    fig, ax = plt.subplots(figsize=(10, 5))
    plt.rc('font', family='serif')
    plt.rc('xtick', labelsize='small')
    plt.rc('ytick', labelsize='small')

    ax.plot(x, y1, label='n = 1440', marker='o')
    ax.plot(x, y2, label='n = 2880', marker='o')
    plt.ylabel('cpu time (s)')
    plt.xlabel('processors')
    plt.title('CPU Time vs Number of processors')
    

    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)    

    plt.tight_layout()
    plt.legend(loc="upper center", ncol=2)

    fig = "{0}.png".format(name)
    plt.savefig(fig, bbox_inches='tight')

if __name__ == '__main__':
    plot()
    plot2()


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

    name = 'week6_hw1/hmw_6_speedup'

    x = [1, 2, 4, 8, 16, 32]
    y1 = np.around(speed_up([1.06585, 0.664834, 0.333293, 0.167226, 0.0838998, 0.106871], 1.06585), 2)
    y2 = np.around(speed_up([5.8479, 3.38721, 1.93796, 1.14583, 0.811821, 0.579867], 5.8479), 2)

    fig, ax = plt.subplots(figsize=(10, 5))
    plt.rc('font', family='serif')
    plt.rc('xtick', labelsize='small')
    plt.rc('ytick', labelsize='small')

    ax.plot(x, y1, label='n=10,000,000', marker='o')
    ax.plot(x, y2, label='n=100,000,000', marker='o')
    plt.ylabel('speedup')
    plt.xlabel('nproc (log-scale)')
    plt.xscale('log')
    

    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)    

    plt.tight_layout()
    plt.legend(loc="upper center", ncol=3)

    fig = "{0}.png".format(name)
    plt.savefig(fig, bbox_inches='tight')

def plot():

    name = 'week6_hw1/hmw_6'

    x = [1, 2, 4, 8, 16, 32]
    y1 = np.around([1.06585, 0.664834, 0.333293, 0.167226, 0.0838998, 0.106871], 2)
    y2 = np.around([5.8479, 3.38721, 1.93796, 1.14583, 0.811821, 0.579867], 2)

    fig, ax = plt.subplots(figsize=(10, 5))
    plt.rc('font', family='serif')
    plt.rc('xtick', labelsize='small')
    plt.rc('ytick', labelsize='small')

    ax.plot(x, y1, label='n=10,000,000', marker='o')
    ax.plot(x, y2, label='n=100,000,000', marker='o')
    plt.ylabel('wall-clock')
    plt.xlabel('nproc (log-scale)')
    plt.xscale('log')
    

    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)    

    plt.tight_layout()
    plt.legend(loc="upper center", ncol=3)

    fig = "{0}.png".format(name)
    plt.savefig(fig, bbox_inches='tight')

if __name__ == '__main__':
    plot()
    plot2()


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

    name = 'midterm/q2/extra/calc_pi_extra'

    x = [1, 2, 4, 8, 16, 32]
    y1 = np.around([74.0415, 40.6471, 26.3364, 16.5192, 10.7275, 6.27667], 2)

    fig, ax = plt.subplots(figsize=(10, 5))
    plt.rc('font', family='serif')
    plt.rc('xtick', labelsize='small')
    plt.rc('ytick', labelsize='small')

    ax.bar(x, y1)
    plt.ylabel('elapsed time (seconds)')
    plt.xlabel('processors')
    

    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)    

    plt.tight_layout()

    fig = "{0}.png".format(name)
    plt.savefig(fig, bbox_inches='tight')

def plot():

    name = 'midterm/q2/calc_pi'

    x = [1, 2, 4, 8, 16, 32]
    y1 = np.around([73.95, 39.185, 20.3912, 11.2147, 7.58456, 5.06471], 2)

    fig, ax = plt.subplots(figsize=(10, 5))
    plt.rc('font', family='serif')
    plt.rc('xtick', labelsize='small')
    plt.rc('ytick', labelsize='small')

    ax.bar(x, y1)
    plt.ylabel('elapsed time (seconds)')
    plt.xlabel('processors')
    

    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)    

    plt.tight_layout()

    fig = "{0}.png".format(name)
    plt.savefig(fig, bbox_inches='tight')

if __name__ == '__main__':
    plot()
    plot2()


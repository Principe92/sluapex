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

def plot3():

    name = 'midterm/square_matrix_3'

    x = [1, 2, 4, 8, 16]
    y1 = np.around(np.divide(speed_up([16.7853, 8.0364, 4.01147, 2.23795, 1.64892], 16.7853),20), 2)
    y2 = np.around(np.divide(speed_up([15.242, 7.80606, 4.3763, 2.30655, 1.46736], 15.242),20), 2)
    y3 = np.around(np.divide(speed_up([15.7491, 7.80587, 4.6183, 2.38072, 1.41545], 15.7491),20), 2)
    y4 = np.around(np.divide(speed_up([15.3132, 8.12131, 4.12227, 2.37072, 1.68193], 15.3132),20), 2)

    fig, ax = plt.subplots(figsize=(10, 5))
    plt.rc('font', family='serif')
    plt.rc('xtick', labelsize='small')
    plt.rc('ytick', labelsize='small')

    ax.plot(x, y1, label='static', marker='o')
    ax.plot(x, y2, label='static,10', marker='o')
    ax.plot(x, y3, label='dynamic', marker='o')
    ax.plot(x, y4, label='dynamic,10', marker='o')
    plt.ylabel('efficiency')
    plt.xlabel('threads')
    

    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)    

    plt.tight_layout()
    plt.legend(loc="upper center", ncol=4)

    fig = "{0}.png".format(name)
    plt.savefig(fig, bbox_inches='tight')

def plot2():

    name = 'midterm/square_matrix_2'

    x = [1, 2, 4, 8, 16]
    y1 = np.around(speed_up([16.7853, 8.0364, 4.01147, 2.23795, 1.64892], 16.7853), 2)
    y2 = np.around(speed_up([15.242, 7.80606, 4.3763, 2.30655, 1.46736], 15.242), 2)
    y3 = np.around(speed_up([15.7491, 7.80587, 4.6183, 2.38072, 1.41545], 15.7491), 2)
    y4 = np.around(speed_up([15.3132, 8.12131, 4.12227, 2.37072, 1.68193], 15.3132), 2)

    fig, ax = plt.subplots(figsize=(10, 5))
    plt.rc('font', family='serif')
    plt.rc('xtick', labelsize='small')
    plt.rc('ytick', labelsize='small')

    ax.plot(x, y1, label='static', marker='o')
    ax.plot(x, y2, label='static,10', marker='o')
    ax.plot(x, y3, label='dynamic', marker='o')
    ax.plot(x, y4, label='dynamic,10', marker='o')
    plt.ylabel('speedup')
    plt.xlabel('threads')
    

    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)    

    plt.tight_layout()
    plt.legend(loc="upper center", ncol=4)

    fig = "{0}.png".format(name)
    plt.savefig(fig, bbox_inches='tight')

def plot():

    name = 'midterm/square_matrix_1'

    x = [1, 2, 4, 8, 16]
    y1 = np.around([16.7853, 8.0364, 4.01147, 2.23795, 1.64892], 2)
    y2 = np.around([15.242, 7.80606, 4.3763, 2.30655, 1.46736], 2)
    y3 = np.around([15.7491, 7.80587, 4.6183, 2.38072, 1.41545], 2)
    y4 = np.around([15.3132, 8.12131, 4.12227, 2.37072, 1.68193], 2)

    fig, ax = plt.subplots(figsize=(10, 5))
    plt.rc('font', family='serif')
    plt.rc('xtick', labelsize='small')
    plt.rc('ytick', labelsize='small')

    ax.plot(x, y1, label='static', marker='o')
    ax.plot(x, y2, label='static,10', marker='o')
    ax.plot(x, y3, label='dynamic', marker='o')
    ax.plot(x, y4, label='dynamic,10', marker='o')
    plt.ylabel('wall-clock (seconds)')
    plt.xlabel('threads')
    

    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)    

    plt.tight_layout()
    plt.legend(loc="upper center", ncol=4)

    fig = "{0}.png".format(name)
    plt.savefig(fig, bbox_inches='tight')

if __name__ == '__main__':
    plot()
    plot2()
    plot3()


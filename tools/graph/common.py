import matplotlib.pyplot as plt
import matplotlib
import math
import errno    
import os

dashes = ["-", "--", "-.", ":"]
#colors2 = ["r", "b+", "gx", "bv"]
colors = ["#d92a3b", "#fcfb5f", "#23bb4e", "#1136a2"]
def init_plotting(fig_width = 8, fig_height=8, font=14):
    #golden_mean = (math.sqrt(5)-1.0)/2.0    # Aesthetic ratio
    #fig_height = fig_width*0.4#golden_mean # height in inches

    plt.rcParams['figure.figsize'] =[fig_width,fig_height]
    plt.rcParams['font.size'] = font
    plt.rcParams['font.family'] = 'Times New Roman'
    plt.rcParams['axes.labelsize'] = plt.rcParams['font.size']
    plt.rcParams['axes.titlesize'] = 1.5*plt.rcParams['font.size']
    plt.rcParams['legend.fontsize'] = plt.rcParams['font.size']
    plt.rcParams['xtick.labelsize'] = plt.rcParams['font.size']
    plt.rcParams['ytick.labelsize'] = plt.rcParams['font.size']
#    plt.rcParams['xtick.major.size'] = 3
#    plt.rcParams['xtick.minor.size'] = 3
#    plt.rcParams['xtick.major.width'] = 1
#    plt.rcParams['xtick.minor.width'] = 1
#    plt.rcParams['ytick.major.size'] = 3
#    plt.rcParams['ytick.minor.size'] = 3
#    plt.rcParams['ytick.major.width'] = 1
#    plt.rcParams['ytick.minor.width'] = 1
    plt.rcParams['legend.frameon'] = False
    plt.rcParams['legend.loc'] = 'upper center'
    plt.rcParams['axes.linewidth'] = 1
    plt.legend(loc='best', fancybox=True)

#    plt.gca().spines['right'].set_color('none')
#    plt.gca().spines['top'].set_color('none')
    plt.gca().xaxis.set_ticks_position('bottom')
    plt.gca().yaxis.set_ticks_position('left')

def mkdir_p(path):
    try:
        os.makedirs(path)
    except OSError as exc:  # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else:
            raise
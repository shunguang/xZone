import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import numpy as np
from scipy import stats
import seaborn as sns

# Plot points (aka markers in mpl) on a coordinate plane and determine best fit

fig, ax = plt.subplots()

# https://matplotlib.org/stable/tutorials/introductory/quick_start.html#parts-of-a-figure

def addLegend(data_filepath: str, transport: str, color: str):
    df = pd.read_csv(data_filepath, engine="pyarrow")
    freqs = pd.unique(df["frequency"])

    ax.set_title(f'Publisher / Subscriber benchmark image ({df["image_height"][0]} x {df["image_width"][0]}) mean values')
    ax.set_xlabel('Frequency (Hz)')
    ax.set_ylabel('Latency (ns)') # nanoseconds, a billionth of a second

    y = [df.loc[df["frequency"] == freq]["latency"].mean() for freq in freqs]
    plt.scatter(freqs, y, label = transport)
    err = [df.loc[df["frequency"] == freq]["latency"].std() for freq in freqs]
    # fmt='none' to prevent the lines from connecting
    ax.errorbar(freqs, y, xerr=None, yerr=err, ls='none')

addLegend("data/sr-imx6/480_360/TCP.csv", "TCP", "tab:purple")
addLegend("data/sr-imx6/480_360/UDP.csv", "UDP", "tab:green")
addLegend("data/sr-imx6/480_360/SHARED_MEMORY.csv", "Shared Memory", 'tab:blue')
ax.legend()

#                         height width
fig.savefig('pubsub_image.png')

print("generated the graph")
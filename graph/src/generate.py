import sys
import re
from glob import glob
import pandas as pd
import matplotlib.pyplot as plt

if len(sys.argv) < 2: # argv[1]
    print("Please provide the machine name as an argument (folder name under data/)")
    exit()
if len(sys.argv) < 3: # argv[2]
    print("Please provide the image height as an argument")
    exit()
if len(sys.argv) < 4: # argv[3]
    print("Please provide the image width as an argument")
    exit()

machine_name = sys.argv[1]
image_height = sys.argv[2]
image_width = sys.argv[3]
time = sys.argv[4]
folder = f"data/{machine_name}/{time}"

fig, ax = plt.subplots()
ax.set_title(f'Publisher / Subscriber benchmark image ({image_height} x {image_width}) mean values')
ax.set_xlabel('Frequency (Hz)')
ax.set_ylabel('Latency (ms)')

# https://matplotlib.org/stable/tutorials/introductory/quick_start.html#parts-of-a-figure
def addLegend(pattern: str, transport: str, color: str):
    filenames = glob(pattern)
    x: list[int] = []
    y: list[float] = []
    err: list[float] = []
    for file in filenames:
        [time, freq, height, width] = re.findall("\\d+", file)
        df = pd.read_csv(file, engine="pyarrow")
        x.append(freq)
        y.append(df["latency"].mean())
        err.append(df["latency"].std())
    
    # fmt='none' to prevent the lines from connecting
    ax.errorbar(x, y, yerr=err, fmt='o', label=transport)

addLegend(f"{folder}/*TCP*.csv", "TCP", "tab:purple")
# addLegend(f"{folder}/UDP.csv", "UDP", "tab:green")
# addLegend(f"{folder}/SHARED_MEMORY.csv", "Shared Memory", 'tab:blue')
ax.legend()

#                         height width
fig.savefig(f'{machine_name}_{image_height}_{image_width}.png')
txt = "The x values of the shared memory tranports are shifted to the right by 5 Hz to prevent overlap.\nThe x value of the TCP transport is shifted to the left by 5 Hz to prevent overlap."
fig.text(0.5, 0.05, txt, ha='center')

print("generated the graph")
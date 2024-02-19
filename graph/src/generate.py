import sys
import re
from glob import glob
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

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
folder = f"data/{machine_name}/{image_height}_{image_width}"

fig, (latency, packet_loss) = plt.subplots(2)
st = fig.suptitle(f'Publisher / Subscriber benchmark image ({image_height} x {image_width})', fontsize="x-large")

latency.set_title('latency values')
latency.set_xlabel('Frequency (Hz)')
latency.set_ylabel('Latency (ms)')
latency.xaxis.set_minor_locator(matplotlib.ticker.AutoMinorLocator())
latency.xaxis.set_major_locator(plt.MaxNLocator())
latency.yaxis.set_minor_locator(matplotlib.ticker.AutoMinorLocator())
# latency.yaxis.set_major_locator(plt.MaxNLocator())

packet_loss.set_title('packet loss')
packet_loss.set_xlabel('Frequency')
packet_loss.set_ylabel('Amount')
packet_loss.xaxis.set_minor_locator(matplotlib.ticker.AutoMinorLocator())
packet_loss.xaxis.set_major_locator(plt.MaxNLocator())
packet_loss.yaxis.set_minor_locator(matplotlib.ticker.AutoMinorLocator())
# packet_loss.yaxis.set_major_locator(plt.MaxNLocator())

# https://matplotlib.org/stable/tutorials/introductory/quick_start.html#parts-of-a-figure
def addLegend(pattern: str, transport: str, color: str):
    filepath = glob(pattern)
    filepath.sort(key=lambda x: int(re.findall("\\d+", re.split(r"\/|\\", x)[-1])[0]))
    frequencies: list[int] = []
    latencies: list[float] = []
    packetLoss: list[int] = []
    err: list[float] = []
    for file in filepath:
        [freq, height, width] = re.findall("\\d+", re.split(r"\/|\\", file)[-1])
        df = pd.read_csv(file, engine="pyarrow")
        # filter out values that are 3 standard deviations away from the mean
        df = df[np.abs(df["latency"]-df["latency"].mean()) <= (3*df["latency"].std())]

        # match transport:
        #     case "Shared Memory":
        #         freq = int(freq) + 5
        #     case "TCP":
        #         freq = int(freq) - 5
        #     case "UDP":
        #         freq = int(freq)

        frequencies.append(freq)
        convertMicroSecondstoMiliseconds = lambda x: x / 1000
        latencies.append(convertMicroSecondstoMiliseconds(df["latency"]).mean())

        # https://stackoverflow.com/a/69731291
        # Calculating packet loss
        condition = df["frame number"].eq(df["frame number"].shift()+1)
        elseConditionReturnValue = df["frame number"]-df["frame number"].shift()
        arr = np.where(condition, 'True' , elseConditionReturnValue)
        packetLoss.append(sum(map(lambda n: int(float(n)), arr[arr != "True"][1:])))
        
        err.append(convertMicroSecondstoMiliseconds(df["latency"]).std())
    
    latency.errorbar(frequencies, latencies, yerr=err, fmt="o", color=color, label=transport, alpha=0.5)
    packet_loss.scatter(frequencies, packetLoss, color=color, label=transport, alpha=0.5)

addLegend(f"{folder}/*/*TCP*.csv", "TCP", "tab:purple")
addLegend(f"{folder}/*/*UDP*.csv", "UDP", "tab:green")
addLegend(f"{folder}/*/*SharedMemory*.csv", "Shared Memory", "tab:blue")

latency.legend()
packet_loss.legend()

txt = "The x values of the shared memory tranports are shifted to the right by 5 Hz to prevent overlap.\nThe x value of the TCP transport is shifted to the left by 5 Hz to prevent overlap."
fig.text(0.5, 0.02, txt, ha='center', wrap=True)

# change the second number to adjust the text. The greater the number, the lower it is positioned
fig.tight_layout(rect=(0,0.12,1,1))
st.set_y(0.95)
fig.subplots_adjust(top=0.85)

#                         height width
fig.savefig(f'{machine_name}_{image_height}_{image_width}.png', dpi=300)
print("generated the graph")
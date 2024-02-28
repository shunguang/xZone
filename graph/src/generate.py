import sys
import re
from glob import glob
import pandas as pd
import matplotlib
import matplotlib.ticker
import matplotlib.pyplot as plt
# import matplotlib.pyplot
# from matplotlib import pyplot as plt
import numpy as np

if len(sys.argv) < 2:  # argv[1]
    print("Please provide the machine name as an argument (folder name under data/)")
    exit()
if len(sys.argv) < 3:  # argv[2]
    print("Please provide the image height as an argument")
    exit()
if len(sys.argv) < 4:  # argv[3]
    print("Please provide the image width as an argument")
    exit()
machine_name = sys.argv[1]
image_height = sys.argv[2]
image_width = sys.argv[3]
folder = f"data/{machine_name}/{image_height}_{image_width}"

fig, (latency, message_loss) = plt.subplots(2)
st = fig.suptitle(
    f"Publisher / Subscriber benchmark image ({image_height} x {image_width})",
    fontsize="x-large",
)

latency.set_title("latency values")
latency.set_xlabel("Frequency (Hz)")
latency.set_ylabel("Latency (ms)")
latency.xaxis.set_minor_locator(matplotlib.ticker.AutoMinorLocator())
latency.xaxis.set_major_locator(plt.MaxNLocator())
latency.yaxis.set_minor_locator(matplotlib.ticker.AutoMinorLocator())
# latency.yaxis.set_major_locator(plt.MaxNLocator())


message_loss.set_title("message loss")
message_loss.set_xlabel("Frequency")
message_loss.set_ylabel("Amount")
message_loss.xaxis.set_minor_locator(matplotlib.ticker.AutoMinorLocator())
message_loss.xaxis.set_major_locator(plt.MaxNLocator())
message_loss.yaxis.set_minor_locator(matplotlib.ticker.AutoMinorLocator())
# packet_loss.yaxis.set_major_locator(plt.MaxNLocator())


def convert_microseconds_to_miliseconds(num):
    return num / 1000


# https://matplotlib.org/stable/tutorials/introductory/quick_start.html#parts-of-a-figure
def add_legend(pattern: str, transport: str, color: str):
    file_path = glob(pattern)
    file_path.sort(key=lambda x: int(re.findall("\\d+", re.split(r"\/|\\", x)[-1])[0]))
    frequencies: list[int] = []
    latencies: list[float] = []
    lost_messages: list[int] = []
    err: list[float] = []
    for file in file_path:
        [freq, height, width] = re.findall("\\d+", re.split(r"\/|\\", file)[-1])
        df = pd.read_csv(file, engine="pyarrow")

        frequencies.append(freq)
        latencies.append(convert_microseconds_to_miliseconds(df["latency"]).mean())

        # https://stackoverflow.com/a/69731291
        # Calculating packet loss

        condition = df["frame number"].eq(df["frame number"].shift() + 1)
        else_condition = (
            df["frame number"] - df["frame number"].shift()
        )  # find difference
        arr = np.where(condition, "True", else_condition)

        lost_messages.append(
            sum(map(lambda n: int(float(n) - 1), arr[arr != "True"][1:]))
        )
        err.append(convert_microseconds_to_miliseconds(df["latency"]).std())
    latency.errorbar(
        frequencies,
        latencies,
        yerr=err,
        fmt="o",
        color=color,
        label=transport,
        alpha=0.5,
    )
    message_loss.scatter(
        frequencies, lost_messages, color=color, label=transport, alpha=0.5
    )


add_legend(f"{folder}/*/*TCP*.csv", "TCP", "tab:purple")
add_legend(f"{folder}/*/*UDP*.csv", "UDP", "tab:green")
add_legend(f"{folder}/*/*SharedMemory*.csv", "Shared Memory", "tab:blue")

latency.legend()
message_loss.legend()

TEXT = """The x values of the shared memory tranports are shifted to the right by 5 Hz to prevent overlap.
          The x value of the TCP transport is shifted to the left by 5 Hz to prevent overlap."""
fig.text(0.5, 0.02, TEXT, ha="center", wrap=True)

# change the second number to adjust the text. The greater the number, the lower it is positioned

fig.tight_layout(rect=(0, 0.12, 1, 1))
st.set_y(0.95)
fig.subplots_adjust(top=0.85)

#                         height width

fig.savefig(f"{machine_name}_{image_height}_{image_width}.png", dpi=300)
print("generated the graph")

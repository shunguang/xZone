

without waiting, it took around 16000 microsecond to receive an image on a windows OS. too slow to archive . ASYNCHRONOUS_PUBLISH_MODE seems not working.

need to move to micron OS

  flow_control_300k_per_sec->max_bytes_per_period = 300 * 1000;
    flow_control_300k_per_sec->period_ms = 1000;
	
300 Hz is the limit on Windows. the program cannot send faster than 300 images per second due to publish (write, ) cannot be ASYNCHRONOUS_PUBLISH_MODE.


HZ < 100, 200 sample's the latency range is between 8000 and 40,000 microsecond, in a wide range
HZ > 125, 200 sample's the latency range is between 8000 and 15,000 microsecond

according these data, it appears sending data slower, and latency is more higher. Why?

it took 1000000/3000 = 3,000 microsecond to prepare images. We may can prepare images and put them in a list, and then publish.

tried to put image to a list, but it seems just a little better (quicker). loop the list seems expensive too.


***updates
Normal rate, 30 pocket  /sec

https://fast-dds.docs.eprosima.com/en/latest/fastdds/transport/transport_api.html

https://fast-dds.docs.eprosima.com/en/v2.0.0/fastdds/transport/transport.html


WHY on_data_available is not triggered
https://github.com/eclipse-cyclonedds/cyclonedds/issues/1084


https://fast-dds.docs.eprosima.com/en/latest/fastdds/api_reference/dds_pim/subscriber/datareaderlistener.html#_CPPv4N8eprosima7fastdds3dds18DataReaderListener17on_data_availableEP10DataReader


https://blog.sflow.com/2022/02/udp-vs-tcp-for-real-time-streaming.html

https://www.researchgate.net/figure/Typical-variation-in-TCP-latency-upper-line-and-UDP-latency-lower-line-near-zero-in_fig2_228637890

https://fast-dds.docs.eprosima.com/en/latest/fastdds/discovery/discovery_server.html

https://github.com/eProsima/Fast-DDS/tree/master/examples/cpp/dds/CustomListenerExample


how to access embed
Tabby terminal 
open new tab, connect to debian

/home/debian/xZone/src/makeFiles
run_all_w_cleanAll.sh

To run
cd me/debian/xZone/build/bin
./test.out config.xml
./ImagePun.out config.xml

windows
C:\Users\conno\Documents\xZone\build-vs2019-x64\bin\Release\logs

C:\Users\conno\Documents\xZone\src\vs2019\open_xZone_vs2019_cwu.bat

to pull commits from a different repository without a making a pull request
```
 git pull https://github.com/ziloka/xZone.git dev:dev
```
[Source](https://stackoverflow.com/questions/24815952/git-pull-from-another-repository)

if you want to build an example from the Fast-DDS library 
- install openssl


To comment code you must perform the following shortcuts in succession 
ctrl + k, ctrl + c

to uncomment code you must do these in succession
ctrl + k, ctrl + u

you can look at these shortcuts by going to Edit -> Advanced -> (Comment / Uncomment) Selection

### clone sharedmem and tcp examples, as well as defualt helloworldexample

```
git clone --depth=1 --no-checkout https://github.com/eProsima/Fast-DDS
cd Fast-DDS
git sparse-checkout set examples/cpp/dds
git checkout
```

### run the following commands in the example folder that you want to run
```
mkdir build
cd build
cmake -DOPENSSL_INCLUDE_DIR="C:\Program Files\OpenSSL-Win64\include" ..
cmake --build .
```


### Recursively delete directory on windows in powershell
```
rm -r -fo dir_name
```

if the image size is larger than Maximum transmission unit, it will take longer to send

Determining system maxmium mtu on windows (command prompt)
```
netsh interface ipv4 show subinterface
```

Determining system maxmium mtu on linux
```
ifconfig | grep -i MTU
```

- shared memory will only be faster than udp when there is a lot of data (mbs, gbs)
- udp can be faster with zero-copy networking

These images assume each pixel is 3 bytes (w x h x 3)

formula to get mb
(w * h * 3)/1e6

(first number is WxH)
- 10 x 20 is 600 bytes or 0.0006 mb
- 256 x 144 is 110,592 bytes or 0.110592 mb
- 426 x 240 is 307,720 bytes or 0.30672 mb
- 480 x 360 is 518,400 bytes or 0.5184 mb
- 640 x 480 is 921,600 bytes or 0.9216 mb
- 720 x 480 is 1,036,800 bytes or 1.03 mb
- 1280 x 720 is 2,764,800 bytes or 2.7648 mb
- 1920 x 1080 is 6,220,800 bytes or 6.22 mb
- 4096 x 2160 is 26,542,080 bytes or 26.5 mb
- 7680 x 4320 is 99,532,800 bytes or 99.5 mb
- 15360 × 8640 is 398,131,200 bytes or 398 mb

Quick build
- If only modified header, delete the library or executable that includes the header

# count lines in file
cat image_pubsub_dataTCP_360_480_20240114193936.csv | wc -l

use macrosecond

make python script to determine lost frames

make program run each frequencies independently, writing a file for each frequency
each file generates one dot on the graph

for freq

subscriber must be aware of when to close the file (must be aware of handling multiple messages)
- when last message send frame_number 0xfffff max number

send out a fixed size, for tcp
tcp there are 10 files for 10 frequencies
change udp same with 10 frequencies

10 files for 10 
shared memory etc

tcp there are 10 files for 10 frequencies

change udp same with 10 freicneis

10 files for 10 
shared memory etc

## reliability plays a big role
```
# very slow ~2 seconds
DataReaderQos rqos;
rqos.reliability().kind = eprosima::fastdds::dds::RELIABLE_RELIABILITY_QOS;

DataWriterQos wqos = DATAWRITER_QOS_DEFAULT;
wqos.reliability().kind = RELIABLE_RELIABILITY_QOS;
```

```
# very fast ~2 miliseconds
DataReaderQos rqos;
rqos.reliability().kind = eprosima::fastdds::dds::BEST_EFFORT_RELIABILITY_QOS;

DataWriterQos wqos = DATAWRITER_QOS_DEFAULT;
wqos.reliability().kind = BEST_EFFORT_RELIABILITY_QOS;
```


1/28/2024
***high priority***
run jetson tx2
run on cubox as well

todo: use miliseconds for latency

2. measure lost messages

3. still reorganize file
- each image and frequency in a single file, python script will plot a single point for each file

- look at relationship between small, medium and huge image sizes
- three controls, frqeuency and image size, and transport protocol

low priority
write (bash) script to automate pipeline

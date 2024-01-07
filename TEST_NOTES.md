

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


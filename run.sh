# collect data
for transport in 1 2 3
do
    XZONE_TRANSPORT=$transport
    ./test.exe config.xml & 
    ./imagePub.exe config.xml &
    
    wait
done
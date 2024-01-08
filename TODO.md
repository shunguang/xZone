notes:
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

example graph -->

https://www.mathworks.com/matlabcentral/answers/10428-standard-deviation-and-mean

magnitude with error bar
plot error bar 

plot the types on type of each other

https://www.biologyforlife.com/interpreting-error-bars.html
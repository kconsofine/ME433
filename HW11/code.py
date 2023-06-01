from ulab import numpy as np
import time
freq1 = 470
freq2 = 450
freq3 = 440
array = np.zeros(1024)
mag = np.zeros(1024)
for i in range(1024):
    t = i*2*3.14/1023
    new = np.sin(t*freq1) + np.sin(t*freq2) + np.sin(t*freq3)
    array[i] = new
r,im = np.fft.fft(array)
for i in range(len(r)/2):
    square = ((r[i])**2 + (im[i])**2)
    mag[i] = np.sqrt(square)
    print((mag[i],))
    time.sleep(0.01)





import matplotlib.pyplot as plt
import numpy as np
import csv

t = [] # column 0
data1 = [] # column 1
dataAvg = [] # column 2

with open('sigA.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(row[0])) # leftmost column
        data1.append(float(row[1])) # second column
        #data2.append(float(row[2])) # third column

#average using X data points
# X = 5
# avg = 0
# for i in range(len(data1)):
#     if (i > X+1):

#         for j in range(X):
#             avg += data1[i-j]
#         dataAvg.append(avg/X)

#         avg = 0
#     else:
#         dataAvg.append(0)
# Prev = data1[0]
# B = 0.99
# A = 0.01
# for i in range(len(data1)):
#     dataAvg.append(B*Prev + A*data1[i])
#     Prev = B*Prev + A*data1[i]


h = [
    0.000000000000000000,
    0.000018998962235043,
    0.000122067974007008,
    0.000342382071281436,
    0.000628765874635697,
    0.000809860891663529,
    0.000593298533998382,
    -0.000370543089677334,
    -0.002344915247939962,
    -0.005301705971039372,
    -0.008716172456440463,
    -0.011453870577825941,
    -0.011841568916304737,
    -0.007970432716844162,
    0.001799259246326488,
    0.018251334297783927,
    0.040826904099676480,
    0.067424473445672872,
    0.094608958121255804,
    0.118231368987389562,
    0.134324283144244855,
    0.140034506651801810,
    0.134324283144244883,
    0.118231368987389618,
    0.094608958121255832,
    0.067424473445672858,
    0.040826904099676473,
    0.018251334297783930,
    0.001799259246326488,
    -0.007970432716844160,
    -0.011841568916304744,
    -0.011453870577825950,
    -0.008716172456440463,
    -0.005301705971039374,
    -0.002344915247939960,
    -0.000370543089677335,
    0.000593298533998383,
    0.000809860891663528,
    0.000628765874635699,
    0.000342382071281437,
    0.000122067974007008,
    0.000018998962235043,
    0.000000000000000000,
]
avg = 0
for i in range(len(data1)):
    if (i > 27):
        for j in range(len(h)):
            avg += h[j]*data1[i-j]
        dataAvg.append(avg)
        avg = 0
    else:
        dataAvg.append(0)



dt = t[-1]/len(t)
# a constant plus 100Hz and 1000Hz

Fs = 1/dt # sample rate
Ts = dt # sampling interval
y = data1 # the data to make the fft from
yAvg = dataAvg
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range
Y = np.fft.fft(y)/n # fft computing and normalization
YAvg = np.fft.fft(yAvg)/n
Y = Y[range(int(n/2))]
YAvg = YAvg[range(int(n/2))]

fig, (ax1, ax2) = plt.subplots(2, 1)

plt.title('Low pass, 43 coeffs, bandwidth 220 Hz, cutoff 140Hz')
ax1.plot(t,y,'k')
ax1.plot(t,yAvg,'r')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'k') # plotting the fft
ax2.loglog(frq,abs(YAvg),'r')
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.show()
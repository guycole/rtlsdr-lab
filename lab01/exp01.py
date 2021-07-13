import numpy as np

from pylab import *
from rtlsdr import *

sdr = RtlSdr()

# configure device
sdr.sample_rate = 2.4e6
sdr.center_freq = 95e6
sdr.center_freq = 94.7e6
#sdr.center_freq = 88.5e6
sdr.gain = 4

print(sdr)

samples = sdr.read_samples(256*1024)
sdr.close()

avg_pwr = np.mean(np.abs(samples)**2)
print(avg_pwr)
print(np.var(samples))

# use matplotlib to estimate and plot the PSD
#psd(samples, NFFT=1024, Fs=sdr.sample_rate/1e6, Fc=sdr.center_freq/1e6)
#xlabel('Frequency (MHz)')
#ylabel('Relative power (dB)')

#show()

PSD = (np.abs(np.fft.fft(samples))/(256*1024))**2
PSD_log = 10.0*np.log10(PSD)
PSD_shifted = np.fft.fftshift(PSD_log)

x = samples * np.hamming(len(samples)) 

f = np.linspace(sdr.center_freq - sdr.sample_rate/2.0, sdr.center_freq + sdr.sample_rate/2.0, len(samples))
plt.plot(f, PSD_shifted)
plt.show()

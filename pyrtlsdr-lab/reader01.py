import numpy as np
#import matplotlib.pyplot as plt

import matplotlib
#matplotlib.use('TkAgg') # Or 'QtAgg'
matplotlib.use('QtAgg') # Or 'QtAgg'
import matplotlib.pyplot as plt


# Example: Reading int16 interleaved I/Q samples
try:
    samples = np.fromfile('2549d83c-8dba-4a51-bdb6-8b4ca7a81cd6.iq', np.int16)
    samples = samples.astype(np.float32)
    samples = samples / 32768 # Convert to range of -1 to +1
    samples = samples[::2] + 1j * samples[1::2]
    print("Successfully read IQ data as interleaved int16.")

except Exception as e:
    print(f"Error reading interleaved int16 IQ file: {e}")

try:
    # Example: Reading complex64 samples
    #samples = np.fromfile('wz2504-2025-05-12.iq', np.complex64)
    samples = np.fromfile('kqed-2025-05-12.iq', np.complex64)
    print("Successfully read IQ data as complex64.")
except Exception as e:
    print(f"Error reading complex62 IQ file: {e}")

# Example: Plotting (optional)
if 'samples' in locals() and samples is not None:
    plt.plot(np.real(samples), np.imag(samples), '.')
    plt.xlabel('I (Real)')
#    pltade.ylabel('Q (Imag)')
    plt.title('Constellation Diagram')
    plt.grid(True)
    plt.show()


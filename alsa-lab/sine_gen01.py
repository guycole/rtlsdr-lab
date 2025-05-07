#
# Title: sine_gen.py
# Description: generate monotone audio signal for aplay(1)
#
# Creates files for gnuplot(1) and aplay(1).
# aplay /tmp/sin-gen.alsa -f S16_LE -r 44100
#
import math
import struct

class SineGen:
    bits_16 = 2**15-1
    results = []

    def __init__(self, duration:int, sample_freq:int, signal_freq:int):
        self.sample_freq = sample_freq
        self.signal_freq = signal_freq

        self.sample_population = duration * sample_freq + 1

    def generate(self) -> None:
        omega = 2.0 * math.pi * self.signal_freq

        time_ticks = [ndx/self.sample_freq for ndx in range(self.sample_population)]

        for sample_ndx in range(len(time_ticks)):
            sample = 0.5 * math.sin(omega * sample_ndx / self.sample_freq)
            yy_value = int(self.bits_16 * (0.5 + sample))

            self.results.append((time_ticks[sample_ndx], yy_value))

    def binary_write(self, file_name: str) -> None:
        audio_data = b''
        for row in self.results:
            audio_data += struct.pack('<h', row[1])
        
        try:
            with open(file_name, "wb") as out_file:
                out_file.write(audio_data)
        except Exception as error:
            print(error)

    def gnuplot_write(self, file_name: str) -> None:
        try:
            with open(file_name, "w") as out_file:
                for row in self.results:
                    out_file.write(f"{row[0]} {row[1]}\n")
        except Exception as error:
            print(error)

    def execute(self, file_name: str) -> None:
        self.generate()
        self.gnuplot_write(f"/tmp/{file_name}.plt")
        self.binary_write(f"/tmp/{file_name}.alsa")

        return

if __name__ == '__main__':
#    print("main")

    sg = SineGen(2, 8000, 500)
    sg = SineGen(2, 200, 20)
    sg = SineGen(2, 44100, 440)
    sg = SineGen(2, 44100, 2000)
    sg.execute("sin-gen")

# aplay /tmp/sin-gen.alsa -f S16_LE -r 44100

#;;; Local Variables: ***
#;;; mode:python ***
#;;; End: ***

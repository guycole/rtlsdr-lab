#
# Title: rtl_sdr_to_numpy.py
# Description: convert rtl_sdr iq file to numpy complex array
# Development Environment: Ubuntu 22.04.5 LTS/python 3.10.12
# Author: G.S. Cole (guycole at gmail dot com)
#
import numpy as np
import os

class RtlSdrIqConverter:

    def iq_reader(self, file_name: str) -> np.ndarray:
        try:
            return np.fromfile(file_name, dtype=np.uint8)
        except FileNotFoundError:
            print(f"Error: File not found at {file_name}")
        except Exception as exception:
            print(f"An error occurred while reading the file: {exception}")

        return None

    def output_file_name(self, input_file_name: str) -> str:
        base_name = os.path.basename(input_file_name)
        return os.path.splitext(base_name)[0]

    def uint_to_complex(self, raw_iq_samples: np.ndarray) -> np.ndarray:
        if raw_iq_samples is None:
            return None
        
        real_iq_parts = []
        imaginary_iq_parts = []
        for ndx in range(0, len(raw_iq_samples), 2):
            real_part = (raw_iq_samples[ndx] - 127.4) / 127.4
            real_iq_parts.append(real_part)
            imaginary_part = (raw_iq_samples[ndx + 1] - 127.4) / 127.4
            imaginary_iq_parts.append(imaginary_part)

        return np.array(real_iq_parts) + 1j * np.array(imaginary_iq_parts)

    def execute(self, input_file_name: str) -> None:
        print(f"converting: {input_file_name}")

        if os.path.isfile(input_file_name) is False:
            print(f"missing {input_file_name}")
            return

        raw_iq_samples = self.iq_reader(input_file_name)
        complex_iq_samples = self.uint_to_complex(raw_iq_samples)
      
        out_file_name = self.output_file_name(input_file_name)
        np.save(out_file_name, complex_iq_samples)
        print(f"saved: {out_file_name}.npy")

print("start conversion")

if __name__ == "__main__":
    # wz2504
    input_file_name = "/Users/gsc/Documents/braingang-s3sync/mellow-buffalo/sample-v1/noaa_wx/581cae4e-43d4-4347-b741-81f90a6fe95f.iq"

    # kqed
    input_file_name = "/Users/gsc/Documents/braingang-s3sync/mellow-buffalo/sample-v1/broadcast_fm/f58c456f-9056-418a-ab20-b6d01424520a.iq"

    converter = RtlSdrIqConverter()
    converter.execute(input_file_name)

print("stop conversion")

# ;;; Local Variables: ***
# ;;; mode:python ***
# ;;; End: ***
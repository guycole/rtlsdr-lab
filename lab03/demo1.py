#
# Title: demo1.py
# Description: explore NOAA WX sample
# Development Environment: Ubuntu 22.04.5 LTS/python 3.10.12
# Author: G.S. Cole (guycole at gmail dot com)
#
import json
import numpy as np
import matplotlib.pyplot as plt
import os

from jsonschema import validate

schema = {
    "type": "object",
    "properties": {
        "antenna": {"type": "string"},
        "callsign": {"type": "string"},
        "centerFreqHz": {"type": "number"},
        "collectionScript": {"type": "string"},
        "durationSeconds": {"type": "number"},
        "host": {"type": "string"},
        "key": {"type": "string", "format": "uuid"},
        "name": {"type": "string"},
        "note": {"type": "string"},
        "receiver": {"type": "string"},
        "sampleRateHz": {"type": "number"},
        "schemaVersion": {"type": "number"},
        "site": {"type": "string"},
        "timeStampEpoch": {"type": "number"},
        "timeStampIso8601": {"type": "string"}, 
    },
    "required": [
        "antenna",
        "centerFreqHz",
        "durationSeconds",
        "name",
        "note",
        "receiver",
        "sampleRateHz",
        "schemaVersion",
        "site",
        "timeStampEpoch",
    ],
    "additionalProperties": False,
}

class SignalDemo1:
    def json_reader(self, file_name: str) -> dict[str, any]:
        if os.path.isfile(file_name) is False:
            print(f"missing {file_name}")
            return {}

        results = {}

        try:
            with open(file_name, "r") as in_file:
                results = json.load(in_file)
                validate(instance=results, schema=schema)
        except Exception as error:
            print(error)
            return {}

        return results

    def grafer(self, samples):
        plt.figure(figsize=(10, 4))
        plt.plot(samples.real, label='In-Phase (I)', alpha=0.7)
        plt.plot(samples.imag, label='Quadrature (Q)', alpha=0.7)
        plt.title('IQ Samples')
        plt.xlabel('Sample Index')
        plt.ylabel('Amplitude')
        plt.legend()
        plt.grid()
        plt.show()

    def grafer2(self,  samples: np.ndarray, center_freq_hz: int, duration_seconds: int, sample_rate_hz: int):
        print("grafer2")

        iq = samples[0:sample_rate_hz]

        Fs = sample_rate_hz
        N = sample_rate_hz
        x = iq[0:N] 
      
        PSD = np.abs(np.fft.fft(iq))**2 / (N*Fs)
        PSD_log = 10.0*np.log10(PSD)
        PSD_shifted = np.fft.fftshift(PSD_log)

        iq = iq * np.hamming(len(iq))

        f = np.arange(Fs/-2.0, Fs/2.0, Fs/N)
        f += center_freq_hz 
        plt.plot(f, PSD_shifted)
        plt.show()  

        print("plot done")

    def x1(self, samples: np.ndarray, duration_seconds: int, sample_rate_hz: int):
        print("x1")

#        for ndx in range(duration_seconds):
#            start = ndx * sample_rate_hz
#            end = start + sample_rate_hz

#            iq = samples[start:end]
#            avg_pwr = np.var(iq)

#            print(f"{start} to {end}")
#            print(f"segment {ndx}: len={len(iq)} avg pwr={avg_pwr}")

    def execute(self, catalog_file_name:str, data_file_name:str) -> None:
        iq_samples = np.load(data_file_name)
        print(len(iq_samples))
        print(type(iq_samples))

        description = self.json_reader(catalog_file_name)
        print(description)

        self.grafer2(iq_samples, description.get("centerFreqHz", 0), description.get("durationSeconds", 0), description.get("sampleRateHz", 0))

print("start demo1")

if __name__ == "__main__":
    # wz2504
    catalog_file_name = "/Users/gsc/Documents/braingang-s3sync/mellow-buffalo/sample-v1/noaa_wx/581cae4e-43d4-4347-b741-81f90a6fe95f.json"
    data_file_name =    "/Users/gsc/Documents/braingang-s3sync/mellow-buffalo/sample-v1/noaa_wx/581cae4e-43d4-4347-b741-81f90a6fe95f.npy"

    # kqed
    #catalog_file_name = "/Users/gsc/Documents/braingang-s3sync/mellow-buffalo/sample-v1/broadcast_fm/f58c456f-9056-418a-ab20-b6d01424520a.json"
    #data_file_name =    "/Users/gsc/Documents/braingang-s3sync/mellow-buffalo/sample-v1/broadcast_fm/f58c456f-9056-418a-ab20-b6d01424520a.npy"

    demo = SignalDemo1()
    demo.execute(catalog_file_name, data_file_name)

print("stop demo1")

# ;;; Local Variables: ***
# ;;; mode:python ***
# ;;; End: ***
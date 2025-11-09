# Copilot Instructions for rtlsdr-lab

## Project Overview
This is a Software Defined Radio (SDR) experimentation repository using RTL-SDR dongles for radio signal capture and analysis. The project focuses on three main domains:
- **Radio signal processing** (Python with pyrtlsdr, numpy, matplotlib)
- **Real-time audio streaming** (Shell scripts with rtl_fm, aplay)
- **ADS-B aircraft tracking** (C++ decoder for Mode S messages)

## Architecture & Data Flow

### Signal Processing Pipeline
1. **RTL-SDR Hardware** → captures RF signals as I/Q samples
2. **Python Scripts** (`pyrtlsdr-lab/`, `lab01/`) → process samples for analysis/visualization
3. **Shell Scripts** (`scripts/`, `rtlsdr-lab/`) → real-time streaming to audio output
4. **C++ Decoders** (`rtl-adsb-lab/`) → decode digital protocols (ADS-B)

### Key Frequency Bands
- **88.5-94.7 MHz**: FM radio (KQED examples)
- **156-157 MHz**: Marine VHF (tech/marine_vhf.json)
- **1090 MHz**: ADS-B aircraft transponders

## Development Patterns

### Python Signal Processing
- Standard config: `sample_rate = 2.4e6`, `gain = 4` for FM reception
- Always call `sdr.close()` after `read_samples()` to prevent USB issues
- Use `np.fft.fftshift()` for frequency domain visualization
- Apply `np.hamming()` windowing for cleaner spectrum analysis
- Example in `pyrtlsdr-lab/exp01.py` shows complete PSD workflow

### Shell Script Conventions
- Scripts use `#!/bin/bash` shebang and explicit PATH setting
- File naming: `{station}-{action}.sh` (e.g., `kqed-file.sh`, `kfpr-audio.sh`)
- Sample collection: Use `rtl_sdr -f FREQ -s RATE -g 90 -b BLOCKSIZE -n SAMPLES file.iq`
- Audio streaming: `rtl_fm -f FREQ -M wbfm -s 256k - | aplay -t raw -r 28000 -c 1 -f S16_LE`
- UUID-based filenames for data collection avoid conflicts

### Data Collection Workflow
1. Generate UUID and metadata via `catalog.py` 
2. Capture I/Q samples to `{UUID}.iq` files
3. Create JSON metadata with frequency, duration, timestamp
4. Use `reader01.py` to visualize captured data

### C++ ADS-B Processing
- Struct-based message parsing in `decoder.h` (DF, ICAO, type codes)
- Pipeline architecture: stdin → converter → dispatcher → decoder
- Build with: `g++ -o decoder -g -Wall *.cxx`

## Key Files & Dependencies
- `lab01/requirements.txt`: Core Python deps (pyrtlsdr==0.2.93)
- `scripts/catalog.py`: Metadata generation for signal captures
- `tech/`: Reference data (marine frequencies, NOAA stations)
- File formats: `.iq` (I/Q samples), `.json` (metadata), `.sh` (automation)

## Common Tasks
- **New frequency analysis**: Copy `pyrtlsdr-lab/demo2.py`, adjust center_freq
- **Audio monitoring**: Use `rtl_fm` with appropriate modulation (-M wbfm for FM)
- **Batch collection**: Use script template from `scripts/kqed-file.sh`
- **Hardware check**: Run `pyrtlsdr-lab/demo1.py` (throws LibUSBError if no dongle)

## Development Notes
- Matplotlib backend may need adjustment (`matplotlib.use('QtAgg')`)
- Sample rates typically 2.4 MHz for analysis, 256k for audio
- PPM correction (freq_correction) varies by dongle - common value: 60
- All frequency values in Hz (e.g., 88.5e6 for 88.5 MHz)
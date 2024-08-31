import soundfile as sf
import sys

# Read the FLAC file and get the PCM data and sample rate
data, samplerate = sf.read(sys.argv[1], dtype='int16')

# Convert the PCM data to bytes
pcm_data = data.tobytes()

with open('output.pcm', 'wb') as pcm_file:
    pcm_file.write(pcm_data)

# Copyright 2019 Matthew Carlin
#
# Create amplitude data for a 16 bit pcm wav file.

import scipy.io.wavfile
import sys

# Read the file, get the actual data which is in the second column,
# and grab one audio channel. For 16 bit pcm wav files from Audaciy,
# this should be int16 (-32768 to 32768) sampled at 44100 samples per second.

print sys.argv[1]
print scipy.io.wavfile.read(sys.argv[1])[1]
# if stereo, need [:,0]. If mono, do not.
# data = scipy.io.wavfile.read(sys.argv[1])[1]
data = scipy.io.wavfile.read(sys.argv[1])[1][:,0]
length_in_seconds = len(data) / 44100

#sys.exit(1)

maximum_amp = 0
outfile = open(sys.argv[2], "w")

# To get an amplitude line every 0.01 seconds,
# we take 441 samples and average them,
# then normalize them from -32768,32768 to -1,1.

storage = []

for i in range(0, length_in_seconds * 100 - 1):
  start = 441 * i
  end = min(441 * (i+1), len(data) - 1)
  data_frame = data[start:end]
  average_amplitude = sum([abs(v) for v in data_frame]) / (441.0 * 36278.0)
  #print "%0.4f" % average_amplitude
  storage.append(average_amplitude)
  if average_amplitude > maximum_amp:
    maximum_amp = average_amplitude

print maximum_amp

if (maximum_amp < 0.0001):
  print "Failed to find amplitude. Quitting without writing."
  sys.exit(1)

for amplitude in storage:
  amplitude = amplitude / maximum_amp
  outfile.write("%0.4f\n" % amplitude)

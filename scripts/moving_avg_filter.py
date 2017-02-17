import os.path
import math
import sys

with open(str(sys.argv[1])) as data:

    # Create/open file to store filtered data
    if not(os.path.isfile('filtered.dat.txt')):
        output = open('filtered.dat.txt', 'w+')
    else:
        output = open('filtered.dat.txt', 'a')

    count = 0 #for average
    avg = 0.0

    for val in data:
        if count == 4:
            avg = avg/4.0
            # write transmission statistics to end of destination file
            output.write(str(avg)+'\n')
            avg = float(val)
            count = 1
        else:
            avg += float(val)
            count += 1


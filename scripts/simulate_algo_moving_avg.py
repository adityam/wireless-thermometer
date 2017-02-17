import os.path
import math
import sys

# Run simulation of transmission algorithm
# Using collected temperature data saved in source file
# Alpha and K_alpha are algorithm parameters
def simulate (alpha, k_alpha):

    # a is autoregressive coefficient
    a = 0.9999

    # open source data file
    with open(str(sys.argv[1])) as data:
        
        # create new file to export simulation results to
        results = open('sim_alpha_'+str(alpha)+'.txt', 'w+')
        results.write('alpha   = ' + str(alpha) +'\nk_alpha = ' + str(k_alpha) + '\n')
        results.close()

        # Create/open file to store transmission statistics
        if not(os.path.isfile('sim_tx_stats.txt')):
            stats = open('sim_tx_stats.txt', 'w+')
            stats.write('ALPHA,K_ALPHA,TX,TOTAL,RATIO,DIST\n')
        else:
            stats = open('sim_tx_stats.txt', 'a')

        # write simulation results to destination file
        with open('sim_alpha_'+str(alpha)+'.txt', 'a') as results:

            tempPrev = -1 # previous temperature value
            total = 0 # total values read
            tx = 0 # total transmissions
            dist = 0 #distortion (RMSE)

            count = 0 #for average
            avg = 0.0

            # for each data sample from source file
            # simulate: 'transmit' or 'estimate'?
            for val in data:
                if count == 4:
                    avg = avg/4.0
                    temp = avg
                    error = temp - a * tempPrev
                    total += 1
                    # transmit if error is over threshold
                    # 1st data sample is always transmitted
                    if abs(error) > k_alpha or tx == 0:
                        tx += 1
                        results.write('TX: ' + str(temp) +'\n')
                    else:
                        # estimate new value based on previous value
                        results.write('ES: ' + str(tempPrev*a) +'\n')
                        # add to distortion
                        dist += math.pow(error,2)
                    tempPrev = temp
                    avg = float(val)
                    count = 1
                else:
                    avg += float(val)
                    count += 1

            # write transmission statistics to end of destination file
            stats.write(str(alpha) + ',' + str(k_alpha) + ',' + str(tx) + ',' + str(total) + ',' + str(float(tx)/float(total)) + ',' + str(float(dist)/float(total)) + '\n')


# Run batch simulation for a vector of alpha values & corresponding k_alpha
# Load alpha, k_alpha values from file
with open('alpha_k_alpha.csv') as parameters:

    for param in parameters:
        pair = param.strip().split(',')
        print 'Simulating... alpha = ' + pair[0] +', k_alpha = '+ pair[1]
        #run simulation
        simulate (float(pair[0]), float(pair[1]))
    print 'DONE!'

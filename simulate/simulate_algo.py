def simulate (alpha, k_alpha):

    a = 0.9999

    with open('data-batch-2.dat.txt') as data:
        
        results = open('sim_alpha_'+str(alpha)+'.txt', 'w+')
        results.write('alpha   = ' + str(alpha) +'\nk_alpha = ' + str(k_alpha) + '\n')
        results.close()

        with open('sim_alpha_'+str(alpha)+'.txt', 'a') as results:

            tempTx = -1
            total = 0
            tx = 0

            for val in data:
                temp = float(val)
                error = temp - a * tempTx
                total += 1
                if abs(error) > k_alpha or tx == 0:
                    tx += 1
                    tempTx = temp
                    results.write('TX: ' + str(temp) +'\n')
                else:
                    results.write('ES: ' + str(temp) +'\n')

            results.write('Tx  = ' + str(tx) + '\nTot = ' + str(total))

simulate (0.10, 0.06103870595)
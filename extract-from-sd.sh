DATESTRING=$(date "+%d%m%Y-%H%M")

scp root@arduino.local:/mnt/sda1/temp02.txt data/data-${DATESTRING}.txt


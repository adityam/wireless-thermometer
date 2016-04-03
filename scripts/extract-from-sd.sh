DATESTRING=$(date "+%d%m%Y-%H%M")

scp root@arduino.local:/mnt/sda1/data.txt ../data/data-${DATESTRING}.txt


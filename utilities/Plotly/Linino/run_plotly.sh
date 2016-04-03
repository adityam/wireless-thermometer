#!/bin/sh
touch /root/start
# kill -9 $(pgrep -f "python /root/run.py")
# python /root/kill_processes.py
touch /root/run
(python /root/run.py)&
touch /root/done

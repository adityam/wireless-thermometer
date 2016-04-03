import os
import time
time.sleep(10)
try:
    os.system("kill -9 $(pgrep -f \"python /root/run.py\")")
except:
    pass

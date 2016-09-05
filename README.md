# Wireless Thermometer for Arduino Yun

## Synopsis

Arduino Yun and TMP38 sensor used to build wireless thermometer testbed. Testbed used for testing tranmission & estimation algorithms which can enable lower tranmission rates while maintaining low distortion in estimated data.

## Arduino

### BasicAlgo

Temperature data is obtained from the sensor and transmission algorithm parameters are used to tag each sample as either transmitted or estimated.

### LogTemperature

Used for collecting temperature data. Temperature data is obtained from the sensor and logged in a text file with timestamps on the SD card and also transmitted via Plotly API.

### WebServer

Using Arduino's webserver capabilities, a web interface can be acessed remotely to display temperature readings from the sensor in real-time.

## Data

### alpha_k_alpha

List of alpha values and corresponding k_alpha values used as algorithm parameters during simulate_algo script simulation.

### final-results

Results of simulate_algo script simulation with data-batch-1.dat.

### raw-data

Timestamped temperature data collected from the sensor periodically indoors near a window during the fall and winter semesters of 2015/2016. "batch" files may contain data from multiple raw data files.

## MATLAB

### rmse

Helper function used for calculating the root mean square error.

## Scripts

### extract-from-sd

Using SSH, script can read up-to-date data logged in a text file on Arduino SD card and write contents in to a local file.

### moving_avg_filter

Reads existing file containing temperature data and outputs data with a moving average filter applied.

### simulate_algo

Reads existing file containing temperature data and simulates the transmission algorithm with multiple alpha values and outputs simulation results in new files.



## License

MIT License

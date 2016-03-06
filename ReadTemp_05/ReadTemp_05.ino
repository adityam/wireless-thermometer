#include <PlotlyYun.h>
#include <YunMessenger.h>
#include <Bridge.h>
#include <Console.h>
#include <FileIO.h>

// tie 3.3V to ARef and measure it with a multimeter
#define aref_voltage 3.3  

// stream tokens (must match "config.json" file on Linino)
plotly plotter1("j3u7df1603");

float val;
float voltage;
float tempC;
int tempPin = 0;
String dataString;

void setup() {

    // set the ARef to something other than 5v
    analogReference(EXTERNAL);

    // start-up the bridge
    Bridge.begin();
    FileSystem.begin();
    
    // start the Plotly-Python program on the Linino
    Process p;
    p.runShellCommand("/root/run_plotly.sh");
    while (p.running()){ ; } // do nothing until process finishes

    delay(2000);
    Console.begin();
    while (!Console) {
      ; // wait for Console port to connect.
    }
    Console.buffer(64);
    delay(2000);

    plotter1.timezone = "America/Montreal";
}

void loop() {
  
    // Get and convert temperature value
    val = analogRead(tempPin);
    // converting that reading to voltage, which is based off the reference voltage
    voltage = val * aref_voltage;
    //converting from 10 mv per degree wit 500 mV offset
    //to degrees ((volatge - 500mV) times 100)
    voltage /= 1024.0;
    tempC = (voltage - 0.5) * 100;

    // Log on SD card
    dataString = "";
    dataString += getTimeStamp();
    dataString += " = ";
    dataString += String(tempC);

    File dataFile = FileSystem.open("/mnt/sd/data.txt", FILE_APPEND);
    if (dataFile) {
      // save to file
      dataFile.println(dataString);
      dataFile.close();
    }
   
    // Send to Plotly
    plotter1.plot(tempC); // automatic time-stamped value in x-axis

    // delay between readings
    delay(5000);
}

// Helper method to get current time as String
String getTimeStamp() {
  String result;
  Process time;
  time.begin("date");
  time.addParameter("+%D-%T");  
  time.run(); 

  while(time.available()>0) {
    char c = time.read();
    if(c != '\n')
      result += c;
  }

  return result;
}

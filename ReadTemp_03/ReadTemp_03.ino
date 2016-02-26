#include <PlotlyYun.h>
#include <YunMessenger.h>
#include <Bridge.h>
#include <Console.h>
#include <FileIO.h>

// stream tokens (must match "config.json" file on Linino)
plotly plotter1("j3u7df1603");

float val;
float mv;
float temp;
int tempPin = 0;
String dataString;

void setup() {

    // start-up the bridge
    Serial.begin(9600);
    Bridge.begin();
    FileSystem.begin();
    
    #define debug

    #ifdef debug
      while(!Serial);  
      Serial.println("Serial initialized\n");
    #endif
    
    // start the Plotly-Python program on the Linino
    Process p;
    p.runShellCommand("/root/run_plotly.sh");
    while (p.running()){ ; } // do nothing until process finishes
    if (Serial){
      Serial.println("Plotly shell complete\n");
    }

    plotter1.timezone = "America/Montreal";
}

void loop() {
  
    // Get and convert temperature value
    val = analogRead(tempPin);
    mv = (val/1024.0)*5000; // 10-bit analog resolution, 5000mv total
    temp = (mv-750)/10 + 25; // 750mv = 25*C, 10mv/*C variation

    // Log on SD card
    dataString = "";
    dataString += getTimeStamp();
    dataString += " = ";
    dataString += String(temp);

    File dataFile = FileSystem.open("/mnt/sd/temp01.txt", FILE_APPEND);
    if (dataFile) {
      // save to file
      dataFile.println(dataString);
      dataFile.close();
      // print to serial
      if (Serial){
        Serial.println(dataString);
      }
    }
    else {
      if (Serial){
        Serial.println("error opening temp01.txt");
      }
    } 
   
    // Send to Plotly
    plotter1.plot(temp); // automatic time-stamped value in x-axis

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


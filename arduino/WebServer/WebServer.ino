#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <FileIO.h>

// tie 3.3V to ARef
#define aref_voltage 3.3  

//WiFi setup:
// Listen on default port 5555, the webserver on the Yún
// will forward there all the HTTP requests for us.
YunServer server;

float val;
float voltage;
float tempC;
int tempPin = 0;

// algorithm parameters
const float A = 0.9999;
const float K_ALPHA = 0.00959410785; // alpha = 0.34

int requestCount = 0;
int txCount = 0;
float tempPrev = -1;
String lastTxTime = "no tx";
float error = 0;
float dist = 0;

float printTemp;
String estimateFlag;

unsigned long previousMillis = 0; 
long interval = 5000;  

void setup() {

  // set the ARef to something other than 5v
    analogReference(EXTERNAL);
  
  // Bridge startup
  Bridge.begin();
  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();

  FileSystem.begin();
  
}

void loop() { 

  /* Get and convert temperature value */
  
  val = analogRead(tempPin);
  // converting that reading to voltage, which is based off the reference voltage
  voltage = val * aref_voltage;
  //converting from 10 mv per degree wit 500 mV offset
  //to degrees ((volatge - 500mV) times 100)
  voltage /= 1024.0;
  tempC = (voltage - 0.5) * 100;

  /* SERVING WEB REQUESTS */
  
  // Get clients coming from server
  YunClient client = server.accept();

  // There is a new client?
  if (client) { 
    // If there is a request, then read the URL command
    String command = client.readStringUntil('/'); //Read in the string up to the frist
    //forward dash "/".
    command.trim();        //kill whitespace
    
    if (command == "temperature") { // if request URL contains "temperature"  
      error = abs(tempC - A * tempPrev);
      if (error > K_ALPHA || requestCount == 0){
        txCount++;
        printTemp = tempC;
        lastTxTime = getTimeStamp();
        estimateFlag = "t";
      }
      else {
        printTemp = tempPrev * A;
        dist += error * 1000;
        estimateFlag = "e";
      }
      tempPrev = tempC;
      requestCount++;
      client.print(estimateFlag);
      client.print(",");
      client.print(printTemp);
      client.print(",");
      client.print(lastTxTime);
      client.print(",");
      client.print(txCount);
      client.print(",");
      client.print(requestCount);
      client.print(",");
      client.print(dist/requestCount);
      client.print("e-4");
      
      //send current temperature in degrees C
    }

    else if (command == "timestamp") {  // if request URL contains "timestamp"
      client.print(getTimeStamp());
    }
    
    // Close connection and free resources.
    client.stop();
    client.flush();//discard any bytes that have been written to client but not yet read.
  }

  /* SAVING TO SD CARD */

  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis > interval) {
    
    previousMillis = currentMillis;  

    // Log on SD card
    String dataString = "";
    dataString += getTimeStamp();
    dataString += " = ";
    dataString += String(tempC);
    saveToFile(dataString);
  }

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

// Helper method to append String to a file
void saveToFile(String content){
    File dataFile = FileSystem.open("/mnt/sd/data.txt", FILE_APPEND);
    if (dataFile) {
      // save to file
      dataFile.println(content);
      dataFile.close();
    }
}


#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

// tie 3.3V to ARef and measure it with a multimeter
#define aref_voltage 3.3  

//WiFi setup:
// Listen on default port 5555, the webserver on the Yún
// will forward there all the HTTP requests for us.
YunServer server;


float val;
float voltage;
float tempC;
int tempPin = 0;

void setup() {

  // set the ARef to something other than 5v
    analogReference(EXTERNAL);
  
  // Bridge startup
  Bridge.begin();
  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();
  
}

void loop() { 
  
  // Get clients coming from server
  YunClient client = server.accept();

  // There is a new client?
  if (client) { 
    // If there is a request, then read the URL command
    String command = client.readStringUntil('/'); //Read in the string up to the frist
    //forward dash "/".
    command.trim();        //kill whitespace
    
    if (command == "temperature") {  //Check to see if the first part of the URL command 
    //included the word "temperature" 
      // Get and convert temperature value
      val = analogRead(tempPin);
      // converting that reading to voltage, which is based off the reference voltage
      voltage = val * aref_voltage;
      //converting from 10 mv per degree wit 500 mV offset
      //to degrees ((volatge - 500mV) times 100)
      voltage /= 1024.0;
      tempC = (voltage - 0.5) * 100;
   
      //Send text data to the client (which will interpretted by client as HTML) 
      //using the client.print command: 
      client.print(tempC); //send current temperature in degrees C
    }

    else if (command == "timestamp") {  //Check to see if the first part of the URL command 
      client.print(getTimeStamp()); //send current temperature in degrees C
    }
    
    // Close connection and free resources.
    client.stop();
    client.flush();//discard any bytes that have been written to client but not 
    //yet read.
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

#include <PlotlyYun.h>
#include <YunMessenger.h>
#include <Bridge.h>
#include <Console.h>

// stream tokens (must match "config.json" file on Linino)
plotly plotter1("j3u7df1603");
//plotly plotter2("f148efz3xy");

float val;
float mv;
float temp;
int tempPin = 0;

void setup() {

    // start-up the bridge
    Bridge.begin();
    
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
    mv = (val/1024.0)*5000; // 10-bit analog resolution, 5000mv total
    temp = (mv-750)/10 + 25; // 750mv = 25*C, 10mv/*C variation

    // Send to Plotly
    plotter1.plot(temp); // automatic time-stamped value in x-axis
    // plotter1.plot( millis(), analogRead(A0) ); manual x-axis value
    delay(1000);
}


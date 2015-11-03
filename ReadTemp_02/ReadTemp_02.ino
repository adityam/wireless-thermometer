#include <PlotlyYun.h>
#include <YunMessenger.h>
#include <Bridge.h>
#include <Console.h>

// Initialize plotly "plotters" with your stream tokens.
// Find your stream tokens in your plotly account here: https://plot.ly/settings
// Initialize as many plotters as you want! Each plotter will send
// data to the same plot as a separate line.
// Make sure that you place these exact-same stream tokens in your `config.json` file
// on the Linino.

plotly plotter1("j3u7df1603");
//plotly plotter2("f148efz3xy");

float val;
float mv;
float temp;
int tempPin = 0;

void setup() {

    // start-up the bridge
    Bridge.begin();

    ////
    // Uncomment the following 3 lines to start the
    // Plotly-Python program on the Linino
    // from the Arduino

    // Process p;
    // p.runShellCommand("/root/run_plotly.sh");
    // while (p.running()){ ; } // do nothing until process finishes

    delay(2000);
    Console.begin();
    while (!Console) {
      ; // wait for Console port to connect.
    }

    Console.buffer(64);
    delay(2000);

    plotter1.timezone = "America/Montreal";
    //plotter2.timezone = "America/Montreal";
}

void loop() {
    // Graph data! Place the "y" value that you want to plot
    // the "x" value will automatically be a time-stamped value
    // Each "plotter" will send data to the same plot as separate lines
      val = analogRead(tempPin);
      mv = (val/1024.0)*5000; 
      temp = mv/10;
    plotter1.plot( temp );
    //plotter2.plot( analogRead(A1) );

    // You can also set the "x" value manually
    // by placing a pair of points in the plot function:
//    plotter1.plot( millis(), analogRead(A0) );
//    plotter2.plot( millis(), analogRead(A1) );
    delay(1000);
}


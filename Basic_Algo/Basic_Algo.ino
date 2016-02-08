float val;
float mv;
int SENSOR_PIN = 0;

int const SAMPLE_INTERVAL = 1000; // in ms
float const K = 1.0; // threshold
float const A = 1.0; // multiplier

float error = 0;
float temp; // most recent temp on Tx side
float tempRx; // most recent temp on Rx side

void setup (){
  Serial.begin(9600);
  temp = getTemp ();
  tempRx = getTemp ();
}

void loop (){
  temp = getTemp();
  error = temp - A * tempRx;
  if (abs(error) > K){
    tempRx = temp;
    Serial.print("Received: ");
  }
  else{
    tempRx = A * tempRx;
    Serial.print("Estimated: ");
  }
  printTemp(tempRx);
  delay(SAMPLE_INTERVAL);
}

// get temperature reading from sensor
float getTemp () {
  val = analogRead(SENSOR_PIN);
  mv = (val/1024.0)*5000; 
  temp = (mv-750)/10 + 25;
  return temp;
}

// prints temperature to serial
void printTemp (float temp) {
  Serial.print(temp);
  Serial.println("*C");
}

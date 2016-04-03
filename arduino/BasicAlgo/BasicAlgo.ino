float val;
float mv;
float temp;
int SENSOR_PIN = 0;

int const SAMPLE_INTERVAL = 1000;
float const K = 1.0;
float const A = 1.0;

float error = 0;
float tempRx;
float alpha = 0;

int total = 0;
int transmitted = 0;

void setup (){
  Serial.begin(9600);
  temp = getTemp ();
  tempRx = getTemp ();
  transmitted++;
}

void loop (){
  temp = getTemp();
  total ++;
  error = temp - A * tempRx;
  if (abs(error) > K){
    tempRx = temp;
    Serial.print("Received: ");
    transmitted ++;
  }
  else{
    tempRx = A * tempRx;
    Serial.print("Estimated: ");
  }
  printTemp(tempRx);
  alpha = transmitted/total;
  Serial.print("transmissions: ");
  Serial.println(transmitted);
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

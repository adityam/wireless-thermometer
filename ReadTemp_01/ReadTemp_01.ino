float val;
float mv;
float temp;
int tempPin = 0;

void setup (){
  Serial.begin(9600);
}

void loop (){
  val = analogRead(tempPin);
  mv = (val/1024.0)*5000; 
  temp = mv/10;
  Serial.print("TEMP: ");
  Serial.print(temp);
  Serial.print("*C");
  Serial.println();
  delay(1000);
}


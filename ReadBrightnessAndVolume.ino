/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
void setup() {
  pinMode(13, OUTPUT);
  pinMode(3, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

String readLine(){
      String s =  "";
      char c;
      while((c = Serial.read()) !='\n'){
          s += c;
      }  
      return s;
}

// the loop routine runs over and over again forever:
void loop() {  
  if(Serial.available())
  {
    String command = readLine();
    if (command == "TURN_ON_1")
      digitalWrite(13, HIGH);
    else if (command == "TURN_OFF_1")
      digitalWrite(13, LOW);
    else if (command == "TURN_ON_2")
      digitalWrite(3, HIGH);
    else if (command == "TURN_OFF_2")
      digitalWrite(3, LOW);

    Serial.println(command);
  }
  String volume = String(analogRead(A2));
  String brightness = String(analogRead(A0));
  Serial.println("B:" + brightness);
  Serial.println("V:" + volume);
  Serial.println("-");
  delay(100);
}

//BD18347AEFV-C EVK for Global Dimming

//Last Modified: 1/8/25
// Change: add exponential global dimming

int globaldimminput = 0;
int globaldimmoutput = 0;

void setup() {

  pinMode(2,OUTPUT); // FET GATE3
  pinMode(3,OUTPUT); // FET GATE2
  pinMode(4,OUTPUT); // FET GATE1
  pinMode(6,OUTPUT); // CRT Global Dimming pin -> !!!! need to short D6 to A5 on the EVK !!!!
  pinMode(A1,INPUT); // Global Dimming potentiometer
  pinMode(A5,INPUT); // set A5 as input so that it doesn't affect CRT
  pinMode(A4,OUTPUT); // MSET1
  pinMode(A3,OUTPUT); // MSET2

  //Serial.begin(9600);

}

void loop() {

  digitalWrite(2, HIGH); digitalWrite(3,HIGH); digitalWrite(4,HIGH); // Turn on all the FETs

  globaldimminput = analogRead(A1);
  //Serial.print("Global Dimm In ="); Serial.print(globaldimminput); Serial.print('\n');

  if(globaldimminput != 0)
  {
    globaldimmoutput = 1.045*exp(0.0054*globaldimminput); // exponential dimming
    globaldimmoutput = constrain(globaldimmoutput,0,255);
  }
  else
  {
    globaldimmoutput = 0;
  }

  //globaldimmoutput = map(globaldimminput,0,1023,0,255);
  //Serial.print("Global Dimm Out ="); Serial.print(globaldimmoutput); Serial.print('\n');

  analogWrite(6, globaldimmoutput); // write the PWM duty based on reading at A1 (pin A5 Nano PWM frequency is 980Hz according to https://www.arduino.cc/reference/tr/language/functions/analog-io/analogwrite/

  analogWrite(A4,255);
  analogWrite(A3,255); //set MSET1 and MSET2 = HIGH

  //delay(1000);

}

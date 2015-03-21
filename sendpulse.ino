//An example that Utilizes a function "sendpulses" to send pulse (clock) , number of pulses, direction and an "enable" flag
//to a stepper motor H-Bridge controller.

bool dir = LOW; //direction flag

void setup() {
  //Serial.begin(9600); //in case we want to debug/ show values
  pinMode(6, OUTPUT);//clock output
  pinMode(7, OUTPUT);//direction
  pinMode(8, OUTPUT);//enable pin
}


//sends pulses at specified parameters to rotate stepper motor CW and CCW
void loop()
{
  sendpulses(800, 400, 6, true);
  delay(100);
  sendpulses(800, 400, 6, false);
  delay(100);
}

void sendpulses(float freq, float numpulse, int pin, bool dir)
{
  digitalWrite(8, HIGH); //assure enable set high
  digitalWrite(7, dir);//set direction
  long time = (numpulse * 1000) / (freq * 1000) * 1000;//1000's added to minimize roundoff error due to division
  //Serial.println(time);
  if (freq < 50.0)// tone does not work at low frequencies - switch to manual (the for loop) below 50Hz
  {
    int i = 0;
    float del = time / numpulse;//calculate proper delay
    for (i = 0; i < numpulse; i++)
    {
      digitalWrite(pin, HIGH);
      delay(del);
      digitalWrite(pin, LOW);
    }
  }
  else
  {
    tone(pin, freq, time); //tone utilizes AVR timers which are capable of much higher frequencies that "Loop" can provide
    delay(time); //even though tone has the 3rd parameter supplied - it seems to require a delay at the same time to wait until all pulses are sent
    noTone(pin);//end tone
  }
}

int feedPin = 8;
int spinPin = 6;
int potPin = 10;
int redLed = 12;
int greenLed = 11;
boolean feedDay = true;
unsigned long startTimePot = 0;
unsigned long startTimeFeed = 0;
unsigned long cookTime = 18000000;
unsigned long waitTime = 72000000;


void setup()
{
  Serial.begin(9600);
  pinMode(feedPin, OUTPUT);
  pinMode(potPin, OUTPUT);
  pinMode(spinPin, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
}



void loop()
{
  while (Serial.available() == 0);
  int val = Serial.read() - '0';
    
  
  if ((feedDay == true) && (val == 1))
  {
    Serial.println("Feeding the fish!!!");
    for  (int i = 0; i < 10; i++)
    {
      flash();
    }
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(feedPin, HIGH);
    delay(2500);
    digitalWrite(feedPin, LOW);
    feedDay = false;
    startTimeFeed = millis();
  }
  
   if ((millis() - startTimeFeed) > waitTime)
    {
     feedDay = true;
     digitalWrite(greenLed, HIGH);
     digitalWrite(redLed, LOW);
    } 
    
  
  if (val == 2) 
  {
    Serial.println("Spinning the Wheel");
    digitalWrite(spinPin, HIGH);
    delay(10000);
    digitalWrite(spinPin, LOW);
  }
  
  
  
  
  if (val == 3) 
  {
    Serial.println("firing up the crockpot!!!");
    digitalWrite(potPin, HIGH);
    startTimePot = millis();
  }
    
    
   if ((potPin == HIGH) && ((millis() - startTimePot) > cookTime))
    {
    digitalWrite(potPin, LOW);
    }
  
  
   if (val == 4)
    {
     feedDay = true;
     digitalWrite(greenLed, HIGH);
     digitalWrite(redLed, LOW);
    }
 
  
  else if (val == 0)
  {
    Serial.println("It's all off boss!!!");
    digitalWrite(feedPin, LOW);
    digitalWrite(spinPin, LOW);
    digitalWrite(potPin, LOW);
  }

}

void flash()
{
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    delay(400);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    delay(400);
}

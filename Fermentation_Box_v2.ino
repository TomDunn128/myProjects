  #include <dht.h>                      //Teaching Arduino about our temperature and humidity sensor (DHT11)
  dht DHT;
  float tempRangeLow;                   //Declaring the desired lower temperature limit as a decimal
  float tempRangeHigh;                  //Declaring the desired upper temperature limit as a decimal
  int idleTime=120000;                  //Setting the idle time to 2 minutes (120,000 ticks)
  int fanPin=12;                        //Assigning the fan to digital pin 12, which puts out 5V (the lowest possible voltage that the fan accepts)
  int heatCableRelayPin=10;             //Assigning the heat cable 5V relay signal input to pin 10
  #define tempSensor 7                  //Assigning the temperature/heat sensor to pin 7
  float temperature;                    //Creating a new float variable for the actual measured temperature of the system


void setup() {
  pinMode(fanPin,OUTPUT);                        //Telling Arduino that we want to send the fan a signal (ON/OFF), not receive one
  analogWrite(fanPin,LOW);                       //Turning the fan off whilst the data is being input
  pinMode(heatCableRelayPin,OUTPUT);             //Telling Arduino that we want to send the relay a 5V signal (ON/OFF), not recive one
  pinMode(tempSensor,INPUT);                     //Telling Arduino that we want to get information from the temperature sensor

 Serial.begin(9600);                             // Setting up the serial port
  float chk = DHT.read11(tempSensor);              // Telling Arduino to get our temperature from the pin labelled "tempSensor"
  
 digitalWrite(fanPin, HIGH);                 //Turning on the fan indefinitely for the duration of the program.
  Serial.println("Fan ON");
 digitalWrite(heatCableRelayPin,HIGH);           //Ensuring that when reset the controller, the heat cable is off
  Serial.println("Heater ON");
}

void loop() {
 float chk = DHT.read11(tempSensor);
 
  temperature=(DHT.temperature);           // Setting the float variable 'temperature' equal to the temperature value read from the DHT11 temp sensor
  Serial.print("Temperature:  ");          // Printing the temperature value to
  Serial.println(temperature);             // the serial monitor to check it's working

  float tempRangeLow = 28.00;                                     // USE THIS SECTION TO CHANGE THE LOWER TEMPERATURE LIMIT
  float tempRangeHigh = 36.00;                                    // USE THIS SECTION TO CHANGE THE UPPER TEMPERATURE LIMIT

  float tempRangeMidpoint = (tempRangeLow + tempRangeHigh) / 2;                                                 // Calculating the temperature range midpoint from the upper and lower limits
  float tempRangeUpperMid = (tempRangeMidpoint + 1);                                                            // Calculating the lower mid temperature range
  float tempRangeLowerMid = (tempRangeMidpoint - 1);                                                            // Calculating the lower mid temperature range
  
  if (temperature > tempRangeUpperMid) {
      digitalWrite(heatCableRelayPin,LOW);
        Serial.println("Heater OFF");
    }
    
  else if (temperature < tempRangeLowerMid)
    {
      digitalWrite(heatCableRelayPin,HIGH);
        Serial.println("Heater ON");
    }

  else {
    
  }

  delay(10000);   //Adding a delay of 100 seconds to the loop before the IF statement is run again to minimize the amount the system gets turned off and on whilst allowing for temperature drift
  
}

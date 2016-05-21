// Define the Pin the Temperature sensor is on
int tempPin = A0;

// Create a variable that will store the temperature value
double temperature = 0.0;
double temperatureF = 0.0;
String temperatureString = "";

void setup()
{
  // Register a Particle variable here
  Particle.variable("temperature", &temperature, DOUBLE);
  Particle.variable("temperatureF", &temperatureF, DOUBLE);
  Particle.variable("tempString", &temperatureString, STRING);

  // Connect the temperature sensor to A0 and configure it
  // to be an input
  pinMode(tempPin, INPUT);
}

void loop()
{
  // Keep reading the sensor value so when we make an API
  // call to read its value, we have the latest one
  int reading = analogRead(tempPin);

  // The returned value from the device is going to be in the range from 0 to 4095
  // Calculate the voltage from the sensor reading
  double voltage = (reading * 3.3) / 4095.0;

  // Calculate the temperature and update our static variable
  temperature = (voltage - 0.5) * 100;

  // Now convert to Farenheight
  temperatureF = ((temperature * 9.0) / 5.0) + 32.0;
  temperatureString = String::format("%.2f", temperatureF);
  Particle.publish("temperature", temperatureString, 60, PRIVATE);
  delay(2000);
}

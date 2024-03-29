/**
 * Measures the delay between the moment a flash unit is fired and  TODO: Docs!
 * the moment it actually lights up
 *
 * Author: Dimitar Kovachev, http://lowvoltage.wordpress.com/
 *
 * Released under the Creative Commons Attribution Share-Alike 3.0 license
 * http://creativecommons.org/licenses/by-sa/3.0/
 */
const int chargePin = 6;                      // The constant-current source is controlled by this pin. LOW is charging, HIGH is not-charging
const int dischargePin = 7;                   // The discharging MOSFET is controlled by this pin. LOW is not-discharging, HIGH is discharging
const int voltagePin = A0;                    // The capacitor voltage is sampled on this pin

const double chargeCurrentMA = 1.285;           // The measured current, provided by the constant current source. Expressed in milli-Amperes.
const double internalReferenceVoltage = 1.081;  // Arduino's internal ADC reference voltage, as measured at the AREF pin

const double targetCapacitorVoltage = 0.2;      // The capacitor will be charged up to this voltage. Expressed in Volts.
const double openCircuitThresholdVoltage = 0.4; // A voltages above this threshold indicates that a capacitor is NOT present at the test terminals. Expressed in Volts.

// Map the voltages to [0, 1023] values, for easier analogRead() comparisons.
const int targetVoltageReading = voltageToReading(targetCapacitorVoltage);
const int openCircuitVoltageReading = voltageToReading(openCircuitThresholdVoltage);

const unsigned long chargeTimeoutUS = 2000000;             // Charging duration limit, in micro-seconds.

void setup()
{
  pinMode(chargePin, OUTPUT);       // Sets the "CHARGE" pin as output
  digitalWrite(chargePin, HIGH);    // Default state is HIGH / not-charging

  pinMode(dischargePin, OUTPUT);    // Sets the "DISCHARGE" pin as output
  digitalWrite(dischargePin, LOW);  // Default state is LOW / not-discharging

  pinMode(voltagePin, INPUT);       // Sets the "VOLTAGE" pin as input

  Serial.begin(9600);               // Initializes serial communication
  
  analogReference(INTERNAL);        // Use the internal 1.1v ADC reference
  
  discharge();
}

void loop()
{
  chargeAndMeasure();
  discharge();  
  delay(5000);
}


void chargeAndMeasure()
{
  // Note the moment the charging starts
  unsigned long startTime = micros();
  
  digitalWrite(dischargePin, LOW);  // Stop discharging
  digitalWrite(chargePin, LOW);     // Start charging
 
  int currentReading = 0; 
  unsigned long elapsedTimeUS = 0;
  while (true)
  {
    currentReading = analogRead(voltagePin);
    
    // Check if a capacitor is present
    if (currentReading >= openCircuitVoltageReading)
    {
      Serial.print("Ready!\n");
      return;
    }
    
    elapsedTimeUS = micros() - startTime;
    if (currentReading >= targetVoltageReading || elapsedTimeUS >= chargeTimeoutUS)
    {
      // Estimate capacity: C = (i * t) / v
      double voltageMV = readingToVoltage(currentReading) * 1000.0;  // In milli-Volts
      double c = (chargeCurrentMA * elapsedTimeUS) / voltageMV;

      Serial.print("Charged in ");
      Serial.print(elapsedTimeUS);
      Serial.print(" usec\n");
      Serial.print("Voltage=");
      Serial.print(voltageMV);
      Serial.print(" mV\n");
      Serial.print("C=");
      Serial.print(c);
      Serial.print(" uF\n");
      
      return;
    }
  }
}

void discharge()
{
  // Note the moment the discharging starts
  unsigned long startTime = micros();

  digitalWrite(chargePin, HIGH);     // Stop charging
  digitalWrite(dischargePin, HIGH);  // Start discharging

  while (analogRead(voltagePin) > 0)
  {
    unsigned long elapsedTimeUS = micros() - startTime;
    if (elapsedTimeUS >= chargeTimeoutUS)
    {
      Serial.print("Failed to discharge");
      Serial.print("\n");
      
      return;
    }
  }
}

inline static int voltageToReading(double voltage)
{
  return voltage * (1024.0 / internalReferenceVoltage);
}

inline static double readingToVoltage(int reading)
{
  return reading * (internalReferenceVoltage / 1024.0);
}

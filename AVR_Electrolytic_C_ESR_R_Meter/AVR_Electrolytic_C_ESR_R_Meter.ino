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

const double chargeCurrentMA = 52.6;           // The measured current, provided by the constant current source. Expressed in milli-Amperes.
const double internalReferenceVoltage = 1.1;  // Arduino's internal ADC reference voltage

const double targetCapacitorVoltage = 0.2;      // The capacitor will be charged up to this voltage. Expressed in Volts.
const double openCircuitThresholdVoltage = 0.4; // A voltages above this threshold indicates that a capacitor is NOT present at the test terminals. Expressed in Volts.

// Map the voltages to [0, 1023] values, for easier analogRead() comparisons.
const int targetVoltageReading = voltageToReading(targetCapacitorVoltage);
const int openCircuitVoltageReading = voltageToReading(openCircuitThresholdVoltage);

const unsigned long chargeTimeoutUS = 2000000;             // Charging duration limit, in micro-seconds.

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void setup()
{
  pinMode(chargePin, OUTPUT);       // Sets the "CHARGE" pin as output
  digitalWrite(chargePin, HIGH);    // Default state is HIGH / not-charging

  pinMode(dischargePin, OUTPUT);    // Sets the "DISCHARGE" pin as output
  digitalWrite(dischargePin, LOW);  // Default state is LOW / not-discharging

  pinMode(voltagePin, INPUT);       // Sets the "VOLTAGE" pin as input

  Serial.begin(9600);               // Initializes serial communication
  
  analogReference(INTERNAL);        // Use the internal 1.1v ADC reference
  

  // set prescale to 16
  sbi(ADCSRA,ADPS2);
  cbi(ADCSRA,ADPS1);
  cbi(ADCSRA,ADPS0);

  discharge();
}

void loop()
{
  measureESR();
  discharge();  
  delay(1000);

  chargeAndMeasure();
  discharge();  
  Serial.print("\n");
  delay(5000);
}


void chargeAndMeasure()
{
  digitalWrite(dischargePin, LOW);  // Stop discharging
  delay(10);

  // Note the moment the charging starts
  unsigned long startTime = micros();
  digitalWrite(chargePin, LOW);     // Start charging
 
  delayMicroseconds(1);
  int esrReading = analogRead(voltagePin);
  
  int currentReading = 0; 
  unsigned long elapsedTimeUS = 0;
  while (true)
  {
    elapsedTimeUS = micros() - startTime;
    currentReading = analogRead(voltagePin);
    
    // Check if a capacitor is present
    if (currentReading >= openCircuitVoltageReading)
    {
      Serial.print("Ready!\n");
      return;
    }
    
    if (currentReading >= targetVoltageReading || elapsedTimeUS >= chargeTimeoutUS)
    {
      digitalWrite(chargePin, HIGH);     // Stop charging

      // Estimate capacity: C = (i * t) / v
      double voltageMV = readingToVoltage(currentReading) * 1000.0;  // In milli-Volts
      double c = (chargeCurrentMA * elapsedTimeUS) / voltageMV;

      Serial.print("Voltage=");
      Serial.print(voltageMV);
      Serial.print(" mV  @ ");
      Serial.print(elapsedTimeUS);
      Serial.print(" usec\n");
      Serial.print("C=");
      Serial.print(c);
      Serial.print(" uF\n");
      
      double esrVoltageMV = readingToVoltage(esrReading) * 1000.0;  // In milli-Volts
      double esr = esrVoltageMV / chargeCurrentMA;    // In Ohms

      Serial.print("V_ESR=");
      Serial.print(esrVoltageMV);
      Serial.print(" mV\n");
      Serial.print("ESR=");
      Serial.print(esr);
      Serial.print(" ohm\n");
      
      Serial.print("V'=");
      Serial.print(voltageMV - esrVoltageMV);
      Serial.print(" mV\n");
      Serial.print("C'=");
      Serial.print((chargeCurrentMA * elapsedTimeUS)/(voltageMV - esrVoltageMV));
      Serial.print(" uF\n");      
      
      return;
    }
  }
}

void measureESR()
{
  digitalWrite(dischargePin, LOW);  // Stop discharging
  delay(10);

  // Note the moment the charging starts
  unsigned long startTime = micros();
  digitalWrite(chargePin, LOW);     // Start charging
  delayMicroseconds(1);
  
  int readings[10]; 
  unsigned long elapsedTimeUS = 0;
  
  for (int i = 0; i < 10; ++i)
  {
    readings[i] = analogRead(voltagePin);
  }
  unsigned long endTime = micros();

  // Report
  if (readings[0] < openCircuitVoltageReading)
  {
    Serial.print("10 ADC readings in ");
    Serial.print(endTime - startTime);
    Serial.print(" uS\n");

    for (int i = 0; i < 10; ++i)
    {
        Serial.print("Voltage[");
        Serial.print(i);
        Serial.print("] = ");
        Serial.print(readingToVoltage(readings[i]) * 1000.0);
        Serial.print(" mV");
        Serial.print("\n");
    }
  }
}

void discharge()
{
  // Note the moment the discharging starts
  unsigned long startTime = micros();

  digitalWrite(chargePin, HIGH);     // Stop charging
  digitalWrite(dischargePin, HIGH);  // Start discharging
  
  delay(5);

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


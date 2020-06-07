int lightValN;
int lightCalN;
int lightValS;
int lightCalS;
int lightN;
int lightS;
int degree;
const int dir = 8;
const int pulse = 9;
const int enable = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lightCalN = analogRead(A0);
  lightCalS = analogRead(A1);
  pinMode(dir, OUTPUT);
  pinMode(pulse, OUTPUT);
  pinMode(enable, OUTPUT);
}

void loop() {
  // Wait cycle
  delay(500);
  
  // Reading inputs
  lightValN = analogRead(A0);
  lightValS = analogRead(A1);
  
  // Doing math to calibrate
  lightN = lightValN - lightCalN;
  lightS = lightValS - lightCalS;
  
  // Serial debug
  Serial.print("RawN:");
  Serial.print(lightValN);
  Serial.print(" CalN:");
  Serial.print(lightN);
  Serial.print(" -");
  Serial.print(" RawS:");
  Serial.print(lightValS);
  Serial.print(" CalS:");
  Serial.print(lightS);
  Serial.print(" Degree:");
  Serial.print(degree);
  Serial.println(" ");
  
  //Program Code
  if (lightN < lightS && degree < 50) {
    digitalWrite(enable, HIGH);
    delay(500);
    digitalWrite(dir, HIGH);
    digitalWrite(pulse, HIGH);
    delay(100);
    digitalWrite(pulse, LOW);
    degree = ++degree;
    digitalWrite(enable, LOW);
    Serial.println("Moving North");
  }
  if (lightN > lightS && degree > -50) {
    digitalWrite(enable, HIGH);
    delay(500);
    digitalWrite(dir, LOW);
    digitalWrite(pulse, HIGH);
    delay(100);
    digitalWrite(pulse, LOW);
    degree = --degree;
    digitalWrite(enable, LOW);
    Serial.println("Moving South");
  }
  if (lightN == lightS) {
    Serial.println("Do Nothing");
  }
  
}


/* Follow up notes:
 * Performed 1 hour test, motor became increasingly hot, cannot touch. - Perhaps set enable pin to activate only when needed and re-attempt 1 hour test. 
 * If that fails, attempt to increase delay time in line 21 "delay(500);" to a longer period while only enabling during checks to reduce "on-time", also monitor the power usage.
 * 
 * Current power usage: 20W idle, 35W no load.
 *  
 * New Analysis:
 * Performed 2 hour test at minimum current setting, previous test was at full current setting. This is dependant on the current required to move the panels on the frame. 
 * Possible to revert code to not include the enable pin and to have that be constant 5v per usual. This will likely also keep the motor where it needs to be long term without loss.
 * Motor was cool to the touch and only used 10-15W of power idle and no load.
 *  
 *  
 *  
 */

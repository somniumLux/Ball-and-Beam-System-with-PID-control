#include <Servo.h> // library for servo motor

// setting pins
#define echoPin 2
#define trigPin 3
#define servoPin 10

// initialization of needed variables
Servo servo;
double current_position, wanted_position = 16., filtered_position, last_position = 0.;
double control, control_1, error, integral = 0, derivative, last_error = 0;
double Kp = 1.5, Ki = 0.1, Kd = 9.75;
double alpha = 0.4;
long duration;
double prop, integ, deriv;

// defining ultrasonic signal function
void position() {
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
}

void setup() {
servo.attach(servoPin);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

// setting trigger pina to low state
digitalWrite(trigPin, LOW);
delayMicroseconds(10);
Serial.begin(9600);
}

void loop()
{
// sending ultrasonic signal
position();

// reading ultrasonic signal travel time
duration = pulseIn(echoPin, HIGH);

// calculating ball's position
current_position = duration * 0.034 / 2;

// correction of calculated distance in low accuracy zone
if(current_position < 2.5 || current_position > 35)
current_position = 0.;

// filtering the position
filtered_position = last_position + alpha*(current_position - last_position);
last_position = filtered_position;

error = wanted_position - filtered_position;

integral += error;
derivative = error - last_error;

// calculating the main control value
control_1 = (Kp * error) + (Ki * integral) + (Kd * derivative);
control = control_1 + 90;

// gains
prop = Kp * error;
integ = Ki * integral;
deriv = Kd * derivative;

// controling the motor
servo.write(control);

last_error = error;

delayMicroseconds(100);

// data printout
Serial.print("Pos: ");
Serial.print(current_position);
Serial.print(",  filtPos: ");
Serial.print(filtered_position);
Serial.print(",   Control: ");
Serial.print(control);
Serial.print(",   Error: ");
Serial.print(error);
Serial.print(",   Prop: ");
Serial.print(prop);
Serial.print(",   Int: ");
Serial.print(integ);
Serial.print(",   Deriv: ");
Serial.println(deriv);
}

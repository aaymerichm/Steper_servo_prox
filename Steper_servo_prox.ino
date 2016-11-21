//SERVO///////////////////
#include <Servo.h>

Servo myservo;

int pos;
int para;
int cm;
int bestValue;
int best;
const int EchoPin = 5;
const int TriggerPin = 6;
//const int LedPin = 13;


//STEPPER/////////////
#include <Stepper.h>  // baixem la llibreria pel Servomotor integrada a Arduino

#define VELOCIDAD 1700 //VELOCITAT. Com més baix més velocitat

int steps = 2;
int direccion = 3;
int reset = 11;
int button = 6;
int desp; //que el stepper pueda girar 170º.  Desplaçament motor
int posicioInicial;  //posició a la que retorna el motor Stepper si el sensor no detecta ninguna presencia

int convert;
int passos;
int a=1;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  //servo.attach (pinServo); //cridem al servo (pin, pulso minimo, pulso maximo)

  // SERVO
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  // STEPPER initialize the digital pin as an output.
  pinMode(steps, OUTPUT);
  pinMode(direccion, OUTPUT);
  pinMode(reset, OUTPUT);

  //SIMLACIÓ
  pinMode(button, INPUT_PULLUP); //fem que un botó simuli el sensor


  //INICIACIÓ POSICIÓ STEPPER
  steps = 200;
  digitalWrite(direccion, LOW); //gira en direcció antihoraria
  digitalWrite(steps, LOW);   // LOW to HIGH hace que el motor avance ya que da la orden al A4988 de avanzar una vez por cada pulso de energia.
  digitalWrite(steps, HIGH);
}

// the loop routine runs over and over again forever
void loop() {

  //SERVO//////////////////////////////////

  Serial.print("Start");
  for (pos = 10; pos <= 170; pos += 5) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);       // tell servo to go to position in variable 'pos'
    cm = bestValue;
    cm = ping(TriggerPin, EchoPin);
    Serial.print("Distancia: ");
    Serial.println(cm);
    delay(5);

    if (bestValue > cm) {
      bestValue = cm;
      best = pos;
    }
  }

  // back to start
  myservo.write(best);              // tell servo to go to position in variable 'pos'
  delay(1000);
  bestValue = 1000000;

  Serial.println(best);

  //STEPPER (Gordu) + SERVO /////////////////////////////

  int angle = 0;

  digitalWrite(reset, LOW);    //Mientras reset este en LOW el motor permanecerá apagado y no sufrirá. El chip apagará todos los puertos y no leerá comandos.
  delay(100);
  digitalWrite(reset, HIGH);   //Cuando reset se encuentre en HIGH el motor arrancará y leerá los comandos enviados.

  convert = passos;
  convert = map(best, 0, 180, 0, 100); //Traduïm el valor del ServoMotor quan detecta algú (graus) al Stepper (passos)

  if (best > angle) {
    a;
  }

  if (best < angle) {
    a = -a;
  }

  desp = passos + (convert * a);
  angle = best;

  digitalWrite(direccion, LOW);
  digitalWrite(steps, LOW);
  digitalWrite(steps, HIGH);
}



int ping(int TriggerPin, int EchoPin) {
  long duration, distanceCm;

  digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos

  distanceCm = duration * 10 / 292 / 2;  //convertimos a distancia, en cm
  return distanceCm;
}



//SI EL SENSOR DETECTA PERSONA. L'ICEBERG VA FINS AL SENSOR (CAS 1)
/*
  if (button == 0) { //Si el sensor està parat (detecta) durant 2 segons. PosFinal(PosSensor)-PosInicial (PosIceberg)
  if (posSensor - posIceberg < posIceberg) { //quan la resta és negativa

    digitalWrite(direccion, LOW); //gira en direcció antihoraria

    digitalWrite(steps, LOW);   // LOW to HIGH hace que el motor avance ya que da la orden al A4988 de avanzar una vez por cada pulso de energia.
    digitalWrite(steps, HIGH);
    //S'HA DE PARAR A LA POSISICÓ DEL SENSOR ----FALTA!!!
    //VELOCITAT --- FALTA!!
  }

  if (posSensor - posIceberg > posIceberg) { //quan la resta és positiva

    digitalWrite(direccion, HIGH); //gira en direcció horaria

    digitalWrite(steps, LOW);   // LOW to HIGH hace que el motor avance ya que da la orden al A4988 de avanzar una vez por cada pulso de energia.
    digitalWrite(steps, HIGH);
    //S'HA DE PARAR A LA POSISICÓ DEL SENSOR ----FALTA!!!
    //VELOCITAT --- FALTA!!
  }
  }

  //SI EL SENSOR NO DETECTA PERSONA. L'ICEBERG TORNA A LA POSICIÓ INICIAL (CAS 2)

  if (button == 1) { //Si el sensor deixa de detectar a ningú. PosFinal(PosIceberg)-PosInicial(PosSensor)
  if (posIceberg - posSensor > posIceberg) {
    digitalWrite(direccion, HIGH); //gira en direcció horaria

    digitalWrite(steps, LOW);   // LOW to HIGH hace que el motor avance ya que da la orden al A4988 de avanzar una vez por cada pulso de energia.
    digitalWrite(steps, HIGH);


    //S'HA DE PARAR A LA POSISICÓ INICIAL DE L'ICEBERG ----FALTA!!!

  }
  if (posIceberg - posSensor < posIceberg) {
    digitalWrite(direccion, LOW); //gira en direcció antihoraria

    digitalWrite(steps, LOW);   // LOW to HIGH hace que el motor avance ya que da la orden al A4988 de avanzar una vez por cada pulso de energia.
    digitalWrite(steps, HIGH);

    //S'HA DE PARAR A LA POSISICÓ INICIAL DE L'ICEBERG ----FALTA!!!
    //VELOCITAT --- FALTA!!
  }
  }

  //////////////////
  digitalWrite(reset, LOW);    //Mientras reset este en LOW el motor permanecerá apagado y no sufrirá. El chip apagará todos los puertos y no leerá comandos.
  delay(100);
  digitalWrite(reset, HIGH);   //Cuando reset se encuentre en HIGH el motor arrancará y leerá los comandos enviados.
  digitalWrite(direccion, HIGH);

  for (int i = 0; i < pasos; i++)     //Equivale al numero de vueltas (200 es 360º grados) o micropasos
  {
  digitalWrite(steps, HIGH);  // This LOW to HIGH change is what creates the
  digitalWrite(steps, LOW); // al A4988 de avanzar una vez por cada pulso de energia.
  delayMicroseconds(VELOCIDAD);     // Regula la velocidad, cuanto mas bajo mas velocidad.

  }

  digitalWrite(reset, LOW);   //Mientras reset este en LOW el motor permanecerá apagado y no sufrirá. El chip apagará todos los puertos y no leerá comandos.
  delay(100);
  digitalWrite(reset, HIGH);   //Cuando reset se encuentre en HIGH el motor arrancará y leerá los comandos enviados.
  digitalWrite(direccion, LOW);

  for (int i = 0; i < pasos; i++)     //Equivale al numero de vueltas (200 es 360º grados) o micropasos
  {

  digitalWrite(steps, LOW);   // LOW to HIGH hace que el motor avance ya que da la orden
  digitalWrite(steps, HIGH);    // al A4988 de avanzar una vez por cada pulso de energia.
  delayMicroseconds(VELOCIDAD);         // Regula la velocidad, cuanto mas bajo mas velocidad.
  }*/



//CODIGO DE COMUNICACIÓN MAESTRO
//CODIGO  PARA MANDAR DATOS AL ESCLAVO
// JUAN PABLO GOMES VILLELA 17517
//------------------------------------------------------------
// ESTE PROGRAMA ES CAPAZ DE MANDARLE DATOS
//AL ESCLAVO Y RECIBIR LA SEÑAL PARA MOVER EL MOTOR
#include <SoftwareSerial.h> //SE INCLUYE LA LIBRERIA DE BT
SoftwareSerial mySerial(2,3); //RX, TX
char maestro;
char bt;
// DEFINIR LAS CONSTANTES
const int R = 8;
const int R2 = 9;
byte numero2 = 0;
const int R3 = 10;
byte numero3 = 0;
byte numero4 = 0;
const int R4 = 11;
float Largo = 0;
float L;
int Altura = 0;

#define dirPin 10
#define stepPin 9
float stepsPerRevolution= 200;
#define fin 4
#define ene 5
int Fin;
int dejar;
int var;
int LedV = 8;
int LedA = 11;
int LedR = 12;
int g;
int h;
void(* reset) (void) = 0;

void setup() {
  Serial.begin(38400); //SE HABILITA PUERTO SERIAL
  while (!Serial) {
    ; // ESPERA PARA QUE SE CONECTE
  }
  Serial.println("¡HOLA ME CONECTE!");//MENSAJE DE CONEXION
  mySerial.begin(38400); //SE HABILITA PUESRTO DE bluetooth
  mySerial.println("HOLA SOY bluetooth");//MENSAJE DE CONEXION
   // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(ene, OUTPUT);
   pinMode(fin, INPUT);
   pinMode(LedV, OUTPUT);
   pinMode(LedA, OUTPUT);
   pinMode(LedR, OUTPUT);
  // var=1;
//---------------------------------------------------------------
digitalWrite(LedV, HIGH);
}
void loop() {
if (Serial.available()>0){
  maestro = (char)Serial.read();
  //bt = (char)mySerial.read();
  // PARA LEER INSTRUCCIONES DE ESPACIO HORIZONTAL
  if (maestro == 'A'){
    Serial.println("ESTA ESCOGIENDO ESTANTERIA A");
    seguridad();
    L = 6.3; 
  }
  else if (maestro == 'B'){
    Serial.println("ESTA ESCOGIENDO ESTANTERIA B");
    seguridad();
    L = 9.5;
  }
  else if (maestro == 'C'){
    Serial.println("ESTA ESCOGIENDO ESTANTERIA C");
    seguridad();
    L = 12.75;
  }
  else if (maestro == 'D'){
    seguridad();
    L = 16;
    
  }
    else if (maestro == 'E'){
    seguridad();
    L = 19.4;
  }
  else if (maestro == 'F'){
    seguridad();
    L = 22.65;
  }
   else if (maestro == 'G'){
    seguridad();
    L = 25.95;
  }
    else if (maestro == 'H'){
    seguridad();
    L = 29.2;
  }
    else if (maestro == 'J'){
    seguridad();
    L = 32.53;
  }
    else if (maestro == 'K'){
    seguridad();
    L = 35.83;
  }
     else if (maestro == 'L'){
    seguridad();
    L = 39.13;
  }
     else if (maestro == 'M'){
    seguridad();
    L = 42.38;
  }
  
// PARA LEER DERECHA/IZAUIERDA Y ALTURA
  else if (maestro == '3'){
    Serial.println("ESTA ESCOGIENDO NIVEL 1");
    mySerial.write('3');
  }

  else if (maestro == '4'){
    Serial.println("ESTA ESCOGIENDO NIVEL 2");
    mySerial.write('4');
  }
  else if (maestro == '5'){
    Serial.println("ESTA ESCOGIENDO NIVEL 3");
    mySerial.write('5');
  }

  else if (maestro == '6'){
    Serial.println("ESTA ESCOGIENDO NIVEL 4");
    mySerial.write('6');
  }

  else if (maestro == '7'){
    Serial.println("ESTA ESCOGIENDO NIVEL 5");
    mySerial.write('7');
  }

  else if (maestro == 'd'){
    Serial.println("ESTA ESCOGIENDO LADO DERECHO");
    mySerial.write('d');
  }
  else if (maestro == 'z'){
    Serial.println("ESTA ESCOGIENDO LADO IZQUIERDO");
    mySerial.write('z');
    }

//  else if (maestro == 'W'){
//    Serial.println("ESTA MANDADO W");
//    //mySerial.write('W');
//    }
  else if (maestro == 't'){ //Ir atraer
    var=1;
    dejar = 0;
    Serial.println(" IR A TRAER");

    }
   else if (maestro == 'u'){ //Ir a dejar
    var=3;
    dejar = 1;
     Serial.println(" IR A DEJAR");
    mySerial.write('u');
    }
   
  }
// ESTA PARTE SE LE AGREGO AL CÓDIGO DE LA VERSIÓN PASADA //
if (mySerial.available()>0){
   bt = (char)mySerial.read();
   if (bt == 'r'){
   Serial.println("LA MÁQUINA ESTA DE REGRESO");
   var = 2;
   }
   else if (bt == '9'){ // OTRA OPCIÓN ES QUITAR ESTA LÍNEA DE CÓDIGO. *
  //  Serial.println("IR A DEJAR PALLET UNO");//*
    var = 5; 
   }
   
//   else if (bt == 'Q' ){ // OTRA OPCIÓN ES QUITAR ESTA LÍNEA DE CÓDIGO. *
//    Serial.println("IR A DEJAR PALLET DOS");//*
//    //var = 7; 
//   }
  }
//-------------------------------------------------------// 
  switch(var){
case 1:
digitalWrite(ene, LOW);
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);
  // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < (L-2) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }

    for (int i = 0; i < (L-(L-2)) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }


 mySerial.write('Y'); //SE MANDA LA SEÑAL "YA" PARA QUE EMPIECE EL MOVIMIENTO VERTICAL
 var=3;
  //delay(1000);
 break;

  case 2:
  digitalWrite(dirPin, LOW);
  
  for (int i = 0; i < 2*L * stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);

    Fin=digitalRead(fin);
    if (Fin==LOW){
     digitalWrite(ene, HIGH);
     delay(1000);
    digitalWrite(LedR, LOW);
    Serial.println("LLEGO A SU FINAL");
    digitalWrite(LedV, HIGH);
     L = 0;
     maestro = 0;
     bt = 0;
     
      }
      else{
        digitalWrite(ene, LOW);
      }
  }
  
  if (dejar == 0){
  var = 4;
  }
  else{
        digitalWrite(ene, LOW);
        delay (3000);
        reset();
      }
  
 break;

case 3:
digitalWrite(ene, HIGH);

break;

case 4:
mySerial.write('8');

var = 0;
break;


case 5:
digitalWrite(ene, LOW);
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);
  // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < (L-5) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }

    for (int i = 0; i < (L-(L-5)) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }


 mySerial.write('W'); //SE MANDA LA SEÑAL "YA" PARA QUE EMPIECE EL MOVIMIENTO VERTICAL
 var=6;
 Serial.println("LLEGo al case 5");
  //delay(1000);
 break;

case 6:
//Serial.println("LLEGo al case 6");
digitalWrite(ene, HIGH);

break;

case 7:
  digitalWrite(dirPin, LOW);
  for (int i = 0; i < 2*L * stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);

    Fin=digitalRead(fin);
    if (Fin==LOW){
     digitalWrite(ene, HIGH);
     delay(1000);
    digitalWrite(LedR, LOW);
    Serial.println("LLEGO A SU FINAL");
    digitalWrite(LedV, HIGH);
     L = 0;
     maestro = 0;
     bt = 0;
      }
      else{
        digitalWrite(ene, LOW);
      }
  }
 break;

}

}

 void seguridad(){
    digitalWrite(LedV, LOW);
    digitalWrite(LedA, HIGH);
    delay(2000);
    digitalWrite(LedA, LOW);
    digitalWrite(LedR, HIGH);
  }

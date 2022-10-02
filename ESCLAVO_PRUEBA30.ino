//CODIGO  PARA MANDAR DATOS AL ESCLAVO
// JUAN PABLO GOMES
//------------------------------------------------------------
// ESTE PROGRAMA ES CAPAZ DE MANDARLE DATOS
//AL ESCLAVO Y RECIBIR LA SEÑAL PARA MOVER EL MOTOR
#include <util/atomic.h> // For the ATOMIC_BLOCK macro
#include <Servo.h>
#define dirPin 16             //definición de pines
#define stepPin 15
float stepsPerRevolution = 200; //pulso necesario para una vuelta completa del nema
#define fin 8
#define ene 14
//VARIABLES
char estanteri;
float L;
float H;
float Altura;
int Fin;
int var;
int LedA = 13;
int derecha;
int izquierda;
int FinalCD=11;
int FinalCI=12; 
int setl = 0;
Servo motorRiel;
Servo motorGarra;
int acomodarH = 0; 
int regreso; 
void(* reset) (void) = 0;

void setup() {
  // Serial.begin(9600);
    Serial.begin(38400);
    //Serial1.begin(38400);
     // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(ene, OUTPUT);
  pinMode(fin, INPUT);
  pinMode(FinalCD, INPUT); //probar con solo INPUT --- INPUT_PULLUP
  pinMode(FinalCI, INPUT); // ''   ''    ''    ''
  pinMode(LedA, OUTPUT);
  motorGarra.attach(9,520,2490);
  motorRiel.attach(10);
}

void loop() {

if (Serial.available()>0){
   estanteri = (char)Serial.read();

   if (estanteri == '3'){
    L = 5.5;
    Altura = 5.5;
  }
  else if (estanteri == '4'){
    L = 15.9;
    Altura = 15.9;
  }
  else if (estanteri == '5'){
    L = 26.1;
    Altura = 26.1;
  }

  else if (estanteri == '6'){
    L = 36.4;
    Altura = 36.4;
  }
  else if (estanteri == '7'){
    L = 46.8;
    Altura = 46.8;
    }
  else if (estanteri == '8'){ //HACER ENTRGA DE PALLET 
    var = 8;
    }
  else if (estanteri == 'd'){
   izquierda=0;
   derecha=1;
    }
  else if (estanteri == 'z'){                  //primer paso lo manda Juanpa
   izquierda=1;
   derecha=0;
   }
    else if (estanteri == 'Y'){                  //primer paso lo manda Juanpa
   var = 1; 
   }

   else if (estanteri == 'u'){                  
   var = 12; 
   }

   else if (estanteri == 'W'){                  
   var = 16; 
   }
  }
  
 
switch(var){
case 1:

//ESCOGE DIRECCIÓN DE GARRA
  if (izquierda==1 && derecha==0){
    
      if (digitalRead(FinalCD)==LOW){
          motorRiel.write(90);         
          delay(500);
          motorGarra.write(180);
          delay(500);
          var=3;
      }
    else{
      motorRiel.write(180);
      delay(300);
      motorGarra.write(90);
        
    }
  }

  if (izquierda==0 && derecha==1){
    
      if (digitalRead(FinalCI)==LOW){
          motorRiel.write(90);
          delay(500);
          motorGarra.write(0);
          delay(500);
          var=3;           
      }
    else{
      motorRiel.write(0);
      delay(300);
      motorGarra.write(90);
    }
  }

break;
    
case 2:                                     
digitalWrite(dirPin, LOW);
  for (int i = 0; i < 2*L * stepsPerRevolution; i++) { //2*L*steps es el ancho de pulso
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000); //define la velocidad
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);  
    
    Fin=digitalRead(fin);
    if (Fin==LOW){
     digitalWrite(ene, HIGH);
     delay(1000);
     L=0;
     var=3;
     
      }
      else{
        digitalWrite(ene, LOW);
      }
  }
  delay(1000); 
break;

  
case 3: //SUBE GARRA

  digitalWrite(ene, LOW);
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

 for (int i = 0; i < (L-(L-2)) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  } 
  // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < (L-5) * stepsPerRevolution; i++) {
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
  
  
 var=4;  
 break;

  case 4:   
  
                                                        //GIRA GARRA A DERECHA/IZQUIERDA Y ENTRA HACIA EL PALLET
  if (derecha==0 && izquierda==1){ //0 1
 
    if (digitalRead(FinalCI)==LOW){  //CD
      motorRiel.write(90);
      var=5;      
      
  }
  else{
      motorRiel.write(0);
    }
  }
  
  if (derecha==1 && izquierda==0){  
 
    if (digitalRead(FinalCD)==LOW){ //CI
      motorRiel.write(90);
      var=5;
      
    }
  else{
    motorRiel.write(180);
    }
  }


  break;

  case 5:
  delay(500);
  digitalWrite(dirPin,HIGH); 
  for(int i = 0; i < 400; i++) {
  digitalWrite(stepPin,HIGH); 
  delayMicroseconds(1000); 
  digitalWrite(stepPin,LOW); 
  delayMicroseconds(1000); 
  }
  

  var=6;  
  break;



   case 6:   
   //RETIRA PALLET

if (derecha==0 && izquierda==1){
 
  if (digitalRead(FinalCD)==LOW){ //i
    motorRiel.write(90);
    var=7;
  }
  else{
    motorRiel.write(180);
    }
  }

   
if (derecha==1 && izquierda==0){
 
  if (digitalRead(FinalCI)==LOW){ //D
    motorRiel.write(90);
    var=7;
  }
  else{
    motorRiel.write(0);
    }
  }

delay(500);

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
     estanteri = 0; 
      L=0;
      //derecha=0;
      //izquierda=0;
    Serial.write('r'); //ESTA PARTE SE LE AGREGO A LA VERSIÓN ANTERIOR 
      //var=2;

      }
      else{
        digitalWrite(ene, LOW);
      }
  } 

   break;
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
case 8:                                                                         //SUBE HACIA PLATAFORMA A DEJAR PALLET
L=6 ;
  digitalWrite(ene, LOW);
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

 for (int i = 0; i < (L-(L-2)) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  } 
  // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < (L-5) * stepsPerRevolution; i++) {
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
  var=9;
  break;
case 9:                                                       /// SE ACERCA A PLATAFORMA A DEJAR PALLET

  if (derecha==0 && izquierda==1){ //0 1
 
    if (digitalRead(FinalCI)==LOW){  //CD
      motorRiel.write(90);
      var=10;      
      
  }
  else{
      motorRiel.write(0);
    }
  }
  
  if (derecha==1 && izquierda==0){  
 
    if (digitalRead(FinalCI)==LOW){ //CI
      motorRiel.write(90);
      delay(500);
                                  //motorGarra.write(180);
      for(int giro = 0; giro <= 180; giro++){
        motorGarra.write(giro);
        delay(5);
      }
                                  
      var=10;
      
    }
  else{
    motorRiel.write(0);
    }
  }
  break;
  
case 10:                         //// BAJA Y DEJA PALLET

  digitalWrite(dirPin, LOW);
  for (int i = 0; i < 2*L * stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);  
    
    Fin=digitalRead(fin);
    if (Fin==LOW){
     digitalWrite(ene, HIGH);
     //delay(1000);
     L=0;
     var=11;     //var 1 se cambió a var 7 para dejar pallets
     //derecha=1;3
     //izquierda=0;
      }
      else{
        digitalWrite(ene, LOW);
      }
  }

  break;
  
case 11:                                                                    ///SE RETIRA DE PLATAFORMA DESPUES DE DEJAR PALLET Y GIRA A 90°
if (derecha==0 && izquierda==1){
 
  if (digitalRead(FinalCD)==LOW){ //i
    motorRiel.write(90);
    delay(500);
    motorGarra.write(90);
    delay(500);
    derecha=0;
    izquierda=0;
  }
  else{
    motorRiel.write(180);
    }
  }

   
if (derecha==1 && izquierda==0){
 
  if (digitalRead(FinalCD)==LOW){ //i
    motorRiel.write(90);
    delay(500);
    motorGarra.write(90);
    delay(500);
     derecha=0;
     izquierda=0;
  }
  else{
    motorRiel.write(180);
    }
  }

  break;

 //Apartir de aqui es ir a dejar 
case 12:
                                                        //GIRA GARRA A DERECHA/IZQUIERDA Y ENTRA HACIA PALLET EN DESPACHO
  if (derecha==0 && izquierda==1){ //0 1
    motorGarra.write(180);
    delay(500);
    if (digitalRead(FinalCI)==LOW){  
      motorRiel.write(90);
      //delay(1000);
      var=13;      
      
  }
  else{
      motorRiel.write(0);
    }
  }
  
  if (derecha==1 && izquierda==0){  
    motorGarra.write(180);
    delay(500);
    if (digitalRead(FinalCI)==LOW){  
      motorRiel.write(90);
      //delay(1000);
      var=13; 
      
    }
  else{
    motorRiel.write(0);
    }
  }
 break;
case 13:                                    //LEVANTA PALLET DE DESPACHO
H=6 ;
  digitalWrite(ene, LOW);
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

 for (int i = 0; i < (H-(H-2)) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  } 
  //delay(1000);
  var=14;
  break;

case 14:
                                                    //RETIRA PALLET DE DESPACHO

if (derecha==0 && izquierda==1){
 
  if (digitalRead(FinalCD)==LOW){ //i
    motorRiel.write(90);
    //delay(1000);
    var=15;
   //acomodarH =1; 
  }
  else{
    motorRiel.write(180);
    }
  }

   
if (derecha==1 && izquierda==0){
 
  if (digitalRead(FinalCI)==LOW){ //i
    motorRiel.write(90);
    //delay(1000);
    for(int giro = 180; giro >= 0; giro--){
        motorGarra.write(giro);
        delay(5);
      }
    var=15;
    //acomodarH = 1; 
  }
  
  }
  delay(500);
  break;


case 15:

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
     estanteri = 0; 
      L=0;
      //derecha=0;
      //izquierda=0;
    Serial.write('9'); //ESTA PARTE SE LE AGREGO A LA VERSIÓN ANTERIOR 
      //var=2;

      }
      else{
        digitalWrite(ene, LOW);
      }
  } 

   break;

case 16:
//Serial.println("ENTRO AL CASO 16");
  digitalWrite(ene, LOW);
  digitalWrite(dirPin, HIGH);

 for (int i = 0; i < (Altura-(Altura-2)) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  } 
  // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < (Altura-5) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }

    for (int i = 0; i < (Altura-(Altura-4)) * stepsPerRevolution; i++) {        
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  } 
  
  var=17;
  break;

case 17:
//Serial.println("ENTRO AL CASO 17");
  if (derecha==0 && izquierda==1){ //0 1
 
    if (digitalRead(FinalCI)==LOW){  //CD
      motorRiel.write(90);
      //delay(500);
      var=18;      
      
  }
  else{
      motorRiel.write(0);
      delay(500);
        motorGarra.write(180);
      delay(500) ;
    }
  }
  
  if (derecha==1 && izquierda==0){  
 
    if (digitalRead(FinalCD)==LOW){ //CI
      motorRiel.write(90);
      //delay(1000);
      var=18;
      
    }
  else{
    motorRiel.write(180);
    delay(500);
        motorGarra.write(0);
      delay(500); 
    }
  }
  break;
  
case 18:                         //// BAJA Y DEJA PALLET
//Serial.println("ENTRO AL CASO 18");
  digitalWrite(dirPin,LOW); 
  for(int i = 0; i < 400; i++) {
  digitalWrite(stepPin,HIGH); 
  delayMicroseconds(1000); 
  digitalWrite(stepPin,LOW); 
  delayMicroseconds(1000); 
  }
   var=19;  
   break;
  
case 19:                                                                    ///SE RETIRA DE PLATAFORMA DESPUES DE DEJAR PALLET Y GIRA A 90°
//Serial.println("ENTRO AL CASO 19");
if (derecha==0 && izquierda==1){
 
  if (digitalRead(FinalCD)==LOW){ //i
    motorRiel.write(90);
    delay(500);
    motorGarra.write(90);
    delay(500);
   regreso = 1;
    var=20;
  }
  else{
    motorRiel.write(180);
    }
  }

   
if (derecha==1 && izquierda==0){
 
  if (digitalRead(FinalCI)==LOW){ //D
    motorRiel.write(90);
    delay(500);
    motorGarra.write(90);
    delay(500);
    regreso = 1;
    var=20;
  }
  else{
    motorRiel.write(0);
    }
  }
  delay(500);
  break;

case 20:                         //// BAJA 
 digitalWrite(dirPin, LOW);
  for (int i = 0; i < 100 * stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);  
    
    Fin=digitalRead(fin);
    if (Fin==LOW){
     digitalWrite(ene, HIGH);
     delay(1000);
     estanteri = 0; 
      L=0;
      
      //derecha=0;
      //izquierda=0;3
      while (regreso == 1){
        Serial.write('r'); //ESTA PARTE SE LE AGREGO A LA VERSIÓN ANTERIOR
        regreso = 0;
        delay (3000);
        reset(); 
       // var = 21;  
    //   resetSoftware();
      }
       
      }
      else{
        digitalWrite(ene, LOW);
      }
  }
  

   break;
  
}
}

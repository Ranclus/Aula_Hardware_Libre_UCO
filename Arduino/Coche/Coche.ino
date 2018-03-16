#include <Servo.h>
#include <SoftwareSerial.h>

//**********************************************************
int luces=8; //Pin para las luces
int triguer=7; //Pin para el disparo del ultrasonidos
int adelante=6; //Pin para el avance del vehiculo
int retroceso=5; //Pin para el retroceso del vehiculo
int servomotor=3; //Pin para el servo del vehiculo
int recepcion_eco=A0; //Pin para recibir el eco del ultrasonidos

int TX=4; //Pin para transmitir datos del bluetooth
int RX=2; //Pin para recibir datos del bluetooth

SoftwareSerial Bluetooth(RX, TX); // Configuracion de los pines para el bluetooth
//**********************************************************

unsigned int eco=0; //Eco recibido del ultrasonido
float distancia=4.0; //Distancia medida por el ultrasonidos
float distancia_min=6.0; //Distancia a partir de la cual el coche no avanzara

char caracter; //Caracter leido actualmente desde el serial
String lectura=""; //Palabra completa recibida
boolean num=0; //Indica si se esta recibiendo un numero o no
unsigned long numero=0; //Valor numerico recibido

int luz=0; //Encendido o apagado de las luces del coche
int angulo=90; //Angulo del servo
int velocidad=0; //valor PWM para el motor
unsigned long tiempo=0; //Tiempo de ejecucion de las ordenes recividas en microsegundos
int anguloa=0; //Angulo del servo en automatico
int velocidada=0; //valor PWM para el motor en automatico


Servo giro; //Declaracion del servo

unsigned long retraso=0; //Tiempo de ejecucion del programa
unsigned long retraso_anterior=0; //Valor actual del micros()
unsigned long contu=0; //Servira para saber cuando hacer el disparo del ultrasonido
unsigned long retrasou=250000; //Tiempo entre disparos del ultrasonido en microsegundos
unsigned long conts=0; //Contador para el tiempo entre giros
unsigned long retrasos=5000; //Tiempo entre giros del servo en microsegundos
unsigned long conta=0; //Contador para el modo automatico

void setup() {
  
  pinMode(luces,OUTPUT); //Luces del coche
  pinMode(triguer,OUTPUT); //Disparo de sonido
  pinMode(adelante,OUTPUT); //Avance del coche
  pinMode(retroceso,OUTPUT); //Retroceso del coche
  giro.attach(servomotor); //Pin para el PWM del servo
  
  Serial.begin(9600); //Inicializacion del serial a 9600 baudios [caracteres/segundo]
  Bluetooth.begin(9600); //Inicializacion del serial para el bluetooth
}

void loop() {
  retraso_anterior=micros();

  if (Bluetooth.available()){ //Lectura de lo recibido a traves del puerto serie del bluetooth
    caracter=Bluetooth.read(); //Recepcion del caracter en el buffer serie del bluetooth (Solo se puede leer un caracter a la vez)
    if (caracter=='0' or caracter=='1' or caracter=='2' or caracter=='3' or caracter=='4' or caracter=='5' or caracter=='6' or caracter=='7' or caracter=='8' or caracter=='9'){
      if (lectura==""){
        //Para saber si se esta recibiendo un numero
        num=1;
      }
    }
    lectura=lectura+caracter; //Acumulacion de los caracteres recibidos
    if (caracter=='.'){ //'.' indica el fin de un dato cualquiera
      
      if (num==0){ //Si no es un numero
        if (lectura=="a."){ //Forzar la detencion del modo automatico
          conta=0;
        }
        if (lectura=="b."){ //Control de la luz del coche
          luz=1-luz;
          if (luz==0){
            digitalWrite(luces, LOW); //Apagado de las luces
          }
          if (luz==1){
            digitalWrite(luces, HIGH); //Encendido de las luces
          }
        }
      }
      if (num==1){ //Si es un numero
        numero=lectura.toInt(); //Conversion de la cadena de caracteres a numero (Int no se refiera al tipo de variable int)
        num=0;
        //Serial.print("Numero recibido: ");Serial.println(numero);
      }
      //Serial.print("Recibido: ");Serial.println(lectura);
      lectura="";
    }
    if (numero>=1 and numero<=181){ //Si el numero esta en ese rango, significa que es el valor del angulo
      angulo=numero-1; //Se resta 1 para tener el angulo
      //Serial.print("Angulo: ");Serial.println(angulo);
    }
    if (numero>=182 and numero<=692){ //Si el numero esta en ese rango, significa que es el valor de la velocidad
      velocidad=numero-437; //Se resta 437 para tener velocidad en un rango de -255 a 255
      //Serial.print("Velocidad: ");Serial.println(velocidad);
    }
    if (numero>=693 and numero<=873){ //Si el numero esta en ese rango, significa que es el valor del angulo en modo automatico
      anguloa=numero-693; //Se resta 693 para tener el angulo
      //Serial.print("Angulo automatico: ");Serial.println(anguloa);
    }
    if (numero>=874 and numero<=1384){ //Si el numero esta en ese rango, significa que es el valor de la velocidad en modo automatico
      velocidada=numero-1129; //Se resta 1129 para tener velocidad en un rango de -255 a 255
      //Serial.print("Velocidad automatica: ");Serial.println(velocidada);
    }
    if (numero>=1385){ //Si el numero esta en ese rango, significa que es el valor del tiempo en modo automatico
      conta=conta+1; //Da inicio al modo automatico
      tiempo=(numero-1385)*1000; //Se resta 1385 para tener el tiempo, y se multiplica por 1000 para tenerlo en microsegundos
      //Serial.print("Tiempo: ");Serial.println(tiempo);
    }
    numero=0;
  }
  
  if (conta>tiempo){ //El modo automatico a de finalizar
    conta=0;
    velocidad=0;
  }
  if (conta<=tiempo and conta>0){ //Si el modo automatico esta activo. reseteara los valores de angulo y velocidad con los del modo automatico
    velocidad=velocidada;
    angulo=anguloa;
    //Serial.println("AUTOMATICO");
  }
  
  if (contu>=retrasou){
    digitalWrite(triguer, HIGH); //Emision de ultrasonidos
    delayMicroseconds(12);
    digitalWrite(triguer, LOW); //Emitido 10 microsegundos
    eco=pulseIn(recepcion_eco, HIGH); //Recepcion del ultrasonido
    distancia=eco*0.0343/2; //Conversion del eco a centimetros
    Serial.println(distancia);
    contu=contu-retrasou; //Reseteo del contador del ultrasonidos
    //Serial.print("Eco: ");Serial.print(eco);Serial.print("  ");Serial.print("Distancia: ");Serial.print(distancia);Serial.println(" cm");
  }
  
  if (velocidad>0){ //El coche debera avanzar, aunque solo podra hacerlo si no tiene nada por delante a menos de 10 cm de distanc
    if (distancia<distancia_min){
      analogWrite(adelante,0);
    }
    else {
      analogWrite(adelante,velocidad);
    }
    analogWrite(retroceso,0);
  }
  if (velocidad<0){ //El coche debera retroceder
    analogWrite(adelante,0);
    analogWrite(retroceso,-velocidad);
  }
  if (velocidad==0){ //El coche debera parar
    analogWrite(adelante,0);
    analogWrite(retroceso,0);
  }
  if (conts>=retrasos){ //El giro se efectuara tras un determinado tiempo
    giro.write(angulo); //Angulo que girara el servo
    conts=conts-retrasos; //Reseteo del contador del servo
  }
  
  retraso=micros()-retraso_anterior; //Medicion del tiempo de ejecucion del programa en microsegundos
  contu=contu+retraso; //Avance para el contador del ultrasonido
  conts=conts+retraso; //Avance para el contador del servo
  if (conta>0){ //Avance para el contador del modo automatico si fuese necesario
    conta=conta+retraso;
  }
  //Serial.print("Tiempo de ejecucion de un ciclo del programa: ");Serial.print(retraso);Serial.println(" microsegundos");
}

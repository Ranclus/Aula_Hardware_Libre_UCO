const int sensorPIN = A0;     // ponemos A0 como entrada analÃ³gica del micrÃ³fono
const int sampleWindow = 150; // Ancho ventana en mS (50 mS = 20Hz)
int ledVerde = 3;
int ledAmarillo = 4;
int ledRojo = 5;
int peakToPeak;

int pin_potenc = A1;
int value;      //variable que almacena la lectura analógica raw
int posicion;   //posicion del potenciometro en tanto por ciento
 
void setup() 
{
   pinMode (3, OUTPUT);
   pinMode (4, OUTPUT);
   pinMode (5, OUTPUT);
   Serial.begin(9600);       //abrimos el monitor serial a 9600 baudios
}
 
int microfono() 
{
   unsigned long startMillis= millis();   //creamos la variable startMillis como unsigned(bits del signo no se utilizan) long
 
   unsigned int signalMax = 0;          //
   unsigned int signalMin = 1024;
 
   // Recopilar durante la ventana
    int sample;
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(sensorPIN);
      if (sample < 1024)
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // Actualizar mÃ¡ximo
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // Actualizar mÃ­nimo
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // Amplitud del sonido, incremento de señal
   //Serial.println(peakToPeak);
   return peakToPeak;
}

   int potenciometro ()
   {
   value = analogRead(pin_potenc);          // realizar la lectura analógica raw
   posicion = map(value, 0, 1023, 0, 100);  // convertir a porcentaje
   Serial.println(posicion);
   //...hacer lo que se quiera, con el valor de posición medido
 
   delay(200);
   return posicion;
   }

int minimo;
int maximo;

   void loop(){

   potenciometro();
   //50 y 100

   
   if (posicion<25){
    maximo=20;
    minimo=10;
   }
    if (posicion<50 and posicion>25){
    maximo=60;
    minimo=40;
   }
    if (posicion<75 and posicion>50){
    maximo=90;
    minimo=70;
   }
    if (posicion>75){
    maximo=200;
    minimo=150;
   }
   
   microfono();
   { 
   if (peakToPeak <= minimo)
   {
    microfono();
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledRojo, LOW);
    delay(250);
   }
   if (peakToPeak >= maximo)
   
   {
     microfono();
    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledVerde, LOW);
    delay(250);
    
   }

   if (minimo<peakToPeak and peakToPeak<maximo)
   {
    microfono();
    digitalWrite(ledAmarillo, HIGH);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRojo, LOW);
    delay(250);
   }
//   else
//    digitalWrite(ledAmarillo, LOW);
//    digitalWrite(ledVerde, LOW);
//    digitalWrite(ledRojo, LOW);
   
 //  }
   }
   }
   
    


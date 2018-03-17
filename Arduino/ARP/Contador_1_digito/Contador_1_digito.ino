//Usaremos un display de 7 segmentos para obtener una cuenta progresiva o regresiva segun la informacion de un boton
//Usar multiplo para la cuenta
int numero=0; //Numero que se mostrara en el display

byte estado_i; //Estado en el que se encuentra el boton izquierdo
byte estadoAnterior_i=LOW; //Estado en el que se encontraba el boton izquierdo
byte estado_c; //Estado en el que se encuentra el boton central
byte estadoAnterior_c=LOW; //Estado en el que se encontraba el boton central
byte estado_d; //Estado en el que se encuentra el boton derecho
byte estadoAnterior_d=LOW; //Estado en el que se encontraba el boton derecho

byte comportamiento=1; //Comportamiento=0, cuenta automatica, Comportamiento=1, cuenta manual
long espera=1000; //Intervalo en milisegundos para el paso de un numero a otro en la cuenta automatica
byte cuenta=0; //Cuenta=0, cuenta progresiva, Cuenta=1, cuenta regresiva
long cont=0; //Con esta variable se conseguira que la cuenta sea independiente de los botones

void setup() {
  // put your setup code here, to run once:
  pinMode(3, INPUT);   //Entrada boton izquierdo
  pinMode(4, INPUT);   //Entrada boton central
  pinMode(5, INPUT);   //Entrada boton derecho
  pinMode(6, OUTPUT);  //Segmento inferior izquierdo
  pinMode(7, OUTPUT);  //Segmento inferior
  pinMode(8, OUTPUT);  //Segmento central
  pinMode(9, OUTPUT);  //Segmento superior izquierdo
  pinMode(10, OUTPUT); //Segmento superior
  pinMode(11, OUTPUT); //Segmento superior derecho
  pinMode(12, OUTPUT); //Segmento inferior derecho
  pinMode(13, OUTPUT); //Segmento punto
}

void loop() {
  // put your main code here, to run repeatedly:

if (comportamiento==0) //El punto del display se encendera o apagara en funcion de si la cuenta es automatica o manual
{
  digitalWrite(13, LOW); //Cuenta automatica, por lo que el punto esta apagado
}
else{
  digitalWrite(13, HIGH); //Cuenta manual, por lo que el punto esta encendido
}

estado_c=digitalRead(4); //Lee el estado del boton central
if(estado_c==HIGH and estadoAnterior_c==LOW) //Sirve para cambiar entre la cuenta automatica y manual
  {
    comportamiento=1-comportamiento;
    if (comportamiento==0)
    {
      cont=0;
    }
    delay(20);
  }
estadoAnterior_c=estado_c;

estado_i=digitalRead(3); //Lee el estado del boton izquierdo
if(estado_i==HIGH and estadoAnterior_i==LOW) //Lee el estado del boton izquierdo
  {
    if(comportamiento==0) //Cuenta automatica
    {
      if(cuenta==0) //Cuenta progresiva, debera reducir el intervalo de paso entre digitos
      {
        espera=espera/2;
        if (espera==62) //Llegado a cierto punto, la cuenta pasara de progresiva a regresiva
        {
          cuenta=1;
          espera=125;
        }
      }
      else{
        espera=espera*2; //Cuando la cuenta pase a regresiva, aumentara el intervalo de paso entre digitos
      }
    }
    else{
      numero=numero-1; //En la cuenta manual, reducira en una unidad el numero actual
    }
  delay(20);
  }
estadoAnterior_i=estado_i;

estado_d=digitalRead(5); //Lee el estado del boton central
if(estado_d==HIGH and estadoAnterior_d==LOW)
  {
    if(comportamiento==0)
    {
      if (cuenta==0) //Cuenta progresiva, debera aumentar el intervalo de paso entre digitos
      {
        espera=espera*2;
      }
      else{
        espera=espera/2; //Cuando la cuenta pase a progresiva, redurira el intervalo de paso entre digitos
        if (espera==62) //Llegado a cierto punto, la cuenta pasara de regresiva a progresiva
        {
          cuenta=0;
          espera=125;
        }
      }
    }
    else{
      numero=numero+1; //En la cuenta manual, aumentara en una unidad el numero actual
    }
  delay(20);
  }
estadoAnterior_d=estado_d;

if (numero==-1) //La variable "numero" solo puede llegar a -1 en una cuenta regresiva, por lo que el valor siguiente sera 9
{
  numero=9;
}
if (numero==10) //La variable "numero" solo puede llegar a 10 en una cuenta progresiva, por lo que el valor siguiente sera 0
{
  numero=0;
}

if (numero==0) //Encendemos los segmentos necesarios para mostrar en el display el numero 0
{
  digitalWrite(6, HIGH);  //Segmento inferior izquierdo
  digitalWrite(7, HIGH);  //Segmento inferior
  digitalWrite(8, LOW);  //Segmento central
  digitalWrite(9, HIGH);  //Segmento superior izquierdo
  digitalWrite(10, HIGH); //Segmento superior
  digitalWrite(11, HIGH); //Segmento superior derecho
  digitalWrite(12, HIGH); //Segmento inferior derecho
}
if (numero==1) //Encendemos los segmentos necesarios para mostrar en el display el numero 1
{
  digitalWrite(6, LOW);  //Segmento inferior izquierdo
  digitalWrite(7, LOW);  //Segmento inferior
  digitalWrite(8, LOW);  //Segmento central
  digitalWrite(9, LOW);  //Segmento superior izquierdo
  digitalWrite(10, LOW); //Segmento superior
  digitalWrite(11, HIGH); //Segmento superior derecho
  digitalWrite(12, HIGH); //Segmento inferior derecho
}
if (numero==2) //Encendemos los segmentos necesarios para mostrar en el display el numero 2
{
  digitalWrite(6, HIGH);  //Segmento inferior izquierdo
  digitalWrite(7, HIGH);  //Segmento inferior
  digitalWrite(8, HIGH);  //Segmento central
  digitalWrite(9, LOW);  //Segmento superior izquierdo
  digitalWrite(10, HIGH); //Segmento superior
  digitalWrite(11, HIGH); //Segmento superior derecho
  digitalWrite(12, LOW); //Segmento inferior derecho
}
if (numero==3) //Encendemos los segmentos necesarios para mostrar en el display el numero 3
{
  digitalWrite(6, LOW);  //Segmento inferior izquierdo
  digitalWrite(7, HIGH);  //Segmento inferior
  digitalWrite(8, HIGH);  //Segmento central
  digitalWrite(9, LOW);  //Segmento superior izquierdo
  digitalWrite(10, HIGH); //Segmento superior
  digitalWrite(11, HIGH); //Segmento superior derecho
  digitalWrite(12, HIGH); //Segmento inferior derecho
}
if (numero==4) //Encendemos los segmentos necesarios para mostrar en el display el numero 4
{
  digitalWrite(6, LOW);  //Segmento inferior izquierdo
  digitalWrite(7, LOW);  //Segmento inferior
  digitalWrite(8, HIGH);  //Segmento central
  digitalWrite(9, HIGH);  //Segmento superior izquierdo
  digitalWrite(10, LOW); //Segmento superior
  digitalWrite(11, HIGH); //Segmento superior derecho
  digitalWrite(12, HIGH); //Segmento inferior derecho
}
if (numero==5) //Encendemos los segmentos necesarios para mostrar en el display el numero 5
{
  digitalWrite(6, LOW);  //Segmento inferior izquierdo
  digitalWrite(7, HIGH);  //Segmento inferior
  digitalWrite(8, HIGH);  //Segmento central
  digitalWrite(9, HIGH);  //Segmento superior izquierdo
  digitalWrite(10, HIGH); //Segmento superior
  digitalWrite(11, LOW); //Segmento superior derecho
  digitalWrite(12, HIGH); //Segmento inferior derecho
}
if (numero==6) //Encendemos los segmentos necesarios para mostrar en el display el numero 6
{
  digitalWrite(6, HIGH);  //Segmento inferior izquierdo
  digitalWrite(7, HIGH);  //Segmento inferior
  digitalWrite(8, HIGH);  //Segmento central
  digitalWrite(9, HIGH);  //Segmento superior izquierdo
  digitalWrite(10, HIGH); //Segmento superior
  digitalWrite(11, LOW); //Segmento superior derecho
  digitalWrite(12, HIGH); //Segmento inferior derecho
}
if (numero==7) //Encendemos los segmentos necesarios para mostrar en el display el numero 7
{
  digitalWrite(6, LOW);  //Segmento inferior izquierdo
  digitalWrite(7, LOW);  //Segmento inferior
  digitalWrite(8, LOW);  //Segmento central
  digitalWrite(9, LOW);  //Segmento superior izquierdo
  digitalWrite(10, HIGH); //Segmento superior
  digitalWrite(11, HIGH); //Segmento superior derecho
  digitalWrite(12, HIGH); //Segmento inferior derecho
}
if (numero==8) //Encendemos los segmentos necesarios para mostrar en el display el numero 8
{
  digitalWrite(6, HIGH);  //Segmento inferior izquierdo
  digitalWrite(7, HIGH);  //Segmento inferior
  digitalWrite(8, HIGH);  //Segmento central
  digitalWrite(9, HIGH);  //Segmento superior izquierdo
  digitalWrite(10, HIGH); //Segmento superior
  digitalWrite(11, HIGH); //Segmento superior derecho
  digitalWrite(12, HIGH); //Segmento inferior derecho
}
if (numero==9) //Encendemos los segmentos necesarios para mostrar en el display el numero 9
{
  digitalWrite(6, LOW);  //Segmento inferior izquierdo
  digitalWrite(7, LOW);  //Segmento inferior
  digitalWrite(8, HIGH);  //Segmento central
  digitalWrite(9, HIGH);  //Segmento superior izquierdo
  digitalWrite(10, HIGH); //Segmento superior
  digitalWrite(11, HIGH); //Segmento superior derecho
  digitalWrite(12, HIGH); //Segmento inferior derecho
}

if (comportamiento==0) //Cuando la cuenta sea automatica, el contador debera sumar una unidad en cada ciclo
{
  cont=cont+1;
  if (cont==espera) //Reseteamos el valor de la variable "cont" cuando se iguale a la variable "espera", puesto que ya habria cumplido su cometido, y asi no usamos memoria innecesariamente
  {
    cont=0;
    if (cuenta==0) //Cuando la cuenta sea progresiva, debera aumentar en una unidad el numero mostrado en el display
    {
      numero=numero+1;
    }
    else{ //Cuando la cuenta sea progresiva, debera reducir en una unidad el numero mostrado en el display
      numero=numero-1;
    }
  }
if (cont>espera) //Cuando cambiamos el intervalo de paso entre digitos, la variable "cont" y "espera" ya no pueden igualarse, o no lo hara adecuadamente, por lo que se corrige de esta manera
{
  cont=0;
}
if (espera<62) //Si la variable "espera" baja por debajo de lo programado, se corregira su valor
{
  espera=125;
}
}

delay(1); //Cada ciclo debe durar un milisegundo para que los intervalos entre digitos se lleven adecuadamente
}

//Usando un LDR haremos que 3 LEDs graduen su nivel de brillo en funcion de la luz del ambiente

//A continuacion se declararan las variables que se usaran durante la ejecucion del programa. "int" para enteros, "float" para reales, etc
int n;                  //Numero de repeticiones que hace la placa en el "void loop"
float valor_inicial;    //Primera lectura procedente del LDR. Se usara para que los LEDs graduen su brillo desde el minimo al maximo posibles
float lecturaLDR;       //Dato proveniente del LDR en el "void loop"
float nivel_luz;        //Proporcion de luz actual con respecto al nivel original, conocido gracias a la variable "valor_inicial"
float luz;              //Intensidad de brillo con el que se encenderan los LEDs
int comportamiento;     //Indica lo que hara la placa. Si comportamiento=0, a mayor luz, mayor intensidad de brillo en los LEDs, si comportamiento=1, a mayor luz, menor intensidad de brillo en los LEDs
int estado;             //Estado en el que se encuentra el boton. Si es 0, o LOW, esta abierto, si es 1, o HIGH, esta cerrado
int estadoAnterior=LOW; //Estado anterior del boton. El estado siguiente a este, corresponde con la variable "estado"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Iniciamos una pantalla en donde se mostraran los datos que elijamos recopilar desde el puerto USB
  valor_inicial=analogRead(0); //Hace una primera lectura en el pin A0
  Serial.println(valor_inicial); //Imprime por pantalla el valor de esta variable, y despues hace un salto de linea
  pinMode(9, OUTPUT); //Definimos un pin de salida
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(8, INPUT);
  n=0; //Asignamos a esta variable un valor
  comportamiento=0;
}

void loop() {
  // put your main code here, to run repeatedly:
lecturaLDR=analogRead(0); //Asignamos a esta variable la lectura en el pin A0
nivel_luz=lecturaLDR/valor_inicial; //Asignamos en esta variable el resultado de esta operacion
n=n+1;

Serial.print("Lectura numero: ");Serial.println(n);Serial.print("Lectura LDR: ");Serial.println(lecturaLDR);Serial.print("Nivel de luz respecto al original: ");Serial.print(nivel_luz*100);Serial.println("%");Serial.print("Valor LED: ");Serial.println(luz);Serial.println("");

//Importante recordar en los esquemas "if" poner las condiciones entre parentesis"()", y lo que pasa cuando ocurren, entre llaves"{}"
if (nivel_luz>=1) //Si la lectura del LDR es superior a la original, se considerara un nivel de luz maximo
  {
    nivel_luz=1;
  }
if (nivel_luz<=0) //Si la lectura del LDR es inferior a la original, se considerara un nivel de luz minimo
  {
    nivel_luz=0;
  }

estado=digitalRead(8); //Asignamos a esta variable la lectura en el pin 8
if (estado==HIGH and estadoAnterior==LOW) //Si se cierra el circuito con el boton, y antes estaba abierto, hara la siguiente operacion
  {
    comportamiento=1-comportamiento;
  delay(20); //La placa no hara nada durante 20 milisegundos, por lo que se anulara el efecto del rebote en el boton
  }
estadoAnterior=estado;

if (comportamiento==0) //Comportamiento de la placa cuando comportamiento=0
{
luz=1023*(nivel_luz);
if (nivel_luz>=0 and nivel_luz<0.33)
  {
    analogWrite(9, luz);
    analogWrite(10, LOW);
    analogWrite(11, LOW);
  }
if (nivel_luz>=0.33 and nivel_luz<0.66)
  {
    analogWrite(9, luz);
    analogWrite(10, luz);
    analogWrite(11, LOW);
  }
if (nivel_luz>=0.66 and nivel_luz<=1)
  {
    analogWrite(9, luz);
    analogWrite(10, luz);
    analogWrite(11, luz);
  }
}

if (comportamiento==1) //Comportamiento de la placa cuando comportamiento=1
{
luz=1023*(1-nivel_luz);

if (nivel_luz>=0 and nivel_luz<0.33)
  {
    analogWrite(9, luz);
    analogWrite(10, luz);
    analogWrite(11, luz);
  }
if (nivel_luz>=0.33 and nivel_luz<0.66)
  {
    analogWrite(9, luz);
    analogWrite(10, luz);
    analogWrite(11, LOW);
  }
if (nivel_luz>=0.66 and nivel_luz<=1)
  {
    analogWrite(9, luz);
    analogWrite(10, LOW);
    analogWrite(11, LOW);
  }
}
//delay(1000); //Util para tomar datos
}

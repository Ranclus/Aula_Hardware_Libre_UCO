int numero; //Numero mostrado en un instante
int numero1=0; //Numero para el primer digito, es decir, unidad de millar en contador
int numero2=0; //Numero para el segundo digito, es decir, centenas en contador
int numero3=0; //Numero para el tercer digito, es decir, decenas en contador
int numero4=0; //Numero para el cuarto digito, es decir, unidades en contador
byte numeroDisplay[]={numero1,numero2,numero3,numero4}; //Vector con los numeros para el display en contador
byte i=0; //Numero de elemento en la variable numeroDisplay
byte j=0; //Para mostrar horas y minutos, o minutos y segundos
int r1=2; //Numero para las decenas de las horas
int r2=3; //Numero para las unidades de las horas
int r3=5; //Numero para las decenas de los minutos
int r4=9; //Numero para las unidades de los minutos
int r5=5; //Numero para las decenas de los segundos
int r6=5; //Numero para las unidades de los segundos
byte reloj[]={r1,r2,r3,r4,r5,r6}; //Vector con los numeros de la hora
byte hm=2; //hm=0, mostrara horas y minutos, hm=2, mostrara minutos y segundos

int a1=2; //Numero para las decenas de las horas en la alarma
int a2=0; //Numero para las unidades de las horas en la alarma
int a3=0; //Numero para las decenas de los minutos en la alarma
int a4=0; //Numero para las unidades de los minutos en la alarma
int a5=0; //Numero para las decenas de los segundos en la alarma
int a6=0; //Numero para las unidades de los segundos en la alarma
byte n_alarma[]={a1,a2,a3,a4,a5,a6}; //Vector con los numeros de la alarma
long cont_parpadeo=0; //Contador para el parpadeo de los numeros en la alarma
long conta=0; //Contador para la alarma
byte alarma=0; //0=alarma desactivada, 1=alarma activada

long contr=0; //Contador para el reloj

byte modo=0; //0=modo automatica, 1=modo manual
unsigned long micros_anterior=micros(); //Valor del micro al inicio de un ciclo
unsigned long retraso; //Tiempo de ejecucion de un ciclo
long cont=0; //Medidor de tiempo
byte comportamiento=1; //0=contador, 1=reloj, 2=cambiar la hora
byte seleccion=4; //Discernira entre los digitos que se cambiaran cuando modo=1,comportamiento=0
byte cuenta=0; //0=cuenta progresiva, 1=cuenta regresiva
long espera[]={0,1000,62500,125000,250000,500000,1000000,2000000,4000000,8000000,16000000,32000000,64000000,128000000};
int tiempo=6; //Numero de elemento en la variable espera

int estado_i; //Estado del boton izquierdo
int estado_A_i=LOW; //Estado anterior del boton izquierdo
int estado_c; //Estado del boton central
int estado_A_c=LOW; //Estado anterior del boton central
int estado_d; //Estado del boton derecho
int estado_A_d=LOW; //Estado anterior del boton derecho

byte clik_I=0; //Numero de cliks del boton izquierdo
long contc_I=0; //Contador para el click izquierdo
byte clik_C=0; //Numero de cliks del boton central
long contc_C=0; //Contador para el click central
byte clik_D=0; //Numero de cliks del boton derecho
long contc_D=0; //Contador para el click derecho
long cont00=0; //contador para el modo=0,comportamiento=0

void setup() {

pinMode(2,OUTPUT); //Primer digito
pinMode(3,OUTPUT); //Segundo digito
pinMode(4,OUTPUT); //Tercer digito
pinMode(5,OUTPUT); //Cuarto digito

pinMode(6,OUTPUT); //Superior derecho
pinMode(7,OUTPUT); //Superior izquierdo
pinMode(8,OUTPUT); //Superior
pinMode(9,OUTPUT); //Central
pinMode(10,OUTPUT); //Inferior derecho
pinMode(11,OUTPUT); //Punto
pinMode(12,OUTPUT); //Inferior
pinMode(13,OUTPUT); //Inferior izquierdo

pinMode(A5,OUTPUT); //LED, o zumbador
//Serial.begin(9600);
retraso=micros()-micros_anterior;
}

void loop() {

micros_anterior=micros();
estado_i=analogRead(A0); //Lee el boton izquierdo

//Para una entrada digital es facil leer un boton, pues solo tiene el estado HIGH o LOW. En una entrada analogica en cambio, solo sabes que es distinto de LOW cuando pulsas el boton

if (estado_i!=LOW and estado_A_i==LOW) //Control con el boton izquierdo
{
  contc_I=1;
  clik_I=clik_I+1;
delay(20);
}

estado_A_i=estado_i;

if (contc_I==0 and clik_I>0) //Acciones por el boton izquierdo
{
  if (modo==0)
  {
    if (comportamiento==0)
    {
      if (cuenta==1)
      {
        tiempo=tiempo+clik_I;
        if (tiempo>=14)
        {
          tiempo=13;
          cont00=1;
        }
      }
      if (cuenta==0)
      {
        tiempo=tiempo-clik_I;
        if (tiempo<=-1)
        {
          cuenta=1;
          tiempo=-1-tiempo;
        }
      }
    }
    if (comportamiento==1)
    {
      if (clik_I!=0)
      {
        hm=0;
      }
    }
  }
  if (modo==1)
  {
    if (comportamiento==0)
    {
      if (clik_I==1)
      {
        if (seleccion==4)
        {
          numero4=numero4-1;
        }
        if (seleccion==3)
        {
          numero3=numero3-1;
        }
        if (seleccion==2)
        {
          numero2=numero2-1;
        }
        if (seleccion==1)
        {
          numero1=numero1-1;
        }
      }
      else{
        seleccion=seleccion-1;
        if (seleccion==0)
        {
          seleccion=4;
        }
      }
    }
    if (comportamiento==1)
    {
      if (clik_I==1)
      {
        if (seleccion==6)
        {
          a6=a6-1;
        }
        if (seleccion==5)
        {
          a5=a5-1;
        }
        if (seleccion==4)
        {
          a4=a4-1;
        }
        if (seleccion==3)
        {
          a3=a3-1;
        }
        if (seleccion==2)
        {
          a2=a2-1;
        }
        if (seleccion==1)
        {
          a1=a1-1;
        }
      }
      else{
        seleccion=seleccion-1;
        if (seleccion==0)
        {
          seleccion=6;
        }
      }
    }
    if (comportamiento==2)
    {
      if (clik_I==1)
      {
        if (seleccion==6)
        {
          r6=0;
        }
        if (seleccion==5)
        {
          r5=r5-1;
        }
        if (seleccion==4)
        {
          r4=r4-1;
        }
        if (seleccion==3)
        {
          r3=r3-1;
        }
        if (seleccion==2)
        {
          r2=r2-1;
        }
        if (seleccion==1)
        {
          r1=r1-1;
        }
      }
      else{
        seleccion=seleccion-1;
        if (seleccion==0)
        {
          seleccion=6;
        }
      }
    }
  }
  clik_I=0;
}

estado_c=analogRead(A1); //Lee el boton central

if (estado_c!=LOW and estado_A_c==LOW) //Control con el boton central
{
  contc_C=1;
  clik_C=clik_C+1;
  
delay(20);
}

estado_A_c=estado_c;

if (contc_C==0 and clik_C>0) //Acciones por el boton central
{
  if (clik_C==1 and conta==0)
  {
    modo=1-modo;
    cont_parpadeo=0;
    if (modo==0 and comportamiento==0)
    {
      digitalWrite(11, LOW);
      seleccion=4;
    }
    if (modo==1 and comportamiento==0)
    {
      digitalWrite(11, HIGH);
    }
    if (comportamiento==1)
    {
      seleccion=1;
      if (modo==1)
      {
        cont_parpadeo=1;
        hm=0;
      }
      if (modo==0)
      {
        cont_parpadeo=0;
        hm=2;
      }
    }
  }
  if (clik_C==2 and conta==0)
  {
    comportamiento=0; //Cambia a contador
    modo=1;
    seleccion=4;
    cont_parpadeo=0;
  }
  if (clik_C==3 and conta==0) //Cambia a reloj
  {
    comportamiento=1;
    modo=0;
    cont_parpadeo=0;
  }
  if (clik_C==4 and conta==0) //Cambia a cambiar la hora
  {
    comportamiento=2;
    modo=1;
    seleccion=1;
    cont_parpadeo=1;
  }
  conta=0;
  digitalWrite(A5, LOW);
  clik_C=0;
}

estado_d=analogRead(A2); //Lee el boton derecho

if (estado_d!=LOW and estado_A_d==LOW) //Control con el boton derecho
{
  contc_D=1;
  clik_D=clik_D+1;
delay(20);
}
estado_A_d=estado_d;

if (contc_D==0 and clik_D>0) //Acciones por el boton derecho
{
  if (modo==0)
  {
    if (comportamiento==0)
    {
      if (cuenta==0)
      {
        tiempo=tiempo+clik_D;
        if (tiempo>=14)
        {
          tiempo=13;
          cont00=1;
        }
      }
      if (cuenta==1)
      {
        tiempo=tiempo-clik_D;
        if (tiempo<=-1)
        {
          tiempo=-1-tiempo;
          cuenta=0;
        }
      }
    }
    if (comportamiento==1)
    {
      if (clik_D!=0)
      {
        hm=2;
      }
    }
  }
  if (modo==1)
  {
    if (comportamiento==0)
    {
      if (clik_D==1)
      {
        if (seleccion==4)
        {
          numero4=numero4+1;
        }
        if (seleccion==3)
        {
          numero3=numero3+1;
        }
        if (seleccion==2)
        {
          numero2=numero2+1;
        }
        if (seleccion==1)
        {
          numero1=numero1+1;
        }
      }
      else{
        seleccion=seleccion+1;
        if (seleccion==5)
        {
          seleccion=1;
        }
      }
    }
    if (comportamiento==1)
    {
      if (clik_D==1)
      {
        if (seleccion==6)
        {
          a6=a6+1;
        }
        if (seleccion==5)
        {
          a5=a5+1;
        }
        if (seleccion==4)
        {
          a4=a4+1;
        }
        if (seleccion==3)
        {
          a3=a3+1;
        }
        if (seleccion==2)
        {
          a2=a2+1;
        }
        if (seleccion==1)
        {
          a1=a1+1;
        }
      }
      else{
        seleccion=seleccion+1;
        if (seleccion==7)
        {
          seleccion=1;
        }
      }
    }
    if (comportamiento==2)
    {
      if (clik_D==1)
      {
        if (seleccion==6)
        {
          r6=0;
        }
        if (seleccion==5)
        {
          r5=r5+1;
        }
        if (seleccion==4)
        {
          r4=r4+1;
        }
        if (seleccion==3)
        {
          r3=r3+1;
        }
        if (seleccion==2)
        {
          r2=r2+1;
        }
        if (seleccion==1)
        {
          r1=r1+1;
        }
      }
      else{
        seleccion=seleccion+1;
        if (seleccion==7)
        {
          seleccion=1;
        }
      }
    }
  }
  clik_D=0;
}

numeroDisplay[0]=numero1;
numeroDisplay[1]=numero2;
numeroDisplay[2]=numero3;
numeroDisplay[3]=numero4;
//Me aseguro de que el numero se muestre como debe
if (comportamiento==0)
{
  if (numero4==10)
  {
    numero4=0;
    numero3=numero3+1;
  }
  if (numero3==10)
  {
    numero3=0;
    numero2=numero2+1;
  }
  if (numero2==10)
  {
    numero2=0;
    numero1=numero1+1;
  }
  if (numero1==10)
  {
    numero1=0;
  }
  
  if (numero4==-1)
  {
    numero4=9;
    numero3=numero3-1;
  }
  if (numero3==-1)
  {
    numero3=9;
    numero2=numero2-1;
  }
  if (numero2==-1)
  {
    numero2=9;
    numero1=numero1-1;
  }
  if (numero1==-1)
  {
    numero1=9;
  }
}
reloj[0]=r1;
reloj[1]=r2;
reloj[2]=r3;
reloj[3]=r4;
reloj[4]=r5;
reloj[5]=r6;
//Correcciones para el numero del reloj
if (r6==10)
{
  r6=0;
  r5=r5+1;
}
if (r5==6)
{
  r5=0;
  r4=r4+1;
}
if (r4==10)
{
  r4=0;
  r3=r3+1;
}
if (r3==6)
{
  r3=0;
  r2=r2+1;
}
if (r2==10)
{
  r2=0;
  r1=r1+1;
}
if (r1==2 and r2==4)
{
  r1=0;
  r2=0;
}
if (r1==3)
{
  r1=0;
}
 
if (r6==-1)
{
  r6=9;
  r5=r5-1;
}
if (r5==-1)
{
  r5=5;
  r4=r4-1;
}
if (r4==-1)
{
  r4=9;
  r3=r3-1;
}
if (r3==-1)
{
  r3=5;
  r2=r2-1;
}
if (r2==-1)
{
  r2=9;
  r1=r1-1;
}
if (r1==-1)
{
  r1=2;
  r2=3;
}
n_alarma[0]=a1;
n_alarma[1]=a2;
n_alarma[2]=a3;
n_alarma[3]=a4;
n_alarma[4]=a5;
n_alarma[5]=a6;
//Correccion para los numeros de la alarma
if (a6==10)
{
  a6=0;
  a5=a5+1;
}
if (a5==6)
{
  a5=0;
  a4=a4+1;
}
if (a4==10)
{
  a4=0;
  a3=a3+1;
}
if (a3==6)
{
  a3=0;
  a2=a2+1;
}
if (a2==10)
{
  a2=0;
  a1=a1+1;
}
if (a1==2 and a2==4)
{
  a1=0;
  a2=0;
}
if (a1==3)
{
  a1=0;
}
 
if (a6==-1)
{
  a6=9;
  a5=a5-1;
}
if (a5==-1)
{
  a5=5;
  a4=a4-1;
}
if (a4==-1)
{
  a4=9;
  a3=a3-1;
}
if (a3==-1)
{
  a3=5;
  a2=a2-1;
}
if (a2==-1)
{
  a2=9;
  a1=a1-1;
}
if (a1==-1)
{
  a1=2;
  a2=3;
}

if (conta>0) //Condicional para cuando la alarma este activa, tres HIGH por segundo hasta que se apague la alarma
{
  conta=conta+retraso;
  if (alarma==1)
  {
    if (conta>0 and conta<=83333)
    {
      digitalWrite(A5, 1023);
    }
    if (conta>83333 and conta<=166667)
    {
      digitalWrite(A5, 0);
    }
    if (conta>250000 and conta<=333333)
    {
      digitalWrite(A5, 1023);
    }
    if (conta>333333 and conta<=416667)
    {
      digitalWrite(A5, 0);
    }
    if (conta>416667 and conta<=500000)
    {
      digitalWrite(A5, 1023);
    }
    if (conta>500000 and conta<=1000000)
    {
      digitalWrite(A5, 0);
    }
    if (conta>1000000)
    {
      conta=1;
    }
  }
  else{
    conta=0;
    digitalWrite(A5, LOW);
  }
}
if (a1==r1 and a2==r2 and a3==r3 and a4==r4 and a5==r5 and a6==r6) //Comprueba si la alarma ha de activarse
{
  conta=1;
  alarma=1;
}

//Hago que se muestre el numero en el display
while (i<4)
{
  if (comportamiento==0) //Numeros del contador
  {
    numero=numeroDisplay[i];
  }
  if (comportamiento==1 and modo==0) //Numeros del reloj
  {
    j=i+hm;
    numero=reloj[j];
  }
  if (comportamiento==1 and modo==1) //Numeros de la alarma
  {
    if (seleccion<=4)
    {
      hm=0;
    }
    else{
      hm=2;
    }
    j=i+hm;
    numero=n_alarma[j];
  }
  if (comportamiento==2 and modo==1) //Numeros de cambiar la hora
  {
    if (seleccion<=4)
    {
      hm=0;
    }
    else{
      hm=2;
    }
    j=i+hm;
    numero=reloj[j];
  }
if (numero==0) //Encendemos los segmentos necesarios para mostrar en el display el numero 0
{
  digitalWrite(13, HIGH);  //Segmento inferior izquierdo
  digitalWrite(12, HIGH);  //Segmento inferior
  digitalWrite(9, LOW);  //Segmento central
  digitalWrite(7, HIGH);  //Segmento superior izquierdo
  digitalWrite(8, HIGH); //Segmento superior
  digitalWrite(6, HIGH); //Segmento superior derecho
  digitalWrite(10, HIGH); //Segmento inferior derecho
}
if (numero==1) //Encendemos los segmentos necesarios para mostrar en el display el numero 1
{
  digitalWrite(13, LOW);  //Segmento inferior izquierdo
  digitalWrite(12, LOW);  //Segmento inferior
  digitalWrite(9, LOW);  //Segmento central
  digitalWrite(7, LOW);  //Segmento superior izquierdo
  digitalWrite(8, LOW); //Segmento superior
  digitalWrite(6, HIGH); //Segmento superior derecho
  digitalWrite(10, HIGH); //Segmento inferior derecho
}
if (numero==2) //Encendemos los segmentos necesarios para mostrar en el display el numero 2
{
  digitalWrite(13, HIGH);  //Segmento inferior izquierdo
  digitalWrite(12, HIGH);  //Segmento inferior
  digitalWrite(9, HIGH);  //Segmento central
  digitalWrite(7, LOW);  //Segmento superior izquierdo
  digitalWrite(8, HIGH); //Segmento superior
  digitalWrite(6, HIGH); //Segmento superior derecho
  digitalWrite(10, LOW); //Segmento inferior derecho
}
if (numero==3) //Encendemos los segmentos necesarios para mostrar en el display el numero 3
{
  digitalWrite(13, LOW);  //Segmento inferior izquierdo
  digitalWrite(12, HIGH);  //Segmento inferior
  digitalWrite(9, HIGH);  //Segmento central
  digitalWrite(7, LOW);  //Segmento superior izquierdo
  digitalWrite(8, HIGH); //Segmento superior
  digitalWrite(6, HIGH); //Segmento superior derecho
  digitalWrite(10, HIGH); //Segmento inferior derecho
}
if (numero==4) //Encendemos los segmentos necesarios para mostrar en el display el numero 4
{
  digitalWrite(13, LOW);  //Segmento inferior izquierdo
  digitalWrite(12, LOW);  //Segmento inferior
  digitalWrite(9, HIGH);  //Segmento central
  digitalWrite(7, HIGH);  //Segmento superior izquierdo
  digitalWrite(8, LOW); //Segmento superior
  digitalWrite(6, HIGH); //Segmento superior derecho
  digitalWrite(10, HIGH); //Segmento inferior derecho
}
if (numero==5) //Encendemos los segmentos necesarios para mostrar en el display el numero 5
{
  digitalWrite(13, LOW);  //Segmento inferior izquierdo
  digitalWrite(12, HIGH);  //Segmento inferior
  digitalWrite(9, HIGH);  //Segmento central
  digitalWrite(7, HIGH);  //Segmento superior izquierdo
  digitalWrite(8, HIGH); //Segmento superior
  digitalWrite(6, LOW); //Segmento superior derecho
  digitalWrite(10, HIGH); //Segmento inferior derecho
}
if (numero==6) //Encendemos los segmentos necesarios para mostrar en el display el numero 6
{
  digitalWrite(13, HIGH);  //Segmento inferior izquierdo
  digitalWrite(12, HIGH);  //Segmento inferior
  digitalWrite(9, HIGH);  //Segmento central
  digitalWrite(7, HIGH);  //Segmento superior izquierdo
  digitalWrite(8, HIGH); //Segmento superior
  digitalWrite(6, LOW); //Segmento superior derecho
  digitalWrite(10, HIGH); //Segmento inferior derecho
}
if (numero==7) //Encendemos los segmentos necesarios para mostrar en el display el numero 7
{
  digitalWrite(13, LOW);  //Segmento inferior izquierdo
  digitalWrite(12, LOW);  //Segmento inferior
  digitalWrite(9, LOW);  //Segmento central
  digitalWrite(7, LOW);  //Segmento superior izquierdo
  digitalWrite(8, HIGH); //Segmento superior
  digitalWrite(6, HIGH); //Segmento superior derecho
  digitalWrite(10, HIGH); //Segmento inferior derecho
}
if (numero==8) //Encendemos los segmentos necesarios para mostrar en el display el numero 8
{
  digitalWrite(13, HIGH);  //Segmento inferior izquierdo
  digitalWrite(12, HIGH);  //Segmento inferior
  digitalWrite(9, HIGH);  //Segmento central
  digitalWrite(7, HIGH);  //Segmento superior izquierdo
  digitalWrite(8, HIGH); //Segmento superior
  digitalWrite(6, HIGH); //Segmento superior derecho
  digitalWrite(10, HIGH); //Segmento inferior derecho
}
if (numero==9) //Encendemos los segmentos necesarios para mostrar en el display el numero 9
{
  digitalWrite(13, LOW);  //Segmento inferior izquierdo
  digitalWrite(12, LOW);  //Segmento inferior
  digitalWrite(9, HIGH);  //Segmento central
  digitalWrite(7, HIGH);  //Segmento superior izquierdo
  digitalWrite(8, HIGH); //Segmento superior
  digitalWrite(6, HIGH); //Segmento superior derecho
  digitalWrite(10, HIGH); //Segmento inferior derecho
}

if (i==0) //Estamos en el primer digito
{
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
if (cont_parpadeo>0 and cont_parpadeo<=500000) //El numero correspondiente parpadeara cuando se este poniendo la alarma o cambiando la hora
{
  if (seleccion==1 and hm==0 or seleccion==3 and hm==2)
  {
    digitalWrite(2,HIGH);
  }
}
if (cont00!=0) //Cuando el valor de la espera sea maximo, y se quiera subir , se iluminaran los puntos para indicar que no se puede incrementar
{
  if (cont00>=1 and cont00<62500)
  {
    digitalWrite(11, HIGH);
    delay(3);
  }
  if (cont00>=62500 and cont00<125000)
  {
    digitalWrite(11, LOW);
    delay(3);
  }
  if (cont00>=125000 and cont00<187500)
  {
    digitalWrite(11, HIGH);
    delay(3);
  }
  if (cont00>=187500 and cont00<250000)
  {
    digitalWrite(11, LOW);
    delay(3);
  }
}
if (seleccion==1 and modo==1 and comportamiento==0) //Se apagara el punto para indicar que numero estas cambiando en el contador manual
{
  digitalWrite(11, LOW);
}
if (seleccion!=1 and modo==1 and comportamiento==0) //Si no estas cambiando este numero, el punto estara iluminado en el contador manual
{
  digitalWrite(11, HIGH);
}
if (hm==0 and comportamiento==1 or hm==0 and comportamiento==2) //Se apagara el punto para indicar que este numero corresponde a las horas
{
  digitalWrite(11,LOW);
}
if (hm==2 and comportamiento==1 or hm==2 and comportamiento==2) //Se encendera este punto para indicar que este numero corresponde a los minutos
{
  digitalWrite(11,HIGH);
}
  delay(3); //Este delay es importante, ya que es el que hace que se vea como debe el numero en el display
}
if (i==1) //Estamos en el segundo digito)
{
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
if (cont_parpadeo>0 and cont_parpadeo<=500000) //El numero correspondiente parpadeara cuando se este poniendo la alarma o cambiando la hora
{
  if (seleccion==2 and hm==0 or seleccion==4 and hm==2)
  {
    digitalWrite(3,HIGH);
  }
}
if (seleccion==2 and modo==1 and comportamiento==0) //Se apagara el punto para indicar que numero estas cambiando en el contador manual
{
  digitalWrite(11, LOW);
}
if (seleccion!=2 and modo==1 and comportamiento==0) //Si no estas cambiando este numero, el punto estara iluminado en el contador manual
{
  digitalWrite(11, HIGH);
}
if (hm==0 and comportamiento==1 or hm==0 and comportamiento==2) //Se apagara el punto para indicar que este numero corresponde a las horas
{
  digitalWrite(11,LOW);
}
if (hm==2 and comportamiento==1 or hm==2 and comportamiento==2) //Se encendera este punto para indicar que este numero corresponde a los minutos
{
  digitalWrite(11,HIGH);
}
  delay(3);
}
if (i==2) //Estamos en el tercer digito
{
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
if (cont_parpadeo>0 and cont_parpadeo<=500000) //El numero correspondiente parpadeara cuando se este poniendo la alarma o cambiando la hora
{
  if (seleccion==3 and hm==0 or seleccion==5 and hm==2)
  {
    digitalWrite(4,HIGH);
  }
}
if (seleccion==3 and modo==1 and comportamiento==0) //Se apagara el punto para indicar que numero estas cambiando en el contador manual
{
  digitalWrite(11, LOW);
}
if (seleccion!=3 and modo==1 and comportamiento==0) //Si no estas cambiando este numero, el punto estara iluminado en el contador manual
{
  digitalWrite(11, HIGH);
}
if (hm==0 and comportamiento==1 or hm==0 and comportamiento==2) //Se encendera el punto para indicar que este numero corresponde a los minutos
{
  digitalWrite(11,HIGH);
}
if (hm==2 and comportamiento==1 or hm==2 and comportamiento==2) //Se apagara este punto para indicar que este numero corresponde a los segundos
{
  digitalWrite(11,LOW);
}
  delay(3);
}
if (i==3) //Estamos en el cuarto digito
{
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
if (cont_parpadeo>0 and cont_parpadeo<=500000) //El numero correspondiente parpadeara cuando se este poniendo la alarma o cambiando la hora
{
  if (seleccion==4 and hm==0 or seleccion==6 and hm==2)
  {
    digitalWrite(5,HIGH);
  }
}
if (seleccion==4 and modo==1 and comportamiento==0) //Se apagara el punto para indicar que numero estas cambiando en el contador manual
{
  digitalWrite(11, LOW);
}
if (seleccion!=4 and modo==1 and comportamiento==0) //Si no estas cambiando este numero, el punto estara iluminado en el contador manual
{
  digitalWrite(11, HIGH);
}
if (hm==0 and comportamiento==1 or hm==0 and comportamiento==2) //Se encendera el punto para indicar que este numero corresponde a los minutos
{
  digitalWrite(11,HIGH);
}
if (hm==2 and comportamiento==1 or hm==2 and comportamiento==2) //Se apagara este punto para indicar que este numero corresponde a los segundos
{
  digitalWrite(11,LOW);
}
  delay(3);
}
i=i+1;
}
i=0;
if (cont00!=0) //Contador para el mensaje de error en el contador automatico
{
  cont00=cont00+retraso;
  if (cont00>=250000)
  {
    cont00=0;
    digitalWrite(11, LOW);
  }
}
if (contc_I) //Contador para poder hacer n cliks en el boton izquierdo
{
  contc_I=contc_I+retraso;
  if (contc_I>400000)
  {
    contc_I=0;
  }
}
if (contc_C) //Contador para poder hacer n cliks en el boton central
{
  contc_C=contc_C+retraso;
  if (contc_C>400000)
  {
    contc_C=0;
  }
}
if (contc_D) //Contador para poder hacer n cliks en el boton derecho
{
  contc_D=contc_D+retraso;
  if (contc_D>400000)
  {
    contc_D=0;
  }
}

if (modo==0) //Contador para el contador automatico
{
  if (comportamiento==0 and cont>=espera[tiempo])
  {
    cont=cont-espera[tiempo];
    if (cuenta==0)
    {
      ++numero4;
    }
    else{
      --numero4;
    }
  }
}

if (modo==1 and comportamiento==1 or modo==1 and comportamiento==2) //Contador para el parpadeo de los numeros en el reloj y el cambio de hora
{
  cont_parpadeo=cont_parpadeo+retraso;
  if (cont_parpadeo>1000000)
  {
    cont_parpadeo=cont_parpadeo-1000000;
  }
}
if (modo==0 and comportamiento==0) //Contador para el parpadeo de los numeros en el reloj y el cambio de hora
{
  cont=cont+retraso;
}
if (contr>=1000000) //Contador para el reloj
{
  r6=r6+1;
  contr=contr-1000000;
}
contr=contr+retraso;

if (micros()>micros_anterior) //Duracion de un ciclo dentro de los 70 minutos
{
  retraso=micros()-micros_anterior+8;
}
else{
  retraso=4294967295-micros_anterior+micros()+8;
}
}

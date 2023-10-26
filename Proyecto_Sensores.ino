//Motor Izq
const int PWMA = 10;
const int AIN2 = 9;
const int AIN1 = 8;
//Activa el control del modulo H
const int STBY = 7;
//Motor Der
const int BIN1 = 12;
const int BIN2 = 13;
const int PWMB = 11;
//Sensores 
const int Trigger2 = 4;   
const int Echo2 = 5;   
const int Trigger1 = 2;   
const int Echo1 = 3;
const int LDR = A0;
//Velocidad motores
float vl = 0;
float vr = 0;
//Pesos
float w0 = 0;
float w1 = 0;
int s1 = 0;
int s2 = 0;

void setup()
{
  //configurar sensores
  pinMode(Trigger1, OUTPUT); 
  pinMode(Echo1, INPUT);
  pinMode(Trigger2, OUTPUT); 
  pinMode(Echo2, INPUT); 
  digitalWrite(Trigger1, LOW); 
  digitalWrite(Trigger2, LOW); 
  pinMode(LDR,INPUT);
  //congifura motores 
  pinMode(PWMA,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(STBY,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(PWMB,OUTPUT);

  digitalWrite(STBY,HIGH);

 Serial.begin(9600);
}


void loop()
{
  long t1;
  long d1;
  long t2;
  long d2;  
  int LDR_estado = analogRead(LDR);
  // Obtenemos informacion del entorno con los sensores
  digitalWrite(Trigger1, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger1, LOW);

  t1 = pulseIn(Echo1, HIGH);
  d1 = t1/59;

  digitalWrite(Trigger2, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger2, LOW);

  t2 = pulseIn(Echo2, HIGH);
  d2 = t2/59;

  Serial.print("Distancia1: ");
  Serial.print(d1);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.print("    Distancia2: ");
  Serial.print(d2);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  
                  //Hacemos una pausa de 100ms

  if (d1 <= 20){
    s1 = 1;
  }

  if (d2 <= 20){
    s2 = 1;
  }

if  (LDR_estado < 10){
  digitalWrite(STBY,LOW);
}
else{
  digitalWrite(STBY,HIGH);
  }

 
  w0 = 100;
  w1 = w0*0.8;

  vl = w0 - w1*s1;     
  vr = w0 - w1*s2;
  
  configurar_motores();
  analogWrite(PWMA,vl);
  analogWrite(PWMB,vr);

  Serial.print("Distancia1: ");
  Serial.print(d1);      //Enviamos serialmente el valor de la distancia 1
  Serial.print("cm");
  Serial.print("    Distancia2: ");
  Serial.print(d2);      //Enviamos serialmente el valor de la distancia 2
  Serial.print("cm");
  Serial.print("    LDR: ");
  Serial.print(LDR_estado);      //Enviamos serialmente el valor del motor izquierdo
  Serial.println();
 
  delay(4000);
  
  s1 = 0;
  s2 = 0;
}

void configurar_motores(){
  //Motor Izq
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  //Motor Der
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
}

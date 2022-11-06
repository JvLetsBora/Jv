#define NOTE_C0  131
#define NOTE_C1  262
#define NOTE_C2  523
#define NOTE_C3  2093
#define NOTE_C4  222
#define NOTE_C5  333
#define NOTE_C6  555
#define NOTE_C7  90
#define NOTE_C8  432
#define NOTE_C9  671
#define NOTE_C10  891

#define alto 4
#define baixo 5
#define bem_baixo 6
#define azul 7
#define buzzer 14
#define sensor 15
#define btn1 45
#define btn2 3

int a = 0;
int numero = 14;
int binario[4] = {1,1,1,1};
int i = 0;
int passado = 44353400;
int nota = 0;
int notas[10] = {
    NOTE_C1,
    NOTE_C2,
    NOTE_C3,
    NOTE_C4,
    NOTE_C5,
    NOTE_C6,
    NOTE_C7,
    NOTE_C8,
    NOTE_C9,
    NOTE_C10
  };
int sequencia[20]={0};
bool capitar = true;
bool btn = true;
bool btn_2 = false;
int luz = 0;
int contador = 0;


void setup() {
  
  Serial.begin(115200);
  pinMode(alto, OUTPUT);
  pinMode(baixo, OUTPUT);
  pinMode(bem_baixo, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sensor, INPUT);
  a = 0;
  capitar = true;
}

void loop() {
  
  if (capitar == true)
  {
    int analog = analogRead(sensor);
    luz = map(analog, 64, 8126, 15, 0);
    check();
    btn_status();
    btn_status2();
  }
  else
  {
    loadMusic();
    contador += 1;
    if (contador > 4)
    {
      //Serial.print("-__Debug__-");
      //capitar = true;
      contador = 0;
      delay(1000);
    }
  }
  if (binario[0] == 1)
    {
      nota += 1;
      digitalWrite(alto, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
  else 
    {
      digitalWrite(alto, LOW);
    }    
  if (binario[1] == 1)
    {
      nota += 2;
      digitalWrite(baixo, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
  else 
    {
      digitalWrite(baixo, LOW);
    } 
  if (binario[2] == 1)
    {
      nota += 3;
      digitalWrite(bem_baixo, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
  else 
    {
      
      digitalWrite(bem_baixo, LOW);
    }   
  if (binario[3] == 1)
    {
      nota += 4;
      digitalWrite(azul, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
  else 
    {
      digitalWrite(azul, LOW);
    }    
   tocar(nota);
}


void resetar(){
  binario[0] = 0;
  binario[1] = 0;
  binario[2] = 0;
  binario[3] = 0;
  noTone(buzzer);
  delay(100);
}


void btn_status(){
  if(digitalRead(btn1) == LOW && btn == true)
  {
   Serial.print(digitalRead(btn1)); 
   btn = false;
  }
  else if (digitalRead(btn1) == HIGH && btn == false)
  {
    Serial.print(digitalRead(btn1)); 
    btn = true;
    sequencia[a] = luz;
    a += 1;
    resetar();
  }
  
}

void btn_status2(){
  if(digitalRead(btn2) == LOW && btn_2 == true)
  {
   btn_2 = false;
   Serial.print(digitalRead(btn2));
  }
  else if (digitalRead(btn2) == HIGH && btn_2 == false)
  {
    Serial.print(digitalRead(btn2));
    btn_2 = true;
    a = 0;
    resetar();
    capitar = false;
   }
  }


void loadMusic(){
  if (contador == 0){
    a += 1;
    luz = sequencia[a];
    Serial.print(sequencia[a]);
  }
  if (sequencia[a] != 0 )
  {
    check();
  }
  else
  {
    resetar();
    capitar = true;
  }
}

void check(){
  if (passado != luz)
  {
    passado = luz;
    resetar();
    i = 0;
    numero = luz;
  }
  else
  {
    if (numero)
    {
      binario[i] = numero % 2;
      //Serial.println(binario[i]);
    }
    if (numero/2 > 0)
    {
        numero = numero/2;
        i += 1;
    }
  }
}


void tocar(int i)
{ 
    nota = 0;
    tone(buzzer, notas[i]);
    delay(25);
    noTone(11);
}

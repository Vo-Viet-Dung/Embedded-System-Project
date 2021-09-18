#define inA1 2 
#define inA2 3 
#define inB1 4
#define inB2 5 
#define hongngoai1 A0
#define hongngoai2 A1
#define hongngoai3 A2
#define hongngoai4 A3
#define hongngoai5 A4
#define ENA 10
#define ENB 11
int prev;
int x1, x2, x3, x4, x5;
void setup() {
pinMode(inA1, OUTPUT);
pinMode(inA2, OUTPUT);
pinMode(inB1, OUTPUT);
pinMode(inB2, OUTPUT);
pinMode(hongngoai1, INPUT);
pinMode(hongngoai2, INPUT);
pinMode(hongngoai3, INPUT);
pinMode(hongngoai4, INPUT);
pinMode(hongngoai5, INPUT);
pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);
Serial.begin(9600);
analogWrite(ENA, 100);
analogWrite(ENB, 100);//đi chậm cho khỏi trượt Line
}
void loop(){ 
x1 = digitalRead(hongngoai1);
x2 = digitalRead(hongngoai2);
x3 = digitalRead(hongngoai3);
x4 = digitalRead(hongngoai4);
x5 = digitalRead(hongngoai5);
if((x1 == 0 && x2 == 1 && x3 == 0 && x4 == 0 && x5 == 0) 
    || (x1 == 1 && x2 == 0 && x3 == 1 && x4 == 1 && x5 == 1)
    || (x1 == 0 && x2 == 0 && x3 == 1 && x4 == 1 && x5 == 1)
    || (x1 == 1 && x2 == 1 && x3 == 0 && x4 == 0 && x5 == 0)){
  quaytrai(); 
  prev = 1;
}
else if( (x1 == 0 && x2 == 0 && x3 == 0 && x4 == 1 && x5 == 0) 
    || (x1 == 1 && x2 == 1 && x3 == 1 && x4 == 0 && x5 == 1)
    || (x1 == 1 && x2 == 1 && x3 == 1 && x4 == 0 && x5 == 0)
    || (x1 == 0 && x2 == 0 && x3 == 0 && x4 == 1 && x5 == 1)){
  quayphai();
  prev = 2;
}
else if((x1 == 0 && x2 == 0 && x3 == 0 && x4 == 0 && x5 == 1) 
    || (x1 == 1 && x2 == 1 && x3 == 1 && x4 == 1 && x5 == 0)){
  quayphai_plus();
  prev = 2;
}
else if((x1 == 0 && x2 == 0 && x3 == 1 && x4 == 0 && x5 == 0)
     || (x1 == 1 && x2 == 1 && x3 == 0 && x4 == 1 && x5 == 1)
     || (x1 == 1 && x2 == 0 && x3 == 1 && x4 == 0 && x5 == 1)
     || (x1 == 0 && x2 == 1 && x3 == 0 && x4 == 1 && x5 == 0)){
  dithang();
  prev = 0;
}
else if((x1 == 1 && x2 == 0 && x3 == 0 && x4 == 0 && x5 == 0) 
    || (x1 == 0 && x2 == 1 && x3 == 1 && x4 == 1 && x5 == 1)){
  quaytrai_plus();
  prev = 1; 
}
else if((x1 == 0 && x2 == 0 && x3 == 0 && x4 == 0 && x5 == 0) 
    || (x1 == 1 && x2 == 1 && x3 == 1 && x4 == 1 && x5 == 1)){
//  if(prev == 0){
    dithang();  
//  }
//  if(prev == 1){
//    quaytrai();
//  }
//  else if(prev == 2){
//    quayphai();
//  }
}
}
void lui(){
           analogWrite(ENA, 90);
           analogWrite(ENB, 90);
           digitalWrite(inA1,HIGH);
           digitalWrite(inA2,LOW);
           digitalWrite(inB1,HIGH);
           digitalWrite(inB2,LOW);
           
   
}
void dithang(){
            analogWrite(ENA, 110);
           analogWrite(ENB, 110);
           digitalWrite(inA1,LOW);
           digitalWrite(inA2,HIGH);
           digitalWrite(inB1,LOW);
           digitalWrite(inB2,HIGH);
           
}
void quayphai(){
           analogWrite(ENA, 100);
           analogWrite(ENB, 100);
           digitalWrite(inA1,LOW);
           digitalWrite(inA2,HIGH);
           digitalWrite(inB1,LOW);
           digitalWrite(inB2,LOW);
           
}
void quaytrai(){
           analogWrite(ENA, 100);
           analogWrite(ENB, 100);
           digitalWrite(inA1,LOW);
           digitalWrite(inA2,LOW);
           digitalWrite(inB1, LOW);
           digitalWrite(inB2,HIGH);
           
}
void quayphai_plus(){
           analogWrite(ENA, 100);
           analogWrite(ENB, 100);
           digitalWrite(inA1,LOW);
           digitalWrite(inA2,HIGH);
           digitalWrite(inB1,HIGH);
           digitalWrite(inB2,LOW);
           
}
void quaytrai_plus(){
           analogWrite(ENA, 100);
           analogWrite(ENB, 100);
           digitalWrite(inA1,HIGH);
           digitalWrite(inA2,LOW);
           digitalWrite(inB1, LOW);
           digitalWrite(inB2,HIGH);
           
}

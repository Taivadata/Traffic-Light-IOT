//GROUP 03:
//GROUP 02_TRAFFICLIGHT:
// Mentor: Trần Ngọc Hoàng
// Leader: Nguyễn Đức Tài CE160859
// Võ Việt Nhân CE160937
// Trần Văn Tới CE160459
// Phạm Minh Thư CE160859
// Nguyễn Thanh Quang Duy CE161080


/*
---Thiết bị được sử dụng---
 Arduino Uno R3
7 Segment Display
Breadboard Mini
Resistor
Photoresistor
Red LED
Yellow LED
Green LED

*/
#define segA 2//connecting segment A to PIN2
#define segB 3// connecting segment B to PIN3
#define segC 4// connecting segment C to PIN4
#define segD 5// connecting segment D to PIN5
#define segE 6// connecting segment E to PIN6
#define segF 7// connecting segment F to PIN7
#define segG 8// connecting segment G to PIN8
            
const int sensorMin = 0;
const int sensorMax = 1000;
  
int checkNight = 0;
int range;
int rangeLast;
int signalSensor = 0;

int i;

int COUNT=0;
int count_timer = 20;
int State = 1; 

int led7_1 = A5; 
int led7_2 = A4; 

int ones = 1;
int tens = 2;

int countLed7 = 2;

void setup()

{
  
  pinMode(A0, INPUT);
  
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT); 		//up
  pinMode(A3, OUTPUT);
  
  pinMode(led7_1, OUTPUT);
  pinMode(led7_2, OUTPUT);
  
   for (int i=0;i<=13;i++)
   {

     pinMode(i, OUTPUT);

   }
  
   noInterrupts();          

  	TCCR1A = 0; 

  	TCCR1B = 0; 

  	TCNT1  = 0; 
  
  	int mSecs = 25; 
  
  	OCR1A = (16e6 / 256L * mSecs) / 1e3 - 1;;   

  	TCCR1B |= (1 << WGM12);  
	
 	 TCCR1B |= (1 << CS12);    

  	TIMSK1 |= (1 << OCIE1A);  

  	interrupts();       

}



ISR(TIMER1_COMPA_vect)   
{
  if ((countLed7 % 4) == 0){
      countLed7 = 1;
      signalSensor = analogRead(A0);		//Đọc tín hiệu từ cảm biến
      range = map(signalSensor, sensorMin, sensorMax, 0, 3);
      if (range != rangeLast){
        if(range > 2){
          count_timer = 20;
          COUNT = 0;
          checkNight = 0;
        } else{
            checkNight = 1;
            ones = 9;
            tens = 9;
         	for(i = 0; i<=13; i++)			//Tắt toàn bộ đèn
              digitalWrite(i,LOW);                	
            digitalWrite(A3,LOW);
            digitalWrite(A2,LOW);
            digitalWrite(A1,LOW);
            digitalWrite(0,LOW);
        }
      }	
      rangeLast = range;
      if (checkNight == 0){						//Nếu ban ngày sẽ chạy bình thường
        COUNT++;

        if (COUNT%10 == 0)
        {
          count_timer = COUNT/10;
          count_timer = 20 - count_timer; 

          if (count_timer == 0)
          {
            COUNT = 0;
            if(State == 2)
            {
              State = 0;
            }
            State++;
          }
        }
        ones = count_timer%10;
        tens = count_timer/10;        
      }
  }
  else{
    	countLed7++;
    	digitalWrite(led7_1, HIGH);
        digitalWrite(led7_2, LOW); 
        display(tens); 
        delay(50); 

        digitalWrite(led7_1, LOW);
        digitalWrite(led7_2, HIGH);
        display(ones);
        delay(50);
   		
  }
}

void display(int ID_COUNT)
{
switch (ID_COUNT)					//Dislay số ra đèn led 7 đoạn
     {
           	case 0:
                 digitalWrite(segA, LOW);
                 digitalWrite(segB, LOW);
                 digitalWrite(segC, LOW);
                 digitalWrite(segD, LOW);
                 digitalWrite(segE, LOW);
                 digitalWrite(segF, LOW);
                 digitalWrite(segG, HIGH);
                 break;
            case 1:
                 digitalWrite(segA, HIGH);
                 digitalWrite(segB, LOW);
                 digitalWrite(segC, LOW);
                 digitalWrite(segD, HIGH);
                 digitalWrite(segE, HIGH);
                 digitalWrite(segF, HIGH);
                 digitalWrite(segG, HIGH);
                 break;
            case 2:
                 digitalWrite(segA, LOW);
                 digitalWrite(segB, LOW);
    			 digitalWrite(segC, HIGH);
                 digitalWrite(segD, LOW);
                 digitalWrite(segE, LOW);
                 digitalWrite(segF, HIGH);
                 digitalWrite(segG, LOW);
                 break;
            case 3:
                 digitalWrite(segA, LOW);
                 digitalWrite(segB, LOW);
                 digitalWrite(segC, LOW);
                 digitalWrite(segD, LOW);
                 digitalWrite(segE, HIGH);
                 digitalWrite(segF, HIGH);
                 digitalWrite(segG, LOW);
                 break;
            case 4:
                 digitalWrite(segA, HIGH);
                 digitalWrite(segB, LOW);
                 digitalWrite(segC, LOW);
                 digitalWrite(segD, HIGH);
                 digitalWrite(segE, HIGH);
                 digitalWrite(segF, LOW);
                 digitalWrite(segG, LOW);
                 break;
            case 5:
                 digitalWrite(segA, LOW);
                 digitalWrite(segB, HIGH);
                 digitalWrite(segC, LOW);
                 digitalWrite(segD, LOW);
                 digitalWrite(segE, HIGH);
                 digitalWrite(segF, LOW);
                 digitalWrite(segG, LOW);
                 break;
            case 6:
                 digitalWrite(segA, LOW);
                 digitalWrite(segB, HIGH);
                 digitalWrite(segC, LOW);
                 digitalWrite(segD, LOW);
                 digitalWrite(segE, LOW);
                 digitalWrite(segF, LOW);
                 digitalWrite(segG, LOW);
                 break;
            case 7:
                 digitalWrite(segA, LOW);
                 digitalWrite(segB, LOW);
                 digitalWrite(segC, LOW);
                 digitalWrite(segD, HIGH);
                 digitalWrite(segE, HIGH);
                 digitalWrite(segF, HIGH);
                 digitalWrite(segG, HIGH);
                 break;
            case 8:
                 digitalWrite(segA, LOW);
                 digitalWrite(segB, LOW);
                 digitalWrite(segC, LOW);
                 digitalWrite(segD, LOW);
digitalWrite(segE, LOW);
                 digitalWrite(segF, LOW);
                 digitalWrite(segG, LOW);
                 break;
            case 9:
                 digitalWrite(segA, LOW);
                 digitalWrite(segB, LOW);
                 digitalWrite(segC, LOW);
                 digitalWrite(segD, LOW);
                 digitalWrite(segE, HIGH);
                 digitalWrite(segF, LOW);
                 digitalWrite(segG, LOW);
                 break;
             break;
     }
}


void loop(){
  if (checkNight == 0){	
    
      if (State == 1)				//Chế độ đèn ban ngày
      {
        digitalWrite(13,HIGH);
        digitalWrite(12,LOW);
        digitalWrite(11,LOW);
        digitalWrite(A3,HIGH);
        digitalWrite(A2,LOW);

        if(count_timer>15){
            digitalWrite(10,LOW);
            digitalWrite(9,LOW);
            digitalWrite(1,HIGH);
            digitalWrite(A1,HIGH);
            digitalWrite(0,LOW);
          delay(250);
        }

        else if(count_timer>5 && count_timer<=15)
        {
            //digitalWrite(10,LOW);
            //digitalWrite(9,LOW);
            //digitalWrite(1,HIGH);
            digitalWrite(A1,LOW);
            digitalWrite(0,HIGH);
          delay(250);
        }
        else if(count_timer<=5)
        {
            //digitalWrite(10,LOW);
            digitalWrite(9,HIGH);
            digitalWrite(1,LOW);
            digitalWrite(A1,HIGH);
            digitalWrite(0,LOW);
          delay(250);
        }

      }

      else if (State == 2)
      {
        digitalWrite(10,HIGH);
        digitalWrite(9,LOW);
        digitalWrite(1,LOW);
        digitalWrite(A1,HIGH);
        digitalWrite(0,LOW);

        if(count_timer>15){
            digitalWrite(13,LOW);
            digitalWrite(12,LOW);
            digitalWrite(11,HIGH);
            digitalWrite(A3,HIGH);
            digitalWrite(A2,LOW);
          delay(250);
        }
        else if(count_timer>5 && count_timer<=15)
        {
            //digitalWrite(13,LOW);
            //digitalWrite(12,LOW);
            digitalWrite(11,HIGH);
            digitalWrite(A3,LOW);
            digitalWrite(A2,HIGH);
          delay(250);
        }
        else if(count_timer<=5)
        {
          
            //digitalWrite(13,LOW);
            digitalWrite(12,HIGH);
            digitalWrite(11,LOW);
            digitalWrite(A3,HIGH);
            digitalWrite(A2,LOW);
          delay(250);
        }

      }     
  }
  else if(checkNight == 1){			//Chế độ ban đêm, chớp nháy đèn vàng
    digitalWrite(12,HIGH);
    digitalWrite(9,HIGH);
    delay(500);
    digitalWrite(12,LOW);
    digitalWrite(9,LOW);
    delay(200);
  }
}
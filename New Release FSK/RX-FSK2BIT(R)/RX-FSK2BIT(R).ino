// Recieve FSK


int input,max,prev,currentTime,prevTime,period,cout = 0,totalTime = 0;
float currentFrequency,prevFrequency;
boolean check = false;

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

int c00 = 0,
    c01 = 0,
    c10 = 0,
    c11 = 0;

void setup(void) 
{
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
  Serial.begin(115200);
}

void loop(void) 
{   
    input = analogRead(A0);
    if(input > 600 && check == true){ //600
      currentTime = micros();
      period =  currentTime -  prevTime;
      currentFrequency = 1000000/period;
      prevFrequency = currentFrequency;
      prevTime = currentTime;
      
      //Serial.println(currentFrequency);

      if(1125 < currentFrequency && currentFrequency <= 1375)   
         c11++;
      if(875 < currentFrequency && currentFrequency <= 1125)
         c10++;
      if(625 < currentFrequency && currentFrequency <= 875)
         c01++;  
      if(375 < currentFrequency && currentFrequency <= 625)
         c00++;   
            
      if(c11 >= 4 || c10 >= 3 ||  c01 >= 2 || c00 >= 2){
        if(c11 == 4)
          Serial.print("1 1 ");
        if(c10 == 3)
          Serial.print("1 0 ");
        if(c01 == 2)
          Serial.print("0 1 ");
        if(c00 == 2)
          Serial.print("0 0 "); 
          
        prevTime = 2000; 
        c11 = 0;
        c10 = 0;
        c01 = 0;
        c00 = 0;
        cout++;
      }
        
      if(cout == 5){
        Serial.println();
        cout = 0;
        c11 = 0;
        c10 = 0;
        c01 = 0;
        c00 = 0;      
      }
      

      
      check = false;
    }
    if(input>max){
    max=input;
    }
    if(max-input > 200 && check==false){ //100//200
    check = true;
    }
  
}

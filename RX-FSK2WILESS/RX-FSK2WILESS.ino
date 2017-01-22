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
  Serial.begin(115200);                   // set buadrate of serial
}

void loop(void) 
{   
    input = analogRead(A0);               // read signal from pin A0
    
    if(input-prev>30 && check==false){    // if signal is rising
      max = 0;
      check = true;
    }
    if(input>max){                        // set max input
      max=input;
    }  
    if(max-input > 50 && check == true){  // if signal is amplitude
      currentTime = micros();             // get time in microsecond
      period =  currentTime - prevTime;   // find period
      currentFrequency = 1000000/period;  // find frequency
      prevFrequency = currentFrequency;
      prevTime = currentTime;
      
      //Serial.println(currentFrequency);   // for debug frequency

      if(1125 < currentFrequency && currentFrequency <= 1375)   // count signal frequency
         c11++;
      if(875 < currentFrequency && currentFrequency <= 1125)
         c10++;
      if(625 < currentFrequency && currentFrequency <= 875)
         c01++;  
      if(375 < currentFrequency && currentFrequency <= 625)
         c00++;   
            
      if(c11 >= 5 || c10 >= 4 ||  c01 >= 3 || c00 >= 2){        // display data
        if(c11 == 5)
          Serial.print("1 1 ");
        if(c10 == 4)
          Serial.print("1 0 ");
        if(c01 == 3)
          Serial.print("0 1 ");
        if(c00 == 2)
          Serial.print("0 0 "); 
          
        prevTime = 3000;                  // set previous time
        c11 = 0;
        c10 = 0;
        c01 = 0;
        c00 = 0;
        cout++;
      }
        
      if(cout == 5){
        Serial.println();
        cout = 0;
        //c11 = 0;
        //c10 = 0;
        //c01 = 0;
        //c00 = 0;      
      } 
      
      check = false;                    
    } 
    prev = input;
}


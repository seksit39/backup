// Recieve FSK


int input,max,prev,currentTime,prevTime,period,cout = 0,totalTime = 0;
float currentFrequency,prevFrequency;
boolean check,cp = false;

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void setup(void) 
{
  cbi(ADCSRA,ADPS2) ;
  sbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
  Serial.begin(115200);

}

void loop(void) 
{   
  
    input = analogRead(A0);               // read signal from pin A0
    
    if(input-prev>10 && check==false){    // if signal is rising
      max = 0;
      check = true;
    }
    if(input>max){                        // set max input
      max=input;
    }  
    if(max-input > 10 && check == true){  // if signal is amplitude
      currentTime = micros();             // get time in microsecond
      period =  currentTime - prevTime;   // find period
      currentFrequency = 1000000/period;  // find frequency
      prevFrequency = currentFrequency;
      prevTime = currentTime;
      
      Serial.println(currentFrequency);   // for debug frequency
      check = false;
      }
    prev=input;
  
}

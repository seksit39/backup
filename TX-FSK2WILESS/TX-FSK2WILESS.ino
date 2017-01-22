/*
sine delay
none       1736 Hz
20  micros 1500 Hz
50  micros 1250 Hz
100 micros 1000 Hz
190 micros 750  Hz
350 micros 500  Hz
*/
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>

  Adafruit_MCP4725 dac;
  uint16_t a = 0;
  uint16_t input[10] = {0,0,0,0,0,0,0,0,0,0};
  const uint16_t sine[4]  = {2048,4095,2048,0};   // At 1700 Hz     
  int del = 0;
  int c00 = 0;
  int c01 = 0;
  int c10 = 0;
  int c11 = 0;

void setup(void) {
  
  Serial.begin(115200);                         // set buadrate serial
  dac.begin(0x62);                              // set to default 
  
}

void loop(void) {

      if(Serial.available() > 0){               // for get input
        for(int i=0 ; i<10 ; i++){
          input[i] = Serial.parseInt();         // save input to array 
          Serial.print(input[i]);  
          Serial.print(" ");
        }
        Serial.println();
        Serial.parseInt();

        //for(int i=0 ; i<10 ; i++)
        for(int k=0 ; k<10 ; k+=2){
          
          if(input[k] == 0){                
            if(input[k+1] == 0){                 // for input 00 - 500 Hz
              for(int j=0 ; j<2 ; j++)
                for(int i=0 ; i<4 ; i++){
                  dac.setVoltage(sine[i], false);
                  delayMicroseconds(360); 
                }
            }
              
             else if(input[k+1] == 1){           // for input 01 - 750 Hz
              for(int j=0 ; j<3 ; j++)
                for(int i=0 ; i<4 ; i++){
                  dac.setVoltage(sine[i], false);
                  delayMicroseconds(190); 
                }                
             }
          }
          else if(input[k] == 1){               // for input 10 - 1000 Hz
            if(input[k+1] == 0){
              for(int j=0 ; j<4 ; j++)
                for(int i=0 ; i<4 ; i++){
                  dac.setVoltage(sine[i], false);
                  delayMicroseconds(100); 
                }
            }
            else if(input[k+1] == 1){            // for input 11 - 1250 Hz
              for(int j=0 ; j<5 ; j++)      
                for(int i=0 ; i<4 ; i++){
                  dac.setVoltage(sine[i], false);
                  delayMicroseconds(50); 
                }             
            }
        } 
      } 
      }
      dac.setVoltage(0, false);                 // for don't send
}


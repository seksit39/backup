#include <Wire.h>
#include <Adafruit_MCP4725.h>

  Adafruit_MCP4725 dac;
  uint16_t a = 0;
  uint16_t input[10] = {0,0,0,0,0,0,0,0,0,0};
  const uint16_t sine[4] = {2048,4095,2048,0}; //at 1700 Hz

void setup() {
  Serial.begin(115200);
  dac.begin(0x62);

}

void loop() {
  if(Serial.available() > 0){
        for(int i=0 ; i<10 ; i++){
          input[i] = Serial.parseInt();
          Serial.print(input[i]);  
          Serial.print(" ");
        }
        Serial.println();
        Serial.parseInt();
        for(int x=0 ; x<10000 ; x++)
        for(int k=0 ; k<10 ; k+=2){
          if(input[k] == 0){
            if(input[k+1] == 0)
              a = 0;
            else if(input[k+1] == 1)
              a = 1;
          }
          else if(input[k] == 1){
            if(input[k+1] == 0)
              a = 2;
            else if(input[k+1] == 1)
              a = 3;
          }
          for(int j=0 ; j<1 ; j++){
              for(int i=0 ; i<4 ; i++){
                dac.setVoltage(sine[i]*(a+1)/4, false);
              }
          }
        }   
      }
      dac.setVoltage(0, false);

}

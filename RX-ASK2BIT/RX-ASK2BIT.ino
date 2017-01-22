  int sum = 0;
  int max = 0;
  int prev = 0;
  int check = false;
  int output = -1;
  int count = 0;
  int tmp = 0;
  
void setup() {
  Serial.begin(115200);
}

void loop() {

  tmp = analogRead(A0);
  
  //Serial.println(tmp);
  
  if(tmp-prev>10 && check==false){ 
    max = 0;
    check = true;
  }
  
  if(tmp>max){
    max=tmp;
  }
  
  if(max-tmp > 10){
    if(check == true){
      if(128<max && max<384){
        Serial.print("0 0 ");
        count++;
      }        
      else if(384<max && max<640){
        Serial.print("0 1 ");
        count++;
      }
      else if(640<max && max<896){
        Serial.print("1 0 ");
        count++;
      }
      else if(896<max && max<1024){
        Serial.print("1 1 ");
        count++;
      }
      if(count == 5){
        Serial.println();
        count = 0;
      }
    }
    check = false;
  }



prev = tmp;
}

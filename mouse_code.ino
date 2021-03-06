//connect 3.3v to AREF


const int ap1 = A5; 
const int ap2 = A4;
const int ap3 = A3;
const int rcl = 2;
const int lcl = 3;

int factor = 4;
int responsedelay = 20;

int sv1 = 0;        
int ov1 = 0;    
int sv2 = 0;      
int ov2= 0;      
int sv3 = 0;       
int ov3= 0;      

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(rcl, INPUT);
  pinMode(lcl, INPUT);
  Mouse.begin();
}

void loop() {
  
  int rightclick = digitalRead(rcl);
  int leftclick = digitalRead(lcl);
  
  analogReference(EXTERNAL);    //connect 3.3v to AREF
  // read the analog in value:
  sv1 = analogRead(ap1);            
  // map it to the range of the analog out:
  ov1 = map(sv1, 0, 1023, 0, 255);  
  // change the analog out value:
  delay(2);                     
  //
  sv2 = analogRead(ap2);            
  
  ov2 = map(sv2, 0, 1023, 0, 255); 
 // 
  delay(2);                 
  //
  sv3 = analogRead(ap3);            
  
  ov3 = map(sv3, 0, 1023, 0, 255);  
  
  // print the results to the serial monitor:
  Serial.print("Xsensor1 = " );                       
  Serial.print(sv1);      
  Serial.print("\t output1 = ");      
  Serial.println(ov1);   
 
  Serial.print("Ysensor2 = " );                       
  Serial.print(sv2);      
  Serial.print("\t output2 = ");      
  Serial.println(ov2);   

  Serial.print("Zsensor3 = " );                       
  Serial.print(sv3);      
  Serial.print("\t output3 = ");      
  Serial.println(ov3);   


  int xdist = 0;
  int ydist = 0;
  if( ov1 > 160)
    xdist = 5;
  else if( ov2 > 160)
    ydist = 5;
  else if( ov1 < 100)
    xdist = -5;
  else if( ov2 < 100)
    ydist = -5;
  else
  {
    xdist = (130 - ov1)/factor;
    ydist = (130 - ov2)/factor;
  }
  
  Mouse.move(xdist,ydist,0);
  
  if(rightclick == HIGH)
  {
    if(!Mouse.isPressed(MOUSE_RIGHT))
      Mouse.press(MOUSE_RIGHT);
  }
  else
  {
    if(Mouse.isPressed(MOUSE_RIGHT))
      Mouse.release(MOUSE_RIGHT);
  }
  if(leftclick == HIGH)
  {
    if(!Mouse.isPressed(MOUSE_LEFT))
      Mouse.press(MOUSE_LEFT);
  }
  else
  {
    if(Mouse.isPressed(MOUSE_LEFT))
      Mouse.release(MOUSE_LEFT);
  }
  
  delay(responsedelay);                     
  
}

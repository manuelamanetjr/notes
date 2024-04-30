#include <LiquidCrystal.h> //Libraries
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Arduino pins to lcd

#define sensor_pin A0 
int adc_value;
int percent_value;

#define bt_silent  A5
int silent=0;

#define G_led 8 
#define R_led 9 

#define buzzer 13

void setup() { // put your setup code here, to run once 

pinMode(sensor_pin, INPUT);

pinMode(bt_silent, INPUT_PULLUP);

pinMode(R_led,OUTPUT); // declare Red LED as output
pinMode(G_led,OUTPUT); // declare Green LED as output
pinMode(buzzer,OUTPUT); // declare Buzzer as output 

lcd.begin(16, 2); // Configura lcd numero columnas y filas
lcd.clear();
lcd.setCursor (0,0);
lcd.print("   Welcome To   ");
lcd.setCursor (0,1);
lcd.print(" Rain  Detector "); 
delay(2000);
lcd.clear();
}

void loop() {

adc_value= analogRead(sensor_pin);
percent_value = map(adc_value,0,1023,100,0);

if(digitalRead (bt_silent) == 0){ 
silent = 1; 
delay(100);
}

lcd.setCursor(0, 0);  
lcd.print("Rain Level: "); 
lcd.print(percent_value); 
lcd.print("%  "); 

lcd.setCursor(0, 1); 
if(percent_value>30){ 
if(silent==0){digitalWrite(buzzer, HIGH);}
lcd.print("Rain Alert...!!!"); 
digitalWrite(G_led, LOW); // Turn LED off.   
digitalWrite(R_led, HIGH);  // Turn LED on.
delay(300);
}else{ silent=0;
lcd.print(".....Normal.....");   
digitalWrite(G_led, HIGH); // Turn LED on.  
digitalWrite(R_led, LOW);  // Turn LED off.
}
  
digitalWrite(buzzer, LOW);
delay(100);
}

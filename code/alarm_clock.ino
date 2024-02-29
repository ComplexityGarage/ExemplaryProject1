#include <LiquidCrystal.h>
#include <Arduino.h>
#include <Ds1302.h>

// RTC class constructor with RST, CLK pin and RST pin respectively
Ds1302 rtc(7,10,9);

// variable used to store current time
Ds1302::DateTime now;

// lcd pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

// lcd constructor with corresponding pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// analog pins getting signal from alarm (or real time) hour and minute button
int a_hour_pin = A1;
int a_min_pin = A0;

// "a_" refers to alarm, "r_" to actual time
// values of alarm hour_pin and min_pin 
int a_hour_val = 0; 
int a_min_val = 0;

// an hour and minute which the alarm is set on
int a_hour = 0;
int a_minute = 0;

// real actual time updated by RTC
int r_hour = 3;
int r_minute = 3;

// values of real hour_pin and min_pin 
int r_hour_val = 0;
int r_min_val = 0;

// strings used for displaying alarm and real time on lcd
String a_date = " ";
String r_date = " ";

// variable saying if alarm should go off or not 
int tidin = 0;

// list of tones used when alarm rings
int tones[10] = {261,277,294,311,330,349,370,392,415,440};

// analog pin connected to photoresistor on which we can read the value of electric current
int photres_pin = A5;

// value of electric current read on phothres_pin
int photres_val = 0;

// the level of actual lighting measured on photoresistor
int brightness_t1 = 0;

// the level of last lighting measured on photoresistor
int brightness_t0 = 0;

// variable saying if user can change real or alarm time
int r_hour_mode = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  rtc.init();

  pinMode(a_min_pin,INPUT);
  pinMode(a_hour_pin,INPUT);
  pinMode(photres_pin, INPUT);
}

void loop() {
  // collecting current time
  rtc.getDateTime(&now);
  r_hour = now.hour;
  r_minute = now.minute;
  
  // creating string which will be used for displaying alarm time on lcd
  if(a_hour < 10){
    if (a_minute < 10){
      a_date = "0" + String(a_hour) + " : 0" + String(a_minute);
    }
    else{
      a_date = "0" + String(a_hour) + " : " + String(a_minute);
    }   
  }
  else{
    if (a_minute < 10){
      a_date = String(a_hour) + " : 0" + String(a_minute);
    }
    else{
      a_date = String(a_hour) + " : " + String(a_minute);
    }
  }

  // creating string which will be used for displaying real time on lcd
  if (r_hour < 10){
    if (r_minute < 10){
      r_date = "0" + String(r_hour) + " : 0" + String(r_minute);
    }
    else{
      r_date = "0" + String(r_hour) + " : " + String(r_minute);
    }   
  }
  else{
    if (r_minute < 10){
      r_date = String(r_hour) + " : 0" + String(r_minute);
    }
    else{
      r_date = String(r_hour) + " : " + String(r_minute);
    }
  }

  // receiving data for alarm
  a_hour_val = analogRead(a_hour_pin);
  a_min_val = analogRead(a_min_pin);

  // changing to "set the current time" mode when both buttons are pushed
  if (a_hour_val == 1023 && a_min_val == 1023){
    r_hour_mode = 1;
    delay(500);

    while (r_hour_mode){
      // receiving data for setting real time
      r_hour_val = analogRead(a_hour_pin);
      r_min_val = analogRead(a_min_pin);

      // creating string which will be used for displaying alarm time on lcd
      if (a_hour < 10){
        if (a_minute < 10){
          a_date = "0" + String(a_hour) + " : 0" + String(a_minute);
        }
        else{
          a_date = "0" + String(a_hour) + " : " + String(a_minute);
        }   
      }
      else{
        if (a_minute < 10){
          a_date = String(a_hour) + " : 0" + String(a_minute);
        }
        else{
          a_date = String(a_hour) + " : " + String(a_minute);
        }
      }

      // creating string which will be used for displaying real time on lcd
      if (r_hour < 10){
        if (r_minute < 10){
          r_date = "0" + String(r_hour) + " : 0" + String(r_minute);
        }
        else{
          r_date = "0" + String(r_hour) + " : " + String(r_minute);
        }   
      }
      else{
        if (r_minute < 10){
          r_date = String(r_hour) + " : 0" + String(r_minute);
        }
        else{
          r_date = String(r_hour) + " : " + String(r_minute);
        }
      }
    
      // displaying alarm and real time on lcd
      lcd.setCursor(11, 0);
      lcd.print("alarm");
      lcd.setCursor(9, 1);
      lcd.print(a_date);
      lcd.setCursor(0, 0);
      lcd.print("time");
      lcd.setCursor(0, 1);
      lcd.print(r_date);

      // switching back to alarm setting mode
      if (r_hour_val == 1023 && r_min_val == 1023){
        delay(500);
        Ds1302::DateTime dt = {
              .year = 24,
              .month = Ds1302::MONTH_FEB,
              .day = 19,
              .hour = r_hour,
              .minute = r_minute,
              .second = 0,
              .dow = Ds1302::DOW_TUE
        }; 
        rtc.setDateTime(&dt);
        r_hour_mode = 0;  
      }
      // setting new real time using buttons
      else if (r_hour_val == 1023){
        if (r_hour < 24){
          r_hour = r_hour + 1;
        }
        else {
          r_hour = 0;
        }
        delay(200); 
      }
      else if (r_min_val == 1023){
        if (r_minute < 60){
          r_minute = r_minute + 1;
        }
        else {
          r_minute = 0;
        }
        delay(200);
      }      
    }
  }

  // setting alarm time using buttons 
  else if (a_hour_val == 1023 && a_min_val != 1023){
    if (a_hour < 24){
      a_hour = a_hour + 1;
    }
    else {
      a_hour = 0;
    }
    delay(200); 
  }
  else if (a_min_val == 1023 && a_hour_val != 1023){
    if (a_minute < 60){
      a_minute = a_minute + 1;
    }
    else {
      a_minute = 0;
    }
    delay(200);
  }

  // displaying alarm and real time on lcd
  lcd.setCursor(11, 0);
  lcd.print("alarm");
  lcd.setCursor(9, 1);
  lcd.print(a_date);
  lcd.setCursor(0, 0);
  lcd.print("time");
  lcd.setCursor(0, 1);
  lcd.print(r_date);

  // displaying alarm message and checking the level of brightness
  if (r_hour == a_hour && r_minute == a_minute){
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.print("Wakey Wakey!It's");
    lcd.setCursor(0,1);
    lcd.print("time for school!");
    tidin = 1;
    brightness_t1 = analogRead(photres_pin);
    brightness_t0 = brightness_t1;
    while (tidin){
      for (int i = 0; i<10; i++){
        tone(13,tones[i]);
        brightness_t0 = brightness_t1;
        delay(1000);
        brightness_t1 = analogRead(photres_pin);
        if (brightness_t1 - brightness_t0 > 200){
          tidin = 0;
          a_hour = 0;
          a_minute = 0;
          noTone(13);
          lcd.begin(16,2);
          break;
        }
      }
    }
  }
}
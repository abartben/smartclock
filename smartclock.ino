//We always have to include the library
#include "LedControl.h"
#include <Time.h>

#include "notes.h"


//this has to be changed
#define SSID "Wifi SSID"
#define PASS "WIFI PASSOWRD"
 
 
 
#include <SoftwareSerial.h>
SoftwareSerial ESPserial(2  , 4); // RX | TX of ESP module

#include <Wire.h>
#include <SparkFun_APDS9960.h>

LedControl lc=LedControl(12,13,10,4);

SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;
byte number_to_led[9] = {B00000000,B00000001,B00000011,B00000111,B00001111,B00011111,B00111111,B01111111,B11111111};
byte number_to_led2[9] = {B11111111,B11111110,B11111100,B11111000,B11110000,B11100000,B11000000,B10000000,B00000000};

int proximity_count = 0;
uint8_t proximity_data = 0;

int reveil_armed = 0; //0 = not armed; 1 = armed; 2 = ringing
int reveil_heure = 00; //hour of alarm
int reveil_minute = 00; //minute of alarm
int reveil_jour = 00; //day of alarm

int time_to_alarm = 0; //time until alarm rings in minutes

int a,b,c,d; //used for animations

int dom_tomorrow = 0; //dom = day of month

 int intensity = 10;

void setup()
{
  
  setTime(00,00,00 ,25,01,2015);
  
  pinMode(5, OUTPUT); //R
  pinMode(6, OUTPUT); //G
  pinMode(9, OUTPUT); //B
  
  pinMode(3, OUTPUT);//buzzer
  
  pinMode(8, OUTPUT); //ESP RESET
  
  //alarm();
  //beep beep
  tone(3,440);
  delay(100);
  noTone(3);
  delay(100);
  tone(3,440);
  delay(100);
  noTone(3);
  
  #ifdef serial
    Serial.begin(9600); 
    Serial.println("bijour");
  #endif
  ESP_init();
  while(ATcheck() == false)
  {
     #ifdef serial
     Serial.println("ATcheck is wrong ... waiting ...");
     #endif
     delay(1000); 
  }
  connectWiFi();
  apds_init();
  matrix_init();
  matrix_wifi();

  while(isConnected()==false)
  {
     #ifdef serial
     Serial.println("Not connected to AP");
     #endif
     rgb(random(0,10)*10,random(0,10)*10,random(0,10)*10);
     matrix_update();
     matrix_luminosity();
     delay(100);
     matrix_wifi();
     delay(2000); 
     connectWiFi();
     delay(3000);
  }
  delay(500);
  while(getSettings()==false)
  {
     matrix_wifi();
     rgb(random(0,10)*10,random(0,10)*10,random(0,10)*10);
     if(isConnected()==false)
     {
        connectWiFi(); 
     }
     delay(3000);
  }
  rgb(0,0,0);
  #ifdef serial
    Serial.println("entering loop");
  #endif
  //beep beep
  /*tone(3,240);
  delay(100);
  noTone(3);
  delay(100);
  tone(3,330);
  delay(150);
  noTone(3);
  delay(100);
  tone(3,430);
  delay(200);
  noTone(3);*/
  
  for(int a = 0;a<20 ;a++)
         {
            rgb(random(0,10)*10,random(0,10)*10,random(0,10)*10);
            tone(3, random(20,400));
            delay(50);
         }
         
         noTone(3);
  
  //animate(4);
  
}

void loop()
{
   for(int i=0;i<35;i++)
   {
     //matrix_animate();
      
     
     if(reveil_armed == 1)
       {
        
        
        //Set color of led
                 
                 time_to_alarm = calc_time_to_alarm();
                 
                 //Serial.print("tta");
                 //Serial.println(time_to_alarm);
                 
                 if(time_to_alarm > 0)
                 {
                     if(time_to_alarm >= 8*60)
                     {
                        
                        rgb_fade(505, intensity); //code 505
                     }
                     else
                     {
                        rgb_fade(time_to_alarm,intensity); 
                     }
         if(apds.readProximity(proximity_data))
         {
             
             //Serial.print("proximity : ");
             //Serial.println(proximity_data);
               if(proximity_data > 200)
               {
                 
                  //if proximity sensor is on then show time of alarm
                 
                   //reveil_heure // reveil_minute
                   show_chiffre(3,reveil_heure/10);
                   show_chiffre(2,reveil_heure%10);
                   show_chiffre(1,reveil_minute/10);
                   show_chiffre(0,reveil_minute%10);
                 
               }
               else
               {
                 matrix_update();
                 matrix_luminosity();
               }
               
           }
      
        }
        else
        {
           matrix_update();
           matrix_luminosity(); 
        }
        
        if(reveil_jour == day() && (reveil_heure*60 + reveil_minute) <= (hour()*60 + minute()) )
        {
           
          
          reveil_armed = 2;
          
          matrix_update();
          matrix_luminosity();
                  
           
        }
        
      }
      else if(reveil_armed == 2)
      {
         //alarm !
         
          rgb(255,255,255);
         
           matrix_update();
           matrix_luminosity();  
         
          
           //Serial.println("ALARME !");
           
           /*watch_stop_alarm();
           if(reveil_armed == 2) //to avoid double beep
           {
             tone(3, 440);
             delay(50);
             noTone(3);
             delay(50);
             tone(3, 440);
             delay(50);
             noTone(3);
             delay(50);
             watch_stop_alarm();
           }
           
           if(reveil_armed == 2) //to avoid double beep
           {
             
             tone(3, 440);
             delay(500);
             noTone(3);
             watch_stop_alarm();
           }*/
           
           alarm_happy();
           
          // getSettings();
          
           
      }
      else
      {
         rgb(0,0,0); //black LED 
         matrix_update();
          matrix_luminosity();
      }
   }
   #ifdef serial
   Serial.println("routine");
   #endif
   //ATcheck();
   
   
  if(isConnected()==true)
   {
       getSettings();
       #ifdef serial
       Serial.println("is connected loop");
       #endif
       //matrix_wifi();
   }
   else
   {
      #ifdef serial
      Serial.println("Not connected");
      #endif
      matrix_wifi();
      delay(100);
      matrix_update();
      connectWiFi();
      delay(1500); 
   }
}

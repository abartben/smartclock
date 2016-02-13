void alarm()
{
   for(int i=0;i<50;i++)
   {
      tone(3,map(i,0,50,200,600));
      delay(map(i,0,50,200,20));
      noTone(3);
      delay(map(i,0,50,100,10));
   } 
}

void alarm_happy()
{
 
    
  
   while(reveil_armed == 2)
   {
     
       rgb(255,255,255);
     
       int melody[] = {NOTE_C4,NOTE_C4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_F4,NOTE_G4,NOTE_A4};
       int noteDurations[] = {4,4,4,4,4,4,4,4,4,4,2};
       play_melody(melody,noteDurations,11);
       delay(500);
       
       
       
       if(reveil_armed==2)
       {
         rgb(random(0,10)*10,random(0,10)*10,random(0,10)*10);
         digitalWrite(3, HIGH);
         delay(50);
         digitalWrite(3, LOW);
         
         /*for(int a = 0;a<5 ;a++)
         {
            rgb(random(0,10)*10,random(0,10)*10,random(0,10)*10);
            tone(3, random(20,400));
            delay(50);
         }
         
         noTone(3);*/
         delay(500);
         
         rgb(random(0,10)*10,random(0,10)*10,random(0,10)*10);
         digitalWrite(3, HIGH);
         delay(50);
         digitalWrite(3, LOW);
         
         /*for(int a = 0;a<5;a++)
         {
            rgb(random(0,10)*10,random(0,10)*10,random(0,10)*10);
            tone(3, random(20,400));
            delay(50);
         }
         
         noTone(3);*/
         delay(500);
         
         
         rgb(255,255,255);
         
         /*melody = {NOTE_C4,NOTE_C4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_F4,NOTE_G4,NOTE_A4};
         noteDurations = {4,4,4,4,4,4,4,4,4,4,2};
         play_melody(melody,noteDurations,11);
         delay(500);*/
         
       }
       
       getSettings();
       matrix_update();
       
   }
 
  
}

void rgb_fade(int i, float intensity)
{
  //i va de 0 à 100
  //intensity va de 0.0 à 1.0 (1.0 étant l'intensité max)
   int r,g,b;
   
   
   
   
      if(i == 505)
   {
      r = 255;
      g = 255;
      b = 255; 
   }
   else
   {
     
     i = map(i,0,480,100,0);
     
     // 0 = bleu
     // 50 = vert
     // 100 = jaune
     // 200 = rouge
     
     if(i< 25)
     {
        r = map(i,0,25,150,0);
        b = 255;
        g = 0;
     }
     else if(i<50)
     {
         //rgb(255,0,0);
         r = 0;
         g = map(i,25,50,0,255);
         b = map(i,25,50,255,0);
     }
     else if(i< 75)
     {
         r = map(i,50,75,0,255);
         g = 255;
         b = 0;
     }
     else
     {
         r = 255;
         g = map(i,75,100,255,0);
         b = 0;
     }
   
   }
   
   //intensity = max((intensity+1)/15,0.008);
   
   
   
   intensity = intensity/10;
   intensity = constrain(intensity,0.025,1.5);
   
   //Serial.print("intensity : ");
   //Serial.println(intensity);
   
   rgb(r*intensity,g * intensity,b * intensity);
   
   //rgb(r,g,b);
}

int calc_time_to_alarm()
{
  
  //Serial.println("calc_time_to_alarm");
  
  if(reveil_armed != 2) //if not ringing
                 {
                 
                   if(reveil_jour == day())
                   {
                      //alarm is for today
                     
                     if( (reveil_heure*60 + reveil_minute) > (hour()*60 + minute()) ) //only if set before time of alarm
                     {
                            reveil_armed = 1;
                            
                            time_to_alarm = (reveil_heure*60 + reveil_minute) - (hour()*60 + minute());
                            
                            #ifdef serial
                            Serial.print("Alarm for today in ");
                            Serial.print(time_to_alarm);
                            Serial.println(" minutes");
                            #endif
                     }
                      
                   }
                   else if(reveil_jour == dom_tomorrow)
                   {
                      reveil_armed = 1; //if it's for tomorrow then it has to be armed
                      
                      //time_to_alarm = time to midnight + time of alarm
                      
                      time_to_alarm = 24*60 - (hour()*60 + minute()) + reveil_heure*60 + reveil_minute;
                      
                      #ifdef serial
                      Serial.print("Alarm for tomorrow in ");
                      Serial.print(time_to_alarm);
                      Serial.println(" minutes");
                      #endif
                      
                   }
                 
                 }
                 
                  return(time_to_alarm);
}

void led_demo()
{
   //function to display how the led will change
  
  
   
  
  for(int i=0;i< 480;i++)
  {
      show_chiffre(3,0);
      show_chiffre(2,i/60%10);
      show_chiffre(1,i/10);
      show_chiffre(0,i%10);
      
      if(i%60 == 0)
      {
        lc.setIntensity(0,15);
        lc.setIntensity(1,15);
        lc.setIntensity(2,15);
        lc.setIntensity(3,15);
        
        rgb_fade(i,15);
        
        delay(200);
      }
      else if(i%60 == 1)
      {
         lc.setIntensity(0,10);
         lc.setIntensity(1,10);
         lc.setIntensity(2,10);
         lc.setIntensity(3,10); 
      }
      
      rgb_fade(i,10);
      
  }
   
}

void rgb(int r,int g,int b)
{
   analogWrite(5 ,255-r);
   analogWrite(6 ,255-g);
   analogWrite(9, 255-b);
}

//in order to avoid to wait too long before turning the alarm off
void watch_stop_alarm() //function checking if proximity is on
{
  
 
           if(apds.readProximity(proximity_data))
           {
             
             //Serial.print("proximity : ");
             //Serial.println(proximity_data);
               if(proximity_data > 200)
               {
                  proximity_count++; 
                  
                  if(proximity_count > 2) //need at least three time to make sure it's not a false positive
                  {
                    
                     //end of alarm !
                    
                     tone(3,520);
                     delay(100);
                     noTone(3);
                     delay(100);
                     tone(3,520);
                     delay(150);
                     noTone(3);
                    
                    
                     reveil_armed = 0;
                     
                  }
                  
               }
               else
               {
                 proximity_count = 0;
                 //back to zero
               }
           }  
}

void play_melody(int melody[],int noteDurations[],int length)
{
    for (int thisNote = 0; thisNote <length && reveil_armed == 2; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 850/noteDurations[thisNote];
    tone(3, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.20;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(3);
    watch_stop_alarm();
  }
}

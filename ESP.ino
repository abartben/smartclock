void ESP_init()
{
  ESPserial.begin(9600);
  
  //digitalWrite(8, HIGH);
  //delay(10);
  //digitalWrite(8, LOW);
  ESPserial.println("AT+CWQAP");
  delay(100);
  ESPserial.println("AT+CIPMUX=1");
  delay(200);
  ESPserial.println("AT+CWMODE=1");
  delay(100);
  ESPserial.println("AT+CWJAP?");
    while ( ESPserial.available() )  
    {
    
      #ifdef serial      
        Serial.write( ESPserial.read() );
      #else
        ESPserial.read();
      #endif
  }  
    

}

boolean ATcheck()
{
    #ifdef serial
      Serial.println("AT check");
    #endif
    while(ESPserial.available())
   {
      ESPserial.read(); 
   }
   ESPserial.println("AT");
   delay(10);
   
   if(ESPserial.find("OK"))
   {
   
   return(true);
   }
   else
   {
       return(false);
   }
}

int getSettings()
{
  #ifdef serial
    Serial.println("getSettings()");
  #endif
  
   while(ESPserial.available())
   {
      ESPserial.read(); 
   }
    //delay(10);
    ESPserial.println("AT+CIPSTART=4,\"TCP\",\"ipadress\",2023"); //change ip adress here
    delay(50);
    if(ESPserial.find("4,CONNECT"))
    {
      
       if(ESPserial.find("OK"))
       {
          #ifdef serial
            Serial.println("OK");
          #endif
          delay(100);
          ///while ( ESPserial.available() )   {  Serial.write( ESPserial.read() );}
          if(ESPserial.find("+IPD"))
           {
               if(ESPserial.find(":"))
               {
           
                 
                 //Serial.println("proutprout");
             
                 int heures = ESPserial.parseInt();
                 int minutes = ESPserial.parseInt();
                 int secondes = ESPserial.parseInt();
                 
                 int jour = ESPserial.parseInt();
                 int mois = ESPserial.parseInt();
                 int annee = ESPserial.parseInt();
                 
                 
                 
                 //delay(50);
                 
                 ESPserial.find(":");
                 
                 int reveil_jour_tmp = ESPserial.parseInt();
                 int reveil_heure_tmp = ESPserial.parseInt();
                 int reveil_minute_tmp = ESPserial.parseInt();
                 
                 
                 #ifdef serial
                 
                   Serial.print(heures);
                   Serial.print(":");
                   Serial.print(minutes);
                   Serial.print(":");
                   Serial.print(secondes);
                   
                   Serial.print(" - ");
                   Serial.print(jour);
                   Serial.print("/");
                   Serial.print(mois);
                   Serial.print("/");
                   Serial.print(annee);
                   
                   Serial.print(" - REVEIL : ");
                   Serial.print(reveil_jour_tmp);
                   Serial.print("/");
                   Serial.print(reveil_heure_tmp);
                   Serial.print(":");
                   Serial.print(reveil_minute_tmp);
                 
                 
                 
                 Serial.println("");
                 
                 #endif
                 
                
                 //alarm stuff
                 reveil_jour = reveil_jour_tmp;
                 reveil_heure = reveil_heure_tmp;
                 reveil_minute = reveil_minute_tmp;
                 
                 setTime(heures,minutes,secondes ,jour,mois,annee);

                 
                 //probably not the best way but it works so ...
                 
                 time_t today = now();
                 time_t tomorow = today + 86400;
                 
                 dom_tomorrow = day(tomorow); //day of month
                 
                 
                /* Serial.print(day(today));
                 Serial.print(" - ");
                 Serial.println(day(tomorow));
                 
                 Serial.print(today);
                 Serial.print(" - ");
                 Serial.println(tomorow);*/
                 
                 time_to_alarm = 0; //time remaining before the alarm in minutes
                 
                 calc_time_to_alarm();
                 
                 
                 if(reveil_jour == 42) //when alarm is disactivated the day is 42
                 {
                    rgb(0,0,0);
                    reveil_armed = 0; 
                 }
                 
                 return(true);
                 
                 
                
               }
                 

               
           }
           else
           {
              #ifdef serial
                Serial.println("pas ipd"); 
              #endif
           }
          
       } 
       else
       {
          #ifdef serial
            Serial.println("pas ok"); 
          #endif
          return(false);
       }
    }
    else
    {
       #ifdef serial
         Serial.println("pas connect"); 
       #endif
       return(false);
    }
    
    return(false);

  
}



boolean isConnected()
{
  while ( ESPserial.available() )   { ESPserial.read();}  
  
  
  for(int i=0;i<5;i++) //try 5 times to get the answer
  {
    
    if(ATcheck())
    {
  
      //ESPserial.flush();
       ESPserial.println("AT+CWJAP?"); 
       delay(150);
       #ifdef serial
         Serial.println("isco?");
       #endif
       //while( ESPserial.available()) { Serial.write(ESPserial.read());}
       if(ESPserial.find("+CWJAP:"))
       {
         ESPserial.find("OK");
          #ifdef serial
            Serial.println("connected");
          #endif
         return(true);
       }
       else
       {
          ESPserial.find("OK");
          #ifdef serial
            Serial.println("not connected");
          #endif
          return(false); 
       }
   
    }
    else
    {
        #ifdef serial
          Serial.println("Delay busy");
        #endif
        delay(1500);
        
    }  
   
  }
   return(false);
}

 
 boolean connectWiFi(){
  #ifdef serial
    Serial.println("connectWifi");
  #endif
  //ESPserial.println("AT+CWMODE=1");
  // while(!ESPserial.available())
  
  while(ESPserial.available())
  {
     #ifdef serial
       Serial.write(ESPserial.read());
     #else
       ESPserial.read();
     #endif
  }
  
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  
  
  for(int i=0;i<5;i++) //5 tries to get the AT check
  {
      if(ATcheck())
      {
          ESPserial.println(cmd);
          
          #ifdef serial
            Serial.println(cmd);
          #endif
          
          //Serial.println("debug MODE");
          //debug();
          
          //delay(200);
           //while(!ESPserial.available())
          
          
         /* while(ESPserial.available())
          {
             Serial.write(ESPserial.read()); 
          }*/
          
          delay(300);
          if(ESPserial.find("OK")){
            Serial.println("OOOOK");
             
             return(true);
          }
      }
  }
  
  
  return(false);
}

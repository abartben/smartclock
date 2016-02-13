void matrix_init()
{
   /*
    INIT of LCD screen
  */ 
  
  //we have already set the number of devices when we created the LedControl
  int devices=lc.getDeviceCount();
  //we have to init all devices in a loop
  for(int address=0;address<devices;address++) {
    /*The MAX72XX is in power-saving mode on startup*/
    lc.shutdown(address,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(address,10);
    /* and clear the display */
    lc.clearDisplay(address);
  }
   
}

void matrix_update()
{
      show_chiffre(3,hour()/10);
      show_chiffre(2,hour()%10);
      show_chiffre(1,minute()/10);
      show_chiffre(0,minute()%10);
      show_bar(second()*32/59);
}

void matrix_luminosity()
{
   if (  apds.readAmbientLight(ambient_light)) 
  {
    
      //Serial.println(ambient_light);
    
      intensity = map(ambient_light,50 ,2000,0,15);
      intensity = constrain(intensity,0,15);
      //Serial.println(intensity);
      lc.setIntensity(0,intensity);
      lc.setIntensity(1,intensity);
      lc.setIntensity(2,intensity);
      lc.setIntensity(3,intensity);
    
  } 
}

void matrix_wifi()
{
   lc.setColumn(3, 0,B00000000);
   lc.setColumn(3, 1,B01000100);
   lc.setColumn(3, 2,B01000100);
   lc.setColumn(3, 3,B01010100);
   lc.setColumn(3, 4,B01010100);
   lc.setColumn(3, 5,B01101100);
   lc.setColumn(3, 6,B00000000);
   lc.setColumn(3, 7,B00000000);
   
   lc.setColumn(2, 0,B00000000);
   lc.setColumn(2, 1,B00000000);
   lc.setColumn(2, 2,B00000000);
   lc.setColumn(2, 3,B00010000);
   lc.setColumn(2, 4,B00000000);
   lc.setColumn(2, 5,B00010000);
   lc.setColumn(2, 6,B00010000);
   lc.setColumn(2, 7,B00110000);
   
   
   lc.setColumn(1, 0,B00000000);
   lc.setColumn(1, 1,B00011000);
   lc.setColumn(1, 2,B00000100);
   lc.setColumn(1, 3,B00001100);
   lc.setColumn(1, 4,B00000100);
   lc.setColumn(1, 5,B00000100);
   lc.setColumn(1, 6,B00000000);
   lc.setColumn(1, 7,B00000000);
   
   lc.setColumn(0, 0,B00000000);
   lc.setColumn(0, 1,B00000000);
   lc.setColumn(0, 2,B00000000);
   lc.setColumn(0, 3,B00001000);
   lc.setColumn(0, 4,B00000000);
   lc.setColumn(0, 5,B00001000);
   lc.setColumn(0, 6,B00001000);
   lc.setColumn(0, 7,B00011000);
  
   
}


void show_chiffre(int address,int chiffre)
{

 int offset = 0;
  
  if(address == 0 || address == 2)
  {
    offset = 0; 
  }
  else
  {
    offset = -2; 
  }
  
  if(chiffre == 1)
   {
       //lc.setColumn(address, offset + 0,B00000000);
      //lc.setColumn(addzress, offset + 1,B00000000);
      lc.setColumn(address, offset + 2,B00010000);
      lc.setColumn(address, offset + 3,B00011000);
      lc.setColumn(address, offset + 4,B00010100);
      lc.setColumn(address, offset + 5,B00010000);
      lc.setColumn(address, offset + 6,B00010000);
      lc.setColumn(address, offset + 7,B00111000);
   }
   else if(chiffre == 2)
   {
       //lc.setColumn(address, offset + 0,B00000000);
      //lc.setColumn(address, offset + 1,B00000000);
      lc.setColumn(address, offset + 2,B00011000);
      lc.setColumn(address, offset + 3,B00100100);
      lc.setColumn(address, offset + 4,B00010000);
      lc.setColumn(address, offset + 5,B00001000);
      lc.setColumn(address, offset + 6,B00000100);
      lc.setColumn(address, offset + 7,B00111100);  
   }
   else if(chiffre == 3)
   {
     //lc.setColumn(address, offset + 0,B00000000);
      //lc.setColumn(address, offset + 1,B00000000);
      lc.setColumn(address, offset + 2,B00011100);
      lc.setColumn(address, offset + 3,B00100000);
      lc.setColumn(address, offset + 4,B00011000);
      lc.setColumn(address, offset + 5,B00100000);
      lc.setColumn(address, offset + 6,B00100000);
      lc.setColumn(address, offset + 7,B00011100);
   }
   else if(chiffre == 4)
   {
      //lc.setColumn(address, offset + 0,B00000000);
      //lc.setColumn(address, offset + 1,B00000000);
      lc.setColumn(address, offset + 2,B00010000);
      lc.setColumn(address, offset + 3,B00011000);
      lc.setColumn(address, offset + 4,B00010100);
      lc.setColumn(address, offset + 5,B00111110);
      lc.setColumn(address, offset + 6,B00010000);
      lc.setColumn(address, offset + 7,B00010000); 
   }
   else if(chiffre == 5)
   {
       //lc.setColumn(address, offset + 0,B00000000);
        //lc.setColumn(address, offset + 1,B00000000);
        lc.setColumn(address, offset + 2,B00111100);
        lc.setColumn(address, offset + 3,B00000100);
        lc.setColumn(address, offset + 4,B00011100);
        lc.setColumn(address, offset + 5,B00100000);
        lc.setColumn(address, offset + 6,B00100100);
        lc.setColumn(address, offset + 7,B00011000);
   }
   else if(chiffre == 6)
   {
     
       //lc.setColumn(address, offset + 0,B00000000);
        //lc.setColumn(address, offset + 1,B00000000);
        lc.setColumn(address, offset + 2,B00011000);
        lc.setColumn(address, offset + 3,B00000100);
        lc.setColumn(address, offset + 4,B00011100);
        lc.setColumn(address, offset + 5,B00100100);
        lc.setColumn(address, offset + 6,B00100100);
        lc.setColumn(address, offset + 7,B00011000);
     
   }
   else if(chiffre == 7)
   {
      //lc.setColumn(address, offset + 0,B00000000);
      //lc.setColumn(address, offset + 1,B00000000);
      lc.setColumn(address, offset + 2,B00111100);
      lc.setColumn(address, offset + 3,B00100000);
      lc.setColumn(address, offset + 4,B00010000);
      lc.setColumn(address, offset + 5,B00001000);
      lc.setColumn(address, offset + 6,B00000100);
      lc.setColumn(address, offset + 7,B00000100); 
   }
   else if(chiffre == 8)
   {
      //lc.setColumn(address, offset + 0,B00000000);
      //lc.setColumn(address, offset + 1,B00000000);
      lc.setColumn(address, offset + 2,B00011000);
      lc.setColumn(address, offset + 3,B00100100);
      lc.setColumn(address, offset + 4,B00011000);
      lc.setColumn(address, offset + 5,B00100100);
      lc.setColumn(address, offset + 6,B00100100);
      lc.setColumn(address, offset + 7,B00011000);
   }
   else if(chiffre == 9)
   {
      //lc.setColumn(address, offset + 0,B00000000);
      //lc.setColumn(address, offset + 1,B00000000);
      lc.setColumn(address, offset + 2,B00011000);
      lc.setColumn(address, offset + 3,B00100100);
      lc.setColumn(address, offset + 4,B00111000);
      lc.setColumn(address, offset + 5,B00100000);
      lc.setColumn(address, offset + 6,B00100100);
      lc.setColumn(address, offset + 7,B00011000);
   }
   else
   {
     //lc.setColumn(address, offset + 0,B00000000);
  //lc.setColumn(address, offset + 1,B00000000);
  lc.setColumn(address, offset + 2,B00011000);
  lc.setColumn(address, offset + 3,B00100100);
  lc.setColumn(address, offset + 4,B00100100);
  lc.setColumn(address, offset + 5,B00100100);
  lc.setColumn(address, offset + 6,B00100100);
  lc.setColumn(address, offset + 7,B00011000);
   }
 }
 
 void show_bar(int value)
{
   value = constrain(value,0,32);
  
   //int tmp = min(8,value);
   
   
   if(minute()%2 == 0)
   {
   
   /*if(value==0)
   {
      lc.setColumn(3,7,B00000000); 
       lc.setColumn(2,0,B00000000); 
        lc.setColumn(1,7,B00000000); 
         lc.setColumn(0,0,B00000000); 
   } */
   lc.setColumn(3,7,number_to_led2[constrain(value,0,8)]);
   lc.setColumn(2,0,number_to_led2[constrain(value- 8,0,8)]);
   lc.setColumn(1,7,number_to_led2[constrain(value- 16,0,8)]);
   lc.setColumn(0,0,number_to_led2[constrain(value- 24,0,8)]);
   }
   else
   {
     
      /* if(value==0)
       {
          lc.setColumn(3,7,B11111111); 
           lc.setColumn(2,0,B11111111); 
            lc.setColumn(1,7,B11111111); 
             lc.setColumn(0,0,B11111111); 
       } */
       lc.setColumn(3,7,number_to_led[constrain(value,0,8)]);
       lc.setColumn(2,0,number_to_led[constrain(value- 8,0,8)]);
       lc.setColumn(1,7,number_to_led[constrain(value- 16,0,8)]);
       lc.setColumn(0,0,number_to_led[constrain(value- 24,0,8)]);
     
   }
   /*Serial.print(constrain(value,0,8));
   Serial.print(" ");
   Serial.print(constrain(value- 8,0,8));
   Serial.print(" ");
   Serial.print(constrain(value- 16,0,8));
   Serial.print(" ");
   Serial.println(constrain(value- 24,0,8));*/
   
}

void animate(int pas)
{
    for(int i = (4-pas)*5;i<20;i++)
    {
       if(i < 4)
       {
          show_chiffre(3, random(0,9));
       }
       else if(i < 8)
       {
           show_chiffre(3, random(0,9));
           show_chiffre(2, random(0,9));
       }
       else if(i< 12)
       {
           show_chiffre(2, random(0,9)); 
           show_chiffre(1, random(0,9));
       }
       else if(i< 16)
       {
           show_chiffre(1, random(0,9)); 
           show_chiffre(0, random(0,9));
       }
       else
       {
          show_chiffre(0, random(0,9)); 
       }
     
       
       
       if(i==8)
       {
           show_chiffre(3,hour()/10);
       }
       else if(i==12)
       { 
           show_chiffre(2,hour()%10);
       }
       else if(i==16)
       {
           show_chiffre(1,minute()/10);
       }
       if(pas==4)
       {
         show_bar(second()*32*i/60/20);
       }
       //delay(0);
       
      
        
    }
    show_chiffre(0,minute()%10);
    
    a = hour()/10;
  b = hour()%10;
  c = minute()/10;
  d = minute()%10;
    
}

boolean matrix_animate()
{
  if(a != hour()/10)
  {
     animate(4); 
      a = hour()/10;
      b = hour()%10;
      c = minute()/10;
      d = minute()%10;
     return(true);
  }
  
  if(b != hour()%10)
  {
     animate(3);
      b = hour()%10;
      c = minute()/10;
      d = minute()%10;
     return(true); 
  }
  
  if(c != minute()/10)
  {
     animate(2);
      c = minute()/10;
      d = minute()%10; 
     return(true);
  }
  
  if( d!= minute()%10)
  {
     animate(1);
    d = minute()%10; 
    return(true);
  }
  
  
 
}

/*

 a = hour()/10;
       b = hour()%10;
       c = minute()/10;
       d = minute()%10;
       
       */

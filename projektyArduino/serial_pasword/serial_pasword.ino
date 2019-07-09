#include <string.h>
#include <EEPROM.h>

char c = ' ';
int a = 1;
char ent[20];
int i = 0;
int tr = 0;
int login = 0;
int bin = ' ';
char newPass1[20];
char newPass2[20];
int aut = 0;
char pass[20];

void setup() {
  Serial.begin (9600);
  loadEEPROM();
}

void updateEEPROM () {
  i = 0;
 while (i != 20){
    EEPROM.write(i,pass[i]);
    i++;
  } 
  i=0;
}

void loadEEPROM () {
 i = 0;
 while (i != 20){
    pass[i] = EEPROM.read(i);
    i++;
  } 
  i=0;
}

void seeDocuments () {
  Serial.println("  Documents:");
  Serial.println("flag:");
  Serial.println();
}


void vycistiVstup()
{
  delay(100);
  while (Serial.available()){
     Serial.read();
  }
}

void changePassword () {
    loginNow();
    if (login == 0) return;
    
    delay(500);
    vycistiVstup();
     i = 0;
    Serial.println("Enter new password");

    while (1)
    {
      while (Serial.available()== 0){}
      char c = Serial.read ();
      if (c == '\n') break;
      newPass1[i]  = c;
      i++;
      if (i == 20) break;
    }
    newPass1[i] = 0;
    
    i = 0;
    Serial.println("Confirm new password");
    while (1)
    {
      while (Serial.available()== 0){}
      char c = Serial.read ();
      if (c == '\n') break;
      newPass2[i]  = c;
      i++;
      if (i == 20) break;
    }
    newPass2[i] = 0;

    if (strcmp(newPass1, newPass2) == 0) {
        Serial.println ("Password changed");
        i = 0;
        while (i < 20) { pass[i] = newPass1[i]; i++; }
        updateEEPROM();
        aut = 0;
    }
    else 
    {
       Serial.println("Passwords do not match");
       Serial.println ();
    }
}

void loginNow()
{
   Serial.println ("Password Required");

   i = 0;
   while (1)
   {
     if (Serial.available()) {
       char c = Serial.read ();
       if (c == '\n') break;
       ent[i]  = c;
       i++;
       if (i == 20) break;
     }
   }
   ent[i] = 0;
   
   if (strcmp(ent, pass) == 0) {
        Serial.println("ACCSESS");
        tr = 0;
        login = 1;
   }
   else {
      Serial.println("NO ACCESS");
      login = 0;
      tr++;
      if (tr == 3){
        Serial.println ("You tried 3 times incorrectly wait 5 seconds");
        Serial.end();
        delay (5000);
        Serial.begin (9600);
        tr = 0;
      }
   }  
}

void loop() 
{
   if (login)
   {
     Serial.println("Choose Option");
     Serial.println("");
     Serial.println("[1] Display data");
     Serial.println("[2] Change Pssword");
     Serial.println("[3] Exit");
     Serial.print("=> ");
     while (Serial.available() !=1){}
     char b = Serial.read ();
     Serial.println (b);
     Serial.println ();
      vycistiVstup();
     if (b == '1') 
     {
      seeDocuments();
      
     } else if (b == '2')
     {
      changePassword ();
     } else if (b == '3')
     {
       login = 0;
     } else {
        Serial.println ("Error: Not a Valid character");
     }
     
       i = 0;
       delay (50);
       
       vycistiVstup();
   }
   else loginNow();   
}

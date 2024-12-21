
#include <DS3232RTC.h>      // https://github.com/JChristensen/DS3232RTC
#include <Streaming.h>      // http://arduiniana.org/libraries/streaming/

  
  static time_t tLast;
  time_t t;
  tmElements_t tm;
#include <LiquidCrystal.h>
LiquidCrystal lcd(13 ,12, 11 , 10 , 9 , 8);
unsigned long eskiZaman=0;
unsigned long yeniZaman;

float santigrat, fahrenheit;
#include <EEPROM.h>
int yay_address = 51;       
int ygun_address = 52;       
int yisi_caddress = 53;       
int yssi_caddress = 54;      
int ref_caddress = 55;       
int durum_caddress = 56;         
int basla_caddress = 57;                                 // the variable which holds the address in the eeprom
int cikim_gunu;

int son_durum_caddress =58;

int y_zaman_address =67;
int y_nem_address =68;
int s_nem_address =69;

int y_sic_address =70;
int s_sic_address =71;
int viyor_address =72;
int yumurta_son_gun;
int yumurta_son_ay;
int dinlenme_zamani=3;

int y_nem;
int s_nem;
int y_zaman;


int isi_led=4;
int rutubet_led=3;
int yumurta_led=2;

int isi_role=A0;
int rutubet_role=A1;
int yumurta_role=A2;
//****************sıcaklık***************
#include <dht11.h>
dht11 DHT11; 
int sicaklik = 0;
int nem = 0;
//***********buton*******************
int menu=0;
int eksi_pin=5;
int arti_pin=6;
int menu_pin=7;
//***********buton*******************


//*****************saat**********************


int yil = 0 ;
int ay;
int gun ;
int saat;
int dakika ;
int saniye ;

int son_durum=0;

int viyor_durum=0;

int y_ay=0;
int y_gun=0;
int s_ay=0;
int s_gun=0;
int y_sic=0;
int s_sic=0;
int ref=0;
int basla=0;
int durum=0;
void setup()
{
  Serial.begin(9600);  // serial ekran haberleşme portalı

   setSyncProvider(RTC.get);
    Serial << F("RTC Sync");
    if (timeStatus() != timeSet) Serial << F(" FAIL!");
    Serial << endl;

pinMode(isi_role,OUTPUT);
pinMode(rutubet_role,OUTPUT);
pinMode(yumurta_role,OUTPUT);


pinMode(isi_led,OUTPUT);
pinMode(rutubet_led,OUTPUT);
pinMode(yumurta_led,OUTPUT);


pinMode(eksi_pin,INPUT);
pinMode(arti_pin,INPUT);
pinMode(menu_pin,INPUT);


digitalWrite(isi_role,LOW);
digitalWrite(rutubet_role,LOW);
digitalWrite(yumurta_role,LOW);

  lcd.begin(16, 2);
  DHT11.attach(A3);

lcd.clear();


  
 son_durum = EEPROM.read(son_durum_caddress);  
 y_sic = EEPROM.read(y_sic_address);  
 s_sic = EEPROM.read(s_sic_address);  
  
 y_nem = EEPROM.read(y_nem_address);  
 s_nem = EEPROM.read(s_nem_address);  
 y_zaman= EEPROM.read(y_zaman_address); 
 
 y_ay = EEPROM.read(yay_address);  
 y_gun = EEPROM.read(ygun_address);  


 
 ref = 1;  
 durum = EEPROM.read(durum_caddress);  
 basla = EEPROM.read(basla_caddress);  
 viyor_durum = EEPROM.read(viyor_address);  


digitalWrite(isi_role,LOW); 
digitalWrite(rutubet_role,LOW); 
digitalWrite(yumurta_role,LOW);

digitalWrite(isi_led,LOW); 
digitalWrite(rutubet_led,LOW); 
digitalWrite(yumurta_led,LOW);



lcd.setCursor (0, 0);lcd.print(" ALPER KARATAS  ");
lcd.setCursor (0, 1);lcd.print("  16008119058   ");
delay(2000);


son_durum=0;
basla=0;
// 
//  EEPROM.write(son_durum_caddress,(son_durum));  
//  EEPROM.write(basla_caddress,(basla));  
//
//EEPROM.write(viyor_address,(0)); 
//lcd.setCursor (0, 0);lcd.print("son_durum      ");lcd.print(son_durum);
//lcd.setCursor (0, 1);lcd.print("basla          ");lcd.print(basla);
//delay(2000);
////
//lcd.setCursor (0, 0);lcd.print("basla          ");lcd.print(basla);
//lcd.setCursor (0, 1);lcd.print("viyor_durum    ");lcd.print(viyor_durum);
delay(2000);
}
 void buton_oku()
{
  if(digitalRead(menu_pin)==1)menu++;
  if (menu > 10)menu = 0;
  if (menu < 0)menu = 0;

  while( digitalRead(menu_pin)==1 ){
    
    
  Serial.print(digitalRead(menu_pin));
  Serial.print(" ");
  Serial.print(digitalRead(arti_pin));
  Serial.print(" ");
  Serial.print(digitalRead(eksi_pin));
  Serial.print(" ");
  Serial.println(menu);
    
    }
}





void loop()
{ bas:
  buton_oku();
  
 t = now();
  if (t != tLast) {
    tLast = t;
    printDateTime(t);
    Serial << endl;
  }

  int chk = DHT11.read();
  sicaklik = (float)DHT11.temperature, 2;
  nem = (float)DHT11.humidity, 2;
   yeniZaman = millis(); 


if(digitalRead(arti_pin)==1 && digitalRead(eksi_pin)==1)
{
durum=0;
basla=0;
      y_gun=0;
      y_ay=0;
      son_durum=0;
  EEPROM.write(son_durum_caddress,(son_durum));  
  EEPROM.write(basla_caddress,(basla));  
  EEPROM.write(ygun_address,(y_gun));  
  EEPROM.write(yay_address,(y_ay));  
EEPROM.write(durum_caddress,(durum));  


digitalWrite(isi_role,LOW); 
digitalWrite(rutubet_role,LOW); 
digitalWrite(yumurta_role,LOW);

digitalWrite(isi_led,LOW); 
digitalWrite(rutubet_led,LOW); 
digitalWrite(yumurta_led,LOW);

lcd.setCursor (0, 0);lcd.print("SUREC DURDURULDU"); 
lcd.setCursor (0, 1);lcd.print("AYARLAR SIFIRLDI");

  delay(2500);
}

if(basla==0)
{
  
lcd.setCursor (0, 1);lcd.print(" SISTEM  KAPALI ");
}

if(basla==1)
{
  

digitalWrite(yumurta_led,LOW);

if(sicaklik > y_sic) {
 digitalWrite(isi_led,LOW);  digitalWrite(isi_role,LOW);lcd.setCursor (7,1);lcd.print("-"); 
}
if(sicaklik < y_sic-ref) {
digitalWrite(isi_led,HIGH); digitalWrite(isi_role,HIGH);lcd.setCursor (7,1);lcd.print("+"); 
}
if(nem > y_nem) {

digitalWrite(rutubet_led,LOW); digitalWrite(rutubet_role,LOW);lcd.setCursor (12,1);lcd.print("-"); 
}
if(nem < y_nem-ref) {
 
digitalWrite(rutubet_led,HIGH); digitalWrite(rutubet_role,HIGH);lcd.setCursor (12,1);lcd.print("+"); 
}


lcd.setCursor (0,1);
lcd.print(" "); if(y_ay<10)lcd.print("0");lcd.print(y_ay);lcd.print(":"); 
if(y_gun<10)lcd.print("0");lcd.print(y_gun);lcd.print(" ");  
lcd.setCursor (8,1); lcd.print("C"); lcd.print(sicaklik); lcd.print(" ");   
lcd.setCursor (13,1);lcd.print("%"); lcd.print(nem); 



if(((saat == 0) || (saat == 4) ||(saat == 8) ||(saat == 12) ||(saat == 16) ||(saat == 20)) && viyor_durum==0 && (basla==1))
{
viyor_durum=1;

EEPROM.write(viyor_address,(viyor_durum)); 
lcd.setCursor (0,0);lcd.print("   VILOR TERS   ");
lcd.setCursor (0,1);lcd.print("   CEVRILIYOR   ");
digitalWrite(yumurta_role,HIGH);
digitalWrite(yumurta_led,HIGH);

  delay(y_zaman*1000);
lcd.clear();
digitalWrite(yumurta_role,LOW);
digitalWrite(yumurta_led,LOW);

}
if(((saat == 2) || (saat == 6) ||(saat == 10) ||(saat == 14) ||(saat == 18) ||(saat == 22))&& viyor_durum ==1 && (basla==1))
{
  viyor_durum=0;
EEPROM.write(viyor_address,(viyor_durum)); 
digitalWrite(yumurta_role,HIGH);
digitalWrite(yumurta_led,HIGH);
lcd.setCursor (0,0);lcd.print("   VILOR TERS   ");
lcd.setCursor (0,1);lcd.print("   CEVRILIYOR   ");

  delay(y_zaman*1000);
lcd.clear();
digitalWrite(yumurta_role,LOW);
digitalWrite(yumurta_led,LOW);
}








}

   
if((y_ay == ay )&& (y_gun == gun) && (son_durum==0) && (basla==1))
{
  son_durum=1;

digitalWrite(yumurta_role,LOW);
digitalWrite(yumurta_led,LOW);
  EEPROM.write(durum_caddress,(durum));  
lcd.setCursor (0, 0);lcd.print("  ZAMAN  DOLDU  ");
lcd.setCursor (0, 1);lcd.print("  SON  3  GUN   ");
delay(3000);
lcd.setCursor (0, 0);lcd.print("DINLENDIRME     ");
lcd.setCursor (0, 1);lcd.print("ZAMANI BASLADI  ");
delay(3000);
    lcd.clear();
  EEPROM.write(son_durum_caddress,(son_durum));  
delay(3000);
lcd.clear();
  eskiZaman = yeniZaman;
}
if (son_durum==1)
{


 t = now();
  if (t != tLast) {
    tLast = t;
    printDateTime(t);
    Serial << endl;
  }



if(ay==1 ||ay==3 ||ay==5 ||ay==7 ||ay==8 ||ay==10 ||ay==12)
{
  yumurta_son_gun=gun+dinlenme_zamani;
  if (yumurta_son_gun>31){yumurta_son_gun=yumurta_son_gun-31; yumurta_son_ay=y_ay+1;}
  else{yumurta_son_ay=y_ay;}
}
else if(ay==4 ||ay==6 ||ay==9 ||ay==11)

{
  yumurta_son_gun=gun+dinlenme_zamani;
  if (yumurta_son_gun>30){yumurta_son_gun=yumurta_son_gun-30; yumurta_son_ay=y_ay+1;}
  else{yumurta_son_ay=y_ay;}
}


else if(ay==2)

{
  yumurta_son_gun=gun+dinlenme_zamani;
  if (yumurta_son_gun>28){yumurta_son_gun=yumurta_son_gun-28; yumurta_son_ay=y_ay+1;}
  else{yumurta_son_ay=y_ay;}
}

  
  while (yumurta_son_gun != gun)
{

digitalWrite(yumurta_role,LOW);

digitalWrite(yumurta_led,LOW);
t = now();
  if (t != tLast) {
    tLast = t;
    printDateTime(t);
    Serial << endl;
  }
  int chk = DHT11.read();
  sicaklik = (float)DHT11.temperature, 2;
  nem = (float)DHT11.humidity, 2;
 
  
  if(sicaklik > s_sic){
    digitalWrite(isi_role,LOW);
    digitalWrite(isi_led,LOW);
  }
 if(sicaklik < s_sic-ref){
  digitalWrite(isi_role,HIGH);
  digitalWrite(isi_led,HIGH);
  }

if(nem > s_nem) {
digitalWrite(rutubet_led,LOW);digitalWrite(rutubet_role,LOW);lcd.setCursor (5,1);lcd.print("-"); 
}
if(nem < s_nem-ref) {
 digitalWrite(rutubet_led,HIGH);digitalWrite(rutubet_role,HIGH);lcd.setCursor (0,1);lcd.setCursor (5,1);lcd.print("*"); 
}
 
  lcd.setCursor (0,1);
lcd.print("CIKIM(");
if(yumurta_son_gun<10)lcd.print("0");
lcd.print(yumurta_son_gun);
lcd.print(")C"); lcd.print(sicaklik); lcd.print(" %"); lcd.print(nem); 
  



if(digitalRead(arti_pin)==1 && digitalRead(eksi_pin)==1)
{
durum=0;
basla=0;
      y_gun=0;
      y_ay=0;
      son_durum=0;
  EEPROM.write(son_durum_caddress,(son_durum));  
  EEPROM.write(basla_caddress,(basla));  
  EEPROM.write(ygun_address,(y_gun));  
  EEPROM.write(yay_address,(y_ay));  
EEPROM.write(durum_caddress,(durum));  
digitalWrite(isi_role,LOW); 
digitalWrite(rutubet_role,LOW); 
digitalWrite(yumurta_role,LOW);  
digitalWrite(isi_led,LOW); 
digitalWrite(rutubet_led,LOW); 
digitalWrite(yumurta_led,LOW);
lcd.setCursor (0, 0);lcd.print("SUREC DURDURULDU"); 
lcd.setCursor (0, 1);lcd.print("AYARLAR SIFIRLDI");

  delay(2500);
  goto bas;
}


}

durum=0;
basla=0;
      y_gun=0;
      y_ay=0;
      son_durum=0;
  EEPROM.write(son_durum_caddress,(son_durum));  
  EEPROM.write(basla_caddress,(basla));  
  EEPROM.write(ygun_address,(y_gun));  
  EEPROM.write(yay_address,(y_ay));  
EEPROM.write(durum_caddress,(durum));  
digitalWrite(isi_role,LOW); 
digitalWrite(rutubet_role,LOW); 
digitalWrite(yumurta_role,LOW);  
digitalWrite(isi_led,LOW); 
digitalWrite(rutubet_led,LOW); 
digitalWrite(yumurta_led,LOW);

  while (1)
      { 
        lcd.setCursor (0, 0); lcd.print("CIKIM TAMAMLANDI");
        lcd.setCursor (0, 1); lcd.print("  FISI CEKINIZ  ");
     delay(1000);
        lcd.setCursor (0, 0); lcd.print("VEYA +- BUTONUNA");
        lcd.setCursor (0, 1); lcd.print("    BASINIZ     ");
     delay(1000);
           if(digitalRead(arti_pin) == 1 && digitalRead(eksi_pin) == 1)
    { 
    lcd.clear();
    goto bas;
    }
      }









}














 
  while (menu == 1) {
    

  ay = month(t) ;
  gun = day(t) ;
  saat = hour(t) ;
  dakika = minute(t) ;
  saniye = second(t);

    if ( digitalRead(arti_pin)==1 )
    {
      yil ++;
      while(digitalRead(arti_pin)==1 ){}

    }


    if ( digitalRead(eksi_pin)==1 )
    {
      yil--;
    if(yil<2022)yil=2022;
      while( digitalRead(eksi_pin)==1 ){}

    }


    saat_ayari();
   buton_oku();
  }
  while (menu == 2) {

    if ( digitalRead(arti_pin)==1 )
    {
      ay ++;
    if(ay>12)ay=12;
      while( digitalRead(arti_pin)==1 ){}

    }


   if ( digitalRead(eksi_pin)==1 )
    {
      ay --;
    if(ay<1)ay=1;
      while( digitalRead(eksi_pin)==1 ){}

    }
    saat_ayari();
    buton_oku();
  
  }
  while (menu == 3) {

   


    if ( digitalRead(arti_pin)==1 )
    {
      gun ++;
    if(gun>31)gun=31;
      while( digitalRead(arti_pin)==1 ){}

    }


   if ( digitalRead(eksi_pin)==1 )
    {
      gun --;
    if(gun<1)gun=1;
      while( digitalRead(eksi_pin)==1 ){}

    }
    saat_ayari();
    buton_oku();
  
  }
  while (menu == 4) {  


    if ( digitalRead(arti_pin)==1 )
    { saat ++;
    if(saat>23)saat=23;
      while( digitalRead(arti_pin)==1 ){} }
   if ( digitalRead(eksi_pin)==1 )
    { saat --;
    if(saat<0)saat=0;
      while( digitalRead(eksi_pin)==1 ){}  }

    saat_ayari();
    buton_oku();   
  }
  while (menu == 5) {
    if ( digitalRead(arti_pin)==1 )
    {  dakika ++;
    if(dakika>59)dakika=59;
      while( digitalRead(arti_pin)==1 ){}
    }

   if( digitalRead(eksi_pin)==1 )
    { dakika --;
    if(dakika<0)dakika=0;
      while( digitalRead(eksi_pin)==1 ){}

    }
    saat_ayari(); 
    buton_oku();
 
  }
  while (menu == 6) { // viyor zaman

  
    if ( digitalRead(arti_pin)==1 )
    {
      y_zaman++;
    if(y_zaman>10)y_zaman=0;
      while( digitalRead(arti_pin)==1 ){} 
  EEPROM.write(y_zaman_address,(y_zaman));  

    }

   if( digitalRead(eksi_pin)==1 )
    {
      y_zaman--;
    if(y_zaman<1)y_zaman=1;
      while( digitalRead(eksi_pin)==1 ){} 
  EEPROM.write(y_zaman_address,(y_zaman));  

    }

lcd.setCursor (0, 0);lcd.print(">VIYOR ZAM:"); if(y_zaman<10)lcd.print("0");lcd.print(y_zaman);lcd.print("    "); 
lcd.setCursor (0, 1);lcd.print("****************"); 
    buton_oku();
}



while (menu == 7) {

lcd.setCursor (0, 0);lcd.print("YUMURTA  SECINIZ"); 
lcd.setCursor (0, 1);lcd.print("     TAVUK      "); 


    if ( digitalRead(arti_pin)==1 ||  digitalRead(eksi_pin)==1 )
    {
 y_sic = 37;
 s_sic = 36;  
 y_nem = 60;
 s_nem = 75;
 cikim_gunu=18;

if(ay==1 ||ay==3 ||ay==5 ||ay==7 ||ay==8 ||ay==10 ||ay==12)
{
  y_gun=gun+cikim_gunu;
  if (y_gun>31){y_gun=y_gun-31; y_ay=ay+1;}
  else{y_ay=ay;}
}
else if(ay==4 ||ay==6 ||ay==9 ||ay==11)

{
  y_gun=gun+cikim_gunu;
  if (y_gun>30){y_gun=y_gun-30; y_ay=ay+1;}
  else{y_ay=ay;}
}


else if(ay==2)

{
  y_gun=gun+cikim_gunu;
  if (y_gun>28){y_gun=y_gun-28; y_ay=ay+1;}
  else{y_ay=ay;}
}



lcd.setCursor (0, 0);lcd.print(" TAVUK  SECILDI ");  
lcd.setCursor (0, 1);lcd.print(" ************** ");
delay(2000);

lcd.setCursor (0, 0);lcd.print("TOPLAM GEL. SURE");
lcd.setCursor (0, 1);lcd.print(cikim_gunu); lcd.print(" GUN Zam."); 
if(y_gun<10)lcd.print("0"); 
lcd.print(y_gun); lcd.print(":"); 
if(y_ay<10)lcd.print("0"); lcd.print(y_ay); 
delay(3000);

lcd.setCursor (0, 0);lcd.print("ILKISI:"); lcd.print(y_sic); lcd.print(" DERECE"); 
lcd.setCursor (0, 1);lcd.print("SONISI:"); lcd.print(s_sic); lcd.print(" DERECE"); 
delay(2000);
lcd.setCursor (0, 0);lcd.print("ILKNEM:"); lcd.print(y_nem); lcd.print(" %      "); 
lcd.setCursor (0, 1);lcd.print("SONNEM:"); lcd.print(s_nem); lcd.print(" %      ");  
delay(2000);
  
lcd.setCursor (0, 0);lcd.print("MAKINE CALISMAYA"); 
lcd.setCursor (0, 1);lcd.print("CALISMAYA HAZIR "); 
delay(1000);
 
  
    
lcd.setCursor (0, 0);lcd.print(" VIYOLU DUZ YAP "); 
lcd.setCursor (0, 1);lcd.print("****************"); 
      basla=1;
  EEPROM.write(basla_caddress,(basla)); 
  delay(2000);
menu=0;


kayit();
    }
    
    buton_oku();
}
   while (menu == 8) {

  
lcd.setCursor (0, 0);lcd.print("YUMURTA  SECINIZ"); 
lcd.setCursor (0, 1);lcd.print("   BILDIRCIN    "); 

    if ( digitalRead(arti_pin)==1 ||  digitalRead(eksi_pin)==1 )
    {
 y_sic = 37;
 s_sic = 36;  
 y_nem = 60;
 s_nem = 75;
 cikim_gunu=15;

if(ay==1 ||ay==3 ||ay==5 ||ay==7 ||ay==8 ||ay==10 ||ay==12)
{
  y_gun=gun+cikim_gunu;
  if (y_gun>31){y_gun=y_gun-31; y_ay=ay+1;}
  else{y_ay=ay;}
}
else if(ay==4 ||ay==6 ||ay==9 ||ay==11)

{
  y_gun=gun+cikim_gunu;
  if (y_gun>30){y_gun=y_gun-30; y_ay=ay+1;}
  else{y_ay=ay;}
}


else if(ay==2)

{
  y_gun=gun+cikim_gunu;
  if (y_gun>28){y_gun=y_gun-28; y_ay=ay+1;}
  else{y_ay=ay;}
}



lcd.setCursor (0, 0);lcd.print("BILDIRCIN SECILI");  
lcd.setCursor (0, 1);lcd.print(" ************** ");
delay(2000);

lcd.setCursor (0, 0);lcd.print("TOPLAM GEL. SURE");
lcd.setCursor (0, 1);lcd.print(cikim_gunu); lcd.print(" GUN Zam."); 
if(y_gun<10)lcd.print("0"); 
lcd.print(y_gun); lcd.print(":"); 
if(y_ay<10)lcd.print("0"); lcd.print(y_ay); 
delay(3000);

lcd.setCursor (0, 0);lcd.print("ILKISI:"); lcd.print(y_sic); lcd.print(" DERECE"); 
lcd.setCursor (0, 1);lcd.print("SONISI:"); lcd.print(s_sic); lcd.print(" DERECE"); 
delay(2000);
lcd.setCursor (0, 0);lcd.print("ILKNEM:"); lcd.print(y_nem); lcd.print(" %      "); 
lcd.setCursor (0, 1);lcd.print("SONNEM:"); lcd.print(s_nem); lcd.print(" %      "); 
delay(2000);
  
lcd.setCursor (0, 0);lcd.print("MAKINE CALISMAYA"); 
lcd.setCursor (0, 1);lcd.print("CALISMAYA HAZIR "); 
delay(1000);
 
  
    
lcd.setCursor (0, 0);lcd.print(" VIYOLU DUZ YAP "); 
lcd.setCursor (0, 1);lcd.print("****************"); 
      basla=1;
  EEPROM.write(basla_caddress,(basla)); 
  delay(2000);
menu=0;
   
kayit();
    }

    buton_oku();
}
     while (menu == 9) {

lcd.setCursor (0, 0);lcd.print("YUMURTA  SECINIZ"); 
lcd.setCursor (0, 1);lcd.print("      KAZ       "); 


    if ( digitalRead(arti_pin)==1 ||  digitalRead(eksi_pin)==1 )
    {
 y_sic = 37;
 s_sic = 37;  
 y_nem = 55;
 s_nem = 75;
 cikim_gunu=30;

if(ay==1 ||ay==3 ||ay==5 ||ay==7 ||ay==8 ||ay==10 ||ay==12)
{
  y_gun=gun+cikim_gunu;
  if (y_gun>31){y_gun=y_gun-31; y_ay=ay+1;}
  else{y_ay=ay;}
  if (y_gun>31){y_gun=y_gun-31; y_ay=ay+1;}
}
else if(ay==4 ||ay==6 ||ay==9 ||ay==11)

{
  y_gun=gun+cikim_gunu;
  if (y_gun>30){y_gun=y_gun-30; y_ay=ay+1;}
  else{y_ay=ay;}
  if (y_gun>30){y_gun=y_gun-30; y_ay=ay+1;}
}


else if(ay==2)

{
  y_gun=gun+cikim_gunu;
  if (y_gun>28){y_gun=y_gun-28; y_ay=ay+1;}
  else{y_ay=ay;}
  if (y_gun>28){y_gun=y_gun-28; y_ay=ay+1;}
}



lcd.setCursor (0, 0);lcd.print("   KAZ SECILDI  ");  
lcd.setCursor (0, 1);lcd.print(" ************** ");
delay(2000);

lcd.setCursor (0, 0);lcd.print("TOPLAM GEL. SURE");
lcd.setCursor (0, 1);lcd.print(cikim_gunu); lcd.print(" GUN Zam."); 
if(y_gun<10)lcd.print("0"); 
lcd.print(y_gun); lcd.print(":"); 
if(y_ay<10)lcd.print("0"); lcd.print(y_ay); 
delay(3000);

lcd.setCursor (0, 0);lcd.print("ILKISI:"); lcd.print(y_sic); lcd.print(" DERECE"); 
lcd.setCursor (0, 1);lcd.print("SONISI:"); lcd.print(s_sic); lcd.print(" DERECE"); 
delay(2000);
lcd.setCursor (0, 0);lcd.print("ILKNEM:"); lcd.print(y_nem); lcd.print(" %      "); 
lcd.setCursor (0, 1);lcd.print("SONNEM:"); lcd.print(s_nem); lcd.print(" %      "); 
delay(2000);
  
lcd.setCursor (0, 0);lcd.print("MAKINE CALISMAYA"); 
lcd.setCursor (0, 1);lcd.print("CALISMAYA HAZIR "); 
delay(1000);
 
  
    
lcd.setCursor (0, 0);lcd.print(" VIYOLU DUZ YAP "); 
lcd.setCursor (0, 1);lcd.print("****************"); 
      basla=1;
  EEPROM.write(basla_caddress,(basla)); 
  delay(2000);
menu=0;
   
kayit();
    }





    buton_oku();
}
  while (menu == 10) {

  
lcd.setCursor (0, 0);lcd.print("YUMURTA  SECINIZ"); 
lcd.setCursor (0, 1);lcd.print("     ORDEK      "); 

    if ( digitalRead(arti_pin)==1 ||  digitalRead(eksi_pin)==1 )
    {
 y_sic = 37;
 s_sic = 36;  
 y_nem = 63;
 s_nem = 80;
 cikim_gunu=26;

if(ay==1 ||ay==3 ||ay==5 ||ay==7 ||ay==8 ||ay==10 ||ay==12)
{
  y_gun=gun+cikim_gunu;
  if (y_gun>31){y_gun=y_gun-31; y_ay=ay+1;}
  else{y_ay=ay;}
  if (y_gun>31){y_gun=y_gun-31; y_ay=ay+1;}
}
else if(ay==4 ||ay==6 ||ay==9 ||ay==11)
{
  y_gun=gun+cikim_gunu;
  if (y_gun>30){y_gun=y_gun-30; y_ay=ay+1;}
  else{y_ay=ay;}
  if (y_gun>30){y_gun=y_gun-30; y_ay=ay+1;}
}


else if(ay==2)

{
  y_gun=gun+cikim_gunu;
  if (y_gun>28){y_gun=y_gun-28; y_ay=ay+1;}
  else{y_ay=ay;}
  if (y_gun>28){y_gun=y_gun-28; y_ay=ay+1;}
}



lcd.setCursor (0, 0);lcd.print(" ORDEK SECILDI  ");  
lcd.setCursor (0, 1);lcd.print(" ************** ");
delay(2000);

lcd.setCursor (0, 0);lcd.print("TOPLAM GEL. SURE");
lcd.setCursor (0, 1);lcd.print(cikim_gunu); lcd.print(" GUN Zam."); 
if(y_gun<10)lcd.print("0"); 
lcd.print(y_gun); lcd.print(":"); 
if(y_ay<10)lcd.print("0"); lcd.print(y_ay); 
delay(3000);

lcd.setCursor (0, 0);lcd.print("ILKISI:"); lcd.print(y_sic); lcd.print(" DERECE"); 
lcd.setCursor (0, 1);lcd.print("SONISI:"); lcd.print(s_sic); lcd.print(" DERECE"); 
delay(2000);
lcd.setCursor (0, 0);lcd.print("ILKNEM:"); lcd.print(y_nem); lcd.print(" %      ");  
lcd.setCursor (0, 1);lcd.print("SONNEM:"); lcd.print(s_nem); lcd.print(" %      "); 
delay(2000);


  
lcd.setCursor (0, 0);lcd.print("MAKINE CALISMAYA"); 
lcd.setCursor (0, 1);lcd.print("CALISMAYA HAZIR "); 
delay(1000);
 
  
    
lcd.setCursor (0, 0);lcd.print(" VIYOLU DUZ YAP "); 
lcd.setCursor (0, 1);lcd.print("****************"); 
      basla=1;
  EEPROM.write(basla_caddress,(basla)); 
  delay(2000);
menu=0;


kayit();

   
    }







    buton_oku();
}








  
  
  

  
}



void saat_ayari()
{
  static time_t tLast;
  time_t t;
  tmElements_t tm;

  //int ay==12;
  tm.Year = 51 + yil;
  tm.Month = ay;
  tm.Day = gun;
  tm.Hour = saat;
  tm.Minute = dakika;
  tm.Second = saniye;
  t = makeTime(tm);
  if (RTC.set(t) == 0) { // Success
    setTime(t);
    Serial << F("RTC set to: ");
    printDateTime(t);
    Serial << endl;
  }
  else
    Serial << F("RTC set failed!") << endl;
  t = now();
  if (t != tLast) {
    tLast = t;
    printDateTime(t);
    Serial << endl;
  }
}


void printDateTime(time_t t)
{
  printDate(t);
  Serial << ' ';
  printTime(t);
}
void printTime(time_t t)
{
  printI00(hour(t), ':');
  printI00(minute(t), ':');
  printI00(second(t), ' ');

  saat = hour(t) ;
  dakika = minute(t) ;
  saniye = second(t);



  if(menu == 1)
  {
lcd.setCursor (0, 0);
lcd.print("YIL AYARI :"); 
lcd.print(year(t)); 
lcd.print(" "); 
lcd.setCursor (0, 1);
lcd.print("****************"); 
    
  }


  else
  {
lcd.setCursor (0, 0);lcd.print(" ");
lcd.setCursor (1, 0);if (month(t) < 10)lcd.print("0"); lcd.print(month(t));
lcd.setCursor (4, 0);if (day(t) < 10)  lcd.print("0"); lcd.print(day(t));

 lcd.setCursor (8, 0); if (hour(t) < 10)    lcd.print("0");  lcd.print(hour(t));
  
 lcd.setCursor (11, 0); if (minute(t) < 10)    lcd.print("0");  lcd.print(minute(t));

 lcd.setCursor (14, 0); if (second(t) < 10)    lcd.print("0");  lcd.print(second(t));

 
    
    if (menu == 2){ lcd.setCursor (3, 0); lcd.print("<");
lcd.setCursor (0, 1);
lcd.print("AY AYARI        "); 
    }     
    else     { lcd.setCursor (3, 0); lcd.print(":");}

    if (menu == 3){ lcd.setCursor (6, 0); lcd.print("< ");
lcd.setCursor (0, 1);
lcd.print("GUN AYARI       "); }     
    else     { lcd.setCursor (6, 0); lcd.print("  ");}
    
    if (menu == 4){ lcd.setCursor (10, 0); lcd.print("<");
    
lcd.setCursor (0, 1);
lcd.print("SAAT AYARI    "); }     
    else     { lcd.setCursor (10, 0); lcd.print(":");}
    
   if (menu == 5){ lcd.setCursor (13, 0); lcd.print("<");
   
lcd.setCursor (0, 1);
lcd.print("DAKIKA AYARI    "); }     
    else     { lcd.setCursor (13, 0); lcd.print(":");}
  }
}
void printDate(time_t t)
{
  printI00(day(t), 0);
  Serial << monthShortStr(month(t)) << _DEC(year(t));



  //    yil =  year(t);
  ay = month(t) ;
  gun = day(t) ;


}
void printI00(int val, char delim)
{
  if (val < 10) Serial << '0';
  Serial << _DEC(val);
  if (delim > 0) Serial << delim;
  return;
}
void kayit()
{
  
  EEPROM.write(y_sic_address,(y_sic));  
  EEPROM.write(s_sic_address,(s_sic));  
  EEPROM.write(y_nem_address,(y_nem));  
  EEPROM.write(s_nem_address,(s_nem));  
  EEPROM.write(yay_address,(y_ay));  
  EEPROM.write(ygun_address,(y_gun));     
  EEPROM.write(son_durum_caddress,(son_durum));  
  EEPROM.write(basla_caddress,(basla));  
  EEPROM.write(ygun_address,(y_gun));  
  EEPROM.write(yay_address,(y_ay));  
  EEPROM.write(durum_caddress,(durum));  
}

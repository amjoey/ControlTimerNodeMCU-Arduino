// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <ESP8266WiFi.h>
#include <EEPROM.h> 

#include <Wire.h>
#include "RTClib.h"

#define SERVER_PORT 21111    //กำหนด Port ใช้งาน
const char* ssid = "wifi2013";       //กำหนด SSID
const char* password = "the0815993598"; //กำหนด Password
WiFiServer server(SERVER_PORT); //สร้าง object server และกำหนด port

RTC_DS3231 rtc;

int pin = 14;

String line,setpoint,Output1;

int address = 0;

int numberstr = 24;
//int value1,value2,value3,value4;
int value[24];



String padding(int c){
    if(c>=10)
        return String(c);
    else
        return "0"+ String(c);
}

void EEPROMWritelong(int address, int value)
      {
      //Decomposition from a long to 4 bytes by using bitshift.
      //One = Most significant -> Four = Least significant byte
      byte two = (value & 0xFF);
      byte one = ((value >> 8) & 0xFF);


      //Write the 4 bytes into the eeprom memory.
      EEPROM.write(address, two);
      EEPROM.write(address + 1, one);
      EEPROM.commit();
      }

//This function will return a 4 byte (32bit) long from the eeprom
//at the specified address to address + 3.
int EEPROMReadlong(int address)
      {
      //Read the 4 bytes from the eeprom memory.
      int two = EEPROM.read(address);
      int one = EEPROM.read(address + 1);


      //Return the recomposed long by using bitshift.
      return ((two << 0) & 0xFF) + ((one << 8) & 0xFFFF);
      }
      
void setup () {
   pinMode(pin, OUTPUT);
   digitalWrite(pin, HIGH); // ให้ LED ติด
   
Serial.begin(115200); // เปิดใช้การ Debug ผ่าน Serial
  WiFi.begin(ssid, password); //เชื่อมต่อกับ AP
  IPAddress ip(192,168,1,44);   
  IPAddress gateway(192,168,1,1);   
  IPAddress subnet(255,255,255,0);   
  WiFi.config(ip, gateway, subnet);
 while (WiFi.status() != WL_CONNECTED)  //รอการเชื่อมต่อ
{
        delay(500);
        Serial.print(".");
}
        Serial.println("WiFi connected");   //แสดงข้อความเชื่อมต่อสำเร็จ  
Serial.println("IP address: "); 
Serial.println(WiFi.localIP());     //แสดงหมายเลข IP
        server.begin();             //เริ่มต้นทำงาน TCP Server
   delay(1000);       
EEPROM.begin(512);

#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif

 // Serial.begin(9600);

//  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop () {
    
  /*  
  value1 = EEPROMReadlong(address);
  value2 = EEPROMReadlong(address+2);
  value3 = EEPROMReadlong(address+4);
  value4 = EEPROMReadlong(address+6);
  */
  for (int m=0; m < numberstr; m++){
    value[m] = EEPROMReadlong(address);
    address = address+2;
   // delay(1);
  }
  address = 0;
  

  DateTime now = rtc.now();

  String result=padding(now.hour())+ padding(now.minute());

  //Serial.println(result.toInt(), DEC);

  int result16 = strtol(result.c_str(), NULL, 16);
  /*
  Serial.print(value, DEC);
  Serial.print("---");*/
  Serial.print(result16, DEC);
  Serial.print("-");
  Serial.print(value[0], DEC);
  Serial.print("-");
  Serial.print(value[1], DEC);
  Serial.print("-");
  Serial.print(value[2], DEC);
  Serial.print("-");
  Serial.println(value[3], DEC);  
  
  
    if ((value[0] <= result16)&&(value[1] > result16)){
      digitalWrite(pin, LOW); // ให้ LED ติด
      Output1 = "ON";
    }else if (value[1] == result16){
      digitalWrite(pin, HIGH); // ให้ LED ติด
      Output1 = "OFF";
    }else if ((value[2] <= result16)&&(value[3] > result16)){
      digitalWrite(pin, LOW); // ให้ LED ติด
      Output1 = "ON";
    }else if (value[3] == result16){
      digitalWrite(pin, HIGH); // ให้ LED ติด
      Output1 = "OFF";
    }else if ((value[4] <= result16)&&(value[5] > result16)){
      digitalWrite(pin, LOW); // ให้ LED ติด
      Output1 = "ON";
    }else if (value[5] == result16){
      digitalWrite(pin, HIGH); // ให้ LED ติด
      Output1 = "OFF";
    }else if ((value[6] <= result16)&&(value[7] > result16)){
      digitalWrite(pin, LOW); // ให้ LED ติด
      Output1 = "ON";
    }else if (value[7] == result16){
      digitalWrite(pin, HIGH); // ให้ LED ติด
      Output1 = "OFF";
    }else if ((value[8] <= result16)&&(value[9] > result16)){
      digitalWrite(pin, LOW); // ให้ LED ติด
      Output1 = "ON";
    }else if (value[9] == result16){
      digitalWrite(pin, HIGH); // ให้ LED ติด
      Output1 = "OFF";
    }else if ((value[10] <= result16)&&(value[11] > result16)){
      digitalWrite(pin, LOW); // ให้ LED ติด
      Output1 = "ON";
    }else if (value[11] == result16){
      digitalWrite(pin, HIGH); // ให้ LED ติด
      Output1 = "OFF";
    }else if ((value[12] <= result16)&&(value[13] > result16)){
      digitalWrite(pin, LOW); // ให้ LED ติด
      Output1 = "ON";
    }else if (value[13] == result16){
      digitalWrite(pin, HIGH); // ให้ LED ติด
      Output1 = "OFF";
    }else if ((value[14] <= result16)&&(value[15] > result16)){
      digitalWrite(pin, LOW); // ให้ LED ติด
      Output1 = "ON";
    }else if (value[15] == result16){
      digitalWrite(pin, HIGH); // ให้ LED ติด
      Output1 = "OFF";
    }else if ((value[16] <= result16)&&(value[17] > result16)){
      digitalWrite(pin, LOW); // ให้ LED ติด
      Output1 = "ON";
    }else if (value[17] == result16){
      digitalWrite(pin, HIGH); // ให้ LED ติด
      Output1 = "OFF";
    }else if ((value[18] <= result16)&&(value[19] > result16)){
      digitalWrite(pin, LOW); // ให้ LED ติด
      Output1 = "ON";
    }else if (value[19] == result16){
      digitalWrite(pin, HIGH); // ให้ LED ติด
      Output1 = "OFF";
    }else if ((value[20] <= result16)&&(value[21] > result16)){
      digitalWrite(pin, LOW); // ให้ LED ติด
      Output1 = "ON";
    }else if (value[21] == result16){
      digitalWrite(pin, HIGH); // ให้ LED ติด
      Output1 = "OFF";
    }else if ((value[22] <= result16)&&(value[23] > result16)){
      digitalWrite(pin, LOW); // ให้ LED ติด
      Output1 = "ON";
    }else if (value[23] == result16){
      digitalWrite(pin, HIGH); // ให้ LED ติด
      Output1 = "OFF";
    }else{
      digitalWrite(pin, HIGH); // ให้ LED ดับ
      Output1 = "OFF";
    }
    
  //delay(1000);
  WiFiClient client = server.available();
  if (!client) // ถ้าไม่มีการเชื่อมต่อมาใหม่
    return; // ส่งลับค่าว่าง ทำให้ลูปนี้ถูกยกเลิก

  Serial.println("New client"); // ส่งข้อความว่า New client ไปที่ Serial Monitor
  while (client.connected()) { // วนรอบไปเรื่อย ๆ หากยังมีการเชื่อมต่ออยู่
    if (client.available()) { // ถ้ามีการส่งข้อมูลเข้ามา
      char c = client.read(); // อ่านข้อมูลออกมา 1 ไบต์
      if (c == '\r') { // ถ้าเป็น \r (return)
        Serial.println(line); // แสดงตัวแปร line ไปที่ Serial Monitor

        
        setpoint = line;
/*
        String cmd[2];
        int k=0, j=0;
        for (int i=0; i < line.length(); i++)
        { if(line.charAt(i) == '%') 
          { 
            cmd[j] = line.substring(k, i);
            k=(i+1); 
            j++; 
          }
        }
        */     if(line != "Return"){   
                int sa[numberstr], r=0, t=0;
               // String oneLine = "aa;bb;cc;dd;";
                
                for (int i=0; i < setpoint.length(); i++)
                { if(setpoint.charAt(i) == ';') 
                  { 
                    sa[t] = setpoint.substring(r, i).toInt();
                    r=(i+1); 
                    t++; 
                  }
                }
              
                for (int k=0; k < numberstr; k++){
                  EEPROMWritelong(address, sa[k]);
                  address = address+2;
                }
                address = 0;
               /*  
                EEPROMWritelong(address, sa[0]);
                EEPROMWritelong(address+2, sa[1]);
                EEPROMWritelong(address+4, sa[2]);
                EEPROMWritelong(address+6, sa[3]);
                EEPROMWritelong(address+8, sa[4]);
                EEPROMWritelong(address+10, sa[5]);
                EEPROMWritelong(address+12, sa[6]);
                EEPROMWritelong(address+14, sa[7]);
              */
              }
        //EEPROM.commit();
        line = ""; // ล้างค่าตัวแปร line
        break; // ออกจากลูป
      } else if (c == '\n') { // ถ้าเป็น \n (new line)
        // Pass {new line}
   
      } else { // ถ้าไม่ใช่
        line += c; // เพิ่มข้อมูล 1 ไบต์ ไปต่อท้ายในตัวแปร line
      }

      
    }                    
  }
  
  if(setpoint=="Return"){
      client.println("%RETURN%,"+String(result16)+","+Output1);
      delay(10);
  }
  setpoint = "";
  
  // setpoint = "";
  //หน่วยเวลาเพื่อให้ส่ง client.println("%OK%");
  client.stop(); // ปิดการเชื่อมต่อกับ Client
  Serial.println("Client disconnect"); // ส่งข้อความว่า Client disconnect ไปที่ Serial Monitor
}

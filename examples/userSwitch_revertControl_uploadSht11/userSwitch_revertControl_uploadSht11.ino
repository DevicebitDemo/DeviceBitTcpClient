#include <SPI.h>
#include <Ethernet.h>
#include <DeviceBitTcpClient.h>
#include <EEPROM.h>
#include <SHT1x.h>

// Specify data and clock connections and instantiate SHT1x object
#define dataPin 4
#define clockPin 5
SHT1x sht1x(dataPin, clockPin);

#define DB_USERKEY "your_api_key"
#define DB_GATEWAY "01"

int relayPin = 6;


//byte mac[] = {0x74,0x69,0x69,0x2D,0x30,0x31};
//IPAddress ip(192,168,1, 15);
//IPAddress mydns(8,8,8,8);
//IPAddress gw(192,168,1,1);
//IPAddress subnet(255,255,255,0);

DeviceBitTcpClient *client;
long starttime;
int postInterval = 30000;
void setup()
{
  Serial.begin(9600);
  pinMode(3, OUTPUT); 
  starttime = millis();
  //you can use 3 ways to init your network
  //1.simplest
  client = new DeviceBitTcpClient(DB_USERKEY, DB_GATEWAY);
  //2.full setting for your network
  //client = new DeviceBitTcpClient(LW_USERKEY, LW_GATEWAY,mac,ip,mydns,gw,subnet);
  
  
  //test1 is the function you write below to handle your program
  //"testFunction" is the function name you set on website:http://www.devicebit.com/
  //on "controll command manager" menu
  //we test transfer 1-5 para from website(you defined on it) to your arduino
  //enjoy it
  
  UserSwitch us1 (switchTest,"relay",1);
  client->addUserSwitch(us1);
//  client->easySetupMode(true);
  client->checkFreeMem();
}

void loop()
{
    client->keepOnline();
    if ((millis()-starttime) > postInterval)
    {
      sendSht11Value();
      starttime = millis();
    }
}

void sendSht11Value()
{
  float temp_c;
  float temp_f;
  float humidity;
  
  // Read values from the sensor
  temp_c = sht1x.readTemperatureC();
  temp_f = sht1x.readTemperatureF();
  humidity = sht1x.readHumidity();
  client->appendSensorValue("temp",temp_c);
  client->sendSensorValue("hum",humidity);
}


void switchTest(char* p1)
{
  Serial.println("switch test");  
  client->checkFreeMem();
}



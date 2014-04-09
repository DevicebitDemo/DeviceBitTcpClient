#include <SPI.h>
#include <Ethernet.h>
#include <DeviceBitTcpClient.h>
#include <EEPROM.h>


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
  pinMode(relayPin, OUTPUT); 
  starttime = millis();
  //you can use 2 ways to init your network
  //1.simplest
  client = new DeviceBitTcpClient(DB_USERKEY, DB_GATEWAY);
  //2.full setting for your network
  //client = new DeviceBitTcpClient(DB_USERKEY, DB_GATEWAY,mac,ip,mydns,gw,subnet);
  
  
  //switchTest is the function you write below to handle your program
  //"relay" is the controller's name you set on website:http://www.devicebit.com/
  //on "controll command manager" menu
  //we test transfer 1 para from website(you defined on it) to your arduino
  //enjoy it
  
  UserSwitch us1 (switchTest,"relay",1);
  client->addUserSwitch(us1);
//  client->easySetupMode(true);
  client->checkFreeMem();
}

void loop()
{
    client->keepOnline();
}



void switchTest(char* p1)
{
  if(String(p1).equals("0"))
	{
		digitalWrite(relayPin,LOW);
		Serial.println("on");
	}
	else if(String(p1).equals("1"))
	{
		digitalWrite(relayPin,HIGH);
		Serial.println("off");
	}
  client->checkFreeMem();
}

#include <SPI.h>  
#include "RF24.h" 

RF24 myRadio (7, 8); 
struct package
{ 
  int pipe = 0;
  int id=0;
  float temperature = 0.0;
  char  text[100] ="empty";
};

byte addresses[][6] = {"0","1"}; 

typedef struct package Package;
Package data;

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.openReadingPipe(2, addresses[1]);
  myRadio.startListening();
}


void loop()  
{
  if(myRadio.available()){
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
    Serial.print("\nPipe: ");
    Serial.print(data.pipe);
    Serial.print("\nPackage:");
    Serial.print(data.id);
    Serial.print("\n");
    Serial.println(data.temperature);
    Serial.println(data.text);
  }

}

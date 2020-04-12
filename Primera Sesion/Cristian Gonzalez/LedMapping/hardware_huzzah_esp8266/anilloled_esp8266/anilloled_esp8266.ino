#include "config.h"
#include <E131.h>
#include <FastLED.h>

E131 e131;
//Array de Pixeles
CRGB leds[NUM_LEDS];
#define DATA_PIN 12  //huzzah feather pin12
#define CLOCK_PIN 13  //huzzah feather pin13


void setup() {
  Serial.begin(115200);
  LEDS.addLeds<APA102,DATA_PIN,CLOCK_PIN,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(84);
  Serial.printf("Por Cristian Gonzalez \n\n");

  delay(500);

  /* Conexion Wifi */
  WiFi.mode(WIFI_STA);
  Serial.println(" ");
  Serial.printf("Conectando a .. : ");
  Serial.print(ssid);
  WiFi.persistent(false);  // no sobreescribir las credenciales wifi 
  WiFi.begin(ssid, pass);
  pinMode(BUILTIN_LED, OUTPUT);
  int contadorReset = 0;
  while (!WiFi.isConnected()) {
    // auto reset si no se conecta 
    delay(100); Serial.print(".");
    contadorReset++;
    if (contadorReset > 70) ESP.restart();   //  x > (70x100ms)  --> Restart
  }
  
  e131.begin(ssid, pass, local_IP, subnet, gateway, gateway); //IP Manual
  //e131.begin(ssid, password); // si se desea asignar la ip mediante dhcp 
  if(WiFi.status() == WL_CONNECTED){
    Serial.printf("  Conectado.\n"); 
    digitalWrite(BUILTIN_LED, LOW);  
  }

  FastLED.show(); 

}

void loop() {
  if (e131.parsePacket()){
    if (e131.universe == UNIVERSO){
      for (int i = 0; i < NUM_LEDS; i++) {
        int j = i * 3 + (CANAL - 1);
        leds[i].setRGB(e131.data[j],e131.data[j + 1],e131.data[j + 2]);
      //  pixels.setPixelColor(i, e131.data[j], e131.data[j + 1], e131.data[j + 2]);
        // leds.setRGB();

      }
      FastLED.show();
    }
  }

}


void apagar() { 
  for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } 


}

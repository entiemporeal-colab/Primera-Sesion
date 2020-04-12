#ifndef CONFIG_H 
#define CONFIG_H

#include <ESP8266WiFi.h>
#include <DNSServer.h>
 

#include "wifi_config.h"  

/*-- Pixeles  --*/
#define NUM_LEDS 24 //Numero de Pixeles
#define UNIVERSO 1     //Universo Art-net 
#define CANAL 1 



/* -- configuracion de red -- */
const char* ssid     = WIFI_SSID;         //definido en wifi_config.h
const char* pass = WIFI_PASSWORD;     // definido en wifi_config.h

/* Parametros de Red */
IPAddress local_IP(192, 168, 1, 150);              
IPAddress gateway(192,168,1,1);               
IPAddress subnet(255, 255, 255, 0); 



#endif 

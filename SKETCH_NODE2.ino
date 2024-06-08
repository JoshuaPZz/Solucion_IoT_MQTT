#include <PubSubClient.h>
#include <ESP8266WiFi.h>


String ssid = "";
String password = "";
const unsigned char pinSound = 4;

const char* mqtt_server = "";

WiFiClient espClient;
PubSubClient client(espClient);

const char* mqtt_topic_bool = "peligro";

bool peligro;

byte cont = 0;
byte max_intentos = 50;
String messageString;

void callback(char* topic, byte* payload, unsigned int length) {
  char message[length + 1];
  
  memcpy(message, payload, length);
  message[length] = '\0'; 

   messageString = String(message);
  
  if(strcmp(topic, mqtt_topic_bool) == 0){
   if (messageString == "true") {
    peligro = true;
} else if (messageString == "false") {
    peligro = false;
}
    if(peligro==true){
    //suena musiquita de peligro
  // c_dball_c();
    Serial.print("SE HA REPORTADO UN CAMBIO, HAY INCENDIO ");
    }
    else{
      //suena musiquita normal
      Serial.print("SE HA REPORTADO UN CAMBIO, TODO ESTA TRANQUILO ");
    //  c_starWars_c();
    }
  }


}

void reconnect() {

  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");
    
    if (client.connect("ESP8266Client2")) {
      Serial.println("Conectado");
  
      client.subscribe(mqtt_topic_bool);
    } else {
      Serial.print("Error, rc=");
      Serial.print(client.state());
      Serial.println(" Intentando de nuevo en 5 segundos");
      
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and cont < max_intentos) {
    cont++;
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  if (cont < max_intentos) {  
    Serial.println("********************************************");
    Serial.print("Conectado a la red WiFi: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("macAdress: ");
    Serial.println(WiFi.macAddress());
    Serial.println("*********************************************");
  } else {
    Serial.println("------------------------------------");
    Serial.println("Error de conexion");
    Serial.println("------------------------------------");
  }
  // Configurar el callback para recibir mensajes
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
    if(peligro==true){
       tone(pinSound, 523) ; 
    Serial.println(" la temperatura esta alta, hay peligro de incendio");
    } else{
      noTone(pinSound);
      Serial.println("No hay de que preocuparse, no hay peligro de incendio");
    }
    delay(5000);
  
}


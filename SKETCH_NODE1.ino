#include <ESP8266WiFi.h>
#include "DHT.h"
#include <PubSubClient.h> 
#include <ThingSpeak.h>

#define DHTPIN 4
#define DHTTYPE DHT22
  

DHT dht(DHTPIN, DHTTYPE);
String ssid     = "J"; // nombre del wifi
String password = ""; // clave del wifi
const char* mqtt_server = ""; // Dirección IP del servidor MQTT
const char* mqtt_topic_temp = "temperatura"; // Tema MQTT para la temperatura
unsigned long channelID = //canal thingspeak;
const char* WriteAPIKey = "token thingspeak";
WiFiClient espClient;
PubSubClient client(espClient);

byte cont = 0;
byte max_intentos = 50;

void setup() {
  // Inicia Serial
  Serial.begin(115200);
  Serial.println("\n");

  // Conexión WIFI
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

  dht.begin();

  // Conexión al servidor MQTT
  client.setServer(mqtt_server, 1883); // Puerto predeterminado de MQTT
  ThingSpeak.begin(espClient);
}

void loop() {
  
  // Intentamos reconectar al servidor MQTT si no estamos conectados
  if (!client.connected()) {
   reconnect();
  }
  client.loop();

  // Leemos la temperatura y la sensación térmica
  float hume = dht.readHumidity();
  float temp = dht.readTemperature();
  float hi = dht.computeHeatIndex(temp, hume);
  String tempa= String(temp).c_str();
  if (client.connected()) {
    client.publish(mqtt_topic_temp, String(temp).c_str());
  }
  ThingSpeak.setField(1,temp);
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print(" °C, Humedad: ");
  Serial.print(hume);
  Serial.print(" %, Sensacion termica: ");
  Serial.print(hi);
  Serial.println(" °C");
   ThingSpeak.writeFields(channelID,WriteAPIKey);
  delay(5000);
}

// Función para reconectar al servidor MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");
    if (client.connect("ESP8266Client1")) { // 
      Serial.println("Conectado");
    } else {
      Serial.print("falló, rc=");
      Serial.print(client.state());
      Serial.println(" Intentaremos de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

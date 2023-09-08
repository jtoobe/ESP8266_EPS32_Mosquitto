/*
   ESP8266 o ESP32 (ver las modificaciones)

*/

#include <ESP8266WiFi.h> // Para ESP8266
// #include <WiFi.h> // Para ESP32
WiFiClient WIFI_CLIENT;
#include <PubSubClient.h>
PubSubClient MQTT_CLIENT;

// Nombre y contraseña red WiFi.
const char* ssid = "<Red WiFi>";
const char* password = "<passwd>";


void setup() {
  Serial.begin(115200);
  delay(10);

  // Conectar con WiFi.
  Serial.println();
  Serial.print("Conectando con ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Configuración de la respuesta.
  MQTT_CLIENT.setCallback(callback);
}

// Aquí configuramos lo que debe hacer cuando recibe un valor.
void callback(char* recibido, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido: ");
  Serial.print(recibido);
  Serial.print("   ");
  for (int i = 0; i < length; i++) {
    char receivedChar = (char)payload[i];
    Serial.print(receivedChar);

  }
  Serial.println();
}

void loop() {
  if (!MQTT_CLIENT.connected()) {
    reconnect();
  }
  MQTT_CLIENT.loop(); // Chequea lo Subscrito.
}


// Reconecta con MQTT broker
void reconnect() {
  // MQTT_CLIENT.setServer("192.168.1.206", 1883);  // si se usa un servidor en la red local, verificar IP
     MQTT_CLIENT.setServer("broker.hivemq.com", 1883);

  MQTT_CLIENT.setClient(WIFI_CLIENT);

  // Intentando conectar con el broker.
  while (!MQTT_CLIENT.connected()) {
    Serial.println("Intentando conectar con MQTT.");
    MQTT_CLIENT.connect("XJXT061651656845165416");   // usar un nombre aleatorio
    //                      topic /  valor
    MQTT_CLIENT.subscribe("XJXT06/aleatorio");

    // Espera antes de volver a intentarlo.
    delay(3000);
  }

  Serial.println("Conectado a MQTT.");
}

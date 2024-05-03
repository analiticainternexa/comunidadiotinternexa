#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "<SSID>";            // Cambia por el nombre de tu red WiFi
const char* password = "<PASSWORD>";  // Cambia por la contraseña de tu red WiFi
const char* ubidotsToken = "<UBIDOTSTOKEN>"; // Cambia por tu token de Ubidots
const char* server = "industrial.api.ubidots.com";
const char* endpoint = "<ENDPOINTUBIDOTS>";

 
void setup() {

  Serial.begin(115200);
  delay(4000);  // Espera un momento para la inicialización

  // Conexión a WiFi
  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado a la red WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Genera un valor aleatorio de temperatura entre 20 y 40 grados Celsius
    float temperatura = random(2000, 4000) / 100.0;
    // Crea el objeto HTTPClient
    HTTPClient http;

    // Prepara el payload JSON con el valor de temperatura
    String payload = "{\"value\": " + String(temperatura) + "}";

 
    // Inicia la solicitud HTTP

    http.begin("http://" + String(server) + String(endpoint));

    http.addHeader("Content-Type", "application/json");

    http.addHeader("X-Auth-Token", ubidotsToken);

    // Realiza la solicitud POST con el payload JSON

    int httpResponseCode = http.POST(payload);

    // Comprueba el código de respuesta

    if (httpResponseCode > 0) {

      Serial.print("Respuesta del servidor: ");

      Serial.println(httpResponseCode);

    } else {

      Serial.print("Error en la solicitud HTTP: ");

      Serial.println(httpResponseCode);

    }

    // Libera los recursos

    http.end();

  }

 
  delay(5000);  // Espera 5 segundos antes de enviar otra solicitud

}

#include <WiFi.h>
#include <WebServer.h>
#include "mbedtls/aes.h"
#include <NewPing.h> // Librería para el sensor ultrasónico

// Definir los pines para el sensor ultrasónico
#define TRIGGER_PIN 4
#define ECHO_PIN 2
#define MAX_DISTANCE 200 // Distancia máxima de detección (en centímetros)
#define MIN_DISTANCE 20  // Distancia mínima para detener el robot (en centímetros)

// Pines para control de motores
#define MOTOR_A_PIN 5
#define MOTOR_B_PIN 19
#define PWM_A_PIN 18
#define PWM_B_PIN 21

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Inicializar el sensor

// Crear un servidor web en el puerto 80
WebServer server(80);
mbedtls_aes_context aes_ctx;

// Clave de cifrado (16 bytes para AES-128)
const unsigned char aes_key[] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
};

volatile bool obstacleDetected = false; // Flag para indicar si se detectó un obstáculo

void IRAM_ATTR isr() {
  // Realizar una lectura del sensor ultrasónico
  unsigned int distance = sonar.ping_cm();
  if (distance > 0 && distance < MIN_DISTANCE) {
    // Detener los motores inmediatamente
    digitalWrite(MOTOR_A_PIN, HIGH);
    ledcWrite(0, 0);
    digitalWrite(MOTOR_B_PIN, LOW);
    ledcWrite(1, 0);
    Serial.println("Motores detenidos");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(MOTOR_A_PIN, OUTPUT);
  pinMode(MOTOR_B_PIN, OUTPUT);
  pinMode(PWM_A_PIN, OUTPUT);
  pinMode(PWM_B_PIN, OUTPUT);

  // Configuración de PWM para control de motores
  ledcSetup(0, 5000, 8);
  ledcAttachPin(PWM_A_PIN, 0);
  ledcSetup(1, 5000, 8);
  ledcAttachPin(PWM_B_PIN, 1);

  // Conexión a WiFi
  Serial.println("Conectando a la red Wi-Fi...");
  WiFi.begin("Jeffi", "12345678");
  int maxAttempts = 30;
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts) {
    delay(1000);
    Serial.print("Intento: ");
    Serial.println(attempts + 1);
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Conexión Wi-Fi establecida");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Fallo al conectar a Wi-Fi. Revise la configuración.");
  }

  // Inicialización de AES
  mbedtls_aes_init(&aes_ctx);
  mbedtls_aes_setkey_enc(&aes_ctx, aes_key, 128);

  // Configuración del servidor web
  server.on("/", handleRoot);
  server.on("/led1/on", handleLedOn);
  server.on("/led1/off", handleLedOff);
  server.on("/led2/on", handleLedOn);
  server.on("/led2/off", handleLedOff);
  server.begin();
  Serial.println("Servidor web iniciado");

  // Configurar la interrupción para el sensor ultrasónico
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), isr, CHANGE);
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  if (server.hasArg("data")) {
    String encryptedData = server.arg("data");
    unsigned char decryptedData[16];
    mbedtls_aes_crypt_ecb(&aes_ctx, MBEDTLS_AES_DECRYPT, (const unsigned char*)encryptedData.c_str(), decryptedData);
    String decryptedText = "";
    for (int i = 0; i < sizeof(decryptedData); ++i) {
      decryptedText += String((char)decryptedData[i]);
    }
    server.send(200, "text/plain", "Datos procesados correctamente: " + decryptedText);
  } else {
    String html = "<!DOCTYPE html>";
    html += "<html lang='es'>";
    html += "<head>";
    html += "<meta charset='UTF-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<title>Control de LED</title>";
    html += "<style>";
    html += "@import url('https://fonts.googleapis.com/css2?family=Baumans&display=swap');";
    html += "body { font-family: 'Baumans', system-ui; margin: 0; padding: 0; background-color: #0D1B2A; color: #E0E1DD; }";
    html += "header { width: auto; padding: 0 20px; padding-block: 1em; border-bottom: 2px solid #4C5C68; display: flex; flex-direction: row; align-items: center; justify-content: space-around; flex-wrap: wrap; box-sizing: border-box; background-color: #1B263B; color: #E0E1DD; font-weight: 500; }";
    html += "a { text-decoration: none; color: #E0E1DD; }";
    html += ".inside { display: flex; flex-direction: row; justify-content: space-around; align-items: flex-end; width: 100%; }";
    html += ".CameraSection { width: 50%; margin-left: 0; height: 600px; }";
    html += "#VideoCamara { display: flex; flex-direction: column; box-sizing: border-box; align-items: center; padding-left: 1em; height: 90%; }";
    html += "#EnVivo { border: 4px solid #4C5C68; width: 600px; height: 450px; margin-bottom: 10px; }";
    html += ".button-cam { background-color: #4056A1; border: none; border-radius: 20px; color: #E0E1DD; padding: 10px 20px; cursor: pointer; }";
    html += ".control-and-data-section { width: 50%; height: 600px; display: flex; flex-direction: column; align-items: center; justify-content: center; }";
    html += ".data { width: 100%; text-align: center; }";
    html += "h1, h2 { margin: 5px; }";
    html += ".controles { display: flex; flex-direction: column; align-items: center; justify-content: center; }";
    html += ".button-row { display: flex; justify-content: center; width: 100%; }";
    html += ".Arriba { margin-bottom: 20px; }"; // Separación entre el botón superior y los inferiores
    html += ".Arriba, .Abajo, .Izquierda, .Derecha { background-color: #4056A1; color: #E0E1DD; border: none; border-radius: 20px; padding: 15px 30px; cursor: pointer; margin: 5px; }";
    html += "</style>";
    html += "</head>";
    html += "<header>";
    html += "<a href=''><h1>Opciones</h1></a>";
    html += "<h1>Kaxan Maák</h1>";
    html += "<h1>Sistema de búsqueda y rescate</h1>";
    html += "</header>";
    html += "<body>";
    html += "<div class='inside'>";
    html += "<div class='CameraSection'>";
    html += "<h1 class='h1-live'>Live</h1>";
    html += "<div id='VideoCamara'>";
    html += "<img src='http://192.168.184.161:4747/video' style='width: 600px; height: 450px;'>";
    html += "<button id='toggleButton' class='button-cam'>Iniciar</button>";
    html += "</div>";
    html += "</div>";
    html += "<div class='control-and-data-section'>";
    html += "<div class='data'>";
    html += "<h1>BOTONES</h1>";
    html += "</div>";
    html += "<div class='controles'>";
    html += "<button class='Arriba' onclick='ledOn(1)'>Adelante</button>";
    html += "<div class='button-row'>";
    html += "<button class='Izquierda' onclick='ledOff(1)'>Izquierda</button>";
    html += "<button class='Abajo' onclick='ledOn(2)'>Atrás</button>";
    html += "<button class='Derecha' onclick='ledOff(2)'>Derecha</button>";
    html += "</div>"; // Cierre de button-row
    html += "</div>"; // Cierre de controles
    html += "</div>"; // Cierre de control-and-data-section
    html += "</div>"; // Cierre de inside
    html += "</body>";
    html += "<script>";
    html += "var buttonPressed;";
    html += "function ledOn(led) { var xhttp = new XMLHttpRequest(); xhttp.open('GET', '/led' + led + '/on', true); xhttp.send(); if (led == 1) { buttonPressed = 'Adelante'; } else if (led == 2) { buttonPressed = 'Atrás'; } console.log('Se presionó: ' + buttonPressed); }";
    html += "function ledOff(led) { var xhttp = new XMLHttpRequest(); xhttp.open('GET', '/led' + led + '/off', true); xhttp.send(); if (led == 1) { buttonPressed = 'Izquierda'; } else if (led == 2) { buttonPressed = 'Derecha'; } console.log('Se presionó: ' + buttonPressed); }";
    html += "document.addEventListener('keydown', function(event) { switch (event.key) { case 'ArrowUp': ledOn(1); break; case 'ArrowDown': ledOn(2); break; case 'ArrowLeft': ledOff(1); break; case 'ArrowRight': ledOff(2); break; case 'Space': espacioPressed(); break; default: break; } });";
    html += "</script>";
    html += "</html>";
    server.send(200, "text/html", html);
  }
}

void handleLedOn() {
  String led = server.uri().substring(1, 5);
  if (led == "led1") {
    digitalWrite(MOTOR_A_PIN, HIGH);
    ledcWrite(0, 255);
    digitalWrite(MOTOR_B_PIN, HIGH);
    ledcWrite(1, 255);
    delay(1000);
    digitalWrite(MOTOR_A_PIN, LOW);
    ledcWrite(0, 0);
    digitalWrite(MOTOR_B_PIN, LOW);
    ledcWrite(1, 0);
  } else if (led == "led2") {
    digitalWrite(MOTOR_A_PIN, LOW);
    ledcWrite(0, 255);
    digitalWrite(MOTOR_B_PIN, HIGH);
    ledcWrite(1, 255);
    delay(1000);
    digitalWrite(MOTOR_A_PIN, LOW);
    ledcWrite(0, 0);
    digitalWrite(MOTOR_B_PIN, LOW);
    ledcWrite(1, 0);
  }
  server.sendHeader("Location", "/");
  server.send(302);
}

void handleLedOff() {
  String led = server.uri().substring(1, 5);
  if (led == "led1") {
    digitalWrite(MOTOR_A_PIN, HIGH);
    ledcWrite(0, 255);
    digitalWrite(MOTOR_B_PIN, HIGH);
    ledcWrite(1, 0);
    delay(1000);
    digitalWrite(MOTOR_A_PIN, LOW);
    ledcWrite(0, 0);
    digitalWrite(MOTOR_B_PIN, LOW);
    ledcWrite(1, 0);
  } else if (led == "led2") {
    digitalWrite(MOTOR_A_PIN, LOW);
    ledcWrite(0, 255);
    digitalWrite(MOTOR_B_PIN, HIGH);
    ledcWrite(1, 255);
    delay(1000);
    digitalWrite(MOTOR_A_PIN, LOW);
    ledcWrite(0, 0);
    digitalWrite(MOTOR_B_PIN, LOW);
    ledcWrite(1, 0);
  }
  server.sendHeader("Location", "/");
  server.send(302);
}
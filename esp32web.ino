#include <WiFi.h>
#include <WebServer.h>

// Define los pines del LED
int D2 = 22;
int D5 = 32;
int D4 = 23;
int D6 = 21;

// Crea un servidor web en el puerto 80
WebServer server(80);

void handleRoot() {
  // Genera la página HTML con dos botones para controlar los LED
  String html = "<!DOCTYPE html>";
html += "<html lang=\"es\">";
html += "<head>";
html += "<meta charset=\"UTF-8\">";
html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
html += "<title>Control de LED</title>";
html += "<style>";
html += "@import url('https://fonts.googleapis.com/css2?family=Baumans&display=swap');";
html += "/*header*/";
html += "header {";
html += "  width: auto;";
html += "  padding: 0 20px;";
html += "  padding-block: 1em;";
html += "  border-bottom: 2px ridge rgb(0, 0, 0);";
html += "  display: flex;";
html += "  flex-direction: row;";
html += "  align-items: center;";
html += "  justify-content: space-around;";
html += "  flex-wrap: wrap;";
html += "  box-sizing: border-box;";
html += "  background-color: rgb(241, 228, 218);";
html += "  color: black;";
html += "  font-family: \"Baumans\", system-ui;";
html += "  font-weight: 500;";
html += "}";
html += "img {";
html += "  border: 2px ridge rgb(249, 241, 234);";
html += "  width: 90px;";
html += "}";
html += ".menu {";
html += "  width: 30px;";
html += "}";
html += "/*fin header*/";
html += "/*Inicio body e inside*/";
html += ".inside {";
html += "  display: flex;";
html += "  flex-direction: row;";
html += "  /* justify-content: center; */";
html += "  justify-content: space-around;";
html += "  align-items: flex-end;";
html += "  width: 100%;";
html += "}";
html += "body {";
html += "  font-family: \"Baumans\", system-ui;";
html += "  margin: 0;";
html += "  padding: 0;";
html += "}";
html += "/*Seccion camara*/";
html += ".CameraSection {";
html += "  width: 50%;";
html += "  margin-left: 0;";
html += "  height: 600px;";
html += "}";
html += "#VideoCamara {";
html += "  display: flex;";
html += "  flex-direction: column;";
html += "  box-sizing: border-box;";
html += "  align-items: center;";
html += "  padding-left: 1em;";
html += "  height: 90%;";
html += "}";
html += "#EnVivo {";
html += "  border: 4px ridge rgb(73, 73, 73);";
html += "  width: 600px;";
html += "  height: 450px;";
html += "  margin-bottom: 10px;";
html += "}";
html += ".button-cam {";
html += "  background-color: rgb(248, 236, 226);";
html += "  border: 2px ridge gray;";
html += "  border-top-left-radius: 10px;";
html += "  border-top-right-radius: 10px;";
html += "  border-bottom-left-radius: 30px;";
html += "  border-bottom-right-radius: 30px;";
html += "}";
html += "@keyframes blink {";
html += "  0% {";
html += "    opacity: 1;";
html += "  }";
html += "  100% {";
html += "    opacity: 0.5;";
html += "  }";
html += "}";
html += "a {";
html += "  text-decoration: none;";
html += "  color: black;";
html += "}";
html += ".h1-live {";
html += "  text-align: center;";
html += "  padding-left: 1em;";
html += "  color: red;";
html += "  animation: blink 1s infinite alternate;";
html += "  font-family: \"Baumans\", system-ui;";
html += "}";
html += ".h1-live::after {";
html += "  content: \"**\";";
html += "  border-radius: 50%;";
html += "  background-color: red;";
html += "  font-size: small;";
html += "}";
html += "/*Fin camara*/";
html += "/*inicio datos y control*/";
html += ".control-and-data-section {";
html += "  width: 50%;";
html += "  height: 600px;";
html += "  display: grid;";
html += "  grid-template-rows: 300px 300px;";
html += "  grid-template-columns: 50% 50%;";
html += "}";
html += ".data {";
html += "  grid-row: 1/3;";
html += "}";
html += ".controles {";
html += "  margin-right: 20px;";
html += "  align-self: center;";
html += "  grid-row: 2;";
html += "  grid-column: 2;";
html += "  display: grid;";
html += "  grid-template-columns: 1fr 1fr 1fr;";
html += "  grid-template-rows: 50px 50px;";
html += "  grid-gap: 10px;";
html += "}";
html += ".Arriba, .Abajo, .Izquierda, .Derecha {";
html += "  font-family: \"Baumans\", system-ui;";
html += "  border: none;";
html += "  border-radius: 20px;";
html += "}";
html += ".Arriba {";
html += "  grid-column: 1;";
html += "  grid-column: 2;";
html += "}";
html += ".Abajo {";
html += "  grid-row: 2;";
html += "  grid-column: 2;";
html += "}";
html += ".Izquierda {";
html += "  grid-row: 2;";
html += "  grid-column: 1;";
html += "}";
html += ".Derecha {";
html += "  grid-row: 2;";
html += "  grid-column: 3;";
html += "}";
html += "</style>";
html += "</head>";
html += "<header>";
html += "<a href=\"\">";
html += "<h1>Opciones</h1>";
html += "</a>";
html += "<h1>Kaxan Maák</h1>";
html += "<h1>Sistema de busqueda y rescate</h1>";
html += "</header>";
html += "<body>";
html += "<div class=\"inside\">";
html += "<div class=\"CameraSection\">";
html += "<h1 class=\"h1-live\">Live </h1>";
html += "<div id=\"VideoCamara\">";
html += "<video id=\"EnVivo\" width=\"auto\" height=\"auto\" autoplay muted></video>";
html += "<button id=\"toggleButton\" class=\"button-cam\">Iniciar</button>";
html += "</div>";
html += "</div>";
html += "<div class=\"control-and-data-section\">";
html += "<div class=\"data\">";
html += "<h1>Datos</h1>";
html += "<h2>velocidad</h2>";
html += "<h2>bateria</h2>";
html += "<h2>texto de prueba cambiar</h2>";
html += "</div>";
html += "<div class=\"controles\">";
html += "<button class=\"Arriba\" onclick=\"ledOn(1)\">Adelante</button>";
html += "<button class=\"Izquierda\" onclick=\"ledOff(1)\">Izquierda</button>";
html += "<button class=\"Abajo\" onclick=\"ledOn(2)\">Atras</button>";
html += "<button class=\"Derecha\" onclick=\"ledOff(2)\">Derecha</button>";
html += "</div>";
html += "</div>";
html += "</div>";
html += "</body>";

html += "<script>";
html += "var buttonPressed;";
html += "function ledOn(led) {";
html += "  var xhttp = new XMLHttpRequest();";
html += "  xhttp.open(\"GET\", \"/led\" + led + \"/on\", true);";
html += "  xhttp.send();";
html += "  if (led == 1) {";
html += "    buttonPressed = \"Adelante\";";
html += "  } else if (led == 2) {";
html += "    buttonPressed = \"Atras\";";
html += "  }";
html += "  console.log(\"Se presiono: \" + buttonPressed);";
html += "}";
html += "function ledOff(led) {";
html += "  var xhttp = new XMLHttpRequest();";
html += "  xhttp.open(\"GET\", \"/led\" + led + \"/off\", true);";
html += "  xhttp.send();";
html += "  if (led == 1) {";
html += "    buttonPressed = \"Izquierda\";";
html += "  } else if (led == 2) {";
html += "    buttonPressed = \"Derecha\";";
html += "  }";
html += "  console.log(\"Se presiono: \" + buttonPressed);";
html += "}";
html += "document.addEventListener('keydown', function (event) {";
html += "  switch (event.key) {";
html += "    case 'ArrowUp':";
html += "      ledOn(1); ";
html += "      break;";
html += "    case 'ArrowDown':";
html += "      ledOn(2); ";
html += "      break;";
html += "    case 'ArrowLeft':";
html += "      ledOff(1); ";
html += "      break;";
html += "    case 'ArrowRight':";
html += "      ledOff(2); ";
html += "      break;";
html += "    case 'Space':";
html += "      espacioPressed();";
html += "      break;";
html += "    default:";
html += "      break;";
html += "  }";
html += "});";

html += "let cameraStream = null;";
html += "let isCameraOn = false;";
html += "function startCameraStream() {";
html += "  navigator.mediaDevices.getUserMedia({ video: true })";
html += "    .then((stream) => {";
html += "      cameraStream = stream;";
html += "      const video = document.querySelector('#EnVivo');";
html += "      video.srcObject = cameraStream;";
html += "      isCameraOn = true;";
html += "    })";
html += " ";
html += "    .catch((error) => {";
html += "      console.error('Error accessing camera stream:', error);";
html += "    });";
html += "}";
html += "function stopCameraStream() {";
html += "  if (cameraStream) {";
html += "    cameraStream.getTracks().forEach(track => track.stop());";
html += "    cameraStream = null;";
html += "    isCameraOn = false;";
html += "  }";
html += "}";
html += "function toggleCameraStream() {";
html += "  if (isCameraOn) {";
html += "    stopCameraStream();";
html += "  } else {";
html += "    startCameraStream();";
html += "  }";
html += "}";

html += "document.addEventListener('DOMContentLoaded', function () {";
html += "  const toggleButton = document.querySelector('#toggleButton');";
html += "  toggleButton.addEventListener('click', toggleCameraStream); ";
html += "});";
html += "</script>";
html += "</body>";
html += "</html>";

  // Envía la página HTML al cliente
  server.send(200, "text/html", html);
}

void handleLedOn() {
  // Obtiene el número de LED a encender de la URL
  String led = server.uri().substring(1, 5);

  // Enciende el LED correspondiente
  if (led == "led1") {
    forward();
    delay(1000);
    stopp();
  } else if (led == "led2") {
    backward();
    delay(1000);
    stopp();
  }

  // Redirige al usuario a la página principal
  server.sendHeader("Location", "/");
  server.send(302);
}

void handleLedOff() {
  // Obtiene el número de LED a apagar de la URL
  String led = server.uri().substring(1, 5);

  // Apaga el LED correspondiente
  if (led == "led1") {
   rotate_right();
   delay(1000);
    stopp();
  } else if (led == "led2") {
    rotate_left();
    delay(1000);
    stopp();
  }

  // Redirige al usuario a la página principal
  server.sendHeader("Location", "/");
  server.send(302);
}

void setup() {
  // Inicializa el puerto serie y los pines de los LEDs
  Serial.begin(115200);
  pinMode(D2, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D6, OUTPUT);

  // Conéctate a la red Wi-Fi
  WiFi.begin("DNieves", "Pan112212");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red Wi-Fi...");
  }
  Serial.println("Conexión Wi-Fi establecida");
  // Imprime la dirección IP asignada al dispositivo
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Registra las funciones de control de LED para las rutas correspondientes
  server.on("/", handleRoot);
  server.on("/led1/on", handleLedOn);
  server.on("/led1/off", handleLedOff);
  server.on("/led2/on", handleLedOn);
  server.on("/led2/off", handleLedOff);

  // Inicia el servidor web
  server.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
  // Maneja las solicitudes del cliente
  server.handleClient();
}



void forward()
{digitalWrite(D2,LOW);
 analogWrite(D5,255);
 digitalWrite(D4,HIGH);
 analogWrite(D6,255);
  }

  void backward()
{digitalWrite(D2,HIGH);
 analogWrite(D5,255);
 digitalWrite(D4,LOW);
 analogWrite(D6,255);
  }

void rotate_left()
{digitalWrite(D2,HIGH);
 analogWrite(D5,255);
 digitalWrite(D4,HIGH);
 analogWrite(D6,255);
  }


  void rotate_right()
{digitalWrite(D2,LOW);
 analogWrite(D5,255);
 digitalWrite(D4,LOW);
 analogWrite(D6,255);
  }



    void stopp()
{digitalWrite(D2,HIGH);
 analogWrite(D5,0);
 digitalWrite(D4,LOW);
 analogWrite(D6,0);
  }

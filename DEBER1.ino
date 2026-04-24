const int pinVerde = 18;
const int pinAmarillo = 19;
const int pinRojo = 21;
const int pinSensor = 22;

volatile int contadorSegundos = 0;
int estado = 1;
hw_timer_t *timer = NULL;

void IRAM_ATTR onTimer() {
  contadorSegundos++;
}

void setup() {
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAmarillo, OUTPUT);
  pinMode(pinRojo, OUTPUT);
  pinMode(pinSensor, INPUT_PULLUP);

  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 1000000, true, 0);
}

void loop() {
  int limiteVerde;
  int brilloVerde;
  bool hayVehiculo;

  if (digitalRead(pinSensor) == LOW) {
    hayVehiculo = true;
  } else {
    hayVehiculo = false;
  }

  if (hayVehiculo == true) {
    limiteVerde = 8;
    brilloVerde = 255;
  } else {
    limiteVerde = 5;
    brilloVerde = 127;
  }

  if (estado == 1) {
    analogWrite(pinVerde, brilloVerde);
    digitalWrite(pinAmarillo, LOW);
    digitalWrite(pinRojo, LOW);
    
    if (contadorSegundos >= limiteVerde) {
      contadorSegundos = 0;
      estado = 2;
    }
  } 
  else if (estado == 2) {
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinAmarillo, HIGH);
    digitalWrite(pinRojo, LOW);
    
    if (contadorSegundos >= 2) {
      contadorSegundos = 0;
      estado = 3;
    }
  } 
  else if (estado == 3) {
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinAmarillo, LOW);
    digitalWrite(pinRojo, HIGH);
    
    if (contadorSegundos >= 5) {
      contadorSegundos = 0;
      estado = 1;
    }
  }
}

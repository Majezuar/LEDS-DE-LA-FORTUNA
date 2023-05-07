// INICIALIZACION DE VARIABLES USADAS
int ledRojo1 = 4;
int ledRojo2 = 6;
int ledRojo3 = 10;
int ledRojo4 = 12;
int ledAzul = 8;
int boton1 = 2;
int boton2 = 3;

// VARIABLES CONTADORAS DE PERDIDAS Y GANADAS
int vecesPerdido = 0;
int vecesGanado = 0;

// VARIABLE PARA CASO DONDE SE GANA Y SE OMITE PRENDER LOS OTROS LEDS
bool omitirGanador = false;

// VARIABLES PARA CASOS DONDE SE PIERDE Y SE OMITE PRENDER LOS OTROS LEDS
bool omitirPerdedor = false;
bool omitirPerdedor1 = false;
bool omitirPerdedor2 = false;
bool omitirPerdedor3 = false;

// VARIABLE PARA DETERMINAR SI ES PERDEDOR
bool esPerdedor = false;
// VARIABLE PARA DETERMINAR SI ES PERDEDOR
bool esGanador = false;

void setup() {
// DECLARACION DE TODO LO NECDESARIO PARA EL FUNCIONAMIENTO DEL PROGRAMA
  Serial.begin(9600);
  pinMode(ledRojo1, OUTPUT);
  pinMode(ledRojo2, OUTPUT);
  pinMode(ledRojo3, OUTPUT);
  pinMode(ledRojo4, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(boton1, INPUT);
  pinMode(boton2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), IntentoGanar, RISING);
  attachInterrupt(digitalPinToInterrupt(3), ReiniciarJuego, RISING);
}


void loop() {
  ApagarLeds();
  // CASO GANADOR
  if (esGanador == true) {
    digitalWrite(ledAzul, HIGH);
    delay(500);
    digitalWrite(ledAzul, LOW);
    delay(500);
  } else {
    // CASO PERDEDOR
    if (esPerdedor == true) {

      digitalWrite(ledRojo1, HIGH);
      digitalWrite(ledRojo2, HIGH);
      digitalWrite(ledRojo3, HIGH);
      digitalWrite(ledRojo4, HIGH);
      delay(500);
      digitalWrite(ledRojo1, LOW);
      digitalWrite(ledRojo2, LOW);
      digitalWrite(ledRojo3, LOW);
      digitalWrite(ledRojo4, LOW);
      delay(500);

    } else {
      // CASO NI PERDEDOR NI GANADOR 
      digitalWrite(ledRojo1, HIGH);
      delay(200);
      digitalWrite(ledRojo1, LOW);
      if (omitirPerdedor == false) {
        delay(200);
        digitalWrite(ledRojo2, HIGH);
        delay(200);
        digitalWrite(ledRojo2, LOW);
        // SI ES PERDEDOR EN ESTE LED OMITIMOS TODO EL CODIGO
        if (omitirPerdedor1 == false) {
          delay(200);
          digitalWrite(ledAzul, HIGH);
          delay(200);
          digitalWrite(ledAzul, LOW);
          // SI ES GANADOR OMITIMOS TODO EL CODIGO
          if (omitirGanador == false) {
            delay(200);
            digitalWrite(ledRojo3, HIGH);
            delay(200);
            digitalWrite(ledRojo3, LOW);
            // SI ES PERDEDOR EN ESTE LED OMITIMOS TODO EL CODIGO
            if (omitirPerdedor2 == false) {
              delay(200);
              digitalWrite(ledRojo4, HIGH);
              delay(200);
              digitalWrite(ledRojo4, LOW);
              // SI ES PERDEDOR EN ESTE LED OMITIMOS TODO EL CODIGO
              if (omitirPerdedor3 == false) {
                delay(200);
              }
            }
          }
        }
      }
    }
  }
}


// FUNCION PARA COMPROBAR SI SE GANO
void IntentoGanar() {
  if (digitalRead(ledAzul) == HIGH) {
    esGanador = true;
    omitirGanador = true;
  } else {
    esPerdedor = true;
    omitirPerdedor = true;
    ;
    omitirPerdedor1 = true;
    omitirPerdedor2 = true;
    omitirPerdedor3 = true;
  }
}

// FUNCION PARA REINICIAR EL JUEGO
void ReiniciarJuego() {
  if (digitalRead(ledAzul) == HIGH) {
    if (esGanador == true) {
      digitalWrite(ledAzul, HIGH);
      digitalWrite(ledRojo1, HIGH);
      digitalWrite(ledRojo2, HIGH);
      digitalWrite(ledRojo3, HIGH);
      digitalWrite(ledRojo4, HIGH);
      delay(200000);
      vecesGanado++;
      Serial.println("Has ganado por: " + String(vecesGanado) + " Vez.\n");
      esGanador = false;
      omitirGanador = false;
    }
  } else {
    if (esPerdedor == true) {
      digitalWrite(ledAzul, HIGH);
      digitalWrite(ledRojo1, HIGH);
      digitalWrite(ledRojo2, HIGH);
      digitalWrite(ledRojo3, HIGH);
      digitalWrite(ledRojo4, HIGH);
      delay(200000);
      vecesPerdido++;
      Serial.println("Has perdido por: " + String(vecesPerdido) + " Vez.\n");
      esPerdedor = false;
      omitirPerdedor = false;
      omitirPerdedor1 = false;
      omitirPerdedor2 = false;
      omitirPerdedor3 = false;
    }
  }
  ApagarLeds();
}

// FUNCION PARA APAGAR LOS LEDS
void ApagarLeds() {
  digitalWrite(ledAzul, LOW);
  digitalWrite(ledRojo1, LOW);
  digitalWrite(ledRojo2, LOW);
  digitalWrite(ledRojo3, LOW);
  digitalWrite(ledRojo4, LOW);
}

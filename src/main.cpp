#include <Arduino.h>

// Definición de frecuencias de notas musicales (en Hz)
#define DO    261   // Do (C4)
#define RE    294   // Re (D4)
#define MI    330   // Mi (E4)
#define FA    349   // Fa (F4)
#define SOL   392   // Sol (G4)
#define LA    440   // La (A4)
#define SI    493   // Si (B4)
#define DO2   523   // Do (C5) (Do+)

// pines botones
int bot1 = 2;
int bot2 = 3;
int bot3 = 4;
int bot4 = 5;
int bot5 = 6;
int bot6 = 7;
int bot7 = 9;
int bot8 = 10;

// pin boton grabar
int botRecord = 11;
bool grabando = false;

// pin reproducir
int botReproducir = 12;

// estado botones
int botEstado = 0;

// variable que ayuda a apagar buzzer
bool notaPresionada = false;

const int tamanoMaxCancion = 10;
int tamanoCancion = 0;
int cancion[tamanoMaxCancion];

int notas[] =   { DO,  RE,  MI,  FA, SOL,  LA,  SI,  DO2};
int botones[] = {bot1,bot2,bot3,bot4,bot5,bot6,bot7,bot8, botRecord, botReproducir};

// pin buzzer
int buzzerPin = 8;

void setup() {
  // inicializar botones
  for (int i = 0; i < 10; i++) {
    pinMode(botones[i], INPUT);
  }
  //  inicializar buzzer
  pinMode(buzzerPin, OUTPUT); 

  Serial.begin(115200);
}
// se usa & para cambiar parametro
void cambiarEstado(bool &objeto){
  objeto = objeto ? false: true;
}

void grabar(int nota){
  if(tamanoCancion < tamanoMaxCancion){
    Serial.println(nota);
    cancion[tamanoCancion] = nota;
    tamanoCancion++;
  }
}

void loop() {
  //sonar al presionar tecla
   for (int i = 0; i < 10; i++) {

    botEstado = digitalRead(botones[i]);
    if (botEstado == HIGH){
      if(i < 8){
        // si se esta grabando
        if(grabando){
          grabar(notas[i]);
        }
          tone(buzzerPin, notas[i],100);
          // delay(300);
          break;
      }
      // bandera grabar
      else if (i == 8){
        cambiarEstado(grabando);
        Serial.println(grabando);
        delay(500);
        break;
      }

      // reproducir
      else if (i == 9){
        Serial.println("reproduciendo");
        for(int f = 0; f < tamanoCancion; f++){
          tone(buzzerPin, cancion[f], 200);
          delay(300); 
        }
        // delay(1000);
      }
    }

  }

}


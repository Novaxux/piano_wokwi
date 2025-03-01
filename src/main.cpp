#include <Arduino.h>

bool grabando = false;

// estado previo botones/ actual
int botEstado = 0;

// variable que ayuda a apagar buzzer
bool notaPresionada = false;

const int tamanoMaxCancion = 10;
int tamanoCancion = 0;
int cancion[tamanoMaxCancion];

              //  DO     RE    MI   FA    SOL   LA   SI     DO+
int notas[] =   { 261,  294,  330,  349, 392,  440,  493,  523};

//pines de botones: bot1,bot2,bot3,bot4,bot5,bot6,bot7,bot8, botRecord, botReproducir
int botones[] =    {  2,   3,  4,   5,  6,   7,   9,   10,     11 ,        12};
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
          delay(300);
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
        break;
      }
    }

  }

}


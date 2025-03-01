#ifndef MUSICALOID_EQUIPOX_h
#define MUSICALOID_EQUIPOX_h

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Definimos el número máximo de melodías
#define MAX_MELODIES 10

// Estructura para representar una melodía
struct Melody {
    int ID;
    String name;
    int notes[10];    // Array para almacenar las notas
    int noteCount;
    unsigned long creationTime;
    unsigned long editTime;
    unsigned long deletionTime;
    bool isDeleted;
};

class MUSICALOID_EQUIPOX {
    public:
      MUSICALOID_EQUIPOX(LiquidCrystal_I2C &lcd);
      void addMelody(String name, int notes[], int noteCount);
      void editMelody(int ID, String newName, int newNotes[], int newNoteCount);
      void deleteMelody(int ID);
      void restoreMelody(int ID);
      void playMelody(int ID);
      void listMelodies();
      void report();
      void sortMelodies(int option);
      void displayMessage(String message);
  
    private:
      Melody melodies[MAX_MELODIES];
      int melodyCount;
      LiquidCrystal_I2C *lcd;
  
      void bubbleSort(int option);
      int findMelodyByID(int ID);
      void showMelody(int index);
  };

#endif
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

TMRpcm music;

// Pins
const int CHANGETRACK_PIN = 2;
const int PLAYPAUSE_PIN = 3;
const int SPEAKER_PIN = 9;
const int SD_SLAVE_PIN = 4;

int songNumber = 1;
boolean paused = false;

void setup() {
  Serial.begin(9600);

  while (!SD.begin(SD_SLAVE_PIN)) {
    Serial.println(F("."));
  }
  Serial.println(F("OK"));

  lcd.begin();
  lcd.backlight();

  pinMode(CHANGETRACK_PIN, INPUT);
  pinMode(PLAYPAUSE_PIN, INPUT);

  lcd.setCursor(5, 0);
  lcd.print("WELCOME!");

  delay(1500);

  lcd.clear();

  music.speakerPin = 9;

  music.play("1.WAV");

  Serial.println("Started");
}

void loop() {
  if (digitalRead(CHANGETRACK_PIN) == LOW) { //Button CHANGETRACK_PIN Pressed
    if (songNumber == 25) {
      songNumber = 0;
    }
    
    songNumber++;

    char name[10];
    sprintf(name, "%d.WAV", songNumber);
    Serial.println(name);

    music.play(name);

    lcd.clear();

    delay(1000);
  }

  if (digitalRead(PLAYPAUSE_PIN) == LOW) {
    music.pause();

    lcd.clear();

    delay(500);

    paused = !paused;
  }

  // Display track name and playback state.
  if (paused) {
    lcd.setCursor(0, 0);
    lcd.print("Paused");
    lcd.setCursor(0, 1);
    lcd.print("Track:");
    lcd.setCursor(7, 1);
    lcd.print(songNumber);
  } else {
    lcd.setCursor(0, 0);
    lcd.print(F("Now playing"));
    lcd.setCursor(0, 1);
    lcd.print("Track:");
    lcd.setCursor(7, 1);
    lcd.print(songNumber);
  }
}

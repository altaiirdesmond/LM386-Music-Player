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

void setup() {
  Serial.begin(9600);

  while (!SD.begin(SD_SLAVE_PIN));

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
    if(songNumber > 25){
      songNumber = 1;
    }

    lcd.clear();

    songNumber++;

    char name[10];
    sprintf(name, "%d.WAV", songNumber);
    Serial.println(name);
    
    music.play(name);

    delay(1000);
  }

  if(digitalRead(PLAYPAUSE_PIN) == LOW){
    music.pause();
  }

  // Display track name and playback state.
  if(music.isPlaying()){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Now playing");
    lcd.setCursor(0, 1);
    lcd.print("Track:");
	lcd.setCursor(7, 1);
    lcd.print(songNumber);
  }else{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Paused");
    lcd.setCursor(0, 1);
    lcd.print("Track:");
	lcd.setCursor(7, 1);
    lcd.print(songNumber);
  }
}

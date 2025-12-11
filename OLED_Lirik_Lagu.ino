#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* lyrics[] = {
  "Temanku semua",
  "pada jahat tante",
  "Aku lagi susah",
  "mereka ga ada",
  "Coba kalo lagi jaya",
  "Aku dipuja tante",
  "",                     // baris kosong
  "Sudah terbiasa",
  "terjadi tante",
  "Teman datang saat",
  "butuh saja",
  "Coba kalo susah",
  "Mereka hilang"
};

const int totalLyrics = sizeof(lyrics) / sizeof(lyrics[0]);

// Emoticon animasi (sudah ditambah 2 emot baru)
const char* emotFrames[] = {
  "(^_^)",
  "(>_<)",
  "(T_T)",
  "(*o*)",
  "(^o^)"
};

const int totalEmot = sizeof(emotFrames) / sizeof(emotFrames[0]);

int emotIndex = 0;   // Posisi emot terakhir

void setup() {
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Error!");
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
}

void showLyrics(int index) {
  display.clearDisplay();

  // Jika lirik tidak kosong → update emot & tampilkan
  if (strlen(lyrics[index]) != 0) {
    emotIndex++;
    if (emotIndex >= totalEmot) emotIndex = 0;

    int emotX = (SCREEN_WIDTH - (strlen(emotFrames[emotIndex]) * 6)) / 2;
    display.setCursor(emotX, 8);
    display.print(emotFrames[emotIndex]);
  }

  // Tampilkan lirik (kosong tetap kosong)
  display.setCursor(5, 40);
  display.print(lyrics[index]);

  display.display();
}

void loop() {
  for (int i = 0; i < totalLyrics; i++) {

    showLyrics(i);

    // waktu jeda
    if (strlen(lyrics[i]) == 0)
      delay(900);
    else
      delay(1500);
  }

  delay(2000);
}

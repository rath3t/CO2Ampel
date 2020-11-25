//#include "../lib/MH-Z19-master/src/MHZ19.h"
////#include "MHZ19.h"
//#include "SSD1306Wire.h"
//#include <Adafruit_NeoPixel.h>
//#include "../lib/Tone32-master/src/Tone32.h"
//
//
//// Maximum CO² levels for green and yellow, everything above is considered red.
//#define GREEN_CO2 800
//#define YELLOW_CO2 1000
//
//// Measurement interval in miliseconds
//#define INTERVAL 6000
//
//// Pins for MH-Z19
//#define RX_PIN 16
//#define TX_PIN 17
//
//// Pins for SD1306
//#define SDA_PIN 21
//#define SCL_PIN 22
//
//// Pin and settings for buzzer
//#define BUZZER_PIN 12
//#define BUZZER_CHANNEL 0
//#include <../lib/PlayRtttl-master/src/PlayRtttl.h>
//const int TONE_PIN = 12;
//
//// Pin for LED
//#define LED_PIN 4
//
//// number of LEDs connected
//#define NUMPIXELS 16
//
//MHZ19 myMHZ19;
//HardwareSerial mySerial(1);
//SSD1306Wire  display(0x3c, SDA_PIN, SCL_PIN);
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_RGB + NEO_KHZ400);
//
//void playRandomSongAndBlink() {
//  char StringBuffer[16];
//  Serial.println();
//  Serial.print("Now playing: ");
//  startPlayRandomRtttlFromArrayPGM(BUZZER_PIN, RTTTLChristmasMelodies, ARRAY_SIZE_CHRISTMAS_MELODIES, StringBuffer,
//                                   sizeof(StringBuffer));
//  Serial.println(StringBuffer);
//
//
//// wait for the song to end
//  while (updatePlayRtttl()) {
//    delay(1);
//  }
//
//  delay(2000);
//}
//bool playSongOnceSwitch = true;
//void set_led_color(int co2) {
//  if (co2 < GREEN_CO2) {
//    // Green
////    for(int i=0; i<NUMPIXELS; i++) {
////      pixels.setPixelColor(i, 30,0,0);
////      pixels.show();
////    }
//    pixels.clear();
//    playSongOnceSwitch = true;
//  } else if (co2 < YELLOW_CO2) {
//    // Yellow
//    for(int i=0; i<NUMPIXELS; i++) {
//      pixels.setPixelColor(i, 40,40,0);
//      pixels.show();
//    }
//    playSongOnceSwitch = true;
//  } else {
//    // Red
//    for(int i=0; i<NUMPIXELS; i++) {
//      pixels.setPixelColor(i, 0,90,0);
//      pixels.show();
//    }
//
////    char StringBuffer[16];
//    if(playSongOnceSwitch) {
//          tone(BUZZER_PIN, NOTE_C4, 500, BUZZER_CHANNEL);
//    noTone(BUZZER_PIN, BUZZER_CHANNEL);
////      playRandomSongAndBlink();
//      playSongOnceSwitch = false;
//    }
//  }
//  pixels.show();
//}
//
//void printErrorCode()
//{
//  Serial.println("Communication error. Error Code: ");  // *Print error code using the library variable
//  Serial.println(myMHZ19.errorCode);                    //  holds the last recieved code
//}
//
//void setRange(int range)
//{
//  Serial.println("Setting range..");
//
//  myMHZ19.setRange(range);                                               // request new range write
//
//  if ((myMHZ19.errorCode == RESULT_OK) && (myMHZ19.getRange() == range)) //RESULT_OK is an alias from the library,
//    Serial.println("Range successfully applied.");
//
//  else
//  {
//    printErrorCode();
//  }
//}
//
//unsigned long getDataTimer = 0;
//int lastvals[120];
//int dheight;
//
//void setup() {
//  Serial.begin(9600);
//
//  mySerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
//  myMHZ19.begin(mySerial);
//  pixels.clear();
//  display.init();
//  display.setContrast(255);
////  delay(1000);
//  display.clear();
//  display.flipScreenVertically();
//  dheight = display.getHeight();
//
//  setRange(2000);
//  if (myMHZ19.errorCode == RESULT_OK)
//    myMHZ19.calibrateZero();                            // Calibrate
//  else
//    printErrorCode();
//
//  if (myMHZ19.errorCode == RESULT_OK)
//    myMHZ19.setSpan(2000);                               // Set Span 2000
//  else
//    printErrorCode();
//
//  if (myMHZ19.errorCode == RESULT_OK)
//    myMHZ19.autoCalibration(false);                       // Turn auto calibration OFF
//  else
//    printErrorCode();
//  // Fill array of last measurements with -1
//  for (int x = 0; x <= 119; x = x + 1) {
//    lastvals[x] = -1;
//  }
//  myMHZ19.setFilter(true, true);
//  pixels.begin();
//  for(int i=0; i<NUMPIXELS; i++) {
//    pixels.setPixelColor(i, pixels.Color(0, 0, 50));
//    delay(250);
//    pixels.show();
//  }
//  set_led_color(myMHZ19.getCO2(false));
//}
//
//int calc_vpos_for_co2(int co2val, int display_height) {
//  return display_height - int((float(display_height) / 3000) * co2val);
//}
//
//
//
//
//
//void loop() {
//
//  if (millis() - getDataTimer >= INTERVAL) {
//    // Get new CO² value.
//    int CO2 = myMHZ19.getCO2(false);
//    float temp = myMHZ19.getTemperature();
//    // Shift entries in array back one position.
//    for (int x = 1; x <= 119; x = x + 1) {
//      lastvals[x - 1] = lastvals[x];
//    }
//    // Add new measurement at the end.
//    lastvals[119] = CO2;
//    // Clear display and redraw whole graph.
//    display.clear();
//    for (int h = 1; h < 120; h = h + 1) {
//      int curval = lastvals[h];
//      if (curval > 0) {
//        int vpos = calc_vpos_for_co2(lastvals[h], dheight);
//        int vpos_last = calc_vpos_for_co2(lastvals[h - 1], dheight);
//        display.drawLine(h - 1, vpos_last, h, vpos);
//      }
//    }
//    // Set LED color and print value on display
//
//    display.setLogBuffer(1, 30);
//    display.setFont(ArialMT_Plain_24);
//    display.setTextAlignment(TEXT_ALIGN_CENTER);
//    String CO2String = String(CO2) + "ppm";
//    String TempString = String(roundf(temp),0) + "°C";
//    display.drawString(64 ,10 , CO2String);
//    display.drawString(64 ,40 , TempString);
//
//    display.drawLogBuffer(0, 0);
//    display.display();
//    // Debug output
//    Serial.print("CO2 (ppm): ");
//    Serial.println(CO2);
//
//    Serial.print("Temp (°C): ");
//    Serial.println(temp);
//    Serial.print("Accuracy: ");
//    Serial.println(myMHZ19.getAccuracy());
//    getDataTimer = millis();
//    set_led_color(CO2);
//  }
//}

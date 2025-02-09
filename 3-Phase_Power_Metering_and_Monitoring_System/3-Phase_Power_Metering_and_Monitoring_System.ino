#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin definitions (adjust according to your board mapping)
const int voltagePinA = A0; // Voltage sensor for Phase A
const int voltagePinB = A1; // Voltage sensor for Phase B
const int voltagePinC = A2; // Voltage sensor for Phase C
const int currentPinA = A3; // Current sensor for Phase A
const int currentPinB = A4; // Current sensor for Phase B
const int currentPinC = A5; // Current sensor for Phase C

// Relay control pins
const int relayPinA = 9;
const int relayPinB = 10;
const int relayPinC = 11;

// Calibration constants
#define ADC_MAX 1024.0
#define VREF 3.3
#define VOLTAGE_SCALE 11.0  // Voltage divider scaling factor
#define CURRENT_OFFSET (VREF/2)  // Assume mid-point offset ~1.65V
#define CURRENT_SENSITIVITY 0.185  // ACS712 sensitivity in V/A

float readVoltage(int pin) {
  int adcValue = analogRead(pin);
  float voltage = (adcValue * (VREF / ADC_MAX)) * VOLTAGE_SCALE;
  return voltage;
}

float readCurrent(int pin) {
  int adcValue = analogRead(pin);
  float voltage = adcValue * (VREF / ADC_MAX);
  float current = (voltage - CURRENT_OFFSET) / CURRENT_SENSITIVITY;
  return current;
}

void setup() {
  Serial.begin(9600);
  
  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  // Initialize relay pins
  pinMode(relayPinA, OUTPUT);
  pinMode(relayPinB, OUTPUT);
  pinMode(relayPinC, OUTPUT);
  digitalWrite(relayPinA, LOW);
  digitalWrite(relayPinB, LOW);
  digitalWrite(relayPinC, LOW);
}

void loop() {
  // Read sensor values for each phase
  float vA = readVoltage(voltagePinA);
  float iA = readCurrent(currentPinA);
  float pA = vA * iA;
  
  float vB = readVoltage(voltagePinB);
  float iB = readCurrent(currentPinB);
  float pB = vB * iB;
  
  float vC = readVoltage(voltagePinC);
  float iC = readCurrent(currentPinC);
  float pC = vC * iC;
  
  // Display the measurements on OLED
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Phase A: ");
  display.print(vA,1);
  display.print("V ");
  display.print(iA,1);
  display.print("A ");
  display.print(pA,1);
  display.println("W");
  
  display.print("Phase B: ");
  display.print(vB,1);
  display.print("V ");
  display.print(iB,1);
  display.print("A ");
  display.print(pB,1);
  display.println("W");
  
  display.print("Phase C: ");
  display.print(vC,1);
  display.print("V ");
  display.print(iC,1);
  display.print("A ");
  display.print(pC,1);
  display.println("W");
  display.display();
  
  // Example relay control logic (if power > threshold, deactivate relay)
  float powerThreshold = 100.0; // Example threshold in Watts
  digitalWrite(relayPinA, (pA > powerThreshold) ? LOW : HIGH);
  digitalWrite(relayPinB, (pB > powerThreshold) ? LOW : HIGH);
  digitalWrite(relayPinC, (pC > powerThreshold) ? LOW : HIGH);
  
  delay(1000);
}

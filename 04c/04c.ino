#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define ANALOG_PIN  4
#define RED_PIN     40
#define YELLOW_PIN  41
#define GREEN_PIN   42
#define SW_PIN      2

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  Wire.begin(48, 47);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Light Level:");
  display.display(); 

  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(SW_PIN, INPUT_PULLUP);
  digitalWrite(RED_PIN, 0);
  digitalWrite(YELLOW_PIN, 0);
  digitalWrite(GREEN_PIN, 0);
  pinMode(SW_PIN, INPUT_PULLUP);

}
void loop() {
  int val = analogReadMilliVolts(ANALOG_PIN);
  printf("%d\n",analogReadMilliVolts(ANALOG_PIN));
  int percent = (3000 - val) / 30;
  if (0 <= percent && percent <= 33){
    digitalWrite(RED_PIN, 1);
    digitalWrite(YELLOW_PIN, 0);
    digitalWrite(GREEN_PIN, 0);
  }
  if (33< percent && percent <= 66){
    digitalWrite(RED_PIN, 0);
    digitalWrite(YELLOW_PIN, 1);
    digitalWrite(GREEN_PIN, 0);
  }
  if (66< percent && percent <=100){
    digitalWrite(RED_PIN, 0);
    digitalWrite(YELLOW_PIN, 0);
    digitalWrite(GREEN_PIN, 1);
  }


  if (digitalRead(SW_PIN) == LOW) {  // Switch is pressed
    display.clearDisplay();  // Clear the display
    display.setCursor(0, 10);
    display.println("Light Level:");
    display.fillRect(0, 20, 0.8 * (3000 - val) / 30, 10, SSD1306_INVERSE);

    // Use a buffer for formatted output
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d%%", (3000 - val) / 30);
    display.setCursor((0.8 * (3000 - val) / 30) + 10, 20);
    display.println(buffer);  // Print the formatted percentage

    display.setCursor(50, 50); // Set cursor to another location
    display.println("Pressed");
    display.display();  // Update the display with the new message
    Serial.println("Press detected"); // Debug output
} else {
    display.clearDisplay();  // Clear the display
    display.setCursor(0, 10);
    display.println("Light Level:");
    display.fillRect(0, 20, 0.8 * (3000 - val) / 30, 10, SSD1306_INVERSE);

    // Use the same buffer for formatted output
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d%%", (3000 - val) / 30);
    display.setCursor((0.8 * (3000 - val) / 30) + 10, 20);
    display.println(buffer);  // Print the formatted percentage

    display.setCursor(50, 50); // Reset cursor position
    display.println("");
    display.display();  // Update the display with the released message
    Serial.println("Release detected"); // Debug output
    
}

  delay(100);
}


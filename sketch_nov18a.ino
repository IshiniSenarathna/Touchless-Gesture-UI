#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String state = "HOME";

// --- Buttons ---
void printButton(int y, String name, bool hover, bool clicked) {
  if (clicked || hover) {
    display.fillRect(0, y, SCREEN_WIDTH, 10, WHITE);
    display.setTextColor(BLACK);
  } else {
    display.fillRect(0, y, SCREEN_WIDTH, 10, BLACK);
    display.setTextColor(WHITE);
  }
  display.setCursor(2, y);
  display.print(name);
}

// --- Page Topics ---
String getPageTopic(String s) {
  if (s == "HOME") return "HOME MENU";
  else if (s == "START_MENU") return "SELECT OPTION";
  else if (s == "PAYMENT") return "PAYMENT SECTION";
  else if (s == "BALANCE") return "ACCOUNT BALANCE";
  else if (s == "INTRO") return "INTRODUCTION";
  return "";
}

// --- Page Content ---
String getPageContent(String s) {
  if (s == "PAYMENT") return "PAYMENT SCREEN CONTENT";
  else if (s == "BALANCE") return "BALANCE SCREEN CONTENT";
  else if (s == "INTRO") return "WELCOME TO SYSTEM";
  return "";
}

void setup() {
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) while (1);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();
}

void loop() {
  while (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    int firstColon = msg.indexOf(':');
    int secondColon = msg.indexOf(':', firstColon + 1);
    if (firstColon != -1 && secondColon != -1) {
      state = msg.substring(0, firstColon);
      String hover = msg.substring(firstColon + 1, secondColon);
      String clicked = msg.substring(secondColon + 1);
      bool clickedFlag = clicked.toInt() == 1;

      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);

      int16_t x1, y1;
      uint16_t w, h;

      // --- Header ---
      String header = "TOUCHLESS SYSTEM";
      display.getTextBounds(header, 0, 0, &x1, &y1, &w, &h);
      display.setCursor((SCREEN_WIDTH - w) / 2, 0);
      display.println(header);

      // --- Topic (compact) ---
      String topic = getPageTopic(state);
      display.getTextBounds(topic, 0, 0, &x1, &y1, &w, &h);
      display.setCursor((SCREEN_WIDTH - w) / 2, 10); // reduced from 12
      display.println(topic);

      // --- Content (compact) ---
      String content = getPageContent(state);
      display.getTextBounds(content, 0, 0, &x1, &y1, &w, &h);
      display.setCursor((SCREEN_WIDTH - w) / 2, 18); // reduced from 24
      display.println(content);

      // --- Buttons (closer spacing) ---
      int btn_y_start = 28; // start closer to content
      int btn_spacing = 12; // smaller spacing
      if (state == "HOME") {
        printButton(btn_y_start, "START", hover == "START", clickedFlag && hover == "START");
        printButton(btn_y_start + btn_spacing, "INTRO", hover == "INTRO", clickedFlag && hover == "INTRO");
      } else if (state == "START_MENU") {
        printButton(btn_y_start, "PAYMENT", hover == "PAYMENT", clickedFlag && hover == "PAYMENT");
        printButton(btn_y_start + btn_spacing, "BALANCE", hover == "BALANCE", clickedFlag && hover == "BALANCE");
        printButton(btn_y_start + 2 * btn_spacing, "CANCEL", hover == "CANCEL", clickedFlag && hover == "CANCEL");
      } else if (state == "PAYMENT" || state == "BALANCE" || state == "INTRO") {
        printButton(btn_y_start + btn_spacing, "BACK", hover == "BACK", clickedFlag && hover == "BACK");
      }

      display.display();
    }
  }
}

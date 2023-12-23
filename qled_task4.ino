#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <TaskScheduler.h>

// Initialize the OLED display
U8G2_SSD1306_128X64_NONAME_F_SW_I2C
u8g2(U8G2_R0, /*clock=*/14,/*data=*/12,U8X8_PIN_NONE);

// Task callbacks
void helloCallback();
void byeCallback();
void welcomeCallback();

// Define tasks for each message
Task taskHello(1000, TASK_FOREVER, &helloCallback); // Run every 1000ms
Task taskBye(2000, TASK_FOREVER, &byeCallback);     // Run every 2000ms
Task taskWelcome(3000, TASK_FOREVER, &welcomeCallback); // Run every 3000ms

Scheduler runner;

void helloCallback() {
  displayMessage("Hello!");
}

void byeCallback() {
  displayMessage("Bye!");
}

void welcomeCallback() {
  displayMessage("Welcome!");
}

void displayMessage(const char* message) {
  Serial.println(message); // Debug message
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x14B_tr);
  u8g2.drawStr(0, 10, message);
  u8g2.sendBuffer();
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  u8g2.begin();

  runner.init();
  Serial.println("Initialized scheduler");

  runner.addTask(taskHello);
  runner.addTask(taskBye);
  runner.addTask(taskWelcome);

  taskHello.enable();
  taskBye.enable();
  taskWelcome.enable();
}

void loop() {
  runner.execute();
}


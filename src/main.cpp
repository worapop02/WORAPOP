#include <Arduino.h>
// กำหนดขาเชื่อมต่อ
#define POT_PIN 36  // ขาอ่านค่า Potentiometer (P1)
#define LED1_PIN 23
#define LED2_PIN 19
#define LED3_PIN 18
#define LED4_PIN 5
#define LED5_PIN 17
#define LED6_PIN 16
#define LED7_PIN 4
#define LED8_PIN 0

void setup() {
  // กำหนดโหมดขา LED เป็น OUTPUT
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  pinMode(LED5_PIN, OUTPUT);
  pinMode(LED6_PIN, OUTPUT);
  pinMode(LED7_PIN, OUTPUT);
  pinMode(LED8_PIN, OUTPUT);
  
  // กำหนดขา Potentiometer เป็น INPUT
  pinMode(POT_PIN, INPUT);
  
  Serial.begin(115200);  // เปิดการสื่อสาร Serial เพื่อตรวจสอบค่า
}

void loop() {
  int potValue = analogRead(POT_PIN);  // อ่านค่าจาก Potentiometer (0-4095)
  
  // แปลงค่า Potentiometer จาก 0-4095 เป็น 0-5V
  float voltage = (potValue / 4095.0) * 5.0;

  // แสดงค่าที่อ่านได้จาก Potentiometer
  Serial.print("Potentiometer Voltage: ");
  Serial.println(voltage);

  // ควบคุมการเปิด/ปิด LED ตามเงื่อนไขที่กำหนด
  if (voltage >= 0.0 && voltage < 1.0) {
    // ปิดทุก LED
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED3_PIN, LOW);
    digitalWrite(LED4_PIN, LOW);
    digitalWrite(LED5_PIN, LOW);
    digitalWrite(LED6_PIN, LOW);
    digitalWrite(LED7_PIN, LOW);
    digitalWrite(LED8_PIN, LOW);
  }
  else if (voltage >= 1.0 && voltage < 2.0) {
    // เปิด LED ที่ 1-3
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED3_PIN, HIGH);
    digitalWrite(LED4_PIN, LOW);
    digitalWrite(LED5_PIN, LOW);
    digitalWrite(LED6_PIN, LOW);
    digitalWrite(LED7_PIN, LOW);
    digitalWrite(LED8_PIN, LOW);
  }
  else if (voltage >= 2.0 && voltage < 3.0) {
    // เปิด LED ที่ 1-5
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED3_PIN, HIGH);
    digitalWrite(LED4_PIN, HIGH);
    digitalWrite(LED5_PIN, HIGH);
    digitalWrite(LED6_PIN, LOW);
    digitalWrite(LED7_PIN, LOW);
    digitalWrite(LED8_PIN, LOW);
  }
  else if (voltage >= 3.0) {
    // เปิด LED ทุกดวง
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED3_PIN, HIGH);
    digitalWrite(LED4_PIN, HIGH);
    digitalWrite(LED5_PIN, HIGH);
    digitalWrite(LED6_PIN, HIGH);
    digitalWrite(LED7_PIN, HIGH);
    digitalWrite(LED8_PIN, HIGH);
  }

  delay(100);  // หน่วงเวลาเล็กน้อยก่อนทำการตรวจสอบใหม่
}

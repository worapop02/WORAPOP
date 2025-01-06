#include <LiquidCrystal_I2C.h>

// กำหนด LCD
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

// กำหนดค่าเริ่มต้น
int menu = 0; // เมนูเริ่มต้น
int sw_next = 15; // ปุ่มเลือกเมนู
int sw_ok = 2; // ปุ่มยืนยันเมนู
int led1 = 23, led2 = 19, led3 = 18, led4 = 5, led5 = 17, led6 = 16, led7 = 4, led8 = 0;

// ฟังก์ชันสำหรับคืนค่า pin ของ LED ตามลำดับ
int getLED(int index) {
  switch (index) {
    case 1: return led1;
    case 2: return led2;
    case 3: return led3;
    case 4: return led4;
    case 5: return led5;
    case 6: return led6;
    case 7: return led7;
    case 8: return led8;
    default: return -1;
  }
}

// ฟังก์ชันตั้งสถานะ LED ทั้งหมด
void setAllLEDs(int state) {
  for (int i = 1; i <= 8; i++) {
    digitalWrite(getLED(i), state);
  }
}

// ฟังก์ชันกระพริบ LED ทั้งหมด
void blinkAllLEDs(int delayTime) {
  setAllLEDs(HIGH);
  delay(delayTime);
  setAllLEDs(LOW);
  delay(delayTime);
}

// ฟังก์ชันกระพริบ LED ทีละคู่
void blinkPairLEDs(int delayTime) {
  for (int i = 1; i <= 8; i += 2) { // ไล่เปิดไฟทีละคู่
    digitalWrite(getLED(i), HIGH);
    digitalWrite(getLED(i + 1), HIGH);
    delay(delayTime);
    digitalWrite(getLED(i), LOW);
    digitalWrite(getLED(i + 1), LOW);
  }
}

// ฟังก์ชันเปิด LED ทีละหลอด
void cycleLEDs(int delayTime) {
  for (int i = 1; i <= 8; i++) {
    digitalWrite(getLED(i), HIGH);
    delay(delayTime);
    digitalWrite(getLED(i), LOW);
  }
}

// ฟังก์ชันเปิด LED สลับระหว่างคู่-คี่
void alternateLEDs(int delayTime) {
  // เปิดเฉพาะ LED คี่
  for (int i = 1; i <= 8; i += 2) {
    digitalWrite(getLED(i), HIGH);
  }
  delay(delayTime);

  // ปิด LED ทั้งหมด
  setAllLEDs(LOW);

  // เปิดเฉพาะ LED คู่
  for (int i = 2; i <= 8; i += 2) {
    digitalWrite(getLED(i), HIGH);
  }
  delay(delayTime);

  // ปิด LED ทั้งหมด
  setAllLEDs(LOW);
}

// ฟังก์ชันไล่ไฟ
void chaseLEDs(int delayTime) {
  for (int i = 1; i <= 8; i++) {
    digitalWrite(getLED(i), HIGH);
    delay(delayTime);
    digitalWrite(getLED(i), LOW);
  }
  for (int i = 8; i >= 1; i--) {
    digitalWrite(getLED(i), HIGH);
    delay(delayTime);
    digitalWrite(getLED(i), LOW);
  }
}

// ฟังก์ชันเลือกทำงานของเมนู
void executeMenu(int menu) {
  switch (menu) {
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Menu 1: All LEDs");
      setAllLEDs(HIGH); // เปิดไฟทั้งหมด
      delay(1000);
      setAllLEDs(LOW); // ปิดไฟทั้งหมด
      break;

    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Menu 2: Alt LEDs");
      alternateLEDs(1000); // สลับไฟคู่-คี่ทุกๆ 1 วินาที
      break;

    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Menu 3: Cycle LEDs");
      cycleLEDs(200); // ไฟวิ่งทีละดวง
      break;

    case 4:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Menu 4: Blink Pairs");
      blinkPairLEDs(1000); // เปิดไฟทีละคู่ทุกๆ 1 วินาที
      break;

    case 5:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Menu 5: Chase LEDs");
      chaseLEDs(200); // ไฟไล่เรียง
      break;

    case 6:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Menu 6: Flash LEDs");
      setAllLEDs(HIGH);
      delay(500);
      setAllLEDs(LOW);
      delay(500);
      break;

    default:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Invalid Menu");
      break;
  }
}

void setup() {
  // เริ่มต้น LCD
  lcd.init();
  lcd.backlight();

  // ตั้งค่า Pin ของปุ่ม
  pinMode(sw_next, INPUT_PULLUP);
  pinMode(sw_ok, INPUT_PULLUP);

  // ตั้งค่า Pin ของ LED
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);

  // ปิดไฟ LED ทั้งหมด
  setAllLEDs(LOW);
}

void loop() {
  int status_next = digitalRead(sw_next);
  if (status_next == LOW) {
    menu++;
    if (menu > 6) {
      menu = 0;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Menu: ");
    lcd.print(menu);
    delay(200); // ป้องกันการกดซ้ำ
  }

  int status_ok = digitalRead(sw_ok);
  if (status_ok == LOW) {
    executeMenu(menu); // เรียกใช้เมนูที่เลือก
    delay(200); // ป้องกันการกดซ้ำ
  }
}
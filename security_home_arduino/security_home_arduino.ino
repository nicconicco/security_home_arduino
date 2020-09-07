#include <Keypad.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns
const int COLUMN_NUM_4 = 4; //three columns

/**
   Star wars music
*/
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
int counter = 0;
const int ledPin1 = 12;
const int ledPin2 = 13;

boolean alarmActivated = true;


char hexaKeys[ROW_NUM][COLUMN_NUM_4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROW_NUM] = {9, 8, 7, 6};
byte colPins[COLUMN_NUM_4] = {5, 4, 3, 2};

//char keys[ROW_NUM][COLUMN_NUM] = {
//  {'1','2','3'},
//  {'4','5','6'},
//  {'7','8','9'},
//  {'*','0','#'}
//};
//
//byte pin_rows[ROW_NUM] = {9, 8, 7, 6};
//byte pin_column[COLUMN_NUM] = {5, 4, 3};

//const int ledPin = 13;
const int buzzer = 11;

Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROW_NUM, COLUMN_NUM_4 );

const String password = "6666"; // change your password here
String input_password;

void setup() {
  Serial.begin(9600);
  input_password.reserve(32); // maximum input characters is 33, change if needed
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {

  char key = keypad.getKey();

  if (key) {
    Serial.println(key);

    switch (key)
    {
      case '*':
        clearInputPassword();
        break;

      case 'A':
        clearInputPassword();
        Serial.println("Activated Alarm");
        alarmActivated = true;
        break;

      case 'B':
        clearInputPassword();
        Serial.println("Sound ON");
        tocar();

        break;

      case 'C':
        clearInputPassword();
        Serial.println("Sound OFF");
        soundAlarm(alarmActivated);
        break;

      case 'D':
        clearInputPassword();
        soundAlarm(false);
        Serial.println("Deactivated");
        alarmActivated = false;
        break;

      case '#':
        checkPassword(input_password);
        break;

      default:
        input_password += key;
        //Serial.println(input_password);
    }
  }
}

void checkPassword(String input_password) {
  //Serial.println(input_password);
  if (password == input_password) {
    Serial.println("password is correct");
  } else {
    Serial.println("password is incorrect, try again");
    soundAlarm(alarmActivated);
  }
}

void soundAlarm(boolean alarmStatus) {
  if (alarmStatus) {
    int i = 0;
    while (i < 5) {
      musicAlarme();
      i++;
    }
  } else {
    noTone(buzzer);
  }
}
void musicAlarme() {
  //Aciona o buzzer na frequencia relativa ao Dó em Hz
  tone(buzzer, 261);
  // Espera um tempo para Desativar
  delay(200);
  //Desativa o buzzer
  noTone(buzzer);
  // Aciona o buzzer na frequencia relativa ao Ré em Hz
  tone(buzzer, 293);
  delay(200);
  noTone(buzzer);
  // Aciona o buzzer na frequencia relativa ao Mi em Hz
  tone(buzzer, 329);
  delay(200);
  noTone(buzzer);
  // Aciona o buzzer na frequencia relativa ao Fá em Hz
  tone(buzzer, 349);
  delay(200);
  noTone(buzzer);
  // Aciona o buzzer na frequencia relativa ao Sol em Hz
  tone(buzzer, 392);
  delay(200);
  noTone(buzzer);
}

void tocar() {
  //Play first section
  firstSection();

  //Play second section
  secondSection();

  //Variant 1
  beep(f, 250);
  beep(gS, 500);
  beep(f, 350);
  beep(a, 125);
  beep(cH, 500);
  beep(a, 375);
  beep(cH, 125);
  beep(eH, 650);

  delay(500);

  //Repeat second section
  secondSection();

  //Variant 2
  beep(f, 250);
  beep(gS, 500);
  beep(f, 375);
  beep(cH, 125);
  beep(a, 500);
  beep(f, 375);
  beep(cH, 125);
  beep(a, 650);

  delay(650);
}

void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(buzzer, note, duration);

  //Play different LED depending on value of 'counter'
  if (counter % 2 == 0)
  {
    digitalWrite(ledPin1, HIGH);
    delay(duration);
    digitalWrite(ledPin1, LOW);
  } else
  {
    digitalWrite(ledPin2, HIGH);
    delay(duration);
    digitalWrite(ledPin2, LOW);
  }

  //Stop tone on buzzerPin
  noTone(buzzer);

  delay(50);

  //Increment counter
  counter++;
}

void firstSection()
{
  beep(a, 500);
  beep(a, 500);
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);

  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);
}

void secondSection()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);
  beep(fSH, 250);

  delay(325);

  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);
  beep(cSH, 175);
  beep(cH, 125);
  beep(b, 125);
  beep(cH, 250);

  delay(350);
}

void clearInputPassword() {
  input_password = ""; // clear input password
  Serial.println("clear input password");
}

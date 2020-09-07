#include <Keypad.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns
const int COLUMN_NUM_4 = 4; //three columns

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

Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROW_NUM, COLUMN_NUM_4 );

const String password = "6666"; // change your password here
String input_password;

void setup() {
  Serial.begin(9600);
  input_password.reserve(32); // maximum input characters is 33, change if needed
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
        Serial.println("Activated");
        break;

      case 'B':
        clearInputPassword();
        Serial.println("Sound ON");
        break;

      case 'C':
        clearInputPassword();
        Serial.println("Sound OFF");
        break;

      case 'D':
        clearInputPassword();
        Serial.println("Deactivated");
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
  }
}

void clearInputPassword() {
  input_password = ""; // clear input password
  Serial.println("clear input password");
}

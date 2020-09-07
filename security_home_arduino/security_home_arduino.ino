#include <Keypad.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns
const int COLUMN_NUM_4 = 4; //three columns

char* musica[] = {"La","Re","Fa","Sol","La","Re", "Fa", "Sol", "Mi", "Pausa", "Sol", "Do", "Fa", "Mi", "Sol", "Do", "Fa", "Mi", "Re", "Fim"}; //Game of Thrones
int duracao[] = {700, 500, 300, 250, 250, 300, 200, 200, 700, 200, 500, 500, 200, 200, 200, 500, 200, 200, 500};
char* starwars[] = {"La","Pausa","La","Pausa","La","Pausa","Fa","Do","La","Pausa","Fa","Do","La","Pausa","Mi","Pausa","Mi","Pausa","Mi","Pausa","Fa","Do","Sol","Pausa","Fa","Do","La","Pausa","La","Pausa","La","Pausa","La","Pausa","La","Pausa","Sol#","Pausa","Sol","Fa#","Fa","Fa#","Fim"}; //Marcha Imperial
int dur[] = {400, 100, 400, 100, 400, 100, 300, 200, 300, 100, 300, 200, 300, 200, 400, 100, 400, 100, 400, 100, 300, 300, 200, 100 , 300, 300, 200, 200, 400, 50, 400, 50, 400, 50, 400, 50, 300, 50, 300, 200, 200, 200};


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
        soundAlarm(true, true);
        break;

      case 'C':
        clearInputPassword();
        Serial.println("Sound OFF");
        soundAlarm(false, true);
        break;

      case 'D':
        clearInputPassword();
        soundAlarm(false, false);
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
    soundAlarm(true, false);
  }
}

void soundAlarm(boolean alarmStatus, boolean fromTest) {
  if (alarmStatus) {
    // Aciona o buzzer na frequencia relativa ao Dó em Hz
//    tone(buzzer, 261);
//    // Espera um tempo para Desativar
//    delay(200);
//    //Desativa o buzzer
//    noTone(buzzer);
//    // Aciona o buzzer na frequencia relativa ao Ré em Hz
//    tone(buzzer, 293);
//    delay(200);
//    noTone(buzzer);
//    // Aciona o buzzer na frequencia relativa ao Mi em Hz
//    tone(buzzer, 329);
//    delay(200);
//    noTone(buzzer);
//    // Aciona o buzzer na frequencia relativa ao Fá em Hz
//    tone(buzzer, 349);
//    delay(200);
//    noTone(buzzer);
//    // Aciona o buzzer na frequencia relativa ao Sol em Hz
//    tone(buzzer, 392);
//    delay(200);
//    noTone(buzzer);
   tocar(starwars,dur);
  } else if(fromTest == false) {
    noTone(buzzer);
  }
}

void tocar(char* mus[], int tempo[]){
  int tom = 0;
  for(int i = 0; mus[i]!="Fim";i++){
    if(mus[i] == "Do") tom = 262;
    if(mus[i] == "Re") tom = 294;
    if(mus[i] == "Mi") tom = 330;
    if(mus[i] == "Fa") tom = 349;
    if(mus[i] == "Sol") tom = 392;
    if(mus[i] == "La") tom = 440;
    if(mus[i] == "Si") tom = 494;
    if(mus[i] == "Do#") tom = 528;
    if(mus[i] == "Re#") tom = 622;
    if(mus[i] == "Fa#") tom = 370;
    if(mus[i] == "Sol#") tom = 415;
    if(mus[i] == "La#") tom = 466;
    if(mus[i] == "Pausa") tom = 0;
    tone(buzzer, tom, tempo[i]);
    delay(tempo[i]);
  }
}

void clearInputPassword() {
  input_password = ""; // clear input password
  Serial.println("clear input password");
}

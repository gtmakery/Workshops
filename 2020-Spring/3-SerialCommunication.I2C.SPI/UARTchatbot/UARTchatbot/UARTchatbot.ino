#include <SoftwareSerial.h>
SoftwareSerial messenger(2, 3);
char username[11];
void setup()
{
  Serial.begin(9600);
  Serial.println("Enter your Name (10 chars)");
  int idx = 0;
  while(!Serial.available()) {
    delay(1000);
  }
  while (Serial.available() > 0) {
    username[idx] = Serial.read();
    username[idx+1] = '\0';
    idx++;
  }
  if (username[idx-1] == '\n') {username[idx-1] = '\0';}
  //while (Serial.available()) {Serial.read();}; // flush remaining input

  Serial.print("Hello, ");Serial.println(username);
  Serial.println("Enter a message!");
  
  messenger.begin(9600);
}

char send_message[50];
void loop()
{ 
  //get message from user
  int idx = 0;
  int sending = 0;
  while (Serial.available() && idx < 50) {
    sending = 1;
    send_message[idx++] = Serial.read();
    send_message[idx] = '\0';
  }
  while (idx < 50) {
    send_message[idx++] = '\0';
  }
  if (sending) {
    //send_message[idx + 1] = '\0';
    Serial.print(username);
    Serial.print(": ");
    Serial.println(send_message);
    messenger.write(username, 11);
    messenger.write(": ");
    messenger.write(send_message, idx);
  }
  int rcv = 0;
  while (messenger.available()) {
    rcv = 1;
    char t = messenger.read();
    if (t != '\0') {
      Serial.print(t);
    }
  }
  
  delay(500);
}

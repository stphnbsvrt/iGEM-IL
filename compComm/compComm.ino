#include <EEPROM.h>

int address = 0;
byte value;
String buffer = "";

void setup()
{
  Serial.begin(9600);
  delay(1000);
}


void loop()
{
  bufferInput();
  String ln = requestLine();
  if(ln.length() > 0) {
    processCommand(ln);
  }
}

void processCommand(String ln) {
  
  String temp = ln;
  String delim = "::";
  byte items = 1;
  while(temp.indexOf(delim) >= 0) {
    items++;
    temp = temp.substring(temp.indexOf(delim)+2, temp.length());
  }
  String params[items];
  int i = 0;
  temp = ln;
  
  while(temp.indexOf(delim) >= 0) {
    params[i] = temp.substring(0, temp.indexOf(delim));
    temp = temp.substring(temp.indexOf(delim)+2, temp.length());
    i++;
  }
  params[items-1] = temp.substring(0, ln.length());
  
  decideCommand(ln, params, items);
}

void decideCommand(String commandText, String* params, byte paramSize) {
  String command = params[0];
  
  if(command.equals("analogRead")) {
    readAnalog(commandText, params, paramSize);
  } else if (command.equals("analogWrite")) {
    writeAnalog(commandText, params, paramSize);
  } else if (command.equals("digitalRead")) {
    readDigital(commandText, params, paramSize);
  } else if (command.equals("digitalWrite")) {
    writeDigital(commandText, params, paramSize);
  } else if (command.equals("pinMode")) {
    //setPinMode(commandText, params, paramSize);
  } else if (command.equals("writeEEPROM")) {
    writeEEPROM(commandText, params, paramSize);
  } else if (command.equals("readEEPROM")) {
    readEEPROM(commandText, params, paramSize);
  } else {
    Serial.println("error::command not recognized");
  }
}

void readEEPROM(String commandText, String* params, byte paramSize) { //IMPLEMENTATION NEEDS TO BE UPDATED
  Serial.println(commandText + "::" + retrieveEEPROM());
}

void writeEEPROM(String commandText, String* params, byte paramSize) { //IMPLEMENTATION NEEDS TO BE UPDATED
  overwriteEEPROM(params[1]);
  Serial.println(commandText + "::done");
}

void readAnalog(String commandText, String* params, byte paramSize)
{
  int pinNum = params[1].toInt();
  Serial.println(commandText + "::" + String(analogRead(pinNum)));
}

void writeAnalog(String commandText, String* params, byte paramSize)
{
  int pinNum = params[1].toInt();
  int value = params[2].toInt();
  analogWrite(pinNum, value);
  Serial.println(commandText + "::done");
}

void readDigital(String commandText, String* params, byte paramSize)
{
  int pinNum = params[1].toInt();
  Serial.println(commandText + "::" + String(digitalRead(pinNum)));
}

void writeDigital(String commandText, String* params, byte paramSize)
{
  int pinNum = params[1].toInt();
  int value = params[2].toInt();
  digitalWrite(pinNum, value);
  Serial.println(commandText + "::done");
}
/*
void setPinMode(String commandText, String* params, byte paramSize)
{
  int pinNum = params[1].toInt();
  if(params[2].equals("INPUT")) {
  
  }
}*/
void bufferInput() {
  if(Serial.available()) {
    buffer += (char) Serial.read();
  }
}

String requestLine() {
  if(buffer.indexOf("xxx") < 0) {
    return "";
  } else {
    String nextLine = buffer.substring(0, buffer.indexOf("xxx"));
    buffer = ""; //NEEDS TO BE FIXED - DOESN'T BUFFER PROPERTY B/C IT WIPES IT CLEAN.
    return nextLine;
  }
}

void overwriteEEPROM(String data) {
  for(int i = 0; i < 255; i++) {
    if(i < data.length()) {
      EEPROM.write(i, data.charAt(i));
    } else {
      EEPROM.write(i, 255);
    }
  }
}

String retrieveEEPROM() {
  String data = "";
  for(int i = 0; i < 512; i++) {
    byte tempByte = EEPROM.read(i);
    if(tempByte == 255) {
      break;
    } else {
      data += (char) EEPROM.read(i);
    }
  }
  return data;
}



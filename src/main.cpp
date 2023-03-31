#include <Arduino.h>
#include <SoftwareSerial.h>

#define pinTXD 3
#define pinRXD 2

// RX = 2, TX = 3
SoftwareSerial HM10(pinRXD, pinTXD);

String string = "";
String serialConvert = "";

char serialReadData;

String executeAT(String serial_str, String description_str) {
    
    string = "";
    unsigned long milliTime = millis();
    HM10.println(serial_str);

    while (true){
        char serial_char = HM10.read();
        if (int(serial_char) == -1 or int(serial_char) == 42) {
            if ((millis() - milliTime) > 2000) {
                return "Error";
            }
            continue;
        }
        if (serial_char == '\n') {
            Serial.print("Bluetooth " + description_str);
            Serial.println(string.substring(0, string.length()));
            return string;
        }
        string += serial_char;
    }

}

void setup() {

    Serial.begin(9600);

    Serial.println("HM-10 serial started at 9600");
    HM10.begin(9600);

    // executeAT("AT+RENEW", "");
    // executeAT("AT+NAMERBot", "Device Name: ");
    // executeAT("AT+MODE2", "Device Mode: ");
    // executeAT("AT+PASS123456", "Device Password: ");

}

void loop() {
  
    HM10.listen();
    while (HM10.available() > 0) {
        serialReadData = HM10.read();
        serialConvert = String(serialReadData);
        Serial.write(serialReadData);
    }


    if (Serial.available()) {
        delay(10);
        HM10.write(Serial.read());
    }
  
}
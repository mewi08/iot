#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// Pines de LCD 16x2
int rs = 12;
int e = 11;
int d4 = 5;
int d5 = 4;
int d6 = 3;
int d7 = 2;

// Pines del sensor ultrasónico
int trig = 8;
int echo = 9;

// Pin del servo
int servo = 7;

// Pin del switch
int pinSwitch = 6;

// Variables
bool valvulaAbierta = false;
bool emergencia = false;
int alturaTanque = 400;

// Objetos
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
Servo servoMotor;

void setup() {
    // LCD
    lcd.begin(16, 2);

    // Servo
    servoMotor.attach(servo);
    servoMotor.write(0);

    // Sensor ultrasónico
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    digitalWrite(trig, LOW);

    // Switch
    pinMode(pinSwitch, INPUT_PULLUP);

    // Mensaje inicial
    lcd.setCursor(0, 0);
    lcd.print("Iniciando...");
    delay(1500);
    lcd.clear();
}

void abrirValvula() {
    for (int angulo = 0; angulo <= 90; angulo++) {
        servoMotor.write(angulo);
        delay(15);
    }

    valvulaAbierta = true;
}

void cerrarValvula() {
    for (int angulo = 90; angulo >= 0; angulo--) {
        servoMotor.write(angulo);
        delay(15);
    }

    valvulaAbierta = false;
}

float medirDistancia() {
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    long duracion = pulseIn(echo, HIGH);
    float distancia = duracion * 0.0343 / 2;
    return distancia;
}

void loop() {
    // Comprobar el estado del switch
    if (digitalRead(pinSwitch) == LOW) {
        emergencia = true;
    } else {
        emergencia = false;
    }

    if (emergencia) {
        // Cerrar la válvula
        if (valvulaAbierta) {
            cerrarValvula();
        }
        // Mostrar emergencia
        lcd.setCursor(0, 0);
        lcd.print("EMERGENCIA      ");
        lcd.setCursor(0, 1);
        lcd.print("Valvula: CERRADA");
        delay(500);
        return;
    }

    float distancia = medirDistancia();
    int porcentaje = map(distancia, alturaTanque, 0, 0, 100);

    if (porcentaje < 90 && !valvulaAbierta) {
        abrirValvula();
    } else if (porcentaje >= 90 && valvulaAbierta) {
        cerrarValvula();
    }

    lcd.setCursor(0, 0);
    lcd.print("Nivel: ");
    lcd.print(porcentaje);
    lcd.print("%   ");

    lcd.setCursor(0, 1);
    if (valvulaAbierta) {
        lcd.print("Valvula: ABIERTA");
    } else {
        lcd.print("Valvula: CERRADA");
    }
    delay(500);
}
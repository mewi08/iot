# Control automático de nivel de agua con Arduino

Sistema que mide el nivel de agua de un tanque con un sensor ultrasónico y controla una válvula (servomotor) de forma automática. Incluye un interruptor de emergencia que cierra la válvula y detiene el llenado. Desarrollado en VS Code con PlatformIO y simulado en Wokwi.

## Componentes

- Arduino Uno
- Sensor ultrasónico HC-SR04
- Servomotor (válvula)
- LCD 16x2 + potenciómetro (contraste) + resistencia de 1 kΩ
- Interruptor (emergencia)
- Protoboard

## Conexiones

| Elemento | Pin |
| --- | --- |
| HC-SR04 TRIG / ECHO | D8 / D9 |
| Servo (PWM) | D7 |
| Interruptor | D6 (otro extremo a GND) |
| LCD RS, E | D12, D11 |
| LCD D4, D5, D6, D7 | D5, D4, D3, D2 |

## Funcionamiento

1. El sensor mide la distancia al agua y Arduino la convierte en porcentaje (tanque de 400 cm).
2. Si el nivel es menor a 100 % y la válvula está cerrada, el servo la abre (90°).
3. Al llegar a 100 %, la cierra (0°).
4. El LCD muestra el nivel y el estado de la válvula.
5. Con el interruptor activado (LOW), la válvula se cierra y se muestra **EMERGENCIA**. Al desactivarlo, el control automático se reanuda.

## Herramientas

Desarrollado en **VS Code** con **PlatformIO** (compilación) y la extensión **Wokwi** (simulación).

## Estructura

```text
├── src/main.cpp       # Código principal
├── diagram.json       # Circuito de Wokwi
├── wokwi.toml         # Configuración de Wokwi
└── platformio.ini     # Configuración de PlatformIO
```

## Uso

1. Abre la carpeta del proyecto en VS Code.
2. Compila con PlatformIO (`Build`).
3. Inicia la simulación con Wokwi (`F1` → *Wokwi: Start Simulator*).
4. Ajusta `alturaTanque` (en cm) según la distancia real del sensor al fondo del tanque.

## Creditos

Desarrollado por: *Melanie Tello*
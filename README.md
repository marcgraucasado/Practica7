# PR7-MarcGrau

## PRÁCTICA 7: Buses de comunicación 3 (I2S)

## Objetivo:

El objetivo del código es reproducir un archivo de audio codificado en formato AAC desde la memoria flash del microcontrolador utilizando una biblioteca de audio específica. A continuación, se detallan los componentes y el flujo del programa.

## Bibliotecas incluidas:

Arduino.h: Esta es la biblioteca principal para programar en Arduino. Proporciona las definiciones básicas y funciones esenciales para trabajar con la plataforma Arduino.

AudioGeneratorAAC.h: Esta biblioteca permite decodificar archivos de audio en formato AAC.

AudioOutputI2S.h: Esta biblioteca proporciona soporte para la salida de audio a través del protocolo I2S (Inter-IC Sound), que se utiliza para transmitir audio digital.

AudioFileSourcePROGMEM.h: Esta biblioteca permite que el audio se lea desde la memoria flash del microcontrolador (PROGMEM).

sampleaac.h: Este archivo debe contener los datos del archivo de audio en formato AAC codificados en un array en PROGMEM.

## Variables: 

in: Un puntero a un objeto AudioFileSourcePROGMEM que se utiliza para leer el archivo de audio desde la memoria flash.

aac: Un puntero a un objeto AudioGeneratorAAC que se utiliza para decodificar el archivo de audio AAC.

out: Un puntero a un objeto AudioOutputI2S que se utiliza para enviar el audio decodificado a través del protocolo I2S.

## Función setup():

La función setup() se ejecuta una vez al iniciar el programa y se utiliza para configurar el entorno y las variables necesarias para la reproducción del audio.

Serial.begin(115200): Inicializa la comunicación serie a una velocidad de 115200 baudios para la depuración y el registro de mensajes.

audioLogger = &Serial: Asigna el puerto serie al logger de audio para registrar mensajes de depuración.

in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac)): Crea un nuevo objeto AudioFileSourcePROGMEM que contiene los datos de audio almacenados en la memoria flash.

aac = new AudioGeneratorAAC(): Crea un nuevo objeto AudioGeneratorAAC para decodificar el audio AAC.

out = new AudioOutputI2S(): Crea un nuevo objeto AudioOutputI2S para manejar la salida del audio a través del protocolo I2S.

aac->begin(in, out): Inicia la decodificación y reproducción del audio utilizando los objetos creados.

## Función loop():

La función loop() se ejecuta repetidamente en un bucle infinito y es responsable de mantener la reproducción del audio y manejar el final de la misma.

if (aac->isRunning()): Comprueba si el decodificador de audio está en funcionamiento.

aac->loop(): Si está en funcionamiento, llama a la función loop() del objeto aac para continuar la decodificación y reproducción del audio.

else: Si el decodificador de audio ha terminado la reproducción:

Serial.printf("AAC done\n"): Envía un mensaje a través del puerto serie indicando que la reproducción del audio ha terminado.

delay(1000): Introduce una pausa de 1 segundo antes de continuar el bucle, para evitar que el mensaje se envíe continuamente.

## Resumen:

El código está diseñado para reproducir un archivo de audio AAC almacenado en la memoria flash del microcontrolador utilizando la plataforma Arduino (salida de audio I2S) . Se inicializan los componentes necesarios en la función setup(), y la reproducción se gestiona dentro de la función loop(). La salida de audio se realiza a través del protocolo I2S, permitiendo que el audio decodificado se envíe a un DAC o amplificador conectado.


### CÓDIGO:
```cpp
// Inclou les llibreries necessàries per a generar àudio, llegir fitxers i comunicar-se via I2S
    #include <Arduino.h>
    #include "AudioGeneratorAAC.h"
    #include "AudioOutputI2S.h"
    #include "AudioFileSourcePROGMEM.h"
    #include "sampleaac.h"

    // Declaració d'objectes globals
    AudioFileSourcePROGMEM *in; // Font d'àudio des de la memòria flash
    AudioGeneratorAAC *aac; // Descodificador AAC
    AudioOutputI2S *out; // Sortida d'àudio per I2S (altaveus/DAC)

// Inicialitza la comunicació sèrie per a depuració
    void setup()
    {
    Serial.begin(115200);

    audioLogger = &Serial;
// Configura la font d'àudio amb les dades AAC emmagatzemades a la memòria flash
    in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
// Inicialitza el descodificador AAC i la sortida I2S
    aac = new AudioGeneratorAAC();
    out = new AudioOutputI2S();

// Inicia la reproducció: descodifica AAC i envia a la sortida I2S
    aac->begin(in, out);
    }


    void loop()
    {
    if (aac->isRunning()) {
        aac->loop();
    } else {
        Serial.printf("AAC done\n");
        delay(1000);
    }
    }
```

## Conclusión:

Hemos logrado configurar y controlar la reproducción de archivos de audio AAC almacenados en la memoria flash a través de la salida I2S. Esta práctica ha sido efectiva y nos proporciona una base sólida para futuros proyectos de audio.

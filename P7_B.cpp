#include "Audio.h"     // Librería para manejo de audio I2S
#include "SD.h"        // Librería para manejo de la tarjeta SD
#include "FS.h"        // Librería para sistemas de archivos
#include "Arduino.h"   // Librería base de Arduino

// Definición de pines para la tarjeta SD y el bus I2S
#define SD_CS          10  // Pin Chip Select para la tarjeta SD
#define SPI_MOSI      11   // Pin para la línea MOSI (Master Out, Slave In)
#define SPI_MISO      13   // Pin para la línea MISO (Master In, Slave Out)
#define SPI_SCK       12   // Pin para el reloj del bus SPI
#define I2S_DOUT       1   // Pin de salida de datos I2S
#define I2S_BCLK      42   // Pin para el reloj de bits I2S
#define I2S_LRC       21   // Pin para la señal de sincronización izquierda/derecha I2S

// Crear una instancia del objeto de audio
Audio audio;

void setup(){
    // Configurar el pin de selección de chip de la tarjeta SD como salida y ponerlo en estado alto
    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH);

    // Iniciar el bus SPI con los pines especificados
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);

    // Iniciar comunicación serial para depuración a 115200 baudios
    Serial.begin(115200);

    // Iniciar la tarjeta SD, debe estar conectada correctamente
    SD.begin(SD_CS);

    // Configurar los pines de audio para I2S
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);

    // Configurar el volumen de salida (rango de 0 a 21)
    audio.setVolume(10);

    // Conectar al sistema de archivos de la tarjeta SD y cargar el archivo de audio
    audio.connecttoFS(SD, "prova.wav");
}

void loop(){
    // Llamada periódica para mantener el flujo de datos de audio
    audio.loop();
}

// Funciones opcionales para manejar diferentes eventos de audio

// Muestra información general sobre el audio en el puerto serie
void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}

// Muestra datos ID3 (metadatos) del archivo de audio
void audio_id3data(const char *info){
    Serial.print("id3data     ");Serial.println(info);
}

// Señala el final de un archivo MP3
void audio_eof_mp3(const char *info){
    Serial.print("eof_mp3     ");Serial.println(info);
}

// Muestra el nombre de la estación si se está reproduciendo una radio en línea
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}

// Muestra información sobre el flujo de audio (bitrate, codec, etc.)
void audio_showstreaminfo(const char *info){
    Serial.print("streaminfo  ");Serial.println(info);
}

// Muestra el título de la canción si se está reproduciendo una radio en línea
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle ");Serial.println(info);
}

// Muestra el bitrate del archivo de audio
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}

// Señala un anuncio comercial en caso de estar escuchando una estación de radio
void audio_commercial(const char *info){
    Serial.print("commercial  ");Serial.println(info);
}

// Muestra la URL de la estación de radio, si está disponible
void audio_icyurl(const char *info){
    Serial.print("icyurl      ");Serial.println(info);
}

// Muestra la última URL de host para transmisiones en vivo
void audio_lasthost(const char *info){
    Serial.print("lasthost    ");Serial.println(info);
}

// Señala el final de un archivo de discurso si se usa la función de texto a voz
void audio_eof_speech(const char *info){
    Serial.print("eof_speech  ");Serial.println(info);
}
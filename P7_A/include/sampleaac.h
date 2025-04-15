#ifndef SAMPLEAAC_H
#define SAMPLEAAC_H

#include <pgmspace.h>

// Este es solo un array de prueba. Reemplaza con tu audio real.
const uint8_t sampleaac[] PROGMEM = {
  0xFF, 0xF1, 0x50, 0x80, 0x00, 0x1F, 0xFC, 0x21,
  0x00, 0x00, 0x00, 0x00, 0x00  // bytes de prueba
};
const uint32_t sampleaac_len = sizeof(sampleaac);

#endif

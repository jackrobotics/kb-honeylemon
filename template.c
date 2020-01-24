#include <Arduino.h>
#include <HONEYLemon.h>
#include <music.h>

${EXTINC}

${VARIABLE}

${FUNCTION}
music music;
void setup()
{
  Serial.begin(115200);
  lemon.begin();
  ${SETUP_CODE}
  ${BLOCKSETUP}
}
void loop()
{
  ${LOOP_CODE}
  ${LOOP_EXT_CODE}
}
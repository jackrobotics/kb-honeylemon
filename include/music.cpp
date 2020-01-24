#include "music.h"

void music::begin(void) {
    // ledcSetup(0, 5000, 27);
}

void music::tone(unsigned int frequency, unsigned long duration)
{
    if (ledcRead(0)) {
        log_e("Tone channel %d is already in use", ledcRead(0));
        return;
    }
    ledcAttachPin(27, 0);
    ledcWriteTone(0, frequency);
    if (duration) {
        delay(duration);
        noTone();
    }
}

void music::noTone()
{
    ledcDetachPin(27);
    ledcWrite(0, 0);
}

void music::song(std::vector<int>notes,int duration)
{
    for(int freq : notes){
        if(freq == -1){
            noTone();
            delay(duration);
        }else{
            tone(freq,duration);
        }
    }
}
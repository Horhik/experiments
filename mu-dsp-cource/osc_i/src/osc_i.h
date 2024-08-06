#ifndef OSC_I_H
#define OSC_I_H
#include <stdio.h>
#include <math.h>
#include <jack/jack.h>
#define PI_F 3.14159265f

extern float freq;
extern float vol;

typedef jack_default_audio_sample_t sample_t;
typedef float (*oscillator_t)(float);



extern const char *module_name;
extern oscillator_t osc;
extern jack_client_t *client;

// audio generation is here:

void jack_osc_init(const char *name, jack_client_t *client);
static void jack_finish(jack_client_t *client){
    jack_deactivate(client);
    jack_client_close(client);
}


#endif // OSC_I_H

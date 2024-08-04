#include <stdio.h>
#include <math.h>
#include <jack/jack.h>
#define PI_F 3.14159265f
static float freq;
static float vol;

typedef jack_default_audio_sample_t sample_t;

static void jack_finish(jack_client_t *client){
    jack_deactivate(client);
    jack_client_close(client);
}

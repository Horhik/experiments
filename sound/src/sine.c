/* sine_unbounded.c: sine oscillator with unbounded phasor */

#include <stdio.h>
#include <math.h>

#include "common.h"

#include "jack/types.h"

#define PI_F 3.14159265f
#include <jack/jack.h>

typedef jack_default_audio_sample_t sample_t;

static jack_client_t *client = NULL;
static jack_port_t *port_out = NULL;
static jack_port_t *port_in = NULL;


static int on_process(jack_nframes_t nframes, void *arg) {

  sample_t *in;
  sample_t *out;
  jack_nframes_t i;

  out = jack_port_get_buffer(port_out, nframes);
  in = jack_port_get_buffer(port_in, nframes);

  for (int i = 0; i < nframes; ++i) {
    out[i] = sinf(2*PI_F*in[i]);
  }

  return 0;
}


static void jack_init(char *client_name, jack_client_t* client) {

  client = jack_client_open(client_name, JackNoStartServer, NULL);


  jack_set_process_callback(client, on_process, NULL);

  port_out = jack_port_register(client, "out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  port_in  = jack_port_register(client, "phs", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);

  jack_activate(client);
}



int main(void) {

  jack_init("sine", client);

  /* idle main thread */
  catch_sigint();
  while(1){;} 

  jack_finish(client);
  return 0;
}

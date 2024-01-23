#include <stdio.h>
#include <jack/jack.h>
#include <math.h>

#define PI_F 3.14159265f

typedef jack_default_audio_sample_t sample_t;


static jack_client_t *client = NULL;
static jack_port_t *port_out = NULL;
static jack_port_t *port_in = NULL;



static int on_process(jack_nframes_t nframes, void *arg);
static void jack_init(void);
static void jack_finish(void);

sample_t saw_wave(sample_t sample){
  return (2*sample - 1);
}

sample_t square_wave(sample_t sample){
  return (sample >= 0.5 ? 1 : 0);
}

sample_t triangle_wave(sample_t sample){
  return 4*(sample >= 0.5 ? 1 - sample: sample) -1;
}




static int on_process(jack_nframes_t nframes, void *arg) {

  sample_t *in;
  sample_t *out;
  jack_nframes_t i;

  out = jack_port_get_buffer(port_out, nframes);
  // array input samples
  in = jack_port_get_buffer(port_in, nframes);

  for (int i = 0; i < nframes; ++i) {
    out[i] = triangle_wave(in[i]);
  }

  return 0;
}



static void jack_init(void) {

  client = jack_client_open("saw", JackNoStartServer, NULL);


  jack_set_process_callback(client, on_process, NULL);

  port_out = jack_port_register(client, "out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  port_in  = jack_port_register(client, "phs", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);

  jack_activate(client);
}

static void jack_finish(void) {

  jack_deactivate(client);
  jack_client_close(client);
}




int main(void) {

  jack_init();
  /* idle main thread */
  char a;
  while(a != 'c')
    a = getchar();


  jack_finish();
  return 0;
}

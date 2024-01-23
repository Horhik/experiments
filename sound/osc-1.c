/* sine_simple.c: sine oscillator with fixed frequency */
#include <stdio.h>
#include <math.h>
//#define PI_F 3.14159265f
#define PI_F (float)M_PI

#include <jack/jack.h>
typedef jack_default_audio_sample_t sample_t;

static jack_client_t *client = NULL;
static jack_port_t *port_out = NULL;
static jack_nframes_t sr;
static int cc = 0;

static int
on_process(jack_nframes_t nframes, void *arg)
{

  cc+=1;
  printf("new launched %d\n", nframes);
  static jack_nframes_t tick = 0;
  sample_t *out;
  jack_nframes_t i;

  out = jack_port_get_buffer(port_out, nframes);

  for (i = 0; i < nframes; ++i)
    out[i] = sin(2*PI_F * 440 * tick++/sr) - sin(2*PI_F * 441 * tick++/sr) + sin(2*PI_F * 221 * tick++/sr) + sin(2*PI_F * 110 * tick++/sr)+sin(2*PI_F * 112 * tick++/sr)  ;

  return 0;
}

static void
jack_init(void)
{
  client = jack_client_open("sine", JackNoStartServer, NULL);

  sr = jack_get_sample_rate(client);
  jack_set_process_callback(client, on_process, NULL);

  port_out = jack_port_register(client, "out",
                                JACK_DEFAULT_AUDIO_TYPE,
                                JackPortIsOutput, 0);

  jack_activate(client);
}

static void
jack_finish(void)
{
  jack_deactivate(client);
  jack_client_close(client);
}

int
main(void)
{
  jack_init();

  /* idle main thread */
  getchar();

  jack_finish();
  return 0;
}

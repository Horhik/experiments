/* sine_unbounded.c: sine oscillator with unbounded phasor */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include<unistd.h>
#include<signal.h>

#define PI_F 3.14159265f
#include <jack/jack.h>

typedef jack_default_audio_sample_t sample_t;

static jack_client_t *client = NULL;
static jack_port_t *port_out = NULL;
static jack_port_t *port_in = NULL;
static jack_port_t *port_x_in = NULL;
static jack_port_t *port_y_in = NULL;
static jack_nframes_t sr;
static float freq= 440;


static int on_process(jack_nframes_t nframes, void *arg) {

  static float phs= 0;
  sample_t *out, *in, *in_x, *in_y;
  jack_nframes_t i;
  float x,y;

  out = jack_port_get_buffer(port_out, nframes);

  in = jack_port_get_buffer(port_in, nframes);
  in_x = jack_port_get_buffer(port_x_in, nframes);
  in_y = jack_port_get_buffer(port_y_in, nframes);
  // array input samples

  for (i = 0; i < nframes; ++i) {
    y = in_y[i];
    x = in_x[i];
    //printf("sound: %f, x: %f, y: %f\n", in[i], x, y);
    if (in[i] < x)
      out[i] = (y/x)*in[i];
    else
      out[i] = ((1-y)/(1-x)) * (in[i] - x) + y;
  }

  return 0;
}





static void jack_init(void) {

  client = jack_client_open("phasor", JackNoStartServer, NULL);

  sr = jack_get_sample_rate(client);

  jack_set_process_callback(client, on_process, NULL);

  port_out = jack_port_register(client, "out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  port_in  = jack_port_register(client, "in", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
  port_x_in  = jack_port_register(client, "X-in", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
  port_y_in  = jack_port_register(client, "Y-in", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);

  jack_activate(client);
}

static void jack_finish(void) {

  jack_deactivate(client);

  jack_client_close(client);
}

void check_initial_frequency(int argc, char ** args){

  if(argc > 1){
    freq = (float)atof(args[1]);
  } else {
    freq = 220;
  }

  printf("The phasor frequency is %f", freq);

}

void update_frequency(){

  char a;
  float fq;

  while(a != 'c'){

    a = getchar();

    //scanf("%f", &fq);

    freq = fq;

  }
}

void sig_handler(int signum)
{
  printf("\nDo some signal handling actions here\n");
  exit( 0 );
}


int main(int argc, char *args[]) {


  jack_init();


  signal( SIGINT, sig_handler );
  while(1){
    freq = 440;
    ;
  }

  jack_finish();

  return 0;
}

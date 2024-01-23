/* sine_unbounded.c: sine oscillator with unbounded phasor */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define PI_F 3.14159265f
#include <jack/jack.h>


// BLOG MOUSE START

#include <SDL.h>

#include <signal.h>

static volatile int done = 0;


static void
die(const char *msg)
{
  SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s\n", msg);
  exit(1);
}


static void
on_signal(int signum)

{
  (void)signum;
  done = 1;
}


// BLOGK MOUSE ENDED

typedef jack_default_audio_sample_t sample_t;

static jack_client_t *client = NULL;
static jack_port_t *port_out = NULL;
static jack_nframes_t sr;
static float freq= 440;


static int on_process(jack_nframes_t nframes, void *arg) {

  static float phs= 0;
  sample_t *out;
  jack_nframes_t i;

  out = jack_port_get_buffer(port_out, nframes);
  // array input samples

  for (int i = 0; i < nframes; ++i) {
    out[i] = phs;
    phs += freq/sr;

    // keeping phs in [0; 1)
    if(phs >= 1) phs --;
    if(phs < 0) phs++;
  }

  return 0;
}


static void jack_init(void) {

  client = jack_client_open("phasor", JackNoStartServer, NULL);

  sr = jack_get_sample_rate(client);

  jack_set_process_callback(client, on_process, NULL);

  port_out = jack_port_register(client, "out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

  jack_activate(client);
}


static void jack_finish(void) {

  jack_deactivate(client);
  jack_client_close(client);
}

float map(float val, float x0, float x1, float y0, float y1){
  return y0 + (y1 - y0)*(val - x0)/(x1 - x0);
  }


int main(int argc, char *args[]) {

  // mouse inicialisation start
    int x = 0, y = 0, prev_x = 0, prev_y = 0;
  (void)argc;
  (void)args;

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    die("fail to init sdl");


  /* catch signal for grace shutdown */

  signal(SIGINT, on_signal);
  // mouset send


  if(argc > 1) {
    freq = (float)atof(args[1]);
  }
    printf("The phasor frequency is %f", freq);


  jack_init();
  /* idle main thread */
  char a;
  float fq;
  while(a != 'c'){

    SDL_Event evt;

    SDL_PollEvent(&evt);

    SDL_GetGlobalMouseState(&x, &y);
    printf("mouse: %d %d\n", x, y);
      /*
    if (x != prev_x || y != prev_y) {
      printf("mouse: %d %d\n", x, y);
      prev_x = x;
      prev_y = y;
      freq = (float)x;
    }
    */
    //a = getchar();
    //scanf("%f", &fq);
    freq = map(x, 0, 1920, 0, 12000);
  }

  jack_finish();

  SDL_Quit();
  return 0;
}

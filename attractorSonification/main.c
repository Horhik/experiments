#include <raylib.h>
#include <raymath.h>
#define HEIGHT 1080
#define WIDTH 1920
#define CENTER_X 1920/2
#define CENTER_Y 1080/2


/* sine_unbounded.c: sine oscillator with unbounded phasor */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define PI_F 3.14159265f
#include <jack/jack.h>

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




Vector3 lorenz(Vector3 vec, float sig, float p, float b) {
  Vector3 res;
  float x = vec.x,y = vec.y,z = vec.z;
  res.x = sig * (y - x);
  res.y = x * (p - z) - y;
  res.z = x*y - b*z;
  return res;

}



int main(void)
{


  jack_init();
  /* idle main thread */
  char a;
  float fq;






  InitWindow(WIDTH, HEIGHT, "raylib [core] example - basic window");
  Vector3 point = {1.0, 1.1, 1.05};
  Vector3 point2 = {0.0, 1.1, 1.05};
  float dt,s,p,b; s = 10; p = 24; b = 2.667; dt = 0.0001;
  float scale = 20.5;
  int mx, my; 
  while (!WindowShouldClose())
    {
      mx = GetMouseX();
      my = GetMouseY();
      BeginDrawing();
      Color color1 = GREEN; 
      Color color2 = YELLOW;
      point = Vector3Add(point , Vector3Scale(lorenz(point, s,p,b), dt));
      DrawPixel(point.x * scale + mx, point.z * scale   + my, color1);

      point2 = Vector3Add(point2 , Vector3Scale(lorenz(point2, s,p,b), dt));
      DrawPixel(point2.x * scale + mx, point2.z * scale   + my, color2);

      freq = 220  + point2.y * 80 + point.x * 220;

      EndDrawing();
    }

  CloseWindow();
  jack_finish();

  return 0;
}

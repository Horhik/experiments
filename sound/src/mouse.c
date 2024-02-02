#include "raylib.h"
#include <stdio.h>
#include <jack/jack.h>
#define SCREEN_SIZE 800

typedef jack_default_audio_sample_t sample_t;

static jack_client_t *client = NULL;
static jack_port_t *port_x_out = NULL;
static jack_port_t *port_y_out = NULL;
static jack_nframes_t sr;
static float freq= 440;


static int on_process(jack_nframes_t nframes, void *arg);

static void jack_init(void) {

  client = jack_client_open("mouse", JackNoStartServer, NULL);

  sr = jack_get_sample_rate(client);

  jack_set_process_callback(client, on_process, NULL);

  port_x_out = jack_port_register(client, "X-out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  port_y_out = jack_port_register(client, "Y-out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

  jack_activate(client);
}

static int on_process(jack_nframes_t nframes, void *arg){

  sample_t *out_x, *out_y;

  out_x = jack_port_get_buffer(port_x_out, nframes);
  out_y = jack_port_get_buffer(port_y_out, nframes);
  // array input samples

  for (int i = 0; i < nframes; ++i) {
    out_x[i] = (float) SCREEN_SIZE / (float) GetMouseX();
    out_y[i] = (float) SCREEN_SIZE / (float) GetMouseY();
  }

  return 0;
}

static void jack_finish(void) {

  jack_deactivate(client);

  jack_client_close(client);
}



int main(void)
{
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Mous Capturing");
    // initialize sound
    jack_init();

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("UP-DOWN: tone, RIGHT-LEFT: shape", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    // finishing sound
    jack_finish();
    CloseWindow();

    return 0;
}

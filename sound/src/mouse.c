// Mouse binded phasor
#include "raylib.h"
#include <stdio.h>
#include <jack/jack.h>
#include <stdlib.h>
#include "common.h"
#define SCREEN_SIZE 800
#define MAX_FREQUENCY 400

typedef jack_default_audio_sample_t sample_t;

static jack_client_t *client = NULL;
static jack_port_t *port_x_out = NULL;
static jack_port_t *port_pitch_out = NULL;
static jack_port_t *port_y_out = NULL;
static jack_nframes_t sr;
static float freq= 440;
static int state = 0;


static int on_process(jack_nframes_t nframes, void *arg);

static void jack_init(char *name, jack_client_t *client) {

  client = jack_client_open(name, JackNoStartServer, NULL);

  sr = jack_get_sample_rate(client);

  jack_set_process_callback(client, on_process, NULL);

  port_pitch_out = jack_port_register(client, "PITCH-out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  port_y_out = jack_port_register(client, "Y-out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  port_x_out = jack_port_register(client, "X-out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

  jack_activate(client);
}

static int on_process(jack_nframes_t nframes, void *arg){

  static float phs= 0;
  sample_t *out_x, *out_y, *out_pitch;
  jack_nframes_t i;

  out_pitch = jack_port_get_buffer(port_pitch_out, nframes);
  out_x = jack_port_get_buffer(port_x_out, nframes);
  out_y = jack_port_get_buffer(port_y_out, nframes);

  // array input samples

  static float old_freq;   
  for (int i = 0; i < nframes; ++i) {
    if(state) {
      old_freq = mapf(GetMouseX(), 0, SCREEN_SIZE, 0, MAX_FREQUENCY );
    }
    
    // if program in other state then keeping `old_freq` as it was the last time
    out_pitch[i] = phs;
    phs += old_freq/sr;

    if(phs >= 1) phs --;
    if(phs < 0) phs++;

    out_x[i] = mapf(GetMouseX(), 0, SCREEN_SIZE, 0.05f, 0.95f );
    out_y[i] = mapf(GetMouseY(), 0, SCREEN_SIZE, 0.05f, 0.95f );
  }



  return 0;
}

void frequency_mode(char *x, char *y){
  state = 1;
  ClearBackground(RAYWHITE);
  DrawText("UP-DOWN: tone, RIGHT-LEFT: shape", 190, 200, 20, LIGHTGRAY);
  sprintf(x, "X: %d", GetMouseX());
  sprintf(y, "Y: %d", GetMouseY());
  DrawText(x, 190, 220, 20, BLACK);
  DrawText(y, 190, 240, 20, BLACK);
}

void bend_mode(char *x, char *y){
  state = 0;
  ClearBackground(DARKBROWN);
  DrawText("UP-DOWN: tone, RIGHT-LEFT: shape", 190, 200, 20, LIGHTGRAY);
  sprintf(x, "X: %d", GetMouseX());
  sprintf(y, "Y: %d", GetMouseY());
  DrawText(x, 190, 220, 20, WHITE);
  DrawText(y, 190, 240, 20, WHITE);
}

void select_state_and_show(char *x, char *y) {
  DrawText("Right Ctrl to change the state", 190, 170, 20, PINK);
  if(IsKeyDown(KEY_LEFT_CONTROL))
    bend_mode(x,y);
  else frequency_mode(x,y);
}


int main(void)
{
  InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Mous Capturing");
  // initialize sound
  jack_init("mouse", client );

  char *x,*y;
  x = malloc((sizeof *x) * 20);
  y = malloc((sizeof *x) * 20);

  while (!WindowShouldClose())
    {
      BeginDrawing();
      ClearBackground(RAYWHITE);
      select_state_and_show(x,y);
      EndDrawing();
    }

  // finishing sound
  jack_finish(client);
  CloseWindow();

  return 0;
}

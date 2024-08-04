/* sine_simple.c: sine oscillator with fixed frequency */
#include <stdio.h>
#include <math.h>
#define PI_F 3.14159265f

#include <jack/jack.h>
typedef jack_default_audio_sample_t sample_t;

static jack_client_t *client = NULL;
static jack_port_t *port_out = NULL;
static jack_nframes_t sr;


static float freq;
static float vol;
static jack_nframes_t frames;

float my_sine(jack_nframes_t t, int f){

    return vol*sin(2*PI_F*f*t/sr);
}

// audio generation is here:
static int on_process(jack_nframes_t nframes, void *arg){


    frames = nframes;
    static jack_nframes_t tick = 0;

    sample_t *out;
    jack_nframes_t i;

    out = jack_port_get_buffer(port_out, nframes);

    for (i = 0; i < nframes; ++i)
        out[i] = my_sine(tick++, freq);

    return 0;
}

// initializing jack with specific on_process function
static void jack_init(void){
    // create jack client
    client = jack_client_open("sine", JackNoStartServer, NULL);

    // get sample rate
    sr = jack_get_sample_rate(client);

    // initialize process callback
    jack_set_process_callback(client, on_process, NULL);


    // initializing OUT port
    port_out = jack_port_register(client, "out",
                                  JACK_DEFAULT_AUDIO_TYPE,
                                  JackPortIsOutput, 0);
    // activating client
    jack_activate(client);
}

static void jack_finish(){
    jack_deactivate(client);
    jack_client_close(client);
}



/*******************************************************************************************
*
*   raylib [core] example - Mouse input
*
*   Example originally created with raylib 1.0, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main (void)
{
    jack_init();


    /* GRAPHIC PART! */
    /**********************************************************************************8*/
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - mouse input");

    Vector2 ballPosition = { -100.0f, -100.0f };
    Color ballColor = DARKBLUE;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        ballPosition = GetMousePosition();

        // freq is global variable:while
        freq = (ballPosition.x/screenWidth)*1800 ;
        vol = (ballPosition.y/screenHeight) ;

        char buf[128];
        char buf2[128];

        sprintf(buf, "freq = %f", freq);
        sprintf(buf2, "vol = %f", vol);

        DrawText(buf,  50,  50, 20, RED);
        DrawText(buf2,  50,  100, 20, RED);
        void DrawPixel(int posX, int posY, Color color);

        sample_t *out;
        jack_nframes_t i;

        out = jack_port_get_buffer(port_out, frames);
        float num = (float)screenWidth/(float)frames;

        for (i = 1; i < frames; ++i){
            DrawLine(i*num,  screenHeight/2 +  (int)(out[i]*100),
                     (i - 1)*num, screenHeight/2 +  (int)(out[i - 1]*100), BLUE);
            DrawLine(i*num,  screenHeight/2 +  10 + (int)(out[i]*100),
                     (i - 1)*num, screenHeight/2 + 10 +  (int)(out[i - 1]*100), RED);
            DrawLine(i*num,  screenHeight/2 + 20+ (int)(out[i]*100),
                     (i - 1)*num, screenHeight/2 + 20+  (int)(out[i - 1]*100), GREEN);


        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawCircleV(ballPosition, 40, ballColor);

            DrawText("move ball with mouse and click mouse button to change color", 10, 10, 20, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    /**********************************************************************************8*/
    /*GRAPHIC ENDED*/
    jack_finish();
    return 0;

}

#include "raylib.h"
#include "osc_i.h"


static float freq = 220.0 ;
static float vol = 1.0;

jack_client_t *client = NULL;
static jack_port_t *freq_out = NULL;
static jack_port_t *vol_out = NULL;
static jack_port_t *sound_in = NULL;
static jack_nframes_t sr;
static jack_nframes_t frames;



static int on_process(jack_nframes_t nframes, void *arg){


    frames = nframes;
    sample_t *out_freq;
    sample_t *out_vol;
    jack_nframes_t i;

    out_freq = jack_port_get_buffer(freq_out, nframes);
    out_vol = jack_port_get_buffer(vol_out, nframes);

    for (i = 0; i < nframes; ++i){
        out_freq[i] = freq;
        out_vol[i] = vol;
    }
    return 0;
}

// initializing jack with specific on_process function





static void jack_init(void){
    // create jack client
    client = jack_client_open("Frequency Changer", JackNoStartServer, NULL);

    // get sample rate
    sr = jack_get_sample_rate(client);

    // initialize process callback
    jack_set_process_callback(client, on_process, NULL);


    // initializing OUT port
    freq_out = jack_port_register(client, "freq",
                                  JACK_DEFAULT_AUDIO_TYPE,
                                  JackPortIsOutput, 0);
    vol_out = jack_port_register(client, "vol",
                                  JACK_DEFAULT_AUDIO_TYPE,
                                  JackPortIsOutput, 0);


    sound_in = jack_port_register(client, "audio in",
                                  JACK_DEFAULT_AUDIO_TYPE,
                                  JackPortIsInput, 0);
    // activating client
    jack_activate(client);
}

int main(){
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
        vol = (ballPosition.y/screenHeight)*1000 ;

        char buf[128];
        char buf2[128];

        sprintf(buf, "freq = %f", freq);
        sprintf(buf2, "vol = %f", vol);

        DrawText(buf,  50,  50, 20, RED);
        DrawText(buf2,  50,  100, 20, RED);
        void DrawPixel(int posX, int posY, Color color);

        const sample_t *sound;
        jack_nframes_t i;

        sound = jack_port_get_buffer(sound_in, frames);
        float num = (float)screenWidth/(float)frames;

        for (i = 1; i < frames; ++i){
            DrawLine(i*num,  screenHeight/2 +  (int)(sound[i]*100),
                     (i - 1)*num, screenHeight/2 +  (int)(sound[i - 1]*100), BLUE);
            DrawLine(i*num,  screenHeight/2 +  10 + (int)(sound[i]*100),
                     (i - 1)*num, screenHeight/2 + 10 +  (int)(sound[i - 1]*100), RED);
            DrawLine(i*num,  screenHeight/2 + 20+ (int)(sound[i]*100),
                     (i - 1)*num, screenHeight/2 + 20+  (int)(sound[i - 1]*100), GREEN);


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

    jack_finish(client);

}

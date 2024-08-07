/* sine_simple.c: sine oscillator with fixed frequency */
#include "osc_i.h"

// audio generation is here:
static int on_process(jack_nframes_t nframes, void *arg){


    frames = nframes;

    sample_t *out;
    const sample_t *in, *volume;
    jack_nframes_t i;



    in = jack_port_get_buffer(port_phase, nframes);
    volume = jack_port_get_buffer(port_volume, nframes);
    out = jack_port_get_buffer(port_out, nframes);

    for (i = 0; i < nframes; ++i)
        out[i] = volume[i]*osc(in[i]);

    return 0;
}

// initializing jack with specific on_process function





static void jack_init(void){
    // create jack client
    client = jack_client_open(module_name, JackNoStartServer, NULL);

    // get sample rate
    sr = jack_get_sample_rate(client);

    // initialize process callback
    jack_set_process_callback(client, on_process, NULL);


    // initializing OUT port
    port_out = jack_port_register(client, "out",
                                  JACK_DEFAULT_AUDIO_TYPE,
                                  JackPortIsOutput, 0);

    port_phase = jack_port_register(client, "in_phase",
                                  JACK_DEFAULT_AUDIO_TYPE,
                                  JackPortIsInput, 0);
    port_volume = jack_port_register(client, "in_vol",
                                  JACK_DEFAULT_AUDIO_TYPE,
                                  JackPortIsInput, 0);

    // activating client
    jack_activate(client);
}

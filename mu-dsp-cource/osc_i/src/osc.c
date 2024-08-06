#include "osc_i.h"


jack_client_t *client = NULL;
oscillator_t osc = NULL;
const char *module_name = NULL;


static jack_port_t *port_out = NULL;
static jack_port_t *port_phase = NULL;
static jack_port_t *port_volume = NULL;
static jack_nframes_t sr;
static jack_nframes_t frames;




static int on_osc_process(jack_nframes_t nframes, void *arg){

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





void jack_osc_init(const char* module_name, jack_client_t *client){
    // create jack client
    client = jack_client_open(module_name, JackNoStartServer, NULL);

    // get sample rate
    sr = jack_get_sample_rate(client);

    // initialize process callback
    jack_set_process_callback(client, on_osc_process, NULL);


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

#include "osc_i.h"

static jack_client_t *client = NULL;
static jack_port_t *port_out = NULL;
static jack_port_t *port_in = NULL;
static jack_nframes_t sr;
static jack_nframes_t frames;


static int phasor_process(jack_nframes_t nframes, void *arg ){

    const sample_t *in;
    sample_t *out;
    jack_nframes_t i;

    out = jack_port_get_buffer(port_out, nframes);
    in = jack_port_get_buffer(port_in, nframes);


    static float phase = 0;

    for ( i = 0; i < nframes; i++){
        out[i] = phase;
        phase += in[i]/sr;

        while(phase >= 1) phase--;
        while(phase < 0) phase++;
    }

}

static void jack_init(void){
    // create jack client
    client = jack_client_open("phasor", JackNoStartServer, NULL);

    // get sample rate
    sr = jack_get_sample_rate(client);

    // initialize process callback
    jack_set_process_callback(client, phasor_process, NULL);


    // initializing OUT port
    port_out = jack_port_register(client, "out",
                                  JACK_DEFAULT_AUDIO_TYPE,
                                  JackPortIsOutput, 0);
    port_in = jack_port_register(client, "in",
                                  JACK_DEFAULT_AUDIO_TYPE,
                                  JackPortIsInput, 0);

    // activating client
    jack_activate(client);
}

int main(){
    jack_init();
    getchar();
    jack_finish(client);
}

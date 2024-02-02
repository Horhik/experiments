

#include <math.h>
#define PI_F 3.14159265f
#include <jack/jack.h>

static void jack_init(void) {

  client = jack_client_open("saw", JackNoStartServer, NULL);


  jack_set_process_callback(client, on_process, NULL);

  port_out = jack_port_register(client, "out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  port_in  = jack_port_register(client, "phs", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);

  jack_activate(client);
}


static void jack_finish(void) {

  jack_deactivate(client);
  jack_client_close(client);
}


#include <jack/jack.h>

void jack_finish(jack_client_t *client);

void catch_sigint();

void termintate_on_sigint(int signum);

float mapf(float val, float x0, float x1, float y0, float y1);

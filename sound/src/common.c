#include <jack/jack.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void jack_finish(jack_client_t *client)
{

  jack_deactivate(client);
  jack_client_close(client);

}

void termintate_on_sigint(int signum)
{

  printf("\nSIGINT. terminating...\n");
  exit( 0 );

}

void catch_sigint()
{

  signal( SIGINT, termintate_on_sigint );

}

float mapf(float val, float x0, float x1, float y0, float y1){
  return y0 + (y1 - y0)*(val - x0)/(x1 - x0);
  }

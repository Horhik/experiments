#include "osc_i.h"


float my_sine(float phi){

    return sinf(2*PI_F*phi);
}


int main (void)

{

    module_name = "sine";
    osc = my_sine;

    jack_osc_init(module_name, client);

    getchar();

    jack_finish(client);
    return 0;

}

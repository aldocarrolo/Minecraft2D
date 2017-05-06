#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

#include "../../vsgl2.h"

using namespace std;
using namespace vsgl2;
using namespace vsgl2::general;
using namespace vsgl2::video;
using namespace vsgl2::audio;
using namespace vsgl2::io;
using namespace vsgl2::ttf_fonts;
using namespace vsgl2::utils;

int main(int argc, char* argv[])
{
    srand(time(NULL));

    init();
    set_window(1280,720,"Prova");

    float massimo = 60;
    float attuale = 45;

    float rosso = 255 - 255*(attuale/massimo);
    float verde = 255*(attuale/massimo);

    while(!done())
    {
        draw_filled_rect(0,0,get_window_width(), get_window_height(), Color(rosso, verde, 0,255));

        update();
    }

    close();
    return 0;
}

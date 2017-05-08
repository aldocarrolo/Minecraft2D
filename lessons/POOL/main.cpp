#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

#include "../../vsgl2.h"

#include "lib/global_variable.h"

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

    while(blocchi_droppati.size() > 0)
        blocchi_droppati.pop_back();

    init();
    set_window(WIDTH_WINDOW,HEIGHT_WINDOW,"Prova",1);

    // CARICAMENTO DEL CRAFTING IN MEMORIA
    caricamento_crafting();
    // CARICAMENTO DELLE INFORMAZIONI SUI TEMPI DI ROTTURA IN MEMORIA
    caricamento_breaking();

    while(!done() && stato_menu == -1)
    {
        menu();
        update();
    }

    if(stato_menu == 1)
    {
        mappa.crea();
        //salva_informazioni_giocatore();
        stato_menu = 2;
    }


    if(stato_menu == 2)
    {
        ifstream in("save/map_info.save");
        int temp, chunk;
        in >> temp >> chunk;
        in.close();

        mappa.preleva(chunk);
        preleva_informazioni_giocatore();

        while(!done())
        {
            mappa.update();

            gestione_giocatore(mappa.mappa);

            //delay_fps(60);
            update();
        }

        mappa.salva(mappa.chunk_attuale);
        salva_informazioni_giocatore();
    }

    wait_for_button_pressed();

    close();
    return 0;
}

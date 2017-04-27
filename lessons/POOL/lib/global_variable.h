/*** COSTANTI GLOBALI ***/

#define WIDTH_CHUNK 16        // LARGHEZZA DELLA MAPPA
#define HEIGHT_CHUNK 100       // ALTEZZA DELLA MAPPA
#define MAXWIDTH 48        // LARGHEZZA DELLA MAPPA
#define MAXHEIGHT 100       // ALTEZZA DELLA MAPPA
#define WIDTH_BLOCK 40      // LARGHEZZA BLOCCO
#define HEIGHT_BLOCK 40     // ALTEZZA BLOCCO
#define WIDTH_WINDOW 1280   // LARGHEZZA DELLA FINESTRA
#define HEIGHT_WINDOW 720   // ALTEZZA DELLA FINESTRA
#define WIDTH_INVENTORY 9
#define HEIGHT_INVENTORY 4
#define TOOLBAR 3

#define flag int

flag stato_menu = -1;

struct Coeff_Movimento
{
    float x = -20;
    float y = 0;
} coeff_movimento;

struct p
{
    float width = 30, height = 75;

    float x = WIDTH_WINDOW/2 - width/2, y = HEIGHT_WINDOW/2 - height/2;

    bool salto = true;
    float coeff_salto = 0;

    bool collisione_destra = false;
    bool collisione_sinistra = false;

    int selezione_toolbar = 0;

    int blocco_attuale_x = coeff_movimento.x/WIDTH_BLOCK - 16;
    int blocco_attuale_y = coeff_movimento.y/HEIGHT_BLOCK - 10;

    int inizio_finestra_x = max((int)(this->x - coeff_movimento.x)/(WIDTH_BLOCK) + WIDTH_CHUNK - 20, 0);
    int inizio_finestra_y = max((int)(this->y - coeff_movimento.y)/(HEIGHT_BLOCK) + WIDTH_CHUNK - 20, 0);
    int fine_finestra_x = min((int)(this->x - coeff_movimento.x)/(WIDTH_BLOCK) + WIDTH_CHUNK + 20, WIDTH_CHUNK*3);
    int fine_finestra_y = min((int)(this->y - coeff_movimento.y)/(HEIGHT_BLOCK) + WIDTH_CHUNK + 20, HEIGHT_CHUNK);

    int inventario[HEIGHT_INVENTORY][WIDTH_INVENTORY] =
    {
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},

        {8,0,0,0,0,0,0,0,0},
    };

    int inventario_quantita[HEIGHT_INVENTORY][WIDTH_INVENTORY] =
    {
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},

        {1,0,0,0,0,0,0,0,0},
    };

    int crafting[2][2] =
    {
        {0, 0},
        {0, 0},
    };


    int crafting_quantita[2][2] =
    {
        {0, 0},
        {0, 0},
    };

    int oggetto_risultato_crafting = 0, quantita_risultato_crafting = 0;

    int crafting_table[3][3] =
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };

    int crafting_table_quantita[3][3] =
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };

    int oggetto_risultato_crafting_table = 0, quantita_risultato_crafting_table = 0;

    int timer_blocco_distrutto = 0;
    int x_blocco_distrutto, y_blocco_distrutto,  tipo_blocco_distrutto;
    bool distruggere = false;
    bool distruggere_secondo_livello = false;

    int forza = 0;

} player;

int albero[6][5] =
{
    {0,4,4,4,0},
    {0,4,4,4,0},
    {4,4,4,4,4},
    {4,4,4,4,4},
    {0,0,5,0,0},
    {0,0,5,0,0},
};

struct Blocco_Droppato
{
    float x, y;
    int type;
};

vector<Blocco_Droppato> blocchi_droppati;

#include "Blocco/Blocco.h"

#include "util_library.h"
#include "lib/Menu/Menu.h"
#include "lib/Mappa/Mappa.h"
#include "lib/Player/Player.h"

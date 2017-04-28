// variabili preprocessore per le varie informazioni sulla mappa
// o informazioni simili

#define WIDTH_CHUNK 16      // LARGHEZZA DELLA MAPPA
#define HEIGHT_CHUNK 100    // ALTEZZA DELLA MAPPA
#define MAXWIDTH 48         // LARGHEZZA DELLA MAPPA
#define MAXHEIGHT 100       // ALTEZZA DELLA MAPPA
#define WIDTH_BLOCK 40      // LARGHEZZA BLOCCO
#define HEIGHT_BLOCK 40     // ALTEZZA BLOCCO
#define WIDTH_WINDOW 1280   // LARGHEZZA DELLA FINESTRA
#define HEIGHT_WINDOW 720   // ALTEZZA DELLA FINESTRA
#define WIDTH_INVENTORY 9   // LARGHEZZA MATRICE INVENTARIO
#define HEIGHT_INVENTORY 4  // ALTEZZA MATRICE INVENTARIO
#define TOOLBAR 3           // NUMERO DI RIGA DELLA TOOLBAR

int stato_menu = -1;    // VARIABILE CHE INDICA LO STATO DELLA SELEZIONE DEL MENU

struct Coeff_Movimento  // COEFFICIENTE UTILIZZATO PER L'INDIVIDUAZIONE E DISEGNO DELLA MAPPA
{
    float x = -20;
    float y = 0;
} coeff_movimento;

struct p    // STRUTTURA COMPLESSA CONTENENTE LE INFORMAZIONI RIGUARDANTI IL PERSONAGGIO
{
    float width = 30, height = 75;  // ALTEZZA E LARGHEZZA DELL'IMMAGINE DEL PERSONAGGIO

    // COORDINATE SU SCHERMO DEL PERSONAGGIO
    float x = WIDTH_WINDOW/2 - width/2, y = HEIGHT_WINDOW/2 - height/2;

    // COEFFICIENTE E FLAG PER IL SALTO
    bool salto = true;
    float coeff_salto = 0;

    // FLAG RIGUARDANTI LA COLISSIONE A DESTRA O A SINISTRA DEL GIOCATORE
    bool collisione_destra = false;
    bool collisione_sinistra = false;

    // INDICATORE DEL BLOCCO NELLA TOOLBAR (ESSO ANDRA' DA 0 A 9)
    int selezione_toolbar = 0;

    // INDICAZIONE DEL BLOCCO ATTUALE IN CUI SI TROVA IL GIOCATORE
    int blocco_attuale_x = coeff_movimento.x/WIDTH_BLOCK - 16;
    int blocco_attuale_y = coeff_movimento.y/HEIGHT_BLOCK - 10;

    // INFORMAZIONI CHE SERVONO PER IL DISEGNO DELLA MAPPA
    // QUESTE SERVONO PER NON DISEGNARE LA MAPPA INTERA MA SOLTANTO LA MAPPA
    // CHE PUO VEDERE IL GIOCATORE
    // MOLTO UTILE PER QUANTO RIGUARDA LA COMPLESSITA COMPUTAZIONALE CHE LA RIDUCE A TANTO
    int inizio_finestra_x = max((int)(this->x - coeff_movimento.x)/(WIDTH_BLOCK) + WIDTH_CHUNK - 20, 0);
    int inizio_finestra_y = max((int)(this->y - coeff_movimento.y)/(HEIGHT_BLOCK) + WIDTH_CHUNK - 20, 0);
    int fine_finestra_x = min((int)(this->x - coeff_movimento.x)/(WIDTH_BLOCK) + WIDTH_CHUNK + 20, WIDTH_CHUNK*3);
    int fine_finestra_y = min((int)(this->y - coeff_movimento.y)/(HEIGHT_BLOCK) + WIDTH_CHUNK + 20, HEIGHT_CHUNK);

    // MATRICE CONTENENTE I TIPO DI BLOCCHI CONTENUTI NELL'INVENTARIO
    int inventario[HEIGHT_INVENTORY][WIDTH_INVENTORY] =
    {
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},

        {0,0,0,0,0,0,0,0,0},
    };

    // MATRICE CONTENENTE LA QUANTITA' DI BLOCCHI CONTENUTI NELL'INVENTARIO
    int inventario_quantita[HEIGHT_INVENTORY][WIDTH_INVENTORY] =
    {
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},

        {0,0,0,0,0,0,0,0,0},
    };

    // MATRICE CONTENENTE I TIPI DI BLOCCHI CONTENUTI NELLA CRAFTING DELL'INVENTARIO
    int crafting[2][2] =
    {
        {0, 0},
        {0, 0},
    };

    // MATRICE CONTENENTE LA QUANTITA' DI BLOCCHI CONTENUTI NELLA CRAFTING DELL'INVENTARIO
    int crafting_quantita[2][2] =
    {
        {0, 0},
        {0, 0},
    };

    // VALORI CHE INDICANO IL TIPO DI BLOCCO E LA QUANTITA DI BLOCCHI CHE VENGONO RESTITUITI
    // DURANTE IL CRAFTING DI UN'OGGETTO
    int oggetto_risultato_crafting = 0, quantita_risultato_crafting = 0;

    // MATRICE CONTENENTE I TIPI DI BLOCCHI CONTENUTI NELLA CRAFTING TABLE IN CUI SI TROVA
    int crafting_table[3][3] =
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };

    // MATRICE CONTENENTE LA QUANTITA' DI BLOCCHI CONTENUTI NELLA CRAFTING TABLE IN CUI SI TROVA
    int crafting_table_quantita[3][3] =
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };

    // VALORI CHE INDICANO IL TIPO DI BLOCCO E LA QUANTITA DI BLOCCHI CHE VENGONO RESTITUITI
    // DURANTE IL CRAFTING DI UN'OGGETTO NELLA CRAFTING TABLE
    int oggetto_risultato_crafting_table = 0, quantita_risultato_crafting_table = 0;

    // TIMER CHE INDICA LA VELOCITA DI SPACCATURA DI UN BLOCCCO
    int timer_blocco_distrutto = 0;
    int x_blocco_distrutto, y_blocco_distrutto,  tipo_blocco_distrutto;

    bool distruggere = false;
    bool distruggere_secondo_livello = false;

    // VARIABILE CONTENENTE L'INFORMAZIONE SULLA FORZA DEL PERSONAGGIO
    // QUESTA SERVIRA' PER POI VEDERE QUANDO IL GIOCATORE PUO' SPACCARE UN BLOCCO O MENO
    int forza = 0;

} player;

struct Cursore  // STRUTTURA CONTENENTE LE INFORMAZIONI SUL CURSORE
{
    int x, y;
    int x_blocco, y_blocco; // COORDINATE DEL BLOCCO CHE INDICA IL CURSORE NELLA MAPPA

    int type = 0, quantita = 0; // TIPO E QUANTITA DI BLOCCHI CHE SONO SELEZIONATI DAL CURSORE

} cursore;

// DISEGNO DELL'ALBERO NELLA MAPPA
int albero[6][5] =
{
    {0,4,4,4,0},
    {0,4,4,4,0},
    {4,4,4,4,4},
    {4,4,4,4,4},
    {0,0,5,0,0},
    {0,0,5,0,0},
};

struct Blocco_Droppato  // STRUTTURA CONTENENTE LE COORDINATE E IL TIPO DI BLOCCO DROPPATO
{
    float x, y;
    int type;
};
vector<Blocco_Droppato> blocchi_droppati;

struct Blocchi_Inventario   // STRUTTURA CONTENENTE LE COORDINATE DI UN BLOCCO DELL'INVENTARIO
{
    int x, y;
};


// vari include delle librerie

#include "Blocco/Blocco.h"
#include "util_library.h"
#include "lib/Menu/Menu.h"
#include "lib/Mappa/Mappa.h"
#include "lib/Player/Player.h"

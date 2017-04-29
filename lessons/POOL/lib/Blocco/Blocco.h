// STRUTTURA CHE SERVE A INDICARE LE VARIE INFORMAZIONI RIGUARDANTI I BLOCCHI
struct Blocco
{
    string texture;     // INDICA L'IMMAGINE DEL BLOCCO/ELEMENTO
    bool distruggi;     // FLAG CHE INDICA SE E' POSSIBILE DISTRUGGERE IL BLOCCO
    bool trasparenza;   // FLAG CHE INDICA SE IL BLOCCO PUò ESSERE ATTRAVERSATO O E' UN BLOCCO SOLIDO
    bool rompi;         // FLAG CHE INDICA SE IL BLOCCO SI ROMPE QUANDO AL BLOCCO DI SOTTO NON C'E' NULLA
    bool blocco;        // FLAG CHE INDICA SE E' UN BLOCCO O UNO STRUMENTO (true INDICA CHE E' UN BLOCCO)

    int secondi;        // NUMERO DI SECONDI CHE VENGONO IMPIEGATI DAL GIOCATORE PER ROMPERE IL BLOCCO
    int durezza;        // DUREZZA DEL BLOCCO, CIOE' SE IL BLOCCO HA UNA DUREZZA MAGGIORE RISPETTO ALLA FORZA
                        // DEL IOCATORE ALLORA IL BLOCCO NON VERRA' DROPPATO

    int oggetto_droppato;   // BLOCCO DA DROPPRE NEL CASO IN CUI LA FORZA DEL GIOCATORE E' MAGGIORE O UGUALE ALLA DUREZZA
                            // DEL BLOCCO
};

Blocco blocchi[] =
{
    // BLOCCHI
    {"", false, true, false, false, 0, 0},     // ARIA
    {"image/grass.png", true, false, false, true, 900, 0, 2},     // ERBA
    {"image/dirt.png", true, false, false, true, 750, 0, 2},      // TERRA
    {"image/stone.png", true, false, false, true, 7500, 100,7},   // PIETRA COTTA
    {"image/leave.png", true, false, false, true, 350, 5, 4},     //FOGLIE
    {"image/oak_wood.png", true, false, false, true, 3000, 0, 5}, // LEGNO DI QUERCIA
    {"image/oak_plank.png", true, false, false, true, 3000, 0, 6},    // TAVOLA DI LEGNO DI QUERCIA
    {"image/cobblestone.png", true, false, false, true, 7500, 100, 7},    // PIETRA GREZZA
    {"image/crafting_table.png", true, false, false, true, 3500, 0, 8},    // TAVOLA DA LAVORO

    // OGGETTI
    {"image/stick.png", false, false, false, false, 0, 0, 9},    // PICCONE DI LEGNO

    // STRUMENTI DI LAVORO
    {"image/wood_pickaxe.png", false, false, false, false, 0, 0, 10},    // PICCONE DI LEGNO
};

struct Blocco
{
    string texture;
    bool distruggi;
    bool trasparenza;
    bool rompi;

    int secondi;
    int durezza;

    int oggetto_droppato;
};

Blocco blocchi[] =
{
    {"", false, true, false, 0, 0},
    {"image/grass.png", true, false, false, 900, 0, 2},
    {"image/dirt.png", true, false, false, 750, 0, 2},
    {"image/stone.png", true, false, false, 7500, 100,7},
    {"image/leave.png", true, false, false, 350, 5, 4},
    {"image/oak_wood.png", true, false, false, 3000, 0, 5},
    {"image/oak_plank.png", true, false, false, 3000, 0, 6},
    {"image/cobblestone.png", true, false, false, 7500, 100, 7},
    {"image/crafting_table.png", true, true, false, 3500, 0, 8},
};

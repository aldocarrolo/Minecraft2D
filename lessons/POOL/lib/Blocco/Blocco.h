// STRUTTURA CHE SERVE A INDICARE LE VARIE INFORMAZIONI RIGUARDANTI I BLOCCHI
struct Blocco
{
    int id;             // VALORE CHE INDICA L'ID DEL BLOCCO

    string texture;     // INDICA L'IMMAGINE DEL BLOCCO/ELEMENTO

    bool blocco;    // FLAG CHE INDICA SE L'OGGETTO E' UN BLOCCO FISICO O UN OGGETTO
    bool strumento; // FLAG CHE INDICA SE L'OGGETTO E' UNO STRUMENTO
                    // PUO' SEMBRARE INUTILE MA QUESTO FLAG SERVE MOLTO PER DIMINUIRE
                    // LA DURABILITA' DI UNO STRUMENTO

    // FLAG UTILI SE L'OGGETTO SELEZIONATO E' UN BLOCCO (GUARDARE IL FLAG blocco)
    bool distruggi;     // FLAG CHE INDICA SE E' POSSIBILE DISTRUGGERE IL BLOCCO
    bool trasparenza;   // FLAG CHE INDICA SE IL BLOCCO PUO' ESSERE ATTRAVERSATO O E' UN BLOCCO SOLIDO
    int secondi;        // NUMERO DI SECONDI CHE VENGONO IMPIEGATI DAL GIOCATORE PER ROMPERE IL BLOCCO

    int da_oggetto, a_oggetto;  // DA QUALE ID A QUALE ID L'OGGETTO PUO' ESSERE ROTTO
                                // CIOE' QUESTO RANGE INDICA CON QUALI BLOCCHI/STRUMENTI PUO' ESSERE DROPPATO L'OGGETTO
                                // QUESTE SERVIRA' PER L'AGGIUNTA DEGLI STRUMENTI
                                // ESEMPIO LE FOGLIE SI ROMPERANNO E VERRANNO DROPPATE ATTRAVERSO LE CESOIE

    int percentuale_senza_strumento;    // PERCENTUALE' DEL DROP DEL BLOCCO SENZA L'AUSILIO DEL CORRETTO STRUMENTO/BLOCCO
    int oggetto_droppato_senza_strumento;   // BLOCCO DA DROPPARE NEL CASO IN CUI NON VENGA UTILIZZATO LO STRUMENTO ADATTO

    int percentuale_strumento;    // PERCENTUALE' DEL DROP DEL BLOCCO CON L'AUSILIO DEL CORRETTO STRUMENTO/BLOCCO
    int oggetto_droppato_strumento;   // BLOCCO DA DROPPARE NEL CASO IN CUI VENGA UTILIZZATO LO STRUMENTO ADATTO

    // FLAG/VARIABILI UTILI PER GLI OGGETTI
    int durabilita;     // FLAG CHE INDICA QUANTA DURABILITA', CIOE' IL NUMERO DI BLOCCHI CHE POSSO SPACCARE CON ESSO

    // FLAG CHE INDICA QUANTI BLOCCHI POSSONO ESSERCI IN UNO SPAZIO DELL'INVENTARIO (DI SOLITO SONO MULTIPLI DI 2)
    int massima_stoccabilita;

    // VALORE INTERO CHE INDICA SE L'OGGETTO EMETTE LUCE (VERRA' SETTATO A -1 SE NON EMETTERA' LUCE DI ALCUN TIPO)
    int luce;
};

Blocco blocchi[MAXID] =
{
    // BLOCCHI
    /**
    *   BLOCCO D'ARIA
    *
    *   blocco = false
    *   strumento = false
    *   distruggi = false
    *   trasparenza = true
    *   secondi = 0
    *   da_oggetto = 0
    *   a_oggetto = 0
    *   percentuale_senza_strumento = 0
    *   oggetto_droppato_senza_strumento = 0
    *   percentuale_strumento = 0
    *   durabilita = 100
    *   massima_stoccabilita = 0
    *   luce = 0
    */
    {AIR, ".", false, false, false, true, 0, 0, 0, 0, 0, 0, 0, 100, 0, 4},                                                          // ARIA

    /**
    *   GRASS (blocco d'erba)
    *
    *   blocco = true
    *   strumento = false
    *   distruggi = true
    *   trasparenza = false
    *   secondi = 900ms
    *   da_oggetto = WOOD_SHOVEL
    *   a_oggetto = DIAMOND_SHOVEL
    *   percentuale_senza_strumento = 100
    *   oggetto_droppato_senza_strumento = DIRT
    *   percentuale_strumento = 100
    *   oggetto_droppato_strumento = DIRT
    *   durabilita = 100
    *   massima_stoccabilita = 64
    *   luce = -1
    */
    {GRASS, "image/grass.png", true, false, true, false, 900, WOOD_SHOVEL, DIAMOND_SHOVEL, 100, DIRT, 100, DIRT, 100, 64, -1},                    // ERBA

    /**
    *   DIRT (blocco di terra)
    *
    *   blocco = true
    *   strumento = false
    *   distruggi = true
    *   trasparenza = false
    *   secondi = 750ms
    *   da_oggetto = WOOD_SHOVEL
    *   a_oggetto = DIAMOND_SHOVEL
    *   percentuale_senza_strumento = 100
    *   oggetto_droppato_senza_strumento = DIRT
    *   percentuale_strumento = 100
    *   oggetto_droppato_strumento = DIRT
    *   durabilita = 100
    *   massima_stoccabilita = 64
    *   luce = -1
    */
    {DIRT, "image/dirt.png", true, false, true, false, 750, WOOD_SHOVEL, DIAMOND_SHOVEL, 100, DIRT, 100, DIRT, 100, 64, -1},                     // TERRA

    /**
    *   STONE (blocco di pietra cotta)
    *
    *   blocco = true
    *   strumento = false
    *   distruggi = true
    *   trasparenza = false
    *   secondi = 7500ms
    *   da_oggetto = WOOD_PICKAXE
    *   a_oggetto = DIAMOND_PICKAXE
    *   percentuale_senza_strumento = 100
    *   oggetto_droppato_senza_strumento = AIR
    *   percentuale_strumento = 100
    *   oggetto_droppato_strumento = COBBLESTONE
    *   durabilita = 100
    *   massima_stoccabilita = 64
    *   luce = -1
    */
    {STONE, "image/stone.png", true, false, true, false, 7500, WOOD_PICKAXE, DIAMOND_PICKAXE, 100, 0, 100, COBBLESTONE, 100, 64, -1},             // PIETRA COTTA

    /**
    *   COBBLESTONE (blocco di pietra grezza)
    *
    *   blocco = true
    *   strumento = false
    *   distruggi = true
    *   trasparenza = false
    *   secondi = 10000ms
    *   da_oggetto = WOOD_PICKAXE
    *   a_oggetto = DIAMOND_PICKAXE
    *   percentuale_senza_strumento = 100
    *   oggetto_droppato_senza_strumento = AIR
    *   percentuale_strumento = 100
    *   oggetto_droppato_strumento = COBBLESTONE
    *   durabilita = 100
    *   massima_stoccabilita = 64
    *   luce = -1
    */
    {COBBLESTONE, "image/cobblestone.png", true, false, true, false, 10000, WOOD_PICKAXE, DIAMOND_PICKAXE, 100, 0, 100, 4, 100, 64, -1},      // PIETRA GREZZA

    /**
    *   LEAVE (foglia)
    *
    *   blocco = true
    *   strumento = false
    *   distruggi = true
    *   trasparenza = false
    *   secondi = 350ms
    *   da_oggetto = SHEARS
    *   a_oggetto = SHEARS
    *   percentuale_senza_strumento = 100
    *   oggetto_droppato_senza_strumento = AIR
    *   percentuale_strumento = 100
    *   oggetto_droppato_strumento = LEAVE (da modificare quando si aggiungeranno gli alberelli)
    *   durabilita = 100
    *   massima_stoccabilita = 64
    *   luce = -1
    */
    {LEAVE, "image/leave.png", true, false, true, false, 350, SHEARS, SHEARS, 100, 0, 100, LEAVE, 100, 64, -1},                          // FOGLIE

    /**
    *   OAK_WOOD (pezzo di legno grezzo)
    *
    *   blocco = true
    *   strumento = false
    *   distruggi = true
    *   trasparenza = false
    *   secondi = 3000ms
    *   da_oggetto = WOOD_AXE
    *   a_oggetto = DIAMOND_AXE
    *   percentuale_senza_strumento = 100
    *   oggetto_droppato_senza_strumento = OAK_WOOD
    *   percentuale_strumento = 100
    *   oggetto_droppato_strumento = OAK_WOOD
    *   durabilita = 100
    *   massima_stoccabilita = 64
    *   luce = -1
    */
    {OAK_WOOD, "image/oak_wood.png", true, false, true, false, 3000, WOOD_AXE, DIAMOND_AXE, 100, OAK_WOOD, 100, OAK_WOOD, 100, 64, -1},                   // LEGNO DI QUERCIA

    /**
    *   OAK_PLANK (pezzo di legno lavorato)
    *
    *   blocco = true
    *   strumento = false
    *   distruggi = true
    *   trasparenza = false
    *   secondi = 3000ms
    *   da_oggetto = WOOD_AXE
    *   a_oggetto = DIAMOND_AXE
    *   percentuale_senza_strumento = 100
    *   oggetto_droppato_senza_strumento = OAK_PLANK
    *   percentuale_strumento = 100
    *   oggetto_droppato_strumento = OAK_PLANK
    *   durabilita = 100
    *   massima_stoccabilita = 64
    *   luce = -1
    */
    {OAK_PLANK, "image/oak_plank.png", true, false, true, false, 3000, WOOD_AXE, DIAMOND_AXE, 100, OAK_PLANK, 100, OAK_PLANK, 100, 64, -1},                  // LEGNO DI QUERCIA LAVORATO

    /**
    *   CRAFTING TABLE (tavola da lavoro)
    *
    *   blocco = true
    *   strumento = false
    *   distruggi = true
    *   trasparenza = false
    *   secondi = 3500ms
    *   da_oggetto = WOOD_AXE
    *   a_oggetto = DIAMOND_AXE
    *   percentuale_senza_strumento = 100
    *   oggetto_droppato_senza_strumento = CRAFTING_TABLE
    *   percentuale_strumento = 100
    *   oggetto_droppato_strumento = CRAFTING_TABLE
    *   durabilita = 100
    *   massima_stoccabilita = 64
    *   luce = -1
    */
    {CRAFTING_TABLE, "image/crafting_table.png", true, false, true, false, 3500, WOOD_AXE, DIAMOND_AXE, 100, CRAFTING_TABLE, 100, CRAFTING_TABLE, 100, 64, -1},             // TAVOLA DA LAVORO

    /**
    *   COAL ORE (minerale di carbone)
    *
    *   blocco = true
    *   strumento = false
    *   distruggi = true
    *   trasparenza = false
    *   secondi = 15000ms
    *   da_oggetto = WOOD_PICKAXE
    *   a_oggetto = DIAMOND_PICKAXE
    *   percentuale_senza_strumento = 100
    *   oggetto_droppato_senza_strumento = AIR
    *   percentuale_strumento = 100
    *   oggetto_droppato_strumento = COAL
    *   durabilita = 100
    *   massima_stoccabilita = 64
    *   luce = -1
    */
    {COAL_ORE, "image/coal_ore.png", true, false, true, false, 15000, WOOD_PICKAXE, DIAMOND_PICKAXE, 100, AIR, 100, COAL, 100, 64, -1},
    //{9,"image/torch.png", false, false, true, true, 50, 0, MAXID, 100, TORCH, 100, TORCH, 100, 64, 9},

    // OGGETTI
    {COAL, "image/coal.png", false, false, false, true, 0, 0, 0, 0, 0, 0, 0, 100, 64, -1},    // CARBONE
    {STICK, "image/stick.png", false, false, true, true, 0, 0, 0, 0, 0, 0, 0, 100, 64, -1},    // BASTONCINO DI LEGNO
    {TORCH, "image/torch.png", true, false, true, true, 50, 0, MAXID, 100, TORCH, 100, TORCH, 100, 64, 9},    // TORCIA

    // STRUMENTI DI LAVORO
    {WOOD_PICKAXE, "image/wood_pickaxe.png", false, true, false, true, 0, 0, 0, 0, 0, 0, 0, 60, 1, -1},    // PICCONE DI LEGNO
    {STONE_PICKAXE, "image/stone_pickaxe.png", false, true, false, true, 0, 0, 0, 0, 0, 0, 0, 132, 1, -1},    // PICCONE DI LEGNO

    {WOOD_AXE, "image/wood_axe.png", false, true, false, true, 0, 0, 0, 0, 0, 0, 0, 100, 1, -1},    // PICCONE DI LEGNO
    {STONE_AXE, "image/stone_axe.png", false, true, false, true, 0, 0, 0, 0, 0, 0, 0, 100, 1, -1},    // PICCONE DI LEGNO
};

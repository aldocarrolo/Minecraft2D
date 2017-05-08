    // MAPPA CONTENENTE I VARI MODI DI ROMPERE DEI BLOCCHI E LA SUA VELOCITA'
// CIOE' SE ROMPO UN BLOCCO DI PIETRA CON IL PICCONE SICURAMENTE SARA' PIU' VELOCE RISPETTO
// A ROMPERE LO STESSO TIPO DI BLOCCO CON UNO STRUMENTO NON ADATTO
// LA STRINGA RAMPPRESENTERA' L'ID UNIVICO DI OGNI POSSIBILE COMBINAZIONE
// ESEMPIO:
//      - PICCONE = 1
//      - PIETRA = 2
//      ID = "21" CIOE' ROMPO LA PIETRA CON IL PICCONE
// E L'INTERO COME VALORE SARA' LA VELOCITA' (IN MILLISECONDI) CHE SI AGGIUNGERA' AL PERSONAGGIO
map<string, int> breaking;

void caricamento_breaking()
{
    breaking[int_to_string(STONE) + int_to_string(WOOD_PICKAXE)] = 6350;
    breaking[int_to_string(COBBLESTONE) + int_to_string(WOOD_PICKAXE)] = 8500;
    breaking[int_to_string(COAL_ORE) + int_to_string(WOOD_PICKAXE)] = 12750;

    breaking[int_to_string(STONE) + int_to_string(STONE_PICKAXE)] = 6900;
    breaking[int_to_string(COBBLESTONE) + int_to_string(STONE_PICKAXE)] = 9500;
    breaking[int_to_string(COAL_ORE) + int_to_string(STONE_PICKAXE)] = 13850;

    breaking[int_to_string(OAK_WOOD) + int_to_string(WOOD_AXE)] = 1500;
    breaking[int_to_string(OAK_PLANK) + int_to_string(WOOD_AXE)] = 1500;

    breaking[int_to_string(OAK_WOOD) + int_to_string(STONE_AXE)] = 2250;
    breaking[int_to_string(OAK_PLANK) + int_to_string(STONE_AXE)] = 2250;
    breaking[int_to_string(CRAFTING_TABLE) + int_to_string(STONE_AXE)] = 1850;

    breaking[int_to_string(GRASS) + int_to_string(WOOD_SHOVEL)] = 450;
    breaking[int_to_string(DIRT) + int_to_string(WOOD_SHOVEL)] = 350;
}

map<string, pair<int, int>> crafting;

void caricamento_crafting()
{
    // CRAFTING DEL OAK_PLANK
    // nell'inventario
    crafting[int_to_string(OAK_WOOD) + "0" +
            "00"].first = OAK_PLANK;
    crafting[int_to_string(OAK_WOOD) + "0" +
            "00"].second = 4;

    crafting["0" + int_to_string(OAK_WOOD) +
            "00"].first = OAK_PLANK;
    crafting["0" + int_to_string(OAK_WOOD) +
            "00"].second = 4;

    crafting["00" +
            int_to_string(OAK_WOOD) + "0"].first = OAK_PLANK;
    crafting["00" +
            int_to_string(OAK_WOOD) + "0"].second = 4;

    crafting["000" +
            int_to_string(OAK_WOOD)].first = OAK_PLANK;
    crafting["000" +
            int_to_string(OAK_WOOD)].second = 4;

    // nella crafting table
    crafting[int_to_string(OAK_WOOD) + "00000000"].first = OAK_PLANK;
    crafting[int_to_string(OAK_WOOD) + "00000000"].second = 4;

    crafting["0"+int_to_string(OAK_WOOD) + "0000000"].first = OAK_PLANK;
    crafting["0"+int_to_string(OAK_WOOD) + "0000000"].second = 4;

    crafting["00"+int_to_string(OAK_WOOD) + "000000"].first = OAK_PLANK;
    crafting["00"+int_to_string(OAK_WOOD) + "000000"].second = 4;

    crafting["000"+int_to_string(OAK_WOOD) + "00000"].first = OAK_PLANK;
    crafting["000"+int_to_string(OAK_WOOD) + "00000"].second = 4;

    crafting["0000"+int_to_string(OAK_WOOD) + "0000"].first = OAK_PLANK;
    crafting["0000"+int_to_string(OAK_WOOD) + "0000"].second = 4;

    crafting["00000"+int_to_string(OAK_WOOD) + "000"].first = OAK_PLANK;
    crafting["00000"+int_to_string(OAK_WOOD) + "000"].second = 4;

    crafting["000000"+int_to_string(OAK_WOOD) + "00"].first = OAK_PLANK;
    crafting["000000"+int_to_string(OAK_WOOD) + "00"].second = 4;

    crafting["0000000"+int_to_string(OAK_WOOD) + "0"].first = OAK_PLANK;
    crafting["0000000"+int_to_string(OAK_WOOD) + "0"].second = 4;

    crafting["00000000"+int_to_string(OAK_WOOD)].first = OAK_PLANK;
    crafting["00000000"+int_to_string(OAK_WOOD)].second = 4;

    // CRAFTING CRAFTING_TABLE
    // nell'inventario
    crafting[int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) +
             int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK)].first = CRAFTING_TABLE;
    crafting[int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) +
             int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK)].second = 1;

    // nella crafting table
    crafting[int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "0" + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "0000"].first = CRAFTING_TABLE;
    crafting[int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "0" + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "0000"].second = 1;

    crafting["0" + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "0" + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "000"].first = CRAFTING_TABLE;
    crafting["0" + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "0" + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "000"].second = 1;

    crafting["000" + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "0" + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "0"].first = CRAFTING_TABLE;
    crafting["000" + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "0" + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "0"].second = 1;

    crafting["0000" + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "0" + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK)].first = CRAFTING_TABLE;
    crafting["0000" + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "0" + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK)].second = 1;

    // STICK
    // nell'inventario
    crafting[int_to_string(OAK_PLANK) + "0" +
             int_to_string(OAK_PLANK) + "0"].first = STICK;
    crafting[int_to_string(OAK_PLANK) + "0" +
             int_to_string(OAK_PLANK) + "0"].second = 4;

    crafting["0" + int_to_string(OAK_PLANK) +
             "0" + int_to_string(OAK_PLANK)].first = STICK;
    crafting["0" + int_to_string(OAK_PLANK) +
             "0" + int_to_string(OAK_PLANK)].second = 4;

    // nella crafting table
    crafting[int_to_string(OAK_PLANK) + "00" + int_to_string(OAK_PLANK) + "00000"].first = STICK;
    crafting[int_to_string(OAK_PLANK) + "00" + int_to_string(OAK_PLANK) + "00000"].second = 4;

    crafting["0" + int_to_string(OAK_PLANK) + "00" + int_to_string(OAK_PLANK) + "0000"].first = STICK;
    crafting["0" + int_to_string(OAK_PLANK) + "00" + int_to_string(OAK_PLANK) + "0000"].second = 4;

    crafting["00" + int_to_string(OAK_PLANK) + "00" + int_to_string(OAK_PLANK) + "000"].first = STICK;
    crafting["00" + int_to_string(OAK_PLANK) + "00" + int_to_string(OAK_PLANK) + "000"].second = 4;

    crafting["000" + int_to_string(OAK_PLANK) + "00" + int_to_string(OAK_PLANK) + "00"].first = STICK;
    crafting["000" + int_to_string(OAK_PLANK) + "00" + int_to_string(OAK_PLANK) + "00"].second = 4;

    crafting["0000" + int_to_string(OAK_PLANK) + "00" + int_to_string(OAK_PLANK) + "0"].first = STICK;
    crafting["0000" + int_to_string(OAK_PLANK) + "00" + int_to_string(OAK_PLANK) + "0"].second = 4;

    crafting["00000" + int_to_string(OAK_PLANK) + "00" + int_to_string(OAK_PLANK)].first = STICK;
    crafting["00000" + int_to_string(OAK_PLANK) + "00" + int_to_string(OAK_PLANK)].second = 4;

    // TORCH
    // nell'inventario
    crafting[int_to_string(COAL) + "0" +
             int_to_string(STICK) + "0"].first = TORCH;
    crafting[int_to_string(COAL) + "0" +
             int_to_string(STICK) + "0"].second = 4;

    crafting["0" + int_to_string(COAL) +
             "0" + int_to_string(STICK)].first = TORCH;
    crafting["0" + int_to_string(COAL) +
             "0" + int_to_string(STICK)].second = 4;

    // nella crafting table
    crafting[int_to_string(COAL) + "00" + int_to_string(STICK) + "00000"].first = TORCH;
    crafting[int_to_string(COAL) + "00" + int_to_string(STICK) + "00000"].second = 4;

    crafting["0" + int_to_string(COAL) + "00" + int_to_string(STICK) + "0000"].first = TORCH;
    crafting["0" + int_to_string(COAL) + "00" + int_to_string(STICK) + "0000"].second = 4;

    crafting["00" + int_to_string(COAL) + "00" + int_to_string(STICK) + "000"].first = TORCH;
    crafting["00" + int_to_string(COAL) + "00" + int_to_string(STICK) + "000"].second = 4;

    crafting["000" + int_to_string(COAL) + "00" + int_to_string(STICK) + "00"].first = TORCH;
    crafting["000" + int_to_string(COAL) + "00" + int_to_string(STICK) + "00"].second = 4;

    crafting["0000" + int_to_string(COAL) + "00" + int_to_string(STICK) + "0"].first = TORCH;
    crafting["0000" + int_to_string(COAL) + "00" + int_to_string(STICK) + "0"].second = 4;

    crafting["00000" + int_to_string(COAL) + "00" + int_to_string(STICK)].first = TORCH;
    crafting["00000" + int_to_string(COAL) + "00" + int_to_string(STICK)].second = 4;

    // WOOD_PICKAXE
    // nella crafting table
    crafting[int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) +
            "0" + int_to_string(STICK) + "0"+
            "0" + int_to_string(STICK) + "0"].first = WOOD_PICKAXE;
    crafting[int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) +
            "0" + int_to_string(STICK) + "0"+
            "0" + int_to_string(STICK) + "0"].second = 1;

    // STONE_PICKAXE
    // nella crafting table
    crafting[int_to_string(COBBLESTONE) + int_to_string(COBBLESTONE) + int_to_string(COBBLESTONE) +
            "0" + int_to_string(STICK) + "0"+
            "0" + int_to_string(STICK) + "0"].first = STONE_PICKAXE;
    crafting[int_to_string(COBBLESTONE) + int_to_string(COBBLESTONE) + int_to_string(COBBLESTONE) +
            "0" + int_to_string(STICK) + "0"+
            "0" + int_to_string(STICK) + "0"].second = 1;

    // WOOD_AXE
    // nella crafting table
    crafting[int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "0" +
            int_to_string(OAK_PLANK) + int_to_string(STICK) + "0"+
            "0" + int_to_string(STICK) + "0"].first = WOOD_AXE;
    crafting[int_to_string(OAK_PLANK) + int_to_string(OAK_PLANK) + "0" +
            int_to_string(OAK_PLANK) + int_to_string(STICK) + "0"+
            "0" + int_to_string(STICK) + "0"].second = 1;

    // STONE_AXE
    // nella crafting table
    crafting[int_to_string(COBBLESTONE) + int_to_string(COBBLESTONE) + "0" +
            int_to_string(COBBLESTONE) + int_to_string(STICK) + "0"+
            "0" + int_to_string(STICK) + "0"].first = STONE_AXE;
    crafting[int_to_string(COBBLESTONE) + int_to_string(COBBLESTONE) + "0" +
            int_to_string(COBBLESTONE) + int_to_string(STICK) + "0"+
            "0" + int_to_string(STICK) + "0"].second = 1;

    // WOOD_SHOVEL
    // nella crafting table
    crafting["0" + int_to_string(OAK_PLANK) + "0" +
            "0" + int_to_string(STICK) + "0"+
            "0" + int_to_string(STICK) + "0"].first = WOOD_SHOVEL;
    crafting["0" + int_to_string(OAK_PLANK) + "0" +
            "0" + int_to_string(STICK) + "0"+
            "0" + int_to_string(STICK) + "0"].second = 1;
}

void disegna_sfondo()
{
    for(int i = 0; i < 40; i++)
    {
        for(int j = 0; j < WIDTH_CHUNK*2; j++)
            draw_image("image/dirt.png", j*40, i*40, 40, 40, 255);
    }

    draw_filled_rect(0,WIDTH_BLOCK, WIDTH_WINDOW, HEIGHT_WINDOW-WIDTH_BLOCK*2, Color(0,0,0,125));
}

void disegna_logo()
{
    draw_image("image/logo.png", WIDTH_WINDOW/2 - 1920/6, 80, 1920/3, 400/3, 255);
}

bool bottone(string testo, int dim, int x, int y, int width, int height)
{
    bool valore_ritorno = false;

    string immagine_bottone = "image/button_unpressed.png";
    if(controllo_collisione(get_mouse_x(), get_mouse_y(), 0, 0, x, y, width, height))
    {
        if(mouse_left_button_pressed())
            valore_ritorno = true;
        immagine_bottone = "image/button_pressed.png";
    }

    draw_image(immagine_bottone, x, y, width, height, 255);

    disegna_testo("font/Minecraftia-Regular.ttf", dim, testo, x + width/2 - (testo.size()*dim)/2 + 15, y + 7, Color(255,255,255,255));

    return valore_ritorno;
}

void menu()
{
    disegna_sfondo();

    disegna_logo();

    if(bottone("Crea", 17, WIDTH_WINDOW/2 - 200, 80+133 + 80, 200*2, 20*2))
        stato_menu = 1;
    if(bottone("Accedi", 17, WIDTH_WINDOW/2 - 200, 80+133 + 120 + 20, 200*2, 20*2))
        stato_menu = 2;
    if(bottone("Esci", 17, WIDTH_WINDOW/2 - 200, 80+133 + 180 + 20, 200*2, 20*2))
        stato_menu = 0;
}



struct Blocchi_Inventario
{
    int x, y;
};

struct Cursore
{
    int x, y;

    int type = 0, quantita = 0;

} cursore;

int n_blocchi_inventario = 36;

Blocchi_Inventario blocchi_inventario[HEIGHT_INVENTORY][WIDTH_INVENTORY] =
{
//    {WIDTH_WINDOW/2 - 176 + 16,HEIGHT_WINDOW/2 - 166 + 16},
//    {WIDTH_WINDOW/2 - 176 + 16,HEIGHT_WINDOW/2 - 166 + 52},
//    {WIDTH_WINDOW/2 - 176 + 16,HEIGHT_WINDOW/2 - 166 + 88},
//    {WIDTH_WINDOW/2 - 176 + 16,HEIGHT_WINDOW/2 - 166 + 124},
    {
        {WIDTH_WINDOW/2 - 176 + 16,HEIGHT_WINDOW/2 - 166 + 168},
        {WIDTH_WINDOW/2 - 176 + 52,HEIGHT_WINDOW/2 - 166 + 168},
        {WIDTH_WINDOW/2 - 176 + 88,HEIGHT_WINDOW/2 - 166 + 168},
        {WIDTH_WINDOW/2 - 176 + 124,HEIGHT_WINDOW/2 - 166 + 168},
        {WIDTH_WINDOW/2 - 176 + 160,HEIGHT_WINDOW/2 - 166 + 168},
        {WIDTH_WINDOW/2 - 176 + 196,HEIGHT_WINDOW/2 - 166 + 168},
        {WIDTH_WINDOW/2 - 176 + 232,HEIGHT_WINDOW/2 - 166 + 168},
        {WIDTH_WINDOW/2 - 176 + 268,HEIGHT_WINDOW/2 - 166 + 168},
        {WIDTH_WINDOW/2 - 176 + 304,HEIGHT_WINDOW/2 - 166 + 168},
    },

    {
        {WIDTH_WINDOW/2 - 176 + 16,HEIGHT_WINDOW/2 - 166 + 204},
        {WIDTH_WINDOW/2 - 176 + 52,HEIGHT_WINDOW/2 - 166 + 204},
        {WIDTH_WINDOW/2 - 176 + 88,HEIGHT_WINDOW/2 - 166 + 204},
        {WIDTH_WINDOW/2 - 176 + 124,HEIGHT_WINDOW/2 - 166 + 204},
        {WIDTH_WINDOW/2 - 176 + 160,HEIGHT_WINDOW/2 - 166 + 204},
        {WIDTH_WINDOW/2 - 176 + 196,HEIGHT_WINDOW/2 - 166 + 204},
        {WIDTH_WINDOW/2 - 176 + 232,HEIGHT_WINDOW/2 - 166 + 204},
        {WIDTH_WINDOW/2 - 176 + 268,HEIGHT_WINDOW/2 - 166 + 204},
        {WIDTH_WINDOW/2 - 176 + 304,HEIGHT_WINDOW/2 - 166 + 204},
    },

    {
        {WIDTH_WINDOW/2 - 176 + 16,HEIGHT_WINDOW/2 - 166 + 240},
        {WIDTH_WINDOW/2 - 176 + 52,HEIGHT_WINDOW/2 - 166 + 240},
        {WIDTH_WINDOW/2 - 176 + 88,HEIGHT_WINDOW/2 - 166 + 240},
        {WIDTH_WINDOW/2 - 176 + 124,HEIGHT_WINDOW/2 - 166 + 240},
        {WIDTH_WINDOW/2 - 176 + 160,HEIGHT_WINDOW/2 - 166 + 240},
        {WIDTH_WINDOW/2 - 176 + 196,HEIGHT_WINDOW/2 - 166 + 240},
        {WIDTH_WINDOW/2 - 176 + 232,HEIGHT_WINDOW/2 - 166 + 240},
        {WIDTH_WINDOW/2 - 176 + 268,HEIGHT_WINDOW/2 - 166 + 240},
        {WIDTH_WINDOW/2 - 176 + 304,HEIGHT_WINDOW/2 - 166 + 240},
    },

    {
        {WIDTH_WINDOW/2 - 176 + 16,HEIGHT_WINDOW/2 - 166 + 284},
        {WIDTH_WINDOW/2 - 176 + 52,HEIGHT_WINDOW/2 - 166 + 284},
        {WIDTH_WINDOW/2 - 176 + 88,HEIGHT_WINDOW/2 - 166 + 284},
        {WIDTH_WINDOW/2 - 176 + 124,HEIGHT_WINDOW/2 - 166 + 284},
        {WIDTH_WINDOW/2 - 176 + 160,HEIGHT_WINDOW/2 - 166 + 284},
        {WIDTH_WINDOW/2 - 176 + 196,HEIGHT_WINDOW/2 - 166 + 284},
        {WIDTH_WINDOW/2 - 176 + 232,HEIGHT_WINDOW/2 - 166 + 284},
        {WIDTH_WINDOW/2 - 176 + 268,HEIGHT_WINDOW/2 - 166 + 284},
        {WIDTH_WINDOW/2 - 176 + 304,HEIGHT_WINDOW/2 - 166 + 284},
    },
};

Blocchi_Inventario crafting_inventario[2][2] =
{
    {{WIDTH_WINDOW/2 - 176 + 98*2, HEIGHT_WINDOW/2 - 166 + 18*2}, {WIDTH_WINDOW/2 - 176 + 116*2, HEIGHT_WINDOW/2 - 166 + 18*2}},
    {{WIDTH_WINDOW/2 - 176 + 98*2, HEIGHT_WINDOW/2 - 166 + 36*2}, {WIDTH_WINDOW/2 - 176 + 116*2, HEIGHT_WINDOW/2 - 166 + 36*2}}
};

Blocchi_Inventario risultato_crafting = {WIDTH_WINDOW/2 - 176 + 154*2, HEIGHT_WINDOW/2 - 166 + 28*2};

void disegna_inventario()
{
    draw_filled_rect(0,0,WIDTH_WINDOW, HEIGHT_WINDOW, Color(0,0,0,125));

    draw_image("image/inventory.png", WIDTH_WINDOW/2 - 176, HEIGHT_WINDOW/2 - 166, 176*2, 166*2, 255);
}

static int flag_controllo_tasto = 0;
bool bottone_premuto()
{
    static bool valore_ritorno = false;

    if(is_pressed(VSGL_E) && flag_controllo_tasto != 1)
    {
        valore_ritorno = !valore_ritorno;
        flag_controllo_tasto = 1;
    }

    if(!is_pressed(VSGL_E) && flag_controllo_tasto == 1)
        flag_controllo_tasto = 0;

    return valore_ritorno;
}

void tasto_sinistro_inventario(int i, int j)
{
    static int tasto_sinistro_inventaro = 0;

    if(mouse_left_button_pressed() && tasto_sinistro_inventaro != 1)
    {
        tasto_sinistro_inventaro  = 1;

        if(cursore.type == 0)
        {
            cursore.type = player.inventario[i][j];
            cursore.quantita = player.inventario_quantita[i][j];
            player.inventario[i][j] = 0;
            player.inventario_quantita[i][j] = 0;
        }
        else
        {
            if(player.inventario[i][j] == 0)
            {
                player.inventario[i][j] = cursore.type;
                player.inventario_quantita[i][j] = cursore.quantita;
                cursore.type = 0;
                cursore.quantita = 0;
            }
            else if(player.inventario[i][j] == cursore.type)
            {
                player.inventario_quantita[i][j] += cursore.quantita;

                if(player.inventario_quantita[i][j] > 64)
                {
                    cursore.quantita = player.inventario_quantita[i][j] - 64;
                    player.inventario_quantita[i][j] = 64;
                }
                else
                {
                    cursore.type = 0;
                    cursore.quantita = 0;
                }
            }
            else
            {
                swap(player.inventario[i][j], cursore.type);
                swap(player.inventario_quantita[i][j], cursore.quantita);
            }
        }
    }

    if(!mouse_left_button_pressed() && tasto_sinistro_inventaro  == 1)
    {
        tasto_sinistro_inventaro = 0;
    }
}

void tasto_destro_inventario(int i, int j)
{
    static int tasto_destro_inventaro = 0;

    if(mouse_right_button_pressed() && tasto_destro_inventaro != 1)
    {
        tasto_destro_inventaro  = 1;

        if(player.inventario[i][j] == 0 && cursore.type != 0)
        {
            cursore.quantita--;
            player.inventario[i][j] = cursore.type;
            player.inventario_quantita[i][j]++;

            if(cursore.quantita == 0)
                cursore.type = 0;
        }
        else if(player.inventario[i][j] == cursore.type && cursore.type != 0 && player.inventario_quantita[i][j] < 64)
        {
            cursore.quantita--;
            player.inventario_quantita[i][j]++;

            if(cursore.quantita == 0)
                cursore.type = 0;
        }
        else if(player.inventario[i][j] != 0 && cursore.type != 0)
        {
            swap(player.inventario[i][j], cursore.type);
            swap(player.inventario_quantita[i][j], cursore.quantita);
        }
    }

    if(!mouse_right_button_pressed() && tasto_destro_inventaro  == 1)
    {
        tasto_destro_inventaro = 0;
    }
}

void tasto_sinistro_crafting(int i, int j)
{
    static int tasto_sinistro_crafting = 0;

    if(mouse_left_button_pressed() && tasto_sinistro_crafting != 1)
    {
        tasto_sinistro_crafting  = 1;

        if(cursore.type == 0)
        {
            cursore.type = player.crafting[i][j];
            cursore.quantita = player.crafting_quantita[i][j];
            player.crafting[i][j] = 0;
            player.crafting_quantita[i][j] = 0;
        }
        else
        {
            if(player.crafting[i][j] == 0)
            {
                player.crafting[i][j] = cursore.type;
                player.crafting_quantita[i][j] = cursore.quantita;
                cursore.type = 0;
                cursore.quantita = 0;
            }
            else if(player.crafting[i][j] == cursore.type)
            {
                player.crafting_quantita[i][j] += cursore.quantita;

                if(player.crafting_quantita[i][j] > 64)
                {
                    cursore.quantita = player.crafting_quantita[i][j] - 64;
                    player.crafting_quantita[i][j] = 64;
                }
                else
                {
                    cursore.type = 0;
                    cursore.quantita = 0;
                }
            }
            else
            {
                swap(player.crafting[i][j], cursore.type);
                swap(player.crafting_quantita[i][j], cursore.quantita);
            }
        }
    }

    if(!mouse_left_button_pressed() && tasto_sinistro_crafting  == 1)
    {
        tasto_sinistro_crafting = 0;
    }
}

void tasto_destro_crafting(int i, int j)
{
    static int tasto_destro_crafting = 0;

    if(mouse_right_button_pressed() && tasto_destro_crafting != 1)
    {
        tasto_destro_crafting  = 1;

        if(player.crafting[i][j] == 0 && cursore.type != 0)
        {
            cursore.quantita--;
            player.crafting[i][j] = cursore.type;
            player.crafting_quantita[i][j]++;

            if(cursore.quantita == 0)
                cursore.type = 0;
        }
        else if(player.crafting[i][j] == cursore.type && cursore.type != 0 && player.crafting_quantita[i][j] < 64)
        {
            cursore.quantita--;
            player.crafting_quantita[i][j]++;

            if(cursore.quantita == 0)
                cursore.type = 0;
        }
        else if(player.crafting[i][j] != 0 && cursore.type != 0)
        {
            swap(player.crafting[i][j], cursore.type);
            swap(player.crafting_quantita[i][j], cursore.quantita);
        }
    }

    if(!mouse_right_button_pressed() && tasto_destro_crafting  == 1)
    {
        tasto_destro_crafting = 0;
    }
}

void controllo_crafting()
{
    string file = "crafting/";
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            file += int_to_string(player.crafting[i][j]);

    file += ".save";

    ifstream in(file);

    if(in != NULL)
    {
        int valore, quantita;
        in >> valore >> quantita;

        player.oggetto_risultato_crafting = valore;
        player.quantita_risultato_crafting = quantita;

        draw_image(blocchi[player.oggetto_risultato_crafting].texture, risultato_crafting.x + 6, risultato_crafting.y + 6, 20,20, 255);
        draw_filled_rect(risultato_crafting.x + 5, risultato_crafting.y + 5, 22, 22, Color(0,0,0,50));

        draw_rect(risultato_crafting.x + 5, risultato_crafting.y + 5, 22,22, Color(0,0,0,255));

        string quantita_crafting = int_to_string(player.quantita_risultato_crafting);
        disegna_testo("font/Minecraftia-Regular.ttf", 13, quantita_crafting,  risultato_crafting.x + 16, risultato_crafting.y + 16, Color(255,255,255,255));
    }
    else
        player.oggetto_risultato_crafting = 0;

    in.close();
}

bool gestione_inventario()
{
    bool valore_ritorno = bottone_premuto();

    if(valore_ritorno)
    {
        SDL_ShowCursor(SDL_ENABLE);
        disegna_inventario();

        cursore.x = -1;
        cursore.y = -1;

        for(int i = 0; i < HEIGHT_INVENTORY; i++)
        {
            int esci = false;
            for(int j = 0; j < WIDTH_INVENTORY; j++)
            {
                if(controllo_collisione(get_mouse_x(), get_mouse_y(), 0, 0, blocchi_inventario[i][j].x, blocchi_inventario[i][j].y, 32, 32))
                {
                    cursore.x = i%9;
                    cursore.y = i/9;

                    esci = true;

                    tasto_sinistro_inventario(i, j);
                    tasto_destro_inventario(i, j);

                    draw_filled_rect(blocchi_inventario[i][j].x, blocchi_inventario[i][j].y, 32, 32, Color(255,255,255,125));

                    break;
                }
            }

            if(esci == true)
                break;
        }

        for(int i = 0; i < 2; i++)
        {
            int esci = false;
            for(int j = 0; j < 2; j++)
            {
                if(controllo_collisione(get_mouse_x(), get_mouse_y(), 0, 0, crafting_inventario[i][j].x, crafting_inventario[i][j].y, 32, 32))
                {
                    cursore.x = i%2;
                    cursore.y = i/2;

                    esci = true;

                    tasto_sinistro_crafting(i, j);
                    tasto_destro_crafting(i, j);

                    draw_filled_rect(crafting_inventario[i][j].x, crafting_inventario[i][j].y, 32, 32, Color(255,255,255,125));

                    break;
                }
            }

            if(esci == true)
                break;
        }

        for(int i = 0; i < HEIGHT_INVENTORY; i++)
        {
            for(int j = 0; j < WIDTH_INVENTORY; j++)
            {
                if(player.inventario[i][j] != 0)
                {
                    draw_image(blocchi[player.inventario[i][j]].texture, blocchi_inventario[i][j].x + 6, blocchi_inventario[i][j].y + 6, 20,20, 255);
                    draw_filled_rect(blocchi_inventario[i][j].x + 5, blocchi_inventario[i][j].y + 5, 22, 22, Color(0,0,0,50));

                    draw_rect(blocchi_inventario[i][j].x + 5, blocchi_inventario[i][j].y + 5, 22,22, Color(0,0,0,255));

                    string quantita = int_to_string(player.inventario_quantita[i][j]);
                    disegna_testo("font/Minecraftia-Regular.ttf", 13, quantita,  blocchi_inventario[i][j].x + 16, blocchi_inventario[i][j].y + 16, Color(255,255,255,255));

                }
            }
        }


        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < 2; j++)
            {
                if(player.crafting[i][j] != 0)
                {
                    draw_image(blocchi[player.crafting[i][j]].texture, crafting_inventario[i][j].x + 6, crafting_inventario[i][j].y + 6, 20,20, 255);
                    draw_filled_rect(crafting_inventario[i][j].x + 5, crafting_inventario[i][j].y + 5, 22, 22, Color(0,0,0,50));

                    draw_rect(crafting_inventario[i][j].x + 5, crafting_inventario[i][j].y + 5, 22,22, Color(0,0,0,255));

                    string quantita = int_to_string(player.crafting_quantita[i][j]);
                    disegna_testo("font/Minecraftia-Regular.ttf", 13, quantita,  crafting_inventario[i][j].x + 16, crafting_inventario[i][j].y + 16, Color(255,255,255,255));

                }
            }
        }

        if(controllo_collisione(get_mouse_x(), get_mouse_y(), 0, 0, risultato_crafting.x, risultato_crafting.y, 32, 32))
        {
            if((mouse_left_button_pressed() || mouse_right_button_pressed()) && cursore.type == 0)
            {
                cursore.type = player.oggetto_risultato_crafting;
                cursore.quantita = player.quantita_risultato_crafting;

                for(int i = 0; i < 2; i++)
                {
                    for(int j = 0; j < 2; j++)
                    {
                        if(player.crafting[i][j] != 0 && player.crafting_quantita[i][j] == 1)
                        {
                            player.crafting[i][j] = 0;
                            player.crafting_quantita[i][j] = 0;
                        }
                        else if(player.crafting[i][j] != 0 && player.crafting_quantita[i][j] > 1)
                        {
                            player.crafting_quantita[i][j]--;
                        }
                    }
                }

                player.oggetto_risultato_crafting = 0;
                player.quantita_risultato_crafting = 0;
            }
            else if((mouse_left_button_pressed() || mouse_right_button_pressed()) && (cursore.type != 0 && cursore.quantita + player.quantita_risultato_crafting <= 64))
            {
                cursore.quantita += player.quantita_risultato_crafting;

                for(int i = 0; i < 2; i++)
                {
                    for(int j = 0; j < 2; j++)
                    {
                        if(player.crafting[i][j] != 0 && player.crafting_quantita[i][j] == 1)
                        {
                            player.crafting[i][j] = 0;
                            player.crafting_quantita[i][j] = 0;
                        }
                        else if(player.crafting[i][j] != 0 && player.crafting_quantita[i][j] > 1)
                        {
                            player.crafting_quantita[i][j]--;
                        }
                    }
                }

                player.oggetto_risultato_crafting = 0;
                player.quantita_risultato_crafting = 0;
            }

            draw_filled_rect(risultato_crafting.x, risultato_crafting.y, 32, 32, Color(255,255,255,125));
        }

        controllo_crafting();


        if(cursore.type != 0)
        {
            draw_image(blocchi[cursore.type].texture, get_mouse_x()-11, get_mouse_y()-11, 22, 22, 255);
            draw_rect(get_mouse_x()-12, get_mouse_y()-12, 24, 24, Color(0,0,0,255));

            string quantita = int_to_string(cursore.quantita);
            disegna_testo("font/Minecraftia-Regular.ttf", 13, quantita, get_mouse_x()-11+16, get_mouse_y()-11+16, Color(255,255,255,255));
        }
    }
    else
        SDL_ShowCursor(SDL_DISABLE);

    return valore_ritorno;
}

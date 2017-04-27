Blocchi_Inventario crafting_table[3][3] =
{
    {
        {WIDTH_WINDOW/2 - 176 + 30*2, HEIGHT_WINDOW/2 - 166 + 17*2},
        {WIDTH_WINDOW/2 - 176 + 48*2, HEIGHT_WINDOW/2 - 166 + 17*2},
        {WIDTH_WINDOW/2 - 176 + 66*2, HEIGHT_WINDOW/2 - 166 + 17*2}
    },
    {
        {WIDTH_WINDOW/2 - 176 + 30*2, HEIGHT_WINDOW/2 - 166 + 35*2},
        {WIDTH_WINDOW/2 - 176 + 48*2, HEIGHT_WINDOW/2 - 166 + 35*2},
        {WIDTH_WINDOW/2 - 176 + 66*2, HEIGHT_WINDOW/2 - 166 + 35*2}
    },
    {
        {WIDTH_WINDOW/2 - 176 + 30*2, HEIGHT_WINDOW/2 - 166 + 53*2},
        {WIDTH_WINDOW/2 - 176 + 48*2, HEIGHT_WINDOW/2 - 166 + 53*2},
        {WIDTH_WINDOW/2 - 176 + 66*2, HEIGHT_WINDOW/2 - 166 + 53*2}
    },
};

Blocchi_Inventario risultato_crafting_table = {WIDTH_WINDOW/2 - 176 + 120*2, HEIGHT_WINDOW/2 - 166 + 31*2};

void disegna_crafting_table()
{
    draw_filled_rect(0,0,WIDTH_WINDOW, HEIGHT_WINDOW, Color(0,0,0,125));

    draw_image("image/crafting_table_gui.png", WIDTH_WINDOW/2 - 176, HEIGHT_WINDOW/2 - 166, 176*2, 166*2, 255);
}

void tasto_sinistro_crafting_table(int i, int j)
{
    static int tasto_sinistro_crafting_table_ = 0;

    if(mouse_left_button_pressed() && tasto_sinistro_crafting_table_ != 1)
    {
        tasto_sinistro_crafting_table_  = 1;

        if(cursore.type == 0)
        {
            cursore.type = player.crafting_table[i][j];
            cursore.quantita = player.crafting_table_quantita[i][j];
            player.crafting_table[i][j] = 0;
            player.crafting_table_quantita[i][j] = 0;
        }
        else
        {
            if(player.crafting_table[i][j] == 0)
            {
                player.crafting_table[i][j] = cursore.type;
                player.crafting_table_quantita[i][j] = cursore.quantita;
                cursore.type = 0;
                cursore.quantita = 0;
            }
            else if(player.crafting_table[i][j] == cursore.type)
            {
                player.crafting_table_quantita[i][j] += cursore.quantita;

                if(player.crafting_table_quantita[i][j] > 64)
                {
                    cursore.quantita = player.crafting_table_quantita[i][j] - 64;
                    player.crafting_table_quantita[i][j] = 64;
                }
                else
                {
                    cursore.type = 0;
                    cursore.quantita = 0;
                }
            }
            else
            {
                swap(player.crafting_table[i][j], cursore.type);
                swap(player.crafting_table_quantita[i][j], cursore.quantita);
            }
        }
    }

    if(!mouse_left_button_pressed() && tasto_sinistro_crafting_table_  == 1)
    {
        tasto_sinistro_crafting_table_ = 0;
    }
}

void tasto_destro_crafting_table(int i, int j)
{
    static int tasto_destro_crafting_table_ = 0;

    if(mouse_right_button_pressed() && tasto_destro_crafting_table_ != 1)
    {
        tasto_destro_crafting_table_  = 1;

        if(player.crafting_table[i][j] == 0 && cursore.type != 0)
        {
            cursore.quantita--;
            player.crafting_table[i][j] = cursore.type;
            player.crafting_table_quantita[i][j]++;

            if(cursore.quantita == 0)
                cursore.type = 0;
        }
        else if(player.crafting_table[i][j] == cursore.type && cursore.type != 0 && player.crafting_table_quantita[i][j] < 64)
        {
            cursore.quantita--;
            player.crafting_table_quantita[i][j]++;

            if(cursore.quantita == 0)
                cursore.type = 0;
        }
        else if(player.crafting_table[i][j] != 0 && cursore.type != 0)
        {
            swap(player.crafting_table[i][j], cursore.type);
            swap(player.crafting_table_quantita[i][j], cursore.quantita);
        }
    }

    if(!mouse_right_button_pressed() && tasto_destro_crafting_table_  == 1)
    {
        tasto_destro_crafting_table_ = 0;
    }
}

void controllo_crafting_table()
{
    string file = "crafting/";
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            file += int_to_string(player.crafting_table[i][j]);

    file += ".save";

    ifstream in(file);

    if(in != NULL)
    {
        int valore, quantita;
        in >> valore >> quantita;

        player.oggetto_risultato_crafting_table = valore;
        player.quantita_risultato_crafting_table = quantita;

        draw_image(blocchi[player.oggetto_risultato_crafting_table].texture, risultato_crafting_table.x + 6, risultato_crafting_table.y + 6, 20,20, 255);
        draw_filled_rect(risultato_crafting_table.x + 5, risultato_crafting_table.y + 5, 22, 22, Color(0,0,0,50));

        draw_rect(risultato_crafting_table.x + 5, risultato_crafting_table.y + 5, 22,22, Color(0,0,0,255));

        string quantita_crafting = int_to_string(player.quantita_risultato_crafting_table);
        disegna_testo("font/Minecraftia-Regular.ttf", 13, quantita_crafting,  risultato_crafting_table.x + 16, risultato_crafting_table.y + 16, Color(255,255,255,255));
    }
    else
        player.oggetto_risultato_crafting_table = 0;

    in.close();
}

bool gestione_crafting_table()
{
    static int valore_ritorno_crafting = false;

    if(valore_ritorno_crafting)
    {
        SDL_ShowCursor(SDL_ENABLE);
        disegna_crafting_table();

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


        for(int i = 0; i < 3; i++)
        {
            int esci = false;
            for(int j = 0; j < 3; j++)
            {
                if(controllo_collisione(get_mouse_x(), get_mouse_y(), 0, 0, crafting_table[i][j].x, crafting_table[i][j].y, 32, 32))
                {
                    cursore.x = i%2;
                    cursore.y = i/2;

                    esci = true;

                    tasto_sinistro_crafting_table(i, j);
                    tasto_destro_crafting_table(i, j);

                    draw_filled_rect(crafting_table[i][j].x, crafting_table[i][j].y, 32, 32, Color(255,255,255,125));

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

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(player.crafting_table[i][j] != 0)
                {
                    draw_image(blocchi[player.crafting_table[i][j]].texture, crafting_table[i][j].x + 6, crafting_table[i][j].y + 6, 20,20, 255);
                    draw_filled_rect(crafting_table[i][j].x + 5, crafting_table[i][j].y + 5, 22, 22, Color(0,0,0,50));

                    draw_rect(crafting_table[i][j].x + 5, crafting_table[i][j].y + 5, 22,22, Color(0,0,0,255));

                    string quantita = int_to_string(player.crafting_table_quantita[i][j]);
                    disegna_testo("font/Minecraftia-Regular.ttf", 13, quantita,  crafting_table[i][j].x + 16, crafting_table[i][j].y + 16, Color(255,255,255,255));

                }
            }
        }

        if(controllo_collisione(get_mouse_x(), get_mouse_y(), 0, 0, risultato_crafting_table.x, risultato_crafting_table.y, 32, 32))
        {
            if((mouse_left_button_pressed() || mouse_right_button_pressed()) && cursore.type == 0)
            {
                cursore.type = player.oggetto_risultato_crafting_table;
                cursore.quantita = player.quantita_risultato_crafting_table;

                for(int i = 0; i < 3; i++)
                {
                    for(int j = 0; j < 3; j++)
                    {
                        if(player.crafting_table[i][j] != 0 && player.crafting_table_quantita[i][j] == 1)
                        {
                            player.crafting_table[i][j] = 0;
                            player.crafting_table_quantita[i][j] = 0;
                        }
                        else if(player.crafting_table[i][j] != 0 && player.crafting_table_quantita[i][j] > 1)
                        {
                            player.crafting_table_quantita[i][j]--;
                        }
                    }
                }

                player.oggetto_risultato_crafting_table = 0;
                player.quantita_risultato_crafting_table = 0;
            }
            else if((mouse_left_button_pressed() || mouse_right_button_pressed()) && (cursore.type != 0 && cursore.quantita + player.quantita_risultato_crafting_table <= 64))
            {
                cursore.quantita += player.quantita_risultato_crafting_table;

                for(int i = 0; i < 3; i++)
                {
                    for(int j = 0; j < 3; j++)
                    {
                        if(player.crafting_table[i][j] != 0 && player.crafting_table_quantita[i][j] == 1)
                        {
                            player.crafting_table[i][j] = 0;
                            player.crafting_table_quantita[i][j] = 0;
                        }
                        else if(player.crafting_table[i][j] != 0 && player.crafting_table_quantita[i][j] > 1)
                        {
                            player.crafting_table_quantita[i][j]--;
                        }
                    }
                }

                player.oggetto_risultato_crafting_table = 0;
                player.quantita_risultato_crafting_table = 0;
            }

            draw_filled_rect(risultato_crafting_table.x, risultato_crafting_table.y, 32, 32, Color(255,255,255,125));
        }

        controllo_crafting_table();

        if(cursore.type != 0)
        {
            draw_image(blocchi[cursore.type].texture, get_mouse_x()-11, get_mouse_y()-11, 22, 22, 255);
            draw_rect(get_mouse_x()-12, get_mouse_y()-12, 24, 24, Color(0,0,0,255));

            string quantita = int_to_string(cursore.quantita);
            disegna_testo("font/Minecraftia-Regular.ttf", 13, quantita, get_mouse_x()-11+16, get_mouse_y()-11+16, Color(255,255,255,255));
        }

        if(is_pressed(VSGL_E))
        {
            valore_ritorno_crafting = false;
            flag_controllo_tasto = 1;
        }
    }
    else
    {
        SDL_ShowCursor(SDL_DISABLE);

        if(mouse_right_button_pressed())
        {
            for(int i = 0; i < HEIGHT_CHUNK; i++)
            {
                for(int j = 0; j < WIDTH_CHUNK*3; j++)
                    if(controllo_collisione(get_mouse_x(), get_mouse_y(), 0, 0, j*WIDTH_BLOCK + coeff_movimento.x,  i*HEIGHT_BLOCK + coeff_movimento.y, WIDTH_BLOCK, HEIGHT_BLOCK) && mappa.mappa[i][j] == 8)
                    {
                        valore_ritorno_crafting = true;
                        break;
                    }
                if(valore_ritorno_crafting == true)
                    break;
            }
        }

    }
    return valore_ritorno_crafting;
}

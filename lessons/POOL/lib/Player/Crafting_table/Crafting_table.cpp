// POSIZIONI DELLA CRAFTING TABLE NELLA FINESTRA DI GIOCO
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

// POSIZIONE DEL RISULTATO DEL CRAFTING NELLA CRAFTING TABLE
Blocchi_Inventario risultato_crafting_table = {WIDTH_WINDOW/2 - 176 + 124*2, HEIGHT_WINDOW/2 - 166 + 35*2};

// FUNZIONE CHE DISEGNA LA CRAFTING TABLE
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

        if(cursore.blocco.blocco.id == 0)
        {
            cursore.blocco.blocco = player.crafting_table[i][j].blocco;
            cursore.blocco.quantita = player.crafting_table[i][j].quantita;
            player.crafting_table[i][j].blocco = blocchi[0];
            player.crafting_table[i][j].quantita = 0;
        }
        else
        {
            if(player.crafting_table[i][j].blocco.id == 0)
            {
                player.crafting_table[i][j].blocco = cursore.blocco.blocco;
                player.crafting_table[i][j].quantita = cursore.blocco.quantita;
                cursore.blocco.blocco = blocchi[0];
                cursore.blocco.quantita = 0;
            }
            else if(player.crafting_table[i][j].blocco.id == cursore.blocco.blocco.id)
            {
                player.crafting_table[i][j].quantita += cursore.blocco.quantita;

                if(player.crafting_table[i][j].quantita > player.crafting_table[i][j].blocco.massima_stoccabilita)
                {
                    cursore.blocco.quantita = player.crafting_table[i][j].quantita - player.crafting_table[i][j].blocco.massima_stoccabilita;
                    player.crafting_table[i][j].quantita = player.crafting_table[i][j].blocco.massima_stoccabilita;
                }
                else
                {
                    cursore.blocco.blocco = blocchi[0];
                    cursore.blocco.quantita = 0;
                }
            }
            else
            {
                swap(player.crafting_table[i][j].blocco, cursore.blocco.blocco);
                swap(player.crafting_table[i][j].quantita, cursore.blocco.quantita);
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

        if(player.crafting_table[i][j].blocco.id == 0 && cursore.blocco.blocco.id != 0)
        {
            cursore.blocco.quantita--;
            player.crafting_table[i][j].blocco = cursore.blocco.blocco;
            player.crafting_table[i][j].quantita++;

            if(cursore.blocco.quantita == 0)
                cursore.blocco.blocco = blocchi[0];
        }
        else if(player.crafting_table[i][j].blocco.id == cursore.blocco.blocco.id && cursore.blocco.blocco.id != 0 && player.crafting_table[i][j].quantita < player.crafting_table[i][j].blocco.massima_stoccabilita)
        {
            cursore.blocco.quantita--;
            player.crafting_table[i][j].quantita++;

            if(cursore.blocco.quantita == 0)
                cursore.blocco.blocco = blocchi[0];
        }
        else if(player.crafting_table[i][j].blocco.id != 0 && cursore.blocco.blocco.id != 0)
        {
            swap(player.crafting_table[i][j].blocco, cursore.blocco.blocco);
            swap(player.crafting_table[i][j].quantita, cursore.blocco.quantita);
        }
    }

    if(!mouse_right_button_pressed() && tasto_destro_crafting_table_  == 1)
    {
        tasto_destro_crafting_table_ = 0;
    }
}

void controllo_crafting_table()
{
    string file;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            file += int_to_string(player.crafting_table[i][j].blocco.id);

    // SE IL FILE ESISTE ALLORA PRELEVO IL TIPO DI BLOCCO CHE MI VIENE RESTITUITO
    // E LA SUA QUANTIA'
    if(crafting[file].first != NULL)
    {
        int valore, quantita;
        valore = crafting[file].first;
        quantita = crafting[file].second;

        player.oggetto_risultato_crafting_table.blocco = blocchi[valore];
        player.oggetto_risultato_crafting_table.quantita = quantita;

        draw_image("item/" + player.oggetto_risultato_crafting_table.blocco.texture, risultato_crafting_table.x, risultato_crafting_table.y, 32,32, 255);

        if(player.oggetto_risultato_crafting_table.quantita > 1)
        {
            string quantita_crafting;
            if(player.oggetto_risultato_crafting.quantita < 10)
                quantita_crafting = "  ";

            quantita_crafting += int_to_string(player.oggetto_risultato_crafting_table.quantita);
            disegna_testo("font/Minecraftia-Regular.ttf", 15, quantita_crafting,  risultato_crafting_table.x + 14, risultato_crafting_table.y + 14, Color(255,255,255,255));
        }
    }
    else
    {
        player.oggetto_risultato_crafting_table.blocco = blocchi[0];
        player.oggetto_risultato_crafting_table.quantita = 0;
    }
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

                    tasto_sinistro_inventario(player.inventario[i][j]);
                    tasto_destro_inventario(player.inventario[i][j]);

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
                if(player.inventario[i][j].blocco.id != 0)
                {
                    disegna_blocco_inventario(player.inventario[i][j].blocco.id, player.inventario[i][j].quantita, blocchi_inventario[i][j], 32, 32);

                    if(player.inventario[i][j].blocco.strumento == true && player.inventario[i][j].blocco.durabilita < blocchi[player.inventario[i][j].blocco.id].durabilita)
                    {
                        float massimo = blocchi[player.inventario[i][j].blocco.id].durabilita;
                        float attuale = player.inventario[i][j].blocco.durabilita;

                        float rosso = 255 - 255*(attuale/massimo);
                        float verde = 255*(attuale/massimo);

                        draw_filled_rect(blocchi_inventario[i][j].x + 4, blocchi_inventario[i][j].y + 26, 26, 4, Color(0,0,0,255));
                        draw_filled_rect(blocchi_inventario[i][j].x + 4, blocchi_inventario[i][j].y + 26, 26.0*(player.inventario[i][j].blocco.durabilita/((float)blocchi[player.inventario[i][j].blocco.id].durabilita)), 2, Color(rosso,verde,0,255));
                    }
                }
            }
        }

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(player.crafting_table[i][j].blocco.id != 0)
                {
                    disegna_blocco_inventario(player.crafting_table[i][j].blocco.id, player.crafting_table[i][j].quantita, crafting_table[i][j], 32, 32);

                    if(player.crafting_table[i][j].blocco.strumento == true && player.crafting_table[i][j].blocco.durabilita < blocchi[player.crafting_table[i][j].blocco.id].durabilita)
                    {
                        float massimo = blocchi[player.crafting_table[i][j].blocco.id].durabilita;
                        float attuale = player.crafting_table[i][j].blocco.durabilita;

                        float rosso = 255 - 255*(attuale/massimo);
                        float verde = 255*(attuale/massimo);

                        draw_filled_rect(crafting_table[i][j].x + 4, crafting_table[i][j].y + 26, 26, 4, Color(0,0,0,255));
                        draw_filled_rect(crafting_table[i][j].x + 4, crafting_table[i][j].y + 26, 26.0*(player.crafting_table[i][j].blocco.durabilita/((float)blocchi[player.crafting_table[i][j].blocco.id].durabilita)), 2, Color(rosso,verde,0,255));
                    }
                }
            }
        }

        if(controllo_collisione(get_mouse_x(), get_mouse_y(), 0, 0, risultato_crafting_table.x, risultato_crafting_table.y, 32, 32))
        {
            if((controllo_tasto_sinistro_premuto() == true || controllo_tasto_destro_premuto() == true))
            {
                if(cursore.blocco.blocco.id == 0 && player.oggetto_risultato_crafting_table.blocco.id != 0)
                {
                    cursore.blocco = player.oggetto_risultato_crafting_table;

                    for(int i = 0; i < 3; i++)
                    {
                        for(int j = 0; j < 3; j++)
                        {
                            if(player.crafting_table[i][j].blocco.id != 0 && player.crafting_table[i][j].quantita == 1)
                            {
                                player.crafting_table[i][j].blocco = blocchi[0];
                                player.crafting_table[i][j].quantita = 0;
                            }
                            else if(player.crafting_table[i][j].blocco.id != 0 && player.crafting_table[i][j].quantita > 1)
                            {
                                player.crafting_table[i][j].quantita--;
                            }
                        }
                    }

                    player.oggetto_risultato_crafting_table.blocco = blocchi[0];
                    player.oggetto_risultato_crafting_table.quantita = 0;
                }
                else if((cursore.blocco.blocco.id != 0 && player.oggetto_risultato_crafting_table.blocco.id != 0 && cursore.blocco.quantita + player.oggetto_risultato_crafting_table.quantita <= cursore.blocco.blocco.massima_stoccabilita))
                {
                    cursore.blocco.quantita += player.oggetto_risultato_crafting_table.quantita;

                    for(int i = 0; i < 3; i++)
                    {
                        for(int j = 0; j < 3; j++)
                        {
                            if(player.crafting_table[i][j].blocco.id != 0 && player.crafting_table[i][j].quantita == 1)
                            {
                                player.crafting_table[i][j].blocco = blocchi[0];
                                player.crafting_table[i][j].quantita = 0;
                            }
                            else if(player.crafting_table[i][j].blocco.id != 0 && player.crafting_table[i][j].quantita > 1)
                            {
                                player.crafting_table[i][j].quantita--;
                            }
                        }
                    }

                    player.oggetto_risultato_crafting_table.blocco = blocchi[0];
                    player.oggetto_risultato_crafting_table.quantita = 0;
                }
            }

            draw_filled_rect(risultato_crafting_table.x, risultato_crafting_table.y, 32, 32, Color(255,255,255,125));
        }

        controllo_crafting_table();

        if(cursore.blocco.blocco.id != 0)
        {
            draw_image("item/" + cursore.blocco.blocco.texture, get_mouse_x()-16, get_mouse_y()-16, 32, 32, 255);

            if(cursore.blocco.blocco.strumento == true && cursore.blocco.blocco.durabilita < blocchi[cursore.blocco.blocco.id].durabilita)
            {
                float massimo = blocchi[cursore.blocco.blocco.id].durabilita;
                float attuale = cursore.blocco.blocco.durabilita;

                float rosso = 255 - 255*(attuale/massimo);
                float verde = 255*(attuale/massimo);

                draw_filled_rect(get_mouse_x() - 16 + 4, get_mouse_y()-16 + 26, 26, 4, Color(0,0,0,255));
                draw_filled_rect(get_mouse_x() - 16 + 4, get_mouse_y()-16 + 26, 26.0*(cursore.blocco.blocco.durabilita/((float)blocchi[cursore.blocco.blocco.id].durabilita)), 2, Color(rosso,verde,0,255));
            }

            if(cursore.blocco.quantita > 1)
            {
                string quantita;

                if(cursore.blocco.quantita < 10)
                    quantita = "  ";

                quantita += int_to_string(cursore.blocco.quantita);
                disegna_testo("font/Minecraftia-Regular.ttf", 15, quantita, get_mouse_x()-16+14, get_mouse_y()-16+14, Color(255,255,255,255));
            }
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
            if(mappa.mappa[cursore.y_blocco][cursore.x_blocco] == CRAFTING_TABLE)
                valore_ritorno_crafting = true;
        }

    }

    return valore_ritorno_crafting;
}

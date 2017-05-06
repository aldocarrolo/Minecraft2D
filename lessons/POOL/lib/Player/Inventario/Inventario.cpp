// BLOCCHI CHE INDICANO LE VARIE POSIZIONI DELL'INVENTARIO
// NELLA FINESTRA DI GIOCO
Blocchi_Inventario blocchi_inventario[HEIGHT_INVENTORY + 3][WIDTH_INVENTORY] =
{
    // BLOCCHI INVENTARIO
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

// VETTORE CHE INDICA I VARI LBOCCHI DEL CRAFTING
// IL CRAFTING DELL'INVENTARIO E' UN 2X2
Blocchi_Inventario crafting_inventario[2][2] =
{
    {{WIDTH_WINDOW/2 - 176 + 98*2, HEIGHT_WINDOW/2 - 166 + 18*2}, {WIDTH_WINDOW/2 - 176 + 116*2, HEIGHT_WINDOW/2 - 166 + 18*2}},
    {{WIDTH_WINDOW/2 - 176 + 98*2, HEIGHT_WINDOW/2 - 166 + 36*2}, {WIDTH_WINDOW/2 - 176 + 116*2, HEIGHT_WINDOW/2 - 166 + 36*2}}
};

// BLOCCO CONTENENTE LA POSIZIONE DEL RISULTATO DEL CRAFTING NELL'INVENTARIO
Blocchi_Inventario risultato_crafting = {WIDTH_WINDOW/2 - 176 + 154*2, HEIGHT_WINDOW/2 - 166 + 28*2};

// FUNZIONE CHE PERMETTE IL DISEGNO DELL'INVENTARIO
void disegna_inventario()
{
    draw_filled_rect(0,0,WIDTH_WINDOW, HEIGHT_WINDOW, Color(0,0,0,125));    // RETTANGOLO NERO CON TRASPARENZA A 125

    draw_image("image/inventory.png", WIDTH_WINDOW/2 - 176, HEIGHT_WINDOW/2 - 166, 176*2, 166*2, 255);  // DISEGNO DELL'IMMAGINE
}

// FUNZIONE CHE DISEGNA UN BLOCCO ALLINTERNO DELL'INVENTARIO
void disegna_blocco_inventario(int posizione, int quantita, Blocchi_Inventario coordinate, int width, int height)
{
    // DISEGNO IL BLOCCO
    draw_image("item/" + blocchi[posizione].texture, coordinate.x, coordinate.y, width,height, 255);

    // E INFINE IL NUMERO DI QUANTITA' DEL BLOCCO
    if(quantita > 1)
    {
        string numero;
        if(quantita < 10)
            numero = "  ";
         numero += int_to_string(quantita);
        disegna_testo("font/Minecraftia-Regular.ttf", 15, numero,  coordinate.x + 14, coordinate.y + 14, Color(255,255,255,255));
    }
}

// FUNZIONE CHE PERMETTE DI RILEVARE UNA SOLA VOLTA LA PRESSIONE DI UN TASTO
// QUESTA FUNZIONE SERVIRA' PER VEDERE SE IL GIOCATORE PREME LA E PER APRIRE L'INVENTARIO
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

// FUNZIONE PER IL "TRASPORTO" O "INSERIMENTO" DI UN BLOCCO ALL'INTERNO DI UN POSTO
// NELL'INVENTARIO
void tasto_sinistro_inventario(Inventario &selezione)
{
    static int tasto_sinistro_inventaro = 0;

    if(mouse_left_button_pressed() && tasto_sinistro_inventaro != 1) // SE PREMO TASTO SINISTRO
    {
        tasto_sinistro_inventaro  = 1;

        // SE IL CURSORE E' VUOTO ALLORA INSERISCO IL BLOCCO NEL CURSORE
        if(cursore.blocco.blocco.id == 0)
        {
            cursore.blocco.blocco = selezione.blocco;
            cursore.blocco.quantita = selezione.quantita;
            selezione.blocco = blocchi[0];
            selezione.quantita = 0;
        }
        else
        {
            // SE IL CURSORE E' VUOTO E IL BLOCCO NELL'INVENTARIO E' VUOTO
            // ALLORA INSERISCO IL BLOCCO DAL CURSORE AL POSTO
            if(selezione.blocco.id == 0)
            {
                selezione.blocco = cursore.blocco.blocco;
                selezione.quantita = cursore.blocco.quantita;
                cursore.blocco.blocco = blocchi[0];
                cursore.blocco.quantita = 0;
            }
            // ALTRIMENTI SE IL BLOCCO NEL CURSORE E' UGUALE AL BLOCCO NEL POSTO DELL'INVENTARIO
            // ALLORA LO AGGIUNGO AI BLOCCHI DELL'INVENTARIO
            else if(selezione.blocco.id == cursore.blocco.blocco.id)
            {
                // SE LA SELEZIONE E' MAGGIORE RISPETTO AL VALORE MASSIMO DI STOCCABILITA'
                if(selezione.quantita + cursore.blocco.quantita > blocchi[selezione.blocco.id].massima_stoccabilita)
                {
                    // ALLORA SETTO COME LA DIFFERENZA TRA LA QUANTITA E LA MASSIMA STOCCABILITA' IL CURSORE
                    cursore.blocco.quantita = selezione.quantita + cursore.blocco.quantita - blocchi[selezione.blocco.id].massima_stoccabilita;
                    // E SETTO LA QUANTITA' DELLA SELEZIONE COME IL VALORE MASSIMO DI STOCCABILITA'
                    selezione.quantita = blocchi[selezione.blocco.id].massima_stoccabilita;
                }
                else
                {
                    // ALTRIMENTO SETTO SOMMO ALLA QUANITTA' DELLA SELEZIONE LA QUANTITA' DEL CURSORE E...
                    selezione.quantita += cursore.blocco.quantita;

                    // ... SETTO COME BLOCCO VUOTO IL CURSORE
                    cursore.blocco.blocco = blocchi[0];
                    cursore.blocco.quantita = 0;
                }
            }
            // ALTRIMENTI SCAMBIO IL BLOCCO DEL CURSORE CON QUELLO DELL'INVENTARIO
            else
            {
                swap(selezione.blocco, cursore.blocco.blocco);
                swap(selezione.quantita, cursore.blocco.quantita);
            }
        }
    }

    if(!mouse_left_button_pressed() && tasto_sinistro_inventaro  == 1)
        tasto_sinistro_inventaro = 0;
}

// FUNZIONE CHE PERMETTE DI PREMERE IL TASTO DESTRO PER FAR ESEGUIRE UNO SPECIFICO EVENTO
void tasto_destro_inventario(Inventario &selezione)
{
    static int tasto_destro_inventaro = 0;

    if(mouse_right_button_pressed() && tasto_destro_inventaro != 1)
    {
        tasto_destro_inventaro  = 1;

        // SE IL CURSORE NON E' VUOTOT
        if(cursore.blocco.blocco.id != 0)
        {
            // E LA POSIZIONE NELL'INVENTARIO E' VUOTA
            // ALLORA INSERISCO UN SOLO BLOCCO
            if(selezione.blocco.id == 0)
            {
                selezione.blocco = cursore.blocco.blocco;
                cursore.blocco.quantita--;

                selezione.quantita = 1;

                if(cursore.blocco.quantita == 0)
                    cursore.blocco.blocco = blocchi[0];
            }
            // ALTRIMENTI SE LA QUANTITA E' COMPRESA TRA 0 E 64 ALLORA INSERISCO UN BLOCCO
            else if(cursore.blocco.blocco.id == selezione.blocco.id && selezione.quantita < blocchi[cursore.blocco.blocco.id].massima_stoccabilita && selezione.quantita > 0)
            {
                cursore.blocco.quantita--;
                selezione.quantita = selezione.quantita + 1;

                if(cursore.blocco.quantita == 0)
                    cursore.blocco.blocco = blocchi[0];
            }
            // ALTRIMENTI SE I TIPI DI BLOCCHI SONO DIVERSI SCAMBIO I BLOCCHI
            else if(selezione.blocco.id != 0)
            {
                swap(selezione.blocco, cursore.blocco.blocco);
                swap(selezione.quantita, cursore.blocco.quantita);
            }
        }
    }

    if(!mouse_right_button_pressed() && tasto_destro_inventaro  == 1)
        tasto_destro_inventaro = 0;
}

// FUNZIONE CHE SERVE PER CONTROLLARE SE ESISTE UN CRAFTING
void controllo_crafting()
{
    // MI CREO LA STRINGA CHE SARA' IL NOME DEL FILE
    string file;
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            file += int_to_string(player.crafting[i][j].blocco.id);

    // SE IL FILE ESISTE ALLORA PRELEVO IL TIPO DI BLOCCO CHE MI VIENE RESTITUITO
    // E LA SUA QUANTIA'
    if(crafting[file].first != NULL)
    {
        int valore, quantita;
        valore = crafting[file].first;
        quantita = crafting[file].second;

        player.oggetto_risultato_crafting.blocco = blocchi[valore];
        player.oggetto_risultato_crafting.quantita = quantita;

        disegna_blocco_inventario(player.oggetto_risultato_crafting.blocco.id, player.oggetto_risultato_crafting.quantita, risultato_crafting, 32, 32);
    }
    else
    {
        player.oggetto_risultato_crafting.blocco = blocchi[0];
        player.oggetto_risultato_crafting.quantita = 0;
    }
}

bool gestione_inventario()
{
    bool valore_ritorno = bottone_premuto();

    if(valore_ritorno)
    {
        SDL_ShowCursor(SDL_ENABLE);
        disegna_inventario();

        cursore.x = 0;
        cursore.y = 0;

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

                    tasto_sinistro_inventario(player.crafting[i][j]);
                    tasto_destro_inventario(player.crafting[i][j]);

                    draw_filled_rect(crafting_inventario[i][j].x, crafting_inventario[i][j].y, 32, 32, Color(255,255,255,125));

                    break;
                }
            }

            if(esci == true)
                break;
        }

        // DISEGNO DEI BLOCCHI DELL'INVENTARIO
        for(int i = 0; i < HEIGHT_INVENTORY; i++)
            for(int j = 0; j < WIDTH_INVENTORY; j++)
                if(player.inventario[i][j].blocco.id != 0)
                    disegna_blocco_inventario(player.inventario[i][j].blocco.id, player.inventario[i][j].quantita, blocchi_inventario[i][j], 32, 32);

        // DISEGNO DEI BLOCCHI DELLA CRAFTING DELL'INVENTARIO
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++)
                if(player.crafting[i][j].blocco.id != 0)
                    disegna_blocco_inventario(player.crafting[i][j].blocco.id, player.crafting[i][j].quantita, crafting_inventario[i][j],32, 32);


        controllo_crafting();

        if(controllo_collisione(get_mouse_x(), get_mouse_y(), 0, 0, risultato_crafting.x, risultato_crafting.y, 32, 32))
        {
            if((controllo_tasto_sinistro_premuto() == true || controllo_tasto_destro_premuto() == true))
            {
                if(cursore.blocco.blocco.id == 0 && player.oggetto_risultato_crafting.blocco.id != 0)
                {
                    cursore.blocco.blocco = player.oggetto_risultato_crafting.blocco;
                    cursore.blocco.quantita = player.oggetto_risultato_crafting.quantita;

                    for(int i = 0; i < 2; i++)
                    {
                        for(int j = 0; j < 2; j++)
                        {
                            if(player.crafting[i][j].blocco.id != 0 && player.crafting[i][j].quantita == 1)
                            {
                                player.crafting[i][j].blocco = blocchi[0];
                                player.crafting[i][j].quantita = 0;
                            }
                            else if(player.crafting[i][j].blocco.id != 0 && player.crafting[i][j].quantita > 1)
                            {
                                player.crafting[i][j].quantita--;
                            }
                        }
                    }

                    player.oggetto_risultato_crafting.blocco = blocchi[0];
                    player.oggetto_risultato_crafting.quantita = 0;
                }
                else if(player.oggetto_risultato_crafting.blocco.id != 0 && (cursore.blocco.blocco.id == player.oggetto_risultato_crafting.blocco.id && cursore.blocco.quantita + player.oggetto_risultato_crafting.quantita <= 64))
                {
                    cursore.blocco.quantita += player.oggetto_risultato_crafting.quantita;

                    for(int i = 0; i < 2; i++)
                    {
                        for(int j = 0; j < 2; j++)
                        {
                            if(player.crafting[i][j].blocco.id != 0 && player.crafting[i][j].quantita == 1)
                            {
                                player.crafting[i][j].blocco = blocchi[0];
                                player.crafting[i][j].quantita = 0;
                            }
                            else if(player.crafting[i][j].blocco.id != 0 && player.crafting[i][j].quantita > 1)
                            {
                                player.crafting[i][j].quantita--;
                            }
                        }
                    }

                    player.oggetto_risultato_crafting.blocco = blocchi[0];
                    player.oggetto_risultato_crafting.quantita = 0;
                }
            }

            draw_filled_rect(risultato_crafting.x, risultato_crafting.y, 32, 32, Color(255,255,255,125));
        }

        if(cursore.blocco.blocco.id != 0)
        {
            draw_image("item/" + blocchi[cursore.blocco.blocco.id].texture, get_mouse_x()-16, get_mouse_y()-16, 32, 32, 255);
            //draw_rect(get_mouse_x()-12, get_mouse_y()-12, 24, 24, Color(0,0,0,255));

            if(cursore.blocco.quantita > 1)
            {
                string quantita;
                if(cursore.blocco.quantita < 10)
                    quantita = "  ";

                quantita += int_to_string(cursore.blocco.quantita);
                disegna_testo("font/Minecraftia-Regular.ttf", 15, quantita, get_mouse_x()-16+14, get_mouse_y()-16+14, Color(255,255,255,255));
            }
        }
    }
    else
        SDL_ShowCursor(SDL_DISABLE);

    return valore_ritorno;
}

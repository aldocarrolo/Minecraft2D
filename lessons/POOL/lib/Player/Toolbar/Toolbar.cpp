// FUNZIONE PER IL DISEGNO DELLA SELEZIONE DEL GIOCATORE NELLA TOOLBAR
// PRATICAMENTE DISEGNA IL QUADRATO GRANDE CHE INDICA LA SELEZIONE
void disegna_toolbar_selezione()
{
    draw_image("image/toolbar_selezione.png", WIDTH_WINDOW/2 - 182-2 + player.selezione_toolbar*40, HEIGHT_WINDOW - 22*2-1, 48, 48, 255);
}

// FUNZIONE PER IL DISEGNO DELLA TOOLBAR
void disegna_toolbar()
{
    draw_image("image/toolbar.png", WIDTH_WINDOW/2 - 182, HEIGHT_WINDOW - 22*2, 182*2, 22*2, 255);
}

// FUNZIONE PER IL DISEGNO DEI BLOCCHI CONTENUTI NELLA TOOLBAR
void disegna_blocchi_toolbar()
{
    // QUINDI PER OGNI BLOCCO CONTENUTO NELLA TOOLBAR
    for(int i = 0; i < WIDTH_INVENTORY; i++)
    {
        // CHE SIA DIVERSO DAL BLOCCO VUOTO
        if(player.inventario[TOOLBAR][i].quantita != 0)
        {
            // DISEGNO IL BLOCCO
            draw_image("item/" + blocchi[player.inventario[TOOLBAR][i].blocco.id].texture, WIDTH_WINDOW/2 - 182 + 40*i + 5.5, HEIGHT_WINDOW - 44-1 + 7, 32,32,255);

            if(player.inventario[TOOLBAR][i].quantita > 1)
            {
                // CON IL NUMERO CHE INDICA LA QUANTITA' DEI BLOCCHI CONTENUTI
                string quantita;

                if(player.inventario[TOOLBAR][i].quantita < 10)
                    quantita = "  ";

                quantita += int_to_string(player.inventario[TOOLBAR][i].quantita);

                disegna_testo("font/Minecraftia-Regular.ttf", 15, quantita, WIDTH_WINDOW/2 - 182 + 40*i + 22/2 + 9, HEIGHT_WINDOW - 44-1 + 22/2 + 12, Color(255,255,255,255));
            }
        }
    }
}

// FUNZIONE PER LO SPOSTAMENTO DELLA SELEZIONE
void sposta_selezione()
{
    // QUESTO SPOSTAMENTO PU' AVVENIRE ATTRAVERSO I NUMERO DA 1-9
    if(is_pressed(VSGL_1))
        player.selezione_toolbar = 0;
    else if(is_pressed(VSGL_2))
        player.selezione_toolbar = 1;
    else if(is_pressed(VSGL_3))
        player.selezione_toolbar = 2;
    else if(is_pressed(VSGL_4))
        player.selezione_toolbar = 3;
    else if(is_pressed(VSGL_5))
        player.selezione_toolbar = 4;
    else if(is_pressed(VSGL_6))
        player.selezione_toolbar = 5;
    else if(is_pressed(VSGL_7))
        player.selezione_toolbar = 6;
    else if(is_pressed(VSGL_8))
        player.selezione_toolbar = 7;
    else if(is_pressed(VSGL_9))
        player.selezione_toolbar = 8;

    // O ATTRAVERSO LA ROTELLINA DEL MOUSE
    // LA FUNZIONE get_mouse_wheel_y  PUO' RESTITUIRE 1 SE LA ROTELLINA VIENE SPOSTATA IN AVANTI
    // O -1 SE VIENE SPOSTATA INDIETRO
    player.selezione_toolbar += -get_mouse_wheel_y();

    if(player.selezione_toolbar == -1)
        player.selezione_toolbar = 8;

    if(player.selezione_toolbar == 9)
        player.selezione_toolbar = 0;
}

// FUNZIONE PER LA GESTIONE DELLA TOOLBAR
// VENGONO CHIAMATE LE FUNZIONI APPENA DESCRITTO
void gestione_toolbar()
{
    sposta_selezione();

    disegna_toolbar();

    disegna_toolbar_selezione();

    disegna_blocchi_toolbar();
}

void disegna_toolbar_selezione()
{
    draw_image("image/toolbar_selezione.png", WIDTH_WINDOW/2 - 182-2 + player.selezione_toolbar*40, HEIGHT_WINDOW - 22*2-1, 48, 48, 255);
}

void disegna_toolbar()
{
    draw_image("image/toolbar.png", WIDTH_WINDOW/2 - 182, HEIGHT_WINDOW - 22*2, 182*2, 22*2, 255);
}

void disegna_blocchi_toolbar()
{
    for(int i = 0; i < WIDTH_INVENTORY; i++)
    {
        if(player.inventario_quantita[TOOLBAR][i] != 0)
        {
            draw_image(blocchi[player.inventario[TOOLBAR][i]].texture, WIDTH_WINDOW/2 - 182 + 40*i + 22/2, HEIGHT_WINDOW - 44-1 + 22/2, 22,22,255);

            string quantita = int_to_string(player.inventario_quantita[TOOLBAR][i]);
            disegna_testo("font/Minecraftia-Regular.ttf", 13, quantita, WIDTH_WINDOW/2 - 182 + 40*i + 22/2 + 12, HEIGHT_WINDOW - 44-1 + 22/2 + 12, Color(255,255,255,255));
        }
    }
}

void sposta_selezione()
{
    if(is_pressed(VSGL_1))
        player.selezione_toolbar = 0;
    if(is_pressed(VSGL_2))
        player.selezione_toolbar = 1;
    if(is_pressed(VSGL_3))
        player.selezione_toolbar = 2;
    if(is_pressed(VSGL_4))
        player.selezione_toolbar = 3;
    if(is_pressed(VSGL_5))
        player.selezione_toolbar = 4;
    if(is_pressed(VSGL_6))
        player.selezione_toolbar = 5;
    if(is_pressed(VSGL_7))
        player.selezione_toolbar = 6;
    if(is_pressed(VSGL_8))
        player.selezione_toolbar = 7;
    if(is_pressed(VSGL_9))
        player.selezione_toolbar = 8;
}

void gestione_toolbar()
{
    sposta_selezione();

    disegna_toolbar();

    disegna_toolbar_selezione();

    disegna_blocchi_toolbar();
}

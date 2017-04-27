#include "Inventario/Inventario.h"
#include "Crafting_table/Crafting_table.h"
#include "Toolbar/Toolbar.h"
#include "Drop/Drop.h"

void salto_giocatore(p *player, Coeff_Movimento *coeff_movimento,  int mappa[][MAXWIDTH])
{
    if(player->salto == false)
    {
        bool collisione_salto = false;

        for(int i = player->inizio_finestra_y; i < player->fine_finestra_y; i++)
        {
            for(int j =  player->inizio_finestra_x; j <  player->fine_finestra_x; j++)
            {
                if(blocchi[mappa[i][j]].trasparenza == false)
                {
                    if(controllo_collisione(player->x + 4, player->y, player->width - 8, player->height,
                                    j*WIDTH_BLOCK + coeff_movimento->x, i*HEIGHT_BLOCK + coeff_movimento->y, WIDTH_BLOCK, HEIGHT_BLOCK))
                    {
                        collisione_salto = true;
                        break;
                    }
                }
            }

            if(collisione_salto == true)
                break;
        }

        if(collisione_salto == false)
        {
            player->coeff_salto = -10;
            player->salto = true;
        }
    }

    if(is_pressed(VSGL_SPACE) && player->salto == false)
    {
        player->coeff_salto = 15;
        player->salto = true;
    }

    if(player->salto == true)
    {
        coeff_movimento->y += player->coeff_salto;

        for(int i = player->inizio_finestra_y; i < player->fine_finestra_y; i++)
        {
            bool flag_uscita = false;
            for(int j =  player->inizio_finestra_x; j <  player->fine_finestra_x; j++)
            {
                if(blocchi[mappa[i][j]].trasparenza == false)
                {
                    if(controllo_collisione(player->x + 4, player->y, player->width - 8, 4, j*WIDTH_BLOCK + coeff_movimento->x, i*HEIGHT_BLOCK + coeff_movimento->y, WIDTH_BLOCK, HEIGHT_BLOCK))
                    {
                        coeff_movimento->y += (player->y) - (((i*HEIGHT_BLOCK) + coeff_movimento->y) + WIDTH_BLOCK);
                        player->coeff_salto = 0;
                        flag_uscita = true;
                        break;
                    }
                }
            }

            if(flag_uscita == true)
                break;
        }

        if(player->coeff_salto > -(HEIGHT_BLOCK-5))
            player->coeff_salto -= 2.5;

        for(int i = player->inizio_finestra_y; i < player->fine_finestra_y; i++)
        {
            for(int j =  player->inizio_finestra_x; j <  player->fine_finestra_x; j++)
            {
                if(blocchi[mappa[i][j]].trasparenza == false)
                {
                    if(controllo_collisione(player->x + 4, player->y+player->height - 4, player->width - 8, 4,
                                    j*WIDTH_BLOCK + coeff_movimento->x, i*HEIGHT_BLOCK + coeff_movimento->y, WIDTH_BLOCK, HEIGHT_BLOCK))
                    {
                        coeff_movimento->y += (player->y + player->height) - ((i*HEIGHT_BLOCK) + coeff_movimento->y);
                        player->salto = false;
                        return;
                    }
                }
            }
        }
    }
}

void movimento_giocatore(p *player, Coeff_Movimento *coeff_movimento,  int mappa[][MAXWIDTH])
{
    player->collisione_sinistra = false;
    player->collisione_destra = false;

    for(int i = player->inizio_finestra_y; i < player->fine_finestra_y; i++)
    {
        for(int j =  player->inizio_finestra_x; j < player->fine_finestra_x; j++)
        {
            if(blocchi[mappa[i][j]].trasparenza == false)
            {
                if(controllo_collisione(player->x, player->y + 4, 4, player->height - 8,
                                j*WIDTH_BLOCK + coeff_movimento->x, i*HEIGHT_BLOCK + coeff_movimento->y, WIDTH_BLOCK, HEIGHT_BLOCK))
                {
                    coeff_movimento->x += (player->x) - (j*WIDTH_BLOCK + coeff_movimento->x + WIDTH_BLOCK);
                    player->collisione_sinistra = true;
                    break;
                }
                else if(controllo_collisione(player->x + player->width-4, player->y + 4, 4, player->height - 8,
                                j*WIDTH_BLOCK + coeff_movimento->x, i*HEIGHT_BLOCK + coeff_movimento->y, WIDTH_BLOCK, HEIGHT_BLOCK))
                {

                    coeff_movimento->x += (player->x + player->width) - (j*WIDTH_BLOCK + coeff_movimento->x);
                    player->collisione_destra = true;
                    break;
                }
            }
        }
    }

    if(is_pressed(VSGL_A) && player->collisione_sinistra == false)
        coeff_movimento->x += 5;

    if(is_pressed(VSGL_D) && player->collisione_destra == false)
        coeff_movimento->x -= 5;
}

void distruggere_blocco(int mappa[][MAXWIDTH], int i, int j, int livello)
{
    if((player.distruggere_secondo_livello == true && livello == 1) || (player.distruggere == true && livello == 0))
    {
        if(ms_time() - player.timer_blocco_distrutto >= blocchi[player.tipo_blocco_distrutto].secondi)
        {
            if(player.forza >= blocchi[mappa[i][j]].durezza)
                blocchi_droppati.push_back({j*WIDTH_BLOCK + 15, i*HEIGHT_BLOCK + 15, blocchi[mappa[i][j]].oggetto_droppato});

            mappa[player.y_blocco_distrutto][player.x_blocco_distrutto] = 0;

            if(livello == 0)
                player.distruggere = false;
            else
                player.distruggere_secondo_livello = false;
        }
        else
        {
            string image_animation;

            if(ms_time() - player.timer_blocco_distrutto <= blocchi[player.tipo_blocco_distrutto].secondi/10)
                image_animation = "image/break_animation/break_1.png";
            else if(ms_time() - player.timer_blocco_distrutto <= blocchi[player.tipo_blocco_distrutto].secondi/10*2)
                image_animation = "image/break_animation/break_2.png";
            else if(ms_time() - player.timer_blocco_distrutto <= blocchi[player.tipo_blocco_distrutto].secondi/10*3)
                image_animation = "image/break_animation/break_3.png";
            else if(ms_time() - player.timer_blocco_distrutto <= blocchi[player.tipo_blocco_distrutto].secondi/10*4)
                image_animation = "image/break_animation/break_4.png";
            else if(ms_time() - player.timer_blocco_distrutto <= blocchi[player.tipo_blocco_distrutto].secondi/10*5)
                image_animation = "image/break_animation/break_5.png";
            else if(ms_time() - player.timer_blocco_distrutto <= blocchi[player.tipo_blocco_distrutto].secondi/10*6)
                image_animation = "image/break_animation/break_6.png";
            else if(ms_time() - player.timer_blocco_distrutto <= blocchi[player.tipo_blocco_distrutto].secondi/10*7)
                image_animation = "image/break_animation/break_7.png";
            else if(ms_time() - player.timer_blocco_distrutto <= blocchi[player.tipo_blocco_distrutto].secondi/10*8)
                image_animation = "image/break_animation/break_8.png";
            else if(ms_time() - player.timer_blocco_distrutto <= blocchi[player.tipo_blocco_distrutto].secondi/10*9)
                image_animation = "image/break_animation/break_9.png";
            else if(ms_time() - player.timer_blocco_distrutto <= blocchi[player.tipo_blocco_distrutto].secondi/10*10)
                image_animation = "image/break_animation/break_10.png";

            draw_image(image_animation, player.x_blocco_distrutto*WIDTH_BLOCK + coeff_movimento.x,  player.y_blocco_distrutto*HEIGHT_BLOCK
                        + coeff_movimento.y, WIDTH_BLOCK, HEIGHT_BLOCK, 255);
        }
    }
}

void eliminazione_blocco_secondo_livello()
{
    int mouse_x = get_mouse_x();
    int mouse_y = get_mouse_y();

    for(int i = player.inizio_finestra_y; i < player.fine_finestra_y; i++)
    {
        bool esci = false;
        for(int j =  player.inizio_finestra_x; j <  player.fine_finestra_x; j++)
        {
            if(blocchi[mappa.secondo_livello[i][j]].distruggi == true)
            {
                if(mouse_x >= j*WIDTH_BLOCK + coeff_movimento.x && mouse_x <= j*WIDTH_BLOCK+WIDTH_BLOCK + coeff_movimento.x &&
                   mouse_y >= i*HEIGHT_BLOCK + coeff_movimento.y && mouse_y <= i*HEIGHT_BLOCK+HEIGHT_BLOCK + coeff_movimento.y)
                {
                    esci = true;

                    if(player.distruggere_secondo_livello == false)
                    {
                        player.timer_blocco_distrutto = ms_time();
                        player.x_blocco_distrutto = j;
                        player.y_blocco_distrutto = i;
                        player.tipo_blocco_distrutto = mappa.secondo_livello[i][j];
                        player.distruggere_secondo_livello = true;
                    }
                    else if(player.distruggere_secondo_livello == true && (player.x_blocco_distrutto != j || player.y_blocco_distrutto != i))
                    {
                        player.timer_blocco_distrutto = ms_time();
                        player.x_blocco_distrutto = j;
                        player.y_blocco_distrutto = i;
                        player.tipo_blocco_distrutto = mappa.secondo_livello[i][j];
                        player.distruggere_secondo_livello = true;
                    }

                    return;
                }
            }
        }

        if(esci == true)
            break;
    }
}

void creazione_blocco_secondo_livello()
{
    int mouse_x = get_mouse_x();
    int mouse_y = get_mouse_y();

    for(int i = player.inizio_finestra_y; i < player.fine_finestra_y; i++)
    {
        for(int j =  player.inizio_finestra_x; j < player.fine_finestra_x; j++)
        {
            if(blocchi[mappa.secondo_livello[i][j]].distruggi == false)
            {
                if(player.inventario[TOOLBAR][player.selezione_toolbar] != 0 && mouse_x >= j*WIDTH_BLOCK + coeff_movimento.x && mouse_x <= j*WIDTH_BLOCK+WIDTH_BLOCK + coeff_movimento.x &&
                   mouse_y >= i*HEIGHT_BLOCK + coeff_movimento.y && mouse_y <= i*HEIGHT_BLOCK+HEIGHT_BLOCK + coeff_movimento.y)
                {
                    mappa.secondo_livello[i][j] = player.inventario[TOOLBAR][player.selezione_toolbar];

                    if(player.inventario_quantita[TOOLBAR][player.selezione_toolbar] > 0)
                        player.inventario_quantita[TOOLBAR][player.selezione_toolbar]--;

                    if(player.inventario_quantita[TOOLBAR][player.selezione_toolbar] == 0)
                        player.inventario[TOOLBAR][player.selezione_toolbar] = 0;

                    return;
                }
            }
        }
    }
}

void crea_elimina_blocchi(int mappa[][MAXWIDTH], Coeff_Movimento coeff_movimento)
{
    distruggere_blocco(mappa,player.y_blocco_distrutto,player.x_blocco_distrutto, 0);
    distruggere_blocco(::mappa.secondo_livello,player.y_blocco_distrutto,player.x_blocco_distrutto, 1);

    if(mouse_left_button_pressed())
    {
        if(is_pressed(VSGL_LSHIFT) || is_pressed(VSGL_RSHIFT))
        {
            eliminazione_blocco_secondo_livello();
        }
        else
        {
            int mouse_x = get_mouse_x();
            int mouse_y = get_mouse_y();

            for(int i = player.inizio_finestra_y; i < player.fine_finestra_y; i++)
            {
                bool esci = false;
                for(int j =  player.inizio_finestra_x; j <  player.fine_finestra_x; j++)
                {
                    if(blocchi[mappa[i][j]].distruggi == true)
                    {
                        if(mouse_x >= j*WIDTH_BLOCK + coeff_movimento.x && mouse_x <= j*WIDTH_BLOCK+WIDTH_BLOCK + coeff_movimento.x &&
                           mouse_y >= i*HEIGHT_BLOCK + coeff_movimento.y && mouse_y <= i*HEIGHT_BLOCK+HEIGHT_BLOCK + coeff_movimento.y)
                        {
                            esci = true;

                            if(player.distruggere == false)
                            {
                                player.timer_blocco_distrutto = ms_time();
                                player.x_blocco_distrutto = j;
                                player.y_blocco_distrutto = i;
                                player.tipo_blocco_distrutto = mappa[i][j];
                                player.distruggere = true;
                            }
                            else if(player.distruggere == true && (player.x_blocco_distrutto != j || player.y_blocco_distrutto != i))
                            {
                                player.timer_blocco_distrutto = ms_time();
                                player.x_blocco_distrutto = j;
                                player.y_blocco_distrutto = i;
                                player.tipo_blocco_distrutto = mappa[i][j];
                                player.distruggere = true;
                            }

                            return;
                        }
                    }
                }
                if(esci == true)
                    break;
            }
        }
    }
    else if(mouse_right_button_pressed())
    {
        if(is_pressed(VSGL_LSHIFT) || is_pressed(VSGL_RSHIFT))
        {
            creazione_blocco_secondo_livello();
        }
        else
        {
            int mouse_x = get_mouse_x();
            int mouse_y = get_mouse_y();

            for(int i = player.inizio_finestra_y; i < player.fine_finestra_y; i++)
            {
                for(int j =  player.inizio_finestra_x; j < player.fine_finestra_x; j++)
                {
                    if(blocchi[mappa[i][j]].distruggi == false)
                    {
                        if(player.inventario[TOOLBAR][player.selezione_toolbar] != 0 && mouse_x >= j*WIDTH_BLOCK + coeff_movimento.x && mouse_x <= j*WIDTH_BLOCK+WIDTH_BLOCK + coeff_movimento.x &&
                           mouse_y >= i*HEIGHT_BLOCK + coeff_movimento.y && mouse_y <= i*HEIGHT_BLOCK+HEIGHT_BLOCK + coeff_movimento.y)
                        {
                            mappa[i][j] = player.inventario[TOOLBAR][player.selezione_toolbar];

                            if(player.inventario_quantita[TOOLBAR][player.selezione_toolbar] > 0)
                                player.inventario_quantita[TOOLBAR][player.selezione_toolbar]--;

                            if(player.inventario_quantita[TOOLBAR][player.selezione_toolbar] == 0)
                                player.inventario[TOOLBAR][player.selezione_toolbar] = 0;

                            return;
                        }
                    }
                }
            }
        }
    }
    else
        player.distruggere = false;
}

void player_cursor(int mappa[][MAXWIDTH], Coeff_Movimento coeff_movimento)
{
    int mouse_x = get_mouse_x();
    int mouse_y = get_mouse_y();

    for(int i = 0; i < MAXHEIGHT; i++)
    {
        for(int j = 0; j < MAXWIDTH; j++)
            if(controllo_collisione(mouse_x, mouse_y, 0, 0, j*WIDTH_BLOCK + coeff_movimento.x, i*HEIGHT_BLOCK + coeff_movimento.y, WIDTH_BLOCK, HEIGHT_BLOCK))
            {
                draw_rect(j*WIDTH_BLOCK + coeff_movimento.x, i*HEIGHT_BLOCK + coeff_movimento.y, WIDTH_BLOCK, HEIGHT_BLOCK, Color(50,50,50,255));

                if(player.inventario[TOOLBAR][player.selezione_toolbar] != 0)
                {
                    draw_image(blocchi[player.inventario[TOOLBAR][player.selezione_toolbar]].texture,get_mouse_x() - 5, get_mouse_y() - 5, 10, 10, 255);
                    draw_rect(get_mouse_x() - 6, get_mouse_y() - 6, 12, 12, Color(255,255,255,255));
                }
                return;
            }
    }
}

void gestione_giocatore(int mappa[][MAXWIDTH])
{
    gestione_blocchi_droppati(mappa);

    player.inizio_finestra_x = max((int)(player.x - coeff_movimento.x)/(WIDTH_BLOCK) - 20, 0);
    player.inizio_finestra_y = max((int)(player.y - coeff_movimento.y)/(HEIGHT_BLOCK) - 20, 0);
    player.fine_finestra_x = min((int)(player.x - coeff_movimento.x)/(WIDTH_BLOCK) + 20, WIDTH_CHUNK*3);
    player.fine_finestra_y = min((int)(player.y - coeff_movimento.y)/(HEIGHT_BLOCK) + 20, HEIGHT_CHUNK);

    if(!gestione_crafting_table())
    {
        if(!gestione_inventario())
        {
            int mouse_x = get_mouse_x();
            if(mouse_x >= 661)
                draw_image("image/alex_destra.png", player.x, player.y, player.width, player.height);
            else if(mouse_x <= 620)
                draw_image("image/alex_sinistra.png", player.x, player.y, player.width, player.height);
            else
                draw_image("image/alex_frontale.png", player.x, player.y, player.width, player.height);

            player_cursor(mappa, coeff_movimento);

            gestione_toolbar();

            movimento_giocatore(&player, &coeff_movimento, mappa);

            crea_elimina_blocchi(mappa, coeff_movimento);

            salto_giocatore(&player, &coeff_movimento, mappa);
        }
    }
}

void preleva_informazioni_giocatore()
{
    ifstream in("save/player_info.save");

    in >> coeff_movimento.x >> coeff_movimento.y;

    for(int i = 0; i < HEIGHT_INVENTORY; i++)
    {
        for(int j = 0; j < WIDTH_INVENTORY; j++)
            in >> player.inventario[i][j];
    }

    for(int i = 0; i < HEIGHT_INVENTORY; i++)
    {
        for(int j = 0; j < WIDTH_INVENTORY; j++)
            in >> player.inventario_quantita[i][j];
    }

    in.close();
}

void salva_informazioni_giocatore()
{
    ofstream out("save/player_info.save");

    out << coeff_movimento.x << " " << coeff_movimento.y << endl;

    for(int i = 0; i < HEIGHT_INVENTORY; i++)
    {
        for(int j = 0; j < WIDTH_INVENTORY; j++)
            out << player.inventario[i][j] << " ";
        out << endl;
    }

    for(int i = 0; i < HEIGHT_INVENTORY; i++)
    {
        for(int j = 0; j < WIDTH_INVENTORY; j++)
            out << player.inventario_quantita[i][j] << " ";
        out << endl;
    }

    out.close();
}

#include "Inventario/Inventario.h"
#include "Crafting_table/Crafting_table.h"
#include "Toolbar/Toolbar.h"

// FUNZIONE CHE PERMETTE DI EFFETTUARE IL SALTO DEL GIOCATORE
void salto_giocatore(p *player, Coeff_Movimento *coeff_movimento,  int mappa[][MAXWIDTH])
{
    if(player->salto == false)  // SE IL GIOCATORE NON STA ANCORA SALANDO
    {
        bool collisione_salto = false;  // SETTO LA COLLISIONE SALTO A FALSE

        // CONTROLLO NELLA MAPPA SE IL GIOCATORE COLLIDE CON QUALCHE BLOCCO NON TRANSPARENTE
        for(int i = player->inizio_finestra_y; i < player->fine_finestra_y; i++)
        {
            for(int j =  player->inizio_finestra_x; j <  player->fine_finestra_x; j++)
            {
                // SE IL BLOCCO NON E' TRANSPARENTE ...
                if(blocchi[mappa[i][j]].trasparenza == false)
                {
                    // ... E COLLIDO
                    if(controllo_collisione(player->x + 4, player->y, player->width - 8, player->height,
                                    j*WIDTH_BLOCK + coeff_movimento->x, i*HEIGHT_BLOCK + coeff_movimento->y, WIDTH_BLOCK, HEIGHT_BLOCK))
                    {
                        // ALLORA SETTO A TRUE LA COLLISIONE
                        collisione_salto = true;
                        break;
                    }
                }
            }

            // PER EFFICIENZA SE TROVO UN BLOCCO IN CUI COLLIDO ALLORA ESCO DAL FOR ESTERNO
            // ALTRIMENTI FAREI CONTROLLI INUTILI
            if(collisione_salto == true)
                break;
        }

        // SE NON AVVIENE COLLISIONE ALLORA AVVIO AVVIO LA GRAVITA' DEL GIOCATORE
        if(collisione_salto == false)
        {
            // SETTANDO IL COEFFICIENTE DI SALTO A -10 E IL FLAG DEL SALTO A TRUE
            // SE IL COEFFICIENTE E' NEGATIVO ALLORA ALLORA IL GIOCATORE SI MUOVERA' VERSO IL BASSO
            player->coeff_salto = -10;
            player->salto = true;
        }
    }

    // SE PREMO SPAZIO E IL COEFFICIENTE DI SALTO E' FALSE ALLORA FACCIO ESEGUIRE UN SALTO AL GIOCATORE
    if(is_pressed(VSGL_SPACE) && player->salto == false)
    {
        player->coeff_salto = 15;   // SETTO A 15 PER CONVENIENZA IL COEFFICIENTE DI SALTO
        player->salto = true;       // ED ESEGUO IL SALTO
    }

    // SE INVECE IL GIOCATORE STA SALTANDO
    if(player->salto == true)
    {
        // MODIFICO IL COEFFICIENTE DI MOVIMENTO RISPETTO AL COEFFICIENTE DI SALTO DEL GIOCATORE
        coeff_movimento->y += player->coeff_salto;

        // POI ESEGUO COME IN PRECEDENZA UN CONTROLLO SUI BLOCCHI DELLA MAPPA
        // PER VERIFICARE SE IL GIOCATORE COLLIDE CON QUALCHE BLOCCO NON TRASPARENTE
        for(int i = player->inizio_finestra_y; i < player->fine_finestra_y; i++)
        {
            bool flag_uscita = false;
            for(int j =  player->inizio_finestra_x; j <  player->fine_finestra_x; j++)
            {
                // SE COLLIDE CON UN BLOCCO NON TRASPARENTE ...
                if(blocchi[mappa[i][j]].trasparenza == false)
                {
                    if(controllo_collisione(player->x + 4, player->y, player->width - 8, 4, j*WIDTH_BLOCK + coeff_movimento->x, i*HEIGHT_BLOCK + coeff_movimento->y, WIDTH_BLOCK, HEIGHT_BLOCK))
                    {
                        // ... ALLORA RISETTO LA GIUSTA POSIZIONE DEL GIOCATORE
                        // CIOE' LO SETTO CHE SI TROVA SOPRA IL BLOCCO
                        // SE NON LO FACESSI IL GIOCATORE ENTREREBBE NEI BLOCCHI
                        coeff_movimento->y += (player->y) - (((i*HEIGHT_BLOCK) + coeff_movimento->y) + WIDTH_BLOCK);
                        player->coeff_salto = 0;    // RISETTO IL COEFFICIENTE A 0
                        flag_uscita = true;         // E SETTO UN FALG TEMPORANEO A TRUE
                        break;
                    }
                }
            }

            // QUESTO FLAG MI SERVE PEOICHE' COME PRIMA SE COLLIDO CON UN BLOCCO
            // E' INUTILE ANDARE A FARE UN CONROLLO SU ALTRI BLOCCHI
            if(flag_uscita == true)
                break;
        }

        // SE IL COEFFICENTE E' MINORE DELL'ALTEZZA DI UN BLOCCO -5
        if(player->coeff_salto > -(HEIGHT_BLOCK-5))
            player->coeff_salto -= 2.5; // ALLORA LO AUMENTO DI 2.5
        // QUESTO PER FAR SEMBRARE CHE IL SALTO SIA REALISTICO IL PIU' POSSIBILE

        // QUESTO FOR SERVE INVECE PER ANDARE A VEDERE SE IL GIOCATORE NON COLLIDA SOPRA LA TESTA
        for(int i = player->inizio_finestra_y; i < player->fine_finestra_y; i++)
        {
            for(int j =  player->inizio_finestra_x; j <  player->fine_finestra_x; j++)
            {
                // SE COLLIDE CON UN BLOCCO NON TRASPARENTE
                if(blocchi[mappa[i][j]].trasparenza == false)
                {
                    if(controllo_collisione(player->x + 4, player->y+player->height - 4, player->width - 8, 4,
                                    j*WIDTH_BLOCK + coeff_movimento->x, i*HEIGHT_BLOCK + coeff_movimento->y, WIDTH_BLOCK, HEIGHT_BLOCK))
                    {
                        // ALLORA RISETTO IL COEFFICIENTE DI MOVIMENTO
                        // IN MODO TALE CHE IL GIOCATORE SI TROVI SOTTO QUEL BLOCCO E NON CHE RIENTRI
                        // SEMPRE PER IL PROBLEMA PRECEDENTE CHE AVVIENE CON IL SALTO
                        coeff_movimento->y += (player->y + player->height) - ((i*HEIGHT_BLOCK) + coeff_movimento->y);
                        player->salto = false;  // E INFINE SETTO IL FLAG DI SALTO A TRUE
                        return;
                    }
                }
            }
        }
    }
}

// FUNZIONE PER IL MOVIMENTO DEL GIOCATORE
// QUESTA FUNZIONE RICHIEDE DEL PLAYER, DEL COEFFICIENTE DI MOVIMENTO E DELLA MAPPA
void movimento_giocatore(p *player, Coeff_Movimento *coeff_movimento,  int mappa[][MAXWIDTH])
{
    // SETTO I FLAG DELLA COLLISIONE A DESTRA E A SINISTRA DEL GIOCATORE
    player->collisione_sinistra = false;
    player->collisione_destra = false;

    // ATTRAVERSO UN FOR CONTROLLO NELLA MAPPA SE IL GIOCATORE COLLIDE A DESTRA O A SINISTRA CON UN BLOCCO
    // NON TRASPARENTE
    for(int i = player->inizio_finestra_y; i < player->fine_finestra_y; i++)
    {
        for(int j =  player->inizio_finestra_x; j < player->fine_finestra_x; j++)
        {
            // SE IL BLOCCO CON CUI COLLIDE IL GIOCATORE NON E' TRASPARENTE
            if(blocchi[mappa[i][j]].trasparenza == false)
            {
                // CONTROLLO DELLA COLLISIONE A SINISTRA DEL PERSONAGGIO
                if(controllo_collisione(player->x, player->y + 4, 4, player->height - 8,
                                j*WIDTH_BLOCK + coeff_movimento->x, i*HEIGHT_BLOCK + coeff_movimento->y, WIDTH_BLOCK, HEIGHT_BLOCK))
                {
                    // ALLORA SETTO COME PER IL SALTO IL COEFFICIENTE IN MODO TALE CHE IL GIOCATORE NON
                    // SI TROVI ALL'INTERNO DEL BLOCCO
                    coeff_movimento->x += (player->x) - (j*WIDTH_BLOCK + coeff_movimento->x + WIDTH_BLOCK);
                    player->collisione_sinistra = true;     // SETTO IL FLAG DI SINISTRA A true
                    break;
                }
                // CONTROLLO DELLA COLLISIONE A DESTRA DEL PERSONAGGIO
                else if(controllo_collisione(player->x + player->width-4, player->y + 4, 4, player->height - 8,
                                j*WIDTH_BLOCK + coeff_movimento->x, i*HEIGHT_BLOCK + coeff_movimento->y, WIDTH_BLOCK, HEIGHT_BLOCK))
                {
                    // ESEGUO LA STESSA COSA DI PRIMA
                    coeff_movimento->x += (player->x + player->width) - (j*WIDTH_BLOCK + coeff_movimento->x);
                    player->collisione_destra = true;   // E SETTO ANCHE IL FLAG DI DESTRA A true
                    break;
                }
            }
        }
    }

    // SE VIENE PREMUTO LA LETTERA A E IL GIOCATORE NON COLLIDE A SINISTRA
    if(is_pressed(VSGL_A) && player->collisione_sinistra == false)
        coeff_movimento->x += 5;    // ALLORA IL GIOCATORE SI SPOSTERA' A SINISTRA

    // SE INVECE VIENE PREMUTO LA LETTERA D
    if(is_pressed(VSGL_D) && player->collisione_destra == false)
        coeff_movimento->x -= 5;    // ALLORA IL GIOCATORE SI SPOSTERA' A DESTRA
}

// FUNZIONE PER L'ANIMAZIONE DEL BLOCCO MENTRE VIENE DISTRUTTO
// COME PARAMETRI VENGONO RICHIESTI LA MAPPA, LE COORDINATE i, j DEL BLOCCO, E IL FLAG CHE INDICA QUALE LIVELLO DISTRUGGERE
void animazione_distruzione_blocco(int mappa[][MAXWIDTH], int i, int j, bool *flag_livello)
{
    // SE IL FLAG E' SETTATO A true
    if(*flag_livello == true)
    {
        // SE IL TEMPO PASSATO E' MAGGIORE, ...
        if(ms_time() - player.timer_blocco_distrutto + player.forza_aggiuntiva >= blocchi[player.tipo_blocco_distrutto].secondi)
        {
            // DIMINUISCO LA DURABILITA' DELLO STRUMENTO
            if(player.inventario[TOOLBAR][player.selezione_toolbar].blocco.strumento == true)
                player.inventario[TOOLBAR][player.selezione_toolbar].blocco.durabilita--;

            // SE LA DURABILITA' DELLO STRUMENTO E' UGUALE 0
            if(player.inventario[TOOLBAR][player.selezione_toolbar].blocco.durabilita == 0)
            {
                // ALLORA LO ELIMINO
                player.inventario[TOOLBAR][player.selezione_toolbar].blocco = blocchi[0];
                player.inventario[TOOLBAR][player.selezione_toolbar].quantita = 0;
            }

            // ...SE VIENE UTILIZZATO LO STRUMENTO ADATTO ...
            if(player.inventario[TOOLBAR][player.selezione_toolbar].blocco.id >= blocchi[mappa[i][j]].da_oggetto && player.inventario[TOOLBAR][player.selezione_toolbar].blocco.id <= blocchi[mappa[i][j]].a_oggetto)
            {
                // ... E UN VALORE CASUALE RIENTRA NELLA PERCENTUALE DELLO STRUMENTO/BLOCCO
                if(rand()%100 <= blocchi[mappa[i][j]].percentuale_strumento && blocchi[mappa[i][j]].oggetto_droppato_strumento != 0)
                {
                    // ALLORA LO DROPPO, CIOE' LO INSERISCO NEL VETTORE blocchi_droppati
                    blocchi_droppati.push_back({j*WIDTH_BLOCK + 15, i*HEIGHT_BLOCK + 15, blocchi[blocchi[mappa[i][j]].oggetto_droppato_strumento]});
                }
            }
            // ALTRIMENTI SE NON UTILIZZO LO STRUMENTO ADATTO
            else
            {
                // PERO' LA PERCENTUALE RIENTRA COMUNQUE
                if(rand()%100 <= blocchi[mappa[i][j]].percentuale_senza_strumento && blocchi[mappa[i][j]].oggetto_droppato_senza_strumento != 0)
                {
                    // ALLORA LO DROPPO L'OGGETTO CHE VERREBBE DROPPATO SENZA STRUMENTO, CIOE' LO INSERISCO NEL VETTORE blocchi_droppati
                    blocchi_droppati.push_back({j*WIDTH_BLOCK + 15, i*HEIGHT_BLOCK + 15, blocchi[blocchi[mappa[i][j]].oggetto_droppato_senza_strumento]});
                }
            }

            // E SETTO IL BLOCCO DELLA MAPPA A 0
            mappa[player.y_blocco_distrutto][player.x_blocco_distrutto] = 0;

            // E IL FLAG_LIVELLO A false
            *flag_livello = false;
        }
        // SE INVECE IL TEMPO E' MAGGIORE ALLORA AVVIO L'ANIMAZIONE
        else
        {
            // RICERCO L'IMMAGINE DELL'ANIMAZIONE
            string image_animation = "image/break_animation/break_";
            string valore;
            int numero = 1;

            for(int i = 1; i <= 10; i++)
            {
                if(ms_time() - player.timer_blocco_distrutto > (blocchi[player.tipo_blocco_distrutto].secondi - player.forza_aggiuntiva)/10*i)
                    numero = i;
                else
                    break;
            }

            valore = int_to_string(numero);
            image_animation += valore + ".png";

            // DISEGNO L'ANIMAZIONE
            draw_image(image_animation, player.x_blocco_distrutto*WIDTH_BLOCK + coeff_movimento.x,  player.y_blocco_distrutto*HEIGHT_BLOCK
                        + coeff_movimento.y, WIDTH_BLOCK, HEIGHT_BLOCK, 255);
        }
    }
}

// FUNZIONE PER ELIMINAZIONE DI UN BLOCCO IN UN LIVELLO
// LA FUNZIONE RICHIEDE DELLA MAPPA E DEL FLAG CHE INDICA SE IL GIOCATORE STA SPACCANDO IL BLOCCO O MENO
void eliminazione_blocco(int mappa[][WIDTH_CHUNK*3], bool *flag)
{
    // SE IL BLOCCO SI PUO' DISTRUGGERE ...
    if(blocchi[mappa[cursore.y_blocco][cursore.x_blocco]].distruggi == true)
    {
        // ... E IL FLAG E' SETTATO A FALSE
        if(*flag == false)
        {
            if(breaking[int_to_string(mappa[cursore.y_blocco][cursore.x_blocco]) + int_to_string(player.inventario[TOOLBAR][player.selezione_toolbar].blocco.id)] != NULL)
                player.forza_aggiuntiva = breaking[int_to_string(mappa[cursore.y_blocco][cursore.x_blocco]) + int_to_string(player.inventario[TOOLBAR][player.selezione_toolbar].blocco.id)];
            else
                player.forza_aggiuntiva = 0;

            //if(player.inventario[TOOLBAR][player.selezione_toolbar].blocco.strumento == true)

            // ALLORA SETTO IL TIMER AL TEMPO ATTUALE
            player.timer_blocco_distrutto = ms_time();

            // INDICO LE COORDINATE DEL BLOCCO
            player.x_blocco_distrutto = cursore.x_blocco;
            player.y_blocco_distrutto = cursore.y_blocco;
            // IL TIPO DI BLOCCO CHE VIENE SPACCATO
            player.tipo_blocco_distrutto = mappa[cursore.y_blocco][cursore.x_blocco];
            *flag = true;   // E IL FLAG LO SETTO A true COSI' SI PUO' AVVIARE L'ANIMAZIONE
        }
        // MENTRE SE IL FLAG E' true E
        else if(*flag == true && (player.x_blocco_distrutto != cursore.x_blocco || player.y_blocco_distrutto != cursore.y_blocco))
        {
            player.timer_blocco_distrutto = ms_time();
            player.x_blocco_distrutto = cursore.x_blocco;
            player.y_blocco_distrutto = cursore.y_blocco;
            player.tipo_blocco_distrutto = mappa[cursore.y_blocco][cursore.x_blocco];
            *flag = true;
        }
    }
}

// FUNZIONE PER LA CREAZIONE DI UN BLOCCO NELLA MAPPA
// LA FUNZIONE RICHIEDE LA MAPPA
void creazione_blocco(int mappa[][WIDTH_CHUNK*3])
{
    // SE IL BLOCCO DELLA MAPPA E' VUOTO
    if(blocchi[mappa[cursore.y_blocco][cursore.x_blocco]].id == 0 &&
       !controllo_collisione(player.x, player.y, player.width, player.height, cursore.x_blocco*WIDTH_BLOCK + coeff_movimento.x, cursore.y_blocco*HEIGHT_BLOCK + coeff_movimento.y, WIDTH_BLOCK, HEIGHT_BLOCK))
    {
        // E NELLA TOOLBAR HO IN MANO UN BLOCCO/OGGETTO CHE SI PUO' "PIAZZARE"
        if(player.inventario[TOOLBAR][player.selezione_toolbar].blocco.blocco == true &&
           (mappa[cursore.y_blocco-1][cursore.x_blocco] != 0 || mappa[cursore.y_blocco+1][cursore.x_blocco] != 0 || mappa[cursore.y_blocco][cursore.x_blocco-1] != 0 || mappa[cursore.y_blocco][cursore.x_blocco+1] != 0 || ::mappa.secondo_livello[cursore.y_blocco][cursore.x_blocco] != 0))
        {
            if(player.inventario[TOOLBAR][player.selezione_toolbar].blocco.id == OAK_SAPLING && (mappa[cursore.y_blocco+1][cursore.x_blocco] == GRASS || mappa[cursore.y_blocco+1][cursore.x_blocco] == DIRT))
            {
                Tree temp;
                temp.x = cursore.x_blocco;
                temp.y = cursore.y_blocco;
                temp.tempo_passato = 0;

                alberi.push_back(temp);
            }

            // ALLORA SETTO IL BLOCCO CHE INDICA IL CURSORE A QUELLO DELLA TOOLBAR
            mappa[cursore.y_blocco][cursore.x_blocco] = player.inventario[TOOLBAR][player.selezione_toolbar].blocco.id;

            // SE LA QUANTITA' DEL BLOCCO TENUTO IN MANO DAL GIOCATORE E' MAGGIORE A 0
            if(player.inventario[TOOLBAR][player.selezione_toolbar].quantita > 0)
                // ALLORA DECREMENTO IL BLOCCO ONTENUTO NELLA TOOLBAR
                player.inventario[TOOLBAR][player.selezione_toolbar].quantita--;
            // SE INVECE E' UGUALE A 0
            if(player.inventario[TOOLBAR][player.selezione_toolbar].quantita == 0)
                // ALLORA SETTO IL BLOCCO STESSO A 0 (BLOCCO VUOTO)
                player.inventario[TOOLBAR][player.selezione_toolbar].blocco = blocchi[0];
        }
    }
}

// FUNZIONE CHE GESTISCE LA CREAZIONE/DISTRUZIONE DEI BLOCCHI NELLA MAPPA
// I PARAMETRI SONO MAPPA E COEFFICIENTE DI MOVIMENTO
void crea_elimina_blocchi(int mappa[][MAXWIDTH], Coeff_Movimento coeff_movimento)
{
    // SE IL GIOCATORE STA DISTRUGGENDO UN BLOCCO NEL PRIMO LIVELLO
    if(player.distruggere == true)
        // AVVIO L'ANIMAZIONE
        animazione_distruzione_blocco(mappa,player.y_blocco_distrutto,player.x_blocco_distrutto, &player.distruggere);
    // SE INVECE IL GIOCATORE STA DISTRUGGENDO UN BLOCCO NEL SECONDO LIVELLO
    else if(player.distruggere_secondo_livello == true)
        // AVVIO L'ANIMAZIONE DELL'ALTRO BLOCCO
        animazione_distruzione_blocco(::mappa.secondo_livello,player.y_blocco_distrutto,player.x_blocco_distrutto, &player.distruggere_secondo_livello);


    // SE VIENE PREMUTO IL TASTO SINISTRO
    if(mouse_left_button_pressed())
    {
        // E ALLO STESSO TEMPO IL TASTO DESTRO/SINISTRO SHIFT
        if(is_pressed(VSGL_LSHIFT) || is_pressed(VSGL_RSHIFT))
        {
            // ALLORA IL FLAG DEL PRIMO LIVELLO A false
            // QUESTO PERCHE' IL GIOCATORE POSSA SOLTANTO SPACCARE UN BLOCCO ALLA VOLTA DI UN LIVELLO DIVERSO
            player.distruggere = false;
            // E AVVIO LA FUNZIONE DI ELIMINAZIONE DEL BLOCCO
            eliminazione_blocco(::mappa.secondo_livello, &player.distruggere_secondo_livello);
        }
        else
        {
            // SETTO ANCHE QUI IL FLAG DEL SECONDO LIVELLO A false
            player.distruggere_secondo_livello = false;
            // E AVVIO LA FUNZIONE DI ELIMINAZIONE BLOCCO
            eliminazione_blocco(mappa, &player.distruggere);
        }
    }
    // MENTRE SE PREMO TASTO DESTRO E IL GIOCATORE SELEZIONA UN BLOCCO CHE SI PUO' PIAZZARE
    else if(mouse_right_button_pressed())
    {
        // E PREMO IL TASTO DESTRO/SINISTRO SHIFT
        if(is_pressed(VSGL_LSHIFT) || is_pressed(VSGL_RSHIFT))
            // INSERISCO IL BLOCCO NEL SECONDO LIVELLO
            creazione_blocco(::mappa.secondo_livello);
        else
            // ALTRIMENTI INSERISCO IL BLOCCO NEL PRIMO LIVELLO
            creazione_blocco(mappa);
    }
    else
    {
        player.distruggere = false;
        player.distruggere_secondo_livello = false;
    }
}

// FUNZIONE CHE GESTISCE IL CURSORE
// ESSA RICHIEDE IL COEFFICIENTE DI MOVIMENTO
void player_cursor(Coeff_Movimento coeff_movimento)
{
    // AGGIORNO IL BLOCCO IN CUI SI TROVA IL CURSORE
    cursore.x_blocco = (int)(get_mouse_x() - coeff_movimento.x)/40;
    cursore.y_blocco = (int)(get_mouse_y() - coeff_movimento.y)/40;

    // DISEGNO IL RETTANGOLO NERO PER INDICARE DOVE SI TROVA IL CURSORE
    draw_rect(cursore.x_blocco*WIDTH_BLOCK + coeff_movimento.x, cursore.y_blocco*HEIGHT_BLOCK + coeff_movimento.y, WIDTH_BLOCK, HEIGHT_BLOCK, Color(50,50,50,255));

    draw_filled_rect(get_mouse_x() - 1, get_mouse_y() - 10, 2, 20, Color(0,0,0,255));
    draw_filled_rect(get_mouse_x() - 10, get_mouse_y() - 1, 20, 2, Color(0,0,0,255));
}

// FUNZIONE PER LA GESTIONE DELLE VARIE FUNZIONALITA' DEL GIOCATORE
void gestione_giocatore(int mappa[][MAXWIDTH])
{
    // FUNZIONE PER IL CONTROLLO DEI BLOCCO DROPPATI
    gestione_blocchi_droppati(mappa);

    // AGGIORNO LA FINESTRA DI DISEGNO DI GIOCO DEL PERSONAGGIO
    player.inizio_finestra_x = max((int)(player.x - coeff_movimento.x)/(WIDTH_BLOCK) - 20, 0);
    player.inizio_finestra_y = max((int)(player.y - coeff_movimento.y)/(HEIGHT_BLOCK) - 20, 0);
    player.fine_finestra_x = min((int)(player.x - coeff_movimento.x)/(WIDTH_BLOCK) + 20, WIDTH_CHUNK*3);
    player.fine_finestra_y = min((int)(player.y - coeff_movimento.y)/(HEIGHT_BLOCK) + 20, HEIGHT_CHUNK);

    // AVVIO LA FUNZIONE DELLA GESTIONE DELLA TOOLBAR...
    gestione_toolbar();

    // DISEGNO IL GIOCATORE
    int mouse_x = get_mouse_x();
    if(mouse_x >= 661)
        draw_image("image/alex_destra.png", player.x, player.y, player.width, player.height);
    else if(mouse_x <= 620)
        draw_image("image/alex_sinistra.png", player.x, player.y, player.width, player.height);
    else
        draw_image("image/alex_frontale.png", player.x, player.y, player.width, player.height);


    // SE IL GIOCATORE NON HA SELEZIONATO LA CRAFTING TABLE
    if(!gestione_crafting_table())
    {
        // E LINVENTARIO
        if(!gestione_inventario())
        {
            // ...E DELLA CREAZIONE/ELIMINAZIONE DEL BLOCCO
            crea_elimina_blocchi(mappa, coeff_movimento);

            // AVVIO LA FUNZIONE DEL CURSORE
            player_cursor(coeff_movimento);

            // ...DEL MOVIMENTO DEL GICOATORE...
            movimento_giocatore(&player, &coeff_movimento, mappa);

            // ...DEL SALTO DEL GIOCATORE...
            salto_giocatore(&player, &coeff_movimento, mappa);
        }
    }
}

// FUNZIONE PER IL PRELIEVO DELLE INFORMAZIONI RIGUARDANTI IL GIOCATORE
void preleva_informazioni_giocatore()
{
    // APRO IL FILE DELLE INFORMAZIONI
    ifstream in("save/player_info.save");

    // PRELEVO I COEFFICIENTI (L'ULTIMA POSIZIONE DEL GIOCATORE)
    in >> coeff_movimento.x >> coeff_movimento.y;

    // PRELEVO L'INVENTARIO
    for(int i = 0; i < HEIGHT_INVENTORY; i++)
    {
        for(int j = 0; j < WIDTH_INVENTORY; j++)
        {
            in >> player.inventario[i][j].blocco.id
            >> player.inventario[i][j].blocco.texture
            >> player.inventario[i][j].blocco.blocco
            >> player.inventario[i][j].blocco.strumento
            >> player.inventario[i][j].blocco.distruggi
            >> player.inventario[i][j].blocco.trasparenza
            >> player.inventario[i][j].blocco.secondi
            >> player.inventario[i][j].blocco.da_oggetto
            >> player.inventario[i][j].blocco.a_oggetto
            >> player.inventario[i][j].blocco.percentuale_senza_strumento
            >> player.inventario[i][j].blocco.oggetto_droppato_senza_strumento
            >> player.inventario[i][j].blocco.percentuale_strumento
            >> player.inventario[i][j].blocco.oggetto_droppato_strumento
            >> player.inventario[i][j].blocco.durabilita
            >> player.inventario[i][j].blocco.massima_stoccabilita;
        }
    }

    // PRELEVO LA QUANTITA INVENTARIO
    for(int i = 0; i < HEIGHT_INVENTORY; i++)
    {
        for(int j = 0; j < WIDTH_INVENTORY; j++)
            in >> player.inventario[i][j].quantita;
    }

    in.close();
}

// FUNZIONE PER IL SALVATAGGIO DELLE INFORMAZIONI SUL GIOCATORE
void salva_informazioni_giocatore()
{
    // APRO IL FILE
    ofstream out("save/player_info.save");

    // SALVO IL COEFFICIENTE DI MOVIMENTO (L'ULTIMA POSIZIONE DEL GIOCATORE)
    out << coeff_movimento.x << " " << coeff_movimento.y << endl;

    // SALVO L'INVENTARIO
    for(int i = 0; i < HEIGHT_INVENTORY; i++)
    {
        for(int j = 0; j < WIDTH_INVENTORY; j++)
            out << player.inventario[i][j].blocco.id << " "
            << player.inventario[i][j].blocco.texture << " "
            << player.inventario[i][j].blocco.blocco << " "
            << player.inventario[i][j].blocco.strumento << " "
            << player.inventario[i][j].blocco.distruggi << " "
            << player.inventario[i][j].blocco.trasparenza << " "
            << player.inventario[i][j].blocco.secondi << " "
            << player.inventario[i][j].blocco.da_oggetto << " "
            << player.inventario[i][j].blocco.a_oggetto << " "
            << player.inventario[i][j].blocco.percentuale_senza_strumento << " "
            << player.inventario[i][j].blocco.oggetto_droppato_senza_strumento << " "
            << player.inventario[i][j].blocco.percentuale_strumento << " "
            << player.inventario[i][j].blocco.oggetto_droppato_strumento << " "
            << player.inventario[i][j].blocco.durabilita << " "
            << player.inventario[i][j].blocco.massima_stoccabilita << endl;
        out << endl;
    }

    // SALVO LA QUANTITA' INVENTARIO
    for(int i = 0; i < HEIGHT_INVENTORY; i++)
    {
        for(int j = 0; j < WIDTH_INVENTORY; j++)
            out << player.inventario[i][j].quantita << " ";
        out << endl;
    }

    out.close();
}

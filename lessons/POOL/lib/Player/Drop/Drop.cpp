bool cerca_posto(int k)
{
    bool trovato = false;

    if(trovato == false)
    {
        for(int i = 0; i < WIDTH_INVENTORY; i++)
        {
            if(player.inventario[TOOLBAR][i].blocco.id == blocchi_droppati[k].blocco.id && player.inventario[TOOLBAR][i].quantita < player.inventario[TOOLBAR][i].blocco.massima_stoccabilita)
            {
                player.inventario[TOOLBAR][i].quantita++;
                trovato = true;
                break;
            }
        }
    }

    if(trovato == false)
    {
        for(int i = 0; i < TOOLBAR; i++)
        {
            for(int j = 0; j < WIDTH_INVENTORY; j++)
            {
                if(player.inventario[i][j].blocco.id == blocchi_droppati[k].blocco.id && player.inventario[i][j].quantita < player.inventario[i][j].blocco.massima_stoccabilita)
                {
                    player.inventario[i][j].quantita++;
                    trovato = true;
                    break;
                }
            }

            if(trovato == true)
                break;
        }
    }

    if(trovato == false)
    {
        for(int i = 0; i < WIDTH_INVENTORY; i++)
        {
            if(player.inventario[TOOLBAR][i].blocco.id == 0)
            {
                player.inventario[TOOLBAR][i].blocco = blocchi_droppati[k].blocco;
                player.inventario[TOOLBAR][i].quantita++;
                trovato = true;
                break;
            }
        }
    }


    if(trovato == false)
    {
        for(int i = 0; i < TOOLBAR; i++)
        {
            for(int j = 0; j < WIDTH_INVENTORY; j++)
            {
                if(player.inventario[i][j].blocco.id == 0)
                {
                    player.inventario[i][j].blocco = blocchi_droppati[k].blocco;
                    player.inventario[i][j].quantita++;
                    trovato = true;
                    break;
                }
            }

            if(trovato == true)
                break;
        }
    }

    return trovato;
}

void prendi_oggetto()
{
    for(int i = 0; i < blocchi_droppati.size(); i++)
    {
        int distanza = sqrt(pow((player.x) - (blocchi_droppati[i].x + coeff_movimento.x), 2) +
                            pow((player.y) - (blocchi_droppati[i].y + coeff_movimento.y), 2));

        if(distanza < 76)
        {
            //  x:1 = differenzaX : distanzaY  --> speedX = differenzaX/differenzaY; speedY = 1

            if(blocchi_droppati[i].x + coeff_movimento.x  < player.x)
                blocchi_droppati[i].x += 2;
            else if(blocchi_droppati[i].x + coeff_movimento.x >= player.x)
                blocchi_droppati[i].x -= 2;
        }

        if(distanza < 65)
        {
            if(cerca_posto(i))
            {
                blocchi_droppati.erase(blocchi_droppati.begin()+i);
                i--;
            }
        }
    }
}

void disegna_blocchi_droppati()
{
    for(int i = 0; i < blocchi_droppati.size(); i++)
        draw_image(blocchi[blocchi_droppati[i].blocco.id].texture, blocchi_droppati[i].x + coeff_movimento.x, blocchi_droppati[i].y + coeff_movimento.y, 10, 10, 255);
}

void gravita_blocchi_droppati(int mappa[][MAXWIDTH])
{
    for(int i = 0; i < blocchi_droppati.size(); i++)
    {
        for(int j = 0; j < HEIGHT_CHUNK; j++)
        {
            if(mappa[j][((int)blocchi_droppati[i].x)/WIDTH_BLOCK] != 0)
            {
//                draw_filled_rect((int)blocchi_droppati[i].x + coeff_movimento.x, j*40 + coeff_movimento.y, 40, 40, Color(255,0,0,255));
//                draw_rect((int)blocchi_droppati[i].x + coeff_movimento.x, j*40 + coeff_movimento.y, 40, 40, Color(0,0,0,255));

                if(!controllo_collisione(blocchi_droppati[i].x + coeff_movimento.x, blocchi_droppati[i].y + coeff_movimento.y, 10, 10, ((int)blocchi_droppati[i].x) + coeff_movimento.x, j*WIDTH_BLOCK + coeff_movimento.y - 5, WIDTH_BLOCK, HEIGHT_BLOCK))
                {
                    blocchi_droppati[i].y += .5;
                }
                else
                {
                    blocchi_droppati[i].y -= (blocchi_droppati[i].y + coeff_movimento.y + 15) - ((j*WIDTH_BLOCK) + coeff_movimento.y);
                    break;
                }
            }
        }
    }
}

void gestione_blocchi_droppati(int mappa[][MAXWIDTH])
{
    prendi_oggetto();

    gravita_blocchi_droppati(mappa);
    disegna_blocchi_droppati();
}

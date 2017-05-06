void giorno()
{
    static bool avanza = false;

    static float sun_x = 0;
    static float sun_y = 300;
    static float sun_speed = -1;

    if(ms_time()%2000 < 1000 && avanza == true)
    {
        avanza = false;
        sun_y += sun_speed;
        sun_speed += .00001;
        sun_x += 10;
    }
    else if(ms_time()%2000 >= 1000)
    {
        avanza = true;
    }

    draw_image("image/sun.png", sun_x, sun_y, 8*4, 8*4, 255);
}

void disegna_ombra()
{
    for(int i = 0; i < HEIGHT_CHUNK; i++)
    {
        for(int j = 0; j < WIDTH_CHUNK*3; j++)
        {
            draw_filled_rect(j*WIDTH_BLOCK + coeff_movimento.x, i*HEIGHT_BLOCK + coeff_movimento.y, WIDTH_BLOCK, HEIGHT_BLOCK, Color(0,0,0, 255 - mappa.ombra[i][j]));
        }
    }
}

void gestione_ombra()
{
    for(int i = player.inizio_finestra_y; i < player.fine_finestra_y; i++)
        for(int j =  player.inizio_finestra_x; j <  player.fine_finestra_x; j++)
            mappa.ombra[i][j] = 0;

    for(int i = player.inizio_finestra_y; i < player.fine_finestra_y; i++)
    {
        for(int j =  player.inizio_finestra_x; j <  player.fine_finestra_x; j++)
        {
            if((mappa.mappa[i][j] == 0 && mappa.secondo_livello[i][j] == 0) || (blocchi[mappa.mappa[i][j]].luce != -1 && mappa.mappa[i][j]))
            {
                for(int k = max(0, i-blocchi[mappa.mappa[i][j]].luce); k <= min(HEIGHT_CHUNK, i+blocchi[mappa.mappa[i][j]].luce); k++)
                {
                    for(int m = max(0, j-blocchi[mappa.mappa[i][j]].luce); m <= min(WIDTH_CHUNK*3, j+blocchi[mappa.mappa[i][j]].luce); m++)
                    {
                        int dist_x = abs(j - m);
                        int dist_y = abs(i - k);
                        int dist_tot = max(dist_x, dist_y);

                        mappa.ombra[k][m] = max(mappa.ombra[k][m], 255 - (255.0/blocchi[mappa.mappa[i][j]].luce)*dist_tot);
                    }
                }
            }
        }
    }
}

void gestione_cielo()
{
/*
    if(ms_time()%600000 < 300000)
    {
        giorno();
    }
    else
    {
        //draw_filled_rect(0,0,WIDTH_WINDOW, HEIGHT_WINDOW, Color(0,0,0,255));
    }*/
}

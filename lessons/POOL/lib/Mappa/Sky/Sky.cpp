float temp_coeff_movimento_x = -20;
void giorno()
{
    static bool avanza = false;

    static float sun_x = 0;
    static float sun_y = 200;
    static float sun_speed = -1;

    if(ms_time()%1000 < 250 && avanza == true)
    {
        avanza = false;
        sun_y += sun_speed;
        sun_speed += .00001;
        sun_x += 1;
    }
    else if(ms_time()%1000 >= 250)
    {
        avanza = true;
    }

    if(is_pressed(VSGL_A) && player.collisione_sinistra == false)
        temp_coeff_movimento_x += 5;

    if(is_pressed(VSGL_D) && player.collisione_destra == false)
        temp_coeff_movimento_x -= 5;
    draw_image("image/day.png",-4*WIDTH_WINDOW+temp_coeff_movimento_x,0,4*WIDTH_WINDOW, HEIGHT_WINDOW, 255);
    draw_image("image/day.png",0+temp_coeff_movimento_x,0,4*WIDTH_WINDOW, HEIGHT_WINDOW, 255);
    draw_image("image/sun.png", sun_x, sun_y, 20*4, 20*4, 255);
}

void notte()
{
    static bool avanza = false;

    static float moon_x = 0;
    static float moon_y = 200;
    static float moon_speed = -1;

    if(ms_time()%1000 < 250 && avanza == true)
    {
        avanza = false;
        moon_y += moon_speed;
        moon_speed += .00001;
        moon_x += 1;
    }
    else if(ms_time()%1000 >= 250)
    {
        avanza = true;
    }

    if(is_pressed(VSGL_A) && player.collisione_sinistra == false)
        temp_coeff_movimento_x += 5;

    if(is_pressed(VSGL_D) && player.collisione_destra == false)
        temp_coeff_movimento_x -= 5;


    draw_image("image/night.png",0+temp_coeff_movimento_x,0,4*WIDTH_WINDOW, HEIGHT_WINDOW, 255);
    draw_image("image/moon.png", moon_x, moon_y, 20*4, 20*4, 255);
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

    if(ms_time()%600000 < 300000)
    {
        giorno();
    }
    else
    {
        notte();
    }
}

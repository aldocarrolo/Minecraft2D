void giorno()
{
    static int timer = 0;
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

void gestione_cielo()
{
    if(ms_time()%600000 < 300000)
    {
        giorno();
    }
    else
    {
        //draw_filled_rect(0,0,WIDTH_WINDOW, HEIGHT_WINDOW, Color(0,0,0,255));
    }
}

bool controllo_collisione(float x1, float y1, float w1, float h1,
                          float x2, float y2, float w2, float h2)
{

    if(x1 >= x2 && x1 <= x2+w2 && y1 >= y2 && y1 <= y2+h2)
        return true;

    if(x1+w1 >= x2 && x1+w1 <= x2+w2 && y1 >= y2 && y1 <= y2+h2)
        return true;

    if(x1 >= x2 && x1 <= x2+w2 && y1+h1 >= y2 && y1+h1 <= y2+h2)
        return true;

    if(x1+w1 >= x2 && x1+w1 <= x2+w2 && y1+h1 >= y2 && y1+h1 <= y2+h2)
        return true;

    return false;
}

string int_to_string(int N)
{
    stringstream ss;
    ss << N;
    string str = ss.str();

    return str;
}

void disegna_testo(string font, int dim, string testo, int x, int y, Color color)
{
    draw_text(font, dim, testo, x+2, y+2, Color(0,0,0,125));
    draw_text(font, dim, testo, x, y, color);
}

bool controllo_tasto_sinistro_premuto()
{
    static int flag_controllo_tasto_sinistro = 0;
    static bool valore_ritorno_tasto_sinistro = false;

    if(!mouse_left_button_pressed() && flag_controllo_tasto_sinistro == 1)
    {
        flag_controllo_tasto_sinistro = 0;
        valore_ritorno_tasto_sinistro = false;
    }
    else if(mouse_left_button_pressed() && flag_controllo_tasto_sinistro == 1)
    {
        valore_ritorno_tasto_sinistro = false;
    }

    if(mouse_left_button_pressed() && flag_controllo_tasto_sinistro != 1)
    {
        flag_controllo_tasto_sinistro = 1;
        valore_ritorno_tasto_sinistro = true;
    }

    return valore_ritorno_tasto_sinistro;
}

bool controllo_tasto_destro_premuto()
{
    static int flag_controllo_tasto_destro = 0;
    static bool valore_ritorno_tasto_destro = false;

    if(!mouse_right_button_pressed() && flag_controllo_tasto_destro == 1)
    {
        flag_controllo_tasto_destro = 0;
        valore_ritorno_tasto_destro = false;
    }
    else if(mouse_right_button_pressed() && flag_controllo_tasto_destro == 1)
    {
        valore_ritorno_tasto_destro = false;
    }

    if(mouse_right_button_pressed() && flag_controllo_tasto_destro != 1)
    {
        flag_controllo_tasto_destro = 1;
        valore_ritorno_tasto_destro = true;
    }

    return valore_ritorno_tasto_destro;
}

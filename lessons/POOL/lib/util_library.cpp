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
    draw_text(font, dim, testo, x+1.5, y+2, Color(0,0,0,125));
    draw_text(font, dim, testo, x, y, color);
}

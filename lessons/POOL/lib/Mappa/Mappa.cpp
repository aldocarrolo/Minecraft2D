#include "Sky/Sky.h"

class Mappa
{
private:
public:
    int mappa[HEIGHT_CHUNK][WIDTH_CHUNK*3];
    int secondo_livello[HEIGHT_CHUNK][WIDTH_CHUNK*3];

    int chunk_iniziale;
    int chunk_finale;
    int chunk_attuale;

    void creazione_caverna(int y, int x, int coeff_casualita);
    void crea();

    void genera_chunk_sinistra(string file_name);
    void genera_sinistra();
    void genera_chunk_destra(string file_name);
    void genera_destra();

    void salva(int chunk);
    void preleva(int chunk);

    void disegna();

    void update();
} mappa;

void Mappa::creazione_caverna(int y, int x, int coeff_casualita)
{
    mappa[y][x] = 0;

    if(rand()%100 >= coeff_casualita)
    {
        if(x < WIDTH_CHUNK*3-1)
            if(mappa[y][x+1] != 0)
                creazione_caverna(y, x+1, coeff_casualita + rand()%15);

        if(x > 0)
            if(mappa[y][x-1] != 0)
                creazione_caverna(y, x-1, coeff_casualita + rand()%15);

        if(y < HEIGHT_CHUNK-1)
            if(mappa[y+1][x] != 0)
                creazione_caverna(y+1, x, coeff_casualita + rand()%15);

        if(y > 0)
            if(mappa[y-1][x] != 0)
                creazione_caverna(y-1, x, coeff_casualita + rand()%15);
    }
}

void Mappa::crea()
{
    for(int i = 0; i < HEIGHT_CHUNK; i++)
    {
        for(int j = 0; j < WIDTH_CHUNK*3; j++)
        {
            this->mappa[i][j] = 0;
            this->secondo_livello[i][j] = 0;
        }
    }

    int altezza_precedente = 55;

    for(int i = 0; i < WIDTH_CHUNK*3; i++)
    {
        int coeff_altezza = rand()%3;

        int altezza_attuale = altezza_precedente;

        int valore_casuale = rand()%2 == 0;
        if(valore_casuale == 0&& altezza_attuale - coeff_altezza < 30)
            altezza_attuale -= coeff_altezza;
        else if(valore_casuale == 1 && altezza_attuale - coeff_altezza > 50)
            altezza_attuale += coeff_altezza;

        if(rand()%100 >= 87 && i - 2 >= 0 && i + 2 < WIDTH_CHUNK*3)
        {
            for(int k = 0; k < 6; k++)
                for(int m = 0; m < 5; m++)
                    if(this->mappa[altezza_attuale - 6 + k][i - 2 + m] == 0)
                        this->mappa[altezza_attuale - 6 + k][i - 2 + m] = albero[k][m];
        }

        this->mappa[altezza_attuale][i] = 1;

        int j;
        for(j = altezza_attuale+1; j < altezza_attuale+rand()%6+6; j++)
        {
            this->mappa[j][i] = 2;
            this->secondo_livello[j][i] = 2;
        }

        for(; j < HEIGHT_CHUNK; j++)
        {
            this->mappa[j][i] = 3;
            this->secondo_livello[j][i] = 3;
        }

        altezza_precedente = altezza_attuale;
    }

    ofstream out("save/map_info.save");
    out << -1 << " " << 0 << " " << 1 << endl;
    out.close();

    ofstream player_info("save/player_info.save");
    player_info << coeff_movimento.x << " " << coeff_movimento.y << endl;

    for(int i = 0; i < HEIGHT_INVENTORY; i++)
    {
        for(int j = 0; j < WIDTH_INVENTORY; j++)
            player_info << player.inventario[i][j] << " ";
        player_info << endl;
    }
    player_info.close();

    this->chunk_iniziale = -1;
    this->chunk_attuale = 0;
    this->chunk_finale = 1;

    this->salva(0);
}

void Mappa::genera_chunk_sinistra(string file_name)
{
    int attuale = 0;
    while(this->mappa[attuale][0] != 1)
        attuale++;

    int mappa_temp[HEIGHT_CHUNK][WIDTH_CHUNK];
    int secondo_livello_temp[HEIGHT_CHUNK][WIDTH_CHUNK];

    for(int i = 0; i < HEIGHT_CHUNK; i++)
    {
        for(int j = 0; j < WIDTH_CHUNK; j++)
        {
            mappa_temp[i][j] = 0;
            secondo_livello_temp[i][j] = 0;
        }
    }

    int altezza_precedente = attuale;

    for(int i = WIDTH_CHUNK-1; i >= 0; i--)
    {
        int coeff_altezza = rand()%3;

        int altezza_attuale = altezza_precedente;

        int valore_casuale = rand()%2 == 0;
        if(valore_casuale == 0&& altezza_attuale - coeff_altezza > 30 && altezza_attuale - coeff_altezza >= 0)
            altezza_attuale -= coeff_altezza;
        else if(valore_casuale == 1 && altezza_attuale - coeff_altezza < 50)
            altezza_attuale += coeff_altezza;

        if(rand()%100 >= 87 && i - 2 > 0 && i + 2 < WIDTH_CHUNK)
        {
            for(int k = 0; k < 6; k++)
                for(int m = 0; m < 5; m++)
                    if(mappa_temp[altezza_attuale - 6 + k][i - 2 + m] == 0)
                        mappa_temp[altezza_attuale - 6 + k][i - 2 + m] = albero[k][m];
        }

        mappa_temp[altezza_attuale][i] = 1;

        int j;
        for(j = altezza_attuale+1; j < altezza_attuale+rand()%6+6; j++)
        {
            mappa_temp[j][i] = 2;
            secondo_livello_temp[j][i] = 2;
        }

        for(; j < HEIGHT_CHUNK; j++)
        {
            mappa_temp[j][i] = 3;
            secondo_livello_temp[j][i] = 3;
        }

        altezza_precedente = altezza_attuale;
    }

    ofstream out(file_name);
    for(int i = 0; i < HEIGHT_CHUNK; i++)
    {
        for(int j = 0; j < WIDTH_CHUNK; j++)
            out << mappa_temp[i][j] << " ";
        out << endl;
    }

    for(int i = 0; i < HEIGHT_CHUNK; i++)
    {
        for(int j = 0; j < WIDTH_CHUNK; j++)
            out << secondo_livello_temp[i][j] << " ";
        out << endl;
    }
    out.close();
}

void Mappa::genera_sinistra()
{
    this->chunk_attuale--;

    ostringstream itos;
    itos << "save/chunk/" << this->chunk_iniziale-1 << ".save";
    string temp = itos.str();

    this->genera_chunk_sinistra(temp);

    ofstream fout("save/map_info.save");
    fout << this->chunk_iniziale-1 << " " << this->chunk_attuale << " " << this->chunk_finale << endl;
    fout.close();

    this->preleva(this->chunk_attuale);
}

void Mappa::genera_chunk_destra(string file_name)
{
    int attuale = 0;
    while(this->mappa[attuale][WIDTH_CHUNK*3-1] != 1)
        attuale++;

    int mappa_temp[HEIGHT_CHUNK][WIDTH_CHUNK];
    int secondo_livello_temp[HEIGHT_CHUNK][WIDTH_CHUNK];

    for(int i = 0; i < HEIGHT_CHUNK; i++)
    {
        for(int j = 0; j < WIDTH_CHUNK; j++)
        {
            mappa_temp[i][j] = 0;
            secondo_livello_temp[i][j] = 0;
        }
    }

    int altezza_precedente = attuale;

    for(int i = 0; i < WIDTH_CHUNK; i++)
    {
        int coeff_altezza = rand()%3;

        int altezza_attuale = altezza_precedente;

        int valore_casuale = rand()%2;
        if(valore_casuale == 0 && altezza_attuale - coeff_altezza > 30 && altezza_attuale - coeff_altezza >= 0)
            altezza_attuale  -= coeff_altezza;
        else if(valore_casuale == 1 && altezza_attuale - coeff_altezza < 50)
            altezza_attuale += coeff_altezza;

        if(rand()%100 >= 87 && i - 2 >= 0 && i + 2 < WIDTH_CHUNK)
        {
            for(int k = 0; k < 6; k++)
                for(int m = 0; m < 5; m++)
                    if(mappa_temp[altezza_attuale - 6 + k][i - 2 + m] == 0)
                        mappa_temp[altezza_attuale - 6 + k][i - 2 + m] = albero[k][m];
        }

        mappa_temp[altezza_attuale][i] = 1;

        int j;
        for(j = altezza_attuale+1; j < altezza_attuale+rand()%6+6; j++)
        {
            mappa_temp[j][i] = 2;
            secondo_livello_temp[j][i] = 2;
        }

        for(; j < HEIGHT_CHUNK; j++)
        {
            mappa_temp[j][i] = 3;
            secondo_livello_temp[j][i] = 3;
        }

        altezza_precedente = altezza_attuale;
    }

    ofstream out(file_name);
    for(int i = 0; i < HEIGHT_CHUNK; i++)
    {
        for(int j = 0; j < WIDTH_CHUNK; j++)
            out << mappa_temp[i][j] << " ";
        out << endl;
    }

    for(int i = 0; i < HEIGHT_CHUNK; i++)
    {
        for(int j = 0; j < WIDTH_CHUNK; j++)
            out << secondo_livello_temp[i][j] << " ";
        out << endl;
    }
    out.close();
}

void Mappa::genera_destra()
{
    this->chunk_attuale++;

    ostringstream itos;
    itos << "save/chunk/" << this->chunk_attuale+1 << ".save";
    string temp = itos.str();

    this->genera_chunk_destra(temp);

    ofstream fout("save/map_info.save");
    fout << this->chunk_iniziale << " " << this->chunk_attuale << " " << this->chunk_finale+1 << endl;
    fout.close();

    this->preleva(this->chunk_attuale);
}

void Mappa::update()
{
    //cout << this->chunk_attuale << endl;
    //cout << (int)(coeff_movimento.x + WIDTH_WINDOW/2)/40 << endl;
    if(this->chunk_attuale-1 == this->chunk_iniziale && -((coeff_movimento.x - player.x)/40.0) <= 15)
    {
        this->salva(this->chunk_attuale);

        coeff_movimento.x -= (WIDTH_CHUNK)*WIDTH_BLOCK;

        this->genera_sinistra();
    }
    else if(this->chunk_attuale-1 != this->chunk_iniziale && -((coeff_movimento.x - player.x)/40.0) <= 15)
    {
        this->salva(this->chunk_attuale);

        ofstream fout("save/map_info.save");
        fout << this->chunk_iniziale << " " <<  (this->chunk_attuale)-1 << " " << this->chunk_finale;
        fout.close();

        coeff_movimento.x -= (WIDTH_CHUNK)*WIDTH_BLOCK;

        this->preleva(this->chunk_attuale-1);
    }

    if(this->chunk_attuale+1 == this->chunk_finale  && -((coeff_movimento.x - player.x)/40.0) >= 32)
    {
        this->salva(this->chunk_attuale);

        coeff_movimento.x += (WIDTH_CHUNK)*WIDTH_BLOCK;

        this->genera_destra();
    }
    else if(this->chunk_attuale+1 != this->chunk_finale && -((coeff_movimento.x - player.x)/40.0) >= 32)
    {
        this->salva(this->chunk_attuale);

        ofstream fout("save/map_info.save");
        fout << this->chunk_iniziale << " " << (this->chunk_attuale)+1 << " " << this->chunk_finale;
        fout.close();

        coeff_movimento.x += (WIDTH_CHUNK)*WIDTH_BLOCK;

        this->preleva(this->chunk_attuale+1);
    }

    this->disegna();
}

void Mappa::salva(int chunk)
{
    for(int k = chunk-1, m = 0; k <= chunk+1; k++, m++)
    {
        ostringstream itos;
        itos << "save/chunk/" << k << ".save";
        string temp = itos.str();

        ofstream out(temp);

        for(int i = 0; i < HEIGHT_CHUNK; i++)
        {
            for(int j = 0 + WIDTH_CHUNK*(m); j < WIDTH_CHUNK+ WIDTH_CHUNK*(m); j++)
                out << this->mappa[i][j] << " ";
            out << endl;
        }

        for(int i = 0; i < HEIGHT_CHUNK; i++)
        {
            for(int j = 0 + WIDTH_CHUNK*(m); j < WIDTH_CHUNK+ WIDTH_CHUNK*(m); j++)
                out << this->secondo_livello[i][j] << " ";
            out << endl;
        }
        out.close();
    }

    vector<Blocco_Droppato> precedente;
    vector<Blocco_Droppato> attuale;
    vector<Blocco_Droppato> successivo;

    for(int i = 0; i < blocchi_droppati.size(); i++)
    {
        int x = blocchi_droppati[i].x;

        if(x <= 16*WIDTH_BLOCK)
        {
            precedente.push_back({x, blocchi_droppati[i].y, blocchi_droppati[i].type});
        }
        else if(x <= 32*WIDTH_BLOCK)
        {
            x -= 16*WIDTH_BLOCK;

            attuale.push_back({x, blocchi_droppati[i].y, blocchi_droppati[i].type});
        }
        else if(x <= 48*WIDTH_BLOCK)
        {
            x -= 32*WIDTH_BLOCK;

            successivo.push_back({x, blocchi_droppati[i].y, blocchi_droppati[i].type});
        }

    }

    ostringstream itos0;
    itos0 << "save/drop_block/" << this->chunk_attuale-1 << ".save";
    string temp_precedente = itos0.str();

    ostringstream itos1;
    itos1 << "save/drop_block/" << this->chunk_attuale << ".save";
    string temp_attuale = itos1.str();

    ostringstream itos2;
    itos2 << "save/drop_block/" << this->chunk_attuale+1 << ".save";
    string temp_successivo = itos2.str();

    ofstream chunk_precedente(temp_precedente);
    ofstream chunk_attuale(temp_attuale);
    ofstream chunk_successivo(temp_successivo);

    chunk_precedente << precedente.size() << endl;
    for(int i = 0; i < precedente.size(); i++)
        chunk_precedente << precedente[i].x << " " << precedente[i].y << " " << precedente[i].type << endl;

    chunk_attuale << attuale.size() << endl;
    for(int i = 0; i < attuale.size(); i++)
        chunk_attuale << attuale[i].x << " " << attuale[i].y << " " << attuale[i].type << endl;

    chunk_successivo << successivo.size() << endl;
    for(int i = 0; i < successivo.size(); i++)
        chunk_successivo << successivo[i].x << " " << successivo[i].y << " " << successivo[i].type << endl;

    chunk_precedente.close();
    chunk_attuale.close();
    chunk_successivo.close();

    while(blocchi_droppati.size() > 0)
        blocchi_droppati.pop_back();

    while(precedente.size() > 0)
        precedente.pop_back();
    while(attuale.size() > 0)
        attuale.pop_back();
    while(successivo.size() > 0)
        successivo.pop_back();
}

void Mappa::preleva(int chunk)
{
    while(blocchi_droppati.size() > 0)
        blocchi_droppati.pop_back();

    ifstream in("save/map_info.save");
    in >> this->chunk_iniziale >> this->chunk_attuale >> this->chunk_finale;
    in.close();

    for(int k = chunk-1, m = 0; k <= chunk+1; k++, m++)
    {
        ostringstream itos;
        itos << "save/chunk/" << k << ".save";
        string temp = itos.str();

        ifstream in(temp);

        for(int i = 0; i < HEIGHT_CHUNK; i++)
            for(int j = 0 + WIDTH_CHUNK * m; j < WIDTH_CHUNK + WIDTH_CHUNK * m; j++)
                in >> this->mappa[i][j];

        for(int i = 0; i < HEIGHT_CHUNK; i++)
            for(int j = 0 + WIDTH_CHUNK * m; j < WIDTH_CHUNK + WIDTH_CHUNK * m; j++)
                in >> this->secondo_livello[i][j];

        in.close();
    }

    ostringstream itos0;
    itos0 << "save/drop_block/" << this->chunk_attuale-1 << ".save";
    string temp_precedente = itos0.str();

    ostringstream itos1;
    itos1 << "save/drop_block/" << this->chunk_attuale << ".save";
    string temp_attuale = itos1.str();

    ostringstream itos2;
    itos2 << "save/drop_block/" << this->chunk_attuale+1 << ".save";
    string temp_successivo = itos2.str();

    ifstream chunk_precedente(temp_precedente);
    ifstream chunk_attuale(temp_attuale);
    ifstream chunk_successivo(temp_successivo);

    int N = 0;
    chunk_precedente >> N;
    for(int i = 0; i < N; i++)
    {
        float x, y;
        int type;

        chunk_precedente >> x >> y >> type;

        blocchi_droppati.push_back({x, y, type});
    }

    N = 0;
    chunk_attuale >> N;
    for(int i = 0; i < N; i++)
    {
        float x, y;
        int type;

        chunk_attuale >> x >> y >> type;

        blocchi_droppati.push_back({x + 16*40, y, type});
    }

    N = 0;
    chunk_successivo >> N;
    for(int i = 0; i < N; i++)
    {
        float x, y;
        int type;

        chunk_successivo >> x >> y >> type;

        blocchi_droppati.push_back({x + 32*WIDTH_BLOCK, y, type});
    }
}

void Mappa::disegna()
{
    //draw_filled_rect(0,0,WIDTH_WINDOW, HEIGHT_WINDOW, Color(218,241,248, 255));

    gestione_cielo();

    for(int i = 0; i < HEIGHT_CHUNK; i++)
    {
        for(int j = 0; j < WIDTH_CHUNK*3; j++)
        {
            if(this->secondo_livello[i][j] != 0)
            {
                draw_image(blocchi[this->secondo_livello[i][j]].texture, j*WIDTH_BLOCK + coeff_movimento.x, i*HEIGHT_BLOCK + coeff_movimento.y, WIDTH_BLOCK, HEIGHT_BLOCK, 255);
                draw_filled_rect(j*WIDTH_BLOCK + coeff_movimento.x, i*HEIGHT_BLOCK + coeff_movimento.y, WIDTH_BLOCK, HEIGHT_BLOCK, Color(0,0,0,125));
            }

            if(this->mappa[i][j] != 0)
                draw_image(blocchi[this->mappa[i][j]].texture, j*WIDTH_BLOCK + coeff_movimento.x, i*HEIGHT_BLOCK + coeff_movimento.y, WIDTH_BLOCK, HEIGHT_BLOCK, 255);
        }
    }
//    for(int i = 0; i < HEIGHT_CHUNK; i++)
//    {
//        for(int j = 0; j < WIDTH_CHUNK*3; j++)
//        {
//            if(mappa[i][j] != 0 && mappa[i][j] != 4 &&  mappa[i][j] != 5)
//            {
//                if(mappa[i+1][j] == 0 || mappa[i-1][j] == 0 || mappa[i][j+1] == 0 || mappa[i][j-1] == 0)
//                    ;
//                else if(mappa[i-2][j] == 0 || mappa[i-2][j] == 4 || mappa[i-2][j] == 5)
//                    draw_image("image/ombra.png", j*WIDTH_BLOCK + coeff_movimento.x, i*HEIGHT_BLOCK + coeff_movimento.y, WIDTH_BLOCK, HEIGHT_BLOCK, 255);
//                else
//                    draw_filled_rect(j*WIDTH_BLOCK + coeff_movimento.x, i*HEIGHT_BLOCK + coeff_movimento.y, WIDTH_BLOCK, HEIGHT_BLOCK, Color(0,0,0,255));
//            }
//        }
//    }

//    for(int i = 0; i < 3; i++)
//        draw_rect(i*(WIDTH_CHUNK*40) + coeff_movimento.x, coeff_movimento.y, WIDTH_BLOCK*WIDTH_CHUNK, HEIGHT_BLOCK*HEIGHT_CHUNK, Color(255,0,0,255));

    draw_filled_rect(WIDTH_WINDOW/2-5, HEIGHT_WINDOW/2-5, 10, 10, Color(0,255,0,255));

}

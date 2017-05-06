class Mappa
{
private:
public:
    int mappa[HEIGHT_CHUNK][WIDTH_CHUNK*3];
    int secondo_livello[HEIGHT_CHUNK][WIDTH_CHUNK*3];
    double ombra[HEIGHT_CHUNK][WIDTH_CHUNK*3];

    int chunk_iniziale;
    int chunk_finale;
    int chunk_attuale;

    void creazione_ore_chunk(int y, int x, int coeff_casualita, int mappa[][WIDTH_CHUNK], int type_ore);
    void creazione_ore(int y, int x, int coeff_casualita, int type_ore);
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

#include "Sky/Sky.h"

void Mappa::creazione_ore(int y, int x, int coeff_casualita, int type_ore)
{
    this->mappa[y][x] = type_ore;

    if(rand()%100 >= coeff_casualita)
    {
        if(x < WIDTH_CHUNK*3-1)
            if(mappa[y][x+1] != 0)
                this->creazione_ore(y, x+1, coeff_casualita + rand()%15, type_ore);

        if(x > 0)
            if(mappa[y][x-1] != 0)
                this->creazione_ore(y, x-1, coeff_casualita + rand()%15, type_ore);

        if(y < HEIGHT_CHUNK-1)
            if(mappa[y+1][x] != 0)
                this->creazione_ore(y+1, x, coeff_casualita + rand()%15, type_ore);

        if(y > 0)
            if(mappa[y-1][x] != 0)
                this->creazione_ore(y-1, x, coeff_casualita + rand()%15, type_ore);
    }
}

void Mappa::creazione_ore_chunk(int y, int x, int coeff_casualita, int mappa[][WIDTH_CHUNK], int type_ore)
{
    mappa[y][x] = type_ore;

    if(rand()%100 >= coeff_casualita)
    {
        if(x < WIDTH_CHUNK-1)
            if(mappa[y][x+1] != 0)
                this->creazione_ore_chunk(y, x+1, coeff_casualita + rand()%15, mappa, type_ore);

        if(x > 0)
            if(mappa[y][x-1] != 0)
                this->creazione_ore_chunk(y, x-1, coeff_casualita + rand()%15, mappa, type_ore);

        if(y < HEIGHT_CHUNK-1)
            if(mappa[y+1][x] != 0)
                this->creazione_ore_chunk(y+1, x, coeff_casualita + rand()%15, mappa, type_ore);

        if(y > 0)
            if(mappa[y-1][x] != 0)
                this->creazione_ore_chunk(y-1, x, coeff_casualita + rand()%15, mappa, type_ore);
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

    // CREAZIONE DI UN GIACIMENTO DI COAL (CARBONE)
    for(int i = 0; i < WIDTH_CHUNK*3; i++)
    {
        if(rand()%100 >= 95)
        {
            int altezza = 55 + rand()%20;
            while(this->mappa[altezza][i] != STONE)
                altezza++;

            this->creazione_ore(altezza, i, 50, COAL_ORE);
        }
    }

    ofstream out("save/map_info.save");
    out << -1 << " " << 0 << " " << 1 << endl;
    out.close();

    ofstream player_info("save/player_info.save");
    player_info << coeff_movimento.x << " " << coeff_movimento.y << endl;

    for(int i = 0; i < HEIGHT_INVENTORY; i++)
    {
        for(int j = 0; j < WIDTH_INVENTORY; j++)
            player_info << player.inventario[i][j].blocco.id << " "
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

    // CREAZIONE DI UN GIACIMENTO DI COAL (CARBONE)
    for(int i = 0; i < WIDTH_CHUNK*3; i++)
    {
        if(rand()%100 >= 95)
        {
            int altezza = 55 + rand()%20;
            while(mappa_temp[altezza][i] != STONE)
                altezza++;

            this->creazione_ore_chunk(altezza, i, 50, mappa_temp,COAL_ORE);
        }
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

    // CREAZIONE DI UN GIACIMENTO DI COAL (CARBONE)
    for(int i = 0; i < WIDTH_CHUNK*3; i++)
    {
        if(rand()%100 >= 95)
        {
            int altezza = 55 + rand()%20;
            while(mappa_temp[altezza][i] != STONE)
                altezza++;

            this->creazione_ore_chunk(altezza, i, 50, mappa_temp,COAL_ORE);
        }
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
            precedente.push_back({x, blocchi_droppati[i].y, blocchi_droppati[i].blocco});
        }
        else if(x <= 32*WIDTH_BLOCK)
        {
            x -= 16*WIDTH_BLOCK;

            attuale.push_back({x, blocchi_droppati[i].y, blocchi_droppati[i].blocco});
        }
        else if(x <= 48*WIDTH_BLOCK)
        {
            x -= 32*WIDTH_BLOCK;

            successivo.push_back({x, blocchi_droppati[i].y, blocchi_droppati[i].blocco});
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
        chunk_precedente << precedente[i].x << " " << precedente[i].y << " "
        << precedente[i].blocco.id << " "
        << precedente[i].blocco.texture << " "
        << precedente[i].blocco.blocco << " "
        << precedente[i].blocco.strumento << " "
        << precedente[i].blocco.distruggi << " "
        << precedente[i].blocco.trasparenza << " "
        << precedente[i].blocco.secondi << " "
        << precedente[i].blocco.da_oggetto << " "
        << precedente[i].blocco.a_oggetto << " "
        << precedente[i].blocco.percentuale_senza_strumento << " "
        << precedente[i].blocco.oggetto_droppato_senza_strumento << " "
        << precedente[i].blocco.percentuale_strumento << " "
        << precedente[i].blocco.oggetto_droppato_strumento << " "
        << precedente[i].blocco.durabilita << " "
        << precedente[i].blocco.massima_stoccabilita << endl;

    chunk_attuale << attuale.size() << endl;
    for(int i = 0; i < attuale.size(); i++)
        chunk_attuale << attuale[i].x << " " << attuale[i].y << " "
        << attuale[i].blocco.id << " "
        << attuale[i].blocco.texture << " "
        << attuale[i].blocco.blocco << " "
        << attuale[i].blocco.strumento << " "
        << attuale[i].blocco.distruggi << " "
        << attuale[i].blocco.trasparenza << " "
        << attuale[i].blocco.secondi << " "
        << attuale[i].blocco.da_oggetto << " "
        << attuale[i].blocco.a_oggetto << " "
        << attuale[i].blocco.percentuale_senza_strumento << " "
        << attuale[i].blocco.oggetto_droppato_senza_strumento << " "
        << attuale[i].blocco.percentuale_strumento << " "
        << attuale[i].blocco.oggetto_droppato_strumento << " "
        << attuale[i].blocco.durabilita << " "
        << attuale[i].blocco.massima_stoccabilita << endl;

    chunk_successivo << successivo.size() << endl;
    for(int i = 0; i < successivo.size(); i++)
        chunk_successivo << successivo[i].x << " " << successivo[i].y << " "
        << successivo[i].blocco.id << " "
        << successivo[i].blocco.texture << " "
        << successivo[i].blocco.blocco << " "
        << successivo[i].blocco.strumento << " "
        << successivo[i].blocco.distruggi << " "
        << successivo[i].blocco.trasparenza << " "
        << successivo[i].blocco.secondi << " "
        << successivo[i].blocco.da_oggetto << " "
        << successivo[i].blocco.a_oggetto << " "
        << successivo[i].blocco.percentuale_senza_strumento << " "
        << successivo[i].blocco.oggetto_droppato_senza_strumento << " "
        << successivo[i].blocco.percentuale_strumento << " "
        << successivo[i].blocco.oggetto_droppato_strumento << " "
        << successivo[i].blocco.durabilita << " "
        << successivo[i].blocco.massima_stoccabilita << endl;

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
        Blocco blocco;

        chunk_precedente >> x >> y
        >> blocco.id
        >> blocco.texture
        >> blocco.blocco
        >> blocco.strumento
        >> blocco.distruggi
        >> blocco.trasparenza
        >> blocco.secondi
        >> blocco.da_oggetto
        >> blocco.a_oggetto
        >> blocco.percentuale_senza_strumento
        >> blocco.oggetto_droppato_senza_strumento
        >> blocco.percentuale_strumento
        >> blocco.oggetto_droppato_strumento
        >> blocco.durabilita
        >> blocco.massima_stoccabilita;
        blocchi_droppati.push_back({x, y, blocco});
    }

    N = 0;
    chunk_attuale >> N;
    for(int i = 0; i < N; i++)
    {
        float x, y;
        Blocco blocco;

        chunk_attuale>> x >> y
        >> blocco.id
        >> blocco.texture
        >> blocco.blocco
        >> blocco.strumento
        >> blocco.distruggi
        >> blocco.trasparenza
        >> blocco.secondi
        >> blocco.da_oggetto
        >> blocco.a_oggetto
        >> blocco.percentuale_senza_strumento
        >> blocco.oggetto_droppato_senza_strumento
        >> blocco.percentuale_strumento
        >> blocco.oggetto_droppato_strumento
        >> blocco.durabilita
        >> blocco.massima_stoccabilita;
        blocchi_droppati.push_back({x + 16*40, y, blocco});
    }

    N = 0;
    chunk_successivo >> N;
    for(int i = 0; i < N; i++)
    {
        float x, y;
        Blocco blocco;

        chunk_successivo >> x >> y
        >> blocco.id
        >> blocco.texture
        >> blocco.blocco
        >> blocco.strumento
        >> blocco.distruggi
        >> blocco.trasparenza
        >> blocco.secondi
        >> blocco.da_oggetto
        >> blocco.a_oggetto
        >> blocco.percentuale_senza_strumento
        >> blocco.oggetto_droppato_senza_strumento
        >> blocco.percentuale_strumento
        >> blocco.oggetto_droppato_strumento
        >> blocco.durabilita
        >> blocco.massima_stoccabilita;
        blocchi_droppati.push_back({x + 32*40, y, blocco});
    }
}

void Mappa::disegna()
{
    //draw_filled_rect(0,0,WIDTH_WINDOW, HEIGHT_WINDOW, Color(218,241,248, 255));

    gestione_ombra();

    for(int i = player.inizio_finestra_y; i < player.fine_finestra_y; i++)
    {
        for(int j =  player.inizio_finestra_x; j <  player.fine_finestra_x; j++)
        {
            if(this->ombra[i][j] > 0)
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
    }

    disegna_ombra();

//    for(int i = 0; i < 3; i++)
//        draw_rect(i*(WIDTH_CHUNK*40) + coeff_movimento.x, coeff_movimento.y, WIDTH_BLOCK*WIDTH_CHUNK, HEIGHT_BLOCK*HEIGHT_CHUNK, Color(255,0,0,255));

}

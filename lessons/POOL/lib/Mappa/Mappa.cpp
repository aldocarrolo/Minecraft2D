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
#include "Tree/Tree.h"

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
        {
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
        }

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

    gestione_alberi();

    this->disegna();
}

void salva_blocchi_droppati(string file_name, vector<Blocco_Droppato> blocchi_droppati)
{
    ofstream out(file_name);

    out << blocchi_droppati.size() << endl;
    for(int i = 0; i < blocchi_droppati.size(); i++)
    {
        out << blocchi_droppati[i].x << " " << blocchi_droppati[i].y << " "
        << blocchi_droppati[i].blocco.id << " "
        << blocchi_droppati[i].blocco.texture << " "
        << blocchi_droppati[i].blocco.blocco << " "
        << blocchi_droppati[i].blocco.strumento << " "
        << blocchi_droppati[i].blocco.distruggi << " "
        << blocchi_droppati[i].blocco.trasparenza << " "
        << blocchi_droppati[i].blocco.secondi << " "
        << blocchi_droppati[i].blocco.da_oggetto << " "
        << blocchi_droppati[i].blocco.a_oggetto << " "
        << blocchi_droppati[i].blocco.percentuale_senza_strumento << " "
        << blocchi_droppati[i].blocco.oggetto_droppato_senza_strumento << " "
        << blocchi_droppati[i].blocco.percentuale_strumento << " "
        << blocchi_droppati[i].blocco.oggetto_droppato_strumento << " "
        << blocchi_droppati[i].blocco.durabilita << " "
        << blocchi_droppati[i].blocco.massima_stoccabilita << endl;
    }

    out.close();
}

void preleva_blocchi_droppati(string file_name, int chunk)
{
    ifstream in(file_name);

    int N = 0;
    in >> N;
    for(int i = 0; i < N; i++)
    {
        float x, y;
        Blocco blocco;

        in >> x >> y
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
        blocchi_droppati.push_back({x + (16*chunk)*40, y, blocco});
    }

    in.close();
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

    string temp_precedente = "save/drop_block/" + int_to_string(this->chunk_attuale-1) + ".save";
    string temp_attuale = "save/drop_block/" + int_to_string(this->chunk_attuale) + ".save";
    string temp_successivo = "save/drop_block/" + int_to_string(this->chunk_attuale+1) + ".save";

    salva_blocchi_droppati(temp_precedente, precedente);
    salva_blocchi_droppati(temp_attuale, attuale);
    salva_blocchi_droppati(temp_successivo, successivo);

    while(blocchi_droppati.size() > 0)
        blocchi_droppati.pop_back();


    vector<Tree> tree_precedente;
    vector<Tree> tree_attuale;
    vector<Tree> tree_successivo;

    for(int i = 0; i < alberi.size(); i++)
    {
        int x = alberi[i].x;

        if(x < 16)
        {
            tree_precedente.push_back({x, alberi[i].y, alberi[i].tempo_passato});
        }
        else if(x < 32)
        {
            tree_attuale.push_back({x, alberi[i].y, alberi[i].tempo_passato});
        }
        else if(x < 48)
        {
            tree_successivo.push_back({x, alberi[i].y, alberi[i].tempo_passato});
        }

    }

    string tree_temp_precedente = "save/tree/" + int_to_string(this->chunk_attuale-1) + ".save";
    string tree_temp_attuale = "save/tree/" + int_to_string(this->chunk_attuale) + ".save";
    string tree_temp_successivo = "save/tree/" + int_to_string(this->chunk_attuale+1) + ".save";

    salva_alberi(tree_temp_precedente, tree_precedente);
    salva_alberi(tree_temp_attuale, tree_attuale);
    salva_alberi(tree_temp_successivo, tree_successivo);

    while(alberi.size() > 0)
        alberi.pop_back();
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

    string temp_precedente = "save/drop_block/" + int_to_string(this->chunk_attuale-1) + ".save";
    string temp_attuale = "save/drop_block/" + int_to_string(this->chunk_attuale) + ".save";
    string temp_successivo = "save/drop_block/" + int_to_string(this->chunk_attuale+1) + ".save";

    preleva_blocchi_droppati(temp_precedente,0);
    preleva_blocchi_droppati(temp_attuale,1);
    preleva_blocchi_droppati(temp_successivo,2);

    string tree_temp_precedente = "save/tree/" + int_to_string(this->chunk_attuale-1) + ".save";
    string tree_temp_attuale = "save/tree/" + int_to_string(this->chunk_attuale) + ".save";
    string tree_temp_successivo = "save/tree/" + int_to_string(this->chunk_attuale+1) + ".save";

    preleva_alberi(tree_temp_precedente,0);
    preleva_alberi(tree_temp_attuale,1);
    preleva_alberi(tree_temp_successivo,2);
}

void Mappa::disegna()
{
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
}

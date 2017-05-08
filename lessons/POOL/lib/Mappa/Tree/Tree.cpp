void preleva_alberi(string file_name, int chunk)
{
    ifstream in(file_name);

    int N = 0;
    in >> N;

    for(int i = 0; i < N; i++)
    {
        Tree temp;
        in >> temp.x >> temp.y >> temp.tempo_passato;

        temp.x += 16*chunk;

        alberi.push_back(temp);
    }

    in.close();
}

void salva_alberi(string file_name, vector<Tree> alberi)
{
    ofstream out(file_name);

    out << alberi.size() << endl;
    for(int i = 0; i < alberi.size(); i++)
        out << alberi[i].x << " " << alberi[i].y << " " << alberi[i].tempo_passato << endl;

    out.close();
}

void gestione_alberi()
{
    static bool incrementatore = false;
    static bool controllo = false;

    for(int i = 0; i < alberi.size(); i++)
    {
        if(mappa.mappa[alberi[i].y][alberi[i].x] != OAK_SAPLING)
        {
            alberi.erase(alberi.begin()+i);
            i--;
            continue;
        }

        if(incrementatore == false && (ms_time()/1000)%2 == 0 && mappa.mappa[alberi[i].y+1][alberi[i].x] != 0)
        {
            alberi[i].tempo_passato++;

            controllo = true;
        }

        if(incrementatore == true && (ms_time()/1000)%2 == 1)
        {
            controllo = false;
        }

        if(alberi[i].tempo_passato >= 30)
        {

            int altezza_attuale = alberi[i].y+1;

            mappa.mappa[alberi[i].y][alberi[i].x] = OAK_WOOD;
            mappa.mappa[alberi[i].y+1][alberi[i].x] = DIRT;

            for(int k = 0; k < 6; k++)
                for(int m = 0; m < 5; m++)
                    if(mappa.mappa[altezza_attuale - 6 + k][alberi[i].x - 2 + m] == 0 && albero[k][m] != 0)
                        mappa.mappa[altezza_attuale - 6 + k][alberi[i].x - 2 + m] = albero[k][m];
            alberi.erase(alberi.begin()+i);
            i--;
        }
    }

    if(controllo == true)
        incrementatore = true;
    else
        incrementatore = false;
}

#include <bits/stdc++.h>

using namespace std;

class Examen
{
    static int contor_id_examen;
    int id_examen;
    string materie;
    float nota_scris;

public:
    Examen(string materie = "", float nota = 0.00);
    Examen(const Examen&);
    virtual ~Examen();
    virtual void afisare();
    virtual void citire();
    string get_materie()const;
    int get_id_examen()const;
    float get_nota_scris()const;
    void set_id_examen(const int);
    void set_materie(const string);
    //void set_nota_scris(const float);
    template <typename T> void set_nota_scris(T nota)
    {
        if(nota>=0 && nota<=10)
            nota_scris = nota;
    }
    Examen operator=(const Examen&);
    friend istream& operator>>(istream &fin, Examen &examen);
    friend ostream& operator<<(ostream &gout, const Examen &examen);
    void verifica_nota_scris();
    static void schimba_contor();
    virtual float get_media();
};

/// ---------------------------------------------------------------------------------------------------------

class Partial:public Examen
{
    float nota_oral;

public:
    Partial(string materie = "", float nota_scris = 0.00, float nota_oral = 0.00);
    Partial(const Partial&);
    virtual ~Partial();
    virtual void afisare() override
    {

        cout<<"Pentru examenul cu id-ul "<<get_id_examen()<<" la materia "
                <<get_materie()<<" nota la scris este: "<<get_nota_scris()<<", iar nota la oral este: "<<nota_oral<<" .\n";
    }
    virtual void citire() override
    {
        Examen::citire();
        cout<<"Introduceti nota la oral: ";
        cin>>nota_oral;
        try
        {
            verifica_nota_oral();
        }
        catch(int)
        {
            cout<<"Nota la oral introdusa gresit!!\n";
            cout<<"Introduceti o nota corecta: ";
            cin>>nota_oral;
        }
        catch(...)
        {
            cout<<"Nota oral gresita!!";
            cout<<"Introduceti o nota corecta: ";
            cin>>nota_oral;
        }
    }
    float get_nota_oral() const;
    template <typename T> void set_nota_oral(T nota)
    {
        if(nota >= 0 && nota <= 10)
            nota_oral = nota;
    }
    void verifica_nota_oral();
    Partial operator=(const Partial&);
    friend istream& operator>>(istream &fin, Partial &partial);
    friend ostream& operator<<(ostream &gout, const Partial &partial);
    virtual float get_media() override
    {
        return nota_oral;
    }
};

/// -------------------------------------------------------------------------------------------------------------------

class Examen_final:public Partial
{
    float puncte_bonus;
public:
    Examen_final(string materie = "", float nota_scris = 0.00, float nota_oral = 0.00, float puncte_bonus = 0.00);
    Examen_final(const Examen_final &);
    virtual ~Examen_final();
    float calculeaza_media();
    virtual void afisare() override
    {
        cout<<"Pentru examenul cu id-ul "<<get_id_examen()<<" la materia "
                <<get_materie()<<" nota la scris este: "<<get_nota_scris()<<", iar nota la oral este: "<<get_nota_oral()<<", punctele bonus sunt "<<puncte_bonus<<", ";
        cout<<"media scris + oral este "<<calculeaza_media()<<" .\n";
    }
    virtual void citire() override
    {
        Partial::citire();
        cout<<"Dati punctele bonus: ";
        cin>>puncte_bonus;
        try
        {
            verfica_puncte_bonus();
        }
        catch(int)
        {
            cout<<"Prea multe puncte bonus!!\n";
            cout<<"Dati alt numar de puncte bonus: ";
            cin>>puncte_bonus;
        }
        catch(...)
        {
            cout<<"Prea multe puncte bonus!!\n";
            cout<<"Dati alt numar de puncte bonus: ";
            cin>>puncte_bonus;
        }
    }
    float get_puncte_bonus() const;
    void set_puncte_bonus(float);
    void verfica_puncte_bonus();
    Examen_final operator=(const Examen_final &);
    friend istream& operator>>(istream &fin, Examen_final &examen);
    friend ostream& operator<<(ostream &gout, Examen_final &examen);
    virtual float get_media() override
    {
        return calculeaza_media();
    }
};

/// ----------------------------------------------------------------------------------------------------------

class Quizz:public Examen_final
{
    int nr_itemi;
    float nota_quizz;

public:
    Quizz(string materie = "", float nota_scris = 0.00, float nota_oral = 0.00, float puncte_bonus = 0.00, int nr = 15, float nota = 0.00);
    Quizz(const Quizz&);
    ~Quizz();
    virtual void afisare() override
    {
        cout<<"Pentru examenul cu id-ul "<<get_id_examen()<<" la materia "
                <<get_materie()<<" nota la scris este: "<<get_nota_scris()<<", iar nota la oral este: "<<get_nota_oral()<<", punctele bonus sunt "<<get_puncte_bonus()<<", ";
        cout<<"media scris + oral este "<<calculeaza_media()<<", ";
        cout<<"nota la quizz pt marire este "<<nota_quizz<<", ";
        cout<<"media dupa marire este "<<calculeaza_media_cu_marire()<<" .\n";
    }
    virtual void citire() override
    {
        Examen_final::citire();
        cout<<"Dati numarul de itemi din quizz: ";
        cin>>nr_itemi;
        cout<<"Introduceti nota quizz: ";
        cin>>nota_quizz;
    }
    void set_nota_quizz(float);
    float get_nota_quizz() const;
    float calculeaza_media_cu_marire();
    Quizz operator=(const Quizz&);
    friend istream& operator>>(istream &fin, Quizz &);
    friend ostream& operator<<(ostream &gout, Quizz &);
    virtual float get_media() override
    {
        return calculeaza_media_cu_marire();
    }
};

/// -------------------------------------------------------------------------------------------------------------

template<class T>
class Catalog_Individual;

template<class T>
istream& operator>>(istream &fin, Catalog_Individual<T>&ob);

template<class T>
ostream& operator<<(ostream &gout, Catalog_Individual<T> &ob);

template<class T>
class Catalog_Individual
{
    int nr_matricol;
    static int contor_matricol;
    int nr_examen_curent;
    vector<T> structura_date;
    //static vector<string> studenti_care_nu_au_trecut_examene;
    static unordered_map<int, vector<string>> umap;

public:
    Catalog_Individual();
    Catalog_Individual(const Catalog_Individual&);
    ~Catalog_Individual();
    Catalog_Individual operator=(const Catalog_Individual&);
    friend istream& operator>> <>(istream &fin, Catalog_Individual<T>&ob);
    friend ostream& operator<< <>(ostream &gout, Catalog_Individual<T> &ob);
    void afisare();
    int get_nr_matricol();
    int get_nr_examene();
    Catalog_Individual operator+=(const T &examen);
    //void set_lista_cu_examene_picate(string nume_student);
    void set_umapul_cu_studentii_picati(string);
    void afiseaza_umapul_cu_sudentii_picati();

};

/// --------------------------------------------------------------------------------------------------------------

template <>
class Catalog_Individual<Quizz>;

template<>
istream& operator>>(istream &fin, Catalog_Individual<Quizz>&ob);

template<>
ostream& operator<<(ostream &gout, Catalog_Individual<Quizz> &ob);

template<>
class Catalog_Individual <Quizz>
{
    int nr_quizzuri;
    int nr_matricol;
    static int contor_matricol;
    int nr_examen_curent;
    vector<Quizz> structura_date;
    static unordered_set <string> elevi;//studentii care au dat cel putin 2 quizzuri


public:
    Catalog_Individual();
    Catalog_Individual(const Catalog_Individual&);
    ~Catalog_Individual();
    Catalog_Individual operator=(const Catalog_Individual&);
    friend istream& operator>> <>(istream &fin, Catalog_Individual<Quizz>&ob);
    friend ostream& operator<< <>(ostream &gout, Catalog_Individual<Quizz> &ob);
    void afisare();
    int get_nr_matricol();
    int get_nr_examene();
    Catalog_Individual operator+=(const Quizz &examen);
    void creste_nr_quizzuri();
    void set_studentii_care_au_2quizzuri(string, int);
    void afiseaza_sudentii_care_au_dat_2quizzuri();


};

/// --------------------------------------------------------------------------------------------------------------

class Elev
{
    string nume;
    int nr_examene;
    int grupa;
    int nr_quizzuri_date;
    Catalog_Individual<Examen>examene;
    Catalog_Individual<Partial>partiale;
    Catalog_Individual<Examen_final>examene_finale;
    Catalog_Individual<Quizz>quizzuri;

public:
    Elev(string nume = "",  int grupa = 0, int nr_examene = 0);
    Elev(const Elev&);
    ~Elev();
    string get_nume()const;
    void set_nume(const string);
    int get_nr_examene()const;
    void set_nr_examene(int);
    void set_nr_examene();
    int get_grupa()const;
    void set_grupa(int);
    Elev operator=(const Elev&);
    friend istream& operator>>(istream &fin, Elev &);
    friend ostream& operator<<(ostream &gout, Elev &);
    void adauga_examen(Examen);
    void adauga_partial(Partial);
    void adauga_examen_final(Examen_final);
    void adauga_quizz(Quizz);
    void set_partiale_picate();
    void afiseaza_partialele_picate();
    void set_examene();
    void afiseaza_examenele_picate();
    void set_examene_finale();
    void afiseaza_examenele_finale();
    void set_quizzuri();
    void afiseaza_quizzurile();
    int get_nr_quizzuri()const;
    Elev* memorare_afisare_n_obiecte();

};

//========================================================================================

void meniu()
{
    Elev e;
    e.memorare_afisare_n_obiecte();
}

//========================================================================================

int main()
{
//    Examen ex1, ex2;
//    cin >> ex1;
//    //cout << ex1;
//    ex1.afisare();
//
//    ex2.citire();
//    ex2.afisare();
//
//    Partial part;
//    //part.citire();
//    cin >> part;
//    cout << part;

//    Quizz ex, pl, ex1;
//    cin >> ex;
//    cout << ex;
//
//    pl = ex;
//    pl.afisare();
//
//    ex1.citire();
//    ex1.afisare();

/// ======================================================
    meniu();
/// ======================================================

    return 0;
}

/// Clasa Examen ----------------------------------------------------------------------------------------------

int Examen::contor_id_examen = 0;

void Examen::schimba_contor()
{
    if(contor_id_examen>20)
    {
        contor_id_examen = 0;
    }
}

Examen::Examen(string materie, float nota):materie(materie), nota_scris(nota)
{
    contor_id_examen++;
    id_examen = contor_id_examen;
}

Examen::Examen(const Examen &o)
{
    set_id_examen(o.id_examen);
    set_materie(o.materie);
    nota_scris = o.nota_scris;
}

Examen::~Examen()
{
    id_examen = 0;
    materie.clear();
    nota_scris = 0.00;
}

string Examen::get_materie() const
{
    return materie;
}

int Examen::get_id_examen()const
{
    return id_examen;
}

float Examen::get_nota_scris()const
{
    return nota_scris;
}

void Examen::set_id_examen(const int id)
{
    id_examen = id;
}
/*
void Examen::set_nota_scris(const float nota)
{
    if(nota>=0 && nota<=10)
        nota_scris = nota;
}
*/
void Examen::set_materie(const string materie)
{
    this->materie = materie;
}

Examen Examen::operator=(const Examen& examen)
{
    if(this != &examen)
    {
        id_examen = examen.id_examen;
        nota_scris = examen.nota_scris;
        materie =  examen.materie;
    }
    return *this;
}

ostream& operator<<(ostream &gout, const Examen &examen)
{
    gout<<"Pentru examenul cu id-ul ";
    gout << examen.id_examen;
    gout<<" la materia ";
    gout<<examen.materie;
    gout<<" nota la scris este: ";
    gout<<examen.nota_scris;
    gout<<" .\n";
    return gout;

}
void Examen::verifica_nota_scris()
{
    if(nota_scris>10 || nota_scris<0)
        throw 0;
}

istream& operator>>(istream &fin, Examen &examen)
{

    cout<<"Introduceti materia: ";
    fin>>examen.materie;
    cout<<"Introduceti nota la scris: ";
    fin>>examen.nota_scris;
    try
    {
        examen.verifica_nota_scris();
    }
    catch(int)
    {
        cout<<"Nota gresit introdusa!\n";
        cout<<"Mai introduceti inca o data o nota corecta: ";
        fin>>examen.nota_scris;
    }
    catch(...)
    {
        cout<<"Nota gresita\n";
        cout<<"Mai introduceti inca o data o nota corecta: ";
        fin>>examen.nota_scris;
    }
    return fin;
}

float Examen::get_media()
{
    return nota_scris;
}
void Examen::afisare()
{
    cout<<"Pentru examenul cu id-ul ";
    cout << id_examen;
    cout<<" la materia ";
    cout<<materie;
    cout<<" nota la scris este:";
    cout<<nota_scris;
    cout<<" .\n";
}
void Examen::citire()
{
    cout<<"Introduceti materia: ";
    cin>>this->materie;
    cout<<"Introduceti nota la scris: ";
    cin>>this->nota_scris;
    try
    {
        this->verifica_nota_scris();
    }
    catch(int)
    {
        cout<<"Nota gresit introdusa!\n";
        cout<<"Mai introduceti inca o data o nota corecta: ";
        cin>>this->nota_scris;
    }
    catch(...)
    {
        cout<<"Nota gresita\n";
        cout<<"Mai introduceti inca o data o nota corecta: ";
        cin>>this->nota_scris;
    }
}
/// Clasa Partial ----------------------------------------------------------------------------------------------

Partial::Partial(string materie1, float nota_scris1, float nota_oral1):Examen(materie1,nota_scris1), nota_oral(nota_oral1)
{

}

Partial::Partial(const Partial &o)
{
    set_id_examen(o.get_id_examen());
    set_materie(o.get_materie());
    set_nota_scris<float>(o.get_nota_scris());
    nota_oral = o.nota_oral;

}

Partial::~Partial()
{
    nota_oral = 0.00;
}

float Partial::get_nota_oral() const
{
    return nota_oral;
}
/*
void Partial::set_nota_oral(float nota)
{
    if(nota>=0 && nota<=10)
        nota_oral = nota;
}
*/
Partial Partial::operator=(const Partial& partial)
{
    if(this != &partial)
    {
        nota_oral=partial.nota_oral;
        set_nota_scris<float>(partial.get_nota_scris());
        set_materie(partial.get_materie());
        set_id_examen(partial.get_id_examen());
    }
    return *this;
}

void Partial::verifica_nota_oral()
{
    if(nota_oral < 0 || nota_oral > 10)
        throw 0;
}

istream& operator>>(istream &fin, Partial &partial)
{

    fin>>dynamic_cast<Examen&>(partial);
    cout<<"Introduceti nota la oral: ";
    fin>>partial.nota_oral;
    try
    {
        partial.verifica_nota_oral();
    }
    catch(int)
    {
        cout<<"Nota la oral introdusa gresit!!\n";
        cout<<"Introduceti o nota corecta: ";
        fin>>partial.nota_oral;
    }
    catch(...)
    {
        cout<<"Nota oral gresita!!";
        cout<<"Introduceti o nota corecta: ";
        fin>>partial.nota_oral;
    }

    return fin;
}
ostream& operator<<(ostream& gout,const Partial &partial)
{
    gout<<"Pentru examenul cu id-ul "<<partial.get_id_examen()<<" la materia "
                <<partial.get_materie()<<" nota la scris este: "<<partial.get_nota_scris()<<", iar nota la oral este: "<<partial.nota_oral<<" .\n";
    return gout;
}
/// Clasa Examen_final

Examen_final::Examen_final(string materie, float nota_scris, float nota_oral, float puncte_bonus):Partial(materie, nota_scris, nota_oral), puncte_bonus(puncte_bonus)
{

}

Examen_final::Examen_final(const Examen_final& o)
{

    set_nota_oral<float>(o.get_nota_oral());
    set_nota_scris<float>(o.get_nota_scris());
    set_materie(o.get_materie());
    set_id_examen(o.get_id_examen());
    puncte_bonus = o.puncte_bonus;

}

Examen_final::~Examen_final()
{
    puncte_bonus = 0.00;
}

Examen_final Examen_final::operator=(const Examen_final& o)
{
    if(this != &o)
    {
        set_nota_oral<float>(o.get_nota_oral());
        set_nota_scris<float>(o.get_nota_scris());
        set_materie(o.get_materie());
        set_id_examen(o.get_id_examen());
        puncte_bonus = o.puncte_bonus;

    }
    return *this;
}

float Examen_final::calculeaza_media()
{
    return (get_nota_oral()+get_nota_scris())/2 + puncte_bonus;
}

float Examen_final::get_puncte_bonus() const
{
    return puncte_bonus;
}

void Examen_final::set_puncte_bonus(float puncte_bonus1)
{
    puncte_bonus = puncte_bonus1;
}

void Examen_final::verfica_puncte_bonus()
{
    if(calculeaza_media() > 10)
    {
        puncte_bonus = 10 - calculeaza_media();
        throw 0;
    }
}

istream& operator>>(istream &fin, Examen_final &examen)
{
    fin>>dynamic_cast<Partial&>(examen);
    cout<<"Dati punctele bonus: ";
    fin>>examen.puncte_bonus;
    try
    {
        examen.verfica_puncte_bonus();
    }
    catch(int)
    {
        cout<<"Prea multe puncte bonus!!\n";
        cout<<"Dati alt numar de puncte bonus: ";
        fin>>examen.puncte_bonus;
    }
    catch(...)
    {
        cout<<"Prea multe puncte bonus!!\n";
        cout<<"Dati alt numar de puncte bonus: ";
        fin>>examen.puncte_bonus;
    }
    return fin;
}
ostream& operator<<(ostream &gout, Examen_final &examen)
{
    gout<<"Pentru examenul cu id-ul "<<examen.get_id_examen()<<" la materia "
                <<examen.get_materie()<<" nota la scris este: "<<examen.get_nota_scris()<<", iar nota la oral este: "<<examen.get_nota_oral()<<", punctele bonus sunt "<<examen.puncte_bonus<<", ";
    gout<<"media scris + oral este "<<examen.calculeaza_media()<<" .\n";
    return gout;
}
/// Class Quizz
Quizz::Quizz(string materie, float nota_scris, float nota_oral, float puncte_bonus, int nr, float nota):Examen_final(materie,nota_scris,nota_oral,puncte_bonus), nr_itemi(nr), nota_quizz(nota)
{

}

Quizz::Quizz(const Quizz &o)
{
    set_nota_oral<float>(o.get_nota_oral());
    set_nota_scris<float>(o.get_nota_scris());
    set_materie(o.get_materie());
    set_id_examen(o.get_id_examen());
    set_puncte_bonus(o.get_puncte_bonus());
    nr_itemi = o.nr_itemi;
    nota_quizz = o.nota_quizz;
}

Quizz::~Quizz()
{
    nr_itemi = 0;
    nota_quizz = 0.00;
}

Quizz Quizz::operator=(const Quizz &o)
{
    if(this != &o)
    {
        set_nota_oral<float>(o.get_nota_oral());
        set_nota_scris<float>(o.get_nota_scris());
        set_materie(o.get_materie());
        set_id_examen(o.get_id_examen());
        set_puncte_bonus(o.get_puncte_bonus());
        nr_itemi = o.nr_itemi;
        nota_quizz = o.nota_quizz;
    }
    return *this;
}

void Quizz::set_nota_quizz(float nota)
{
    nota_quizz = nota;
}

float Quizz::get_nota_quizz()const
{
    return nota_quizz;
}

float Quizz::calculeaza_media_cu_marire()
{
    return (calculeaza_media() + nota_quizz)/2;
}

istream& operator>>(istream &fin, Quizz &ob)
{
    fin>>dynamic_cast<Examen_final&>(ob);
    cout<<"Dati numarul de itemi din quizz: ";
    fin>>ob.nr_itemi;
    cout<<"Introduceti nota quizz: ";
    fin>>ob.nota_quizz;
    return fin;
}

ostream& operator<<(ostream &gout, Quizz &ob)
{
    gout<<"Pentru examenul cu id-ul "<<ob.get_id_examen()<<" la materia "
                <<ob.get_materie()<<" nota la scris este: "<<ob.get_nota_scris()<<", iar nota la oral este: "<<ob.get_nota_oral()
                    <<", punctele bonus sunt "<<ob.get_puncte_bonus()<<", ";
    gout<<"media scris + oral este "<<ob.calculeaza_media()<<", ";
    gout<<"nota la quizz pt marire este "<<ob.nota_quizz<<", ";
    gout<<"media dupa marire este "<<ob.calculeaza_media_cu_marire()<<" .\n";
}
/// Class template Catalog_individual<>

template <class  T>
int Catalog_Individual<T>::contor_matricol = 0;

template <class T>
Catalog_Individual<T>::Catalog_Individual()
{
    contor_matricol++;
    nr_examen_curent = 0;
    nr_matricol = contor_matricol;

}

template <class T>
Catalog_Individual<T>::Catalog_Individual(const Catalog_Individual& ob)
{
    nr_matricol = ob.nr_matricol;
    structura_date = ob.structura_date;
    umap = ob.umap;
}

template <class T>
Catalog_Individual<T>::~Catalog_Individual()
{
    nr_matricol = 0;
    nr_examen_curent = 0;
    structura_date.clear();
}

template<class T>
Catalog_Individual<T> Catalog_Individual<T>::operator=(const Catalog_Individual& ob)
{
    if(this != &ob)
    {
        nr_matricol = ob.nr_matricol;
        structura_date = ob.structura_date;
        umap = ob.umap;
    }
    return *this;
}

template<class T>
int Catalog_Individual<T>::get_nr_matricol()
{
    return nr_matricol;
}

template<class T>
int Catalog_Individual<T>::get_nr_examene()
{
    return nr_examen_curent;
}

template<class T>
void Catalog_Individual<T>::afisare()
{
    cout<<" nr matricol  "<<nr_matricol<<"\n";
    if(structura_date.empty() == true)
        cout<<"studentul nu a sustinut acest tip de examene\n";
    else
    {
        cout<<"acesta a dat examenele:\n";
        for(auto &it: structura_date)
        {
            it.afisare();
            ///cout<<"\n";
        }
    }
}

template<class T>
Catalog_Individual<T> Catalog_Individual<T>::operator+=(const T &ob)
{
    nr_examen_curent++;
    structura_date.push_back(ob);
    return *this;
}

template <class T>
istream &operator>> (istream &fin, Catalog_Individual<T>&ob)
{
    cout<<"dati nr maricol:\n";
    fin>>ob.nr_matricol;
    cout<<"dati nr de examene sustinute:\n";
    fin>>ob.nr_examen_curent;
    for(int i = 0; i <ob.nr_examen_curent; i++)
    {
        T x;
        cout<<"dati examenul\n";
        fin>>x;
    }

    return fin;
}
template <class T>
ostream &operator<< (ostream &gout,const Catalog_Individual<T>&ob)
{
    gout<<" nr matricol  "<<ob.nr_matricol<<"\n";
    if(ob.structura_date.empty() == true)
        gout<<"studentul nu a sustinut acest tip de examene\n";
    else
    {
        gout<<"acesta a dat examenele:\n";
        for(auto &it: ob.structura_date)
        {
            it.afisare();
            ///cout<<"\n";
        }
    }
    return gout;
}


//template<class T>
//vector<string> Catalog_Individual<T>::studenti_care_nu_au_trecut_examene = {""};

template<class T>
unordered_map<int, vector<string>> Catalog_Individual<T>::umap = {{ 0, {""} }};

template<class T>
void Catalog_Individual<T>::set_umapul_cu_studentii_picati(string nume)
{
    for (unsigned i=0; i<structura_date.size(); i++)
    {
        if (umap.find(structura_date[i].get_id_examen()) == umap.end())
        {
            ///cheia nu a fost introdusa in umap pana acum;
            umap.insert({ structura_date[i].get_id_examen(), {""} });
        }

        if(structura_date[i].get_media() < 5 or structura_date[i].get_nota_scris() < 5)
        {
            umap[structura_date[i].get_id_examen()].push_back(nume);
        }
    }
}

template<class T>
void Catalog_Individual<T>::afiseaza_umapul_cu_sudentii_picati()
{
    for(const auto& p : umap)
    {
        if(p.first != 0)
        {
            cout << p.first << ":";
            for(const auto& i : p.second)
            {
                cout << i;
            }
            cout<<"\n";
        }
    }
}
/// Class template Catalog_Individual<Quizz>

int Catalog_Individual<Quizz>::contor_matricol = 0;
unordered_set<string> Catalog_Individual<Quizz>::elevi = {""};

Catalog_Individual<Quizz>::Catalog_Individual()
{
    contor_matricol++;
    nr_examen_curent = 0;
    nr_matricol = contor_matricol;

}


Catalog_Individual<Quizz>::Catalog_Individual(const Catalog_Individual<Quizz>& ob)
{
    nr_matricol = ob.nr_matricol;
    structura_date = ob.structura_date;
}

Catalog_Individual<Quizz>::~Catalog_Individual()
{
    nr_matricol = 0;
    nr_examen_curent = 0;
    structura_date.clear();
   /// elevi.clear();
}

Catalog_Individual<Quizz> Catalog_Individual<Quizz>::operator=(const Catalog_Individual<Quizz>& ob)
{
    if(this != &ob)
    {
        nr_matricol = ob.nr_matricol;
        structura_date = ob.structura_date;
        nr_quizzuri = ob.nr_quizzuri;
    }
    return *this;
}


int Catalog_Individual<Quizz>::get_nr_matricol()
{
    return nr_matricol;
}

int Catalog_Individual<Quizz>::get_nr_examene()
{
    return nr_examen_curent;
}

void Catalog_Individual<Quizz>::afisare()
{
    cout<<" nr matricol  "<<nr_matricol<<"\n";
    if(structura_date.empty() == true)
        cout<<"studentul nu a sustinut acest tip de examene\n";
    else
    {
        cout<<"acesta a dat examenele:\n";
        for(auto &it: structura_date)
        {
            it.afisare();
            ///cout<<"\n";
        }
    }
}

Catalog_Individual<Quizz> Catalog_Individual<Quizz>::operator+=(const Quizz&ob)
{
    nr_examen_curent++;
    structura_date.push_back(ob);
    return *this;
}

template <>
istream&operator>> (istream &fin, Catalog_Individual<Quizz>&ob)
{
    cout<<"dati nr maricol:\n";
    fin>>ob.nr_matricol;
    cout<<"dati nr de examene sustinute:\n";
    fin>>ob.nr_examen_curent;
    for(int i = 0; i <ob.nr_examen_curent; i++)
    {
        Quizz x;
        cout<<"dati examenul\n";
        fin>>x;
    }
    return fin;
}

template <>
ostream&operator<< (ostream &gout,Catalog_Individual<Quizz>&ob)
{
    gout<<" nr matricol  "<<ob.nr_matricol<<"\n";
    if(ob.structura_date.empty() == true)
        gout<<"studentul nu a sustinut acest tip de examene\n";
    else
    {
        gout<<"acesta a dat examenele:\n";
        for(auto &it: ob.structura_date)
        {
            it.afisare();
            ///cout<<"\n";
        }
    }
    return gout;
}


void Catalog_Individual<Quizz>::set_studentii_care_au_2quizzuri(string nume, int nr_quizzuri)
{
    if (nr_quizzuri >=2)
    {
        if(elevi.find(nume) == elevi.end())  ///daca numele nu e in set;
            elevi.insert(nume);
    }
}

void Catalog_Individual<Quizz>::afiseaza_sudentii_care_au_dat_2quizzuri()
{
    for (auto const& i: elevi)
    {
        cout << i << " ";
    }
}
//// Class Elev

Elev::Elev(string nume,  int grupa, int nr_examene):nume(nume), nr_examene(nr_examene), grupa(grupa)
{
    nr_quizzuri_date = 0;
}

Elev::Elev(const Elev & ob)
{
    grupa = ob.grupa;
    nr_examene = ob.nr_examene;
    nume = ob.nume;
    nr_quizzuri_date = ob.nr_quizzuri_date;

}

Elev::~Elev()
{
    grupa = 0;
    nr_examene = 0;
    nume.clear();
    nr_quizzuri_date = 0;

}

Elev Elev::operator=(const Elev &ob)
{
    if(this != &ob)
    {
        grupa = ob.grupa;
        nr_examene = ob.nr_examene;
        nume = ob.nume;
        nr_quizzuri_date = ob.nr_quizzuri_date;
    }
    return *this;
}

int Elev::get_grupa()const
{
    return grupa;
}

int Elev::get_nr_examene()const
{
    return nr_examene;
}

int Elev::get_nr_quizzuri()const
{
   return nr_quizzuri_date;
}

string Elev::get_nume() const
{
    return nume;
}

void Elev::set_grupa(const int nr)
{
    grupa = nr;
}

void Elev::set_nr_examene(const int nr)
{
    nr_examene = nr;
}

void Elev::set_nr_examene()
{
    nr_examene = examene.get_nr_examene() + partiale.get_nr_examene() + examene_finale.get_nr_examene() + quizzuri.get_nr_examene();
}

void Elev::set_nume(const string nume1)
{
    nume = nume1;
}

void Elev::adauga_examen(Examen examen)
{
    examene += examen;
}

void Elev::adauga_partial(Partial partial)
{
    partiale += partial;
}

void Elev::adauga_examen_final(Examen_final examen_final)
{
    examene_finale += examen_final;
}

void Elev::adauga_quizz(Quizz quizz)
{
    quizzuri += quizz;
}

istream& operator>>(istream &fin, Elev &ob)
{
    cout<<"Introduceti numele: ";
    fin.get();
    getline(fin, ob.nume);
    cout<<"Dati grupa: ";
    fin>>ob.grupa;
    cout<<"Dati numarul de examene(fara alte paritale, puncte bonus sau quizz-uri): ";
    fin>>ob.nr_examene;
    return fin;

}

ostream& operator<<(ostream &gout, Elev &ob)
{
    gout<<"Pentru studentul cu numele "<< ob.nume<<", grupa "<<ob.grupa<<", cu numarul de examene simple fara alte partiale / quizzuri / examene finale: "
                            <<ob.nr_examene<< ".\n";
    gout<<"\n";
    gout<<"Fisa a) cu examene scrise: " ;
    ob.examene.afisare();
    gout<<"\n";
    gout<<"Fisa b) cu partiale: ";
    ob.partiale.afisare();
    gout<<"\n";
    gout<<"Fisa c) cu examene finale: ";
    ob.examene_finale.afisare();
    gout<<"\n";
    gout<<"Fisa d) cu quizzuri este: ";
    ob.quizzuri.afisare();

    gout<<"\n-------------------------------------------------------------------------------------\n\n";


    return gout;

}

void Elev::set_partiale_picate()
{
    partiale.set_umapul_cu_studentii_picati(get_nume());
}

void Elev::set_examene()
{
    examene.set_umapul_cu_studentii_picati(get_nume());
}

void Elev::set_examene_finale()
{
    examene_finale.set_umapul_cu_studentii_picati(get_nume());
}

void Elev::set_quizzuri()
{
    quizzuri.set_studentii_care_au_2quizzuri(get_nume(), this->nr_quizzuri_date);
}

void Elev::afiseaza_quizzurile()
{
    cout<<"Studentii care au dat cel putin 2 quizzuri sunt:\n";
    quizzuri.afiseaza_sudentii_care_au_dat_2quizzuri();
}

void Elev::afiseaza_partialele_picate()
{
    cout<<"Id-ul partialului + studentii picati la partiale: \n";
    partiale.afiseaza_umapul_cu_sudentii_picati();
    cout<<'\n';
}

void Elev::afiseaza_examenele_picate()
{
    cout<<"Id-ul exemenelor scrise + studentii picati la examenele scrise: \n";
    examene.afiseaza_umapul_cu_sudentii_picati();
    cout<<'\n';
}

void Elev::afiseaza_examenele_finale()
{
    cout<<"Id-ul exemenelor finale + studentii picati la examenele finale: \n";
    examene_finale.afiseaza_umapul_cu_sudentii_picati();
    cout<<'\n';
}

Elev* Elev::memorare_afisare_n_obiecte()
{
    int n;
    cout<<"Dati numarul de elevi: ";
    cin>>n;
    Elev a[1000];
    for (int i=0; i<n; i++)
        {
            cin>>a[i];
            for(int j = 0 ; j < a[i].nr_examene; ++j)
            {
                Examen e;
                cin>>e;
                a[i].adauga_examen(e);
                a[i].set_examene();
            }
            int nr_partiale;
            cout<<"Dati numarul de examene care contin si partiale(examene + partiale): ";
            cin>>nr_partiale;
            for(int j = 0 ; j < nr_partiale; ++j)
            {
                Partial e;
                cin>>e;
                a[i].adauga_partial(e);
                a[i].set_partiale_picate();
            }
            int nr_examene_finale;
            cout<<"Dati numarul de examene finale(examene + partiale + puncte bonus): ";
            cin>>nr_examene_finale;
            for(int j = 0 ; j < nr_examene_finale; ++j)
            {
                Examen_final e;
                cin>>e;
                a[i].adauga_examen_final(e);
                a[i].set_examene_finale();
            }
            cout<<"Dati numarul de quizz-uri, cu tot cu examene si partiale si puncte bonus: ";
            cin>>a[i].nr_quizzuri_date;
            a[i].set_quizzuri();
            for(int j = 0 ; j < a[i].nr_quizzuri_date; ++j)
            {
                Quizz e;
                cin>>e;
                a[i].adauga_quizz(e);
            }
            cout<<'\n';
        }

    bool verif = true;
    while(verif)
    {
        cout<<"\n------------------------------------------------------------------------------------------------\n\n";
        cout<<"Toate optiunile:\n";
        cout<<"1 - Afiseaza tot catalogul cu studenti\n";
        cout<<"2 - Afiseaza catalogul unui student anume\n";
        cout<<"3 - Adaugati un nou student in catalog\n";
        cout<<"4 - Afisati studentii care au dat cel putin 2 quizz-uri\n";
        cout<<"5 - Afiseaza lista cu studentii picati\n";
        cout<<"0 - Exit meniu alegeri\n";
        cout<<"\n------------------------------------------------------------------------------------------------\n\n";
        cout<<"Introduceti optiunea pe care o doriti: ";
        int optiune;
        cin>>optiune;
        int i;
        switch(optiune)
        {
        case 1:
            for (int i=0; i<n; i++)
                cout<<a[i];
            break;
        case 2:
            cout<<"Dati index student(de la 0 la n-1): ";
            int indx;
            cin>>indx;
            cout<<a[indx];
            break;
        case 3:
            i=n;
            cin>>a[i];
            for(int j = 0 ; j < a[i].nr_examene; ++j)
            {
                Examen e;
                cin>>e;
                a[i].adauga_examen(e);
                a[i].set_examene();
            }
            int nr_partiale;
            cout<<"Dati numarul de examene care contin si partiale(examene + partiale): ";
            cin>>nr_partiale;
            for(int j = 0 ; j < nr_partiale; ++j)
            {
                Partial e;
                cin>>e;
                a[i].adauga_partial(e);
                a[i].set_partiale_picate();
            }
            int nr_examene_finale;
            cout<<"Dati numarul de examene finale(examene + partiale + puncte bonus): ";
            cin>>nr_examene_finale;
            for(int j = 0 ; j < nr_examene_finale; ++j)
            {
                Examen_final e;
                cin>>e;
                a[i].adauga_examen_final(e);
                a[i].set_examene_finale();
            }
            cout<<"Dati numarul de quizz-uri, cu tot cu examene si partiale si puncte bonus: ";
            cin>>a[i].nr_quizzuri_date;
            a[i].set_quizzuri();
            for(int j = 0 ; j < a[i].nr_quizzuri_date; ++j)
            {
                Quizz e;
                cin>>e;
                a[i].adauga_quizz(e);
            }
            ++n;
            cout<<'\n';
            break;
        case 4:
            a[i].afiseaza_quizzurile();
            break;
        case 5:
            a[i].afiseaza_examenele_picate();
            a[i].afiseaza_partialele_picate();
            a[i].afiseaza_examenele_finale();
            break;
        case 0:
            verif=false;
            break;
        }

    }

        return a;
}

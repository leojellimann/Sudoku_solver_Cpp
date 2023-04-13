#include <iostream>

using namespace std;

#define CARACTEREREMPLACANT '.'

class Sudoku
{
private:

    char grille[9][9];
    int nb_essai;

public:
    Sudoku(const char gr[]);
    ~Sudoku();

    void Affiche();
    bool EstValide();

    bool Resout();

    friend std::ostream& operator<<(std::ostream &stream, const Sudoku& sudo);
};


Sudoku::Sudoku(const char gr[]):nb_essai(0)
{
    int col,lig;
    for(lig=0; lig<9; lig++)
        for(col=0; col<9; col++)
        {
            char v= gr[lig*9+col];
            if ((v>='1' && v<='9')
                    || v==CARACTEREREMPLACANT)
                grille[lig][col]=v;
            else
                throw "Erreur de remplissage de la grille";
        }
}

Sudoku::~Sudoku()
{
}

ostream& operator <<(std::ostream& stream, const Sudoku& sudo)
{
    int col,lig;
    stream << "***********" << endl;
    for(lig=0; lig<9; lig++)
    {
        for(col=0; col<9; col++)
        {
            stream << sudo.grille[lig][col];
            if (col==2 || col==5)
                stream << " ";
        }
        stream << endl;
        if (lig==2 || lig==5)
            stream << endl;
    }
    stream << "*********** " << sudo.nb_essai << "essais." <<endl;
    return stream;
}


void Sudoku::Affiche()
{

    cout << *this;

}

bool Sudoku::EstValide()
{
    int col,lig, next;
    // Verification des lignes
    for(lig=0; lig<9; lig++)
    {
        for(col=0; col<8; col++)
        {
            if (grille[lig][col]==CARACTEREREMPLACANT)
                continue;
            for(next=col+1; next<9; next++)
                if (grille[lig][col]==grille[lig][next])
                    return false;
        }
    }
    // Verification des colonnes
    for(col=0; col<9; col++)
    {
        for(lig=0; lig<8; lig++)
        {
            if (grille[lig][col]==CARACTEREREMPLACANT)
                continue;
            for(next=lig+1; next<9; next++)
                if (grille[lig][col]==grille[next][col])
                    return false;
        }
    }

    // Verification des cubes
    int next2;
    for(col=0; col<9; col++)
    {
        for(lig=0; lig<9; lig++)
        {
            if (grille[lig][col]==CARACTEREREMPLACANT)
                continue;
            int col_cube=(col/3)*3;
            int lig_cube=(lig/3)*3;
            for(next=0; next<3; next++)
            {
                for(next2=0; next2<3; next2++)
                {
                    if (col==col_cube+next && lig==lig_cube+next2)
                        continue;
                    if (grille[lig][col]==grille[lig_cube+next2][col_cube+next])
                        return false;
                }
            }
        }
    }


    return true;
}

bool Sudoku::Resout()
{
    int col,lig;

    if (EstValide()==false)
        return false;

    for(lig=0; lig<9; lig++)
        for(col=0; col<9; col++)
            if (grille[lig][col]==CARACTEREREMPLACANT)
            {
                for( char essai='1'; essai<='9'; essai++)
                {
                    grille[lig][col]=essai;
                    nb_essai++;
                    if (EstValide())
                        if(Resout())
                            return true;
                    // Pas reussit a résoudre on passe à l'essai suivant
                }
                // Aucun essai n'a reussit
                grille[lig][col]=CARACTEREREMPLACANT;
                return false;
            }

    return true;
}




int main()
{
    Sudoku s("..192..56"
             "..23....8"
             "9..61...."
             "6...8.49."
             "2.95.18.7"
             ".58.6...1"
             "....96..4"
             "3....76.."
             "58..431..");

    cout << s;
    if (s.EstValide())
        cout << "GrilleOk"<<endl<<endl;

    if (s.Resout())
        cout << "Solution : "<< endl << s ;

    return 0;
}


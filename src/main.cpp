#include "../include/KenoBet.h"

int main( int argc, char **argv )
{
    if( argc < 2 or argc > 2 )
    {
        std::cerr << "Erro: o programa deve receber apenas um argumento = nome do arquivo de aposta. ex: aposta1.txt" << std::endl;
        return EXIT_FAILURE;
    }
    std::ifstream rFile( argv[1] );
    if( !rFile.good() )
    {
        std::cerr << "Erro: falha na leitura do arquivo " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }
    /// criando aposta
    KenoBet aposta1;
    float wage;
    rFile >> wage;
    if( aposta1.set_wage(wage) )
    {
        int nr;
        rFile >> nr;
    }
    number_type aux;
    number_type count(0);
    //set_of_numbers_type spots;

    /// prenchendo m_spots, falta tirar os elementos unicos( usar unique ) e ordenar( qsort ) 
    while( rFile >> aux or count < 15 )
    {
        if( aposta1.add_number(aux) )
        {
            ++count;
        }
    }

    return EXIT_SUCCESS;
}
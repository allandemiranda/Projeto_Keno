/**
 * @file main.cpp
 * @author Allan de Miranda and Josue Claudio
 * @brief Main to the game
 * @version 0.1
 * @date 2018-10-06
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include <fstream>  // std::ifstream
#include <string>   // std::string
#include <cstring>  // std::strcat

#include <iostream>

//#include "../include/KenoBet.h"

/**
 * @brief Function to get base file parameters
 * 
 * @param fileName File name
 * @param bet Vector that keeps the three parameters
 * @return true If everything happened normal
 * @return false If there were any errors
 */
bool catch_bet(char *fileName, float *bet){
    std::string route = "../data/"; // Begin route
    route = route + fileName; // Complete route
    std::ifstream ifs(route); // Open Route
    if(!ifs.good()){
        return false;
    }
    for(int i(0); i<3; ++i){
        ifs >> bet[i];
    }
	ifs.close();
    return true;
}

int main( int argc, char **argv )
{/*
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
    }*/

    float teste[3];
    catch_bet(argv[1],teste);
    for(int i(0); i<3; ++i){
        std::cout << teste[i] << std::endl;
    }

    return EXIT_SUCCESS;
}
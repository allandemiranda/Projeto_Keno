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

#include <iostream> // std::cout , std::cin , std::endl;
#include <fstream>  // std::ifstream
#include <string>   // std::string
#include <vector>   // std::vector
#include <fstream>
#include <iomanip>

#include "../include/KenoBet.h"

// Global vector
std::vector < std::vector <float> > payout_table = {
    {
        0, 3
    },
    {
        0, 1, 9
    },
    {
        0, 1, 2, 16
    },
    {
        0, 0.5, 2, 6, 12
    },
    {
        0, 0.5, 1, 3, 15, 50
    },
    {
        0, 0.5, 1, 2, 3, 30, 75
    },
    {
        0, 0.5, 0.5, 1, 6, 12, 36, 100
    },
    {
        0, 0.5, 0.5, 1, 3, 6, 19, 90, 720
    },
    {
        0, 0.5, 0.5, 1, 2, 4, 8, 20, 80, 1200 
    },
    {
        0, 0, 0.5, 1, 2, 3, 5, 10, 30, 600, 1800
    },
    {
        0, 0, 0.5, 1, 1, 2, 6, 15, 25, 180, 1000, 3000
    },
    {
        0, 0, 0, 0.5, 1, 2, 4, 24, 72, 250, 500, 2000, 4000
    },
    {
        0, 0, 0, 0.5, 0.5, 3, 4, 5, 20, 80, 240, 500, 3000, 6000
    },
    {
        0, 0, 0, 0.5, 0.5, 2, 3, 5, 12, 50, 150, 500, 1000, 2000, 7500
    },
    {
        0, 0, 0, 0.5, 0.5, 1, 2, 5, 15, 50, 150, 300, 600, 1200, 2500, 10000
    }
};

/**
 * @brief Function to get base file parameters
 * 
 * @param fileName File name
 * @param bet Vector that keeps the three parameters
 * @return true If everything happened normal
 * @return false If there were any errors
 */
bool catch_bet(char *fileName, std::vector <float> &bet){
    std::string route = "../data/"; // Begin route
    route = route + fileName; // Complete route
    std::ifstream ifs(route); // Open Route
    if(!ifs.good()){
        return false;
    }
    float valuer;
    while(ifs >> valuer){
        bet.push_back(valuer);
    }
	ifs.close();
    return true;
}

/**
 * @brief Function to initialize game parameters
 * 
 * @param FileName File name game playes
 * @param fist The bet
 * @return true If everything happened normal
 * @return false If there were any errors
 */
bool initialization_parameters(char *FileName, KenoBet &fist){
    std::vector <float> parameters;
    if(!catch_bet(FileName, parameters)){
        return false;
    }
    //fist.set_wage(parameters[0]); // Sets the amount of money the player is betting
    //fist.rounds(parameters[1]); ONDE ESTÀ O PARÃMETRO DAS RODADAS ???
    for(int i(2); i<(parameters.size()); ++i){
        //fist.add_number((unsigned short int)(parameters[i]));
    } 
    return true;
}

int main( int argc, char **argv )
{
    /**
     * @brief Initialized player
     * 
     */
    KenoBet player_bet;
    std::cout << ">>> Preparing to read bet file [data/" << argv[1] << "], please wait..." << std::endl;
    if(!initialization_parameters(argv[1],player_bet)){
        std::cout << ">>> Displays startup error, check the data file" << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << ">>> Bet successfully read!" << std::endl;
    }

    /**
     * @brief Initial Detail
     * 
     */
    std::cout << "You are going to wage a total of $" << /*player_bet.m_wage() [pegar quantidade de dienhiro ??]  << */ " dollars." << std::endl;
    std::cout << "Going for a total of " << /*player_bet.roud() [pegar rodadas ??]  << */ " rounds, waging $" << /*player_bet.m_wage()/player_bet.roud() [??]  << */ " per round." << std::endl;
    std::cout << std::endl;
    std::cout << "Your bet has " << /*player_bet.m_spots.size() << */" numbers. They are: [ ";
    /*
    for(unsigned short int i : player_bet.m_spots){
        std::cout << i << " ";
    }
    */
    std::cout << "]" << std::endl;

    return EXIT_SUCCESS;
    
}
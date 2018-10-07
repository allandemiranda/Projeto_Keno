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
        //fist.add_number((short int)(parameters[i]));
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
    std::cout << "You are going to wage a total of $1500 dollars." << std::endl;
    std::cout << "Going for a total of 3 rounds, waging $500 per round." << std::endl;
    std::cout << std::endl;
    std::cout << "Your bet has 3 numbers. They are: [ 12 21 64 ]" << std::endl;

    return EXIT_SUCCESS;
    
}
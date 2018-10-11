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
#include "KenoBet.h"
/**
 * @brief Main
 * 
 * @param argc 1 
 * @param argv File name
 * @return int EXIT
 */

int main( int argc, char **argv )
{ 
    /**
     * @brief Initialized player
     * 
     */
    KenoBet player_bet;
    std::cout << ">>> Preparing to read bet file [data/" << argv[1] << "], please wait..." << std::endl;
    if(!player_bet.initialization_parameters(argv[1], player_bet)){
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
    std::cout << "    You are going to wage a total of $" << player_bet.get_wage_initial() << " dollars." << std::endl;
    std::cout << "    Going for a total of " << player_bet.get_rounds() << " rounds, waging $" << player_bet.get_wage_initial()/player_bet.get_rounds()  <<  " per round." << std::endl;
    std::cout << std::endl;
    std::cout << "    Your bet has " << player_bet.get_spots().capacity() << " numbers. They are: [ ";    
    for(number_type i : player_bet.get_spots()){
        std::cout << i << " ";
    }      
    std::cout << "]" << std::endl;
    std::cout << "         -------+---------" << std::endl;    
    std::cout << "         Hits   | Payout  " << std::endl;
    std::cout << "         -------+---------" << std::endl;
    for(number_type i(0); i < payout_table[player_bet.size()-1].size(); ++i){
        std::cout << std::setw(10);
        std::cout << std::fixed << i << std::setw(7) << " |";
        std::cout << " " << std::setprecision(0) << payout_table[player_bet.size()-1][i] << std::endl;
    }

    /**
     * @brief Playing
     * 
     */
    for(number_type i(1); i <= player_bet.get_rounds(); ++i){
        player_bet.This_is_round(i, player_bet);
    }

    /**
     * @brief Finishing
     * 
     */
    std::cout << ">>> End of rounds!" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "===== SUMMARY =====" << std::endl;
    std::cout << ">>> You spent in this game a total of " << player_bet.get_wage_initial()<<  std::endl;
    if( (player_bet.get_net_balance() - player_bet.get_wage_initial()) > 0 ){
        std::cout << ">>> Hooray, you won $" << player_bet.get_net_balance() - player_bet.get_wage_initial() << " dollars"<<std::endl;
    } else {
        std::cout << ">>> ;( you dont won nothing, bye ;(" << std::endl;
    }
    std::cout << ">>> You are leaving the Keno table with $" << player_bet.get_net_balance() << " dollars"<<std::endl;

    // Exiting
    return EXIT_SUCCESS;    
}
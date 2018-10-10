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
#include "../include/KenoBet.h"

// Global vector
std::vector < std::vector <cash_type> > payout_table = {
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
    if(!fist.set_wage_initial( (parameters[0]) ) ){  
        return false;
    }
    
    fist.set_wage( (parameters[0]) );
    if(!fist.set_rounds((number_type)(parameters[1]))){
        return false;
    }
    for(number_type i(2); i<(parameters.size()); ++i){
        if(!fist.add_number((number_type)(parameters[i]))){
            return false;
        }
    } 
    return true;
}

/**
 * @brief 
 * 
 * @param round_now 
 * @param fist 
 */
void This_is_round(const number_type &round_now, KenoBet &fist/*, cash_type Payout_rate*/){
    std::cout << "         --------------------------------------------------" << std::endl;
    std::cout << "         This is round #" << round_now << " of " << fist.get_rounds() << ", and your wage is $" << fist.get_wage_initial() / fist.get_rounds() << ". Good luck!" << std::endl;
    fist.set_wage( fist.get_wage() - ( fist.get_wage_initial() / fist.get_rounds() ) + fist.get_m_round_payment() );
    // std::cout<< "aqui " << fist.get_wage() << std::endl;
    /// criando, inicializando e exibindo o vetor de hits
    set_of_numbers_type hits_are = ( fist.get_hits(fist.set_hits()) );
    std::cout << "         The hits are: [ ";
    for(number_type i : hits_are){
        std::cout << i << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << std::endl;

    /// criando, inicializando e exibindo o vetor com os valores que foram acertados no sorteio
    set_of_numbers_type spots = fist.get_spots();
    set_of_numbers_type You_hit;
    number_type k(0); /// qtd de acertos
    for( number_type i(0); i < spots.capacity(); ++i )
    {
        for( number_type j(0); j < hits_are.capacity(); ++j )
        {
            if( spots[i] == hits_are[j] )
            {
                You_hit.push_back( spots[i] );
                ++k;
            }        
        }       
    }
    
    /// se acertou algum número sorteado
    if( k > 0 )
    {
        /// mostrando números acertados
        std::cout << "         You hit the following number(s) [ ";
        for( number_type i : You_hit )
            std::cout << i << " ";  
        std::cout << "], a total of " << You_hit.size() << " hits out of " << fist.size() << std::endl; 
        /// setando o cash currente e o pagamento
        fist.set_wage( ( fist.get_wage_initial() / fist.get_rounds() ) * payout_table[fist.get_spots().size()-1][You_hit.size()] );
        fist.set_m_round_payment( ( fist.get_wage_initial() / fist.get_rounds() ) * payout_table[fist.get_spots().size()-1][You_hit.size()]);
        // mostrando o pagamento da tabela
        std::cout << "         Payout rate is " <<payout_table[fist.get_spots().size()-1][You_hit.size()] << ", thus you came out with: $" << fist.get_m_round_payment() << std::endl;
    }
    else
    {
        std::cout << "         You dont hit anyone number" << std::endl;        
    }
    /// finaliza mostrando o net balance
    std::cout << "         Your net balance so far is: $" << fist.get_net_balance() << " dollars." << std::endl;
    // std::cout << "--------------------------------------------------" << std::endl;
}

int main( int argc, char **argv )
{ 
    /**
     * @brief Initialized player
     * 
     */
    KenoBet player_bet;
    std::cout << ">>> Preparing to read bet file [data/" << argv[1] << "], please wait..." << std::endl;
    if(!initialization_parameters(argv[1], player_bet)){
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
    for(number_type i(0); i<(payout_table[player_bet.get_rounds()-1].size()); ++i){
        std::cout << std::setw(10);
        // std::cout << std::setfill('');
        std::cout << std::fixed << i << std::setw(7) << " |";
        std::cout << " " << std::setprecision(0) << payout_table[player_bet.get_rounds()-1][i] << std::endl;
    }

    /**
     * AQUI FICARÁ A PARTE DAS RODADAS DE CADA JOGO.
     *      USANDO A FUNÇÃO CORRETA, É POSSIVEL GERAR O LAYOUT NECESSÁRIO.
     * FUNÇÃO TESTE ADOTADA TEMPORARIAMENTE !!!
     * 
     */
    for(number_type i(1); i <= player_bet.get_rounds(); ++i){
        This_is_round(i, player_bet);
    }

    /// FIM
    std::cout << ">>> End of rounds!" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    std::cout << "===== SUMMARY =====" << std::endl;
    std::cout << ">>> You spent in this game a total of " << player_bet.get_wage_initial()<<  std::endl;
    if( player_bet.get_net_balance() - player_bet.get_wage_initial() > 0 )
        std::cout << ">>> Hooray, you won $" << player_bet.get_net_balance() - player_bet.get_wage_initial() << " dollars"<<std::endl;
    else
        std::cout << ">>> ;( you dont won nothing, bye ;(" << std::endl;
    std::cout << ">>> You are leaving the Keno table with $" << player_bet.get_net_balance() << " dollars"<<std::endl;

    return EXIT_SUCCESS;
    
}
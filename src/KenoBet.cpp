/**
 * @file KenoBet.cpp
 * @author Allan de Miranda and Josue Claudio
 * @brief Class definition
 * @version 0.1
 * @date 2018-10-06
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "../include/KenoBet.h" // Include the header

/**
 * @brief Global vector payout_table
 * 
 */
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
    std::string route = "../data/"; // <! Begin route
    route = route + fileName; // <! Complete route
    std::ifstream ifs(route); // <! Open Route
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
 * @brief Rounds with plays
 * 
 * @param round_now Current round number
 * @param fist Player bet
 */
void This_is_round(const number_type &round_now, KenoBet &fist){
    std::cout << "         --------------------------------------------------" << std::endl;
    std::cout << "         This is round #" << round_now << " of " << fist.get_rounds() << ", and your wage is $" << fist.get_wage_initial() / fist.get_rounds() << ". Good luck!" << std::endl;
    fist.set_wage( fist.get_wage() - ( fist.get_wage_initial() / fist.get_rounds() ) + fist.get_m_round_payment() );
    set_of_numbers_type hits_are = ( fist.get_hits(fist.set_hits()) );
    std::cout << "         The hits are: [ ";
    // <! hits vector
    for(number_type i : hits_are){ 
        std::cout << i << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << std::endl;
    // <! Vector with the values that were drawn in the draw
    set_of_numbers_type spots = fist.get_spots();
    set_of_numbers_type You_hit;
    number_type num_hits(0); // Number of hits
    //// ***-----> Verificar se aqui pode ser feito uma busca binaria <-------*** /////
    /*for( number_type i(0); i < spots.capacity(); ++i ){
        for( number_type j(0); j < hits_are.capacity(); ++j ){
            if( spots[i] == hits_are[j] ){
                You_hit.push_back( spots[i] );
                ++num_hits;
            }        
        }       
    }*/
    for(number_type i(0); i < spots.capacity(); ++i){ // <<<<<<<-------------- PQ CAPACITY ?
        if(std::binary_search(hits_are.begin(), hits_are.end(), spots[i])){
            You_hit.push_back( spots[i] );
            ++num_hits;
        }
    }    
    // <! Hit some number
    if(num_hits > 0){
        // <! Showing successful numbers
        std::cout << "         You hit the following number(s) [ ";
        for(number_type i : You_hit){
            std::cout << i << " ";  
        }
        std::cout << "], a total of " << You_hit.size() << " hits out of " << fist.size() << std::endl; 
        // <! Set cash currente and payment
        fist.set_wage( ( fist.get_wage_initial() / fist.get_rounds() ) * payout_table[fist.get_spots().size()-1][You_hit.size()] );
        fist.set_m_round_payment( ( fist.get_wage_initial() / fist.get_rounds() ) * payout_table[fist.get_spots().size()-1][You_hit.size()]);
        // <! Sho the payment da table
        std::cout << "         Payout rate is " <<payout_table[fist.get_spots().size()-1][You_hit.size()] << ", thus you came out with: $" << fist.get_m_round_payment() << std::endl;
    }
    else
    {
        std::cout << "         You dont hit anyone number" << std::endl;        
    }
    // <! Show the net balance
    std::cout << "         Your net balance so far is: $" << fist.get_net_balance() << " dollars." << std::endl;
}

/**
 * @brief Adds a number to the spots only if the number is not already there
 * 
 * @param spot_ The number we wish to include in the bet
 * @return true If number chosen is successfully inserted
 * @return false Otherwise
 */
bool KenoBet::add_number(number_type spot_)
{
    if( (spot_ > 0) and (spot_ < 81) )
    {
        m_spots.push_back(spot_);
        /// *** ------>>>>>  TERMINAR ESTA PARTE *** <<<<-------------
        std::sort(m_spots.begin(), m_spots.end());
        std::unique(m_spots.begin(), m_spots.end());
        auto last = std::unique(m_spots.begin(), m_spots.end());
        m_spots.erase( last, m_spots.end() );
       
    }
    return ((spot_ > 0) and (spot_ < 81));
}

/**
 * @brief Sets the amount of money the player is betting
 * 
 * @param wage_ The wage
 * @return true If we have a wage above zero
 * @return false Otherwise
 */
bool KenoBet::set_wage(cash_type wage_)
{
    m_wage = wage_;

    return (wage_ > 0);
}

/**
 * @brief Resets a bet to an empty state
 * 
 */
void KenoBet::reset(void)
{
    m_spots.clear();
    m_wage = 0;
}

/**
 * @brief Retrieves the player ’s wage on this bet
 * 
 * @return cash_type The wage value
 */
cash_type KenoBet::get_wage(void) const
{
    return m_wage;
}

/**
 * @brief Returns to the current number of spots in the player ’s bet
 * 
 * @return size_t Number of spots present in the bet
 */
size_t KenoBet::size(void) const
{
    return m_spots.size();
}

/**
 * @brief Sets the number of the rounds
 * 
 * @param rounds NUmber of the rounds
 * @return true If we have a number of the rounds
 * @return false Otherwise
 */
bool KenoBet::set_rounds(const number_type rounds)
{
    if(rounds > 0)
    {
        m_rounds = rounds;
    }
    return (m_rounds > 0);
}

/**
 * @brief Get the number of the rounds
 * 
 * @return number_type Number of the rounds
 */
number_type KenoBet::get_rounds(void) const
{
    return m_rounds;
}

/**
 * @brief Way to keep the starting money for final calculations
 * 
 * @param wage_initial My starting money
 * @return true If it's money
 * @return false Otherwise
 */
bool KenoBet::set_wage_initial(cash_type wage_initial)
{
    if(wage_initial > 0)
    {
        m_wage_initial = wage_initial;
    }
    return (wage_initial > 0);
    
}

/**
 * @brief Get my starting money
 * 
 * @return cash_type My start money
 */
cash_type KenoBet::get_wage_initial(void) const
{
    return m_wage_initial;
}

/**
 * @brief To get a net balance
 * 
 * @return cash_type The money about net balance
 */
cash_type KenoBet::get_net_balance(void)
{
    m_net_balance = m_wage + m_round_payment;
    return m_net_balance;
}

/**
 * @brief Set the round payment
 * 
 * @param _round_payment The new payment
 */
void KenoBet::set_m_round_payment(cash_type _round_payment)
{
    m_round_payment = _round_payment;
}

/**
 * @brief Get the roud payment
 * 
 * @return cash_type The money about the round payment
 */
cash_type KenoBet::get_m_round_payment(void) const
{
    return m_round_payment;
}

/**
 * @brief Get spots
 * 
 * @return set_of_numbers_type The spots number
 */
set_of_numbers_type KenoBet::get_spots(void) const
{
    return m_spots;
}

/**
 * @brief Set a number of hits
 * 
 * @return set_of_numbers_type Tatal of the hits 
 */
set_of_numbers_type KenoBet::set_hits(void)
{
    std::random_device rd;
    std::mt19937 mt( rd() ); /// <---------------------------- O QUE É ISSO ????
    std::uniform_int_distribution<number_type> dist(1, 80);
    set_of_numbers_type hits;
    for( number_type i(0); i < 15; ++i )
    {
        hits.push_back(dist(mt));
    }
    std::sort(hits.begin(), hits.end());
    auto last = std::unique(hits.begin(), hits.end());
    hits.erase( last, hits.end() );
    
    return hits;
}

/**
 * @brief Determine how many spots match the hits passed as argument
 * 
 * @param hits_ List of hits randomly chosen by the computer
 * @return set_of_numbers_type An vector with the list of hits
 */
set_of_numbers_type KenoBet::get_hits(const set_of_numbers_type &hits_) const
{
    return hits_;
}
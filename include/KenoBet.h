/**
 * @file KenoBet.h
 * @author Allan de Miranda and Josue Claudio
 * @brief Class KenoBet
 * @version 0.1
 * @date 2018-10-06
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#ifndef KENO_BET_H
#define KENO_BET_H

#include <iostream>  
#include <algorithm>
#include <cstdlib>     
#include <fstream> 
#include <iomanip>
#include <random>  

using number_type = unsigned short int; // <! data type for a keno hit .
using cash_type = float;                // <! Defines the wage type in this application .
using set_of_numbers_type = std ::vector<number_type>;

class KenoBet
{
    public:
        //! Creates an empty Keno bet .
        KenoBet() : m_wage(0){/* empty */};
        /*! Adds a number to the spots only if the number is not already there .
        @param spot_ The number we wish to include in the bet .
        @return T if number chosen is successfully inserted ; F otherwise . */
        bool add_number(number_type spot_);
        /*! Sets the amount of money the player is betting .
        @param wage_ The wage .
        @return True if we have a wage above zero ; false otherwise . */
        bool set_wage(cash_type wage_);
        //! Resets a bet to an empty state .
        void reset(void);
        /*! Retrieves the player ’s wage on this bet .
        @return The wage value . */
        cash_type get_wage(void) const;
        /*! Returns to the current number of spots in the player ’s bet .
        @return Number of spots present in the bet . */
        size_t size(void) const;
        /**
         * @brief 
         * 
         * @return set_of_numbers_type 
         */
        set_of_numbers_type set_hits();
        /*! Determine how many spots match the hits passed as argument .
        @param hits_ List of hits randomly chosen by the computer .
        @return An vector with the list of hits . */
        set_of_numbers_type
        get_hits(const set_of_numbers_type &hits_) const;
        /*! Return a vector < spot_type > with the spots the player has picked so far .
        @return The vector < spot_type > with the player ’s spots picked so far . */
        set_of_numbers_type get_spots(void) const;

        /**
         * @brief Get the rounds object
         * 
         * @param rounds 
         * @return true 
         * @return false 
         */
        bool set_rounds(const number_type rounds); 

        /**
         * @brief Get the rounds object
         * 
         * @return number_type 
         */
        number_type get_rounds(void) const;
        // wage functions
        /**
         * @brief Set the wage initial object
         * 
         * @param wage_initial 
         * @return true 
         * @return false 
         */
        bool set_wage_initial(cash_type wage_initial);
        /**
         * @brief Get the wage initial object
         * 
         * @return cash_type 
         */
        cash_type get_wage_initial(void) const;
        /**
         * @brief Get the net balance object
         * 
         * @return cash_type 
         */
        cash_type get_net_balance(void);
        /**
         * @brief Set the m round payment object
         * 
         * @param _round_payment 
         */
        void set_m_round_payment(cash_type _round_payment);
        /**
         * @brief Get the m round payment object
         * 
         * @return cash_type 
         */
        cash_type get_m_round_payment(void) const;

    private:
        set_of_numbers_type m_spots; // <! The player ’s bet .
        cash_type m_wage; // <! The player ’s wage
        number_type m_rounds; // "Quantidade de rodadas" de apostas que o jogador irá jogar
        
        cash_type m_net_balance; // ( "m_wage" - ("Valor inicial" / "Quantidade de rodadas") )+ "Pagamento da rodada"
        cash_type m_wage_initial; // Valor inicial
        cash_type m_round_payment; // Pagamento da rodada
        
};

#endif
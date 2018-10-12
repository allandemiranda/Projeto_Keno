/**
 * @file KenoBet.h
 * @author Allan de Miranda and Josue Claudio
 * @brief Class KenoBet
 * @version 0.1
 * @date 2018-10-11
 */

#ifndef KENO_BET_H
#define KENO_BET_H

/// Library includes
#include <iostream>
#include <algorithm>      
#include <fstream> 
#include <iomanip>
#include <random>  

/// Typedefs 
using number_type = unsigned short int; // <! data type for a keno hit .
using cash_type = float;                // <! Defines the wage type in this application .
using set_of_numbers_type = std::vector<number_type>; // <! Vector

/**
 * @brief Const vector payout_table
 * 
 */
const std::vector < std::vector <cash_type> > payout_table = {
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
 * @brief Class KenoBet to play the game
 * 
 */
class KenoBet
{
    public:
        
        //! Creates an empty Keno bet
        KenoBet() : m_wage(0){/* empty */};

        /*! Adds a number to the spots only if the number is not already there
        @param spot_ The number we wish to include in the bet
        @return T if number chosen is successfully inserted; F otherwise */
        bool add_number(number_type spot_);

        /*! Sets the amount of money the player is betting
        @param wage_ The wage
        @return True if we have a wage above zero; false otherwise */
        bool set_wage(cash_type wage_);

        //! Resets a bet to an empty state
        void reset(void);

        /*! Retrieves the player ’s wage on this bet
        @return The wage value */
        cash_type get_wage(void) const;

        /*! Returns to the current number of spots in the player’s bet
        @return Number of spots present in the bet */
        size_t size(void) const;

        /**
         * @brief Sets a game with 15 random hits
         * 
         * @return set_of_numbers_type A vector with the hits 
         */
        set_of_numbers_type set_hits(void);

        /*! Determine how many spots match the hits passed as argument
        @param hits_ List of hits randomly chosen by the computer
        @return A vector with the list of hits */
        set_of_numbers_type get_hits(const set_of_numbers_type &hits_) const;

        /*! Return a vector < spot_type > with the spots the player has picked so far
        @return The vector < spot_type > with the player ’s spots picked so far */
        set_of_numbers_type get_spots(void) const;

        /**
         * @brief Sets the number of the rounds
         * 
         * @param rounds NUmber of the rounds
         * @return true If we have a number of the rounds
         * @return false Otherwise
         */
        bool set_rounds(const int &rounds); 

        /**
         * @brief Get the number of the rounds
         * 
         * @return number_type Number of the rounds
         */
        number_type get_rounds(void) const;

        /**
         * @brief Way to keep the starting money for final calculations
         * 
         * @param wage_initial My starting money
         * @return true If it's money
         * @return false Otherwise
         */
        bool set_wage_initial(cash_type wage_initial);

        /**
         * @brief Get my starting money
         * 
         * @return cash_type My start money
         */
        cash_type get_wage_initial(void) const;

        /**
         * @brief Set the round payment
         * 
         * @param _round_payment The new payment
         */
        void set_m_round_payment(cash_type _round_payment);

        /**
         * @brief Get the round payment
         * 
         * @return cash_type The money about the round payment
         */
        cash_type get_m_round_payment(void) const;

        /**
         * @brief Function to get base file parameters
         * 
         * @param fileName File name
         * @param bet Vector that keeps the three parameters
         * @return true If everything happened normal
         * @return false If there were any errors
         */
        bool catch_bet(char *fileName, std::vector <float> &bet);

        /**
         * @brief Function to initialize game parameters
         * 
         * @param FileName File name game playes
         * @param fist The bet
         * @return true If everything happened normal
         * @return false If there were any errors
         */
        bool initialization_parameters(char *FileName, KenoBet &fist);

       /**
         * @brief Rounds with plays
         * 
         * @param round_now Current round number
         * @param fist Player bet
         */
        void This_is_round(const number_type &round_now, KenoBet &fist);

        /**
         * @brief Sorts elements within a search space defined by first and last, using the algorithm insertion sort
         * 
         * @tparam T Template class
         * @param first Beginning of the search space
         * @param last End of the search space 
         */
        template<class T>
        void insertionSort(T first, T last);

    private:
        set_of_numbers_type m_spots; // <! The player’s bet
        number_type m_rounds; // <!"Number of rounds" of bets that the player will play 
        cash_type m_wage; // <! The player’s wage
        cash_type m_wage_initial; // <! Initial value
        cash_type m_round_payment; // <! Round payment   
};

#endif
/**
 * @file KenoBet.cpp
 * @author Allan de Miranda and Josue Claudio
 * @brief Library defines
 * @version 0.1
 * @date 2018-10-06
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "../include/KenoBet.h" // Include the header

/**
 * @brief 
 * 
 * @param spot_ 
 * @return true 
 * @return false 
 */
bool KenoBet::add_number(number_type spot_)
{
    if( spot_ > 0 and spot_ < 81 )
    {
        m_spots.push_back(spot_);
        // TERMINAR ESTA PARTE 
        std::sort(m_spots.begin(), m_spots.end());
    }
    return spot_ > 0 and spot_ < 81;
}

/**
 * @brief 
 * 
 * @param wage_ 
 * @return true 
 * @return false 
 */
bool KenoBet::set_wage(cash_type wage_)
{
    if(wage_ > 0)
    {
        m_wage = wage_;
    }
    return wage_ > 0;
}

/**
 * @brief 
 * 
 */
void KenoBet::reset(void)
{
    m_spots.clear();
    m_wage = 0;
}

/**
 * @brief 
 * 
 * @return cash_type 
 */
cash_type KenoBet::get_wage(void) const
{
    return m_wage;
}

/**
 * @brief 
 * 
 * @return size_t 
 */
size_t KenoBet::size(void) const
{
    return m_spots.size();
}

/**
 * @brief 
 * 
 * @param rounds_ 
 * @return true 
 * @return false 
 */
bool KenoBet::set_rounds(const number_type rounds)
{
    if(rounds > 0)
    {
        m_rounds = rounds;
    }
    return m_rounds > 0;
}

/**
 * @brief 
 * 
 * @return number_type 
 */
number_type KenoBet::get_rounds(void) const
{
    return m_rounds;
}


/**
 * @file KenoBet.cpp
 * @author Allan de Miranda and Josue Claudio
 * @brief ?????????
 * @version 0.1
 * @date 2018-10-06
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include <vector> // std::vector

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
        m_spots.push_back(spot_);
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
    if(wage_ < 0)
    {
        m_wage = wage_;
    }
    return wage_ < 0;
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
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
        std::unique(m_spots.begin(), m_spots.end());
        auto last = std::unique(m_spots.begin(), m_spots.end());
        m_spots.erase( last, m_spots.end() );
       
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
    // if(wage_ > 0)
    // {
        m_wage = wage_;
    // }
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

bool KenoBet::set_wage_initial(cash_type wage_initial)
{
    if(wage_initial > 0)
    {
        m_wage_initial = wage_initial;
    }
    return wage_initial > 0;
    
}

cash_type KenoBet::get_wage_initial(void) const
{
    return m_wage_initial;
}

// cash_type KenoBet::set_net_balance(cash_type net_balance)
// {
//     m_net_balance = m_wage - (m_wage_initial / m_rounds) + m_round_payment;
// }

cash_type KenoBet::get_net_balance(void)
{
    m_net_balance = m_wage + m_round_payment;
    return m_net_balance;
}

void KenoBet::set_m_round_payment(cash_type _round_payment)
{
    m_round_payment = _round_payment;
}

cash_type KenoBet::get_m_round_payment(void) const
{
    return m_round_payment;
}

set_of_numbers_type KenoBet::get_spots(void) const
{
    return m_spots;
}

set_of_numbers_type KenoBet::set_hits()
{
    std::random_device rd;
    std::mt19937 mt( rd() );
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

set_of_numbers_type KenoBet::get_hits(const set_of_numbers_type &hits_) const
{
    return hits_;
}




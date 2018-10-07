#include "../include/KenoBet.h"

bool KenoBet::add_number(number_type spot_)
{
    if( spot_ > 0 and spot_ < 81 )
        m_spots.push_back(spot_);
    return spot_ > 0 and spot_ < 81;
}

bool KenoBet::set_wage(cash_type wage_)
{
    if(wage_ < 0)
    {
        m_wage = wage_;
    }
    return wage_ < 0;
}

void KenoBet::reset(void)
{
    m_spots.clear();
    m_wage = 0;
}

cash_type KenoBet::get_wage(void) const
{
    return m_wage;
}

size_t KenoBet::size(void) const
{
    return m_spots.size();
}
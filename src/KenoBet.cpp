/**
 * @file KenoBet.cpp
 * @author Allan de Miranda and Josue Claudio
 * @brief Class definition
 * @version 0.1
 * @date 2018-10-11
 */

#include "KenoBet.h" /// Include the header

bool KenoBet::catch_bet(char *fileName, std::vector <cash_type> &bet){
    std::string route = "../data/"; // <! Begin route
    route = route + fileName; // <! Complete route
    std::ifstream ifs(route); // <! Open Route
    if(!ifs.good()){
        return false;
    }
    cash_type valuer;
    while( ifs >> valuer ){
        bet.push_back(valuer);
    }
    if( not ifs.eof() )
        return false;
	ifs.close();
    return true;
}

bool KenoBet::initialization_parameters(char *FileName, KenoBet &bet){
    std::vector <cash_type> parameters;
    if(!catch_bet(FileName, parameters)){
        return false;
    }
    if(!bet.set_wage_initial( (parameters[0]) ) ){  
        return false;
    }
    
    bet.set_wage( (parameters[0]) );
    if(!bet.set_rounds((int)(parameters[1]))){
        return false;
    }
    for(number_type i(2); i<(parameters.size()); ++i){
        if(!bet.add_number((number_type)(parameters[i]))){
            return true;
        }
    } 
    return true;
}

void KenoBet::This_is_round(const number_type &round_now, KenoBet &bet){
    std::cout << "         --------------------------------------------------" << std::endl;
    std::cout << "         This is round #" << round_now << " of " << bet.get_rounds() << ", and your wage is $" << std::setprecision(2) << bet.get_wage_initial() / bet.get_rounds() << ". Good luck!" << std::endl;
    bet.set_wage( bet.get_wage() - ( bet.get_wage_initial() / bet.get_rounds() ) );
    set_of_numbers_type hits_are = ( bet.get_hits(bet.set_hits()) );
    std::cout << "         The hits are: [ ";
    // <! hits vector
    for(number_type i : hits_are){ 
        std::cout << i << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << std::endl;
    // <! Vector with the values that were drawn in the draw
    set_of_numbers_type spots = bet.get_spots();
    set_of_numbers_type You_hit;
    number_type num_hits(0); // Number of hits
    for(number_type i(0); i < spots.capacity(); ++i){
        if(std::binary_search(hits_are.begin(), hits_are.end(), spots[i])){
            You_hit.push_back( spots[i] );
            ++num_hits;
        }
    }    
    // <! Hit check number
    if(num_hits > 0){
        // <! Showing successful numbers
        std::cout << "         You hit the following number(s) [ ";
        for(number_type i : You_hit){
            std::cout << i << " ";  
        }
        std::cout << "], a total of " << You_hit.size() << " hits out of " << bet.size() << std::endl; 
        // <! Set cash currente and payment        
        bet.set_m_round_payment( ( bet.get_wage_initial() / bet.get_rounds() ) * (payout_table[bet.get_spots().size()-1][You_hit.size()]));
        // <! Sho the payment da table
        std::cout << "         Payout rate is " <<payout_table[bet.get_spots().size()-1][You_hit.size()] << ", thus you came out with: $" << bet.get_m_round_payment() << std::endl;
        // <! Show the net balance
        bet.set_wage(bet.get_m_round_payment()+bet.get_wage());
        std::cout << "         Your net balance so far is: $" <<  std::abs( bet.get_wage() ) << " dollars." << std::endl;
    }
    else
    {
        std::cout << "         You did not hit any number" << std::endl;     
        // <! Show the net balance
        std::cout << "         Your net balance so far is: $" << std::abs( bet.get_wage() ) << " dollars." << std::endl;   
    }
}

bool KenoBet::add_number(number_type spot_)
{
    if( (spot_ > 0) and (spot_ < 81) )
    {
        m_spots.push_back(spot_);
        
        insertionSort(m_spots.begin(), m_spots.end());
        std::unique(m_spots.begin(), m_spots.end());
        
        auto last = std::unique(m_spots.begin(), m_spots.end());
        m_spots.erase( last, m_spots.end() );
        return true;
    }
    return true;
}

bool KenoBet::set_wage(cash_type wage_)
{
    m_wage = wage_;
    return (wage_ > 0);
}

void KenoBet::reset(void)
{
    m_spots.clear();
    m_wage = 0;
}

cash_type KenoBet::get_wage(void) const
{
    if( m_wage == 0 )
        return std::abs( m_wage );
    return m_wage;
}

size_t KenoBet::size(void) const
{
    return m_spots.size();
}

bool KenoBet::set_rounds(const int &rounds)
{
    if(rounds > 0)
    {
        m_rounds = rounds;
    }
    return (rounds > 0);
}

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
    return (wage_initial > 0);  
}

cash_type KenoBet::get_wage_initial(void) const
{
    return m_wage_initial;
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

set_of_numbers_type KenoBet::set_hits(void)
{
    std::random_device rd;
    std::mt19937 mt( rd() ); 
    std::uniform_int_distribution<number_type> dist(1, 80);
    set_of_numbers_type hits;
    for(int i(0); i<15; ++i){
        while(true){
            auto new_rand = dist(mt);
            if(std::binary_search(hits.begin(), hits.end(), new_rand)){
                continue;
            } else {
                hits.push_back(new_rand);
                break;
            } 
        }
        insertionSort(hits.begin(), hits.end());
    }   
    return hits;
}

set_of_numbers_type KenoBet::get_hits(const set_of_numbers_type &hits_) const
{
    return hits_;
}

template<class T>
void KenoBet::insertionSort( T first, T last )
{
    for( auto i(1); first+i < last; ++i )
    {
        auto escolhido = *(first+i);
        auto j = (i-1);

        for( /* empty */ ; (j >= 0) and ( *(first+j) > escolhido); --j )
        {
            *(first+j+1) = *(first+j);
        }
        *(first+j+1) = escolhido;
    }
}


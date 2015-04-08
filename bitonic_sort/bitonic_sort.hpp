/*
* Copyright 2015 Ryan H. Lewis
* This code is released under the BSD see LICENSE
*/
#ifndef BITONIC_SORT_HPP
#define BITONIC_SORT_HPP

#include <algorithm>
#include <iterator>
#include <cmath>
#include <cassert>
#include <vector>


namespace distributed{

namespace detail {
constexpr bool UP =1;
constexpr bool DOWN=0;
bool is_power_two( std::size_t x){ return !(x & x - 1) && x ; }

std::size_t power_two_below( std::size_t x){ 
	std::size_t r=2; 
	while( r < x){ r*=2; } return r/2;  
}

std::size_t power_two_above( std::size_t x){
	return 2*power_two_below( x); 
}


} //end namespace detail

namespace debug{
template< typename Communicator>
void print_partners( Communicator& world, std::size_t partner){
  for( auto r = 0; r < world.size(); ++r){
	if( r == world.rank()){
		std::cout << world.rank() << "-" << partner << " |  " << std::flush;
	}
	world.barrier();
   }
   world.barrier();
   if( world.rank() == 0){ std::cout << std::endl << std::flush; }
   world.barrier();
}

template< typename Communicator, typename Iterator>
void print_list( Communicator & world, Iterator begin, Iterator end){
for( auto r = 0; r < world.size(); ++r){
	if( r == world.rank()){
	for( auto i = begin; i != end; ++i){ std::cout << *i << " " << std::flush;}
	if( r != world.size()-1){ std::cout << "\b|" << std::flush; }
	}
	world.barrier();
}
if( world.rank() == 0){ std::cout << std::endl << std::flush; }
world.barrier();
}
}

template< bool direction,
	  typename Communicator, 
	  typename Vector, 
	  typename Vector1, 
	  typename Less>
void exchange_and_merge( Communicator& world, 
			 std::size_t partner,
			 Vector& our_data, 
			 Vector1& their_data, 
			 Less& less){ 
	//TODO: Finish ME
} 

template< typename Communicator, typename Range, typename Less> 
void bitonic_sort_binary(Communicator& world, Range& our_data, Less& less){
  typedef typename Range::value_type T;
  std::vector< T> their_data;
  for (std::size_t i = 2; i <= world.size(); i*=2){
      bool ith_bit_unset = ((world.rank() & i) == 0);
      bool ith_bit_set = !ith_bit_unset;
      std::size_t l = log2( i);
      for (std::size_t j = (1 << (l-1)); j > 0; j >>= 1) {
       std::size_t partner = world.rank() ^ j;
       bool jth_bit_unset = (world.rank() < partner);
       bool jth_bit_set = !jth_bit_unset;

       //if( world.rank() == 0){ std::cout << "l = " << l <<std::endl; }
       //debug::print_partners( world, partner);
       //debug::print_list( world, our_data.begin(), our_data.end());
	//either we are to the left of our neighbor and ith_bit_unset
	//or we are to the right of our neighbor and the ith_bit_set	
       if ( (jth_bit_unset && ith_bit_unset) || (ith_bit_set && jth_bit_set)){ 
          exchange_and_merge< detail::DOWN>( world, partner, 
             	         		     our_data, their_data, 
					     less);
       }else{
         exchange_and_merge< detail::UP>( world, partner, 
					  our_data, their_data, 
					  less);
      }
      // debug::print_list( world, our_data.begin(), our_data.end());
      // if( world.rank() == 0){ std::cout << "----------------------------------"
      //  				 << std::endl << std::flush; }
      // world.barrier();
    } //end decreasing 
  } //end outer loop
}

} //end namespace distributed

#endif //BITONIC_SORT_HPP

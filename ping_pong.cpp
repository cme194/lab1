#include <boost/mpi.hpp>

#define MESSAGE_COUNT 1000
namespace mpi = boost::mpi;
template< typename Stream, typename V>
void print_times( Stream out, const V&v, std::size_t m){
	for( auto& t : v){
		out << m << " " <<  v[ i] << std::endl; 
		m *= 2;
	}
	out << std::endl;
}

int main( int argc, char** argv){
	mpi::environment env( argc, argv);
	mpi::communicator world;
	if (world.size() > 2){ env.abort( 1); return 1; }
	int max_message_size = 4096;

	//TODO: put your code here

	if( world.rank() == 0){
		print_times( std::cout, times, 2, max_message_size);
		world.barrier();
	}
	else{
		world.barrier();
		print_times( std::cout, times, 2, max_message_size);
	}
	return 0;		

}

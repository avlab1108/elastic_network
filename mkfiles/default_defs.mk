export CXX
export CXXFLAGS
export LDFLAGS
export RM

RM 										= /bin/rm -f

COMPILER_LOCATION 		= /usr
CXX_NAME							= mpic++

CXX_SPECIFIC_FLAGS   	= -pipe -pedantic -Wall -Werror

AR 										= /usr/bin/ar
ARFLAGS 							= vcq

CXX                  	= $(COMPILER_LOCATION)/bin/$(CXX_NAME)
LD									 	= /usr/bin/ld

CPLUSPLUS_SLIB  			= $(CXX) -shared

SLIB_ALL  						= -Wl,--whole-archive
SLIB_NONE 						= -Wl,--no-whole-archive

BOOST_INCLUDE_DIR			= -I/home/minas/third_party/boost/install/include
BOOST_LIB_DIR					= -L/home/minas/third_party/boost/install/lib
BOOST_LIBS						= -lboost_system -lboost_serialization -lboost_mpi -lboost_filesystem -lboost_program_options

CXXFLAGS             	= -std=c++11 -fPIC -Werror -MD -O3 -fopenmp -I. $(BOOST_INCLUDE_DIR)
LDFLAGS              	= $(BOOST_LIB_DIR) $(BOOST_LIBS)

-include overrides.mk

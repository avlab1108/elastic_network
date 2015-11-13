export CXX
export CXXFLAGS
export LDFLAGS
export RM

RM 										= /bin/rm -f

#COMPILER_LOCATION 		= /usr
#CXX_NAME							= c++
COMPILER_LOCATION 		= /home/minas/tasks/graph_new/mpich/install
CXX_NAME							= mpic++

CXX_SPECIFIC_FLAGS   	= -pipe -pedantic -Wall -Werror

AR 										= /usr/bin/ar
ARFLAGS 							= vcq

CXX                  	= $(COMPILER_LOCATION)/bin/$(CXX_NAME)
LD									 	= /usr/bin/ld

CPLUSPLUS_SLIB  			= $(CXX) -shared

SLIB_ALL  						= -Wl,--whole-archive
SLIB_NONE 						= -Wl,--no-whole-archive

BOOST_INCLUDE					= -I/home/minas/tasks/graph_new/boost/install/include
BOOST_LIBS						= -L/home/minas/tasks/graph_new/boost/install/lib -lboost_system -lboost_serialization -lboost_mpi -lboost_filesystem

CXXFLAGS             	= -std=c++11 -fPIC -Werror -MD -g -I. $(BOOST_INCLUDE)
LDFLAGS              	= $(BOOST_LIBS)

-include overrides.mk

export CXX
export CXXFLAGS
export LDFLAGS
export RM

RM 										= /bin/rm -f

COMPILER_LOCATION 		= /usr
CXX_NAME 							= c++

CXX_SPECIFIC_FLAGS   	= -pipe -pedantic -Wall -Werror

AR 										= /usr/bin/ar
ARFLAGS 							= vcq

CXX                  	= $(COMPILER_LOCATION)/bin/$(CXX_NAME)
LD									 	= /usr/bin/ld

CPLUSPLUS_SLIB  			= $(CXX) -shared

SLIB_ALL  						= -Wl,--whole-archive
SLIB_NONE 						= -Wl,--no-whole-archive

CXXFLAGS             	= -std=c++11 -fPIC -Werror -MD -g -I.
LDFLAGS              	=

-include overrides.mk

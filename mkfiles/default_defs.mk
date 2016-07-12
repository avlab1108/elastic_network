RM                     = /bin/rm -f

COMPILER_LOCATION     = /usr
CXX_NAME              = mpic++

CXX_SPECIFIC_FLAGS    = -pipe -pedantic -Wall

AR                    = /usr/bin/ar
ARFLAGS               = vcq

CXX                   = $(COMPILER_LOCATION)/bin/$(CXX_NAME)
LD                    = /usr/bin/ld

CPLUSPLUS_SLIB        = $(CXX) -shared

SLIB_ALL              = -Wl,--whole-archive
SLIB_NONE             = -Wl,--no-whole-archive

YAML_INCLUDE_DIR      =
YAML_LIB_DIR          =
YAML_LIB              = -lyaml-cpp

ARMADILLO_INCLUDE_DIR =
ARMADILLO_LIB_DIR     =
ARMADILLO_LIB         = -larmadillo

BOOST_INCLUDE_DIR     = -I/home/minas/third_party/boost/install/include
BOOST_LIB_DIR         = -I/home/minas/third_party/boost/install/lib
BOOST_LIBS            = -lboost_system -lboost_serialization -lboost_mpi -lboost_filesystem -lboost_program_options

CXXFLAGS              = -std=c++11 -fPIC -Wall -MD -O3 -fopenmp -I. $(BOOST_INCLUDE_DIR) $(YAML_INCLUDE_DIR) $(ARMADILLO_INCLUDE_DIR)
LDFLAGS               = -fopenmp $(BOOST_LIB_DIR) $(BOOST_LIBS) $(YAML_LIB_DIR) $(YAML_LIB) $(ARMADILLO_LIB_DIR) $(ARMADILLO_LIB)

-include overrides.mk

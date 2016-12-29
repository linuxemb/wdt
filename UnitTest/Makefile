
include ../../../../include.mk

# The application name.
APPNAME = unit_test

# Application version.
# The major.minor version is defined first. If "TESTBUILD" is defined when
# calling "Make" then the TESTBUILD number is appended to the version.
VERSION := 1.23
ifdef TESTBUILD
VERSION := $(VERSION).$(TESTBUILD)
endif

INC += -I. -I../
#LIB += -L.
LIB += -L../../../../OS/OAL
LIB += -L../
LIBS += -lwatchdogapi -loal -lboost_system -lboost_thread -lpthread -lboost_chrono -lboost_unit_test_framework
OPTIONS += -std=gnu++0x

# Default goal is "all".
ifeq ($(MAKECMDGOALS),)
override MAKECMDGOALS = all
endif

# Make a list of all .cpp source files in the current directory.
srcFiles = $(wildcard *.cpp) $(wildcard ../*.cpp)

# Create a list of object files from the source file list.
cpp_obj = $(addsuffix .o, $(basename $(srcFiles)))

# Make a list of all .cpp source files in the current directory.
protoFiles = $(wildcard ../*.proto)

protoCC = $(addsuffix .pb.cc, $(basename $(protoFiles)))
protoHH = $(addsuffix .pb.h, $(basename $(protoFiles)))

cc_obj = $(addsuffix .o, $(basename $(protoCC)))

# Make a list of header files.
headers = $(wildcard *.h) $(wildcard ../*.h)

# Build all goals

all:		$(APPNAME)

# Full build
full:		clean all package

# Clean-up
clean:
		$(RM) -f *.o
		$(RM) -f *~
		$(RM) -f core
		$(RM) -f $(APPNAME)
		$(RM) -f *.ipk
		$(RM) -fr ipk
		$(RM) -fr protoc_middleman $(protoCC) $(cpp_obj) $(cc_obj) $(protoHH)

# Build the OpenWRT package.
package:
		@echo "Empty target"

# Build the unit test.
unittest:
		@echo "Empty target"


# Create the object files.
$(cpp_obj):	%.o:	%.cpp $(headers)
#		echo "const char *version=\"$(VERSION)\";" > version.h
		$(GPP) $(DEFINES) $(INC) $(LIB) $(OPTIONS) -c $< -o $@

$(cc_obj):	%.o:	%.cc $(headers)
		echo "const char *version=\"$(VERSION)\";" > version.h
		$(GPP) $(DEFINES) $(INC) $(LIB) $(OPTIONS) -c $< -o $@

# Create the executable.
$(APPNAME):	 $(cc_obj) $(cpp_obj)  $(headers)
		$(GPP) $(DEFINES) $(INC) $(LIB) $(OPTIONS) \
			$(cpp_obj) $(cc_obj) $(LIBS) -o $(APPNAME)

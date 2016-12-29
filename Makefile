
include ../../../include.mk

# Application version.
# The major.minor version is defined first. If "TESTBUILD" is defined when
# calling "Make" then the TESTBUILD number is appended to the version.
VERSION := 0.1
ifdef TESTBUILD
VERSION := $(VERSION).$(TESTBUILD)
endif

# Library file names.
BASENAME = libwatchdogapi
SONAME = $(BASENAME).so
LIBNAME = $(BASENAME).so.$(VERSION)
STATICLIBNAME = $(BASENAME).a

INCPATHS = ../commsAPI
DEPENDSLIBPATH = ../commsAPI

INC += $(addprefix -I, $(INCPATHS))
LIB += -L../../../OS/OAL
LIBS = += -loal
OPTIONS += -fpic -std=gnu++0x

# Make a list of all .cpp source files in the current directory.
srcFiles = $(wildcard *.cpp)

# Create a list of object files from the source file list.
cpp_obj = $(addsuffix .o, $(basename $(srcFiles)))


# Make a list of header files.
headers = $(wildcard *.h)

# Build all goals
all:		dependlibs $(LIBNAME)

dependlibs:
		make -C $(DEPENDSLIBPATH)

# Full build
full:		clean all 

#test:   all
#		make -C test

install:
		mkdir -p $(HOME)/lib
		$(CP)  $(LIBNAME) $(STATICLIBNAME) $(HOME)/lib
		$(LN)  -sf $(HOME)/lib/$(LIBNAME) $(HOME)/lib/$(SONAME)
# Clean-up
clean:
		$(RM) -f *.o
		$(RM) -f *~
		$(RM) -f core
		$(RM) -f $(LIBNAME)
		$(RM) -f $(SONAME)
		$(RM) -f $(STATICLIBNAME)
		$(RM) -f *.ipk
		$(RM) -fr ipk
		$(RM) -fr protoc_middleman
		$(RM) -fr $(protoCC) $(protoHH)
		#make -C test clean
		$(RM) -f deps.out

# Unit tests
.PHONY: unittest
unittest:
		@echo "Unit test target."

# Create an OpenWRT package.
package:
ifeq ($(PLATFORM),qca)
		@echo "Empty target"
else
		@echo "Packages are not built for the PC target."
endif

# Create object files
$(cpp_obj):	%.o:	%.cpp $(headers)
		echo "const char *version=\"$(VERSION)\";" > version.h
		$(GPP) $(DEFINES) $(INC) $(LIB) $(OPTIONS) -c $< -o $@

$(cc_obj):	%.o:	%.cc $(headers)
		echo "const char *version=\"$(VERSION)\";" > version.h
		$(GPP) $(DEFINES) $(INC) $(LIB) $(OPTIONS) -c $< -o $@

# Create the library
$(LIBNAME): $(cc_obj) $(cpp_obj)  $(headers)
		echo $(srcCCFiles)
		$(AR) -r $(STATICLIBNAME) $(cpp_obj)  $(cc_obj)
		$(GCC) -shared -Wl,-soname,$(SONAME) $(LIB) -o $(LIBNAME) \
			$(cpp_obj) $(cc_obj) -lc
		$(LN) -sf $(LIBNAME) $(SONAME)

-include deps.out

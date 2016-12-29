#******************************************************************************

include ../../../../include.mk

# The application name.
APPNAME = WatchdogLib 
TEST =	WatchdogLib 
# Application version.
# The major.minor version is defined first. If "TESTBUILD" is defined when
# calling "Make" then the TESTBUILD number is appended to the version.
VERSION := 1.0
ifdef TESTBUILD
VERSION := $(VERSION).$(TESTBUILD)
endif


INCPATH = 	/usr/include/boost \
           ../../../../OS/OAL\
           ../

LIBSPATH = 	../../../../OS/OAL\
		../
LIBNAMES =  	boost_system \
             boost_thread pthread\
             boost_chrono boost_date_time \
             boost_unit_test_framework\
             oal

INC = $(addprefix -I, $(INCPATH))
LIB = $(addprefix -L, $(LIBSPATH))
LIBS = $(addprefix -l, $(LIBNAMES))
RPATHCMD = -Wl,-rpath=../../../../OS/OAL

ifndef OPTIONS
OPTIONS = -Wall -Werror -Wl,--no-as-needed -fpic -std=gnu++0x $(RPATHCMD)
else
OPTIONS += $(RPATHCMD) -std=gnu++0x
endif

# Make list for source files

srcFiles := $(wildcard *.cpp))
          


# Create a list of object files from the source file list.
cpp_obj = $(addsuffix .o, $(basename $(srcFiles)))

# Make a list of header files.
headers = $(wildcard *.h)

# Build all goals
.PHONY:	all
all:		$(APPNAME)

.PHONE: docs
docs:
		$(DOXYGEN) -g doxyfile
		$(DOXYGEN) doxyfile

# Full build
.PHONY:	full
full:		clean all package

# Clean-up
.PHONY:	clean
clean:
		$(RM) -f *.o
		$(RM) -f *~
		$(RM) -f core
		$(RM) -f $(APPNAME)
		$(RM) -f *.ipk
		$(RM) -f version.h
		$(RM) -fr ipk
		$(RM) -fr latex
		$(RM) -fr html
		$(RM) -f deps.out


# Build the OpenWRT package.
.PHONY:	package
package:
		(\
		mkdir -p $(HOME)/ipk; \
		mkdir -p ipk/usr/bin; \
		mkdir -p ipk/CONTROL; \
		echo "Package: $(APPNAME)" > ipk/CONTROL/control;\
		echo "Version: $(VERSION)" >> ipk/CONTROL/control;\
		echo "Depends:" >> ipk/CONTROL/control;\
		echo "Provides:" >> ipk/CONTROL/control;\
		echo "Source: $(srcFiles)" >> ipk/CONTROL/control;\
		echo "Section: CoreFramework" >> ipk/CONTROL/control;\
		echo "Essential: no" >> ipk/CONTROL/control;\
		echo "Priority: optional" >> ipk/CONTROL/control;\
		echo "Maintainer: Tyco Developers" >> ipk/CONTROL/control;\
		echo "Architecture: ipq806x" >> ipk/CONTROL/control;\
		echo "Installed-Size: " >> ipk/CONTROL/control;\
		echo "Description:  This package contains an application for local socket." \
			 >> ipk/CONTROL/control;\
		)
		$(CP) $(APPNAME) ipk/usr/bin
		$(IPKGBUILD) -c -o 0 -g 0 ipk
#		$(CP) *.ipk $(HOME)/ipk

# Create the object files.
$(cpp_obj):	%.o: %.cpp $(headers) version.h
		$(GPP) $(DEFINES) $(INC) $(LIB) $(OPTIONS) -c $< -o $@

# Create the executable.
$(APPNAME):	$(cpp_obj) $(headers)
		$(GPP) $(DEFINES) $(INC) $(LIB) $(OPTIONS) \
		$(cpp_obj) $(LIBS) -o $(APPNAME)

# Create the version header file.
version.h:
		echo "const char *version=\"$(VERSION)\";" > version.h




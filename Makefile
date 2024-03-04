
# -- S E T T I N G S ----------------------------------------------------------

# set default target
.DEFAULT_GOAL := all

# use one shell for all commands
.ONESHELL:

# delete intermediate files on error
.DELETE_ON_ERROR:

# silent mode
.SILENT:

# set shell program
override SHELL := $(shell which zsh)

# set shell flags
.SHELLFLAGS := -d -f -c -e -o pipefail -u

# set make flags
override MAKEFLAGS += --warn-undefined-variables --no-builtin-rules



# -- O P E R A T I N G  S Y S T E M -------------------------------------------

# Detect operating system
override OS := $(shell uname -s)

# check for macOSX
ifeq ($(OS), Darwin)
    override PLATFORM   := macosx
    override THREAD     := $(shell sysctl -n hw.ncpu)
# check for Linux
else ifeq ($(OS), Linux)
    override PLATFORM   := linux
    override THREAD     := $(shell nproc)
# unsupported OS
else
    $(error $(shell echo "Unsupported OS: \x1b[31m$(OS)\x1b[0m"))
endif



# -- T A R G E T S ------------------------------------------------------------

# project name
override PROJECT = Matt_daemon

# main executable
override EXEC = $(PROJECT)

# compile commands for clangd
override COMPILE_COMMANDS = compile_commands.json



# -- D I R E C T O R I E S ----------------------------------------------------

# source directory
override SRCDIR := sources

# include directory
override INCDIR := includes

# build directory
override BLDDIR := build

# object directory
override OBJDIR := $(BLDDIR)/object

# dependency directory
override DEPDIR := $(BLDDIR)/dependency

# json directory
override JSNDIR := $(BLDDIR)/json


# -- D Y N A M I C  V A R I A B L E S -----------------------------------------

# include flags
INCLUDES ?=

# linker flags
LDFLAGS ?=



# -- S O U R C E S ------------------------------------------------------------

# get all source files
override SRC := $(shell find $(SRCDIR) -type f -name '*.cpp')

# get all header files
override HDR := $(shell find $(INCDIR) -type f -name '*.hpp')

# get all header directories
override HDRDIR := $(sort $(dir $(HDR)))

# pattern substitution for object files
override OBJ := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o,    $(SRC))

# pattern substitution for dependency files
override DEP := $(patsubst $(OBJDIR)/%.o,   $(DEPDIR)/%.d,    $(OBJ))

# pattern substitution for compile commands
override JSN := $(patsubst $(SRCDIR)/%.cpp, $(JSNDIR)/%.json, $(SRC))

#
override HIR := $(sort $(dir $(SRC)))
override OBJHIR := $(HIR:$(SRCDIR)/%=$(OBJDIR)/%)
override DEPHIR := $(HIR:$(SRCDIR)/%=$(DEPDIR)/%)
override JSNHIR := $(HIR:$(SRCDIR)/%=$(JSNDIR)/%)


# include flags
INCLUDES += $(addprefix -I,$(HDRDIR))



# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# make directory if not exists
override MKDIR := mkdir -p

# remove recursively force
override RM := rm -rf

# compiler
override CXX := $(shell which clang++)

# compiler standard
override STD := -std=c++2a

# compiler optimization
override OPT := -O0

# compiler debug
override DEBUG := -g3 -gdwarf-2

# warning scope
override CXXFLAGS := -Wall -Wextra

# warning impact
override CXXFLAGS += -Werror

# standard respect
override CXXFLAGS += -Wpedantic -Weffc++

# unused suppression
override CXXFLAGS += -Wno-unused -Wno-unused-variable -Wno-unused-parameter

# optimization
override CXXFLAGS += -Winline

# type conversion
override CXXFLAGS += -Wconversion -Wsign-conversion -Wfloat-conversion -Wnarrowing

# shadowing
override CXXFLAGS += -Wshadow



# dependency flags
override DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# compile commands flags
override CMPFLAGS = -MJ $(JSNDIR)/$*.json


# command line defines
DEF :=

# defines flags
override DEFINES := $(addprefix -D,$(DEF))



# -- C O L O R  S E T T I N G S -----------------------------------------------

define COLOR
	@printf "\e[7;32m %s \e[0m\n" $(1)
endef

define LINES
 @printf "\e[90m%s\e[0m\n" '--------------------------------------------'
endef


# -- P H O N Y  T A R G E T S -------------------------------------------------

# phony targets
.PHONY: all clean fclean re ascii obj exec leaks


# -- M A I N  T A R G E T S ---------------------------------------------------

all: ascii obj $(EXEC)
	$(call LINES)
	$(call COLOR,"done ◝(ᵔᵕᵔ)◜")
	echo -n '\n'

$(EXEC): $(OBJ) $(COMPILE_COMMANDS)
	$(call LINES)
	$(call COLOR,"linking")
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)
	ls -la $@


# -- C O M P I L A T I O N ----------------------------------------------------

# self call with threads
obj:
	$(call LINES)
	$(call COLOR,"compilation")
	$(MAKE) --silent -j$(THREAD) $(OBJ)

-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp Makefile | $(OBJHIR) $(DEPHIR) $(JSNHIR)
	$(CXX) $(STD) $(OPT) $(DEBUG) $(CXXFLAGS) $(DEFINES) $(CMPFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@
	print -f '- %s\n' $@


# -- C O M P I L E  C O M M A N D S -------------------------------------------

$(COMPILE_COMMANDS): $(JSN)
	$(call LINES)
	$(call COLOR,"compile database")
	echo "[\n"$$(cat $(JSN) | sed '$$s/,\s*$$//')"\n]" | jq > $@
	ls -la $@


# -- D I R E C T O R I E S  C R E A T I O N -----------------------------------

$(OBJHIR) $(DEPHIR) $(JSNHIR):
	$(MKDIR) $@


# -- C L E A N I N G ----------------------------------------------------------

clean:
	$(call LINES)
	$(call COLOR,"cleaning project")
	$(RM) $(BLDDIR) $(COMPILE_COMMANDS) .cache

fclean: clean
	$(call COLOR,"full cleaning project")
	$(RM) $(EXEC)


# -- L E A K S ----------------------------------------------------------------

leaks: ascii $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes $(EXEC)



# -- R E C O M P I L E --------------------------------------------------------

re: clean all


# -- A S C I I  A R T ---------------------------------------------------------

ascii:
	echo '\x1b[32m' \
		'   ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁	\n' \
		'  ╱        ╲╱        ╲╱    ╱   ╲╱        ╲	\n' \
		' ╱         ╱         ╱         ╱         ╱	\n' \
		'╱         ╱         ╱        ▁╱       ▁▁╱	\n' \
		'╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱	\n' \
		'\t\t\tGNU Make:' $(MAKE_VERSION)'\x1b[0m\n'




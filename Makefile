# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artblin <artblin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/10 19:37:03 by artblin           #+#    #+#              #
#    Updated: 2024/05/10 19:38:06 by artblin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


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
override PROJECT := Matt_daemon

# main executable
override EXEC := $(PROJECT)

# compile commands for clangd
override COMPILE_DB := compile_commands.json



# -- D I R E C T O R I E S ----------------------------------------------------

# source directory
override SRC_DIR := sources

# include directory
override INC_DIR := includes


# -- S O U R C E S ------------------------------------------------------------

# get all source files
override SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')

# object files
override OBJS := $(SRCS:%.cpp=%.o)

# dependency files
override DEPS := $(OBJS:%.o=%.d)


# -- T O O L S ----------------------------------------------------------------

# make directory if not exists
override MKDIR := mkdir -p

# remove recursively force
override RM := rm -rf



# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# compiler
override CXX := $(shell which clang++)

# compiler standard
override STD := -std=c++2a

# compiler optimization
override OPT := -O0

# compiler debug
override DEBUG := -g3 -gdwarf-2

# warning scope
override FLAGS := -Wall -Wextra

# warning impact
override FLAGS += -Werror

# standard respect
override FLAGS += -Wpedantic -Weffc++

# unused suppression
override FLAGS += -Wno-unused -Wno-unused-variable -Wno-unused-parameter

# optimization
override FLAGS += -Winline

# type conversion
override FLAGS += -Wconversion -Wsign-conversion -Wfloat-conversion -Wnarrowing

# shadowing
override FLAGS += -Wshadow

# include flags
override INCLUDES := -I$(INC_DIR)

# dependency flags
override DEPFLAGS = -MT $@ -MMD -MP -MF $*.d

# cxx flags
override CXXFLAGS := $(STD) $(OPT) $(DEBUG) $(FLAGS) $(INCLUDES)



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

all: ascii $(EXEC)
	$(call LINES)
	$(call COLOR,"done ◝(ᵔᵕᵔ)◜")
	echo -n '\n'

$(EXEC): $(OBJS)
	$(call LINES)
	$(call COLOR,"linking")
	$(CXX) $^ -o $@
	ls -la $@

-include $(DEPS)
%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@
	print -f '- %s\n' $@



# -- C L E A N I N G ----------------------------------------------------------

clean:
	$(call LINES)
	$(call COLOR,"cleaning project")
	$(RM) $(OBJS) $(DEPS) .cache

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




CXX = clang++
CXXFLAGS = -O0 -ggdb -Wall -Werror -pedantic -std=c++14
LDFLAGS =
LDLIBS =

SRCDIR = src
INCDIR = inc

INCLUDES = -I$(INCDIR)

BUILDDIR = build

SRCS := $(shell find $(SRCDIR) -name '*.cpp')
HDRS := $(shell find $(INCDIR) -name '*.hpp')
FILES = $(SRCS) $(HDRS)

OBJS = $(addprefix $(BUILDDIR)/, $(notdir $(subst .cpp,.o, $(SRCS))))
OUT = $(BUILDDIR)/main.out

EDITOR = subl

# ==================
# build targets

run: all
	@echo "Running..." && \
	echo "==========" && \
	$(OUT)

all: $(OUT)

$(OUT): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(OUT) $(OBJS) $(LDLIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ 

clean:
	rm -rf $(BUILDDIR)/*

# ==================
# utility targets

edit: 
	$(EDITOR) $(FILES)

editDir:
	$(EDITOR) $(SRCDIR)
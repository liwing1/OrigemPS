CC = g++
INCDIR = header
SRCDIR = src
OBJDIR = obj
CFLAGS = -c -Werror -I$(INCDIR)
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
EXE = ./a.out

all: clean $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJDIR)/*.o -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJDIR)/*.o $(EXE) 
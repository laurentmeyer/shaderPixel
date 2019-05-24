CC = 		clang++
CFLAGS =	-g -Wall -Wextra -std=c++11
# CFLAGS =	-g -Wall -Wextra -Werror -std=c++11
BINARY =	openGLProject
BUILDDIR =	builds

HEADERDIR = includes
HEADERFILES = Camera.h  \
							Shader.h  \
							Transform.h  \
							Window.h  \

SOURCEDIR =	srcs
SRCFILES = main.cpp			\

GLFW = 		./libs/GLFW
GLEW = 		./libs/GLEW

CCHEADERS = -I./$(HEADERDIR) \
			-I$(GLFW)/include/ \
			-I$(GLEW)/include/ \
			-I$(LIBFT)/libft/includes \

CCLIBS =	-L$(GLFW)/lib -lglfw		\
			-L$(GLEW)/lib -lGLEW		\

CCFRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

SOURCES = $(SRCFILES:%.cpp=$(SOURCEDIR)/%.cpp)
OBJECTS = $(SOURCES:$(SOURCEDIR)/%.cpp=$(BUILDDIR)/%.o)

.PHONY: clean fclean all re norme $(LIBFT)/libft.a

all : $(BINARY)

$(BINARY) : $(OBJECTS)
	@$(CC) $(CCHEADERS) $(CCLIBS) $(OBJECTS) $(CCFRAMEWORKS) -o $(BINARY)

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CCHEADERS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(BINARY)

run: re
	./$(BINARY)

re: fclean all
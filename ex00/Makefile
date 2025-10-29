NAME =		easyfind

CXX =		c++

CXXFLAGS =	-Wall -Wextra -Werror -std=c++98

SRCS =		main.cpp
			

OBJS =		$(SRCS:.cpp=.o)

HEADERS =	easyfind.hpp

# ANSI color codes
YELLOW = \033[1;33m
CYAN = \033[1;36m
GREEN = \033[1;32m
RED = \033[1;31m
NC = \033[0m

# Emojis
WIP =	🚧
DONE =	✅

# Total number of source files
TOTAL_FILES = $(words $(SRCS))

# Counter for compiled files
COMPILED_FILES = 0

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)$(WIP) Compiling $@ $(WIP)$(NC)"
	@if $(CXX) $(CXXFLAGS) -o $@ $(OBJS); then \
		echo "$(GREEN)$(DONE) Successfully compiled $@ $(DONE)$(NC)"; \
	else \
		echo "$(RED)❌ Compilation failed with errors ❌$(NC)"; \
		exit 1; \
	fi

%.o: %.cpp $(HEADERS)
	$(eval COMPILED_FILES=$(shell expr $(COMPILED_FILES) + 1))
	$(eval PERCENTAGE=$(shell expr $(COMPILED_FILES) \* 100 / $(TOTAL_FILES)))
	@echo "$(YELLOW)$(WIP) $< ($(YELLOW)$(PERCENTAGE)%$(NC) [$(CYAN)$(COMPILED_FILES)/$(TOTAL_FILES)$(NC]) $(WIP)$(NC)"
	@if ! $(CXX) $(CXXFLAGS) -c $< -o $@; then \
		echo "$(RED)❌ Error compiling $< ❌$(NC)"; \
		exit 1; \
	fi

clean:
	@rm -f $(OBJS)
	@echo "$(GREEN)$(DONE) Cleaned object files $(DONE)$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)$(DONE) Fully cleaned $(NAME) $(DONE)$(NC)"

re: fclean all

.PHONY: all clean fclean re
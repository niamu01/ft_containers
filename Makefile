NAME = ft_containers
CXXFLAGS = -Wall -Wextra -Werror
#CXXFLAGS += -g -fsanitize=address
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY : all
all : $(NAME)

$(NAME) : $(OBJS)
	c++ $(CXXFLAGS) -c $(SRCS)
	c++ $(CXXFLAGS) $(OBJS) -o $(NAME)

.PHONY : clean
clean :
	rm -rf $(OBJS)

.PHONY : fclean
fclean :
	make clean
	rm -rf $(NAME)

.PHONY : re
re :
	make fclean
	make all

NAME = ft_containers
CFLAGS = -Wall -Wextra -Werror -g
SRCS = test.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY : all
all : $(NAME)

$(NAME) : $(OBJS)
	c++ $(CFLAGS) -c $(SRCS)
	c++ $(CFLAGS) $(OBJS) -o $(NAME)

.PHONY : clean
clean :
	rm -rf $(OBJS)

.PHONY : fclean
fclean : clean
	rm -rf $(NAME)

.PHONY : re
re :
	make fclean
	make all
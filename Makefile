NAME = a.out
CXXFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
SRCS = vector_test.cpp
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
fclean : clean
	rm -rf $(NAME)

.PHONY : re
re :
	make fclean
	make all
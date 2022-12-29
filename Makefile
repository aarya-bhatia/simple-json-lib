all: main

main: main.cpp.o json.cpp.o
	g++ $^ -o $@

%.cpp.o: %.cpp
	@mkdir -p $(dir $@);
	g++ -std=c++11 -Wall -Wextra -Werror -MMD -MP -g -c $< -o $@

clean:
	rm -rf *.o main

-include $(OBJ_DIR)/*.d

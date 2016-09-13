test: test_c_vector.o c_vector.o
	g++ -pthread $^ -I/usr/include /usr/lib/libgtest.a -o $@

test_c_vector.o: test_c_vector.cpp c_vector.h
	g++ -std=c++11 -Wall -Werror -c $< -o $@

main: main.o c_vector.o
	gcc $^ -o $@

main.o: main.c
	gcc -std=c99 -Wall -Werror -c $< -o $@

c_vector.o: c_vector_right_answer.c c_vector.h
	gcc -std=c99 -Wall -Werror -c $< -o $@

clean:
	rm -rf *.o test

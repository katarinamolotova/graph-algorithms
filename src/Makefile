WWW = -std=c++17 -Wall -Werror -Wextra
LIBS=-lgtest -lgmock -pthread

all: clean test

test: s21_graph_algorithms.a
	g++ $(WWW) $(LIBS) s21_graph_algorithms.a s21_test.cc -o test
	CK_FORKS=no leaks -atExit -- ./test	

s21_graph.o:
	g++ $(WWW) -c s21_graph.cc helpers/matrix.cc

s21_graph_algorithms.o:
	g++ $(WWW) -c helpers/*.cc s21_graph_algorithms.cc s21_graph.cc Tsm/*.cc

s21_graph_algorithms.a: clean
	rm -rf *.o
	make s21_graph_algorithms.o
	ar rcs s21_graph_algorithms.a *.o
	ranlib s21_graph_algorithms.a

s21_graph.a: clean
	g++ -c s21_graph.cc
	ar rcs s21_graph.a s21_graph.o
	ranlib s21_graph.a

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n ./*.cc ./*.h ./*/*.cc ./*/*.h

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf test
	rm -rf a.out

demo: s21_graph_algorithms.a
	g++ $(WWW) main.cc Interface/Interface.cc s21_graph_algorithms.a
	./a.out

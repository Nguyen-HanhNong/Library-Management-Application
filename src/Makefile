objects = Criteria.o Book.o Address.o Library.o main.o TestBook.o Tester.o
flags = -Wall -o

all: LibraryManagementApplication

LibraryManagementApplication: $(objects)
	g++ $(flags) LibraryManagementApplication $(objects)

main.o: main.cc 
	g++ -c main.cc

Tester.o: Tester.cc Tester.hh
	g++ -c Tester.cc

TestBook.o: TestBook.cc TestBook.hh
	g++ -c TestBook.cc

Library.o: Library.cc Library.hh
	g++ -c Library.cc

Address.o: Address.cc Address.hh
	g++ -c Address.cc

Criteria.o: Criteria.cc Criteria.hh
	g++ -c Criteria.cc
	
Book.o: Book.cc Book.hh
	g++ -c Book.cc

clean:
	rm -f LibraryManagementApplication *.o	
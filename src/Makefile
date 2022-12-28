main_classes = Criteria.o Book.o Address.o Library.o 
tester_classes = TestBook.o TestLibrary.o Tester.o
main_file = main.o 

flags = -Wall -o

all: LibraryManagementApplication

LibraryManagementApplication: $(main_classes) $(tester_classes) $(main_file)
	g++ $(flags) LibraryManagementApplication $(main_classes) $(tester_classes) $(main_file)

main.o: main.cc 
	g++ -c main.cc

Tester.o: Tester.cc Tester.hh
	g++ -c Tester.cc

TestLibrary.o: TestLibrary.cc TestLibrary.hh
	g++ -c TestLibrary.cc

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
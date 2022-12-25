objects = Criteria.o Book.o main.o TestBook.o Tester.o

all: LibraryManagementApplication

LibraryManagementApplication: $(objects)
	g++ -o LibraryManagementApplication $(objects)

main.o: main.cc 
	g++ -c main.cc

Tester.o: Tester.cc Tester.hh
	g++ -c Tester.cc

TestBook.o: TestBook.cc TestBook.hh
	g++ -c TestBook.cc

Criteria.o: Criteria.cc Criteria.hh
	g++ -c Criteria.cc
	
Book.o: Book.cc Book.hh
	g++ -c Book.cc

clean:
	rm -f LibraryManagementApplication *.o	
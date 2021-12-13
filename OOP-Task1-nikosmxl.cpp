// If K1 > L or K2 > L or K2 > K1, the program just ignores the unnecessary place_books/take_books without warning/exiting.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "bookcase.h"

int main(int argc, char *argv[]){

    if (argc != 5){
        std::cout << "Give the right data" << std::endl;
        return 1;
    }

    unsigned long currtime = time(NULL);
    srand( (unsigned int) currtime);

    const unsigned int Nmax = std::stoi(argv[1]);
    const unsigned int L = std::stoi(argv[2]);
    const unsigned int K1 = std::stoi(argv[3]);
    const unsigned int K2 = std::stoi(argv[4]);

    Bookcase mybookcase(Nmax);

    Book** books = new Book*[L];

    // Array of Books
    for (int i = 0 ; i < L ; i++){
        books[i] = new Book( std::to_string(i+6).c_str(), std::to_string(i+7).c_str(), i);      // Giving numbers for titles and author names
    }

    //Placing Books
    for (int i = 0 ; i < K1 ; i++){
        if (i < L){                                                                             // Explaining at line 1
            mybookcase.place_book(books[i], (rand() % 5) + 1);                                  // From 1 to 5
        }
    }

    //Taking Books
    for (int i = 0 ; i < K2 ; i++){
        if (i < L && i < K1){                                                                   // Explaining at line 1
            mybookcase.take_book((rand() % 5) + 1);                                             // From 1 to 5
        }
    }

    //Deleting
    for (int i = 0 ; i < L ; i++){
        delete books[i];
    }

    delete[] books;
    return 0;
} 
#include <iostream>
#include <cstring>

#include "bookcase.h"

Book::Book(const char* title1, const char* author1, int isbn1){
    title = new char[strlen(title1) + 1];
    strcpy(title, title1);
    author = new char[strlen(author1) + 1];
    strcpy(author, author1);
    isbn = isbn1;

    std::cout << "A book was constructed" << std::endl;
}

Book::~Book(void){
    delete[] title;
    delete[] author;

    std::cout << "A book was destructed" << std::endl;
}
Shelf::Shelf(int N){
    num_of_books = 0;
    Nmax = N;
    books = new Book*[Nmax];

    std::cout << "A shelf was constructed" << std::endl;
}

Shelf::~Shelf(void){

    delete[] books;

    std::cout << "A shelf was destructed" << std::endl;
}

Base::Base(void){

    std::cout << "The base was constructed" << std::endl;
}

Base::~Base(void){

    std::cout << "The base was destructed" << std::endl;
}

Locker::Locker(int N){
    upper = new Shelf(N);
    lower = new Shelf(N);

    std::cout << "The locker was constructed" << std::endl;
}

Locker::~Locker(void){
    delete lower;
    delete upper;

    std::cout << "The locker was destructed" << std::endl;
}

Bookcase::Bookcase(int N){

    base = new Base();
    upper = new Shelf(N);
    middle = new Shelf(N);
    lower = new Shelf(N);
    locker = new Locker(N);

    std::cout << "The bookcase was constructed" << std::endl;
}

Bookcase::~Bookcase(void){

    delete locker;
    delete lower;
    delete middle;
    delete upper;
    delete base;

    std::cout << "The bookcase was destructed" << std::endl;
}

void Book::print_book(void){
    std::cout << "Title: " << title << ", Author: " << author << ", ISBN: " << isbn << std::endl << std::endl;
}

bool Shelf::print_books(void){
    if (num_of_books == 0){
        std::cout << "Empty locker shelf. No book to print." << std::endl << std::endl;
        return false;
    }
    for (int i = 0 ; i < num_of_books ; i++){
        std::cout << "Book number " << i + 1 << ": ";
        books[i]->print_book();
    }
    return true;
}

void Locker::print_books(void){
    std::cout << "Printing every book of the upper locker shelf:" << std::endl;
    upper->print_books();
    std::cout << "Printing every book of the lower locker shelf:" << std::endl;
    lower->print_books();
}

void Bookcase::print_books(void){
    std::cout << "Printing every book of the upper shelf:" << std::endl;
    upper->print_books();

    std::cout << "Printing every book of the middle shelf:" << std::endl;
    middle->print_books();

    std::cout << "Printing every book of the lower shelf:" << std::endl;
    lower->print_books();

    std::cout << "Printing every book in the locker:" << std::endl;
    locker->print_books();

    std::cout << "Printed all the bookcase." << std::endl;
}

bool Shelf::place_book(Book* book){
    if (num_of_books < Nmax){
        books[num_of_books] = book;
        num_of_books++;
    }
    else{
        return false;
    }
    return true;
}

bool Locker::place_book(Book* book, int i){
    if (i == 1){
        return upper->place_book(book);
    }
    else{
        return lower->place_book(book);
    }
}

bool Bookcase::place_book(Book* book, int i){
    if (i == 1){
        if (upper->place_book(book) == true){
            std::cout << "A book was placed at the upper shelf of the bookcase." << std::endl;
        }
        else{
            std::cout << "The upper shelf of the bookcase is full. Failed to place book." << std::endl;
            return false;
        }
    }
    else if (i == 2){
        if (middle->place_book(book) == true){
            std::cout << "A book was placed at the middle shelf of the bookcase." << std::endl;
        }
        else{
            std::cout << "The middle shelf of the bookcase is full. Failed to place book." << std::endl;
            return false;
        }
    }
    else if (i == 3){
        if (lower->place_book(book) == true){
            std::cout << "A book was placed at the lower shelf of the bookcase." << std::endl;
        }
        else{
            std::cout << "The lower shelf of the bookcase is full. Failed to place book." << std::endl;
            return false;
        }
    }
    else if (i == 4 || i == 5){
        if (locker->place_book(book, i%3) == true){
            if (i%3 == 1){
                std::cout << "A book was placed at the upper locker shelf of the bookcase." << std::endl;
            }
            else{
                std::cout << "A book was placed at the lower locker shelf of the bookcase." << std::endl;
            }
        }
        else{
            if (i%3 == 1){
                std::cout << "The upper locker shelf of the bookcase is full. Failed to place book." << std::endl;
            }
            else{
                std::cout << "The lower locker shelf of the bookcase is full. Failed to place book." << std::endl;
            }
            return false;
        }
    }
    else{
        std::cout << "Give number <= 5" << std::endl;
        return false;
    }
    return true;
}

bool Shelf::take_book(void){
    if (num_of_books > 0){
        num_of_books--;
    }
    else{
        return false;
    }
    return true;
}

bool Locker::take_book(int i){
    if (i == 1){
        if (upper->take_book() == true){
            std::cout << "A book was taken from the upper locker shelf of the bookcase. The remaining books of the shelf are:" << std::endl;
            upper->print_books();
        }
        else{
            std::cout << "The upper locker shelf of the bookcase is empty. Failed to take book." << std::endl;
            return false;
        }
    }
    else{
        if (lower->take_book() == true){
            std::cout << "A book was taken from the lower locker shelf of the bookcase. The remaining books of the shelf are:" << std::endl;
            lower->print_books();
        }
        else{
            std::cout << "The lower locker shelf of the bookcase is empty. Failed to take book." << std::endl;
            return false;
        }
    }
    return true;
}

bool Bookcase::take_book(int i){
    if (i == 1){
        if (upper->take_book() == true){
            std::cout << "A book was taken from the upper shelf of the bookcase. The remaining books of the shelf are:" << std::endl;
            upper->print_books();
        }
        else{
            std::cout << "The upper shelf of the bookcase is empty. Failed to take book." << std::endl;
            return false;
        }
    }
    else if (i == 2){
        if (middle->take_book() == true){
            std::cout << "A book was taken from the middle shelf of the bookcase. The remaining books of the shelf are:" << std::endl;
            middle->print_books();
        }
        else{
            std::cout << "The middle shelf of the bookcase is empty. Failed to take book." << std::endl;
            return false;
        }
    }
    else if (i == 3){
        if (lower->take_book() == true){
            std::cout << "A book was taken from the lower shelf of the bookcase. The remaining books of the shelf are:" << std::endl;
            lower->print_books();
        }
        else{
            std::cout << "The lower shelf of the bookcase is empty. Failed to take book." << std::endl;
            return false;
        }
    }
    else if (i == 4 || i == 5){
        if (locker->take_book(i%3) == false){
            return false;
        }
    }
    else{
        std::cout << "Give number <= 5" << std::endl;
        return false;
    }
    print_books();
    return true;
} 
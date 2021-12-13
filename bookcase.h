#include <iostream>

class Book{
    char* title;
    char* author;
    int isbn;

    public:
    Book(const char*, const char*, int);        //Constructor
    ~Book();                                    //Destructor
    void print_book(void);
};

class Shelf{
    int num_of_books;
    int Nmax;
    Book **books;

    public:
    Shelf(int);                         //Constructor
    ~Shelf();                           //Destructor
    bool place_book(Book*);
    bool take_book(void);
    bool print_books(void);
};

class Locker{
    Shelf *upper;
    Shelf *lower;

    public:
    Locker(int);                        //Constructor
    ~Locker();                          //Destructor
    bool place_book(Book*, int);
    bool take_book(int);
    void print_books(void);
};

class Base{

    public:
    Base();                             //Constructor
    ~Base();                            //Destructor
};

class Bookcase{
    Base *base;
    Shelf *upper;
    Shelf *middle;
    Shelf *lower;
    Locker *locker;
    void print_books(void);

    public:
    Bookcase(int);                      //Constructor
    ~Bookcase();                        //Destructor
    bool place_book(Book*, int);
    bool take_book(int);
}; 
// Person base class header
#ifndef PERSON
#define PERSON

#include <iostream>

using namespace std;

class Person {

    public:
        Person(); // default constructor
        Person(int id); // id-only overloaded constructor
        Person(int id, string name, string level); // fully overloaded constructor
        Person(const Person& other); // copy constructor
        virtual ~Person(); // destructor

        virtual string toString() const;

        // overloaded operators
        bool operator==(const Person& other) const;
        bool operator!=(const Person& other) const;
        bool operator>(const Person& other) const;
        bool operator<(const Person& other) const;
        friend ostream& operator<<(ostream& os, const Person& other);

        int id;
        string name;
        string level;
};

#endif

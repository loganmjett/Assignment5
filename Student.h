// Student header file

#ifndef STUDENT
#define STUDENT

#include "Person.h"

class Student : public Person {
    public:
        Student(); // default constructor
        Student(int id); // id-only overloaded constructor
        Student(int id, string name, string level, string major, double gpa, int advisor); // fully overloaded constructor
        Student(const Student& other); // copy constructor
        virtual ~Student(); // destructor

        string toString() const override;

        string major;
        double gpa;
        int advisor;
};

#endif

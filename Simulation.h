#ifndef SIMULATION
#define SIMULATION

#include "Student.h"
#include "Faculty.h"
#include "BinarySearchTree.h"
#include "GenStack.h"
#include <iostream>

using namespace std;

class Simulation
{
  public:
    Simulation();
    ~Simulation();

    /* Used by FileManager */
    void addStudentFromFile(Student* student); // adds Student from file to the BST
    void addFacultyFromFile(Faculty* faculty); // adds Faculty from file to the BST


    /* User Options */
    void printStudentAscending(); // print all students and their information (sorted by ascending id #)
    void printFacultyAscending(); // print all faculty and their information (sorted by ascending id #)
    void displayStudent(); // find and display student information given a student id
    void displayFaculty(); // find and display faculty information given a faculty id
    void getStudentAdvisor(); // given a student id, print the name and info of their faculty advisor
    void getAdvisorStudents(); // given a faculty id, print ALL names and info of his/her advisees
    void addStudent(); // add a new student
    void deleteStudent(); // delete a student given the id
    void addFaculty(); // add a new faculty
    void deleteFaculty(); // delete a faculty given the id
    void changeStudentAdvisor(); // change a student's advisor given the student id and the new faculty id
    void removeAdvisee(); // remove an advisee from a faculty member given the ids
    void rollback(); // undo previous insertion/removal



    BinarySearchTree<Student> *studentBST;
    BinarySearchTree<Faculty> *facultyBST;
    GenStack<BinarySearchTree<Student>> *studentBSTImages;
    GenStack<BinarySearchTree<Faculty>> *facultyBSTImages;

    private:
        Student* getStudentByID(int id); // returns a student from BST given an id
        Faculty* getFacultyByID(int id); // returns a faculty from BST given an id
        int getInputID(string type); // gets id from cin (type: "Student" or "Faculty")
        void saveCurrentTrees(); // saves current tree data into the stacks
        bool changeStudentAdvisor(int sID); // changes a student's advisor given the student id
};

#endif

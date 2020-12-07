#include "Simulation.h"

using namespace std;

// default constructor
Simulation::Simulation()
{
    studentBST = new BinarySearchTree<Student>();
    facultyBST = new BinarySearchTree<Faculty>();
    studentBSTImages = new GenStack<BinarySearchTree<Student>>(5);
    facultyBSTImages = new GenStack<BinarySearchTree<Faculty>>(5);
}

// destructor
Simulation::~Simulation()
{
    delete studentBST;
    delete facultyBST;
    delete studentBSTImages;
    delete facultyBSTImages;
}

/* Used by FileManager */

// adds Student from file to the BST
void Simulation::addStudentFromFile(Student* student) {
    studentBST->insertNode(student);
}

// adds Faculty from file to the BST
void Simulation::addFacultyFromFile(Faculty* faculty) {
    facultyBST->insertNode(faculty);
}

// print all students and their information (sorted by ascending id #)
void Simulation::printStudentAscending() {
    cout << "    --- Student List ---" << endl;
    studentBST->printEntireTree();
}

// print all faculty and their information (sorted by ascending id #)
void Simulation::printFacultyAscending() {
    cout << "    --- Faculty List ---" << endl;
    facultyBST->printEntireTree();
}

// find and display student information given a student id
void Simulation::displayStudent() {

    int id = getInputID("Student");
    Student* s = getStudentByID(id);
    if(s == NULL)
        return;
    cout << *s << endl;
}

// find and display faculty information given a student id
void Simulation::displayFaculty() {

    int id = getInputID("Faculty");
    Faculty* f = getFacultyByID(id);
    if(f == NULL)
        return;
    cout << *f << endl;
}

// given a student id, print the name and info of their faculty advisor
void Simulation::getStudentAdvisor() {

    int id = getInputID("Student");
    Student* s = getStudentByID(id);
    Faculty* f = getFacultyByID(s->advisor);
    cout << "Advisor:\n" << *f << endl;
}

// given a faculty id, print ALL names and info of his/her advisees
void Simulation::getAdvisorStudents() {

    int id = getInputID("Faculty");
    Faculty* f = getFacultyByID(id);
    cout << "Advisees:" << endl;
    Student* s;
    for (int i = 0; i < f->advisees->size(); ++i) {
        s = getStudentByID(f->advisees->at(i));
        cout << *s << endl;
    }
}

// add a new student
void Simulation::addStudent() {

    saveCurrentTrees();

    int id = getInputID("Student"); /* TODO: make sure id is unique */

    string name;
    cout << "Enter Student's Name: " << endl;
    cin.ignore();
    getline(cin, name);
    cin.clear();

    string level;
    cout << "Enter Student's Level: " << endl;
    cin >> level;
    cin.clear();

    string major;
    cout << "Enter Student's Major: " << endl;
    cin.ignore();
    getline(cin, major);
    cin.clear();

    string gpaStr;
    cout << "Enter Student's GPA: " << endl;
    cin >> gpaStr;
    cin.clear();
    double gpa = stod(gpaStr); /* TODO: add error checking */

    int advisor;
    Faculty* f;
    while(true) { /* TODO: clean up for better error checking */
        string studentAdvisor;
        cout << "Enter Student's Advisor ID: " << endl;
        cin >> studentAdvisor;
        cin.clear();
        advisor = stoi(studentAdvisor); /* TODO: add error checking */
        f = getFacultyByID(advisor);

        if (facultyBST->searchNode(f)) {
            break;
        } else {
            cout << "There is no faculty with this ID number; try again. " << endl;
        }
    }
    Student* newStudent = new Student(id, name, level, major, gpa, advisor); /* TODO: add error checking */
    studentBST->insertNode(newStudent);
    //add student to advisor list
    f->advisees->push_back(id);
}

// delete a student given the id
void Simulation::deleteStudent() {

    saveCurrentTrees();

    int id = getInputID("Student");
    Student* s = getStudentByID(id);
    int advisor = s->advisor; // save for later
    bool success = studentBST->deleteNode(s);
    if(success) {
        cout << "Student successfully deleted." << endl;
    } else {
        cout << "Student could not be deleted." << endl;
        return;
    }

    // delete student id from any faculty advisees
    Faculty* f = getFacultyByID(advisor);
    for(int i = 0; i < f->advisees->size(); ++i) {
        if(id == f->advisees->at(i)) {
            f->advisees->erase(f->advisees->begin() + i);
            break;
        }
    }
}

// add a new faculty
void Simulation::addFaculty()
{
    saveCurrentTrees();

    int id = getInputID("Faculty"); /* TODO: make sure id is unique */

    string name;
    cout << "Enter Faculty's Name: " << endl;
    cin.ignore();
    getline(cin, name);
    cin.clear();

    string level;
    cout << "Enter Faculty's Level: " << endl;
    cin >> level;
    cin.clear();

    string department;
    cout << "Enter Faculty's Department: " << endl;
    cin.ignore();
    getline(cin, name);
    cin.clear();

    Faculty* f = new Faculty(id, name, level, department);
    facultyBST->insertNode(f);
}

// delete a faculty given the id
void Simulation::deleteFaculty()
{
    saveCurrentTrees();

    int id = getInputID("Faculty");
    Faculty* f = getFacultyByID(id);
    int adviseeCount = f->advisees->size();

    // copy vector so that we can delete the advisor first (as to avoid issues with reassigning advisees)
    vector<int>* tempAdvisees = new vector<int>(*f->advisees);
    bool success = facultyBST->deleteNode(f);

    if(!success) {
        cout << "Faculty could not be deleted." << endl;
        delete tempAdvisees;
        return;
    }

    if (adviseeCount > 0) {
        cout << "Faculty currently has " << adviseeCount << " advisees, must reassign them to new advisors." << endl;
        for (int i = 0; i < adviseeCount; ++i) {
            cout << "Enter new faculty advisor for student \'" << tempAdvisees->at(i) << "\': " << endl;
            bool success = changeStudentAdvisor(tempAdvisees->at(i));
            if(!success) {
                cout << "Faculty ID not found, try again." << endl;
                i--;
            }
        }
    }

    delete tempAdvisees;

    cout << "Faculty successfully deleted." << endl;
}

// change a student's advisor given the student id and the new faculty id
void Simulation::changeStudentAdvisor()
{
    int sID = getInputID("Student");
    changeStudentAdvisor(sID);
}

// remove an advisee from a faculty member given the ids
void Simulation::removeAdvisee()
{
  int fID = getInputID("Faculty");
  Faculty* f = getFacultyByID(fID);

  int sID = getInputID("Student");
  Student* s = getStudentByID(sID);

  bool success = false;
  for (int i = 0; i < f->advisees->size(); ++i)
  {
    if (f->advisees->at(i) == sID)
    {
      f->advisees->erase(f->advisees->begin() + i);
      success = true;
      break;
    }
  }

  if(success) {
      cout << "Advisee successfully removed." << endl;
  } else {
      cout << "Advisee could not be found." << endl;
  }

  cout << "Need to assign the Student to a new advisor." << endl;
  changeStudentAdvisor(sID);
}

// undo previous insertion/removal
void Simulation::rollback()
{
    if(studentBSTImages->isEmpty()) {
        cout << "No changes to undo." << endl;
        return;
    }

    delete studentBST;
    delete facultyBST;

    studentBST = studentBSTImages->pop();
    facultyBST = facultyBSTImages->pop();

    cout << "Rollback was successful." << endl;
}



/* Private Functions */

Student* Simulation::getStudentByID(int id) {

    Student* ret = NULL;

    Student* temp = new Student(id);

    if (studentBST->searchNode(temp)) {
        ret = studentBST->getNode(temp);
    } else {
        cout << "There is no student with this ID." << endl;
    }
    delete temp;
    return ret;
}

Faculty* Simulation::getFacultyByID(int id) {

    Faculty* ret = NULL;

    Faculty* temp = new Faculty(id);

    if (facultyBST->searchNode(temp)) {
        ret = facultyBST->getNode(temp);
    } else {
        cout << "There is no faculty with this ID." << endl;
    }
    delete temp;
    return ret;
}

int Simulation::getInputID(string type) {

    string input;
    int id;
    cout << "Enter " << type << "\'s ID: " << endl;
    cin >> input;
    id = stoi(input); /* TODO: add error checking */

    return id;
}

// saves current tree data into the stacks
void Simulation::saveCurrentTrees() {
    // make copies of trees
    BinarySearchTree<Student>* sBSTCopy = new BinarySearchTree<Student>(*studentBST);
    BinarySearchTree<Faculty>* fBSTCopy = new BinarySearchTree<Faculty>(*facultyBST);
    // push to stacks
    studentBSTImages->push(sBSTCopy);
    facultyBSTImages->push(fBSTCopy);
}

// changes a student's advisor given the student id
bool Simulation::changeStudentAdvisor(int sID)
{
    Student* s = getStudentByID(sID);
    int fID = getInputID("Faculty");
    Faculty* f = getFacultyByID(fID);
    if(f == NULL)
        return false;
    for(int i = 0; i < f->advisees->size(); ++i) {
        if(f->advisees->at(i) == sID) {
            cout << "Already Student's advisor." << endl;
            return false;
        }
    }
    f->advisees->push_back(sID);
    Faculty* currentAdvisor = getFacultyByID(s->advisor);
    for (int i = 0; i < currentAdvisor->advisees->size(); ++i)
    {
      if (currentAdvisor->advisees->at(i) == sID)
      {
        currentAdvisor->advisees->erase(currentAdvisor->advisees->begin() + i);
        break;
      }
    }

    s->advisor = fID;
    return true;
}

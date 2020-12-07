#include "FileManager.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {

    Simulation* sim = new Simulation();
    FileManager* fm = new FileManager(sim);

    fm->loadData();

    cout << "\n\n\n-----------------------| Student & Faculty Database |-----------------------" << endl;

    // main loop
    while(true) {
        string input;
        int inputNum;

        cout << "\n\n----------------------------------------------------------------------------" << endl;
        cout << "\nEnter a number to select a command:\n" << endl;
        cout << "1.  Print all students and their information (sorted by ascending id #)" << endl;
        cout << "2.  Print all faculty and their information (sorted by ascending id #)" << endl;
        cout << "3.  Find and display student information given the students id" << endl;
        cout << "4.  Find and display faculty information given the faculty id" << endl;
        cout << "5.  Given a student’s id, print the name and info of their faculty advisor" << endl;
        cout << "6.  Given a faculty id, print ALL the names and info of his/her advisees." << endl;
        cout << "7.  Add a new student" << endl;
        cout << "8.  Delete a student given the id" << endl;
        cout << "9.  Add a new faculty member" << endl;
        cout << "10. Delete a faculty member given the id." << endl;
        cout << "11. Change a student’s advisor given the student id and the new faculty id." << endl;
        cout << "12. Remove an advisee from a faculty member given the ids" << endl;
        cout << "13. Rollback" << endl;
        cout << "14. Exit\n" << endl;

        while(true) {
            cin >> input;
            try {
                inputNum = stoi(input);
            } catch(int e) {
                cout << "\nIncorrect input, please enter a number 1-14." << endl;
                continue;
            }
            if(inputNum > 0 && inputNum < 15) {
                break;
            } else {
                cout << "\nIncorrect input, please enter a number 1-14." << endl;
            }
        }

        cout << "----------------------------------------------------------------------------\n" << endl;

        switch(inputNum) {
            case 1:
                sim->printStudentAscending();
                break;
            case 2:
                sim->printFacultyAscending();
                break;
            case 3:
                sim->displayStudent();
                break;
            case 4:
                sim->displayFaculty();
                break;
            case 5:
                sim->getStudentAdvisor();
                break;
            case 6:
                sim->getAdvisorStudents();
                break;
            case 7:
                sim->addStudent();
                break;
            case 8:
                sim->deleteStudent();
                break;
            case 9:
                sim->addFaculty();
                break;
            case 10:
                sim->deleteFaculty();
                break;
            case 11:
                sim->changeStudentAdvisor();
                break;
            case 12:
                sim->removeAdvisee();
                break;
            case 13:
                sim->rollback();
                break;
            case 14:
                break;
            default:
                cout << "Something went wrong..." << endl;
                break;
        }

        if(inputNum == 14) {
            break;
        }

    }

    cout << "\nExiting program." << endl;

    fm->saveData();

    //we think there is an issue deleting, where the root node is set to null, and a segmentation fault occurs
    delete sim;
    delete fm;

    return 0;
}

// FileManager header

#ifndef FILEMANAGER
#define FILEMANAGER

#include "Simulation.h"
#include "Student.h"
#include "Faculty.h"
#include <fstream>

using namespace std;

class FileManager {

    public:
        FileManager();
        FileManager(Simulation* sim);
        ~FileManager();

        void loadData(); // reads from files and converts data to sTree and fTree
        void saveData(); // converts data from sTree and fTree and writes to files

    private:
        fstream studentFile; // file to read/write from containing Student tree data
        fstream facultyFile; // file to read/write from containing Faculty tree data
        Simulation* sim; // used to call addStudentFromFile() and addFacultyFromFile() from within Simulation

        void readStudentFile();
        void readFacultyFile();
        void writeStudentFile();
        void writeFacultyFile();
        void recAddStudents(Student** arrStudents, int l, int r);
        void recAddFacultys(Faculty** arrFacultys, int l, int r);

        bool openFiles(bool isWrite); // opens files and returns true if files already exist
        void closeFiles(); // closes student and faculty files
        bool isEmpty(fstream& file); // returns true if a file is empty

        string getFormattedStudent(Student& s); // formats student information to write to file
        string getFormattedFaculty(Faculty& f); // formats faculty information to write to file
};

#endif

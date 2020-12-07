// FileManager implementation

#include "FileManager.h"

FileManager::FileManager() {}

FileManager::FileManager(Simulation* sim) {
    this->sim = sim;
}

FileManager::~FileManager() {
    closeFiles();
}


// reads from files and adds
void FileManager::loadData() {
    bool filesAlreadyExist = openFiles(false);
    if(filesAlreadyExist) {
        // time to add students to simulation
        readStudentFile();
        readFacultyFile();
    } else {
        // add nothing
    }
    closeFiles();
}

// converts data from sTree and fTree and writes to files
void FileManager::saveData() {
    openFiles(true);

    // write Student data from Simulation BST inorder to file
    writeStudentFile();

    // write Faculty data from Simulation BST inorder to file
    writeFacultyFile();

    closeFiles();
}

void FileManager::readStudentFile() {
    Student** arrStudents;
    int studentCount;
    Student* currStudent;
    string currLine = "";

    // first line: amount of students
    std::getline(studentFile, currLine);
    studentCount = stoi(currLine);
    if(studentCount == 0)
        return;

    arrStudents = new Student*[studentCount];

    // add Students to array
    for(int i = 0; i < studentCount; ++i) {
        std::getline(studentFile, currLine);
        int id = stoi(currLine);

        std::getline(studentFile, currLine);
        string name = currLine;

        std::getline(studentFile, currLine);
        string level = currLine;

        std::getline(studentFile, currLine);
        string major = currLine;

        std::getline(studentFile, currLine);
        double gpa = stod(currLine);

        std::getline(studentFile, currLine);
        int advisor = stoi(currLine);

        currStudent = new Student(id, name, level, major, gpa, advisor);
        arrStudents[i] = currStudent;
    }

    // recursively add Students to Simulation BST
    recAddStudents(arrStudents, 0, studentCount - 1);
}

void FileManager::readFacultyFile() {
    Faculty** arrFacultys;
    int facultyCount;
    Faculty* currFaculty;
    string currLine = "";

    // first line: amount of faculties
    std::getline(facultyFile, currLine);
    facultyCount = stoi(currLine);
    if(facultyCount == 0)
        return;

    arrFacultys = new Faculty*[facultyCount];

    // add Faculties to array
    for(int i = 0; i < facultyCount; ++i) {
        std::getline(facultyFile, currLine);
        int id = stoi(currLine);

        std::getline(facultyFile, currLine);
        string name = currLine;

        std::getline(facultyFile, currLine);
        string level = currLine;

        std::getline(facultyFile, currLine);
        string department = currLine;

        std::getline(facultyFile, currLine);
        int adviseeCount = stoi(currLine);

        vector<int>* advisees = new vector<int>();
        for(int i = 0; i < adviseeCount; ++i) {
            std::getline(facultyFile, currLine);
            advisees->push_back(stoi(currLine));
        }

        currFaculty = new Faculty(id, name, level, department, advisees);
        arrFacultys[i] = currFaculty;
    }

    // recursively add Faculties to Simulation BST
    recAddFacultys(arrFacultys, 0, facultyCount - 1);
}

void FileManager::writeStudentFile() {
    studentFile << to_string(sim->studentBST->getSize()) << endl;
    while(!sim->studentBST->isEmpty()) {
        Student* s = sim->studentBST->getMin();
        string formattedStudent = getFormattedStudent(*s);
        studentFile << formattedStudent;
        sim->studentBST->deleteNode(s);
    }
}

void FileManager::writeFacultyFile() {
    facultyFile << to_string(sim->facultyBST->getSize()) << endl;
    while(!sim->facultyBST->isEmpty()) {
        Faculty* f = sim->facultyBST->getMin();
        string formattedFaculty = getFormattedFaculty(*f);
        facultyFile << formattedFaculty;
        sim->facultyBST->deleteNode(f);
    }
}

// adds Students to Simulation BST in a balanced order
void FileManager::recAddStudents(Student** arrStudents, int l, int r) {
    int m = (l + r) / 2;
    sim->addStudentFromFile(arrStudents[m]);
    if(l != r) {
        if(l != m)
            recAddStudents(arrStudents, l, m - 1);
        recAddStudents(arrStudents, m + 1, r);
    }
}

// adds Faculties to Simulation BST in a balanced order
void FileManager::recAddFacultys(Faculty** arrFacultys, int l, int r) {
    int m = (l + r) / 2;
    sim->addFacultyFromFile(arrFacultys[m]);
    if(l != r) {
        if(l != m)
            recAddFacultys(arrFacultys, l, m - 1);
        recAddFacultys(arrFacultys, m + 1, r);
    }
}

/* PRIVATE METHODS */

// opens files and returns true if both files already exist
bool FileManager::openFiles(bool isWrite) {

    if(isWrite) {
        studentFile.open("studentData.txt", fstream::out | fstream::trunc);
        facultyFile.open("facultyData.txt", fstream::out | fstream::trunc);
    } else {
        studentFile.open("studentData.txt");
        facultyFile.open("facultyData.txt");
    }

    return ( !isEmpty(studentFile) || !isEmpty(facultyFile) );
}

// closes student and faculty files
void FileManager::closeFiles() {
    studentFile.close();
    facultyFile.close();
}

// returns true if a file is empty
bool FileManager::isEmpty(fstream& file) {
    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);

    return (length == 0);
}

// formats student information to write to file
string FileManager::getFormattedStudent(Student& s) {
    string str;
    str = to_string(s.id) + "\n";
    str += s.name + "\n";
    str += s.level + "\n";
    str += s.major + "\n";
    str += to_string(s.gpa) + "\n";
    str += to_string(s.advisor) + "\n";
    return str;
}

// formats faculty information to write to file
string FileManager::getFormattedFaculty(Faculty& f) {
    string str;
    str = to_string(f.id) + "\n";
    str += f.name + "\n";
    str += f.level + "\n";
    str += f.department + "\n";
    str += to_string(f.advisees->size()) + "\n";
    for(int advisee : *f.advisees) {
        str += to_string(advisee) + "\n";
    }
    return str;
}

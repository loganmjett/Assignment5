# cpsc350-fall2020-assignment5
Eli Annoni
2348182
annoni@chapman.edu

Logan Jett
2342344
ljett@chapman.edu

**I (Logan) was unable to work on this project as much as Eli due to other class commitments, please do not dock him points for errors in the Simulation header and cpp files, as it was my fault should any occur!**

CPSC 350-01
Assignment 5: Building a Database with Binary Search Trees

Source files:
    1. main.cpp
    2. TreeNode.h
    3. BST.h
    4. Faculty.h
    5. Faculty.cpp
    6. Student.h
    7. Student.cpp
    8. Person.h
    9. Person.cpp
    10. GenStack.h
    11. Simulation.h
    12. Simulation.cpp
    13. FileManager.h
    14. FileManager.cpp

Compile/run commands:
    - make all
    - ./assignment5.exe *file name*

Errors:
    - We believe there to be an issue when deleting the tree images from the stack. Sometimes, this leads to a segmentation fault when exiting after completing a operation. We tested removing the deletions at the end of main.cpp, and were presented with memory leaks, we were unsure of how to fix this.

References:
    - zybooks.com
    - http://www.cplusplus.com/reference/vector/vector/
    - https://stackoverflow.com/questions/16098362/how-to-deep-copy-a-binary-tree
    - geeksforgeeks.org

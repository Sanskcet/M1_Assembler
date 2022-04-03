# M1_Assembler
  The Makefile is portable with Linux as well as Windows Systems. 
  However, CppCheck, Buildtools, Make, Valgrind, Doxygen, gcc must be preinstalled in order to produce correct results.
## MakeFile Commands available:
* all - Default task. Compiles the project.
* run - Runs the Compiled project. If not compiled yet, compiles and then runs the project.
* test - Performs UnitTest on the project using Unity Framework.
* doc - outputs the Documentation in html format using Doxygen.
* doc_run - Opens the documentation index.html file in the browser.
* staticcheck - Performs CppCheck.
* memcheck - Performs memory check using valgrind.
* sanitize_check - Performs Sanitize Check on the project.
* coverage - Performs Code Coverage on the project.
* analyze - Performs all of the above checks on the project.
* clean - Removes the Build files.
* clean_doc - Removes the Doxygen Output files.

# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\jjba-tests.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\jjba-tests.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\jjba-tests.dir\flags.make

CMakeFiles\jjba-tests.dir\tests\test_main.cc.obj: CMakeFiles\jjba-tests.dir\flags.make
CMakeFiles\jjba-tests.dir\tests\test_main.cc.obj: ..\tests\test_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jjba-tests.dir/tests/test_main.cc.obj"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\jjba-tests.dir\tests\test_main.cc.obj /FdCMakeFiles\jjba-tests.dir\ /FS -c C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\tests\test_main.cc
<<

CMakeFiles\jjba-tests.dir\tests\test_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jjba-tests.dir/tests/test_main.cc.i"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe > CMakeFiles\jjba-tests.dir\tests\test_main.cc.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\tests\test_main.cc
<<

CMakeFiles\jjba-tests.dir\tests\test_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jjba-tests.dir/tests/test_main.cc.s"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\jjba-tests.dir\tests\test_main.cc.s /c C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\tests\test_main.cc
<<

CMakeFiles\jjba-tests.dir\src\engine\board.cc.obj: CMakeFiles\jjba-tests.dir\flags.make
CMakeFiles\jjba-tests.dir\src\engine\board.cc.obj: ..\src\engine\board.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/jjba-tests.dir/src/engine/board.cc.obj"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\jjba-tests.dir\src\engine\board.cc.obj /FdCMakeFiles\jjba-tests.dir\ /FS -c C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\src\engine\board.cc
<<

CMakeFiles\jjba-tests.dir\src\engine\board.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jjba-tests.dir/src/engine/board.cc.i"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe > CMakeFiles\jjba-tests.dir\src\engine\board.cc.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\src\engine\board.cc
<<

CMakeFiles\jjba-tests.dir\src\engine\board.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jjba-tests.dir/src/engine/board.cc.s"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\jjba-tests.dir\src\engine\board.cc.s /c C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\src\engine\board.cc
<<

CMakeFiles\jjba-tests.dir\src\engine\tile.cc.obj: CMakeFiles\jjba-tests.dir\flags.make
CMakeFiles\jjba-tests.dir\src\engine\tile.cc.obj: ..\src\engine\tile.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/jjba-tests.dir/src/engine/tile.cc.obj"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\jjba-tests.dir\src\engine\tile.cc.obj /FdCMakeFiles\jjba-tests.dir\ /FS -c C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\src\engine\tile.cc
<<

CMakeFiles\jjba-tests.dir\src\engine\tile.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jjba-tests.dir/src/engine/tile.cc.i"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe > CMakeFiles\jjba-tests.dir\src\engine\tile.cc.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\src\engine\tile.cc
<<

CMakeFiles\jjba-tests.dir\src\engine\tile.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jjba-tests.dir/src/engine/tile.cc.s"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\jjba-tests.dir\src\engine\tile.cc.s /c C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\src\engine\tile.cc
<<

CMakeFiles\jjba-tests.dir\src\gui\jjba_strategy_app.cc.obj: CMakeFiles\jjba-tests.dir\flags.make
CMakeFiles\jjba-tests.dir\src\gui\jjba_strategy_app.cc.obj: ..\src\gui\jjba_strategy_app.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/jjba-tests.dir/src/gui/jjba_strategy_app.cc.obj"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\jjba-tests.dir\src\gui\jjba_strategy_app.cc.obj /FdCMakeFiles\jjba-tests.dir\ /FS -c C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\src\gui\jjba_strategy_app.cc
<<

CMakeFiles\jjba-tests.dir\src\gui\jjba_strategy_app.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jjba-tests.dir/src/gui/jjba_strategy_app.cc.i"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe > CMakeFiles\jjba-tests.dir\src\gui\jjba_strategy_app.cc.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\src\gui\jjba_strategy_app.cc
<<

CMakeFiles\jjba-tests.dir\src\gui\jjba_strategy_app.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jjba-tests.dir/src/gui/jjba_strategy_app.cc.s"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\jjba-tests.dir\src\gui\jjba_strategy_app.cc.s /c C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\src\gui\jjba_strategy_app.cc
<<

CMakeFiles\jjba-tests.dir\src\gui\render_engine.cc.obj: CMakeFiles\jjba-tests.dir\flags.make
CMakeFiles\jjba-tests.dir\src\gui\render_engine.cc.obj: ..\src\gui\render_engine.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/jjba-tests.dir/src/gui/render_engine.cc.obj"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\jjba-tests.dir\src\gui\render_engine.cc.obj /FdCMakeFiles\jjba-tests.dir\ /FS -c C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\src\gui\render_engine.cc
<<

CMakeFiles\jjba-tests.dir\src\gui\render_engine.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jjba-tests.dir/src/gui/render_engine.cc.i"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe > CMakeFiles\jjba-tests.dir\src\gui\render_engine.cc.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\src\gui\render_engine.cc
<<

CMakeFiles\jjba-tests.dir\src\gui\render_engine.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jjba-tests.dir/src/gui/render_engine.cc.s"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\jjba-tests.dir\src\gui\render_engine.cc.s /c C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\src\gui\render_engine.cc
<<

# Object files for target jjba-tests
jjba__tests_OBJECTS = \
"CMakeFiles\jjba-tests.dir\tests\test_main.cc.obj" \
"CMakeFiles\jjba-tests.dir\src\engine\board.cc.obj" \
"CMakeFiles\jjba-tests.dir\src\engine\tile.cc.obj" \
"CMakeFiles\jjba-tests.dir\src\gui\jjba_strategy_app.cc.obj" \
"CMakeFiles\jjba-tests.dir\src\gui\render_engine.cc.obj"

# External object files for target jjba-tests
jjba__tests_EXTERNAL_OBJECTS =

Debug\jjba-tests\jjba-tests.exe: CMakeFiles\jjba-tests.dir\tests\test_main.cc.obj
Debug\jjba-tests\jjba-tests.exe: CMakeFiles\jjba-tests.dir\src\engine\board.cc.obj
Debug\jjba-tests\jjba-tests.exe: CMakeFiles\jjba-tests.dir\src\engine\tile.cc.obj
Debug\jjba-tests\jjba-tests.exe: CMakeFiles\jjba-tests.dir\src\gui\jjba_strategy_app.cc.obj
Debug\jjba-tests\jjba-tests.exe: CMakeFiles\jjba-tests.dir\src\gui\render_engine.cc.obj
Debug\jjba-tests\jjba-tests.exe: CMakeFiles\jjba-tests.dir\build.make
Debug\jjba-tests\jjba-tests.exe: C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\lib\msw\x86\Debug\v140\cinder.lib
Debug\jjba-tests\jjba-tests.exe: CMakeFiles\jjba-tests.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable Debug\jjba-tests\jjba-tests.exe"
	"C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\jjba-tests.dir --rc=C:\PROGRA~2\WI3CF2~1\8.1\bin\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\8.1\bin\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1.0\VC\bin\link.exe /nologo @CMakeFiles\jjba-tests.dir\objects1.rsp @<<
 /out:Debug\jjba-tests\jjba-tests.exe /implib:jjba-tests.lib /pdb:C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\cmake-build-debug\Debug\jjba-tests\jjba-tests.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:windows  /SUBSYSTEM:CONSOLE /NODEFAULTLIB:LIBCMT /NODEFAULTLIB:LIBCPMT   -LIBPATH:C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\lib\msw\x86  C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\lib\msw\x86\Debug\v140\cinder.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\jjba-tests.dir\build: Debug\jjba-tests\jjba-tests.exe

.PHONY : CMakeFiles\jjba-tests.dir\build

CMakeFiles\jjba-tests.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\jjba-tests.dir\cmake_clean.cmake
.PHONY : CMakeFiles\jjba-tests.dir\clean

CMakeFiles\jjba-tests.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\cmake-build-debug C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\cmake-build-debug C:\Users\asus\CLionProjects\cinder_0.9.2_vc2015\my-projects\final-project-JacobAlbus\cmake-build-debug\CMakeFiles\jjba-tests.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\jjba-tests.dir\depend


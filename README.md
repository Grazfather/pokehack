#pokehack
##Pokemon Generation 3 .sav file editor

## How to Use
### GUI

1. Compile:

Download CMake (http://www.http://cmake.org/cmake/resources/software.html)

Pokehack is compatible with GCC and MSVC. The steps in common before compiling are as follows:

a. Make a build directory in which to compile the files.

b. From the build directory, run:

```
cmake <source directory>
```

Alternatively, run the CMake GUIand do this process there.

GCC

```
cd <build directory>
make
```

MSVC (command line)

```
cd <build directory>
devenv pokehack.sln /build Release /project ALL_BUILD
```

MSVC (GUI)

a. Open pokehack.sln in MSVC.

b. In the top toolbars, make sure the build is set to Release.

c. From the top menu, select Build -> Build Solution.

NOTE: If you want to install Pokehack somewhere instead of simply building it, use this CMake
command instead:

```
cmake -DCMAKE_INSTALL_PREFIX=<install directory> <source directory>
```

In GCC:

```
cd <build directory>
make install
```

In MSVC (command line):

```
cd <build directory>
devenv pokehack.sln /build release /project ALL_BUILD
```

### Command line
1. Edit main() in pkc3.c and change whatever attributes of the six pokemon_t.  See include/pokestructs.h to see their structure.
1. Compile:

    (In root repo directory)

    ```
make
```

1. Run:
 * Game = 0 for Ruby, Sapphire, or Emerald
 * Game = 1 for FireRed or LeafGreen

    ```
pokehack_cmd <path/to/savefile> [outfile] <game>
```

## Feature Wish List
### GUI
* Pokeball list
* Location list
* 'Shiny' button
 * Changes personality value and/or original trainer id to set pokemon to shiny state.
  * Changing personality changes the gender and the nature. More volatile
  * Changing the trainer ID is easier to detect (should change trainer name, too) and makes pokemon gain extra experience. On the otherhand we can just set the original trainer ID to exactly match the pokemon's personality value and be done with it.

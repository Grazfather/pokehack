#pokehack
##Pokemon Generation 3 .sav file editor
GUI currently supports viewing first pokemon in party.
The console application supports editing any data from any pokemon, but requires editing pkc3.c and recompiling.

## How to Use
### GUI

1. Compile:

    ```
cd src
qmake
make release
```

1. Run: Open pokehack.exe in the release subdirectory. File > Open to select a save state.

**NOTES:**
* Can only view belt pokemon
* Will only save the currently viewed pokemon. Be sure to save every pokemon you edit before switching to another.
* 'Save As...' does nothing. Only saving over the opened file works. For that reason BACK UP YOUR .sav!!!

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
pokehack.exe <path/to/savefile> [outfile] <game>
```

## Feature Wish List
### GUI
* Pokeball list
* Location list
* 'Shiny' button
 * Changes personality value and/or original trainer id to set pokemon to shiny state.
  * Changing personality changes the gender and the nature. More volatile
  * Changing the trainer ID is easier to detect (should change trainer name, too) and makes pokemon gain extra experience. On the otherhand we can just set the original trainer ID to exactly match the pokemon's personality value and be done with it.

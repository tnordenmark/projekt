// ProjMain.cpp
// Huvudfil för ett program för att hantera en personlista
// Thomas Nordenmark 2014-01-14
// Ver 0.1
//------------------------------------------------------------------------------
#include <iostream> // cin, cout
#include <vector> // vector
#include <algorithm> // numeric_limits
#include "ProjFunc.h" // Egna funktioner
#include "ProjStruct.h" // Egna datatyper
using namespace std;

//------------------------------------------------------------------------------
// Huvudprogram
//------------------------------------------------------------------------------
int main()
{
    // Lagra menyvalet
    int menu_choice;
    // Skapa en vector för att lagra personobjekten
    vector<Person> Pers_vec;
    // Skapa ett objekt av typen Person
    Person pers;
    // Lagra valet för sortering
    int sort;

    // Visa huvudmenyn så länge valet inte är 9
    do
    {
        // Visa huvudmenyn
        showMenu();
        // Hämta menyvalet
        menu_choice = menuChoice();

        // Hantera huvudmenyns olika val
        switch(menu_choice)
        {
            case 1:
                // Lägg till person
                addPerson(pers, Pers_vec);
                break;
            case 2:
                // Skriv ut listan till skärm
                printList(Pers_vec);
                break;
            case 3:
                // Sök person
                findPerson(Pers_vec);
                break;
            case 4:
                // Radera person
                delPerson(Pers_vec);
                break;
            case 5:
                // Fråga efter och läs in sorteringsvalet med teckenverifiering
                while ((cout << "Hur vill du sortera listan (1)Namn, (2)Signatur eller (3)Längd? ")
                         && (!(cin >> sort)
                         || sort < 1
                         || sort > 3))
                {
                    invalidSortChoice();
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                // Sortera listan
                sortList(sort, Pers_vec);
                break;
            case 6:
                // Slumpa listan
                randList(Pers_vec);
                break;
            case 7:
                // Spara på fil
                saveFile(Pers_vec);
                break;
            case 8:
                // Läs från fil
                readFile(pers, Pers_vec);
                break;
            case 9:
                // Avsluta program
                cout << "Avslutar program..." << endl;
                return 0;
            default:
                // Bör inte hända, skriver felmeddelande
                invalidChoice();
        }
    }while(menu_choice != 9);

    return 0;
}

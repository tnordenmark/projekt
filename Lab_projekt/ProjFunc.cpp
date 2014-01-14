// ProjFunc.cpp
// Funktionsdefinitioner till programmet för att hantera en personlista
// Thomas Nordenmark 2014-01-14
// Ver 0.1
//------------------------------------------------------------------------------
#include <iostream> // cout, cin
#include <string> // string, getline
#include <vector> // vector, push_back, clear, erase
#include <iomanip> // setw, fixed, setprecision
#include <fstream> // ifstream, ofstream
#include <sstream> // stringstream
#include <algorithm> // find, numeric_limits, sort
#include <cctype> // tolower
#include "ProjFunc.h"
#include "ProjStruct.h"
#include "ProjGlob.h"
using namespace std;

//------------------------------------------------------------------------------
// showMenu
//------------------------------------------------------------------------------
// Uppgift: Visar en huvudmeny
// Indata :
// Utdata : Menyn skrivs till skärmen
//------------------------------------------------------------------------------
void showMenu()
{
    cout << "=========================" << endl;
    cout << "        Huvudmeny" << endl;
    cout << "1. Lägg till person" << endl;
    cout << "2. Skriv lista till skärm" << endl;
    cout << "3. Sök person" << endl;
    cout << "4. Ta bort person" << endl;
    cout << "5. Sortera lista" << endl;
    cout << "6. Slumpa lista" << endl;
    cout << "7. Skriv lista till fil" << endl;
    cout << "8. Läs lista från fil" << endl;
    cout << "9. Avsluta" << endl;
    cout << "=========================" << endl;
}

//------------------------------------------------------------------------------
// menuChoice
//------------------------------------------------------------------------------
// Uppgift: Hanterar menyval för en huvudmeny
// Indata :
// Utdata : menu_choice returneras som en integer
//------------------------------------------------------------------------------
int menuChoice()
{
    // Lagra menyvalet
    int menu_choice;

    // Fråga efter och läs in menyvalet med teckenverifiering
    while ((cout << "Menyval: ")
             && (!(cin >> menu_choice)
             || menu_choice < 1
             || menu_choice > 9))
    {
        invalidChoice();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Returnera menyvalet som en integer
    return menu_choice;
}

//------------------------------------------------------------------------------
// invalidChoice
//------------------------------------------------------------------------------
// Uppgift: Skriver ut felmeddelande vid ogiltig inmatning
// Indata :
// Utdata : Funktionen skriver ut ett felmeddelande
//------------------------------------------------------------------------------
void invalidChoice()
{
    cout << "Ogiltigt val, mata in en siffra mellan 1 och 9." << endl;
}

//------------------------------------------------------------------------------
// invalidChoice
//------------------------------------------------------------------------------
// Uppgift: Skriver ut felmeddelande vid ogiltig inmatning
// Indata :
// Utdata : Funktionen skriver ut ett felmeddelande
//------------------------------------------------------------------------------
void invalidSortChoice()
{
    cout << "Ogiltigt val, mata in en siffra mellan 1 och 3." << endl;
}

//------------------------------------------------------------------------------
// addPerson
//------------------------------------------------------------------------------
// Uppgift: Lägger till ett person-objekt till en vector efter kontroll att
//          personen är unik
// Indata : p (Person), v (vector)
// Utdata : Funktionen skapar ett person-objekt och lägger till det i vectorn
//------------------------------------------------------------------------------
void addPerson(Person p, vector<Person> &v)
{
    // Variabler för att lagra de olika attributen
    string first_name, last_name, signature;
    double height = 0.0;

    // Vectorns storlek som unikt löpnummer
    string vsize = to_string(v.size() + 1);

    // Om vectorns storlek är 0-9, lägg till en nolla före
    if(vsize.size() == 1)
        vsize = to_string(0) + vsize;

    // Något skit i tuben som måste tas bort
    cin.get();

    // Fråga efter och mata in persondata
    cout << "Ange personens förnamn: ";
    getline(cin, first_name);

    cout << "Ange personens efternamn: ";
    getline(cin, last_name);

    cout << "Ange personens signatur (xxxyyy): ";
    cin >> signature;
    // Om förnamn och efternamn båda innehåller 3 tecken eller fler
    // fyll på signaturen på rätt plats
    if(first_name.size() >= 3 && last_name.size() >= 3)
        signature.insert(6, vsize);
    // Om förnamn innehåller 2 tecken och efternamn 2 tecken
    // fyll på signaturen på rätt plats
    if(first_name.size() == 2 && last_name.size() == 2)
    {
        signature.insert(2, FILL);
        signature.insert(5, FILL);
        signature.insert(6, vsize);
    }
    // Om förnamn innehåller 3 eller fler tecken men efternamn 2 tecken
    // fyll på signaturen på rätt plats
    if(first_name.size() >= 3 && last_name.size() == 2)
    {
        signature.insert(5, FILL);
        signature.insert(6, vsize);
    }
    // Om förnamn innehåller 2 tecken men efternamn 3 eller fler tecken
    // fyll på signaturen på rätt plats
    if(first_name.size() == 2 && last_name.size() >= 3)
    {
        signature.insert(2, FILL);
        signature.insert(6, vsize);
    }

    cout << "Ange personens längd (M.CM): ";
    cin >> height;

    // Kontrollera om förnamn, efternamn och längd är unika
    if(!(isUnique(first_name, last_name, height, v)))
        // Om ej unik, skriv ut felmeddelande
        cout << "Personen finns redan, försök igen med en unik person." << endl;
    else
    {
        // Om personen är unik, lägg till i listan
        p.first_name = first_name;
        p.last_name = last_name;
        p.signature = signature;
        p.height = height;
        v.push_back(p);
    }
}

//------------------------------------------------------------------------------
// isUnique
//------------------------------------------------------------------------------
// Uppgift: Kontrollerar om en inmatad person är unik utan hänsyn till versaler
//          och gemener
// Indata : f (string), l (string), h (string), v (vector)
// Utdata : Funktionen returnerar true om unik, false om ej unik
//------------------------------------------------------------------------------
bool isUnique(string f, string l, double &h, vector<Person> v)
{
    // Sätt systemets standardlocale
    locale loc;

    // Konvertera strängobjektet a till versaler
    transform(f.begin(), f.end(), f.begin(), [loc](char c)
    {return toupper<char>(c, loc);});

    // Konvertera strängobjektet b till versaler
    transform(l.begin(), l.end(), l.begin(), [loc](char c)
    {return toupper<char>(c, loc);});

    // Loopa igenom vectorns element
    for(size_t i = 0; i < v.size(); i++)
    {
        // Konvertera vectorns first_name till versaler
        transform(v[i].first_name.begin(), v[i].first_name.end(), v[i].first_name.begin(), [loc](char c)
        {return toupper<char>(c, loc);});

        // Konvertera vectorns last_name till versaler
        transform(v[i].last_name.begin(), v[i].last_name.end(), v[i].last_name.begin(), [loc](char c)
        {return toupper<char>(c, loc);});

        // Om namnet ej är unikt, returnera false
        if(f == v[i].first_name && l == v[i].last_name && h == v[i].height)
            return false;
    }

    // Om namnet är unikt, returnera true
    return true;
}

//------------------------------------------------------------------------------
// printList
//------------------------------------------------------------------------------
// Uppgift: Skriver ut en vectors innehåll till skärmen, 20 namn åt gången
// Indata : v (vector)
// Utdata : Funktionen skriver ut vectorns innehåll till skärmen
//------------------------------------------------------------------------------
void printList(vector<Person> &v)
{
    // Antal personer i listan = antal objekt i vectorn
    int num_pers = v.size();
    // Variabel för modulus för att skriva ut 20 namn åt gången
    int num = 1;

    // Läs bort lite skit i tuben
    cin.get();

    // Rubrik samt antal nuvarande personer i listan
    cout << "======= Namnlista =======" << endl;
    cout << "Antal personer i listan: " << num_pers << endl << endl;

    // Kolumnrubriker
    cout << left << setw(7) << "Nr";
    cout << setw(10) << "Sign";
    cout << setw(30) << "Namn";
    cout << right << setw(16) << "Längd [m]" << endl;

    // Skriv ut vectorns innehåll till skärmen, formaterat i kolumner
    for(size_t i = 0; i < v.size(); i++)
    {
        // Om löpnumret är två siffror, justera formatering
        if(i+1 > 9)
        {
            cout << left << setw(2) << i+1 << setw(5) << ".";
            cout << setw(10) << v[i].signature;
            cout << setw(30) << v[i].first_name + " " + v[i].last_name;
            cout << right << setw(10) << fixed << setprecision(2) << v[i].height << endl;

            // Skriv ut 20 namn åt gången
            if(num % 20 == 0)
            {
                cout << "Tryck på valfri tangent för att fortsätta..." << endl;
                cin.get();
            }

            // Uppdatera räknaren för modus
            num++;
        }
        // Om löpnumret är en siffra
        else
        {
            cout << left << setw(1) << i+1 << setw(6) << ".";
            cout << setw(10) << v[i].signature;
            cout << setw(30) << v[i].first_name + " " + v[i].last_name;
            cout << right << setw(10) << fixed << setprecision(2) << v[i].height << endl;

            // Skriv ut 20 namn åt gången
            if(num % 20 == 0)
            {
                cout << "Tryck på valfri tangent för att fortsätta..." << endl;
                cin.get();
            }

            // Uppdatera räknaren för modus
            num++;
        }
    }
}

//------------------------------------------------------------------------------
// findSignIdx
//------------------------------------------------------------------------------
// Uppgift: Söker efter en persons signatur i vectorn
// Indata : k (string), v (vector)
// Utdata : Funktionen returnerar indexplats om träff, annars size()
//------------------------------------------------------------------------------
int findSignIdx(string k, vector<Person> &v)
{
    // Hämta sökpredikatet från Person-objektet i vectorn
    auto it = find_if(begin(v), end(v), [=] (Person const &p)
    {
        return (p.signature == k);
    });

    // Beräkna söksträngens index i vectorn
    int idx = it - v.begin();

    // Returnera index
    return idx;
}

//------------------------------------------------------------------------------
// findPerson
//------------------------------------------------------------------------------
// Uppgift: Söker efter en person i vectorn
// Indata : v (vector)
// Utdata : Funktionen skriver ut personen om träff, felmeddelande om miss
//------------------------------------------------------------------------------
void findPerson(vector<Person> &v)
{
    // Söksträng
    string key;
    // Indexplats i vectorn
    int idx = 0;
    // Vectorns storlek
    int size = v.size();

    // Fråga efter och mata in eftersökt signatur
    cout << "Mata in signatur att söka efter: ";
    cin >> key;

    // Hämta söknyckelns index i vectorn
    idx = findSignIdx(key, v);

    // Om index är större än antalet objekt i vectorn
    if(idx > size - 1)
        cout << "Inga träffar vid sökning efter " << "\"" << key << "\"." << endl;
    // Om det eftersökta objektet finns på ett index i vectorn
    else
    {
        // Kolumnrubriker
        cout << left << setw(6) << "Nr";
        cout << setw(10) << "Sign";
        cout << setw(30) << "Namn";
        cout << right << setw(16) << "Längd [m]" << endl;

        // Persondata
        cout << left << idx+1 << setw(5) << ".";
        cout << setw(10) << v[idx].signature;
        cout << setw(30) << v[idx].first_name + " " + v[idx].last_name;
        cout << right << setw(10) << fixed << setprecision(2) << v[idx].height << endl;
    }
}

//------------------------------------------------------------------------------
// delPerson
//------------------------------------------------------------------------------
// Uppgift: Söker efter och raderar en person i vectorn
// Indata : v (vector)
// Utdata : Funktionen raderar person med eftersökt signatur
//------------------------------------------------------------------------------
void delPerson(vector<Person> &v)
{
    // Söksträng
    string key;
    // Indexplats i vectorn
    int idx = 0;
    // Vectorns storlek
    int size = v.size();

    // Fråga efter och mata in eftersökt signatur
    cout << "Mata in signatur att radera: ";
    cin >> key;

    // Hämta söknyckelns index i vectorn
    idx = findSignIdx(key, v);

    // Om index är större än antalet objekt i vectorn
    if(idx > size - 1)
        cout << "Inga träffar vid sökning efter " << "\"" << key << "\"." << endl;
    // Om det eftersökta objektet finns på ett index i vectorn
    else
    {
        // Radera person på plats idx
        v.erase(v.begin() + idx);
        cout << "Raderade person med signatur " << "\"" << key << "\"." << endl;
    }
}

//------------------------------------------------------------------------------
// sortList
//------------------------------------------------------------------------------
// Uppgift: Sorterar listan efter namn, signatur eller längd
// Indata : v (vector)
// Utdata : Funktionen soterar och skriver ut listan
//------------------------------------------------------------------------------
void sortList(int s, vector<Person> &v)
{
    // Switch för att hantera de olika valen för sortering
    switch(s)
    {
        case NAME:
            cout << "Listan sorterad efter namn" << endl;
            cout << "==========================" << endl;
            // Sorterar listan stigande efter namn
            sort(v.begin(), v.end(), compareStr);
            // Skriver ut den sorterade listan
            printList(v);
            break;
        case SIGN:
            cout << "Listan sorterad efter signatur" << endl;
            cout << "==============================" << endl;
            // Soterar listan stigande efter signatur
            sort(v.begin(), v.end(), compareSign);
            // Skriver ut den sorterade listan
            printList(v);
            break;
        case HEIGHT:
            cout << "Listan sorterad efter längd" << endl;
            cout << "===========================" << endl;
            // Sorterar listan fallande efter längd
            sort(v.begin(), v.end(), compareHeight);
            // Skriver ut den sorterade listan
            printList(v);
            break;
        default:
            // Bör inte hända, skriver ut felmeddelande om
            invalidSortChoice();
            break;
    }
}

//------------------------------------------------------------------------------
// compareStr
//------------------------------------------------------------------------------
// Uppgift: Jämför två objekt av typen sträng i en vector, utan hänsyn till
//          versaler och gemener
// Indata : a (Person), b (Person)
// Utdata : Returnerar true om a är mindre än b
//------------------------------------------------------------------------------
bool compareStr(Person a, Person b)
{
    // Sätt systemets standardlocale
    locale loc;

    // Konvertera strängobjektet a till versaler
    transform(a.last_name.begin(), a.last_name.end(), a.last_name.begin(), [loc](char c)
    {return toupper<char>(c, loc);});

    // Konvertera strängobjektet b till versaler
    transform(b.last_name.begin(), b.last_name.end(), b.last_name.begin(), [loc](char c)
    {return toupper<char>(c, loc);});

    // Jämför efternamnen
    return (a.last_name < b.last_name);
}

//------------------------------------------------------------------------------
// compareSign
//------------------------------------------------------------------------------
// Uppgift: Jämför ASCII-värden för två objekt av typen string i en vector
// Indata : a (const Person), b (const Person)
// Utdata : Returnerar true om a är mindre än b
//------------------------------------------------------------------------------
bool compareSign(const Person &a, const Person &b)
{
    // Jämför signaturerna
    return a.signature < b.signature;
}

//------------------------------------------------------------------------------
// compareHeight
//------------------------------------------------------------------------------
// Uppgift: Jämför två objekt av typen double i en vector
// Indata : a (const Person), b (const Person)
// Utdata : Returnerar true om a är större än b
//------------------------------------------------------------------------------
bool compareHeight(const Person &a, const Person &b)
{
    // Jämför längderna
    return a.height > b.height;
}

//------------------------------------------------------------------------------
// randList
//------------------------------------------------------------------------------
// Uppgift: Slumpar objektens ordning i en vector
// Indata : v (Person)
// Utdata : Funktionen slumpar och skriver ut listan
//------------------------------------------------------------------------------
void randList(vector<Person> &v)
{
    // Slumpa listan med algorithm
    random_shuffle(v.begin(), v.end());

    // Skriv ut listan
    printList(v);
}

//------------------------------------------------------------------------------
// saveFile
//------------------------------------------------------------------------------
// Uppgift: Sparar innehållet i en vector till fil
// Indata : v (vector)
// Utdata : Funktionen skriver data till angivet filnamn
//------------------------------------------------------------------------------
void saveFile(vector<Person> &v)
{
    // Variabel för att lagra filnamnet
    string filename;

    // Fråga efter och mata in filnamn
    cout << "Ange filnamn att spara data till: ";
    cin >> filename;

    // Öppna filen för skrivning, lägg till till befintligt innehåll
    ofstream outFile(filename);

    // Om det gick bra att öppna filen
    if(outFile.is_open())
    {
        // Skriv vectorns innehåll till FILENAME
        for(size_t i = 0; i < v.size(); i++)
            outFile << v[i].first_name
                    << DELIM << v[i].last_name
                    << DELIM << v[i].signature
                    << DELIM << v[i].height << endl;
    }
    else
        // I/O error, om filen inte kunde öppnas
        cout << "Kunde inte öppna filen." << endl;

    // Stäng utfilen
    outFile.close();
}

//------------------------------------------------------------------------------
// readFile
//------------------------------------------------------------------------------
// Uppgift: Läser in en fils innehåll till en vector
// Indata : p (Person), v (vector)
// Utdata : Funktionen läser data från angivet filnamn
//------------------------------------------------------------------------------
void readFile(Person &p, vector<Person> &v)
{
    // Variabel för att lagra filnamnet
    string filename;

    // Fråga efter och mata in filnamn
    cout << "Ange filnamn att läsa data från: ";
    cin >> filename;

    // Öppna filen FILENAME
    ifstream inFile(filename);

    // Töm vectorn om den har något innehåll
    if(!v.empty())
        v.clear();

    // Om det gick bra att öppna filen
    if(inFile.is_open())
    {
        // Temporära strängar att lagra filens olika poster i
        string tempstr, tfirst_name, tlast_name, tsignature, theight;

        // Så länge filen har innehåll
        while(getline(inFile, tempstr))
        {
            // Omvandla filens innehåll till en strängström
            stringstream ss(tempstr);

            // Om det går bra att läsa in varje post fram till avskiljaren |
            if(getline(ss, tfirst_name, '|') &&
            getline(ss, tlast_name, '|') &&
            getline(ss, tsignature, '|') &&
            getline(ss, theight))
            {
                // Tilldela värdena till objektet pers
                p.first_name = tfirst_name;
                p.last_name = tlast_name;
                p.signature = tsignature;
                p.height = stod(theight);

                // Lägg objektet i vectorn v
                v.push_back(p);
            }
            else
                // I/O error, om filen inte kunde läsas
                cout << "Filens data kunde inte läsas, kontrollera formatet." << endl;
        }
    }
    else
        // I/O error, om filen inte kunde öppnas
        cout << "Kunde inte öppna filen." << endl;

    // Stäng filen
    inFile.close();
}

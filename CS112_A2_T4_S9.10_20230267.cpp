// File: CS112_A2_T4_S9.10_20230267.cpp
// Purpose: This program contains 3 crypts which are substitute crypt, polybus crypt and xor crypt.
// Author 1: Omar Mostafa Saad - 20230267 - S9.10
// Email: omar16220061622006@gmail.com

#include <iostream>
#include <sstream>
#include <array>
#include <iomanip>

using namespace std;

// Crypts codes.
#define SUBSTITUTE_CRYPT 1
#define POLYBUS_CRYPT 2
#define XOR_CRYPT 3

// Operations codes.
#define ENCRYPT 1
#define DECRYPT 2

// general functions.
int getChoice(string catalog, int choicesCount);
string getAlphaSpacesText();
string getDigSpacesText();
string getHexSpacesText();
string getNonEmptyText();

// Substitute crypt functions.
string substituteCrypt(string text, string key, int opType);
string getSubstituteKey();

// Polybus crypt functions.
string polybusCrypt(string text, string key, int opType);
string getPolyBusKey();

// Xor crypt functions.
string xorCrypt(string text, string key, int opType);
string getXorKey();

int main()
{
    cout << "Welcome, we got some crypt algorithms for you!\n"
         << "===========================================" << endl;

    while (true)
    {
        int crypt = getChoice("1- Substitute Crypt\n2- Polybuis Crypt\n3- XOR Crypt\n4- Exit", 4);
        if (crypt == SUBSTITUTE_CRYPT)
        {
            int opType = getChoice("Do you want to (1)encrypt or (2)decrypt: ", 2);
            string text = getAlphaSpacesText();
            string key = getSubstituteKey();

            cout << '\n'
                 << substituteCrypt(text, key, opType) << '\n'
                 << endl;
        }
        else if (crypt == POLYBUS_CRYPT)
        {
            int opType = getChoice("Do you want to (1)encrypt or (2)decrypt: ", 2);
            string text = opType == ENCRYPT ? getAlphaSpacesText() : getDigSpacesText();
            string key = getPolyBusKey();

            cout << '\n'
                 << polybusCrypt(text, key, opType) << '\n'
                 << endl;
        }
        else if (crypt == XOR_CRYPT)
        {
            int opType = getChoice("Do you want to (1)encrypt or (2)decrypt: ", 2);
            string text = opType == ENCRYPT ? getNonEmptyText() : getHexSpacesText();
            string key = getXorKey();

            cout << '\n'
                 << xorCrypt(text, key, opType) << '\n'
                 << endl;
        }
        else
        {
            cout << '\n'
                 << "Good Bye!" << '\n'
                 << endl;
            break;
        }
    }

    return 0;
}

int getChoice(string catalog, int choicesCount)
{
    string choice;
    cout << catalog << '\n'
         << "Enter your choice: ";
    getline(cin, choice);
    while (true)
    {
        for (int i = 1; i <= choicesCount; i++)
        {
            if (choice == to_string(i))
            {
                return stoi(choice);
            }
        }

        cout << "INVALID! please enter only from 1 to " << choicesCount << ": ";
        getline(cin, choice);
    }
}

string getAlphaSpacesText()
{
    string text;
    cout << "Enter the text: ";
    getline(cin, text);
    while (true)
    {
        if (text.length() != 0)
        {
            bool allValid = true;
            for (int i = 0; i < text.length(); i++)
            {
                if (!isalpha(text[i]) && !isspace(text[i]))
                {
                    allValid = false;
                }
            }
            if (allValid)
            {
                break;
            }
        }
        cout << "INVALID! enter non empty text that contains alphabetic characters and spaces only: ";
        getline(cin, text);
    }
    return text;
}

string getDigSpacesText()
{
    string text;
    cout << "Enter the text: ";
    getline(cin, text);
    while (true)
    {
        if (text.length() != 0)
        {
            bool allValid = true;
            for (int i = 0; i < text.length(); i++)
            {
                if (!isdigit(text[i]) && !isspace(text[i]))
                {
                    allValid = false;
                }
            }
            if (allValid)
            {
                break;
            }
        }
        cout << "INVALID! enter non empty text that contains digits and spaces only: ";
        getline(cin, text);
    }
    return text;
}

string getHexSpacesText()
{
    string text;
    cout << "Enter the text: ";
    getline(cin, text);
    while (true)
    {
        if (text.length() != 0)
        {
            bool allValid = true;
            for (int i = 0; i < text.length(); i++)
            {
                if (!isdigit(text[i]) && !isspace(text[i]) &&
                    text[i] != 'a' && text[i] != 'b' &&
                    text[i] != 'c' && text[i] != 'd' &&
                    text[i] != 'e' && text[i] != 'f')
                {
                    allValid = false;
                }
            }
            if (allValid)
            {
                break;
            }
        }
        cout << "INVALID! enter non empty text that contains hex digits and spaces only: ";
        getline(cin, text);
    }
    return text;
}

string getNonEmptyText()
{
    string text;
    cout << "Enter the text: ";
    getline(cin, text);

    while (text.length() == 0)
    {
        cout << "INVALID! text length can't be zero: ";
        getline(cin, text);
    }

    return text;
}

string substituteCrypt(string text, string key, int opType)
{
    // build the encrypted alphabet
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string encryptedAlphabet = key;
    for (int i = 0; i < alphabet.length(); i++)
    {
        bool isFromKey = false;
        for (int j = 0; j < key.length(); j++)
        {
            if (alphabet[i] == tolower(key[j]))
            {
                isFromKey = true;
                break;
            }
        }
        if (!isFromKey)
        {
            encryptedAlphabet = encryptedAlphabet + alphabet[i];
        }
    }

    // now we can work.
    string result = "";
    for (int i = 0; i < text.length(); i++)
    {
        if (isspace(text[i]))
        {
            result += text[i];
            continue;
        }
        if (opType == 1)
        {
            char c = tolower(text[i]);
            result += tolower(encryptedAlphabet[c - 97]);
        }
        else
        {
            char c = tolower(text[i]);
            for (int j = 0; j < encryptedAlphabet.length(); j++)
            {
                if (tolower(encryptedAlphabet[j]) == c)
                {
                    result += alphabet[j];
                    break;
                }
            }
        }
    }
    return result;
}

string getSubstituteKey()
{
    string key;
    const int KEY_LENGTH = 5;
    cout << "Enter five character key: ";
    getline(cin, key);
    while (true)
    {
        if (key.length() == KEY_LENGTH)
        {
            bool allValid = true;
            for (int i = 0; i < key.length(); i++)
            {
                if (!isalpha(key[i]))
                {
                    allValid = false;
                    break;
                }
                for (int j = i + 1; j < key.length(); j++)
                {
                    if (key[i] == key[j])
                    {
                        allValid = false;
                        break;
                    }
                }
                if (!allValid)
                {
                    break;
                }
            }
            if (allValid)
            {
                break;
            }
        }
        cout << "INVALID! please enter five different alphabetic characters only: ";
        getline(cin, key);
    }
    return key;
}

string polybusCrypt(string text, string key, int opType)
{
    // generate encrypted alphabet
    string encryptedAlphabet[25];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            encryptedAlphabet[i * 5 + j] = string() + key[i] + key[j];
        }
    }

    if (opType == ENCRYPT)
    {

        string result = "";
        for (int i = 0; i < text.length(); i++)
        {
            if (isspace(text[i]))
            {
                result += text[i];
            }
            else
            {
                // as i and j have the same key, this boolean at the end is needed
                result += encryptedAlphabet[tolower(text[i]) - 'a' - (tolower(text[i]) >= 'j')];
            }
        }
        return result;
    }
    else
    {
        string result = "";
        for (int i = 0; i < text.length(); i++)
        {
            if (isspace(text[i]))
            {
                result += text[i];
                continue;
            }

            // this means that it is only one number without it's twin.
            if (i + 1 == text.length())
            {
                break;
            }

            string encryptedLetter = string() + text[i] + text[i + 1];
            // 25 is the encrypted alphabet size
            for (int j = 0; j < 25; j++)
            {
                if (encryptedAlphabet[j] == encryptedLetter)
                {
                    // as i and j have the same key, we shift right by one starting from j
                    result += ('a' + j + (j > 8));
                }
            }
            // if it is a letter not space, we have read two chars.
            i++;
        }
        return result;
    }
}

string getPolyBusKey()
{
    string key;
    const int KEY_LENGTH = 5;
    cout << "Enter five digit key: ";
    getline(cin, key);
    while (true)
    {
        if (key.length() == KEY_LENGTH)
        {
            bool allValid = true;
            for (int i = 0; i < key.length(); i++)
            {
                if (!isdigit(key[i]))
                {
                    allValid = false;
                    break;
                }
                for (int j = i + 1; j < key.length(); j++)
                {
                    if (key[i] == key[j])
                    {
                        allValid = false;
                        break;
                    }
                }
                if (!allValid)
                {
                    break;
                }
            }
            if (allValid)
            {
                break;
            }
        }
        cout << "INVALID! please enter five different digits only: ";
        getline(cin, key);
    }
    return key;
}

string xorCrypt(string text, string key, int opType)
{
    if (opType == ENCRYPT)
    {
        string result = "";
        string hexResult = "";
        stringstream stream;

        int keyIndex = 0;
        for (int i = 0; i < text.length(); i++)
        {
            if (keyIndex == key.length())
            {
                keyIndex = 0;
            }

            char encryptedChar = text[i] ^ key[keyIndex];

            stream << setfill('0') << setw(2) << hex << (int)encryptedChar;
            string hexChar = stream.str();
            stream.str("");

            result += encryptedChar;
            hexResult += hexChar;

            if (i != text.length() - 1)
            {
                hexResult += ' ';
            }

            keyIndex++;
        }

        return result + '\n' + hexResult;
    }
    else
    {
        string result;
        unsigned int c;
        stringstream ss(text);

        int keyIndex = 0;
        while (ss >> hex >> c)
        {
            if (c > 255)
            {
                continue;
            }

            c = c ^ key[keyIndex];
            result += (char)c;
            keyIndex++;

            if (keyIndex == key.length())
            {
                keyIndex = 0;
            }
        }
        return result;
    }
}

string getXorKey()
{
    string key;
    cout << "Enter the key: ";
    getline(cin, key);

    while (key.length() == 0)
    {
        cout << "INVALID! key can't be empty: ";
        getline(cin, key);
    }

    return key;
}
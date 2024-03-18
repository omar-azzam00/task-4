#include <iostream>

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

// Substitute crypt functions.
string substituteCrypt(string text, string key, int opType);
string getSubstituteKey();

int main()
{
    cout << "Welcome, we got some crypt algorithms for you!\n"
         << "===========================================" << endl;

    while (true)
    {
        int crypt = getChoice("1- Substitute Crypt\n2- Polybuis Crypt\n3- XOR Crypt\n4- Exit", 4);
        if (crypt == SUBSTITUTE_CRYPT)
        {
            string text = getAlphaSpacesText();
            string key = getSubstituteKey();
            int opType = getChoice("Do you want to (1)encrypt or (2)decrypt: ", 2);

            cout << substituteCrypt(text, key, opType) << endl;
        }
        else if (crypt == POLYBUS_CRYPT)
        {
            cout << "Not Implemented!" << endl;
        }
        else if (crypt == XOR_CRYPT)
        {
            cout << "Not Implemented!" << endl;
        }
        else
        {
            cout << "Good Bye!" << endl;
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

        cout << "INVALID! please enter only from 1 to  " << choicesCount << ": ";
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
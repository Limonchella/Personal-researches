#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <conio.h>
#include <set>
#include <locale.h>
void showData(std::vector<std::string>& data);

enum color
{
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
const std::string folder = "databases";
std::vector<std::filesystem::path> path_files;
std::vector<std::string> curFileFields;
int MENU = 1;
//bool GO_ON = false;
int curFile = 0;

void COUT(std::string str, color textColor = LightGray, color backColor = Black)
{
    SetConsoleTextAttribute(console, (WORD)(backColor << 4 | textColor));
    std::cout << str;
    SetConsoleTextAttribute(console, (WORD)(Black << 4 | LightGray));
}

void pathInit()
{
    for (auto curFile : std::filesystem::directory_iterator(folder))
        path_files.push_back(curFile.path());
}

void langInit()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}


void showDataBases()
{
    for (int i = 0; i < path_files.size(); i++)
    {
        std::cout << "(" << i + 1 << ") : " << path_files[i].filename() << std::endl;
    }
}

void createDataBase(std::vector<std::string>& fields, std::string name)
{
    std::string path = folder + "/" + name + ".txt";
    std::ofstream file(path);

    file << "Поля:" << '\n';

    for (int i = 0; i < fields.size(); i++)
        file << fields[i] << '\n';
    file << "--------------------\n";
    file.close();
    path_files.push_back(path);
}

void menu1()
{
    std::cout << std::endl;
    COUT("                      Create new base  (1)                  \n", White, Blue);
    std::cout << std::endl;
    COUT("                   Download the existing base (2)               \n", White, Blue);
    std::cout << std::endl;
    COUT("                           Global search  (3)                     \n", White, Blue);
    std::cout << std::endl;
    COUT("                          Quit  (4)                      \n", White, Blue);

    char choise;
    do
    {
        choise = _getch();
    } while (!(choise >= '1' && choise <= '4'));
    system("cls");

    if (choise == '1')
        MENU = 2;
    else if (choise == '2')
        MENU = 3;
    else if (choise == '3')
        MENU = 5;
    else if (choise == '4')
        exit(0);
}

void fixFile()
{
    std::ifstream file(path_files[curFile]);

    curFileFields.clear();
    std::string str;
    std::getline(file, str);
    while (true)
    {
        std::getline(file, str);
        if (str == "--------------------")
            break;
        curFileFields.push_back(str);
    }


    file.close();
}

void menu3()
{
    COUT("                      Download the existing base                       \n", Black, White);

    if (path_files.size() == 0)
    {
        COUT("\nNo bases. Create new base to work with\n\n", LightRed);
        std::cout << "Push any botton to continue...";
        _getch();
        rewind(stdin);
        system("cls");
        MENU = 1;
        return;
    }

    COUT("\nExisting databases:\n", White);
    showDataBases();
    std::cout << std::endl;
    COUT("Enter 'Yes', to choose database, or else , to return:\n");
    std::string str;
    std::cin >> str;
    if (str != "Yes")
    {
        MENU = 1;
        system("cls");
        return;
    }
    std::cout << "\n";
    COUT("Choose the file:");


    do
    {
        std::cin >> curFile;
        if (curFile >= 1 && curFile <= path_files.size() + 1)
            break;
        else
        {
            COUT("Error!\n", LightRed);
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            rewind(stdin);
        }

    } while (true);
    curFile--;
    fixFile();
    MENU = 4;
    system("cls");
}

void menu2()
{
    COUT("                      Create new database                       \n", Black, White);
    std::cout << std::endl;
    COUT("Enter 'Yes' to create a database, or another to go back:\n");
    std::string str;
    std::cin >> str;
    if (str != "Так")
    {
        MENU = 1;
        system("cls");
        return;
    }
    std::cout << "\n";
    COUT("Enter a name for the new database: ");
    std::string name;
    rewind(stdin);
    std::getline(std::cin, name);

    std::vector<std::string> fields;
    std::string field;
    do
    {
        COUT("Введіть назву поля: ");
        rewind(stdin);
        std::getline(std::cin, field);
        fields.push_back(field);
        COUT("Enter 'Yes', to enter more, else, to finish:\n");
        std::cin >> str;
        if (str != "Yes")
            break;
    } while (true);
    createDataBase(fields, name);
    system("cls");
    std::cout << std::endl;
    COUT("                     Create one more database (1)                  \n\n", White, Blue);
    COUT("                       Change the added file (2)                   \n\n", White, Blue);
    COUT("                               Back  (3)                           \n\n", White, Blue);

    char choise;
    do
    {
        choise = _getch();
    } while (!(choise >= '1' && choise <= '3'));
    system("cls");

    if (choise == '3')
        MENU = 1;
    else if (choise == '1')
        MENU = 2;
    else
    {
        curFile = path_files.size() - 1;
        fixFile();///
        MENU = 4;
    }
}

void addObj()
{
    std::ofstream file(path_files[curFile], std::ios::app);
    std::string str = "Yes";

    while (str == "Yes")
    {
        rewind(stdin);
        for (int i = 0; i < curFileFields.size(); i++)
        {
            COUT(curFileFields[i] + ": ", White);
            file << curFileFields[i] << ": ";
            std::string str;
            std::getline(std::cin, str);
            if (str == "")
                str = " ";
            file << str << "\n";
        }
        file << "\n";
        std::cout << std::endl;
        COUT("Print 'Yes', if you want to add another item, else, to return to :\n");
        std::cin >> str;
    }

    rewind(stdin);
    file.close();
    system("cls");
}

void getData(std::string& fld, int i)
{
    fld.erase(0, curFileFields[i].length() + 2);
}


void findObj()
{
    std::ifstream file(path_files[curFile]);

    COUT("Choose which option to search for:\n\n");
    for (int i = 0; i < curFileFields.size(); i++)
        COUT("(" + std::to_string(i + 1) + ") : " + curFileFields[i] + "\n", White);
    COUT("(" + std::to_string(curFileFields.size() + 1) + ") : " + "By all parameters\n", White);
    int choise;
    do
    {
        std::cin >> choise;
        if (choise >= 1 && choise <= curFileFields.size() + 1)
            break;
        else
        {
            COUT("Error!\n", LightRed);
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }

    } while (true);
    system("cls");

    COUT("Selected option: ", White);
    std::cout << ((choise == curFileFields.size() + 1) ? "By all parameters\n" : curFileFields[choise - 1] + "\n");
    COUT("Enter a keyword: ");
    std::string key;
    std::cin >> key;
    std::cout << std::endl;


    std::string str;
    std::getline(file, str);
    while (true)
    {
        std::getline(file, str);
        if (str == "--------------------")
            break;
    }


    int found = 0;
    std::vector<std::string> curData;
    bool saveCur = false;
    while (file.eof() == false)
    {
        for (int i = 0; i < curFileFields.size(); i++)
        {
            std::getline(file, str);
            getData(str, i);
            curData.push_back(str);
            if (saveCur == false && (choise == curFileFields.size() + 1 || choise == i + 1))
            {
                if (str.find(key) != std::string::npos)
                    saveCur = true;
            }
        }
        if (saveCur == true)
        {
            std::cout << "(" + std::to_string(found + 1) + ")\n";
            showData(curData);
            std::cout << "\n";
            found++;
            saveCur = false;
        }
        curData.clear();
        std::getline(file, str);
    }

    if (found == 0)
        COUT("There are no such objects in the database \n", White);


    file.close();
    _getch();
    system("cls");
}

void findObj(std::string key)
{
    std::ifstream file(path_files[curFile]);

    std::string str;
    std::getline(file, str);
    while (true)
    {
        std::getline(file, str);
        if (str == "--------------------")
            break;
    }


    int found = 0;
    std::vector<std::string> curData;
    bool saveCur = false;
    while (file.eof() == false)
    {
        for (int i = 0; i < curFileFields.size(); i++)
        {
            std::getline(file, str);
            getData(str, i);
            curData.push_back(str);
            if (saveCur == false)
            {
                if (str.find(key) != std::string::npos)
                    saveCur = true;
            }
        }
        if (saveCur == true)
        {

            std::cout << "(" + std::to_string(found + 1) + ")\n";
            showData(curData);
            std::cout << "\n";
            found++;
            saveCur = false;
        }
        curData.clear();
        std::getline(file, str);
    }

    if (found == 0)
        COUT("No things like this in the base\n", White);


    file.close();
}

int showBase(bool cont = false)
{
    std::ifstream file(path_files[curFile]);
    std::string str;
    std::getline(file, str);
    while (true)
    {
        std::getline(file, str);
        if (str == "--------------------")
            break;
    }
    if (file.peek() == EOF)
    {
        COUT("Database is empty!\n", White);
        file.close();
        if (!cont)
        {
            _getch();
            system("cls");
        }
        return 0;
    }
    int spaces = 0;
    int prevN = 0;
    int curN = 1;
    while (file.eof() == false)
    {

        std::getline(file, str);
        if (str != "")
            spaces = 0;
        else
            curN++;
        if (prevN != curN && spaces == 0)
        {
            std::cout << "(" << std::to_string(curN) << ")" << std::endl;
            prevN = curN;
        }
        COUT(str, White);
        if (str == "" && spaces < 2)
        {
            std::cout << std::endl;
            spaces++;
        }

        if (spaces < 2)
        {
            std::cout << std::endl;
            spaces++;
        }


    }

    file.close();
    if (!cont)
    {
        _getch();
        system("cls");
    }
    return prevN;
}

void deleteEl(int toDelN)
{
    std::ofstream fileCpy(folder + "/tempCopy_.txt");
    std::ifstream file(path_files[curFile]);

    std::string str;
    std::getline(file, str);
    fileCpy << str << "\n";
    while (true)
    {
        std::getline(file, str);
        fileCpy << str << "\n";
        if (str == "--------------------")
            break;
    }

    int spaces = 0;
    int curN = 1;
    while (file.eof() == false)
    {
        std::getline(file, str);
        if (str.length() != 0)
            spaces = 0;
        else
        {
            curN++;
            if (toDelN == 1 && curN == toDelN + 1)
                spaces += 2;
            else if (curN == toDelN + 1)
            {
                fileCpy << "\n";
                spaces += 2;
                continue;
            }

        }

        if (curN != toDelN)
        {
            fileCpy << str;
            if (str == "" && spaces < 2)
            {
                fileCpy << "\n";
                spaces++;
            }
            if (spaces < 2)
            {
                fileCpy << "\n";
                spaces++;
            }
        }
    }


    file.close();
    fileCpy.close();

    remove(path_files[curFile]);
    rename((folder + "/tempCopy_.txt").c_str(), path_files[curFile]);
}


void showData(std::vector<std::string>& data)
{
    for (int j = 0; j < curFileFields.size(); j++)
    {
        COUT(curFileFields[j] + ": ", White);
        COUT(data[j] + "\n", White);
    }
    std::cout << std::endl;
}

void deleteObj()
{
    COUT("                       Search to delete(1)                \n\n", White, Blue);
    COUT("                       Show the database (2)              \n\n", White, Blue);
    COUT("                               Back (3)                   \n\n", White, Blue);

    char choise;
    do
    {
        choise = _getch();
    } while (!(choise >= '1' && choise <= '3'));
    system("cls");

    if (choise == '3')
    {
        MENU = 4;
        return;
    }
    else if (choise == '2')
    {
        system("cls");
        int N = showBase(true);

        if (N == 0)
        {
            COUT("\nPush any button to quit", White);
            _getch();
            system("cls");
            MENU = 1;
            return;
        }

        COUT("Choose the number to delete: ");
        int toDelete = 0;

        do
        {
            std::cin >> toDelete;
            if (!(toDelete >= 1 && toDelete <= N))
            {
                COUT("ERROR! NO SUCH ELEMENT!\n", LightRed);
                COUT("Choose the number to delete: ", White);
            }
            else
                break;
        } while (true);

        deleteEl(toDelete);
        COUT("Success!", Green);
        _getch();
        system("cls");
        MENU = 4;
    }
    else
    {
        system("cls");
        COUT("Choose the parameters by which the search will be made:\n\n");
        for (int i = 0; i < curFileFields.size(); i++)
            COUT("(" + std::to_string(i + 1) + ") : " + curFileFields[i] + "\n", White);
        COUT("(" + std::to_string(curFileFields.size() + 1) + ") : " + "By all parameters\n", White);
        int choise;
        do
        {
            std::cin >> choise;
            if (choise >= 1 && choise <= curFileFields.size() + 1)
                break;
            else
            {
                COUT("Error!\n", LightRed);
                std::cin.clear();
                std::cin.ignore(32767, '\n');
            }

        } while (true);
        system("cls");

        COUT("Selected option: ", White);
        std::cout << ((choise == curFileFields.size() + 1) ? "By all parameters\n" : curFileFields[choise - 1] + "\n");
        COUT("Enter a keyword : ");
        std::string key;
        std::cin >> key;
        std::cout << std::endl;

        std::ifstream file(path_files[curFile]);

        std::string str;
        std::getline(file, str);
        while (true)
        {
            std::getline(file, str);
            if (str == "--------------------")
                break;
        }

        std::vector<std::string> curData;
        std::set<int> showed;
        bool saveCur = false;
        int N = 1;
        while (file.eof() == false)
        {
            for (int i = 0; i < curFileFields.size(); i++)
            {
                std::getline(file, str);
                getData(str, i);
                curData.push_back(str);
                if (saveCur == false && (choise == curFileFields.size() + 1 || choise == i + 1))
                {
                    if (str.find(key) != std::string::npos)
                        saveCur = true;
                }
            }
            if (saveCur == true)
            {
                showed.insert(N);
                COUT("(" + std::to_string(N) + ")\n", White);
                showData(curData);
                saveCur = false;
            }
            N++;
            curData.clear();
            std::getline(file, str);
        }
        file.close();

        if (showed.size() == 0)
        {
            COUT("\nNo results!\nPush any botton to exit", White);
            _getch();
            system("cls");
            MENU = 4;
            return;
        }

        int toD;
        COUT("Choose the element to delete: ", White);
        do
        {
            std::cin >> toD;
            if (showed.find(toD) != showed.end())
                break;
            else
            {
                COUT("Error!\n", LightRed);
                std::cin.clear();
                std::cin.ignore(32767, '\n');
            }
        } while (true);
        deleteEl(toD);
        COUT("Success!", Green);
        _getch();
        system("cls");
        MENU = 4;
    }
}


void editEl(int toDelN, std::vector<std::string>& newObj)
{
    std::ofstream fileCpy(folder + "/tempCopy_.txt");
    std::ifstream file(path_files[curFile]);

    std::string str;
    std::getline(file, str);
    fileCpy << str << "\n";
    while (true)
    {
        std::getline(file, str);
        fileCpy << str << "\n";
        if (str == "--------------------")
            break;
    }
    bool ed = false;
    int spaces = 0;
    int curN = 1;
    while (file.eof() == false)
    {
        std::getline(file, str);
        if (str.length() != 0 && (toDelN != 1 || curN != 1))
        {
            spaces = 0;
            if (toDelN == curN)
                continue;
        }
        else
        {
            if (str.length() == 0)
                curN++;

            if (toDelN == curN && ed == false)
            {
                if (curN != 1)
                    fileCpy << "\n";
                for (int i = 0; i < curFileFields.size(); i++)
                {
                    fileCpy << newObj[i];
                    if (i != curFileFields.size() - 1)
                        fileCpy << "\n";
                }
                ed = true;
                continue;
            }
        }

        if (curN != toDelN)
        {
            fileCpy << str;
            if (str == "" && spaces < 2)
            {
                fileCpy << "\n";
                spaces++;
            }
            if (spaces < 2)
            {
                fileCpy << "\n";
                spaces++;
            }
        }
    }


    file.close();
    fileCpy.close();

    remove(path_files[curFile]);
    rename((folder + "/tempCopy_.txt").c_str(), path_files[curFile]);
}

void editObj()
{
    COUT("                            Find to edit (1)                         \n\n", White, Blue);
    COUT("                            Show the base (2)                        \n\n", White, Blue);
    COUT("                               Back (3)                              \n\n", White, Blue);

    char choise;
    do
    {
        choise = _getch();
    } while (!(choise >= '1' && choise <= '3'));
    system("cls");

    if (choise == '3')
    {
        MENU = 4;
        return;
    }
    else if (choise == '2')
    {
        system("cls");
        int N = showBase(true);

        if (N == 0)
        {
            COUT("\nTo exit, press any key ", White);
            _getch();
            system("cls");
            MENU = 1;
            return;
        }

        COUT("Choose the number to edit: ");
        int toDelete = 0;

        do
        {
            std::cin >> toDelete;
            if (!(toDelete >= 1 && toDelete <= N))
            {
                COUT("Error, such element does not exist !!\n", LightRed);
                COUT("Select a number to delete: ", White);
            }
            else
                break;
        } while (true);

        system("cls");
        std::vector<std::string> newObj;
        std::string inp;
        COUT("Enter new parameters:  \n", White);
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        for (int i = 0; i < curFileFields.size(); i++)
        {
            COUT(curFileFields[i] + ": ", White);
            std::getline(std::cin, inp);
            newObj.push_back(curFileFields[i] + ": " + inp);
        }


        editEl(toDelete, newObj);
        COUT("Success!", Green);
        _getch();
        system("cls");
        MENU = 4;
    }
    else
    {
        system("cls");
        COUT("Choose which option to search for :\n\n");
        for (int i = 0; i < curFileFields.size(); i++)
            COUT("(" + std::to_string(i + 1) + ") : " + curFileFields[i] + "\n", White);
        COUT("(" + std::to_string(curFileFields.size() + 1) + ") : " + "By all parameters \n", White);
        int choise;
        do
        {
            std::cin >> choise;
            if (choise >= 1 && choise <= curFileFields.size() + 1)
                break;
            else
            {
                COUT("Error!\n", LightRed);
                std::cin.clear();
                std::cin.ignore(32767, '\n');
            }

        } while (true);
        system("cls");

        COUT("Selected option: ", White);
        std::cout << ((choise == curFileFields.size() + 1) ? "By all parameters \n" : curFileFields[choise - 1] + "\n");
        COUT("Enter a keyword: ");
        std::string key;
        std::cin >> key;
        std::cout << std::endl;

        std::ifstream file(path_files[curFile]);

        std::string str;
        std::getline(file, str);
        while (true)
        {
            std::getline(file, str);
            if (str == "--------------------")
                break;
        }

        std::vector<std::string> curData;
        std::set<int> showed;
        bool saveCur = false;
        int N = 1;
        while (file.eof() == false)
        {
            for (int i = 0; i < curFileFields.size(); i++)
            {
                std::getline(file, str);
                getData(str, i);
                curData.push_back(str);
                if (saveCur == false && (choise == curFileFields.size() + 1 || choise == i + 1))
                {
                    if (str.find(key) != std::string::npos)
                        saveCur = true;
                }
            }
            if (saveCur == true)
            {
                showed.insert(N);
                COUT("(" + std::to_string(N) + ")\n", White);
                showData(curData);
                saveCur = false;
            }
            N++;
            curData.clear();
            std::getline(file, str);
        }
        file.close();

        if (showed.size() == 0)
        {
            COUT("\nNo results!\nTo exit, press any key ", White);
            _getch();
            system("cls");
            MENU = 4;
            return;
        }

        int toD;
        COUT("Select an item to edit : ", White);
        do
        {
            std::cin >> toD;
            if (showed.find(toD) != showed.end())
                break;
            else
            {
                COUT("Error!\n", LightRed);
                std::cin.clear();
                std::cin.ignore(32767, '\n');
            }
        } while (true);

        system("cls");
        std::vector<std::string> newObj;
        std::string inp;
        COUT("Enter the new settings: \n", White);
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        for (int i = 0; i < curFileFields.size(); i++)
        {
            COUT(curFileFields[i] + ": ", White);
            std::getline(std::cin, inp);
            newObj.push_back(curFileFields[i] + ": " + inp);
        }


        editEl(toD, newObj);
        COUT("Success!", Green);
        _getch();
        system("cls");
        MENU = 4;
    }
}

int getAmount()
{
    std::ifstream file(path_files[curFile]);
    std::string str;
    std::getline(file, str);
    while (true)
    {
        std::getline(file, str);
        if (str == "--------------------")
            break;
    }
    if (file.peek() == EOF)
    {
        file.close();
        return 0;
    }
    int spaces = 0;
    int prevN = 0;
    int curN = 1;
    while (file.eof() == false)
    {

        std::getline(file, str);
        if (str != "")
            spaces = 0;
        else
            curN++;
        if (prevN != curN && spaces == 0)
            prevN = curN;
        if (str == "" && spaces < 2)
            spaces++;
        if (spaces < 2)
            spaces++;
    }

    file.close();

    return prevN;
}

std::vector<std::string> getEl(std::ifstream& file)
{
    std::vector<std::string> ret;
    std::string str;
    for (int i = 0; i < curFileFields.size(); i++)
    {
        std::getline(file, str);
        getData(str, i);
        ret.push_back(str);
    }
    std::getline(file, str);
    return ret;
}

bool isEqual(std::vector<std::string>& one, std::vector<std::string>& two)
{
    for (int i = 0; i < one.size(); i++)
    {
        if (one[i] != two[i])
            return false;
    }
    return true;
}

std::vector<std::string> getMax(std::ifstream& file, int k, std::vector<std::string>* maxPrev = NULL)
{
    bool fChoise = false;
    std::vector<std::string> curMax;
    std::vector<std::string> buffer;
    int N = 1;
    int maxN = 1;
    while (file.peek() != EOF)
    {
        buffer = getEl(file);
        if (fChoise == true && buffer[k] < curMax[k])
        {
            curMax = buffer;
            maxN = N;
        }
        else if (fChoise == false)
        {
            fChoise = true;
            curMax = buffer;
            maxN = N;
        }

        N++;
    }
    file.close();
    deleteEl(maxN);
    return curMax;
}

void sortFile()
{
    int N = getAmount();
    if (N == 0)
    {
        COUT("The base is empty. Sorting is impossible ", LightRed);
        _getch();
        system("cls");
        rewind(stdin);
        return;
    }
    else if (N == 1)
    {
        COUT("One element in the database. Sorting is impossible", LightRed);
        _getch();
        system("cls");
        rewind(stdin);
        return;
    }
    COUT("Select a key field to sort :\n\n", White);
    for (int i = 0; i < curFileFields.size(); i++)
    {
        COUT("(" + std::to_string(i + 1) + "): " + curFileFields[i] + "\n", White);
    }

    int keyField;
    do
    {
        COUT("Select a key field : ", White);
        std::cin >> keyField;
        if (keyField >= 1 && keyField <= curFileFields.size())
            break;
        else
        {
            COUT("Error!\n", LightRed);
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }
    } while (true);

    std::ifstream file(path_files[curFile]);
    std::ofstream fileSorted(folder + "/tempS_.txt");

    std::string str;
    std::getline(file, str);
    fileSorted << str << "\n";
    while (true)
    {
        std::getline(file, str);
        fileSorted << str << "\n";
        if (str == "--------------------")
            break;
    }

    int file_ = curFile;
    bool first = false;
    std::vector<std::string> prev;
    std::vector<std::string> cur;


    for (int i = 0; i < N; i++)
    {
        cur = getMax(file, keyField - 1, ((i == 0) ? NULL : &cur));
        file.open(path_files[curFile]);
        while (true)
        {
            std::getline(file, str);
            if (str == "--------------------")
                break;
        }
        for (int j = 0; j < curFileFields.size(); j++)
        {
            fileSorted << curFileFields[j] + ": " << cur[j] << "\n";
        }
        fileSorted << "\n";
    }


    file.close();
    fileSorted.close();
    remove(path_files[curFile]);
    rename(folder + "/tempS_.txt", path_files[curFile]);

    COUT("\nSuccess!\n", Green);
    char ch = _getch();
    rewind(stdin);
    system("cls");
}


void workMenu()
{
    COUT("                     Add an object to the database  (1)                 \n\n", White, Blue);
    COUT("                    Delete the object from the database  (2)                 \n\n", White, Blue);
    COUT("                     Edit database object  (3)                   \n\n", White, Blue);
    COUT("                     Find objects by parameter  (4)                 \n\n", White, Blue);
    COUT("                         Sort database (5)                    \n\n", White, Blue);
    COUT("                          Print database  (6)                     \n\n", White, Blue);
    COUT("                               Back (7)                             \n\n", White, Blue);

    char choise;
    do
    {
        choise = _getch();
    } while (!(choise >= '1' && choise <= '7'));
    system("cls");

    if (choise == '1')
        addObj();
    else if (choise == '2')
        deleteObj();
    else if (choise == '3')
        editObj();
    else if (choise == '4')
        findObj();
    else if (choise == '5')
        sortFile();
    else if (choise == '6')
        showBase();
    else if (choise == '7')
        MENU = 1;
}

void globalSearchMenu()
{
    COUT("                       Search in all databases                      \n\n", Black, White);

    if (path_files.size() == 0)
    {
        COUT("\nThere are no databases. Create a database to work with \n\n", LightRed);
        std::cout << "Press any key to continue ...";
        _getch();
        rewind(stdin);
        system("cls");
        MENU = 1;
        return;
    }


    COUT(" Enter keyword : ", White);
    std::string key;
    rewind(stdin);
    std::getline(std::cin, key);

    system("cls");

    for (int i = 0; i < path_files.size(); i++)
    {
        curFile = i;
        fixFile();
        std::cout << path_files[i].filename() << std::endl;
        findObj(key);
        std::cout << std::endl << std::endl;
    }

    _getch();
    system("cls");
    MENU = 1;
}

int main()
{
    pathInit();
    langInit();
    while (true)
    {
        switch (MENU)
        {
        case 1: menu1(); break;
        case 2: menu2(); break;
        case 3: menu3(); break;
        case 4: workMenu(); break;
        case 5: globalSearchMenu(); break;
        }
    }
}


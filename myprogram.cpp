#include <iostream>
#include <map>
#include <vector>
#include <string>

template<typename T1, typename T2>
struct Registry {
    std::map<T1, std::vector<T2>> registryEntries;
};
template<typename T1, typename T2>
Registry<T1, T2> registry;

//----------------------------------------------------add---------------------------------------------------------------
template<typename T1, typename T2>
void Add(T1 key, T2 value) {
    registry<T1, T2>.registryEntries[key].push_back(value);
}
//----------------------------------------------------print-------------------------------------------------------------
void PrintIntInt () {
    for (auto & registryEntrie : registry<int, int>.registryEntries) {
        std::cout << registryEntrie.first << ": ";
        for (int i : registryEntrie.second)
            std::cout << i << ", ";
        std::cout << '\n';
    }
}
void PrintIntDouble () {
    for (auto & registryEntrie : registry<int, double>.registryEntries) {
        std::cout << registryEntrie.first << ": ";
        for (double i : registryEntrie.second)
            std::cout << i << ", ";
        std::cout << '\n';
    }
}
void PrintIntString () {
    for (auto & registryEntrie : registry<int, std::string>.registryEntries) {
        std::cout << registryEntrie.first << ": ";
        for (const auto & i : registryEntrie.second)
            std::cout << i << ", ";
        std::cout << '\n';
    }
}
//----------------------------------------------------------------------------------------------------------------------
void PrintDoubleInt () {
    for (auto & registryEntrie : registry<double, int>.registryEntries) {
        std::cout << registryEntrie.first << ": ";
        for (int i : registryEntrie.second)
            std::cout << i << ", ";
        std::cout << '\n';
    }
}
void PrintDoubleDouble () {
    for (auto & registryEntrie : registry<double, double>.registryEntries) {
        std::cout << registryEntrie.first << ": ";
        for (double i : registryEntrie.second)
            std::cout << i << ", ";
        std::cout << '\n';
    }
}
void PrintDoubleString () {
    for (auto & registryEntrie : registry<double, std::string>.registryEntries) {
        std::cout << registryEntrie.first << ": ";
        for (const auto & i : registryEntrie.second)
            std::cout << i << ", ";
        std::cout << '\n';
    }
}
//----------------------------------------------------------------------------------------------------------------------
void PrintStringInt () {
    for (auto & registryEntrie : registry<std::string, int>.registryEntries) {
        std::cout << registryEntrie.first << ": ";
        for (int i : registryEntrie.second)
            std::cout << i << ", ";
        std::cout << '\n';
    }
}
void PrintStringDouble () {
    for (auto & registryEntrie : registry<std::string, double>.registryEntries) {
        std::cout << registryEntrie.first << ": ";
        for (double i : registryEntrie.second)
            std::cout << i << ", ";
        std::cout << '\n';
    }
}
void PrintStringString () {
    for (auto & registryEntrie : registry<std::string, std::string>.registryEntries) {
        std::cout << registryEntrie.first << ": ";
        for (const auto & i : registryEntrie.second)
            std::cout << i << ", ";
        std::cout << '\n';
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Print() {
    PrintIntInt(); PrintIntDouble(); PrintIntString();
    PrintDoubleInt(); PrintDoubleDouble(); PrintDoubleString();
    PrintStringInt(); PrintStringDouble(); PrintStringString();
}
//----------------------------------------------------find--------------------------------------------------------------
template<typename T>
void FindInt(const T& key) {
    for (auto it = registry<T, int>.registryEntries.begin(); it != registry<T, int>.registryEntries.end(); ++it) {
        if (it->first == key) {
            for (int i = 0; i < it->second.size(); ++i)
                std::cout << it->second[i] << ", ";
        }
    }
}
template<typename T>
void FindDouble(const T& key) {
    for (auto it = registry<T, double>.registryEntries.begin(); it != registry<T, double>.registryEntries.end(); ++it) {
        if (it->first == key) {
            for (int i = 0; i < it->second.size(); ++i)
                std::cout << it->second[i] << ", ";
        }
    }
}
template<typename T>
void FindString(const T& key) {
    for (auto it = registry<T, std::string>.registryEntries.begin(); it != registry<T, std::string>.registryEntries.end(); ++it) {
        if (it->first == key) {
            for (int i = 0; i < it->second.size(); ++i)
                std::cout << it->second[i] << ", ";
        }
    }
}

template<typename T>
void Find(T key) {
    FindInt(key);
    FindDouble(key);
    FindString(key);
    std::cout << '\n';
}
//----------------------------------------------------remove------------------------------------------------------------
template<typename T>
void RemoveInt(const T& key) {
    registry<T, int>.registryEntries.erase(key);
}
template<typename T>
void RemoveDouble(const T& key) {
    registry<T, double>.registryEntries.erase(key);
}
template<typename T>
void RemoveString(const T& key) {
    registry<T, std::string>.registryEntries.erase(key);
}

template<typename T>
void Remove(T key) {
    RemoveInt(key);
    RemoveDouble(key);
    RemoveString(key);
}
//----------------------------------------------------------------------------------------------------------------------
bool CheckingForDouble(std::string& str) {
    bool good = true;

    int countPoint = 0;
    for (char i : str)
        if (i == '.')
            countPoint++;

    int positionPoint = -1;
    if (countPoint == 1 && str.length() > 1) {
        bool found = false;
        for (int i = 0; str.length() > i && !found; i++)
            if (str[i] == '.') {
                found = true;
                positionPoint = i;
            }
    } else good = false;

    if (positionPoint == 0) {
        bool found = false;
        for (int i = 1; i < str.length() && !found; i++)
            if (str[i] < '0' || str[i] > '9') {
                found = true;
                good = false;
            }
    } else if (positionPoint > 0 && positionPoint < str.length() - 1 && str[str.length() - 1] != '0') {
        bool found = false;
        for (int i = 0; i < positionPoint && !found; i++)
            if (str[i] < '0' || str[i] > '9') {
                found = true;
                good = false;
            }
        for (int i = positionPoint + 1; i < str.length() && !found; i++)
            if (str[i] < '0' || str[i] > '9') {
                found = true;
                good = false;
            }
    } else good = false;

    if (good && std::stod(str) > 1.7976931348623158e+308)
        good = false;
    return good;
}

bool CheckingForInt(std::string& str) {
    bool found = false;
    for (int i = 0; i < str.length() && !found; i++)
        if (!std::isdigit(str[i]))
            found = true;
    if (!found && std::stoi(str) > 2147483647)
        found = true;
    return found;
}

std::string VariableType(std::string& str) {
    if (CheckingForDouble(str))
        return "double";
    else if (!CheckingForInt(str))
        return "int";
    else {
        return "string";
    }
}

void BeforeAdd(std::string& strKey, std::string& strValue) {
    if (VariableType(strKey) == "int" && VariableType(strValue) == "int")
        Add(std::stoi(strKey), std::stoi(strValue));
    else if (VariableType(strKey) == "int" && VariableType(strValue) == "double")
        Add(std::stoi(strKey), std::stod(strValue));
    else if (VariableType(strKey) == "int" && VariableType(strValue) == "string")
        Add(std::stoi(strKey), strValue);
    else if (VariableType(strKey) == "double" && VariableType(strValue) == "int")
        Add(std::stod(strKey), std::stoi(strValue));
    else if (VariableType(strKey) == "double" && VariableType(strValue) == "double")
        Add(std::stod(strKey), std::stod(strValue));
    else if (VariableType(strKey) == "double" && VariableType(strValue) == "string")
        Add(std::stod(strKey), strValue);
    else if (VariableType(strKey) == "string" && VariableType(strValue) == "int")
        Add(strKey, std::stoi(strValue));
    else if (VariableType(strKey) == "string" && VariableType(strValue) == "double")
        Add(strKey, std::stod(strValue));
    else if (VariableType(strKey) == "string" && VariableType(strValue) == "string")
        Add(strKey, strValue);
}

void BeforeFind(std::string& strKey) {
    if (VariableType(strKey) == "int")
        Find(std::stoi(strKey));
    else if (VariableType(strKey) == "double")
        Find(std::stod(strKey));
    else if (VariableType(strKey) == "string")
        Find(strKey);
}

void BeforeRemove(std::string& strKey) {
    if (VariableType(strKey) == "int")
        Remove(std::stoi(strKey));
    else if (VariableType(strKey) == "double")
        Remove(std::stod(strKey));
    else if (VariableType(strKey) == "string")
        Remove(strKey);
}

int main() {
    std::string command;
    while (command != "exit") {
        std::cout << "Enter command(add/remove/print/find/exit): ";
        std::cin >> command;

        if (command == "add") {
            std::cout << "Enter Add key and value separated by a space: ";
            std::string key, value;
            std::cin >> key >> value;
            BeforeAdd(key, value);
        } else if (command == "remove") {
            std::cout << "Enter the key to delete the item(s): ";
            std::string key;
            std::cin >> key;
            BeforeRemove(key);
        } else if (command == "print") {
            std::cout << "Displaying all elements with their keys:\n";
            Print();
        } else if (command == "find") {
            std::cout << "Finding all elements by their key: ";
            std::string key;
            std::cin >> key;
            BeforeFind(key);
        }
    }
}
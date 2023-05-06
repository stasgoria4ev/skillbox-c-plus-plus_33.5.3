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
    } else if (positionPoint > 0 && positionPoint < str.length() - 1) {
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

//----------------------------------------------------add---------------------------------------------------------------
template<typename T1, typename T2>
void Add(T1 key, T2 value) {
    registry<T1, T2>.registryEntries[key].push_back(value);
}
//----------------------------------------------------print-------------------------------------------------------------
template<typename T>
void PrintInt() {
    for (auto it = registry<int, T>.registryEntries.begin(); it != registry<int, T>.registryEntries.end(); ++it) {
        std::cout << it->first << ": ";
        for (int i = 0; i < it->second.size(); ++i)
            std::cout << it->second[i] << ", ";
        std::cout << '\n';
    }
}

template<typename T>
void PrintDouble() {
    for (auto it = registry<double, T>.registryEntries.begin(); it != registry<double, T>.registryEntries.end(); ++it) {
        std::cout << it->first << ": ";
        for (int i = 0; i < it->second.size(); ++i)
            std::cout << it->second[i] << ", ";
        std::cout << '\n';
    }
}

template<typename T>
void PrintString() {
    for (auto it = registry<std::string, T>.registryEntries.begin(); it != registry<std::string, T>.registryEntries.end(); ++it) {
        std::cout << it->first << ": ";
        for (int i = 0; i < it->second.size(); ++i)
            std::cout << it->second[i] << ", ";
        std::cout << '\n';
    }
}

template<typename T>
void BeforePrint() {
    PrintInt<T>();
    PrintDouble<T>();
    PrintString<T>();
}
void Print() {
    BeforePrint<int>(); BeforePrint<double>(); BeforePrint<std::string>();
}
//----------------------------------------------------find--------------------------------------------------------------
template<typename T1, typename T2>
void FindAllTypes(const T1& key) {
    for (auto it = registry<T1, T2>.registryEntries.begin(); it != registry<T1, T2>.registryEntries.end(); ++it) {
        if (it->first == key) {
            for (int i = 0; i < it->second.size(); ++i)
                std::cout << it->second[i] << ", ";
        }
    }
}

template<typename T>
void Find(T key) {
    FindAllTypes<T, int>(key);
    FindAllTypes<T, double>(key);
    FindAllTypes<T, std::string>(key);
    std::cout << '\n';
}
//----------------------------------------------------remove------------------------------------------------------------
template<typename T1, typename T2>
void RemoveAllTypes(const T1& key) {
    registry<T1, T2>.registryEntries.erase(key);
}

template<typename T>
void Remove(T key) {
    RemoveAllTypes<T, int>(key);
    RemoveAllTypes<T, double>(key);
    RemoveAllTypes<T, std::string>(key);
}
//----------------------------------------------------------------------------------------------------------------------

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
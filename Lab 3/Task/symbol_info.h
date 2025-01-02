#include <bits/stdc++.h>

using namespace std;

class symbol_info
{
private:
    string name;
    string type;
    string symbolType; // attribute to store the type of symbol (variable/array/function)
    string returnType; // attribute to store the return type of the symbol (int/float/void/...)
    map <string, vector<string>> parameters; // attribute to store the parameters of the function
    int arraySize; // attribute to store the array size if the symbol is an array
    symbol_info* next;

public:
    symbol_info(string name, string type, string symbolType = "", string returnType = "", const vector<string> &parametersType = vector<string>(), const vector<string> &parametersName = vector<string>(), int arraySize = 0)
    {
        this->name = name;
        this->type = type;
        this->symbolType = symbolType;
        this->returnType = returnType;
        this->parametersType = parametersType;
        this->parametersName = parametersName;
        this->arraySize = arraySize;
    }
    string getname()
    {
        return name;
    }
    string get_type()
    {
        return type;
    }
    void set_name(string name)
    {
        this->name = name;
    }
    void set_type(string type)
    {
        this->type = type;
    }
    string get_symbolType()
    {
        return symbolType;
    }
    void set_symbolType(string symbolType)
    {
        this->symbolType = symbolType;
    }
    string get_returnType()
    {
        return returnType;
    }
    void set_returnType(string returnType)
    {
        this->returnType = returnType;
    }
    vector<string> get_parameters()
    {
        return parameters;
    }
    void set_parametersType(map<string, vector<string>> &parameters)
    {
        this->parameters = parameters;
    }

    int get_arraySize()
    {
        return arraySize;
    }
    void set_arraySize(int arraySize)
    {
        this->arraySize = arraySize;
    }
    symbol_info* get_next()
    {
        return next;
    }
    void set_next(symbol_info* next)
    {
        this->next = next;
    }
    ~symbol_info()
    {
        // Write necessary code to deallocate memory, if necessary
    }
};
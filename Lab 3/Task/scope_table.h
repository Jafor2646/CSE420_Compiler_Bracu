#include "symbol_info.h"

using namespace std;

class scope_table
{
private:
    int bucket_count;
    int unique_id;
    scope_table *parent_scope = NULL;
    vector<list<symbol_info *>> table;

    int hash_function(string name)
    {
        // write your hash function here
        int sum = 0;
        for (char c : name)
        {
            sum += c;
        }
        return sum % bucket_count;
    }

public:
    scope_table();
    scope_table(int bucket_count, int unique_id, scope_table *parent_scope);
    scope_table *get_parent_scope();
    int get_unique_id();
    symbol_info *lookup_in_scope(symbol_info* symbol);
    bool insert_in_scope(symbol_info* symbol);
    bool delete_from_scope(symbol_info* symbol);
    void print_scope_table(ofstream& outlog);
    ~scope_table();

    // you can add more methods if you need
};

scope_table::scope_table()
{
    // default constructor
    bucket_count = 0;
    unique_id = 1;
    parent_scope = NULL;
}

scope_table::scope_table(int bucket_count, int unique_id, scope_table *parent_scope)
{
    // parameterized constructor
    this->bucket_count = bucket_count;
    this->unique_id = unique_id;
    this->parent_scope = parent_scope;

    // initialize the table with empty lists
    table.resize(bucket_count);
}

scope_table *scope_table::get_parent_scope()
{
    return parent_scope;
}

int scope_table::get_unique_id()
{
    return unique_id;
}

symbol_info *scope_table::lookup_in_scope(symbol_info* symbol)
{
    int index = hash_function(symbol->getname());
    list<symbol_info *> &bucket = table[index];

    for (symbol_info *info : bucket)
    {
        if (info->getname() == symbol->getname())
        {
            return info;
        }
    }

    return NULL;
}

bool scope_table::insert_in_scope(symbol_info* symbol)
{
    if (lookup_in_scope(symbol) != NULL)
    {
        return false; // symbol already exists in the scope
    }

    int index = hash_function(symbol->getname());
    list<symbol_info *> &bucket = table[index];
    bucket.push_back(symbol);

    return true;
}

bool scope_table::delete_from_scope(symbol_info* symbol)
{
    int index = hash_function(symbol->getname());
    list<symbol_info *> &bucket = table[index];

    for (auto it = bucket.begin(); it != bucket.end(); ++it)
    {
        if ((*it)->getname() == symbol->getname())
        {
            bucket.erase(it);
            return true;
        }
    }

    return false; // symbol not found in the scope
}

void scope_table::print_scope_table(ofstream& outlog)
{
    outlog << "ScopeTable # " << unique_id << endl;

    for (int i = 0; i < bucket_count; i++)
    {
        outlog << i << " --> ";
        list<symbol_info *> &bucket = table[i];

        for (symbol_info *info : bucket)
        {
            outlog << "<" << info->getname() << ": " << info->get_type() << "> ";
        }

        outlog << endl;
    }
}

scope_table::~scope_table()
{
    // destructor
    for (int i = 0; i < bucket_count; i++)
    {
        list<symbol_info *> &bucket = table[i];

        for (symbol_info *info : bucket)
        {
            delete info;
        }
    }
}
#include "scope_table.h"

using namespace std;

class symbol_table
{
private:
    scope_table *current_scope;
    int bucket_count;
    int current_scope_id;

public:
    symbol_table(int bucket_count);
    ~symbol_table();
    void enter_scope();
    void exit_scope();
    bool insert(symbol_info* symbol);
    symbol_info* lookup(symbol_info* symbol);
    void print_current_scope(ofstream& outlog);
    void print_all_scopes(ofstream& outlog);
    int get_current_scope_id() { return current_scope_id; }
    // you can add more methods if you need 
};

symbol_table::symbol_table(int bucket_count)
{
    this->bucket_count = bucket_count;
    this->current_scope = new scope_table(bucket_count, 1, NULL);
    this->current_scope_id = 1;
}

symbol_table::~symbol_table()
{
    delete current_scope;
}

void symbol_table::enter_scope()
{
    scope_table *new_scope = new scope_table(bucket_count, current_scope_id, current_scope);
    current_scope = new_scope;
    current_scope_id++;
}

void symbol_table::exit_scope()
{
    if (current_scope->get_parent_scope() != nullptr)
    {
        scope_table *parent_scope = current_scope->get_parent_scope();
        delete current_scope;
        current_scope = parent_scope;
        current_scope_id--;
    }
}

bool symbol_table::insert(symbol_info* symbol)
{
    return current_scope->insert_in_scope(symbol);
}

symbol_info* symbol_table::lookup(symbol_info* symbol)
{
    scope_table *temp_scope = current_scope;
    while (temp_scope != nullptr)
    {
        symbol_info *found_symbol = temp_scope->lookup_in_scope(symbol);
        if (found_symbol != nullptr)
        {
            return found_symbol;
        }
        temp_scope = temp_scope->get_parent_scope();
    }
    return nullptr;
}

void symbol_table::print_current_scope(ofstream& outlog)
{
    current_scope->print_scope_table(outlog);
}

void symbol_table::print_all_scopes(ofstream& outlog)
{
    outlog << "################################" << endl << endl;
    scope_table *temp = current_scope;
    while (temp != nullptr)
    {
        temp->print_scope_table(outlog);
        temp = temp->get_parent_scope();
    }
    outlog << "################################" << endl << endl;
}
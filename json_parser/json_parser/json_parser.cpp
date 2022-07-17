#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

#define NULL 0
#define INT 1
#define DOUBLE 2
#define STR 3
#define BOOL 4
#define OBJECT 5
#define LIST 6


class Object {
private:
    int INT_VAL;
    double DOUBLE_VAL;
    string STRING_VAL;
    bool BOOL_VAL;
    unordered_map<string, Object> OBJECT_VAL;
    vector<Object> LIST_VAL;
    
    int type;
    
    void del() {
        if (type == STR) STRING_VAL = "";
        if (type == OBJECT) OBJECT_VAL.clear();
        if (type == LIST) LIST_VAL.clear();
        type = NULL;
    }
    
    stringstream ss;
public:
    //constructors
    Object() {
        //initialize
        INT_VAL = 0;
        DOUBLE_VAL = 0;
        STRING_VAL = "";
        BOOL_VAL = true;
        OBJECT_VAL = {};
        LIST_VAL = {};
        type = NULL;
    }
    Object(const int& x) {
        del();
        type = INT;
        INT_VAL = x;
    }
    Object(const double& x) {
        del();
        type = DOUBLE;
        DOUBLE_VAL = x;
    }
    Object(const string& x) {
        del();
        type = STR;
        STRING_VAL = x;
    }
    Object(const char* x) {
        del();
        type = STR;
        STRING_VAL = x;
    }
    Object(const bool& x) {
        del();
        type = BOOL;
        BOOL_VAL = x;
    }

    string get_type() {
        if (type == INT) return "INT";
        if (type == DOUBLE) return "DOUBLE";
        if (type == STR) return "STRING";
        if (type == BOOL) return "BOOL";
        if (type == OBJECT) return "OBJECT";
        if (type == LIST) return "LIST";
        return "NULL";
    }
    void set_type(int a) {
        type = a;
    }
    void parse(string json) {
        
    }

    
};



int main()
{
    
}

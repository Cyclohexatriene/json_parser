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


stringstream ss;

class Object {
private:
    int INT_VAL;
    double DOUBLE_VAL;
    string STRING_VAL;
    bool BOOL_VAL;
    unordered_map<string, Object* > OBJECT_VAL;
    vector<Object* > LIST_VAL;
    vector<string> keys;

    int type;
    
    void del() {
        if (type == STR) STRING_VAL = "";
        if (type == OBJECT) OBJECT_VAL.clear();
        if (type == LIST) LIST_VAL.clear();
        type = NULL;
    }
    void set_type(int a) {
        type = a;
    }

    void insert(string key, Object* val) {
        if (type != OBJECT) {
            del();
            set_type(OBJECT);
        }
        keys.push_back(key);
        OBJECT_VAL[key] = val;
    }
    void push(Object* val) {
        if (type != LIST) {
            del();
            set_type(LIST);
        }
        LIST_VAL.push_back(val);
    }

    //parsers
    Object parse_val() {
        if (ss.peek() == -1) {
            Object nl;
            nl.set_type(NULL);
        }
        else if (ss.peek() == '"') return parse_str();
        else if (ss.peek() == 'f' || ss.peek() == 't') return parse_bool();
        else if (ss.peek() == '{') return parse_object();
        else if (ss.peek() == '[') return parse_list();
        else if (ss.peek() == 'n') return parse_null();
        else return parse_num();
    }
    Object parse_num() {
        string str;
        bool isfloat = false;
        while (isdigit(ss.peek()) || ss.peek() == '-' || ss.peek() == '+' || ss.peek() == '.' || ss.peek() == 'e') {
            if (ss.peek() == '.' || ss.peek() == 'e') isfloat = true;
            str += ss.get();
        }
        if (isfloat) return Object(stof(str));
        else return Object(stoi(str));

    }
    Object parse_str() {
        ss.get();
        string str;
        while (ss.peek() != '"') str += ss.get();
        ss.get();
        return Object(str);
    }
    Object parse_bool() {
        if (ss.peek() == 'f') {
            ss.get(); ss.get(); ss.get(); ss.get(); ss.get();
            return Object(false);
        }
        else {
            ss.get(); ss.get(); ss.get(); ss.get();
            return Object(true);
        }
    }
    Object parse_object() {
        Object res;
        ss.get();
        while (ss.peek() != '}') {
            ss >> ws;
            string key;
            while (ss.peek() != ' ' && ss.peek() != ':' && ss.peek() != '\t' && ss.peek() != '\n') key += ss.get();
            ss >> ws; ss.get(); ss >> ws;//remove ':' and whitespaces
            Object* val = new Object();
            *val = parse_val();
            res.insert(key, val);
            //remove ',' and whitespaces
            ss >> ws;
            if (ss.peek() == ',') {
                ss.get();
                ss >> ws;
            }
        }
        ss.get();
        return res;
    }
    Object parse_list() {
        ss.get();
        Object res;
        while (ss.peek() != ']') {
            Object* temp = new Object();
            *temp = parse_val();
            res.push(temp);
            ss >> ws;
            if (ss.peek() == ',') {
                ss.get();
                ss >> ws;
            }
        }
        ss.get();
        res.set_type(LIST);
        return res;
        
    }
    Object parse_null() {
        ss.get(); ss.get(); ss.get(); ss.get();
        return Object();
    }

    void printNULL() {
        cout << "null";
    }
    void printINT() {
        cout << INT_VAL;
    }
    void printSTR() {
        cout << '"'<<STRING_VAL<<'"';
    }
    void printDOUBLE() {
        cout << DOUBLE_VAL;
    }
    void printBOOL() {
        if (BOOL_VAL) cout << "true";
        else cout << "false";
    }
    void printOBJECT() {
        cout << "{ ";
        bool a = true;
        for (auto i : keys) {
            if (a) a = false;
            else cout << " , ";
            cout << i;
            cout << " : ";
            OBJECT_VAL[i]->show(false);
        }
        cout << " }";
    }
    void printLIST() {
        cout << "[";
        bool a = true;
        for (auto i : LIST_VAL) {
            if (a) a = false;
            else cout << " , ";
            i->show(false);
        }
        cout << "]";
    }
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
    
    void parse(string json) {
        ss.clear();
        ss << json;
        ss >> ws;
        *this = parse_val();
    }
    void show(bool end = true) {
        if (type == NULL) printNULL();
        else if (type == INT) printINT();
        else if (type == DOUBLE) printDOUBLE();
        else if (type == STR) printSTR();
        else if (type == BOOL) printBOOL();
        else if (type == OBJECT) printOBJECT();
        else if (type == LIST) printLIST();
        if (end) cout << endl;
    }
    Object get_val(string key) {
        return  *OBJECT_VAL['"'+key+'"'];
    }
    Object get_val(int idx) {
        return *LIST_VAL[idx];
    }
};

int main()
{
    Object test;
    test.parse(
        "{\"sites\": [{ \"name\":\"菜鸟教程\" , \"url\":\"www.runoob.com\" }, { \"name\":\"google\" , \"url\":\"www.google.com\" }, { \"name\":\"微博\" , \"url\":\"www.weibo.com\" }]}"
    );
    test.show();
    test.get_val("sites").get_val(0).get_val("name").show();
    
}

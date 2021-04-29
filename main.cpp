#include "Trie.h"

using namespace std;

void search(const Trie& t, const string& str)
{
    cout << str << " ";
    if (!t.search(str)) {
        cout << "NOT ";
    }
    cout << "found" << endl;
}

void startsWith(const Trie& t, const string& str)
{
    cout << str << " is ";
    if (!t.startsWith(str)) {
        cout << "NOT ";
    }
    cout << "present as a prefix" << endl;
}

int main()
{
    Trie t;
    t.insert("the");
    t.insert("a");
    t.insert("therefore");
    t.insert("answer");
    t.insert("any");
    t.insert("by");
    t.insert("bye");
    t.insert("their");
    t.insert("app");
    t.insert("apple");
    search(t, "a");
    search(t, "ap");
    search(t, "app");
    search(t, "t");
    search(t, "then");
    search(t, "there");
    search(t, "their");
    search(t, "therefore");
    search(t, "buy");
    search(t, "by");
    startsWith(t, "a");
    startsWith(t, "ap");
    startsWith(t, "app");
    startsWith(t, "t");
    startsWith(t, "then");
    startsWith(t, "there");
    startsWith(t, "their");
    startsWith(t, "therefore");
    startsWith(t, "buy");
    startsWith(t, "by");
    return 0;
}

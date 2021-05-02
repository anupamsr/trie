#include "Trie.h"
#include <cassert>
using namespace std;

int main(int argc, char * argv[])
{
    Trie t;
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            t.insert(argv[i]);
        }
        t.print();
        return 0;
    }

    // Test mode
    t.insert("apple");
    t.insert("apple");
    assert(t.size() == 6);
    assert(t.countWordsEqualTo("apple") == 2);
    assert(t.countWordsStartingWith("app") == 2);
    t.erase("apple");
    assert(t.size() == 6);
    assert(t.countWordsEqualTo("apple") == 1);
    assert(t.countWordsStartingWith("app") == 1);
    t.erase("apple");
    assert(t.size() == 1);
    assert(t.countWordsStartingWith("app") == 0);
    t.insert("the");
    t.insert("a");
    t.insert("therefore");
    t.insert("answer");
    t.insert("any");
    t.insert("by");
    t.insert("bye");
    t.insert("their");
    t.insert("app");
    t.insert("app");
    t.insert("apple");
    t.print();
    assert(t.search("a"));
    assert(!t.search("ap"));
    assert(t.search("app"));
    assert(!t.search("t"));
    assert(!t.search("then"));
    assert(!t.search("there"));
    assert(t.search("their"));
    assert(t.search("therefore"));
    assert(!t.search("buy"));
    assert(t.search("by"));
    assert(t.startsWith("a"));
    assert(t.startsWith("ap"));
    assert(t.startsWith("app"));
    assert(t.startsWith("t"));
    assert(t.startsWith("the"));
    assert(!t.startsWith("then"));
    assert(t.startsWith("there"));
    assert(t.startsWith("their"));
    assert(t.startsWith("therefore"));
    assert(!t.startsWith("buy"));
    assert(t.startsWith("by"));
    assert(t.countWordsEqualTo("a") == 1);
    assert(t.countWordsEqualTo("ap") == 0);
    assert(t.countWordsEqualTo("app") == 2);
    assert(t.countWordsEqualTo("appl") == 0);
    assert(t.countWordsEqualTo("apple") == 1);
    assert(t.countWordsEqualTo("applee") == 0);
    assert(t.countWordsStartingWith("a") == 6);
    assert(t.countWordsStartingWith("ap") == 3);
    assert(t.countWordsStartingWith("app") == 3);
    assert(t.countWordsStartingWith("appl") == 1);
    assert(t.countWordsStartingWith("apple") == 1);
    assert(t.countWordsStartingWith("applee") == 0);
    assert(t.size() == 26);
    t.erase("app");
    assert(t.size() == 26);
    assert(t.countWordsEqualTo("app") == 1);
    t.erase("app");
    assert(t.size() == 26);
    assert(t.countWordsEqualTo("app") == 0);
    t.erase("app");
    assert(t.countWordsEqualTo("app") == 0);
    t.erase("apple");
    assert(t.size() == 22);
    assert(t.countWordsStartingWith("a") == 3);
    assert(t.countWordsStartingWith("ap") == 0);
    assert(t.countWordsStartingWith("app") == 0);
    assert(t.countWordsStartingWith("appl") == 0);
    assert(t.countWordsStartingWith("apple") == 0);
    cout << "All asserts passed" << endl;
    return 0;
}

#pragma once

#include <iostream>
#include <queue>
#include <string>

using namespace std;

//size_t
//find_common_prefix(const string& s, const string& t, const size_t& i)
//{
//    if (i >= s.size() || i >= t.size() || s[i] != t[i]) {
//        return i;
//    }

//    return find_common_prefix(s, t, i + 1);
//}

//string
//find_common_prefix(const string& s, const string& t)
//{
//    auto end = find_common_prefix(s, t, 0);

//    return s.substr(0, end);
//}

class Trie {
private:
    struct Node {
        size_t end = 0;
        Node* leaf[26] = { 0 }; // Only supporting lower case as of now
    };

    Node* root;
    void insert(Node* head, const string& word, const size_t pos)
    {
        if (pos > word.size()) {
            return;
        } else if (pos == word.size()) {
            ++head->end;
        }

        auto idx = word[pos] - 'a';
        Node* node = head->leaf[idx];
        if (node == nullptr) {
            node = new Node();
            head->leaf[idx] = node;
        }
        insert(node, word, pos + 1);
    }

    size_t count(Node* head)
    {
        if (head == nullptr)
            return 0;
        size_t c = head->end;
        for (size_t i = 0; i < 26; ++i) {
            c += count(head->leaf[i]);
        }
        return c;
    }

public:
    Trie()
        : root(new Node())
    {
    }

    void insert(const string& word)
    {
        insert(root, word, 0);
    }

    bool search(const string& word) const
    {
        auto* node = root;
        size_t pos = 0;
        while (node != nullptr && pos < word.size()) {
            node = node->leaf[word[pos] - 'a'];
            if (node == nullptr) {
                break;
            }
            ++pos;
        }
        if (node != nullptr && node->end != 0) {
            return true;
        }
        return false;
    }

    bool startsWith(const string& word) const
    {
        auto* node = root;
        size_t pos = 0;
        while (node != nullptr && pos < word.size()) {
            node = node->leaf[word[pos] - 'a'];
            if (node == nullptr) {
                break;
            }
            if (pos == word.size() - 1) {
                return true;
            }
            ++pos;
        }
        return false;
    }

    size_t countWordsEqualTo(const string& word)
    {
        Node* node = root;
        size_t pos = 0;
        while (node != nullptr && pos < word.size()) {
            size_t idx = word[pos] - 'a';
            if (node->leaf[idx] == nullptr) {
                return 0;
            }
            node = node->leaf[idx];
            ++pos;
        }
        if (node != nullptr) {
            return node->end;
        }
        return 0;
    }

    size_t countWordsStartingWith(string prefix)
    {
        Node* node = root;
        size_t pos = 0;
        while (node != nullptr && pos < prefix.size()) {
            size_t idx = prefix[pos] - 'a';
            if (node->leaf[idx] == nullptr) {
                return 0;
            }
            node = node->leaf[idx];
            ++pos;
        }
        if (node != nullptr) {
            return count(node);
        }
        return 0;
    }

    void print() const
    {
        cout << "[root]" << endl;
        queue<Node*> q;
        q.push(root);
        do {
            auto* node = q.front();
            q.pop();
            for (size_t i = 0; i < 26; ++i) {
                if (node->leaf[i] != nullptr) {
                    cout << "[" << (char)('a' + i) << "]" << node->leaf[i]->end << " ";
                    q.push(node->leaf[i]);
                }
            }
            cout << endl;
        } while (!q.empty());
    }
};

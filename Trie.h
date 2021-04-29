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
        Node* children[26] = { 0 }; // Only supporting lower case as of now
    };

    Node* root;
    void insert(Node* head, const string& word, const size_t start)
    {
        if (start >= word.size()) {
            return;
        }

        auto first_char_idx = word[start] - 'a';

        Node* node = head->children[first_char_idx];
        if (node == nullptr) {
            node = new Node();
            head->children[first_char_idx] = node;
        }
        if (start + 1 >= word.size()) {
            ++node->end;
        } else {
            insert(node, word, start + 1);
        }
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
        size_t key = 0;
        while (node != nullptr && key < word.size()) {
            node = node->children[word[key] - 'a'];
            if (node == nullptr) {
                break;
            }
            if (key == word.size() - 1 && node->end != 0) {
                return true;
            }
            ++key;
        }
        return false;
    }

    bool startsWith(const string& word) const
    {
        auto* node = root;
        size_t key = 0;
        while (node != nullptr && key < word.size()) {
            node = node->children[word[key] - 'a'];
            if (node == nullptr) {
                break;
            }
            if (key == word.size() - 1) {
                return true;
            }
            ++key;
        }
        return false;
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
                if (node->children[i] != nullptr) {
                    cout << "[" << ('a' + i) << "]" << node->children[i]->end << " ";
                    q.push(node->children[i]);
                }
            }
            cout << endl;
        } while (!q.empty());
    }
};

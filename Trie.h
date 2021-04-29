#pragma once

#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

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
        unordered_map<char, Node*> children;
    };

    Node* root;
    void insert(Node* head, const string& word, const size_t start)
    {
        if (start >= word.size()) {
            return;
        }

        auto first_char = word[start];
        auto it = head->children.find(first_char);
        Node* node;
        if (it != head->children.end()) {
            node = it->second;
        } else {
            node = new Node();
            head->children[first_char] = node;
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
            auto it = node->children.find(word[key]);
            if (it == node->children.end()) {
                break;
            }
            if (key == word.size() - 1 && it->second->end != 1) {
                return true;
            }
            node = it->second;
            ++key;
        }
        return false;
    }

    bool startsWith(const string& word) const
    {
        auto* node = root;
        size_t key = 0;
        while (node != nullptr && key < word.size()) {
            auto it = node->children.find(word[key]);
            if (it == node->children.end()) {
                break;
            }
            if (key == word.size() - 1) {
                return true;
            }
            node = it->second;
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
            if (node != nullptr) {
                for (const auto& p : node->children) {
                    cout << "[" << p.first << "]" << p.second->end << " ";
                    q.push(p.second);
                }
                cout << endl;
            }
        } while (!q.empty());
    }
};

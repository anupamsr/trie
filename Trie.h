#pragma once

#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Trie {
private:
    struct Node {
        size_t end = 0;
        Node* leaf[26] = { 0 }; // Only supporting lower case as of now
    };

    Node* root;

    size_t countWords(Node* head)
    {
        if (head == nullptr) {
            return 0;
        }
        size_t count = head->end;
        for (size_t i = 0; i < 26; ++i) {
            count += countWords(head->leaf[i]);
        }
        return count;
    }

    size_t size(Node* head)
    {
        if (head == nullptr) {
            return 0;
        }
        size_t count = 1;
        for (size_t i = 0; i < 26; ++i) {
            count += size(head->leaf[i]);
        }
        return count;
    }

    void erase(Node* head, const string& word, const size_t pos)
    {
        if (head == nullptr) {
            return;
        }
        size_t idx = word[pos] - 'a';
        Node* node = head->leaf[idx];
        if (node == nullptr)
            return;
        if (pos + 1 == word.size()) {
            if (node->end > 0) {
                --node->end;
            }
        } else {
            erase(node, word, pos + 1);
        }
        if (node->end == 0) {
            bool all_leaves_null = true;
            for (size_t i = 0; i < 26; ++i) {
                if (node->leaf[i] != nullptr) {
                    all_leaves_null = false;
                    break;
                }
            }
            if (all_leaves_null) {
                delete node;
                head->leaf[idx] = nullptr;
            }
        }
        return;
    }

    void clear(Node* head)
    {
        if (head == nullptr) {
            return;
        }
        for (size_t i = 0; i < 26; ++i) {
            if (head->leaf[i] != nullptr) {
                clear(head->leaf[i]);
            }
        }
        delete head;
    }

public:
    Trie()
        : root(new Node())
    {
    }

    ~Trie()
    {
        clear(root);
    }

    void insert(const string& word)
    {
        Node* node = root;
        for (size_t i = 0; i < word.size(); ++i) {
            if (node->leaf[word[i] - 'a'] == nullptr) {
                node->leaf[word[i] - 'a'] = new Node();
            }
            node = node->leaf[word[i] - 'a'];
        }
        ++node->end;
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
            return countWords(node);
        }
        return 0;
    }

    void erase(const string& word)
    {
        erase(root, word, 0);
    }

    size_t size()
    {
        return size(root);
    }

    void print() const
    {
        cout << "[root]" << endl;
        print({ root });
    }

    void print(const vector<Node*>& nodes) const
    {
        vector<vector<char>> leaves(nodes.size());
        size_t total_leaves = 0;
        for (size_t i = 0; i < leaves.size(); ++i) {
            for (size_t j = 0; j < 26; ++j) {
                if (nodes[i]->leaf[j] != nullptr) {
                    leaves[i].emplace_back((char)('a' + j));
                    ++total_leaves;
                }
            }
        }
        if (total_leaves == 0) {
            return;
        }
        for (size_t i = 0; i < leaves.size(); ++i) {
            if (leaves[i].size() == 1) {
                cout << "|";
            } else {
                for (size_t j = 0; j < leaves[i].size(); ++j) {
                    cout << "-";
                }
            }
            cout << " ";
        }
        cout << endl;

        for (size_t i = 0; i < leaves.size(); ++i) {
            for (size_t j = 0; j < leaves[i].size(); ++j) {
                cout << "|";
            }
            cout << " ";
        }
        cout << endl;

        for (size_t i = 0; i < leaves.size(); ++i) {
            for (size_t j = 0; j < leaves[i].size(); ++j) {
                cout << leaves[i][j];
            }
            cout << " ";
        }
        cout << endl;
        vector<Node*> down;
        for (size_t i = 0; i < nodes.size(); ++i) {
            for (size_t j = 0; j < leaves[i].size(); ++j) {
                down.emplace_back(nodes[i]->leaf[leaves[i][j] - 'a']);
            }
        }
        print(down);
    }
};

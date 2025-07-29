// autocomplete_trie.cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class TrieNode {
public:
    bool isEnd;
    unordered_map<char, TrieNode*> children;
    TrieNode() : isEnd(false) {}
};

class Trie {
private:
    TrieNode* root;

    void dfs(TrieNode* node, string prefix, vector<string>& results) {
        if (node->isEnd) results.push_back(prefix);
        for (auto& pair : node->children) {
            dfs(pair.second, prefix + pair.first, results);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c])
                node->children[c] = new TrieNode();
            node = node->children[c];
        }
        node->isEnd = true;
    }

    vector<string> autocomplete(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->children[c])
                return {}; // No matches
            node = node->children[c];
        }
        vector<string> results;
        dfs(node, prefix, results);
        return results;
    }
};

int main() {
    Trie trie;
    trie.insert("hello");
    trie.insert("hell");
    trie.insert("helicopter");
    trie.insert("heat");
    trie.insert("hero");

    string prefix;
    cout << "Enter prefix: ";
    cin >> prefix;

    vector<string> matches = trie.autocomplete(prefix);
    cout << "Autocomplete suggestions for \"" << prefix << "\":\n";
    for (string word : matches)
        cout << " - " << word << endl;

    return 0;
}

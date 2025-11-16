#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// ---------------------------
// Trie Node Structure
// ---------------------------
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int isEndOfWord;
};

// Create a new Trie node
struct TrieNode* createNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    node->isEndOfWord = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;

    return node;
}

// ---------------------------
// INSERT a key into Trie
// ---------------------------
void insert(struct TrieNode* root, char* key) {
    struct TrieNode* crawler = root;

    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';   // position 0–25

        if (crawler->children[index] == NULL)
            crawler->children[index] = createNode();

        crawler = crawler->children[index];
    }

    crawler->isEndOfWord = 1;  // mark end of key
}

// ---------------------------
// SEARCH for a key in Trie
// ---------------------------
int search(struct TrieNode* root, char* key) {
    struct TrieNode* crawler = root;

    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';

        if (crawler->children[index] == NULL)
            return 0;   // key not found

        crawler = crawler->children[index];
    }

    return (crawler != NULL && crawler->isEndOfWord);
}

// ---------------------------
// MAIN PROGRAM
// ---------------------------
int main() {
    struct TrieNode* root = createNode();

    // Sample words
    char* words[] = {"the", "a", "there", "answer", "any", "by", "bye"};
    int n = sizeof(words) / sizeof(words[0]);

    // Insert all words
    for (int i = 0; i < n; i++)
        insert(root, words[i]);

    // Search keys
    char* testKeys[] = {"the", "these", "answer", "bye", "xyz"};
    int m = sizeof(testKeys) / sizeof(testKeys[0]);

    for (int i = 0; i < m; i++) {
        if (search(root, testKeys[i]))
            printf("%s → FOUND\n", testKeys[i]);
        else
            printf("%s → NOT FOUND\n", testKeys[i]);
    }

    return 0;
}

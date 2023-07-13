#pragma once

#include <unordered_map>

struct TrieNode {
	std::unordered_map<char, TrieNode *> child;
	bool isLast;

	TrieNode();
};

void insert(TrieNode *&root, std::string s);
void displayNode(TrieNode *curNode, std::string prefix);
void displayNodes(TrieNode *root, std::string str);
void insertIntoTrie(TrieNode *&root, std::string codes[], int n);
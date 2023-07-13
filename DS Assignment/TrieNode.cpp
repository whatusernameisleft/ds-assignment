#include <string>
#include <iostream>
#include "TrieNode.h"

TrieNode::TrieNode() {
	for (char i = 'a'; i <= 'z'; i++) child[i] = NULL;
	this->isLast = false;
}

void insert(TrieNode *&root, std::string s) {
	int len = s.length();

	TrieNode *itr = root;
	for (int i = 0; i < len; i++) {
		TrieNode *nextNode = itr->child[s[i]];
		if (nextNode == NULL) {
			nextNode = new TrieNode();
			itr->child[s[i]] = nextNode;
		}

		itr = nextNode;

		if (i == len - 1) itr->isLast = true;
	}
}

void displayNode(TrieNode *curNode, std::string prefix) {
	if (curNode->isLast) std::cout << prefix << std::endl;

	for (char i = 'a'; i <= 'z'; i++) {
		TrieNode *nextNode = curNode->child[i];
		if (nextNode != NULL) displayNode(nextNode, prefix + (char)i);
	}
}

void displayNodes(TrieNode *root, std::string str) {
	TrieNode *prevNode = root;
	std::string prefix = "";
	int len  = str.length();

	int i;
	for (i = 0; i < len; i++) {
		prefix += (char)str[i];
		char lastChar = prefix[i];
		TrieNode *curNode = prevNode->child[lastChar];

		if (curNode == NULL) {
			std::cout << "\nNo results found for " << prefix << std::endl;
			i++;
			break;
		}

		std::cout << "\nSuggestions based on " << prefix << " are ";
		displayNode(curNode, prefix);
		prevNode = curNode;
	}
}

void insertIntoTrie(TrieNode *&root, std::string codes[], int n) {
	for (int i = 0; i < n; i++) {
		insert(root, codes[i]);
	}
}
#include <iostream>
#include <unordered_map>

class TrieNode {
  public: // TODO make private with getter & setter
  std::unordered_map<char, TrieNode*> children;
  long offset;
  TrieNode() {
    this->offset = -1; // no file is pointed by this
  }
};

class Trie {
  private:
  TrieNode *root;
  public:
  Trie() {
    root = new TrieNode();
  }
  void insert(std::string key, long offset) {
    TrieNode *current;
    for (const char& c : key) {
      
    }
  }
  long search(std::string key) {

  }
};
class TILDB {
  private:
  Trie trie;
  public:
  std::string getKey(std::string key) {

  }
  void setKey(std::string key, std::string value){

  }
};
int main() {
  std::cout << "Welcome to TrieIndexLogDB!\n";
  return 0;
}
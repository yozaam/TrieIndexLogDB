#include <iostream>

class TrieNode {

};

class Trie {
  private:
  TrieNode *root;
  public:
  Trie() {
    root = new TrieNode();
  }
  void insert(std::string key, long offset) {
    
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
  return 0
}
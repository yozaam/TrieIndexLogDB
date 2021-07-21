#include <iostream>
#include <unordered_map> // for class TrieNode
#include <string> // for class TILDB.reader ifstream
#include <fstream>

class TrieNode {
  public: // TODO make private with getter & setter
  std::unordered_map<char, TrieNode*> children;
  long disk_offset;
  TrieNode() {
    this->disk_offset = -1; // no file is pointed by this
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
    TrieNode *current = root;
    for (const char& c : key) {
      if (current->children.count(c) == 0) {
        current->children[c] = new TrieNode(); // TODO make a pool / pre build the trie ?
      }
      current = current->children[c];
    }
    current->disk_offset = offset;
  }
  long search(std::string key) { // returning -1 for missing key -> should we use exceptions?
    TrieNode *current = root;
    for (const char& c : key) {
      if (current->children.count(c) == 0) {
        return -1;
      }
      current = current->children[c];
    }
    return current->disk_offset;
  }
};

class TILDB {
  private:
  Trie trie;
  // TODO create read and write threads 
  // -> write thread must be single -> read can be multiple
  std::ofstream writer;
  std::ifstream reader;
  public:
  TILDB(std::string filename) {
    writer.open("database/"+filename, std::ios_base::app);
    reader.open("database/"+filename);
  }
  std::string getKey(std::string key) { // TODO should I take a reference of value instead ?
    long file_offset = trie.search(key);
    std::string value = "";
    if (file_offset != -1) {
      reader.seekg(file_offset, std::ios::beg);
      std::getline(reader, value);
      return value;
    } else {
      return ""; // TODO should I use an exception / warning instead
    }
  }
  void setKey(std::string key, std::string value){
    writer << key;
    long file_offset = writer.tellp();
    writer << value << std::endl;
    trie.insert(key, file_offset);
  }
  ~TILDB() {
    writer.close();
    reader.close();
  }
};

class MenuCLI {
  public:
  static void show_menu(){
    while (true) {
      std::string filename = "default", key, value;
      int selection;
      TILDB *tildb = new TILDB(filename); // TODO make a pool for all different files
      std::cout << "1. Change current filename/DB \n2. Write to DB \n3. Read From DB\n";
      std::cin >> selection;
      switch (selection) {
        case 1:
          std::cout << "  Enter filename: ";
          std::cin >> filename;
          tildb = new TILDB(filename);
          break;
        case 2:
          std::cout << "  Enter Key: ";
          std::cin >> key;
          std::cout << "  Enter Value: ";
          std::cin >> value;
          tildb->setKey(key, value);
          std::cout << "Stored in DB\n";
          break;
        case 3:
          std::cout << "  Enter Key: ";
          std::cin >> key;
          value = tildb->getKey(key);
          std::cout << value << "\n";
          break;
      }
    }
  }
};

int main() {
  std::cout << "Welcome to TrieIndexLogDB!\n";
  MenuCLI::show_menu();
  return 0;
}


class TILDB {
  private:
  Trie trie;
  public:
  std::string getKey(std::string key);
  void setKey(std::string key, std::string value);
};
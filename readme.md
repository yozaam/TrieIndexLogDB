TrieIndexLogDB is a key/value datastore using log-structured files with trie structured indexes, allowing very fast write access and lowering RAM requirements compared to other log-structured datastores which use Hash Table Indices

# How to run ?

1. Clone repo  
`git clone https://github.com/yozaam/TrieIndexLogDB.git`
2. Go inside directory  
`cd TrieIndexLogDB`
3. Compile the program  
`g++ main.cpp -o main.o`
4. Run the program  
`./main.o`

# Design of the engine

"Example of Hash Index: [Bitcask](https://docs.riak.com/riak/kv/2.2.3/setup/planning/backend/bitcask/index.html#:~:text=Bitcask%20is%20an%20Erlang%20application,that%20provide%20very%20fast%20access.) is an Erlang application that provides an API for storing and retrieving key/value data using log-structured hash tables that provide very fast access."


- General Architecture for Log Structured DB  
  - Every create/update appends new key value pair into the file 
  - maintain the pointer to the ***latest*** occurance of a key in the hash table / index
- Bitcask architecture / Hash Index
![Hash Index Log Structured DB](/images/hash_index_log_structured_db.png "Hash Index Log Structured DB")

- TrieIndexLogDB architecture / Trie Index
![Trie Index Log Structured DB](/images/trie_index_log_structured_db.png "Trie Index Log Structured DB")

- Bitcask stores every key in memory, along with the byte offset for that key in disk

- This limits the no. of keys that may be stored because they all have to fit in RAM

- My lightwieght storage engine will reduce the space requirements by using a 'Trie' index


*(A string Hash (Bitcask) & Trie traversal both have the same asymptotic time complexity but Trie saves a lot of space by avoiding duplication!)*

### Future Scope
Range Updates (by simultaneous Trie Traversal and sorted Trie Children)
/*Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
The functions get and put must each run in O(1) average time complexity.

  Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4 */

class LRUCache {
public:
    class Node{
        public:
            int val;
            int key;
            Node* next;
            Node* prev;

            Node(int k, int v){
                key = k;
                val = v;
            }
    };

    int size = 0;
    unordered_map<int, Node*> mp; //Each key is mapped to its node's address, so that searching takes O(1) time
    Node* head = new Node(-1, -1), *tail = new Node(-1, -1); //Dummy nodes

     void deleteNode(Node* node){
        Node* after = node->next, *prev = node->prev;

        prev->next = after;
        after->prev = prev;
    }

    void insertNode(Node* node){ //Insert after head
        Node* after = head->next;

        head->next = node;
        node->next = after;

        node->prev = head;
        after->prev = node;
    }

    LRUCache(int capacity) {
        size = capacity;
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) { //TC:O(1)
        if(mp.find(key) == mp.end()) return -1; //Key DNE in LRU

        int val = mp[key]->val;
        deleteNode(mp[key]); //Move node to the front of the LL
        insertNode(mp[key]);

        return val;
    }
    
    void put(int key, int value) { //TC:O(1)
        if(mp.find(key) != mp.end()){ //Key already exists
            mp[key]->val = value; //Update the value
            deleteNode(mp[key]); //Move it to the front of the LL
            insertNode(mp[key]);
        }
        else{  //Key doesn't exist in LL
            if(mp.size() == size){ //LL is full, so remove the last node
                Node* node = tail->prev;
                mp.erase(node->key);
                deleteNode(node);
            }
        
            Node* node = new Node(key, value); //Insert new node at the beginning
            mp[key] = node;
            insertNode(mp[key]);
        }
    }
};

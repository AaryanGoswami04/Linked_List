#include <iostream>
using namespace std;
class Node{
  public:
    int data;
    Node* next;

    Node(int data){
      this->data = data;
      next = NULL;
    }
};
Node* tail=NULL, *head=NULL;

void Insert_End(int val){
  Node* temp = new Node(val);
    if(tail){
      tail->next = temp;
      tail=temp;
    }
    else 
      head=tail=temp;
}

void Insert_Beginning(int val){
  Node* temp = new Node(val);
  temp->next = head;
  head=temp;
  if(!tail) tail=head;
}

void print(){
  Node* temp=head;
  while(temp){
    cout<<temp->data<<" ";
    temp=temp->next;
  }
  cout<<"\n";
}

void insertAt(int val, int pos){
  if(pos == 1){
    Insert_Beginning(val);
    return;
  }
  
  int idx=1;
  Node* temp=NULL;
  
  while(idx != pos){
    temp=temp->next;
    idx++;
  }
  Node* after_temp = temp->next;
  Node* new_node = new Node(val);
  
  temp->next=new_node;
  new_node->next=after_temp;
}

void delete_end(){
  if(!tail) return;
  else{
    Node* temp=head;
    while(temp->next != tail)
      temp=temp->next;
    
    temp->next=NULL;
    delete tail;
    tail=temp;
  }
}
void delete_beginning(){
   if(!head) return;
   Node* new_head = head->next;
   delete head;
   head=new_head;
}
bool search(int key){
  Node* temp=head;
 
  while(temp){
      if(temp->data == key) return 1;
      temp=temp->next;
  }
  return 0;
}
int main() {
  Insert_Beginning(10);
  Insert_Beginning(20);
  Insert_Beginning(30);
  print();
  insertAt(40,2);
  print();
  delete_beginning();
  print();
  cout<<search(30);
}
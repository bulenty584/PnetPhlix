#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED


#include <iostream>
#include <vector>


template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator(): valueList()
        {
            count = 0;
            valueList = nullptr;
            
        }
        
        Iterator(std::vector<ValueType>& vList)
        {
            valueList = &vList;
            count = 0;
           
        }

        ValueType& get_value()
        {
            if (this->is_valid())
                return valueList->at(count);
            throw 1;
            
        }

        bool is_valid() const
        {
            if (valueList == NULL)
                return false;
            if (valueList->empty()) return false;
            if (count >= valueList->size())
                return false;
            if (valueList == nullptr)
                return false;
            
            return true;
        }

        void advance()
        {
            count++;
            
            
        }

      private:
        int count;
        std::vector<ValueType>* valueList;
    };

    TreeMultimap()
    {
        root = nullptr;
        m_size = 0;
    }

    ~TreeMultimap()
    {
        freeTree(root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if (root == nullptr){
            root = new Node;
            root->m_key= key;
            root->valueList.push_back(value);
            root->left=nullptr;
            root->right=nullptr;
            m_size++;
            
        }
        
        else
            insertHelper(root, key, value);
        
       
    }

    Iterator find(const KeyType& key) const
    {
        Node* cur = root;
        
        if (cur == NULL) return Iterator();
        
        while (cur != nullptr){
            if (key == cur->m_key){
                return Iterator(cur->valueList);
            }
            
            else if (key < cur->m_key){
                cur = cur->left;
            }
        
            else if (key > cur->m_key){
                cur = cur->right;
            }
        }
        
        return Iterator();
    }

  private:
    
    struct Node{
        
        KeyType m_key;
        Node* left;
        Node* right;
        std::vector<ValueType> valueList;
                
    };
    
    
    int m_size;
    Node* root;
        
    void insertHelper(Node* inst, const KeyType& key, const ValueType& value){
        
        m_size++;
        
        if (inst->right==nullptr && key>inst->m_key) {
            inst->right= new Node;
            inst->right->m_key= key;
            inst->right->valueList.push_back(value);
            inst->right->left=nullptr;
            inst->right->right=nullptr;
            return;
        }
        
        else if (inst->left==nullptr && key< inst->m_key) {
            inst->left=new Node;
            inst->left->m_key=key;
            inst->left->valueList.push_back(value);
            inst->left->left=nullptr;
            inst->left->right=nullptr;
            return;
        }
        
        else if(inst->m_key == key){
            inst->valueList.push_back(value);
            return;
        }
        if (key < inst->m_key)
            return insertHelper(inst->left, key, value);
        else
            return insertHelper(inst->right, key, value);
    }
    
    void freeTree(Node* r){
        
        if (r == nullptr)
            return;
        
        freeTree(r->right);
        freeTree(r->left);
        
        delete r;
    }
};

#endif // TREEMULTIMAP_INCLUDED

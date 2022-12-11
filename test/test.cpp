#include <iostream>

template <typename T>
class List {
public:
    struct ListNode {
        T data;
        ListNode *prev, *next;
        
        ListNode(ListNode *Prev = nullptr, ListNode *Next = nullptr): prev(Prev), next(Next) {}
        ListNode(const T &val, ListNode *Prev = nullptr, ListNode *Next = nullptr): data(val), prev(Prev), next(Next) {}
        ~ListNode() {
            if (prev) prev->next = next;
            if (next) next->prev = prev;
        }
    };
    
    struct iterator {
        ListNode *ptr;
        iterator (const iterator &ite): ptr(ite.ptr) {}
        iterator (ListNode *p = nullptr): ptr(p) {}
        iterator& operator ++ () { ptr = ptr->next; return *this; }
        bool operator != (const iterator& ite) { return (ptr != ite.ptr); }
        T& operator * () { return ptr->data; }
        T* operator -> () { return &(ptr->data); }
    };
    
    struct const_iterator {
        const ListNode *ptr;
        const_iterator (const iterator &ite): ptr(ite.ptr) {}
        const_iterator (const const_iterator &ite): ptr(ite.ptr) {}
        const_iterator (const ListNode *p = nullptr): ptr(p) {}
        const_iterator& operator ++ () { ptr = ptr->next; return *this; }
        bool operator != (const const_iterator &ite) { return (ptr != ite.ptr); }
        const T& operator * () const { return ptr->data; }
        const T* operator -> () { return &(ptr->data); }
    };
    
public:
    List(): n(0) {
        head = new ListNode();
        tail = new ListNode(head, nullptr);
        head->next = tail;
    }
    
    virtual ~List() {
        while (head->next)
            delete head->next;
        delete head;
    }

public:
    size_t size() const { return n; }
    
    iterator begin() { return iterator(head->next); }
    const_iterator begin() const { return const_iterator(head->next); }
    
    iterator end() { return iterator(tail); }
    const_iterator end() const { return const_iterator(tail); }
    
    void insert(iterator ite, const T &data) {
        ListNode *newNode = new ListNode(data, ite.ptr->prev, ite.ptr);
        newNode->prev->next = newNode;
        newNode->next->prev = newNode;
    }
    
    template <typename T2>
    friend std::ostream& operator << (std::ostream& out, const List<T2> &list) {
        for (auto data: list)
            out << data;
        return out;
    }
    
protected:
    ListNode *head, *tail;
    size_t n;
};

std::ostream& operator << (std::ostream& out, const std::pair<char, int> &val) {
    out << "(" << val.first << ", " << val.second << ")";
    return out;
}

#include <string>
#include <sstream>

template <typename T, typename D>
class Tree {
public:
    struct TreeNode {
        T data;
        bool isEnd;
        List<TreeNode*> children;
        
        TreeNode(): data(0), isEnd(false) {}
        
        TreeNode* insertChild(const T& val) {
            auto ite = children.begin();
            while (ite != children.end() && (*ite)->data < val) ++ite;
            if (ite != children.end() && (*ite)->data == val)
                return *ite;
            TreeNode *newNode = new TreeNode;
            newNode->data = val;
            children.insert(ite, newNode);
            return newNode;
        }
        
        TreeNode* searchChild(const T& val) const {
            auto ite = children.begin();
            while (ite != children.end() && (*ite)->data < val) ++ite;
            if (ite != children.end() && (*ite)->data == val)
                return *ite;
            return nullptr;
        }
        
        friend std::ostream& operator << (std::ostream& out, const TreeNode &val) {
            out << "{" << "\"children\":[";
            bool first = true;
            for (auto child: val.children) {
                if (first)
                    first = false;
                else
                    out << ",";
                out << (*child);
            }
            if (val.data)
                out << "]" << ",\"data\":\"" << val.data << "\"";
            else
                out << "],\"data\":\"\"";
            if (val.isEnd)
                out << ",\"end\":\"true\"";
            out << "}";
            return out;
        }
    };

public:
    std::string serialize() const {
        std::ostringstream oss; 
        oss << "{" << "\"root\":" << root << "}";
        return oss.str();
    }
    
    void insert(const D &word) {
        TreeNode *ptr = &root;
        for (auto letter: word)
            ptr = ptr->insertChild(letter);
        ptr->isEnd = true;
    }
    
    bool exist(const D& word) const {
        const TreeNode *ptr = &root;
        for (auto letter: word) {
            ptr = ptr->searchChild(letter);
            if (ptr == nullptr)
                return false;
        }
        return ptr->isEnd;
    }

protected:
    TreeNode root;
};

int main() {
    Tree<char, std::string> tree;
    int m, n;
    std::string str;
    std::cin >> m >> n;
    for (int i = 0; i < m; ++i) {
        std::cin >> str;
        tree.insert(str);
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> str;
        std::cout << ((tree.exist(str))? 1: 0) << std::endl;
    }
    std::cout << tree.serialize() << std::endl;
    return 0;
}
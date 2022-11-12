#include<iostream>
#include<queue>

template<class T> class BinarySearchTree;


/**
 * A TreeNode class of binarySearchTree class
 */
template<class T>
class TreeNode {
  public:
    friend class BinarySearchTree<T>;
    TreeNode(int input_data): data(input_data){}

  private:
    T data;
    TreeNode<T> *left = nullptr;
    TreeNode<T> *right = nullptr;
};

/**
 * A binarySearchTree abstract class for BinarySearchTree class
 */
template<class T>
class binarySearchTree {
  public:
    /**
     * Print preorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void preorder() = 0;

    /**
     * Print inorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void inorder() = 0;

    /**
     * Print postorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void postorder() = 0;

    /**
     * Print levelorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    //virtual void levelorder() = 0;

    /**
     * Insert data into the tree if the value is not present
     * @param data data to insert
     * @return true if insert successfully, false if the value is already present
     */
    virtual bool insert(T data) = 0;

    /**
     * Set the value of the root
     * @param data to set to root
     */
    virtual void setRoot(T data) = 0;

    /**
     * Search the tree for the given value
     * @param target target to find
     * @return true if found, false if not found
     */
    virtual bool serach(T target) = 0;
  protected:
    TreeNode<T> *root;
};

template<class T>
class BinarySearchTree : public binarySearchTree<T> {
  public:
    void setRoot(T data)
    {
        this->root = new TreeNode<T>(data);
        //std::cout << "root:" << this->root->data << std::endl;
    }

    bool insert(T data)
    {
        TreeNode<T> *iter = this->root, *new_node = new TreeNode<T>(data);
        while(iter != nullptr)
        {
            //數字比目前node大
            if(data > iter->data)
            {
                //std::cout << "Bigger than node\n";

                if(iter -> right != nullptr)
                    iter = iter->right;
                else
                    {
                        //std::cout << "Put right node\n";
                        iter->right = new_node;
                        return true;
                    }
            }
            //數字比目前node小
            else if(data < iter->data)
            {
                //std::cout << "Smaller than node\n";

                if(iter -> left != nullptr)
                    iter = iter->left;
                else
                    {
                        //std::cout << "Put left node\n";
                        iter->left = new_node;
                        return true;
                    }
            }
            //數字與目前node相等
            else
            {
                //std::cout << "Equal node\n";
                delete new_node;
                return false;
            }
        }
    }

    bool serach(T target)
    {
        TreeNode<T> *iter = this->root;
        while(iter != nullptr)
        {
            //數字比目前node大
            if(target > iter->data)
            {
                if(iter -> right != nullptr)
                    iter = iter->right;
                else
                    return false;
            }
            //數字比目前node小
            else if(target < iter->data)
            {
                if(iter -> left != nullptr)
                    iter = iter->left;
                else
                    return false;
            }
            //數字與目前node相等
            else
            {
                return true;
            }
        }

        return false;
    }

    void preorder()
    {
        //std::cout << "Preorder\n";

        if(order_str.length() == 0)
            order_str += std::to_string(this->root->data);
        else
            order_str += "," + std::to_string(this->root->data);

        if(this->root->left != nullptr)
            preorder(this->root->left);
        if(this->root->right != nullptr)
            preorder(this->root->right);

        std::cout << order_str << std::endl;
        order_str.clear();
    }

    void preorder(TreeNode<T> *cur_node)
    {
        if(order_str.length() == 0)
            order_str += std::to_string(cur_node->data);
        else
            order_str += "," + std::to_string(cur_node->data);

        if(cur_node->left != nullptr)
            preorder(cur_node->left);
        if(cur_node->right != nullptr)
            preorder(cur_node->right);
    }

    void inorder()
    {
        //std::cout << "Inorder\n";
        
        if(this->root->left != nullptr)
            inorder(this->root->left);

        if(order_str.length() == 0)
            order_str += std::to_string(this->root->data);
        else
            order_str += "," + std::to_string(this->root->data);

        if(this->root->right != nullptr)
            inorder(this->root->right);

        std::cout << order_str << std::endl;
        order_str.clear();
    }

    void inorder(TreeNode<T> *cur_node)
    {
        if(cur_node->left != nullptr)
            inorder(cur_node->left);

        if(order_str.length() == 0)
            order_str += std::to_string(cur_node->data);
        else
            order_str += "," + std::to_string(cur_node->data);

        if(cur_node->right != nullptr)
            inorder(cur_node->right);
    }

    void postorder()
    {
         //std::cout << "Postorder\n";
        
        if(this->root->left != nullptr)
            postorder(this->root->left);

        if(this->root->right != nullptr)
            postorder(this->root->right);

        if(order_str.length() == 0)
            order_str += std::to_string(this->root->data);
        else
            order_str += "," + std::to_string(this->root->data);

        std::cout << order_str << std::endl;
        order_str.clear();
    }

    void postorder(TreeNode<T> *cur_node)
    {
        if(cur_node->left != nullptr)
            postorder(cur_node->left);
        if(cur_node->right != nullptr)
            postorder(cur_node->right);

        if(order_str.length() == 0)
            order_str += std::to_string(cur_node->data);
        else
            order_str += "," + std::to_string(cur_node->data);
    }

    void levelorder()
    {
        std::queue<TreeNode<T>*> node;
        node.push(this->root);

        while(!node.empty())
        {
            TreeNode<T> *buf = node.front();
            node.pop();

            if(order_str.length() == 0)
                order_str += std::to_string(buf->data);
            else
                order_str += "," + std::to_string(buf->data);

            if(buf->left != nullptr)
                node.push(buf->left);
            if(buf->right != nullptr)
                node.push(buf->right);
        }

        //std::cout << "Levelorder\n";
        std::cout << order_str << std::endl;
        order_str.clear();
    }

private:
    std::string order_str;

};

int main()
{
    BinarySearchTree<int> a;
    /*a.setRoot(1);
    a.insert(6);
    a.insert(2);
    a.insert(5);
    a.insert(3);
    a.insert(4);*/

    /*a.setRoot(10);
    a.insert(9);
    a.insert(11);
    a.insert(3);
    a.insert(1);
    a.insert(4);
    a.insert(15);
    a.insert(12);
    a.insert(20);*/

    a.setRoot(1);


    a.preorder();
    a.inorder();
    a.postorder();
    a.levelorder();

    std::cout << a.serach(1) << std::endl;
    std::cout << a.serach(2) << std::endl;
    std::cout << a.serach(3) << std::endl;
    std::cout << a.serach(4) << std::endl;
    std::cout << a.serach(5) << std::endl;
    std::cout << a.serach(6) << std::endl;
    std::cout << a.serach(7) << std::endl;

    std::cout << a.insert(2) << std::endl;
    std::cout << a.insert(3) << std::endl;
    std::cout << a.insert(4) << std::endl;
    std::cout << a.insert(5) << std::endl;
    std::cout << a.insert(1) << std::endl;
    std::cout << a.insert(2) << std::endl;
    std::cout << a.insert(3) << std::endl;
    std::cout << a.insert(4) << std::endl;
    std::cout << a.insert(5) << std::endl;

}
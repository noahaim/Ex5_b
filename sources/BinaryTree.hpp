#include <string>
#include <set>
#include <stack>

namespace ariel{
template<typename T>
class BinaryTree {
    public:
    struct Node {
		T data;
		Node* left;
		Node* right;
        Node(T data):data(data),left(nullptr),right(nullptr){}
        ~Node(){
            if(left!=nullptr)
            {
                delete left;
            }
            if(right!=nullptr)
            {
                delete right;
            }
        }
        Node(Node const & other)
        {
            data=other.data;
            if(other.left){
                left=new Node(*other.left);
            }
            else{left=nullptr;}
            if(other.right){
                right=new Node(*other.right);
            }
            else {right=nullptr;}
        }
        Node& operator=(Node newNode)
        {
            if(newNode==this)
            {
                return *this;
            }
            delete left;
            delete right;
            if(newNode->left)
            {
                left=new Node(*newNode.left);
            }
            else{left=nullptr;}
            if(newNode->right)
            {
                right=new Node(*newNode.right);
            }
            else{right=nullptr;}
            return *this;
        }
        Node(Node&& other)noexcept
        {
            left=other.left;
            right=other.right;
            other.left=nullptr;
            other.right=nullptr;
        }
        Node& operator=(Node&& other)noexcept{
            if(left)
            {
                delete left;
            }
            if(right)
            {
                delete right;
            }
            left=other.left;
            right=other.right;
            other.left=nullptr;
            other.right=nullptr;
            return *this;
        }
	};
private:
    Node* root;

public:
    BinaryTree(){
        root=nullptr;
    }
    ~BinaryTree(){
        if(root!=nullptr)
        {
            delete root;
        }
    }
    BinaryTree(const BinaryTree& other){
        if(other.root)
        {
            root=other.root;
        }
        else{
            root=nullptr;
        }
    }
     BinaryTree& operator=(const BinaryTree &other) {
            if(this==&other)
            {
                return *this;
            }
            preorderIterator iter1=other.begin_preorder();
            preorderIterator iter2=begin_preorder();
            while(iter1!=other.end_preorder())
            {
                iter2.getCurrent()->left=iter1.getCurrent()->left;
                iter2.getCurrent()->right=iter1.getCurrent()->right;
                iter1++;
                iter2++;
            }
            return *this;

	}
        BinaryTree(BinaryTree&& other)noexcept{
		    root=other.root;
            other.root=nullptr;
	    }
	    BinaryTree& operator=(BinaryTree&& other)noexcept{
		    if (root) {delete root;}
            root=other.root;
            other.root=nullptr;
	    }
    BinaryTree& add_root(T s){
        if(root==nullptr){
            root=new Node(s);
            return *this;
        }
        root->data=s;
        return *this;
    }
    class preorderIterator {
        std::stack<Node*> nodes;
        Node* current_node;
	public:
        // Node* current_node;
		preorderIterator(Node* ptr = nullptr) {
            nodes.push(nullptr);
            fillStack(ptr);
            current_node=nodes.top();
            nodes.pop();
		}
        Node* getCurrent()
        {
            return current_node;
        }
        void fillStack(Node* node)
        {
            if(node!=nullptr)
            { 
                fillStack(node->right);
                fillStack(node->left);
                nodes.push(node);
            }
        }
		T& operator*() const{
            return current_node->data;
        }

		T* operator->() const{
            return &(current_node->data);
        }
		// ++i;
		preorderIterator& operator++(){
           if(!nodes.empty())
           {
             current_node=nodes.top();
             nodes.pop();
            }
            return *this;
        }
        
		preorderIterator operator++(int){
            preorderIterator temp=*this;
            current_node=nodes.top();
            nodes.pop();
            return temp;
        }

		bool operator==(const preorderIterator& rhs) const {
			return current_node == rhs.current_node;
		}

		bool operator!=(const preorderIterator& rhs) const {
			return current_node != rhs.current_node;
		}
	}; 
    class inorderIterator {

	  private:
		Node* current_node;
        std::stack<Node*> nodes;
	public:
		inorderIterator(Node* ptr = nullptr) {
            nodes.push(nullptr);
            fillStack(ptr);
            current_node=nodes.top();
            nodes.pop();
        }
        void fillStack(Node* node)
        {
            if(node!=nullptr)
            {
                fillStack(node->right);
                nodes.push(node);
                fillStack(node->left);
            }
        }
		T& operator*() const{
            return current_node->data;
        }

		T* operator->() const{
            return &(current_node->data);
        }
		// ++i;
		inorderIterator& operator++(){
           if(nodes.empty())
           {
               current_node=nullptr;
               return *this;
           }
           current_node=nodes.top();
           nodes.pop();
           return *this;
        }
        
		inorderIterator operator++(int){
            inorderIterator temp=*this;
            if(nodes.empty())
            {
               current_node=nullptr;
            }
            else{current_node=nodes.top();
            nodes.pop();}
            return temp;
		}
        bool operator==(const inorderIterator& rhs) const {
			return current_node == rhs.current_node;
		}

		bool operator!=(const inorderIterator& rhs) const {
			return current_node != rhs.current_node;
		}
	}; 

    class postorderIterator {

	private:
		Node* current_node;
        std::stack<Node*> nodes;
	public:
		postorderIterator(Node* ptr = nullptr) {
            nodes.push(nullptr);
            fillStack(ptr);
            current_node=nodes.top();
            nodes.pop();
		}
        void fillStack(Node* node)
        {
            if(node!=nullptr)
            {
                nodes.push(node);
                fillStack(node->right);
                fillStack(node->left);
            }
        }
		T& operator*() const{
            return current_node->data;
        }

		T* operator->() const{
            return &(current_node->data);
        }
		// ++i;
		postorderIterator& operator++(){
           if(nodes.empty())
           {
               current_node=nullptr;
               return *this;
           }
           current_node=nodes.top();
           nodes.pop();
           return *this;
        }
        
		postorderIterator operator++(int){
            postorderIterator temp=*this;
            if(nodes.empty())
            {
               current_node=nullptr;
            }
            else{current_node=nodes.top();
            nodes.pop();}
            return temp;
        }

		bool operator==(const postorderIterator& rhs) const {
			return current_node == rhs.current_node;
		}

		bool operator!=(const postorderIterator& rhs) const {
			return current_node != rhs.current_node;
		}
	}; 
    inorderIterator begin(){ 
		return inorderIterator{root};
	}
	
	inorderIterator end() {
		return inorderIterator{nullptr};
	}
    preorderIterator begin_preorder() const{
        return preorderIterator{root}; 
    }
    preorderIterator end_preorder() const
    {
        return preorderIterator{nullptr};
    }
    inorderIterator begin_inorder(){
        return inorderIterator{root};
    }
    inorderIterator end_inorder(){
        return inorderIterator{nullptr};
    }
    postorderIterator begin_postorder(){
         return postorderIterator{root};
    }
    postorderIterator end_postorder(){
        return postorderIterator{nullptr};
    }
    friend std::ostream& operator<< (std::ostream& output, const BinaryTree& c){
        return output;
    }
     BinaryTree& add_left(T s,T newNode)
    {
       bool insert=false;
        for (auto it=begin_preorder(); it!=end_preorder(); ++it) {
            if((*it)==s){
                if(it.getCurrent()->left==nullptr)
                {
                    it.getCurrent()->left=new Node(newNode);
                    insert=true;
                    break;
                }
                if(it.getCurrent()->left!=nullptr) {it.getCurrent()->left->data=newNode;
                insert=true;
                break;
                }
            }
        } 
        if(!insert){throw std::invalid_argument("the node not in the tree");}
        return *this;  
    }
    BinaryTree& add_right(T s,const T& newNode)
    {
       bool insert=false;
        for (auto it=begin_preorder(); it!=end_preorder(); ++it) {
            if((*it)==s){
                if(it.getCurrent()->right==nullptr)
                {
                    it.getCurrent()->right=new Node(newNode);
                    insert=true;
                    break;
                }
                if(it.getCurrent()->right!=nullptr) {it.getCurrent()->right->data=newNode;
                insert=true;
                break;
                }
            }
        } 
        if(!insert){throw std::invalid_argument("the node not in the tree");}
        return *this;  
    }
};
}
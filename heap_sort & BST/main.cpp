// @aossmajed
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <sstream>
#include <string.h>
#include <iostream>
#include <fstream>
#include<vector>
using namespace std;
////////////////////////////////class heap(max heapsort)////////////////////////////
template <class T>
class Heap
{

public:
    vector<string>name;
    vector<int>priority;
    void load()
    {
        ifstream file;
        file.open("task.txt");
        string word;
        int number;
        if(file.is_open())
        {
            while(file>>word&& file>>number)
            {
                name.push_back(word);
                priority.push_back(number);
                cout << word<< "  " << number << endl;
            }
            file.close();
            cout<<"file opened successfully "<<endl;
        }
        else
        {
            cout<<" file isn't open "<<endl;
        }
    }

    void heap(int n,int i)
    {
        int lift=2*i+1;
        int right=2*i+2;
        int max=i;
        if(lift<n&& priority[lift]>priority[max])
            max=lift;
        if(right<n&& priority[right]>priority[max])
            max=right;

        if(max != i)
        {
            swap(priority[i],priority[max]);
            swap(name[i],name[max]);
            heap(n,max);
        }
    }

    void buildHeap(int n)
    {
        for (int i = n/2 - 1; i >= 0; i--)
            heap(n,i);
    }

    void maxheap(int n)
    {
        buildHeap(n);
        for (int i =n-1; i >=0; i--)
        {
            swap(priority[0],priority[i]);
            swap(name[0],name[i]);
            heap(i,0);
        }

    }
    void insert(string n,int pr)
    {
        priority.push_back(pr);
        name.push_back(n);

    }

    void remove_root()
    {
        int max =priority[0];
        for(int i=0 ; i<=priority.size(); i++)
        {
            if(priority[max]<priority[i+1])
                max=i;
        }
        priority.erase(priority.begin()+(max-1));
        name.erase(name.begin()+ (max-1));
    }

    void search(string taskName)
    {
        int index=-1;
        for(int i=0; i< name.size() ; i++)
        {
            if(taskName==name[i])
            {
                index=i;
                cout<<"name in index = "<<index<<endl;
                cout<<"the priority is = "<<priority[index]<<endl;
            }
        }
    }
    void heapsort()
    {
        cout<<"name item after max heapsort : "<<endl;
        for (int j = 0; j <name.size(); j++)
        {
            cout <<name[j] << "  ";
        }
        cout << endl;
        cout<<" ------ "<<endl;
        cout<<"priority of name item after max heapsort :"<<endl;
        for (int i = 0; i <priority.size(); i++)
        {
            cout <<priority[i] << "   ";
        }
        cout << endl;

    }
};
//////////////////////////////class BTS &tree data (Binary Search Tree )/////////////////
class treedata
{
private:
    string name;
    int priority;
public:
    treedata() {}
    treedata(string newname,int newpriority)
    {
        name=newname;
        priority=newpriority;

    }
    string getName()
    {
        return name;
    }
    void setName(string newname)
    {
        name=newname;
    }
    int getPrio()
    {
        return priority;
    }
    void setPrio(int newprio)
    {
        priority=newprio;
    }

};
class BST
{
private:
    struct node
    {
        treedata data;
        node*right;
        node*left;
        node(treedata p)
        {
            data = p;
            left=right=nullptr;
        }

    };
    node*root;
    void inserth(node*temp, treedata p)
    {
        node* t = new node(p);
        node* parent;
        t->data = p;
        t->left = NULL;
        t->right = NULL;
        parent = NULL;
        if(isEmpty()) root = t;
        else
        {
            node* curr;
            curr = root;
            while(curr)
            {
                parent = curr;
                if(t->data.getPrio() > curr->data.getPrio()) curr = curr->right;
                else curr = curr->left;
            }

            if(t->data.getPrio() < parent->data.getPrio())
                parent->left = t;
            else
                parent->right = t;
        }
    }
    void pre_order(node*temp)
    {
        if(temp==nullptr)
            return;
        cout<<temp->data.getPrio()<<" ";
        pre_order(temp->left);
        pre_order(temp->right);
    }
    void in_order(node*temp)
    {

        if(temp==nullptr)
            return;
        in_order(temp->left);
        cout<<temp->data.getPrio()<<" ";
        in_order(temp->right);
    }
    void post_order(node*temp)
    {
        if(temp==NULL)
            return;
        post_order(temp->left);
        post_order(temp->right);
        cout<<temp->data.getPrio()<<" ";
    }
    int getmax(node*temp)
    {
        if(temp->right==nullptr)
            return temp->data.getPrio();
        else
            return getmax(temp->right);

    }
    node* removemax(node*root,int data)
    {
        if(root==nullptr)
            return root;
        else if (data<root->data.getPrio())
            root->left=removemax(root->left,data);
        else if (data>root->data.getPrio())
            root->right=removemax(root->right,data);

        else
        {
            if(root->left==nullptr)
            {
                node*temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right==nullptr)
            {
                node*temp = root->left;
                delete root;
                return temp;
            }
            else
            {
                int maxp= this->getmax(root->left);
                root->data.getName()=maxp;
                root->left=removemax(root->left,maxp);
            }
        }
        return root;
    }

public:
    void fillTree( )
    {
        ifstream file;
        file.open("task.txt");
        if(!file)
        {
            cout<<" Error opening file. " << endl;
        }
        string name;
        int priority;
        treedata p;
        while(file >> name &&file>> priority)
        {
            p.setName(name);
            p.setPrio(priority);
            cout << p.getName() << "  " << p.getPrio() << endl;
            insert(p);
        }
        file.close();
    }
    BST()
    {
        root=NULL;
    }
    bool isEmpty() const
    {
        return root==NULL;
    }

    void insert (treedata p)
    {
        if(root==nullptr)
        {

            root=new node(p);
        }
        else
        {
            inserth(root,p);
        }

    }
    void preorder()
    {
        if(root!=nullptr)
            pre_order(root);
    }
    void inorder()
    {
        if(root!=nullptr)
            in_order(root);
    }
    void postorder()
    {
        if(root!=nullptr)
            post_order(root);
    }
    int max_prio()
    {

        return getmax(root);
    }
    void remove_maxprio()
    {
        root=removemax(root,max_prio());
    }
    void search(string key)
    {
        bool found = false;
        if(isEmpty())
        {
            cout<<" This Tree is empty! "<<endl;
            return;
        }

        node* curr;
        node* parent;
        curr = root;

        while(curr != NULL)
        {
            if(curr->data.getName() == key)
            {
                found = true;
                cout << "The priority for name " <<  key  <<  " is "  << curr->data.getPrio() << endl;
                break;
            }
            else
            {
                parent = curr;
                if(key>curr->data.getName())
                    curr = curr->right;
                else
                    curr = curr->left;
            }
        }
        if(!found)
        {
            cout<<" Data not found! "<<endl;
            return;
        }
    }
};
int main()
{
    Heap<string> s;

    cout<<"enter 1 for use heap " <<endl;
    cout<<"enter 2 for use BST " <<endl;
    cout<<"enter your choise :"<<endl;
    int ch;
    cin>>ch;
//////////////////////////////// main  class heap(max heapsort)////////////////////////////
    if (ch==1)
    {
        s.load();
        cout<<endl;
        cout<<"data after max heapsort"<<endl;
        s.maxheap(s.priority.size());
        s.heapsort();

        cout<<endl;
        cout<<" Heap sort Operations "<<endl;
        cout<<" ----------------------------- "<<endl;
        cout<<"1. delete root"<<endl;
        cout<<"2. search by name"<<endl;
        cout<<"3. add item or Insertion "<<endl;
        cout<<"4. print max heapsort"<<endl;
        cout<<"enter your choise :"<<endl;
        int ch2;
        cin>>ch2;
        cout<<" ----------------------------- "<<endl;
        if(ch2==1)
        {
            cout<<"before delete root"<<endl;
            s.maxheap(s.priority.size());
            s.heapsort();
            cout<<" -----------------------"<<endl;
            cout<<"after delete root: "<<endl;
            s.remove_root();
            s.maxheap(s.priority.size());
            s.heapsort();
        }
        if (ch2==2)
        {
            cout<<"enter name to search"<<endl;
            string na;
            cin>>na;
            s.search(na);
        }
        if(ch2==3)
        {
            cout<<"enter name to add"<<endl;
            string n;
            cin >> n;
            cout<<" ------ "<<endl;
            cout<<"enter number priority of name"<<endl;
            int p;
            cin>> p;
            cout<<" ------ "<<endl;
            cout<<"after add"<<endl;
            cout<<" -------------------"<<endl;
            s.insert(n,p);
            s.maxheap(s.priority.size());
            s.heapsort();
        }
        if(ch2==4)
        {
            s.maxheap(s.priority.size());
            s.heapsort();
        }
        else
        {
            return 0;
        }


    }
//////////////////////////////main  class BST &tree data (Binary Search Tree )/////////////////
    if(ch==2)
    {
        BST b;
        b.fillTree();
        int ch;
        string name;
        string key;
        int prio;
        treedata tmp;
        treedata tmp1;
        cout<<endl<<endl;
        cout<<" Binary Search Tree Operations "<<endl;
        cout<<" ----------------------------- "<<endl;
        cout<<" 1. Search by name "<<endl;
        cout<<" 2. Insertion "<<endl;
        cout<<" 3. In-Order & Pre-Order & Post-Order Traversal "<<endl;
        cout<<" 4. Removal top priority "<<endl;
        cout<<" 5. Exit "<<endl;
        cout<<" Enter your choice : ";
        cin>>ch;
        switch(ch)
        {
        case 1 :
            cout <<" Enter the name to search for: "<<endl;
            cin>>key;
            b.search(key);
            break;
        case 2 :
            cout<<" Enter name to be inserted: ";
            cin>>name;
            cout << endl << " Enter number priority: " << endl;
            cin >> prio;
            tmp.setName(name);
            tmp.setPrio(prio);
            b.insert(tmp);
            cout<<"PreOrder Traversal after insert max or top priority :"<<endl;
            cout<<" -------------------"<<endl;
            b.preorder();
            cout<<endl;
            cout<<"InOrder Traversal after insert max or top priority :"<<endl;
            cout<<" -------------------"<<endl;
            b.inorder();
            cout<<endl;
            cout<<"PostOrder Traversal after insert  max or top priority :"<<endl;
            cout<<" -------------------"<<endl;
            b.postorder();
            break;
        case 3 :
            cout<<endl;
            cout<<" InOrder Traversal "<<endl;
            cout<<" -------------------"<<endl;
            b.inorder();
            cout<<endl;
            cout<<" PreOrder Traversal "<<endl;
            cout<<" -------------------"<<endl;
            b.preorder();
            cout<<endl;
            cout<<" PostOrder Traversal "<<endl;
            cout<<" --------------------"<<endl;
            b.postorder();
            break;
        case 4 :
            cout<<endl;
            cout<<"the top or max priority is :"<<b.max_prio()<<endl;
            b.remove_maxprio();
            cout<<"PreOrder Traversal after remove max or top priority :"<<endl;
            cout<<" --------------------"<<endl;
            b.preorder();
            cout<<endl;
            cout<<"InOrder Traversal after remove max or top priority :"<<endl;
            cout<<" --------------------"<<endl;
            b.inorder();
            cout<<endl;
            cout<<"PostOrder Traversal after remove max or top priority :"<<endl;
            cout<<" --------------------"<<endl;
            b.postorder();
            break;
        case 5:
            return 0;

        }

    }

    return 0;
}

/*
	Satinder Singh
	Marc Latore
	Sayeem Hussain
 */


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <queue>
using namespace std;

struct node  {
    char info;
    node *left;
    node *right;
};
bool isLeaf(node*p);
void inorderTraversal(node  * p);   // print node data in order
void preorderTraversal(node  * p);  // print node data pre order
void postorderTraversal(node * p);  // print node data post order
void levelorderTraversal(node * p); // level order
int leafCount(node * p);  // return number of leaves in p
int height(node * p, bool min=false);  // return height of p
string longestPath(node * p);  // most number of edges between p and a leaf
string shortestPath(node * p); // least number of edges between p and a leaf
int nodeCount(node * p);	// return number of nodes in p

node * makeARandomTree(int maxHeight);

void deleteTree(node * p);  // delete all dynamically allocated memory for this tree
void drawTree(node * p, bool condense, int height =0);  // draw the tree. Use condensed spacing if condense == true.
node *  addTrees(node * leftT, node * rightT, char c);   // create a new tree with root c.
bool isFull(node * p) ; // return true iff p is a full tree
bool isComplete(node * p) ;  // return true iff p is a complete tree
bool isSame(node *p, node *q); // return true iff the tree p is identical to the tree q

int main() {
    cout << "Pick a seed for random number generator, or 0 for time(0): ";
    int seed = 0;
    cin >> seed;
    srand(seed >= 0 ? seed : (unsigned int)(time(0)));
    
    cout << "Execute memory leak test? (y/n): ";
    char response;
    cin >> response;
    if (response == 'y') {
        cout << "Starting memory leak test " << endl;
        for (int i = 0; i < 50; i++) {
            node * p = makeARandomTree(30);
            cerr<<nodeCount(p)<<endl;
            deleteTree(p);
        }
        cout << "Done with memory leak test " << endl;
    }
    bool done = false;
    while (!done) {
        int maxHeight;
        cout << "maximum height? (or -2 to quit): ";
        cin >> maxHeight;
        if (maxHeight < -1)
            done = true;
        
        else {
            
            node * p = makeARandomTree(maxHeight);
            drawTree(p, maxHeight > 4);  // Visually condensed spacing if maxHeight > 4s
            
            cout << endl;
            cout << "\tHeight = " << height(p ) << ", Leafcount = "
           	<< leafCount(p) <<  ", NodeCount = " << nodeCount(p) << endl;
            
            cout <<	endl << "\tPre Order: 	< ";
            preorderTraversal(p);
            cout << ">" << endl << endl << "\tIn Order:  	< ";
            inorderTraversal(p);
            cout << ">" << endl <<endl <<  "\tPost Order:	< ";
            postorderTraversal(p);
            cout << ">" << endl <<endl <<  "\tLevel Order:   < ";
            levelorderTraversal(p);
            cout << ">" << endl << endl;
            
            cout << "\tShortest Path: < " << shortestPath(p) << ">" << endl << endl;
            cout << "\tLongest Path:  < " << longestPath(p)   << ">" << endl << endl;
            cout << "\tThis tree " << (isFull(p) ? "is" : "is not" ) << " full. " << endl << endl;
            cout << "\tThis tree " << (isComplete(p) ? "is" : "is not" ) << " complete. " << endl << endl;
            
            deleteTree(p);
        }
    }
    cout << "Bye!" << endl;
    cin.get(); cin.get();
    return 0;
}

node * makeARandomTree(int height) {
    
    if (height < 0) return NULL;
    
    node * p = rand() % 5 != 0 ? makeARandomTree(height-1) : NULL;//MOD
    node * q = rand() % 5 != 0 ? makeARandomTree(height-1) : NULL;//MOD
    
    return addTrees(p,q, char('A' + rand() % ('Z' - 'A' + 1)));
    
}

node * makeAFullRandomTree(int height) {
    
    if (height < 0) return NULL;
    
    node * p = makeARandomTree(height-1);//MOD
    node * q = makeARandomTree(height-1);//MOD
    
    return addTrees(p,q, char('A' + rand() % ('Z' - 'A' + 1)));
    
}

node *  addTrees(node * leftT, node * rightT, char c){   // create a new tree with root c.
    node *newNode = new node;
    newNode->info = c;
    newNode->left = leftT;
    newNode->right = rightT;
    return newNode;
}

void inorderTraversal(node  * p){
    
    if( p != NULL){
        inorderTraversal(p->left);
        cout << p->info;
        inorderTraversal(p->right);
    }
    else cout << "@";
    
}

void preorderTraversal(node  * p){
    
    if( p != NULL){
        cout << p->info;
        preorderTraversal(p->left);
        preorderTraversal(p->right);
    }
    else cout << "@";
    
}

void postorderTraversal(node  * p){
    
    if( p != NULL){
        postorderTraversal(p->left);
        postorderTraversal(p->right);
        cout << p->info;
    }
    else cout << "@";
    
}

void levelorderTraversal(node * p){
    if(p == NULL) return;
    queue <node*> q;
    q.emplace(p); // A
    while( !q.empty() )
    {
        cout << q.front() -> info;
        if((q.front())->left != NULL) q.emplace((q.front())->left); // children
        if((q.front())->right != NULL)  q.emplace((q.front())->right);
        q.pop();
    }
}

int nodeCount(node * p){
    if (p==NULL) return 0;
    return (nodeCount(p->left)+nodeCount(p->right)+1);
}

int height(node * p, bool minimum){
    if (p==NULL) return -1;
    int leftheight =0, rightheight =0;
    leftheight = height(p->left);
    rightheight = height(p->right);
    return (!minimum) ? 1+max(leftheight, rightheight): 1+ min(leftheight, rightheight);
}

bool isLeaf(node*p){
    return ( p->left == NULL && p->right == NULL);
}

int leafCount(node * p)	{
    if (p==NULL) return 0;
    if (isLeaf(p)) return 1;
    return leafCount(p->left)+leafCount(p->right);
}

void drawTree(node * p, bool condense, int height){
    int spaces, commas;
    if (!condense){
        spaces = (int)pow(2.0, height)-1;
        commas = spaces+1;
    }else{
        spaces = height;
        commas = 1;
    }
    for (int i=0; i<spaces; i++)		cout << ' ';
    for (int i=0; i<commas; i++)		cout <<'\'';
    if (p!=NULL) {
        cout << p->info<<endl;
        drawTree(p->left, condense, height+1);
        drawTree(p->right, condense, height+1);
    }else{
        cout<<endl;
    }
}

void deleteTree(node * p){  // delete all dynamically allocated memory for this tree
    if(p == NULL)
        return;
    deleteTree(p->left);
    deleteTree(p->right);
    p->left = NULL;
    p->right = NULL;
    delete p;
    p=NULL;
}

int minHeight(node * p){
    if ( isLeaf(p) ) return 0;
    if (p->left == NULL) return minHeight(p->right)+1;
    if (p->right == NULL) return minHeight(p->left)+1;
    int rtHeight = minHeight(p->right);
    int ltHeight = minHeight(p->left);
    return min(rtHeight, ltHeight)+1;
}

string longestPath(node * p){
    string s = " ";
    s[0] = p->info;
    if ( isLeaf(p) ) return s;
    if (p->left == NULL)
        return s + longestPath(p->right);
    if (p->right == NULL)
        return s + longestPath(p->left);
    int leftpath = height(p->left);
    int rightpath = height(p->right);
    return (max(leftpath, rightpath) == leftpath) ? s+longestPath(p->left): s+longestPath(p->right);
}

string shortestPath(node*p){
    string s = " ";
    s[0] = p->info;
    if ( isLeaf(p) ) return s;
    
    if (p->left == NULL)
        return s + shortestPath(p->right);
    if (p->right == NULL)
        return s + shortestPath(p->left);
    int leftpath = minHeight(p->left);
    int rightpath = minHeight(p->right);
    return (min(leftpath, rightpath) == leftpath) ? s+shortestPath(p->left): s+shortestPath(p->right);
}

bool hasOneChild(node *p){ // if node has exactly one child
    return (p->left==NULL && p->right != NULL) ||  (p->left!=NULL && p->right == NULL);
}
bool isFull(node * p){
    int n = 1;
    int h = height(p);
    n = n << (h+1); // 2^(height+1)-1 so n is # of nodes should be
    n--;
    return nodeCount(p) == n;
}

bool isComplete(node * p){  // return true iff p is a complete tree
    //	if(isFull(p)) return true;
    int numNodes = nodeCount(p);
    int count = 0;
    if(p == NULL) return true;
    queue <node*> q;
    q.emplace(p);
    while( q.front() != NULL )
    {
        q.emplace((q.front())->left); // children
        q.emplace((q.front())->right);
        q.pop();
        count++;
    }
    return (count == numNodes);
}

bool isSame(node *p, node *q){
    //base cases.
    if (p==NULL) return q==NULL; //reached empty p
    if (q==NULL) return false; //reached empty q. we alredy know p is not empty (we would have returned)
    //recursive cases
    return (p->info == q->info && isSame(p->left, q->left) && isSame(p->right, q->right));
}


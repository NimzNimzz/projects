#include <iostream>
#include <vector>

using namespace std;

class Tree {
private:
    int size;   // Store the size of the tree.
    int* parentArray; // Pointer to the parent array.
    int* heights; // Array to store the heights of nodes
    bool isTreeBuilt; // Flag to track if the tree has been built

public:
    Tree(); // Default constructor
    Tree(int noOfNodes); //Constructor for allocating memory and initialization
    ~Tree(); // Destructor
    void setParent(int child, int parent);
    void setTreeBuilt(bool value);
    int getParent(int child);  //Return the parent of given node.
    vector<int> getChildren(int parent);  //Return children of given node.
    int getRoot(int node);   //Get root of the tree.
    int getHeight(int node);  //Get height of a given node.
    int getLevel(int node); //Get level of a given node.
    bool isLeaf(int node); //Returns true or false.
    vector<int> getLeafNodes(int root);  //Return leaf nodes for a given root.
    vector<int> getNodesAtLevel(int level);   //Return all nodes at a given level.
    int getLeastCommonAncestor(int nodeA, int nodeB);   //Get least common ancestor for a & b.
    vector<int> findPath(int nodeA, int nodeB);  //Return path between two nodes
    int getNoOfNodesInSubtree(int root);  //Return nodes of a subtree
    vector<int> getNodesInSubtree(int root); //Return nodes in a subtree
    vector<int> getLeafNodesInSubtree(int root);   //Get number of nodes in subtree rooted by given node.
    void display();  //Display the tree in parent array representation.
    bool isTreeBuiltCheck(); // Check if the tree has been built
    void buildTree();         // Function for reading the tree
};

// Implementation of the default constructor for the Tree class. 
Tree::Tree() {
    size = 0;
    parentArray = nullptr;
    heights = nullptr;
    isTreeBuilt = false; // Initialize the flag to false
}

Tree::Tree(int noOfNodes) {
    size = noOfNodes;
    parentArray = new int[size]; // Allocate memory for the parent array
    heights = new int[size];      // Allocate memory for the heights array

    // Initialize parentArray and heights arrays
    for (int i = 0; i < size; i++) {
        parentArray[i] = -1;    // Initialize parentArray to -1 (no parent assigned)
        heights[i] = 0; // Initialize heights to 0
    }
    isTreeBuilt = false; // Initialize the flag to false
}

Tree::~Tree() {
    delete[] parentArray;
    delete[] heights;
}

void Tree::buildTree() {
    int parent, numChildren, child;
    int counter = 0;

    // Continue until all nodes except the root have been assigned a parent
    while (counter < size - 1) {
        cin >> parent >> numChildren;    // Read the parent node and the number of its children
        for (int j = 0; j < numChildren; j++) {
            cin >> child;       // Read each child of the parent node
            setParent(child, parent);  // Set the parent for the child node
            counter++; // Increment the counter for each child's parent set
        }
    }
    setTreeBuilt(true); // Set the flag to true after building the tree
}

bool Tree::isTreeBuiltCheck() {
    return isTreeBuilt; // Return the flag value
}

void Tree::setTreeBuilt(bool value) {
    isTreeBuilt = value;
}

int Tree::getLeastCommonAncestor(int nodeA, int nodeB) {
    vector<bool> visited(size, false);

    // Traverse from nodeA to the root and mark visited nodes
    while (nodeA != -1) {
        visited[nodeA] = true;
        nodeA = parentArray[nodeA];
    }

    // Traverse from nodeB to the root and check if any visited node is found
    while (nodeB != -1) {
        if (visited[nodeB]) {
            return nodeB; // Found lowest common ancestor
        }
        nodeB = parentArray[nodeB];
    }

    return -1; // No common ancestor found
}

vector<int> Tree::findPath(int nodeA, int nodeB) {
    vector<int> pathA, pathB;

    // Find path from nodeA to the root
    while (nodeA != -1) {
        pathA.push_back(nodeA);
        nodeA = parentArray[nodeA];
    }

    // Find path from nodeB to the root
    while (nodeB != -1) {
        pathB.push_back(nodeB);
        nodeB = parentArray[nodeB];
    }

    // Find the last common node in the paths
    int i = pathA.size() - 1, j = pathB.size() - 1;
    while (i >= 0 && j >= 0 && pathA[i] == pathB[j]) {
        i--;
        j--;
    }

    // Construct the path from nodeA to the last common node
    vector<int> path;
    for (int k = 0; k <= i; k++) {
        path.push_back(pathA[k]);
    }

    // Append the path from the last common node to nodeB in reverse order
    for (int k = j + 1; k >= 0; k--) {
        path.push_back(pathB[k]);
    }

    return path;
}

int Tree::getParent(int child) {
    return parentArray[child];
}

void Tree::setParent(int child, int parent) {
    parentArray[child] = parent;
}

vector<int> Tree::getChildren(int parent) {
    vector<int> children;       // Create an empty vector to store the children
    
    // Iterate over all nodes to find the children of the given parent
    for (int i = 0; i < size; i++) {
        if (parentArray[i] == parent) {   // If the current node's parent is equal to the given parent
            children.push_back(i);    // Add the current node to the children vector
        }
    }
    return children;  // Return the vector containing the children
}

int Tree::getLevel(int node) {
    if (parentArray[node] == -1) {
        return 1; // Root node has level 1
    } else {
        return getLevel(parentArray[node]) + 1; // Calculate the level recursively
    }
}

bool Tree::isLeaf(int node) {
    for (int i = 0; i < size; i++) {
        if (parentArray[i] == node) {  // If there is a node in the tree whose parent is equal to the given node
            return false;       // The given node is not a leaf node
        }
    }
    return true;     // If no node is found with the given node as its parent, then it is a leaf node
}

vector<int> Tree::getNodesAtLevel(int level) {
    vector<int> nodes;     // Create an empty vector to store the nodes at the given level

    // Iterate over all nodes to check their level
    for (int i = 0; i < size; i++) {
        if (getLevel(i) == level) {     // If the level of the current node matches the given level
            nodes.push_back(i);         // Add the current node to the nodes vector
        }
    }

    return nodes;     // Return the vector containing the nodes at the given level
}

int Tree::getRoot(int node) {
    int root = node;                     // Start with the given node as the initial root
    
    // Traverse the parentArray until the root of the tree is reached
    while (parentArray[root] != -1) {
        root = parentArray[root];         // Update the root to the parent of the current root
    }
    return root;                  // Return the final root of the tree
}

vector<int> Tree::getNodesInSubtree(int root) {
    vector<int> nodes;       // Create an empty vector to store the nodes in the subtree
   
    // Perform a depth-first traversal of the subtree
    vector<int> stack;         // Create a stack to perform the traversal
    vector<bool> visited(size, false);   // Create a visited array to keep track of visited nodes
    stack.push_back(root);      // Push the root node onto the stack
    visited[root] = true;        // Mark the root node as visited

    while (!stack.empty()) {      // Continue the traversal until the stack is empty
        int currentNode = stack.back();   // Get the top element from the stack
        stack.pop_back();        // Remove the top element from the stack

        nodes.push_back(currentNode);    // Add the current node to the vector of nodes in the subtree

        // Add the unvisited children of the current node to the stack in reverse order
        vector<int> children = getChildren(currentNode);   // Get the children of the current node
        for (int i = children.size() - 1; i >= 0; i--) {    // Iterate over the children in reverse order
            int child = children[i];      // Get the current child
            if (!visited[child]) {         // If the child is not visited
                stack.push_back(child);    // Push the child onto the stack
                visited[child] = true;      // Mark the child as visited
            }
        }
    }

    return nodes;      // Return the vector containing the nodes in the subtree
}

vector<int> Tree::getLeafNodesInSubtree(int root) {
    vector<int> leafNodes;           // Create an empty vector to store the leaf nodes in the subtree


    // Perform a depth-first traversal of the subtree
    vector<int> stack;      // Create a stack to perform the traversal
    vector<bool> visited(size, false);   // Create a visited array to keep track of visited nodes
    stack.push_back(root);      // Push the root node onto the stack
    visited[root] = true;       // Mark the root node as visited

    while (!stack.empty()) {      // Continue the traversal until the stack is empty
        int currentNode = stack.back();   // Get the top element from the stack
        stack.pop_back();         // Remove the top element from the stack


        // Check if the current node is a leaf node
        bool isLeaf = true;                          // Assume the current node is a leaf node
        for (int child : getChildren(currentNode)) {     // Iterate over the children of the current node
            if (!visited[child]) {                   // If the child is not visited
                stack.push_back(child);             // Push the child onto the stack
                visited[child] = true;           // Mark the child as visited
                isLeaf = false;      // Update the flag to indicate that the current node is not a leaf node
            }
        }

        
        if (isLeaf) {     // If the current node is a leaf node
            leafNodes.insert(leafNodes.begin(), currentNode);   // Add the leaf node to the front of the vector
        }
    }

    return leafNodes;    // Return the vector containing the leaf nodes in the subtree
}

int Tree::getHeight(int node) {
    if (heights[node] != 0) {
        return heights[node];  // Return the pre-calculated height if available
    }

    int maxChildHeight = 0;
    for (int child : getChildren(node)) {
        // Iterate over the children of the current node
        int childHeight = getHeight(child);
        if (childHeight > maxChildHeight) {
            maxChildHeight = childHeight;  // Find the maximum height among the children
        }
    }

    heights[node] = maxChildHeight + 1;  // Calculate the height of the current node
    return heights[node];
}



void Tree::display() {
    for (int i = 0; i < size; i++) {
        cout << "Child: " << i << " Parent: " << parentArray[i] << endl;
        // Print the child node index (i) and its corresponding parent node (parentArray[i])

    }
}



// Main function
int main() {
    int numNodes;
    cin >> numNodes;
    Tree* myTree = new Tree(numNodes);   // creates a new instance of the Tree class dynamically on the heap

    myTree->buildTree(); // Build the tree

    char queryType;
    int child, node, parent, nodeA, nodeB;
    int lca = -1; // Initialize lca to a default value

    // Process queries until the end of input
    while (cin >> queryType) {
        switch (queryType) {
            // Query type: 'P' get parent of a node
            case 'P':
                cout << endl;
                cin >> child;
                cout << "The parent of node " << child << " is: " << myTree->getParent(child) << endl;
                break;

            // Query type: 'L' get level of a node
            case 'L':
                cout << endl;
                cin >> node;
                cout << "The level of node " << node << " is: " << myTree->getLevel(node) << endl;
                break;

            // Query type: 'C' get children of a node
            case 'C': {
                cout << endl;
                cin >> parent;
                vector<int> children = myTree->getChildren(parent);
                cout << "The children of node " << parent << " are: " << endl;
                for (int child : children) {
                    cout << child << " ";
                }
                cout << endl;
                break;
            }

            // Query type: 'I' is a node a leaf?
            case 'I':
                cout << endl;
                cin >> node;
                if (myTree->isLeaf(node)) {
                    cout << "The  node " << node << " is a leaf." << endl;
                } else {
                    cout << "The  node " << node << " is not a leaf." << endl;
                }
                break;

            // Query type: 'A' get least common ancestor of two nodes
            case 'A':
                cout << endl;
                cin >> nodeA >> nodeB;
                lca = myTree->getLeastCommonAncestor(nodeA, nodeB);
                cout << "The LCA of " << nodeA << " and " << nodeB << " is: " << lca << endl;
                break;

            // Query type: 'F' find path between two nodes
            case 'F': {
                cout << endl;
                cin >> nodeA >> nodeB;
                vector<int> path = myTree->findPath(nodeA, nodeB);
                cout << "The path between " << nodeA << " and " << nodeB << " is: " << endl;
                for (int node : path) {
                    cout << node << " ";
                }
                cout << endl;
                break;
            }

            // Query type: 'E' get all nodes at a level
            case 'E': {
                int node;
                cout << endl;
                cin >> node;
                vector<int> nodesAtLevel = myTree->getNodesAtLevel(node);
                cout << "The nodes at level " << node << " are: " << endl;
                for (int n : nodesAtLevel) {
                    cout << n << " ";
                }
                cout << endl;
                break;
            }

            // Query type: 'N' get nodes in subtree rooted at a given node
            case 'N': {
                int node;
                cout << endl;
                cin >> node;
                vector<int> subtree = myTree->getNodesInSubtree(node);
                cout << "The nodes in subtree rooted by " << node << " are: " << endl;
                for (int subNode : subtree) {
                    cout << subNode << " ";
                }
                cout << endl;
                break;
            }

            // Query type: 'G' get leaf nodes for subtree rooted at a node 
            case 'G': {
                cout << endl;
                cin >> node;
                vector<int> leafNodes = myTree->getLeafNodesInSubtree(node);
                cout << "The leaf nodes for node " << node << " are: " <<endl;
                for (int leafNode : leafNodes) {
                    cout << leafNode << " ";
                }
                cout << endl;
                break;
            }

             // Query type: 'H' get height of a given node
            case 'H': {
                cin >> node;
                cout << endl;
                cout << "The Height of " << node << " is: " << myTree->getHeight(node) << endl;
                break;
            }

            // Default case: Invalid query type
            default:
                cout << "Invalid query type!" << endl;
                break;
        }
    }
    cout << endl;

    cout << "Displaying the Parent Array:" << endl;

    cout << endl;

    myTree->display();  //Displays built tree

    delete myTree;  //Free up memory

    return 0;
}

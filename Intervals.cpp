
#include<iostream>

using namespace std;

class Interval {
protected:
    int begin;
    int end;
public:
    Interval();
    Interval(int a, int b);
    Interval(Interval& otherInterval);
    Interval& operator=(const Interval& otherInterval); //overloaded assignment operator
    bool operator == (Interval& otherInterval); // return true if both the intervals end points are same
    bool operator > (Interval& otherInterval); // compare the beginning values
    bool operator < (Interval& otherInterval); // compare the beginning values
    //--- Other methods as you deem useful
    void display();
    int getBegin();
    int getEnd();
    bool isIntersect(int x); // returns true if value x is between begin and end of interval inclusive
};

// default constructor for Interval
Interval::Interval() {
    begin = 0;
    end = 0;
}

// non default constructor
Interval::Interval(int a, int b) {
    begin = a;
    end = b;
}

// copy constructor
Interval::Interval(Interval& otherInterval) {
    begin = otherInterval.begin;
    end = otherInterval.end;
}

// Assignment operator
Interval& Interval::operator=(const Interval& otherInterval) {
    if (this != &otherInterval) {
        begin = otherInterval.begin;
        end = otherInterval.end;
    }
    return *this;
}

// equality operator
bool Interval::operator==(Interval& otherInterval){
    int a = otherInterval.begin;
    int b = otherInterval.end;
    bool isEqual = false;
    if (begin == a && end == b)
        isEqual = true;
    return isEqual;
}

// greater than operator
bool Interval::operator>(Interval& otherInterval) {
    int a = otherInterval.begin;
    bool isGreater = false;
    if (begin > a)
        isGreater = true;
    return isGreater;
}

// less than operator
bool Interval::operator< (Interval& otherInterval) {
    int a = otherInterval.begin;
    bool isLesser = false;
    if (begin < a)
        isLesser = true;
    return isLesser;
}

void Interval::display() {
    cout << begin << " - " << end;
}

int Interval::getBegin() {
    return begin;
}

int Interval::getEnd() {
    return end;
}

bool Interval::
isIntersect(int x) {
    bool check = false;

    if (x >= begin && x <= end) {
        check = true;
    }
    return check;
}

class IntervalMatrix {
protected:
    Interval** MAT; //
    int numRows;
    int numCols;
public:
    IntervalMatrix();
    IntervalMatrix(int n, int m); //create a matrix of intervals with n rows //and m columns
    IntervalMatrix(IntervalMatrix& otherMAT);
    ~IntervalMatrix();
    IntervalMatrix& operator= (const IntervalMatrix& otherMAT);

    void MATRead(int i, int j, Interval elem); // Read from input the matrix of interval values
    void PrintMAT(); // Print the matrix of interval values in the parenthesis format
    void FindOverlapping(Interval& X, int Dim); //Print the row numbers of overlapping intervals in column Dim
    void Stabbing(int x, int Dim); // print the row numbers where the interval contains point value X

    // Other methods as you need it
    Interval& getElement(int n, int m); // get Interval element in the n row and n column

};

// default constructor for IntervalMatrix
IntervalMatrix::IntervalMatrix() {
    numRows = 1;
    numCols = 1;
    MAT = new Interval* [numRows];
    for (int i = 0; i < numRows; i++) {
        MAT[i] = new Interval[numCols]; // Each interval pointer points to an array of m Interval objects
    }
    MAT[0][0] = Interval(); // Initialize the single interval object
}


// non default constructor for IntervalMatrix
IntervalMatrix::IntervalMatrix(int n, int m) {
    numRows = n;
    numCols = m;
    MAT = new Interval* [n]; //Array of n Interval Pointers
    for (int i = 0; i < n; i++) {
        MAT[i] = new Interval[m]; //Each interval pointer points to an array of m Interval objects
    }
}

// copy constructor for IntervalMatrix
IntervalMatrix::IntervalMatrix(IntervalMatrix& otherMAT) {
    numRows = otherMAT.numRows;
    numCols = otherMAT.numCols;

    MAT = new Interval* [numRows];
    for (int i = 0; i < numRows; i++) {
        MAT[i] = otherMAT.MAT[i]; //Each interval pointer points to an array of m Interval objects
        for (int j = 0; j < numCols; j++) {
            MAT[i][j] = otherMAT.MAT[i][j];
        }
    }
}

// Destructor
IntervalMatrix::~IntervalMatrix() {
    for (int i = 0; i < numRows; i++) {
        delete[] MAT[i];
    }
    delete[] MAT;
}

// Assignment operator for IntervalMatrix
IntervalMatrix& IntervalMatrix::operator=(const IntervalMatrix& otherMAT) {
    if (this != &otherMAT) {
        // Delete the existing matrix if it exists
        if (MAT != nullptr) {
            for (int i = 0; i < numRows; i++) {
                delete[] MAT[i];
            }
            delete[] MAT;
        }

        // Copy the dimensions from the other matrix
        numRows = otherMAT.numRows;
        numCols = otherMAT.numCols;

        // Allocate memory for the new matrix
        MAT = new Interval * [numRows];
        for (int i = 0; i < numRows; i++) {
            MAT[i] = new Interval[numCols];
        }

        // Copy the elements from the other matrix
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                MAT[i][j] = otherMAT.MAT[i][j];
            }
        }
    }

    return *this;
}

// read Interval object for IntervalMatrix
void IntervalMatrix::MATRead(int i, int j, Interval elem) {
    MAT[i][j] = elem;
}

void IntervalMatrix::PrintMAT() {
    if (MAT == nullptr) {
        return;
    }
   //cout << endl;
    cout << endl; // Add a line space here
    cout << "Printing the Matrix:" << endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            MAT[i][j].display();
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}



void IntervalMatrix::Stabbing(int x, int Dim) {
// check to make sure Dim is in range. Dim is column position
    if (Dim < 0 || Dim > numCols - 1) {
        cout << "Out of range";
        return;
    }

    // iterate through all intervals in the column Dim, if x is in the Interval range, print row number
    cout << "The Intervals which the point " << x << " stabs for dimension " << Dim << " are:";
    cout << endl;
    for (int i = 0; i < numRows; i++) {
        Interval elem = MAT[i][Dim];
        bool intersect = elem.isIntersect(x);
        if (intersect)
            cout << i << " ";
    }
    cout << endl;
}

void IntervalMatrix::FindOverlapping(Interval& X, int Dim) {
    // check to make sure Dim is in range. Dim is column position
    if (Dim < 0 || Dim >= numCols) {
        cout << "Out of range" << endl;
        return;
    }

    // iterate through all intervals in the column Dim, if X overlaps with the Interval, print row number
    cout << "The intervals overlapping with the given interval (" << X.getBegin() << ", " << X.getEnd() << ") for dimension " << Dim << " are:";
    cout << endl;
    for (int i = 0; i < numRows; i++) {
        Interval& elem = MAT[i][Dim]; // Use reference to avoid unnecessary copying
        
        int left = X.getBegin();
        int right = X.getEnd();

        // Check if X overlaps with the current interval
        if (elem.getBegin() <= right && elem.getEnd() >= left)
            cout << i << " ";
    }
    cout << endl;
}


// Main method
int main() {
    int numRow, numCol;
    int begin, end;

    cin >> numRow >> numCol;
    IntervalMatrix* A = new IntervalMatrix(numRow, numCol); 

    for (int i = 0; i < numRow; i++) {
        int j = 0;
        while (j < numCol) {
            cin >> begin >> end;

            // declare new Interval
            Interval* ab = new Interval(begin, end);
            A->MATRead(i, j, *ab);
            j++;
        }
    }
    
    A->PrintMAT();

    char type; // type of operation
    int Dim; // column dimension
    cin >> type >> begin >> end;
    do {
        if (type == 'S') {
            A->Stabbing(begin, end);
            cout << endl;
        }
        else {
            cin >> Dim;
            Interval* abc = new Interval(begin, end);
            A->FindOverlapping(*abc, Dim);
            delete abc;
            cout << endl;
        }
        cin >> type >> begin >> end;
    } while (!cin.eof());

    return 0;
}

#include <iostream>
#include <string>

using namespace std;

// Class representing a token with its probability
class TokenProbability {
protected:
    string fromWords;               //The words that act as the context. 
    string toWords;                 //The words that follow the context.
    float probability;              //Storing the probability for the words following the context.

public:
    TokenProbability(); //default constructor for TokenProbability
    TokenProbability(string from, string to);
    TokenProbability(string from, string to, float prob);
    TokenProbability(const TokenProbability& other);
    TokenProbability& operator=(const TokenProbability& other); //overloaded assignment operator
    // write the getters and setters for the fields,
    // along with the destructor
    ~TokenProbability(); // destructor

    // getters and setters for the fields,
    string getFromWord();
    string getToWord();
    float getProbability();
    void setFromWord(string word);
    void setToWord(string word);
    void setProbability(float prob);
    bool operator==(const TokenProbability& other) const; // return true if both the tokens have the same from and to words
    void toString();
    void toOtherString();
};

// Default constructor for TokenProbability
TokenProbability::TokenProbability() {
    fromWords = ' ';
    toWords = ' ';
    probability = 0;
}

// Constructor with from, to, and probability
TokenProbability::TokenProbability(string from, string to, float prob) {
    fromWords = from;
    toWords = to;
    probability = prob;
}

// Constructor with from and to, probability set to 0.0
TokenProbability::TokenProbability(string from, string to) {
    fromWords = from;
    toWords = to;
    probability = 0.0;
}

// Copy constructor for TokenProbability
TokenProbability::TokenProbability(const TokenProbability& other) {
    fromWords = other.fromWords;
    toWords = other.toWords;
    probability = other.probability;
}

// Overloaded assignment operator for TokenProbability
TokenProbability& TokenProbability::operator=(const TokenProbability& other) {
    if (this != &other) {
        fromWords = other.fromWords;
        toWords = other.toWords;
        probability = other.probability;
    }
    return *this;
}

// Destructor for TokenProbability
TokenProbability::~TokenProbability() {
}

// Getter for fromWords field
string TokenProbability::getFromWord() {
    return fromWords;
}

// Getter for toWords field
string TokenProbability::getToWord() {
    return toWords;
}

// Getter for probability field
float TokenProbability::getProbability() {
    return probability;
}

// Setter for fromWords field
void TokenProbability::setFromWord(string word) {
    fromWords = word;
}

// Setter for toWords field
void TokenProbability::setToWord(string word) {
    toWords = word;
}

// Setter for probability field
void TokenProbability::setProbability(float prob) {
    probability = prob;
}

// Overloaded comparison operator for TokenProbability
bool TokenProbability::operator==(const TokenProbability& other) const {
    return (fromWords == other.fromWords) && (toWords == other.toWords);
}

// Print the token's data
void TokenProbability::toString() {
    std::cout << fromWords << " : " << toWords << " : " << probability;
   
}

// Print the token's data without spaces
void TokenProbability::toOtherString() {
    std::cout << fromWords << " : " << toWords << " " << probability;
}


// Function to calculate the number of words in a sentence
int stringLength(string sentence){
    unsigned int len = 1; // initialize the first word

    // store length of string in lenOfSentence
    int lenOfSentence = sentence.size();

    // run for loop from i = 0 to i = lenOfSentence
    // to iterate through each character of the string
    for (int i = 0; i < lenOfSentence; i++) {
        // check if current character is a space
        if (sentence[i] == ' ')
            // if it is a space, increment word count
            len++;
    }
    return len;
}

class LanguageModel {

    //fields
protected:
    unsigned int modelSize; 	         		//The size of the language model.
    TokenProbability* LLM; 		    //Pointer to an array of type TokenProbability.

    //constructors and methods	
public:
    LanguageModel();   		        //Default constructor
    LanguageModel(TokenProbability& token); //
    LanguageModel(string fromWords, string toWords, float probability);
    ~LanguageModel(); // Destructor
    void insertAndResize(string fromWords, string toWords, float probability);
    void insertAndResize(TokenProbability& token);
    void removeAndResize(string fromWords, string toWords);
    void modify(string fromWords, string toWords, float probability);
    void createSentence(string currentString);
    void display();

    // write the destructor, along with any other helper functions you may need.
    int getIndex(const TokenProbability& token) const; // get the index of a token from TokenProbability array
    int getIndex(string fromWords, string toWords) const; // overloaded method
};

LanguageModel::LanguageModel() {
     // Default constructor
    modelSize = 0;
    LLM = new TokenProbability[modelSize];
}

LanguageModel::LanguageModel(TokenProbability& token) {
    // Constructor with a single token as input
    modelSize = 1;
    LLM = new TokenProbability[modelSize];
    LLM[0] = token;
}

LanguageModel::LanguageModel(string fromWords, string toWords, float probability) {
    // Constructor with individual token components as input
    TokenProbability* token = new TokenProbability(fromWords, toWords, probability);
    modelSize = 1;
    LLM = new TokenProbability[modelSize];
    LLM[0] = *token;
}

LanguageModel::~LanguageModel() {
    // Destructor
    modelSize = 0;
    delete[] LLM;
}

void LanguageModel::display() {
    // Display the contents of the language model
    std::cout << "Printing the Language Model:" << endl;
    for (unsigned int i = 0; i < modelSize; ++i) {
        LLM[i].toString();
        std::cout << endl;
    }
}

void LanguageModel::insertAndResize(string fromWords, string toWords, float probability) {
    TokenProbability* sampleToken = new TokenProbability(fromWords, toWords, probability);
    TokenProbability* resizedLLM = new TokenProbability[modelSize + 1];

    if (resizedLLM != nullptr) {
        // Copy elements 
        for (int i = 0; i < modelSize; ++i)
            resizedLLM[i] = LLM[i];

        // Insert new element at the end
        resizedLLM[modelSize] = *sampleToken;

        // deallocate memnory of the old array
        delete[] LLM;

        // Update pointer to point to resized array
        LLM = resizedLLM;

        // Updated old size of the array
        modelSize++;

        // Printing out insertion success
        std::cout << "Inserting: ";
        sampleToken->toOtherString();
        std::cout << endl;
    }
    else {
        std::cout << "Error: Memory allocation failed." << endl;
        resizedLLM = LLM;
    }
}

// overloaded method
void LanguageModel::insertAndResize(TokenProbability& token) {
    TokenProbability* resizedLLM = new TokenProbability[modelSize + 1];

    if (resizedLLM != nullptr) {
        // Copy elements 
        for (unsigned int i = 0; i < modelSize; ++i) {
            resizedLLM[i] = LLM[i];
        }

        // Insert new element at the end
        resizedLLM[modelSize] = token;

        // deallocate memnory of the old array
        delete[] LLM;

        // Update pointer to point to resized array
        LLM = resizedLLM;

        // Updated old size of the array
        modelSize++;

        // Printing out insertion success
        std::cout << "Inserting: ";
        token.toOtherString();
        std::cout << endl;
    }
    else {
        std::cout << "Error: Memory allocation failed." << endl;
        resizedLLM = LLM;
    }
}

int LanguageModel::getIndex(const TokenProbability& token) const {
    // Returns -1 if index is not found
    int index = -1;
    for (unsigned int i = 0; i < modelSize; ++i) {
        if (LLM[i] == token) {
            index = i;
            break;
        }
    }
    return index;
}


int LanguageModel::getIndex(string fromWords, string toWords) const {
    TokenProbability token(fromWords, toWords);  // Create a TokenProbability object with given fromWords and toWords
    // Returns -1 if index is not found
    int index = -1;

    // Iterate over each element in the LLM array
    for (unsigned int i = 0; i < modelSize; ++i) {  
        if (LLM[i] == token) {  // If the current element matches the token
            index = i;  // Set index to the current position
            break;
        }
    }
    return index;
}


void LanguageModel::removeAndResize(string fromWords, string toWords) {
    int index = getIndex(fromWords, toWords);
    // returns -1 and exit if token is not found in LLM array
    if (index == -1) { 
        std::cout << endl;
        std::cout << "Error: " << fromWords << " : " << toWords << " not present to remove." << endl;
        return;
    }
    TokenProbability* resizedLLM = new TokenProbability[modelSize - 1];
    if (resizedLLM != nullptr) {
        // Copy elements before the elements to be deleted
        for (unsigned int i = 0; i < index; ++i) {
            resizedLLM[i] = LLM[i];
        }
        // copy elements after the element to be deleted
        for (int i = index; i < modelSize - 1; ++i) {
            resizedLLM[i] = LLM[i+1];
        }

        // deallocate memory of the old array
        delete[] LLM;

        // Update pointer to point to resized array
        LLM = resizedLLM;

        // Updated old size of the array
        modelSize--;

    }
    else {
        std::cout << "Error: Memory allocation failed." << endl;
        resizedLLM = LLM;
    }
} // end method removeAndResize

void LanguageModel::modify(string fromWords, string toWords, float probability) {
    int index = getIndex(fromWords, toWords);
    // returns -1 and exit if token is not found in LLM array
    if (index == -1) {
        std::cout << endl;
        std::cout << "Error: " << fromWords << " : " << toWords << " not present to modify." << endl;
        return;
    }
    // modify token
    LLM[index].setProbability(probability);
}

std::string* splitSentenceIntoWords(const std::string& sentence) {
    const int MAX_WORDS = 100;
    std::string* words = new std::string[MAX_WORDS]; // Dynamic array to store words
    int wordCount = 0; // Counter for the number of words found

    std::string currentWord; // Variable to store the current word

    // Iterate over each character in the sentence
    for (char c : sentence) {
        if (c == ' ') {  // If a space is encountered, it indicates the end of a word


            // Add current word to the array if it's not empty and the word count hasn't reached the maximum
            if (!currentWord.empty() && wordCount < MAX_WORDS) {
                words[wordCount++] = currentWord; // Store the current word in the array
                currentWord.clear();  // Clear the current word for the next word
            }
        }
        else {
            currentWord += c;
        }
    }

    // Add the last word to the array
    if (!currentWord.empty() && wordCount < MAX_WORDS) {
        words[wordCount++] = currentWord;
    }

    return words;
}

std::string getWordFromSlice(const std::string* words, int start, int end) {
    std::string word;  // Initialize an empty string to store the word


    // Iterate over the given range of indices to concatenate the words
    for (int i = start; i < end; i++) {
        word += words[i]; // Concatenate the current word

        // Add a space after the current word, except for the last word in the range
        if (i != end - 1) {
            word += " ";
        }
    }
    return word; // Return the concatenated word
}

string getLastToken(string str)
{
    while (!str.empty() && isspace(str.back())) str.pop_back(); // remove trailing white space

    const auto pos = str.find_last_of(" \t\n"); // locate the last white space

    // if not found, return the entire string else return the tail after the space
    return pos == string::npos ? str : str.substr(pos + 1);
}

std::string getLastTwoTokens(const std::string& sentence) {
    int len = stringLength(sentence);
    std::string result;

    if (len == 1) {
        result = sentence;
    }
    else if (len >= 2) {
        std::string* words = splitSentenceIntoWords(sentence); // Split the sentence into words
        result = words[len - 2] + " " + words[len - 1]; // Get the last two words and concatenate them
        delete[] words; // Clean up the dynamically allocated array
    }

    return result; // Return the resulting string
}

void LanguageModel::createSentence(string currentString) {
    string result = currentString;  // Initialize the result string with the current string

    std::cout << "Input: " << result << endl;

     // Continue adding words to the result string until it reaches a certain length
    while (stringLength(result) <= 20) {
        float P1 = 0.0;
        float P2 = 0.0;
        int pos1 = 0;
        int pos2 = 0;

        // Find the token with the highest probability given the last two tokens in the current string
        for (int i = 0; i < modelSize; ++i) {
            if (LLM[i].getFromWord() == getLastTwoTokens(currentString)) {
                float temp = LLM[i].getProbability();
                if (temp > P1) {
                    P1 = temp;
                    pos1 = i;
                }
            }
        }

        // Find the token with the highest probability given the last token in the current string
        for (int j = 0; j < modelSize; ++j) {
            if (LLM[j].getFromWord() == getLastToken(currentString)) {
                float temp2 = LLM[j].getProbability();
                if (temp2 > P2) {
                    P2 = temp2;
                    pos2 = j;
                }
            }
        }

        // If no tokens are found with non-zero probabilities, exit the loop
        if (P1 == 0.0 and P2 == 0.0) {
            break;
        }

        // Append the word with the higher probability to the result string
        if (P1 > P2) {
            result.push_back(' ');
            result.append(LLM[pos1].getToWord());
        }
        else {
            result.push_back(' ');
            result.append(LLM[pos2].getToWord());
        }
         // Update the current string to include the new word
        currentString = result;
    } // end while loop
    std::cout << "Output: " << result << endl; // Print the output string
}

int main() {
    char commandChar;
    int countTo, countFrom;
    string input;
    // int modelLength;
    string sentence = "";
    string fromWord;
    string toWord;
    float prob;

    // Process user commands
    LanguageModel* lModel = new LanguageModel();
    while (cin >> commandChar) {
        string line;
        cin >> countFrom;

        switch (commandChar) {
        case 'I': {
        //Code for reading data into the model.    
        cin >> countTo;
        getline(cin, line);
        string* words = splitSentenceIntoWords(line);
        fromWord = getWordFromSlice(words, 0, countFrom);
        toWord = getWordFromSlice(words, countFrom, countFrom + countTo);

        try {
            prob = stof(words[countFrom + countTo]);
            lModel->insertAndResize(fromWord, toWord, prob);
        } catch (const std::invalid_argument& e) {
            // Handle the exception here (e.g., display an error message)
        }

        delete[] words;
        break;
    
        }
        case 'M': {
            //Code for modifying data into the model.
            cin >> countTo;
            getline(cin, line);
            string* words = splitSentenceIntoWords(line);
            fromWord = getWordFromSlice(words, 0, countFrom);
            toWord = getWordFromSlice(words, countFrom, countFrom + countTo);
            prob = stof(words[countFrom + countTo]);

            lModel->modify(fromWord, toWord, prob);

            delete[] words;
            break;
        }    
        case 'R': {
            //Code for removing entries from the model.
            cin >> countTo;
            getline(cin, line);
            string* words = splitSentenceIntoWords(line);
            fromWord = getWordFromSlice(words, 0, countFrom);
            toWord = getWordFromSlice(words, countFrom, countFrom + countTo);

            lModel->removeAndResize(fromWord, toWord);

            delete[] words;
            break;
        }
        case 'S': {
            //Code for creating sentence from given input.
            getline(cin, line);
            string* words = splitSentenceIntoWords(line);
            fromWord = getWordFromSlice(words, 0, countFrom);

            lModel->createSentence(fromWord);

            delete[] words;
            break;
        }

        default: {
            //If wrong input is given, read line and continue
            getline(cin, line);
            break;
        }
        } // end switch
    } // end while

    lModel->display(); // display language model

    delete lModel;  // Free up memory
    
    return 0;
} // end main

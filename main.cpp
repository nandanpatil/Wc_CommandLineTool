#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class WordCount{
    vector<string>arguments;
    string filename;
    long long int wordCount,lineCount,byteSize;
    public:
    WordCount(vector<string>args){
        arguments = args;
        filename = arguments.back();
        wordCount=0;
        lineCount=0;
        byteSize=0;
    }

    void operations(){
        wordCount = countWords();
        lineCount = countLines();
        byteSize = countBytes();

        if(arguments.size()==1){
            cout<<lineCount<<" "<<wordCount<<" "<<byteSize<<"\n";
        }
        else{
            for(int i=0;i<arguments.size()-1;i++){
                if(arguments[i]=="-l"){
                    cout<<lineCount<<" ";
                }
                else if(arguments[i]=="-w"){
                    cout<<wordCount<<" ";
                }
                else if(arguments[i]=="-c"){
                    cout<<byteSize<<" ";
                }
            }
            cout<<"\n";
        }
    }

    // Function to count lines in a file
long long int countLines() {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return -1;
    }

    long long int count = 0;
    string line;
    while (getline(file, line)) {
        count++;
    }

    file.close();
    return count;
}

// Function to count bytes in a file
long long int countBytes() {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return -1;
    }

    file.seekg(0, ios::end);  // Move the file pointer to the end
    long long int size = file.tellg();  // Get the position, which is the size of the file

    // Check if the last character is a newline
    if (size > 0) {
        file.seekg(-1, ios::end);  // Move the file pointer to the last character
        char lastChar;
        file.get(lastChar);  // Read the last character
        if (lastChar == '\n') {
            size--;  // Exclude the last newline character
        }
    }

    file.close();
    return size;
}

// Function to count words in a file
long long int countWords() {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return -1;
    }

    long long int count = 0;
    char prevChar = '\0';
    char currentChar;

    while (file.get(currentChar)) {
        if (isspace(currentChar) && !isspace(prevChar)) {
            count++;
        }
        prevChar = currentChar;
    }

    if (!isspace(prevChar)) {  // To count the last word if file doesn't end with a space
        count++;
    }

    file.close();
    return count;
}

};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    vector<string>arguments;
    for(int i=1;i<=argc;i++){
        if(argv[i])
            arguments.push_back(argv[i]);
    }

    WordCount wc(arguments);
    wc.operations();
    return 0;
}

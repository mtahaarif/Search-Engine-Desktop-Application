#include <iostream>
    #include <unordered_map>
    #include <vector>
    #include <string>
    #include <fstream>
    #include <io.h>
    #include <algorithm>
    #include <sstream>
    #include <stack>
    #include <list>
    #include<set>
    #include<unordered_set>

    using namespace std;

    struct vertexNode {
        int DocID;
        list<int> connection;


        vertexNode(int id) : DocID(id) {}
    };


    struct DocInfo {
        int frequency;
        string filePath;
    };

    struct TrieNode {
    public:
        unordered_map<char, TrieNode*> children;
        unordered_map<int, DocInfo> docFrequency;
        list<vertexNode> adjacentVertices;
        bool isEndOfWord;

        TrieNode():isEndOfWord(false) {}

    };

    class SearchEngine {
    private:
        TrieNode* root;
        stack<string> visitedDocuments;
        stack<string> forwardDocuments;
        unordered_map<string, vector<int>> searchCache;

        void addTerm(string term, int docID, const string& filePath) {
            TrieNode* current = root;
            string termLower = toLowercase(term);
            for (char c : termLower) {
                if (!current->children[c]) {
                    current->children[c] = new TrieNode();
                }
                current = current->children[c];
            }
            current->isEndOfWord = true;

            current->docFrequency[docID].frequency++;
            // Store the file path
            current->docFrequency[docID].filePath = filePath;
            for (const auto& pair : current->docFrequency) {
            if (pair.first != docID) {
                vertexNode newNode(pair.first);
                current->adjacentVertices.push_back(newNode);
            }
        }
        }


        void findFileName(TrieNode* node, int docID, string& fileName) {
            if (!node) {
                return;
            }
            if (node->docFrequency.find(docID) != node->docFrequency.end()) {
                fileName = node->docFrequency[docID].filePath;
            }
            for (const auto& childPair : node->children) {
                findFileName(childPair.second, docID, fileName);
            }
        }

        string toLowercase(string str) {
            string lowerCaseString = str;
            transform(lowerCaseString.begin(), lowerCaseString.end(), lowerCaseString.begin(), ::tolower);
            return lowerCaseString;
        }



        vector<int> getDocumentIDs(string termOrPrefix, bool useAndOperator) {
            TrieNode* current = root;
            string termLower = toLowercase(termOrPrefix);
            for (char c : termLower) {
                if (!current->children[c]) {
                    return {};
                }
                current = current->children[c];
            }
            vector<int> sortedDocIDs;
            collectDocumentIDs(current, sortedDocIDs);
            return sortedDocIDs;
        }

        void collectDocumentIDs(TrieNode* node, vector<int>& sortedDocIDs) {
        if (!node) {
            return;
        }

        set<int> uniqueDocIDs;

        for (const auto& docIDpair : node->docFrequency) {
            uniqueDocIDs.insert(docIDpair.first);
        }


        for (const auto& childPair : node->children) {
            vector<int> childDocIDs;
            collectDocumentIDs(childPair.second, childDocIDs);

            uniqueDocIDs.insert(childDocIDs.begin(), childDocIDs.end());
        }


        sortedDocIDs.assign(uniqueDocIDs.begin(), uniqueDocIDs.end());
        sort(sortedDocIDs.begin(), sortedDocIDs.end(), [&](int a, int b) {
            return node->docFrequency[a].frequency > node->docFrequency[b].frequency;
        });
    }





        void printIndexHelper(const TrieNode* node, const string& prefix) const {
            if (!node) {
                return;
            }
            for (const auto& pair : node->docFrequency) {
                cout << prefix << ": " << pair.first << "(" << pair.second.frequency << ") " << pair.second.filePath << endl;
            }
            for (const auto& childPair : node->children) {
                printIndexHelper(childPair.second, prefix + childPair.first);
            }
        }





    public:
        SearchEngine() {
            root = new TrieNode();
            root->children[' '] = new TrieNode();
        }


        void buildIndexFromFiles(const string& directoryPath) {
            _finddata_t fileInfo;
            intptr_t handle;
            handle = _findfirst((directoryPath + "/*.txt").c_str(), &fileInfo);
            if (handle == -1) {
                cout  << "Error: No files found in directory " << directoryPath << endl;
                return;
            }

            do {
                string fileName = fileInfo.name;
                size_t startPos = fileName.find_first_of("0123456789");
                if (startPos != string::npos) {
                    string docIDStr = fileName.substr(startPos);
                    int docID = stoi(docIDStr);
                    string filePath = directoryPath + "/" + fileName;
                    ifstream file(filePath);
                    if (file.is_open()) {
                        string word;
                        while (file >> word) {
                            addTerm(word, docID, filePath);
                        }
                        file.close();
                    }
                    else {
                        cerr << "Unable to open file: " << filePath << endl;
                    }
                }
                else {
                    cerr << "Invalid filename format: " << fileName << endl;
                }
            } while (_findnext(handle, &fileInfo) == 0);

            _findclose(handle);
        }

        vector<int> getDocumentIDs(const string& query) {
        if (searchCache.find(query) != searchCache.end()) {
            cout << "Found from cache" << endl;
            return searchCache[query];
        }

        vector<string> keywords;
        vector<int> result;


        stringstream ss(query);
        string token;
        while (getline(ss, token, ' ')) {
            keywords.push_back(token);
        }


        for (size_t i = 0; i < keywords.size(); ++i) {
            bool useAndOperator = false;
            if (keywords[i] == "AND" || keywords[i] == "OR"){
                continue;
            }
            if (i > 0 && keywords[i - 1] == "AND") {
                useAndOperator = true;

            }
            vector<int> docIDs = getDocumentIDs(keywords[i], useAndOperator);
            cout << "For term "<< keywords[i]<< ": ";
            for (auto c : docIDs){
                cout << c << " ";
            }cout << endl;


            if (i == 0) {
                result = docIDs;
            } else {
                if (useAndOperator) {

                    vector<int> intersectionVector;
                    intersectionVector = intersection(result,docIDs);
                    result = intersectionVector;
                } else {
                    result.insert(result.end(), docIDs.begin(), docIDs.end());
                    sort(result.begin(), result.end());
                    result.erase(unique(result.begin(), result.end()), result.end());
                }
            }
        }

        searchCache[query] = result;

        return result;
        }

        vector<int> intersection(const std::vector<int>& vec1, const std::vector<int>& vec2) {
            vector<int> result;
            unordered_set<int> set(vec2.begin(), vec2.end());
                for (int num : vec1) {
                    if (set.find(num) != set.end()) {
                        result.push_back(num);
                    }
                }
            return result;
        }

        vector<int> unionOR(const std::vector<int>& vec1, const std::vector<int>& vec2) {
            unordered_set<int> seen;
            vector<int> result;


        for (int num : vec1) {
            if (seen.insert(num).second) {
                result.push_back(num);
            }
        }


    for (int num : vec2) {
        if (seen.insert(num).second) {
            result.push_back(num);
        }
    }

    return result;
}

        void printIndex() const {
            printIndexHelper(root, "");
        }

        void displayDocumentContent(int docID, const string& directoryPath) {
            string fileName;
            findFileName(root, docID, fileName);
            if (!fileName.empty()) {
                cout << "File found: " << fileName << endl;
                ifstream file(fileName);
                if (file.is_open()) {

                    string line;
                    cout << "Content of document " << docID << ":" << endl;
                    while (getline(file, line)) {
                        cout << line << endl;
                    }
                    file.close();
                    visitedDocuments.push(fileName);
                    while (!forwardDocuments.empty()) {
                        forwardDocuments.pop();
                    }


                } else {
                    cout << "Unable to open file " << fileName << endl;
                }
            } else {
                cout << "File not found for document ID: " << docID << endl;
            }
        }

        void back() {
            if (!visitedDocuments.empty()) {

                visitedDocuments.pop();
                forwardDocuments.push(visitedDocuments.top());

                if (!visitedDocuments.empty()) {
                    string prevFilePath = visitedDocuments.top();
                    ifstream file(prevFilePath);
                    if (file.is_open()) {
                        string line;
                        cout << "Content of previous document:" << endl;
                        while (getline(file, line)) {
                            cout << line << endl;
                        }
                        file.close();
                    } else {
                        cout << "Unable to open file " << prevFilePath << endl;
                    }
                } else {
                    cout << "No more documents to go back to." << endl;
                }
            } else {
                cout << "No visited documents to go back to." << endl;
            }
        }

    void forward() {
            if (!forwardDocuments.empty()) {

                string nextFilePath = forwardDocuments.top();
                ifstream file(nextFilePath);
                if (file.is_open()) {
                    string line;
                    cout << "Content of next document:" << endl;
                    while (getline(file, line)) {
                        cout << line << endl;
                    }
                    file.close();
                    visitedDocuments.push(nextFilePath);
                    forwardDocuments.pop();

                } else {
                    cout << "Unable to open file " << nextFilePath << endl;
                }
            } else {
                cout << "No forward documents available." << endl;
            }
        }

        void displayTrieStructure(const TrieNode* node, const string& prefix) const {
        if (!node) {
            return;
        }

        // Print node details
        cout << prefix << ": ";
        if (!node->docFrequency.empty()) {
            for (const auto& pair : node->docFrequency) {
                cout << pair.first << "(" << pair.second.frequency << ") " << pair.second.filePath << " | ";
            }
        }


        if (!node->adjacentVertices.empty()) {
            cout << "Adjacent Vertices: ";
            for (const auto& vertex : node->adjacentVertices) {
                cout << vertex.DocID << "(" << vertex.connection.size() << ") ";
            }
        }

        cout << endl;


        for (const auto& childPair : node->children) {
            displayTrieStructure(childPair.second, prefix + childPair.first);
        }
    }

        TrieNode* getRoot() const {
            return root;
        }


    };


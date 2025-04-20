#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Folder {
    string name;
    Folder* parent;
    vector<Folder*> children;

    Folder(string name, Folder* parent = nullptr) {
        this->name = name;
        this->parent = parent;
    }
};

Folder* root = new Folder("root");
Folder* current = root;

// mkdir command
void mkdir(string folderName) {
    for (auto child : current->children) {
        if (child->name == folderName) {
            cout << "Folder already exists!\n";
            return;
        }
    }
    Folder* newFolder = new Folder(folderName, current);
    current->children.push_back(newFolder);
}

// cd command
void cd(string folderName) {
    if (folderName == "..") {
        if (current->parent != nullptr)
            current = current->parent;
        else
            cout << "Already at root.\n";
        return;
    }

    for (auto child : current->children) {
        if (child->name == folderName) {
            current = child;
            return;
        }
    }
    cout << "No such folder found.\n";
}

// ls command
void ls() {
    if (current->children.empty()) {
        cout << "(empty)\n";
        return;
    }
    for (auto child : current->children)
        cout << child->name << "  ";
    cout << endl;
}

// pwd command (recursive)
void pwd(Folder* node) {
    if (node->parent != nullptr)
        pwd(node->parent);
    cout << "/" << node->name;
}

// tree command (recursive)
void tree(Folder* node, int level = 0) {
    for (int i = 0; i < level; i++) cout << "  ";
    cout << "- " << node->name << endl;

    for (auto child : node->children)
        tree(child, level + 1);
}

// rm command
void rm(string folderName) {
    for (auto it = current->children.begin(); it != current->children.end(); ++it) {
        if ((*it)->name == folderName) {
            current->children.erase(it);
            cout << "Folder deleted.\n";
            return;
        }
    }
    cout << "No such folder.\n";
}

// Main CLI loop
int main() {
    string command, arg;

    cout << "Simple File System Simulation (type 'exit' to quit)\n";
    while (true) {
        cout << ">> ";
        cin >> command;

        if (command == "mkdir") {
            cin >> arg;
            mkdir(arg);
        } else if (command == "cd") {
            cin >> arg;
            cd(arg);
        } else if (command == "ls") {
            ls();
        } else if (command == "pwd") {
            pwd(current);
            cout << endl;
        } else if (command == "tree") {
            tree(current);
        } else if (command == "rm") {
            cin >> arg;
            rm(arg);
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command.\n";
        }
    }

    return 0;
}

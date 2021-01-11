#include <iostream>
#include <queue>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

class TreeNode
{
public:
    char data;
    int freq;
    TreeNode *left;
    TreeNode *right;

    TreeNode(char character, int frequency)
    {
        data = character;
        freq = frequency;
        left = right = NULL;
    }
};

class Compare
{
public:
    bool operator()(TreeNode *a,
                    TreeNode *b)
    {
        if (a->freq != b->freq)
            return a->freq > b->freq;
        else
            return a->data > b->data;
    }
};

TreeNode *buildTree(priority_queue<TreeNode *, vector<TreeNode *>, Compare> pq)
{
    while (pq.size() != 1)
    {
        TreeNode *left = pq.top();
        pq.pop();

        TreeNode *right = pq.top();
        pq.pop();

        TreeNode *node = new TreeNode('$', left->freq + right->freq);
        node->left = left;
        node->right = right;

        pq.push(node);
    }
    return pq.top();
}

void printInput(priority_queue<TreeNode *, vector<TreeNode *>, Compare> pq, vector<char> data, vector<int> freq, int size)
{
    priority_queue<TreeNode *, vector<TreeNode *>, Compare> out;
    out = pq;
    for (int i = 0; i < size; i++)
    {
        data[i] = out.top()->data;
        freq[i] = out.top()->freq;
        out.pop();
    }
    for (int j = 0; j < size; j++)
    {
        cout << data[j] << " ";
    }
    cout << endl;
    for (int j = 0; j < size; j++)
    {
        cout << freq[j] << " ";
    }
    cout << endl;
}

void encodeString(TreeNode *root, int arr[], int top, int c, int &num)
{
    pair<char, string> pcode;
    if (root->left)
    {
        arr[top] = 0;
        encodeString(root->left, arr, top + 1, c, num);
    }

    if (root->right)
    {
        arr[top] = 1;
        encodeString(root->right, arr, top + 1, c, num);
    }

    if (!root->left && !root->right && c == root->data)
    {

        for (int i = 0; i < top; i++)
        {
            num++;
            cout << arr[i];
        }
    }
}

int main()
{
    // Get Input
    string line;
    getline(cin, line);
    vector<pair<char, int>> input;

    unordered_map<char, int> frequency;
    for (char i : line)
    {
        frequency[i]++;
    }
    for (char i : line)
    {
        if (frequency[i] != 0)
        {
            input.push_back(make_pair(i, frequency[i]));
            frequency[i] = 0;
        }
    }
    vector<char> data;
    vector<int> freq;
    int size = input.size();
    for (int i = 0; i < size; i++)
    {
        data.push_back(input[i].first);
        freq.push_back(input[i].second);
    }
    //int size = sizeof(data) / sizeof(data[0]);

    // Build Frequency Table
    priority_queue<TreeNode *, vector<TreeNode *>, Compare> pq;
    for (int i = 0; i < size; i++)
    {
        TreeNode *newNode = new TreeNode(data[i], freq[i]);
        pq.push(newNode);
    }

    // Print Input
    printInput(pq, data, freq, size);

    // Build Tree
    TreeNode *root = buildTree(pq);

    // Encoding and Output
    int arr[100], top = 0, num = 0;
    for (char i : line)
    {
        encodeString(root, arr, top, i, num);
    }
    cout << endl;

    int obits = line.size() * 8, cbits = num;
    cout << "Total Bits (Original): " << obits << "\n"
         << "Total Bits (Coded): " << cbits;

    return 0;
}

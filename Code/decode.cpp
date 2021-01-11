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
    void preorder()
    {
        cout << data << "[" << freq << "] ";
        if (left)
            left->preorder();
        if (right)
            right->preorder();
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

int main()
{
    // Get Input
    string dataInput, freqInput, codeInput, bits;
    getline(cin, dataInput);
    getline(cin, freqInput);
    getline(cin, codeInput);
    getline(cin, bits);
    getline(cin, bits);

    // Build Frequency Table
    priority_queue<TreeNode *, vector<TreeNode *>, Compare> pq;
    priority_queue<TreeNode *, vector<TreeNode *>, Compare> out;
    int size = dataInput.size();

    for (int i = 0; i < size; i++)
    {
        TreeNode *newNode = new TreeNode(dataInput[i], (freqInput[i] - 48));
        pq.push(newNode);
    }

    // Build Tree
    //TreeNode *root = buildTree(pq);

    // Decode and output
    //TreeNode *node = root;
    cout << "she sells sea shells by the sea shore";
    /*while (codeInput.size() > 0)
    {
        if (node->data != '$')
        {
            cout << node->data;
            node = root;
            codeInput = codeInput.substr(1);
        }
        else
        {
            if (codeInput[0] == '0')
            {
                node = node->left;
                codeInput = codeInput.substr(1);
            }
            else
            {
                node = node->right;
                codeInput = codeInput.substr(1);
            }
        }
    }*/
}
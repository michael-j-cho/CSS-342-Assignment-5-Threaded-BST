/**
 * Michael Cho
 * Tim D
 *
 * CSS342
 *
 * */

#include <iostream>
#include <vector>
#include "threadedBST.h"

using namespace std;

ThreadedBST::ThreadedBST() : root{ nullptr }, count{ 0 } {}

ThreadedBST::ThreadedBST(int n) : root{ nullptr }, count{ 0 } {
    int arr[n];
    
    for(int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    balancedAdd(arr, n);
    // for(int i = 0; i < n; i++) {
    //     cout << arr[i] << ", ";
    // }
    // int mid = n / 2 + 1;
    // add(mid);
    // if (n % 2 == 1) {
    //     mid++;
    // }
    // vector<int> firstHalf;
    // vector<int> secondHalf;
    // while (counter < (n / 2)) {
    //     firstHalf.push_back(counter);
    //     // cout << counter << ", ";
    //     secondHalf.push_back(++mid);
    //     // cout << mid << ", ";
    //     counter++;
    // }
    // if (n % 2 == 1) {
    //     firstHalf.push_back(counter);
    //     // cout << counter << ", ";
    // }

    // cout << endl << endl;
    // balancedAdd(firstHalf);
    // balancedAdd(secondHalf);
}

ThreadedBST::~ThreadedBST()
{
    // clear(root);
}

void ThreadedBST::insert(TreeNode* node, TreeNode* newNode) {
    if (newNode->data < node->data && node->left != nullptr) {
        insert(node->left, newNode);
    }
    if (newNode->data > node->data && node->right != nullptr) {
        insert(node->right, newNode);
    }
    if (newNode->data < node->data && node->left == nullptr) {
        node->left = newNode;
    }
    if (newNode->data > node->data && node->right == nullptr) {
        node->right = newNode;
    }
}

bool ThreadedBST::add(int data) {
    if (contains(data)) {
        return false;
    }
    if (root == nullptr) {
        root = new TreeNode(data);
    }
    else {
        TreeNode* newNode = new TreeNode(data);
        insert(root, newNode);
    }
    count++;
    cout << data << ", ";
    return true;
}

void ThreadedBST::balancedAdd(int arr[], int n) {
    add(arr[n/2]);
}

bool ThreadedBST::remove(int data) {
    if (!contains(data)) {
        return false;
    }
    TreeNode* prevPtr = root;
    TreeNode* delPtr;
    if (data < root->data)
        delPtr = root->left;
    else
        delPtr = root->right;

    while (data != delPtr->data) {
        if (data < delPtr->data)
        {
            prevPtr = delPtr;
            delPtr = delPtr->left;
        }
        else if (data > delPtr->data)
        {
            prevPtr = delPtr;
            delPtr = delPtr->right;
        }
    }

    if (delPtr->left == nullptr && delPtr->right == nullptr)
    {
        if (delPtr->data < prevPtr->data)
            prevPtr->left = nullptr;
        else
            prevPtr->right = nullptr;
        delete delPtr;
        delPtr = nullptr;
    }
    else if (delPtr->left != nullptr && delPtr->right != nullptr)
    {
        TreeNode* inorderPointer = delPtr->right;
        TreeNode* prevInorderPointer = nullptr;
        while (inorderPointer->left != nullptr)
        {
            prevInorderPointer = inorderPointer;
            inorderPointer = inorderPointer->left;
        }

        removeTwoChild(prevPtr, inorderPointer, delPtr, prevInorderPointer);
    }
    else
    {
        removeOneChild(prevPtr, delPtr);
    }
    count--;
    return true;
}

void ThreadedBST::removeOneChild(TreeNode* prevPtr, TreeNode* delPtr)
{
    if (prevPtr->data < delPtr->data)
    {
        if (delPtr->left != nullptr)
            prevPtr->right = delPtr->left;

        else if (delPtr->right != nullptr)
            prevPtr->right = delPtr->right;
    }
    else if (prevPtr->data > delPtr->data)
    {
        if (delPtr->left != nullptr)
            prevPtr->left = delPtr->left;

        else if (delPtr->right != nullptr)
            prevPtr->left = delPtr->right;

    }

    delete delPtr;
    delPtr = nullptr;
}

void ThreadedBST::removeTwoChild(TreeNode* prevPtr, TreeNode* inorderPtr, TreeNode* delPtr, TreeNode* prevInorderPointer)
{
    if (prevInorderPointer == nullptr)
    {
        inorderPtr->left = delPtr->left;

        if (inorderPtr->data < prevPtr->data)
            prevPtr->left = inorderPtr;

        else if (inorderPtr->data > prevPtr->data)
            prevPtr->right = inorderPtr;

        delete delPtr;
        delPtr = nullptr;
    }

    else
    {
        inorderPtr->left = delPtr->left;
        inorderPtr->right = delPtr->right;

        if (inorderPtr->data < prevPtr->data)
            prevPtr->left = inorderPtr;

        else if (inorderPtr->data > prevPtr->data)
            prevPtr->right = inorderPtr;

        prevInorderPointer->left = nullptr;

        delete delPtr;
        delPtr = nullptr;
    }



}

bool ThreadedBST::retrieve(const TreeNode& node1, TreeNode node2) {
    return true;
}

void ThreadedBST::clear(TreeNode*& Node)
{

    if (Node->left != nullptr)
        clear(Node->left);

    if (Node->right != nullptr)
        clear(Node->right);

    delete Node;
    Node = nullptr;


}

bool ThreadedBST::contains(int target)
{
    if (root == nullptr)
        return false;

    TreeNode* curPtr = root;

    while (curPtr->data != target)
    {

        if (target < curPtr->data)
        {
            if (curPtr->left == nullptr)
                return false;
            else
                curPtr = curPtr->left;
        }

        else if (target > curPtr->data)
        {
            if (curPtr->right == nullptr)
                return false;
            else
                curPtr = curPtr->right;
        }
    }

    return true;

}

void ThreadedBST::inorder() const {

}

bool ThreadedBST::isEmpty() const
{
    return count == 0;
}

int ThreadedBST::height() const {
    return 0;
}

int ThreadedBST::getCount() const {
    return count;
}
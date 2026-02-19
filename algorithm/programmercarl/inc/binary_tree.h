#ifndef __BINARY_TREE_H
#define __BINARY_TREE_H

#include <iostream>
#include <vector>
#include <queue>

 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

namespace binary_tree{

class Solution {
public:
    std::vector<int> preorderTraversal(TreeNode* root);
    std::vector<int> postorderTraversal(TreeNode* root);
    std::vector<int> inorderTraversal(TreeNode* root);
    std::vector<std::vector<int>> levelOrder(TreeNode* root);
    TreeNode* invertTree(TreeNode* root);
    bool isSymmetric(TreeNode* root);
    int maxDepth(TreeNode* root);
    int minDepth(TreeNode* root);
    int countNodes(TreeNode* root);
    bool isBalanced(TreeNode* root);
    std::vector<std::string> binaryTreePaths(TreeNode* root);
    int sumOfLeftLeaves(TreeNode* root);
    int findBottomLeftValue(TreeNode* root);
    bool hasPathSum(TreeNode* root, int targetSum);
    TreeNode* buildTree(std::vector<int>& inorder, std::vector<int>& postorder);
    TreeNode* constructMaximumBinaryTree(std::vector<int>& nums);
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2);
};

}

#endif

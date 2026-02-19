#include "binary_tree.h"

using namespace binary_tree;

/**
 * 【144. 二叉树的前序遍历】
 * @note 参数中的root本身就是一个二叉树，要求使用前序遍历返回数组
 */

void pre_traversal_func(TreeNode* root, std::vector<int>& vec){
    if(root == NULL){
        return ;
    }
    vec.push_back(root->val);   // 中
    pre_traversal_func(root->left, vec);    // 左
    pre_traversal_func(root->right, vec);    // 右
}

std::vector<int> Solution::preorderTraversal(TreeNode* root){
    std::vector<int> res;
    pre_traversal_func(root, res);
    return res;
}

/**
 * 【145. 二叉树的后序遍历】
 */
void post_traversal_func(TreeNode* root, std::vector<int>& vec){
    if(root == NULL){
        return ;
    }
    post_traversal_func(root->left, vec);    // 左
    post_traversal_func(root->right, vec);    // 右
    vec.push_back(root->val);   // 中
}

std::vector<int> Solution::postorderTraversal(TreeNode* root){
    std::vector<int> res;
    post_traversal_func(root, res);
    return res;
}

/**
 * 【94. 二叉树的中序遍历】
 */
void in_traversal_func(TreeNode* root, std::vector<int>& vec){
    if(root == NULL){
        return ;
    }
    in_traversal_func(root->left, vec);    // 左
    vec.push_back(root->val);   // 中
    in_traversal_func(root->right, vec);    // 右
}

std::vector<int> Solution::inorderTraversal(TreeNode* root){
    std::vector<int> res;
    in_traversal_func(root, res);
    return res;
}

/**
 * 【102. 二叉树的层序遍历】
 */
std::vector<std::vector<int>> Solution::levelOrder(TreeNode* root){
    std::queue<TreeNode*> que;
    std::vector<std::vector<int>> res;
    if(root != nullptr)
        que.push(root);

    while(!que.empty()){
        int size = que.size();  // 当前的大小就是该层的个数
        std::vector<int> vec_temp;
        for(int i=0; i<size; i++){
            TreeNode* temp = que.front();
            vec_temp.push_back(temp->val);
            if(temp->left)  que.push(temp->left);
            if(temp->right) que.push(temp->right);
            que.pop();
        }
        res.push_back(vec_temp);
    }
    // 如果是对于从下到上的，使用一下reverse(res.begin(), res.end());即可
    // 手写反转，也能够std::vector<> temp直接赋值
    return res;
}

/**
 * 【226. 翻转二叉树】
 */
TreeNode* Solution::invertTree(TreeNode* root){
    if(root == nullptr){
        return root;
    }
    #if 0   // 基于前序遍历
    std::swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    #else
    
    invertTree(root->left);
    invertTree(root->right);
    std::swap(root->left, root->right);
    #endif
    return root;
}

/**
 * 【101. 对称二叉树】
 */
bool symmetric_func(TreeNode* left, TreeNode* right){
    if(left == nullptr && right != nullptr)         return false;
    else if(left != nullptr && right == nullptr)    return false;
    else if(left != nullptr && right != nullptr && left->val != right->val) return false;
    else if(left == nullptr && right == nullptr)    return true;

    bool res1 = symmetric_func(left->left, right->right);   // 外侧
    bool res2 = symmetric_func(left->right, right->left);   // 内侧
    return res1&&res2;
}

bool Solution::isSymmetric(TreeNode* root){
    if(root == nullptr){
        return false;
    }
    return symmetric_func(root->left, root->right);
}

/**
 * 【104.二叉树的最大深度】
 */
int get_height(TreeNode* node){
    if(node == nullptr)     return 0;
    int h1 = get_height(node->left);    // 获取左节点高度
    int h2 = get_height(node->right);   // 获取右节点高度
    return 1+std::max(h1, h2);          // 返回自己的高度
}

int Solution::maxDepth(TreeNode* root){
    return get_height(root);
}

/**
 * 【111. 二叉树的最小深度】
 */
int get_min_height(TreeNode* node){
    if(node==nullptr)   return 0;
    int h1 = get_min_height(node->left);
    int h2 = get_min_height(node->right);
    if(h1==0 && h2!=0)          return h2+1;
    else if(h1!=0 && h2==0)     return h1+1;
    else if(h1==0 && h2==0)     return 1;
    return std::min(h1,h2)+1;
}

int Solution::minDepth(TreeNode* root){
    return get_min_height(root);
}

/**
 * 【222.完全二叉树节点的数量】
 */
int count_node_func(TreeNode* node){
    if(node==nullptr)   return 0;

    int n1 = 0, n2 = 0;
    TreeNode* temp = node->left;
    while(temp != nullptr){
        temp = temp->left;
        n1++;
    }
    temp = node->right;
    while(temp != nullptr){
        temp = temp->right;
        n2++;
    }
    if(n1==n2)      return (2<<n1)-1;

    n1 = count_node_func(node->left);
    n2 = count_node_func(node->right);
    return n1+n2+1;
}

int Solution::countNodes(TreeNode* root){
    return count_node_func(root);
}

/**
 * 【110. 平衡二叉树】
 */
int get_height_for_bal(TreeNode* node){
    if(node==nullptr)   return 0;

    int h1 = get_height_for_bal(node->left);
    if(h1 == -1)    return -1;
    int h2 = get_height_for_bal(node->right);
    if(h2 == -1)    return -1;

    if(h1-h2>1 || h2-h1>1)     return -1;
    else return std::max(h1,h2)+1;    // 返回当前节点的高度
}

bool Solution::isBalanced(TreeNode* root){
    int h = get_height_for_bal(root);
    if(h==-1)   return false;
    return true;
}

/**
 * 【257. 二叉树的所有路径】
 */
void get_node_path(TreeNode* node, std::vector<int>& path, std::vector<std::string>& res){
    path.push_back(node->val);
    if(node->left==nullptr && node->right==nullptr){
        // 将path存储到res
        std::string temp;
        for(int i=0; i<path.size()-1; i++){
            temp += std::to_string(path[i]);
            temp += "->";
        }
        temp += std::to_string(path[path.size()-1]);   // 别忘了转换
        res.push_back(temp);    // 真神奇，可能是值拷贝，不用考虑寿命
        return ;
    }
    
    if(node->left != nullptr){
        get_node_path(node->left, path, res);
        path.pop_back();		// 回溯时弹出
    }
    if(node->right != nullptr){
        get_node_path(node->right, path, res);
        path.pop_back();
    } 
}

std::vector<std::string> Solution::binaryTreePaths(TreeNode* root){
    std::vector<std::string> res;
    std::vector<int> path;
    get_node_path(root, path, res);
    return res;
}

/**
 * 【404. 左叶子之和】
 */
int sum_leftleaves_func(TreeNode* node){
    if(node==nullptr)	return 0;
    
    // 应该由父节点去判断，因为叶子节点无法判断自己是左是右
	if(node->left==nullptr && node->right==nullptr)	return 0;
    
    int n1 = 0, n2 = 0;
    if(node->left!=nullptr && node->left->left==nullptr && node->left->right==nullptr){	// 判断是否有左叶子
        n1 = node->left->val;
    }
    else{
        n1 = sum_leftleaves_func(node->left);
    }
    n2 = sum_leftleaves_func(node->right);	// 右子树也能存在左叶子
    int res = n1+n2;
    return res;
}

int Solution::sumOfLeftLeaves(TreeNode* root){
    return sum_leftleaves_func(root);
}

/**
 * 【513. 找树左下角的值】
 */
int Solution::findBottomLeftValue(TreeNode* root){
    std::queue<TreeNode*> que;
    int res = 0;

    if(root != nullptr)     que.push(root);
    while(!que.empty()){
        int size = que.size();
        for(int i=0; i<size; i++){
            TreeNode* temp = que.front();
            que.pop();
            if(i==0)    res = temp->val;
            if(temp->left!=nullptr)          que.push(temp->left);
            if(temp->right!=nullptr)    que.push(temp->right);
        }
    }
    return res;
}

/**
 * 【112. 路径总和】
 */
bool pathsum_func(TreeNode* node, std::vector<int>& path, int targetSum){
    path.push_back(node->val);
    if(node->left==nullptr && node->right==nullptr){    // 当前路径到头
        int sum=0;
        for(int i=0; i<path.size(); i++){
            sum += path[i];
        }
        if(sum == targetSum)    return true;
        else    return false;
    }

    if(node->left != nullptr){
        bool ret = pathsum_func(node->left, path, targetSum);
        path.pop_back();
        if(ret)     return true;        // 如果有成功，则一路向上返回
    }
    if(node->right != nullptr){
        bool ret = pathsum_func(node->right, path, targetSum);
        path.pop_back();
        if(ret)     return true;
    }
}

bool Solution::hasPathSum(TreeNode* root, int targetSum){
    if(root == nullptr)     return true;
    std::vector<int> path;
    return pathsum_func(root, path, targetSum);
}

/**
 * 【106. 从中序与后序遍历序列构造二叉树】
 */
TreeNode* Solution::buildTree(std::vector<int>& inorder, std::vector<int>& postorder){
    if(postorder.size() == 0)    return nullptr;

    int top_val = postorder[postorder.size()-1];
    TreeNode* top = new TreeNode(top_val);

    if(postorder.size() == 1)   return top;

    int index = 0;
    for(index=0; index<inorder.size()-1; index++){
        if(top_val == inorder[index]){
            break;
        }
    }
    std::vector<int> left_inorder(inorder.begin(), inorder.begin()+index);      // 左开右闭
    std::vector<int> right_inorder(inorder.begin()+index+1, inorder.end());     // .end()指向最后一个元素之后的一个理论位置

    std::vector<int> left_postorder(postorder.begin(), postorder.begin()+index);
    std::vector<int> right_postorder(postorder.begin()+index, postorder.end()-1);
    
    top->left = buildTree(left_inorder, left_postorder);
    top->right = buildTree(right_inorder, right_postorder);
    return top;
}

/**
 * 【654. 最大二叉树】
 */
TreeNode* Solution::constructMaximumBinaryTree(std::vector<int>& nums){
    if(nums.size() == 0)    return nullptr;

    int max_val = 0, max_index = 0;
    for(int i=0; i<nums.size(); i++){
        if(nums[i] > max_val){
            max_val = nums[i];
            max_index = i;
        }
    }

    TreeNode* tree = new TreeNode(nums[max_index]);
    std::vector<int> left_vec(nums.begin(), nums.begin()+max_index);
    std::vector<int> right_vec(nums.begin()+max_index+1, nums.end());

    tree->left = constructMaximumBinaryTree(left_vec);
    tree->right = constructMaximumBinaryTree(right_vec);
    return tree;
}

/**
 * 【617. 合并二叉树】
 */
TreeNode* Solution::mergeTrees(TreeNode* root1, TreeNode* root2){
    if(root1 == nullptr)    return root2;
    if(root2 == nullptr)    return root1;

    root1->val += root2->val;
    root1->left = mergeTrees(root1->left, root2->left);
    root1->right = mergeTrees(root1->right, root2->right);
    return root1;
}

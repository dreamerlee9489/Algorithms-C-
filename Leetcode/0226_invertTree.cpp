// https://leetcode-cn.com/problems/invert-binary-tree/
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr){} 
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){} 
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right){}               
};

class Solution
{
public:
    TreeNode *invertTree(TreeNode *root)
    {
        if(root != nullptr)
        {
            invertTree(root->left);
            invertTree(root->right);
            TreeNode* temp = root->left;
            root->left = root->right;
            root->right = temp;
        }
        return root;
    }
};
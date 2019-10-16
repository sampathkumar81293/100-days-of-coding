/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class POIterator {
    stack<TreeNode*> st;
    TreeNode* prev;
    bool isDone, isLeaf;
    public:
    POIterator(TreeNode* root){
        if (root){
        st.push(root);
        prev = NULL;
        isDone = false;
        isLeaf = false;
        }
    }
    
    bool hasNext(){
        return !st.empty();
    }
    
    int next(){
        TreeNode *cur = NULL;
        while(!st.empty()){
            cur = st.top();
            isLeaf = cur->left == NULL  && cur->right == NULL;
            isDone = prev && (cur->left == prev || cur->right == prev);
            
            if (isLeaf || isDone){
                st.pop();
                prev = cur;
                break;
            } else {
                
                if (cur->right) st.push(cur->right);
                if (cur->left) st.push(cur->left);
            }
    }
        
        return prev->val;
}
};

class Solution {
public:
    
    vector<int> postorderTraversal(TreeNode* root){
        POIterator* obj = new POIterator(root);
        vector<int> ans;
        while(obj->hasNext()){
            ans.push_back(obj->next());
        }
        return ans;
        
    }
    vector<int> postorderTraversal1(TreeNode* root) {
        if (!root) return vector<int>();
        stack <TreeNode*> st;
        vector<int> ans;
        TreeNode *cur = root, *prev= NULL;
        
        bool isLeaf = false, isDone = false;
        st.push(cur);
        
        while(!st.empty()){
            cur = st.top();
            isLeaf = cur->left == NULL  && cur->right == NULL;
            isDone = prev && (cur->left == prev || cur->right == prev);
            
            if (isLeaf || isDone){
                ans.push_back(cur->val);
                cout << cur->val << endl;
                st.pop();
                prev = cur;
            } else {
                
                if (cur->right) st.push(cur->right);
                if (cur->left) st.push(cur->left);
            }
        }
        
        return ans;
    }
};

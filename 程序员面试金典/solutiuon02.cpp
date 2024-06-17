#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:

    // 面试题 04.01. 节点间通路
    // 此函数用于检查给定图中从'start'节点到'target'节点是否存在路径
    bool findWhetherExistsPath(int n, vector<vector<int>>& graph, int start, int target) {
        // 将图的邻接表转换为邻接映射，以便于后续查找
        for (int i = 0; i < graph.size(); i++) {
            map[graph[i][0]].insert(graph[i][1]);
        }

        // 初始化一个visited向量，用于记录已访问过的节点
        visited = vector<bool>(n, false);

        // 调用深度优先搜索（DFS）函数，检查是否存在从'start'到'target'的路径
        return dfs(start, target);
    }

    // 深度优先搜索（DFS）递归函数，用于检查从'start'到'target'是否存在路径
    bool dfs(int start, int target) {
        // 如果当前节点即是目标节点，则返回true
        if (start == target) {
            return true;
        }

        // 如果当前节点已被访问过，则返回false
        if (visited[start]) {
            return false;
        }

        // 标记当前节点为已访问
        visited[start] = true;

        // 遍历当前节点的所有邻居节点
        for (auto& neighbor : map[start]) {
            // 如果从邻居节点出发可以到达目标节点，则返回true
            if (dfs(neighbor, target)) {
                return true;
            }
        }

        // 如果没有找到从当前节点到目标节点的路径，则返回false
        return false;
    }

    // 面试题 04.02. 最小高度树
    // 函数：将一个整数数组转化为一个平衡二叉搜索树
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // 调用辅助函数来完成转化
        return helper(nums, 0, nums.size() - 1);
    }

    // 辅助函数：递归地将数组的中间元素转化为根节点，并分别构建左右子树
    TreeNode* helper(vector<int>& nums, int left, int right) {
        // 如果左索引大于右索引，说明当前区间为空，返回空指针
        if (left > right) {
            return nullptr;
        }

        // 计算中间索引，并将该位置的元素作为当前节点的值
        int mid = (left + right) / 2;

        // 创建一个新的树节点，并初始化其值为数组中的中间元素
        TreeNode* node = new TreeNode(nums[mid]);

        // 递归构建左子树
        node->left = helper(nums, left, mid - 1);

        // 递归构建右子树
        node->right = helper(nums, mid + 1, right);

        // 返回当前节点
        return node;
    }


    // 面试题 04.03. 特定深度节点链表
    // 函数：根据树的深度创建一个链表列表
    vector<ListNode*> listOfDepth(TreeNode* tree) {
        // 使用队列来存储树的节点
        queue<TreeNode*> que;
        vector<ListNode*> vec;

        // 如果树为空，则直接返回空列表
        if (tree == nullptr) {
            return vec;
        }

        // 将根节点加入队列
        que.push(tree);

        // 当队列不为空时，进行循环处理
        while (!que.empty()) {
            int size = que.size();
            ListNode* head = nullptr; // 定义当前深度的链表头节点
            ListNode* headIt = nullptr; // 定义当前深度的链表头节点的指针

            // 循环处理当前深度的所有节点
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();

                // 创建新的链表节点
                if (headIt == nullptr) {
                    head = new ListNode(node->val);
                    headIt = head;
                }
                else {
                    ListNode* listNode = new ListNode(node->val);
                    headIt->next = listNode;
                    headIt = listNode;
                }

                // 将该节点的左右子节点加入队列，以便进行下一层的处理
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }

            // 将该深度的链表加入结果列表
            vec.push_back(head);
        }

        // 返回结果列表
        return vec;
    }

    // 面试题 04.04. 检查平衡性
    bool isBalanced(TreeNode* root) {
        return (getDepth(root) == -1) ? false : true;
    }

    int getDepth(TreeNode* node) {
        // 递归终止条件：节点为null，表示已经到最后一个叶子节点，返回0
        if (node == nullptr) {
            return 0;
        }

        // 前序遍历，左右节点
        int leftDepth = getDepth(node->left);
        if (leftDepth == -1) return -1;

        int rightDepth = getDepth(node->right);
        if (rightDepth == -1) return -1;

        // 如果绝对值大于1的话，返回-1，表示不是平衡二叉树，反之返回高度
        return abs(leftDepth - rightDepth) > 1 ? -1 : 1 + max(leftDepth, rightDepth);
    }

    // 面试题 04.05. 合法二叉搜索树 (还有一种方法直接中序遍历到数组中，判断是否递增)
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        bool left = isValidBST(root->left);
        if (maxVal < root->val) {
            maxVal = root->val;
        }
        else {
            return false;
        }
        bool right = isValidBST(root->right);
        return left && right;
    }

    // 面试题 04.06. 后继者 
    // https://leetcode.cn/problems/successor-lcci/solutions/1490642/hou-ji-zhe-by-leetcode-solution-6hgc/?envType=study-plan-v2&envId=cracking-the-coding-interview
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode* tmp = nullptr;
        // 如果有右子树，找到右子树最小的节点
        if (p->right != nullptr) {
            tmp = p->right;
            while (tmp->left != nullptr) {
                tmp = tmp->left;
            }
            return tmp;
        }
        // 如果没有右子树，要找他的左子树的最小节点
        TreeNode* node = root;
        while (node != nullptr) {
            if (node->val > p->val) {
                tmp = node;
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        return tmp;
    }
private:
    std::vector<bool> visited;
    unordered_map<int, unordered_set<int>> map;
    long long maxVal = LONG_MIN;

    // 面试题 04.08. 首个共同祖先
public:
    TreeNode* ans;

    // 使用深度优先搜索（DFS）寻找两个节点p和q的最近公共祖先（LCA）
    // 如果p和q在同一子树中，那么它们的LCA就是该子树的根节点
    // 如果p和q分别在两个子树中，那么它们的LCA就是它们的根节点的父节点
    // 本例中，我们使用递归的方式实现DFS算法

    // DFS辅助函数：在以root为根的子树中寻找p和q的LCA
    bool dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 如果当前节点为空，则返回false
        if (root == nullptr) return false;

        // 在左子树中递归寻找p和q的LCA
        bool lson = dfs(root->left, p, q);

        // 在右子树中递归寻找p和q的LCA
        bool rson = dfs(root->right, p, q);

        // 如果左子树和右子树都有p和q的LCA，那么当前节点就是p和q的LCA
        if ((lson && rson) || ((root->val == p->val) || (root->val == q->val) && (lson || rson))) {
            ans = root;
        }

        // 如果左子树或右子树有p或q，或者当前节点的值等于p或q的值，
        // 那么返回true，表示已经找到了p或q的LCA
        return lson || rson || (root->val == p->val || root->val == q->val);
    }

    // 寻找以root为根的二叉树中两个节点p和q的最近公共祖先（LCA）
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 调用DFS辅助函数，寻找p和q的LCA，并返回结果
        dfs(root, p, q);
        return ans;
    }

    // 面试题 04.09. 二叉搜索树序列
public:
    // 获取二叉搜索树的所有可能序列
    vector<vector<int>> BSTSequences(TreeNode* root) {
        // 如果根节点为空，则返回一个空列表
        if (root == nullptr) return {{}};
        
        // 使用双端队列存储当前节点的父节点
        deque<TreeNode*> dq;
        // 将根节点加入双端队列
        dq.push_back(root);
        // 调用DFS辅助函数
        dfs(dq);
        // 返回结果
        return res;
    }

private:
    // DFS辅助函数：获取以当前节点为根的二叉搜索树的所有序列
    void dfs(deque<TreeNode*>& dq) {
        // 如果双端队列为空，则将当前路径加入结果列表
        if (dq.empty()) {
            res.push_back(path);
            return;
        }

        // 获取双端队列的大小
        int size = dq.size();
        for (int i = 0; i < size; i++) {
            // 获取当前节点
            TreeNode* node = dq.front();
            // 将当前节点从双端队列中移除
            dq.pop_front();
            // 将当前节点的值加入当前路径
            path.push_back(node->val);
            // 如果当前节点有左子节点，则加入双端队列
            if (node->left) dq.push_back(node->left);
            // 如果当前节点有右子节点，则加入双端队列
            if (node->right) dq.push_back(node->right);
            // 递归调用DFS辅助函数
            dfs(dq);
            // 将当前节点从双端队列中移除
            if (node->left) dq.pop_back();
            // 将当前节点从双端队列中移除
            if (node->right) dq.pop_back();
            // 将当前节点加入双端队列
            dq.push_back(node);
            // 将当前节点从当前路径中移除
            path.pop_back();
        }
    }
    
    // 存储当前路径
    vector<int> path;
    // 存储结果
    vector<vector<int>> res;

    // 面试题 04.10. 检查子树
public:

    // 比较两棵树是否相同的函数
    bool compare(TreeNode* t1, TreeNode* t2) {
        // 如果t2是空节点，但t1不是，则两棵树不同
        if (t2 == nullptr && t1 != nullptr) return false;

        // 如果t1是空节点，但t2不是，则两棵树不同
        if (t1 == nullptr && t2 != nullptr) return false;

        // 如果t1和t2都是空节点，则两棵树相同
        if (t1 == nullptr && t2 == nullptr) return true;

        // 如果t1和t2的值相同，则比较它们的左右子树
        if (t1->val == t2->val) {
            return compare(t1->left, t2->left) && compare(t1->right, t2->right);
        }

        // 如果t1和t2的值不同，则两棵树不同
        return false;
    }

    // 检查t2是否是t1的子树的函数
    bool checkSubTree(TreeNode* t1, TreeNode* t2) {
        // 如果t1是空节点，则返回false
        if (t1 == nullptr) {
            return false;
        }

        // 如果t2是空节点，则返回true
        if (t2 == nullptr) {
            return true;
        }

        // 如果t1和t2是相同的树，或者t2是t1的左子树，或者t2是t1的右子树，则返回true
        return compare(t1, t2) || checkSubTree(t1->left, t2) || checkSubTree(t1->right, t2);
    }
};
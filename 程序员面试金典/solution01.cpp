#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    // 面试题 01.01. 判定字符是否唯一
    bool isUnique(string astr) {
        // 如果字符串长度超过100，直接返回false，因为题目限制字符串长度最多为100
        if (astr.length() > 100) {
            return false;
        }

        // 创建一个大小为100的数组，用于统计每个字符出现的次数
        int charCount[100] = {0};

        // 遍历字符串中的每个字符
        for (auto& c : astr) {
            // 将字符c减去'a'，得到字符在数组中的索引，然后增加对应索引的计数
            charCount[c - 'a']++;
            // 如果某个字符的计数大于1，说明字符串中有重复字符，返回false
            if (charCount[c - 'a'] > 1) return false;
        }

        // 如果所有字符都只有出现一次，返回true
        return true;
    }

    // 面试题 01.02. 判定是否互为字符重排
    bool CheckPermutation(string s1, string s2) {

        // 如果两个字符串的长度不相等，直接返回false
        if (s1.length() != s2.length()) {
            return false;
        }

        // 获取字符串的长度
        int len = s1.length();
        // 创建一个哈希表，用于统计s1中每个字符出现的次数
        std::unordered_map<char, int> s1Count;

        // 遍历s1中的每个字符，统计每个字符出现的次数
        for (auto& a : s1) {
            s1Count[a]++;
        }

        // 遍历s2中的每个字符，将s1Count中对应字符的计数减一
        for (auto& b : s2) {
            s1Count[b]--;
        }

        // 遍历哈希表，检查每个字符的计数是否为0
        for (auto it = s1Count.begin(); it != s1Count.end(); it++) {
            // 如果某个字符的计数不为0，说明两个字符串中该字符出现的次数不相等，返回false
            if (it->second != 0) {
                return false;
            }
        }

        // 如果所有字符的计数都为0，说明两个字符串是排列词，返回true
        return true;
    }

    // 面试题 01.03. URL化
    string replaceSpaces(string S, int length) {
        // 该函数用于将字符串S中的空格替换为"%20"

        // 如果字符串长度大于500000，直接返回空字符串
        if (length > 500000) {
            return "";
        }

        // 计算字符串S中的空格数
        int cnt = 0;
        for(int i=0; i<length; ++i)
        {
            if(' '==S[i])
            {
                ++cnt;
            }
        }

        // 调整字符串S的大小，使其能够容纳替换后的字符
        S.resize(length + 2 * cnt);
        // 初始化指针cur，指向字符串S的末尾
        int cur = S.size() - 1;

        // 遍历字符串S中的每个字符
        while(length--)
        {
            // 如果当前字符是空格
            if(' '==S[length])
            {
                // 将"%20"的字符依次替换到字符串S的尾部
                S[cur--] = '0';
                S[cur--] = '2';
                S[cur--] = '%';
            }
            else
            {
                // 如果当前字符不是空格，将其替换到字符串S的尾部
                S[cur--] = S[length];
            }
        }

        // 返回替换后的字符串S
        return S;
    }
    // 方法二
    // string replaceSpaces(string S, int length) {
    //         //先计算有多少空格，就可以知道替换后的最后一个字符的位置
    //         int cnt=0;
    //         for(int i=0; i<length; ++i)
    //         {
    //             if(' '==S[i] )
    //             {
    //                 ++cnt;
    //             }
    //         }

    //         S.resize( length+2*cnt ); //扩充实际空间到最后返回的空间
    //         int cur=S.size()-1;
    //         while( length-- )
    //         {
    //             if( ' '==S[length] )
    //             {
    //                 S[cur--]='0';
    //                 S[cur--]='2';
    //                 S[cur--]='%';
    //             }
    //             else
    //             {
    //                 S[cur--]=S[length];
    //             }
    //         }

    //         return S;
    //     }

    // 面试题 01.04. 回文排列
    bool canPermutePalindrome(string s) {
        // 该函数用于判断字符串s是否可以通过排列字符成为回文字符串

        // 如果字符串s为空，直接返回false
        if (s.size() == 0) {
            return false;
        }

        // 获取字符串s的长度
        int lenn = s.size();
        // 创建一个哈希表，用于统计s中每个字符出现的次数
        unordered_map<char, int> cntMap;
        // 遍历字符串s中的每个字符，统计每个字符出现的次数
        for (int i = 0; i < lenn; i++) {
            cntMap[s[i]]++;
        }

        // 记录出现奇数次的字符个数
        int count = 0;
        // 遍历哈希表中的每个字符
        for (auto it = cntMap.begin(); it != cntMap.end(); it++) {
            // 如果某个字符出现的次数为奇数，累加到count中
            if (it->second % 2 != 0) {
                count++;
            }
        }
        // 如果出现奇数次的字符个数大于等于2，无法构成回文字符串，返回false
        if (count >= 2) {
            return false;
        }
        // 否则，可以通过排列字符成为回文字符串，返回true
        return true;
    }

    // 面试题 01.05. 一次编辑
    bool oneEditAway(string first, string second) {
        // 检查两个字符串是否相差一个编辑操作

        // 如果两个字符串相等，或者它们的长度之差为1，直接返回true
        if (first == second || (first.size() + second.size() == 1)) {
            return true;
        }

        int fLen = first.size();
        int eLen = second.size();

        int minusLen = fLen - eLen;
        // 如果第一个字符串比第二个字符串长2个或更多字符，直接返回false
        if (minusLen >= 2) {
            return false;
        }
        // 如果第一个字符串和第二个字符串长度相等，检查是否有且仅有一个位置的字符不同
        else if (minusLen == 0) {
            unordered_map<char, int> cntMap;
            for (auto& c : first) {
                cntMap[c]++;
            }

            for (auto& d : second) {
                cntMap[d]--;
            }

            bool flg = false;
            for (auto it = cntMap.begin(); it != cntMap.end(); it++) {
                if (it->second == 1) {
                    flg = !flg;
                }
            }

            return flg;
        }
        // 如果第一个字符串比第二个字符串短，检查是否有且仅有一个位置的字符不同
        else {
            if (fLen == eLen) {
                int cnt = 0;
                for (int i = 0; i < fLen; i++) {
                    if (first[i] != second[i]) {
                        cnt++;
                    }
                }

                if (cnt == 1) {
                    return true;
                }
                return false;
            }
            else {
                if (fLen > eLen) {
                    int j = 0;
                    int cnt = 0;
                    for (int i = 0; i < fLen; i++) {
                        if (first[i] != second[j]) {
                            cnt++;
                        }
                        else {
                            j++;
                        }
                    }
                    if (cnt == 1) {
                        return true;
                    }
                    return false;
                }
                else {
                    int j = 0;
                    int cnt = 0;
                    for (int i = 0; i < eLen; i++) {
                        if (second[i] != first[j]) {
                            cnt++;
                        }
                        else {
                            j++;
                        }
                    }
                    if (cnt == 1) {
                        return true;
                    }
                    return false;
                }
            }
        }
    }

    // 面试题 01.06. 字符串压缩
    string compressString(string S) {
        // 压缩字符串S，返回压缩后的字符串

        // 初始化一个空字符串a，用于存储压缩后的字符串
        string a = "";
        // 初始化计数器cnt，用于统计连续相同字符的数量
        int cnt = 1;
        // 初始化变量len，用于存储压缩后的字符串的长度
        int len = 0;
        // 初始化字符charc，用于存储当前字符
        char charc = S[0];

        // 遍历字符串S中的每个字符
        for (int i = 1; i < S.length(); i++) {
            // 如果当前字符与前一个字符相同，cnt加1
            if (S[i] == charc) {
                cnt++;
            }
            else {
                // 将前一个字符及其计数添加到字符串a中
                a += charc + to_string(cnt);
                // 更新当前字符为当前字符
                charc = S[i];
                // 重置计数器cnt为1
                cnt = 1;
            }
        }

        // 将最后一个字符及其计数添加到字符串a中
        a += charc + to_string(cnt);

        // 如果压缩后的字符串长度大于等于原字符串长度，则返回原字符串
        if (a.length() >= S.length()) {
            return S;
        }

        // 否则，返回压缩后的字符串
        return a;
    }

    // 面试题 01.07. 旋转矩阵
    void rotate(vector<vector<int>>& matrix) {
        // 旋转矩阵

        // 如果矩阵为空或矩阵的行数为1，直接返回
        if (matrix.size() == 0 || matrix[0].size() == 1) {
            return;
        }
        // 初始化临时变量temp，用于存储矩阵中的元素
        int temp = 0;
        // 获取矩阵的大小（行数）
        int n = matrix.size();
        // 遍历矩阵的前一半行
        for (int i = 0; i < n/2; i++) {
            // 遍历矩阵的当前行中的所有列
            for (int j = i; j < n - i - 1; ++j) {
                // 将当前元素存储到临时变量temp中
                temp = matrix[i][j];
                // 将右上角的元素移动到左上角
                matrix[i][j] = matrix[n - j - 1][i];
                // 将左下角的元素移动到右上角
                matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
                // 将右下角的元素移动到左下角
                matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
                // 将左上角的元素移动到右下角
                matrix[j][n - i - 1] = temp;
            }
        }
    }

    // 面试题 01.08. 零矩阵
    // void setZeroes(vector<vector<int>>& matrix) {
    //     if (matrix.size() == 0) return;
    //     vector<vector<int>> tmp(matrix);
    //     int M = matrix.size();
    //     int N = matrix[0].size();
    //     for (int i = 0; i < M; i++) {
    //         for (int j = 0; j < N; j++) {
    //             if (tmp[i][j] == 0) {
    //                 for (int a = 0; a < M; a++) {
    //                     matrix[a][j] = 0;
    //                 }

    //                 for (int b = 0; b < N; b++) {
    //                     matrix[i][b] = 0;
    //                 }
    //             }
    //         }
    //     }
    // }
    void setZeroes(vector<vector<int>>& matrix) {
        // 给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。

        // 初始化矩阵的大小（行数和列数）
        int M = matrix.size();
        int N = matrix[0].size();

        // 标记第一行和第一列是否需要清零
        bool flgCol = false;
        bool flgRow = false;

        // 遍历矩阵的每一行
        for (int i = 0; i < M;i++) {
            // 如果第一列中有元素为0，则标记第一列为true
            if (matrix[i][0] == 0) {
                flgCol = true;
            }
        }

        // 遍历矩阵的每一列
        for (int j = 0; j < N;j++) {
            // 如果第一行中有元素为0，则标记第一行为true
            if (matrix[0][j] == 0) {
                flgRow = true;
            }
        }

        // 遍历矩阵的剩余元素
        for(int i = 1; i < M; i++) {
            for (int j = 1; j < N; j++) {
                // 如果当前元素为0，则将该行和该列的第一个元素设为0
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // 遍历矩阵的剩余元素
        for(int i = 1; i < M; i++) {
            for (int j = 1; j < N; j++) {
                // 如果该行或该列的第一个元素为0，则将该当前元素设为0
                if (!matrix[i][0] || !matrix[0][j]) {
                    matrix[i][j] = 0;
                }
            }
        }

        // 如果第一行需要清零，则将第一行的所有元素设为0
        if (flgCol) {
            for (int i = 0; i < M;i++) {
                matrix[i][0] = 0;
            }
        }

        // 如果第一列需要清零，则将第一列的所有元素设为0
        if (flgRow) {
            for (int j = 0; j < N;j++) {
                matrix[0][j] = 0;
            }
        }
    }

    // 面试题 01.09. 字符串轮转
    bool isFlipedString(string s1, string s2) {
        return s1.length() == s2.length() && (s2 + s2).find(s1) != -1;
    }
};
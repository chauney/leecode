#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;



class Solution {
public:

    // 对于二进制表示小数，通过 1/2 + 1/2^1 + 1/2^2表示 0.111
    // 因此每次将小数乘2可以去除最高位，输入到字符串中
    string printBin(double num) {
        string res = "0.";
        while(res.size() <= 32 && num != 0) {
            num *= 2;
            int digit = num;
            res.push_back(digit + '0');
            num -= digit;
        }

        return res.size() <= 32 ? res : "ERROR";
    }

    // 面试题 05.03. 翻转数位
    // 动态规划解决
    int reverseBits(int num) {
        int curCnt = 0, reserveCnt = 0; // 初始化当前连续1的个数和最大连续1的个数
        int maxLen = 0; // 初始化最大连续1的个数

        for (int i = 0; i < 32; i++) { // 遍历32位二进制数
            if (num & 1 == 1) { // 如果当前位为1
                reserveCnt++; // 增加连续1的个数
                curCnt++; // 增加当前连续1的个数
            } else { // 如果当前位为0
                reserveCnt = curCnt + 1; // 更新最大连续1的个数
                curCnt = 0; // 重置当前连续1的个数
            }

            if (reserveCnt > maxLen) { // 更新最大连续1的个数
                maxLen = reserveCnt;
            }
            num >>= 1; // 右移当前数，去掉最低位
        }
        return maxLen; // 返回最大连续1的个数
    }
};
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
};
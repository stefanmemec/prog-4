#include <bits/stdc++.h>
using namespace std;

class BigInt {
public:
    string num;

    BigInt(string s = "0") {
        num = s;
    }

    bool isLess(BigInt other) {
        if (num.length() != other.num.length()) {
            return num.length() < other.num.length();
        }
        return num < other.num;
    }

    bool operator==(BigInt other) {
        return num == other.num;
    }

    BigInt operator+(BigInt other) {
        string result = "";
        int i = num.length() - 1, j = other.num.length() - 1, carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            int digit1 = (i >= 0) ? num[i--] - '0' : 0;
            int digit2 = (j >= 0) ? other.num[j--] - '0' : 0;
            int sum = digit1 + digit2 + carry;
            result += (char)((sum % 10) + '0');
            carry = sum / 10;
        }
        reverse(result.begin(), result.end());
        return BigInt(result);
    }

    BigInt operator-(BigInt other) {
        string result = "";
        int i = num.length() - 1, j = other.num.length() - 1, borrow = 0;
        while (i >= 0) {
            int digit1 = num[i--] - '0';
            int digit2 = (j >= 0) ? other.num[j--] - '0' : 0;
            int diff = digit1 - digit2 - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result += (char)(diff + '0');
        }
        while (result.length() > 1 && result.back() == '0') result.pop_back();
        reverse(result.begin(), result.end());
        return BigInt(result);
    }

    BigInt operator*(BigInt other) {
        int n = num.length(), m = other.num.length();
        vector<int> prod(n + m, 0);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int mul = (num[i] - '0') * (other.num[j] - '0');
                int sum = mul + prod[i + j + 1];
                prod[i + j + 1] = sum % 10;
                prod[i + j] += sum / 10;
            }
        }
        string result = "";
        for (int d : prod) if (!(result.empty() && d == 0)) result += (char)(d + '0');
        return result.empty() ? BigInt("0") : BigInt(result);
    }

    pair<BigInt, BigInt> divmod(BigInt other) {
        if (other.num == "0") return {BigInt("Error"), BigInt("Error")};
        string quotientStr = "", remainderStr = "";
        for (char c : num) {
            remainderStr += c;
            while(remainderStr.size() > 1 && remainderStr[0] == '0') remainderStr.erase(0, 1);
            BigInt current(remainderStr);
            int count = 0;
            while (!(current.isLess(other))) {
                current = current - other;
                remainderStr = (current.num == "0") ? "" : current.num;
                count++;
            }
            quotientStr += (char)(count + '0');
        }
        size_t first = quotientStr.find_first_not_of('0');
        string q = (first == string::npos) ? "0" : quotientStr.substr(first);
        string r = remainderStr.empty() ? "0" : remainderStr;

        return {BigInt(q), BigInt(r)};
    }

    BigInt operator/(BigInt other) { return divmod(other).first; }
    BigInt operator%(BigInt other) { return divmod(other).second; }
};


BigInt binpow(BigInt base, BigInt exp, BigInt mod) {
    BigInt result("1");
    base = base % mod;
    while (!(exp == BigInt("0"))) {
        BigInt rem = exp % BigInt("2");
        if (!(rem == BigInt("0"))) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / BigInt("2");
    }
    return result;
}


int main() {
    BigInt base("7");
    BigInt exponent("15");
    BigInt modulus("100");

    BigInt result = binpow(base, exponent, modulus);

    cout <<  "Base: " << base.num << endl;
    cout <<  "Exponent: " << exponent.num << endl;
    cout <<  "Modulus: " << modulus.num << endl;
    cout <<  "Result: " << result.num << endl;

    return 0;
}

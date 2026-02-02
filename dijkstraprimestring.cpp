#include <bits/stdc++.h>
using namespace std;

class BigInt {
public:
    string number;

    BigInt(string num = "0") {
        number = num;
    }

    bool isLess(BigInt other) {
        if (number.length() != other.number.length())
            return number.length() < other.number.length();
        return number < other.number;
    }

    BigInt operator+(BigInt other) {
        string result = "";
        int i = number.length() - 1, j = other.number.length() - 1, carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            int digit1 = (i >= 0) ? number[i--] - '0' : 0;
            int digit2 = (j >= 0) ? other.number[j--] - '0' : 0;
            int sum = digit1 + digit2 + carry;
            result += (char)((sum % 10) + '0');
            carry = sum / 10;
        }
        reverse(result.begin(), result.end());
        return BigInt(result);
    }

    BigInt operator-(BigInt other) {
        string result = "";
        int i = number.length() - 1, j = other.number.length() - 1, borrow = 0;
        while (i >= 0) {
            int digit1 = number[i--] - '0';
            int digit2 = (j >= 0) ? other.number[j--] - '0' : 0;
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
        int n = number.length(), m = other.number.length();
        vector<int> prod(n + m, 0);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int mul = (number[i] - '0') * (other.number[j] - '0');
                int sum = mul + prod[i + j + 1];
                prod[i + j + 1] = sum % 10;
                prod[i + j] += sum / 10;
            }
        }
        string result = "";
        for (int d : prod) if (!(result.empty() && d == 0)) result += (char)(d + '0');
        return result.empty() ? BigInt("0") : BigInt(result);
    }

    BigInt operator/(BigInt other) {
        if (other.number == "0") return BigInt("Error");
        string result = "", temp = "";
        for (char c : number) {
            temp += c;
            while (temp.size() > 1 && temp[0] == '0') temp.erase(0, 1);
            BigInt current(temp);
            int count = 0;
            while (!(current.isLess(other))) {
                current = current - other;
                temp = (current.number == "0") ? "" : current.number;
                count++;
            }
            result += (char)(count + '0');
        }
        size_t first = result.find_first_not_of('0');
        return (first == string::npos) ? BigInt("0") : BigInt(result.substr(first));
    }
};

struct Compare {
    bool operator()(pair<BigInt, BigInt> a, pair<BigInt, BigInt> b) {
        return b.first.isLess(a.first);
    }
};

void dijkstraBigIntPrimes(int limit) {
    priority_queue<pair<BigInt, BigInt>, vector<pair<BigInt, BigInt>>, Compare> pq;

    cout << "2 ";
    pq.push({BigInt("4"), BigInt("2")});

    for (int i = 3; i <= limit; i++) {
        BigInt num(to_string(i));
       
        if (num.isLess(pq.top().first)) {
            cout << i << " ";
            pq.push({num * num, num});
        } else {
            while (num.number == pq.top().first.number) {
                auto top = pq.top();
                pq.pop();
                pq.push({top.first + top.second, top.second});
            }
        }
    }
    cout << endl;
}

int main() {
    dijkstraBigIntPrimes(50);
    return 0;
}

#include<string>
#include<iostream>
using namespace std;

const int MAX = 256;
int a_pos, b_pos;
int a_len, b_len;
string remain = "0"; //保存除法的余数

//函数声明 
string def_multiply(string a, string b); 
string multiply(string a, string b);
string def_add(string a, string b);
string add(string a, string b);
string def_subtract(string a, string b);
string subtract(string a, string b);
string def_divide(string a, string b);
string divide(string a, string b);

int main()
{
    cout << "请输入一个运算式，数字和符号之间用空格隔开，例如：1（空格）*（空格）2" << endl;
    string a;
    string b;
    char syn;
    cin >> a >> syn >> b;
    if (syn == '+')
        cout << a << "+" << b << "=" << add(a, b) << endl;
    if (syn == '-')
        cout << a << "-" << b << "=" << subtract(a, b) << endl;
    if (syn == '*')
        cout << a << "*" << b << "=" << multiply(a, b) << endl;
    if (syn == '/')
        cout << a << "/" << b << "=" << divide(a, b) << "余数为：" << remain << endl;
    return 0;
}

//////////////////////////////////////////////////加法 ///////////////////////////////////////////////////////////
string def_add(string a, string b)
{
    string result_str = "";
    char result[MAX] = { 0 };
    int flag = 0, sum = 0;
    int length;
    a_len = a.length(), b_len = b.length();
    int  len = (a_len > b_len ? a_len : b_len);
    length = len - 1;
    for (int i = 0, b_pos = b_len - 1, a_pos = a_len - 1; i < len; i++, a_pos--, b_pos--)
    {
        if (b_pos < 0)
        {
            sum = a[a_pos] - 48 + flag;
            result[i] = sum % 10;
            flag = sum / 10;
        }
        else if (a_pos < 0)
        {
            sum = b[b_pos] - 48 + flag;
            result[i] = sum % 10;
            flag = sum / 10;
        }
        else
        {
            sum = a[a_pos] + b[b_pos] - 96 + flag;
            result[i] = sum % 10;
            flag = sum / 10;
        }
    }
    if (flag > 0)
    {
        length++;
        result[len] = flag;
    }
    for (; length >= 0; length--)
    {
        result_str += result[length] + 48;
    }
    return result_str;
}

string add(string a, string b)
{
    string str;
    if (a[0] == '-' && b[0] != '-')
    {
        a = a.substr(1);
        return subtract(b, a);
    }
    else if (b[0] == '-' && a[0] != '-')
    {
        b = b.substr(1);
        return subtract(a, b);
    }
    else if (b[0] == '-' && a[0] == '-')
    {
        a = a.substr(1);
        b = b.substr(1);
        str = "-" + def_add(a, b);
        return str;
    }
    else
    {
        return def_add(a, b);
    }
}

//////////////////////////////////////////////////减法 ///////////////////////////////////////////////////////////
string def_subtract(string a, string b)
{
    char result[MAX] = { 0 };
    a_len = a.length(), b_len = b.length();
    int flag = 0;
    int i = 0;
    string str = "";
    for (b_pos = b_len - 1, a_pos = a_len - 1; i < b_len; i++, a_pos--, b_pos--)
    {
        if (a[a_pos] < b[b_pos])
        {
            result[i] = a[a_pos] + 10 - b[b_pos];
            a[a_pos - 1] -= 1;
        }
        else
        {
            result[i] = a[a_pos] - b[b_pos];
        }

    }
    for (i = a_len - b_len - 1; i >= 0; i--)
    {
        if (a[i] < '0')
        {
            a[i - 1]--;
            result[a_len - i - 1] = a[i] - 38;
        }
        else { result[a_len - i - 1] = a[i] - 48; }
    }

    for (i = a_len - 1; i >= 0; i--)
    {
        str += result[i] + 48;
    }
    int j = 0;
    while (str[j] == '0' && j != str.length())
    {
        j++;
    }
    if (j != 0)str.erase(0, j);
    if (str.length() == 0)str = "0";
    return str;
}

string subtract(string a, string b)
{
    string str;
    if (a[0] == '-' && b[0] != '-')
    {
        a = a.substr(1);
        str = "-" + def_add(a, b);
        return str;
    }
    else if (b[0] == '-' && a[0] != '-')
    {
        b = b.substr(1);
        str = def_add(a, b);
        return str;
    }
    else if (b[0] == '-' && a[0] == '-')
    {
        a = a.substr(1);
        b = b.substr(1);
        return subtract(b, a);
    }
    else
    {
        if (a.length() > b.length() || (a.length() == b.length() && a >= b))
        {
            str = def_subtract(a, b);
            return str;
        }
        else
        {
            str = "-" + def_subtract(b, a);
            return str;
        }
    }
}

//////////////////////////////////////////////////乘法 ///////////////////////////////////////////////////////////
string def_multiply(string a, string b)
{
    char result[MAX] = { 0 };
    int length;
    a_len = a.length(), b_len = b.length();
    string result_str = "";
    int flag = 0, sum = 0;
    int top;
    for (int i1 = 0, a_pos = a_len - 1; i1 < a_len; i1++, a_pos--)
    {
        for (int i2 = 0, b_pos = b_len - 1; i2 < b_len; i2++, b_pos--)
        {
            top = i1 + i2;
            sum = result[top] + (a[a_pos] - 48) * (b[b_pos] - 48) + flag;
            result[top] = sum % 10;
            flag = sum / 10;
        }
        if (flag > 0)
        {
            top++;
            result[top] = result[top] + flag % 10;
            flag = flag / 10;
        }
        length = top;
    }
    for (; length >= 0; length--)
    {
        result_str += result[length] + 48;
    }
    return result_str;
}

string multiply(string a, string b)
{
    string str;
    if (a[0] == '-' && b[0] != '-')
    {
        a = a.substr(1);
        str = "-" + def_multiply(a, b);
        return str;
    }
    else if (b[0] == '-' && a[0] != '-')
    {
        b = b.substr(1);
        str = "-" + def_multiply(a, b);
        return str;
    }
    else if (b[0] == '-' && a[0] == '-')
    {
        a = a.substr(1);
        b = b.substr(1);
        return def_multiply(a, b);
    }
    else
    {
        return def_multiply(a, b);
    }
}

//////////////////////////////////////////////////除法 ///////////////////////////////////////////////////////////
string def_divide(string a, string b)
{
    int length, j = 0;
    string s, b2, sum = "0", temp = "";
    a_len = a.length(), b_len = b.length();
    if (a == b)
        return "1";
    if (a_len > b_len)
    {
        s = a;
        length = a_len - b_len;
        for (; length >= 0; length--)
        {
            b2 = b;
            for (int i = 0; i < length; i++)
                b2 = b2 + '0';

            while (s[0] != '-')
            {
                s = subtract(s, b2);
                j++;
            }
            s = add(s, b2);
            char ch = j + 48 - 1;
            temp += ch;
            for (int i = 0; i < length; i++)
                temp = temp + "0";
            sum = def_add(sum, temp);
            temp = "", j = 0;
        }
        remain = s;
        return sum;
    }
    else if (a_len == b_len && a > b)
    {
        s = a;
        sum = (a[0] - 48) / (b[0] - 48) + 48;
        for (int i = 0; i < (a[0] - 48) / (b[0] - 48); i++)
        {
            s = def_subtract(s, b);
        }
        return sum;
    }
    else
    {
        remain = a;
        return "0";
    }
}

string divide(string a, string b)
{
    string str;
    if (a[0] == '-' && b[0] != '-')
    {
        a = a.substr(1);
        str = "-" + def_divide(a, b);
        remain = "-" + remain;
        return str;
    }
    else if (b[0] == '-' && a[0] != '-')
    {
        b = b.substr(1);
        return "-" + def_divide(a, b);
    }
    else if (b[0] == '-' && a[0] == '-')
    {
        a = a.substr(1);
        b = b.substr(1);
        str = def_divide(a, b);
        remain = "-" + remain;
        return str;
    }
    else
    {
        return def_divide(a, b);
    }
}


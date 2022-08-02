#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

struct HTNode
{
    int weight;
    int parent, lchild, rchild;
    HTNode() :weight(0), parent(-1), lchild(-1), rchild(-1) {}
};

//函数声明
void huffmancode(HTNode* HT, string* code, int root, string space);
void compress(ifstream& infile, ofstream& outfile);
void uncompress(ifstream& infile, ofstream& outfile);

class woutstream
{
    ofstream& outfile;
    uint8_t buff;
    int buffp;
public:
    woutstream(ofstream& outfile)
        :outfile(outfile), buff(0), buffp(0) {}
    void writebit(int bit)
    {
        buff |= bit << buffp;
        buffp++;
        if (buffp == 8)
            flush();
    }

    void flush()
    {
        outfile.write((char*)&buff, 1);
        buff = 0;
        buffp = 0;
    }

    void writebits(string s)
    {
        for (int i = 0; i < s.size(); i++)
            writebit(s[i] - '0');
    }
};


class winstream
{
    ifstream& infile;
    HTNode* HT;
    uint8_t buff;
    int buffp;
    int root;
public:
    winstream(ifstream& infile, HTNode* HT, int root)
        :infile(infile), HT(HT), root(root), buff(0), buffp(0) {}
    int readbit()
    {
        if (buffp == 0)
        {
            infile.read((char*)&buff, 1);
        }
        int bit = (buff >> buffp) & 1;
        buffp++;
        buffp %= 8;
        return bit;
    }

    uint8_t readchar()
    {
        int p;
        for (p = root; HT[p].lchild >= 0 || HT[p].rchild >= 0; p = readbit() ? HT[p].rchild : HT[p].lchild);
        return p;
    }

};

int main()
{
    srand(time(0));
    char inputFile[50];
    char resultFile[50];
    char Filename[50];
    int choice;
    cout << "请用数字输入操作：" << endl;
    cout << "1：随机生成一个充满字母的文件" << endl;
    cout << "2：压缩文件" << endl;
    cout << "3：解压文件" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:cout << "请输入生成的文件名："; break;
    case 2:cout << "请输入要压缩的文件名："; break;
    case 3:cout << "请输入要解压的文件名："; break;
    default:cout << "输入错误"; break;
    }

    if (choice == 2 || choice == 3)
    {
        cin >> inputFile;
        cout << "请输入操作结果文件名：";
        cin >> resultFile;

        ifstream infile(inputFile, std::ios::binary);
        if (!infile)
        {
            cout << "打开文件出错" << endl;
            return 0;
        }
        ofstream outfile(resultFile, std::ios::binary);
        if (!outfile)
        {
            cout << "打开目标文件出错" << endl;
            return 0;
        }
        switch (choice)
        {
        case 2:
            compress(infile, outfile);
            cout << "压缩完成，输出文件：" << resultFile << endl; break;
        case 3:
            uncompress(infile, outfile);
            cout << "解压完成，输出文件：" << resultFile << endl; break;
            break;
        default:
            cout << "错误" << endl; break;
        }
        infile.close();
        outfile.close();
    }
    else
    {
        cin >> Filename;
        ofstream outfile(Filename);
        if (!outfile)
        {
            cout << "打开目标文件出错" << endl;
            return 0;
        }
        for (int i = 0; i < 1000000; i++)
        {
            char c = rand() % 26 + 97;
            outfile.write(&c, 1);
        }
        cout << "已生成" << endl;
    }
    return 0;
}


//哈夫曼编码
void huffmancode(HTNode* HT, string* code, int root, string space = "")
{
    if (HT[root].lchild < 0 && HT[root].rchild < 0)
    {
        code[root] = space;
    }
    else
    {
        if (HT[root].lchild >= 0)
            huffmancode(HT, code, HT[root].lchild, space + "0");
        if (HT[root].rchild >= 0)
            huffmancode(HT, code, HT[root].rchild, space + "1");
    }
}

void compress(ifstream& infile, ofstream& outfile)
{
    HTNode HT[511];
    uint8_t c;
    int i;

    while (!infile.eof())
    {
        infile.read((char*)&c, 1);
        HT[c].weight++;
    }

    for (int i = 256; i < 511; i++)
    {
        int m1 = 999999, m2 = 999999, p1 = -1, p2 = -1;

        for (int j = 0; j < i; j++)
        {
            if (HT[j].parent < 0)
            {
                if (p1 < 0 || HT[j].weight < m1)
                {
                    m2 = m1;
                    p2 = p1;
                    m1 = HT[j].weight;
                    p1 = j;
                }
                else if (p2 < 0 || HT[j].weight < m2)
                {
                    m2 = HT[j].weight;
                    p2 = j;
                }
            }
        }
        if (p1 > p2)
        {
            swap(p1, p2);
            swap(m1, m2);
        }
        HT[i].weight = HT[p1].weight + HT[p2].weight;
        HT[i].lchild = p1; HT[i].rchild = p2;
        HT[p1].parent = i; HT[p2].parent = i;
    }

    string code[256];
    huffmancode(HT, code, 510);
    outfile << "lyf" << '\0';
    infile.clear();
    uint32_t filesize = infile.tellg();
    outfile.write((char*)&filesize, 4);
    for (int i = 0; i < 510; i++)
    {
        c = HT[i].parent & 255;
        outfile.write((char*)&c, 1);
    }

    infile.seekg(0);
    woutstream obin(outfile);
    while (!infile.eof())
    {
        infile.read((char*)&c, 1);
        obin.writebits(code[c]);
    }
    obin.flush();
}

void uncompress(ifstream& infile, ofstream& outfile)
{
    char filehead[4];
    int i;
    infile.read(filehead, 4);
    for (int i = 0; i < 4; i++)
    {
        if (filehead[i] != "lyf"[i])
        {
            cout << "wrong file!" << endl;
            return;
        }
    }
    uint32_t filesize;
    infile.read((char*)&filesize, 4);
    HTNode HT[511];
    uint8_t c;
    for (int i = 0; i < 510; i++)
    {
        infile.read((char*)&c, 1);
        int p = c + 256;
        HT[i].parent = p;
        if (HT[p].lchild < 0)
            HT[p].lchild = i;
        else
        {
            HT[p].rchild = i;
            if (HT[p].lchild > HT[p].rchild)
            {
                swap(HT[p].lchild, HT[p].rchild);
            }
        }
    }
    winstream ibin(infile, HT, 510);
    for (i = 0; i < filesize; i++)
    {
        c = ibin.readchar();
        outfile.write((char*)&c, 1);
    }
}
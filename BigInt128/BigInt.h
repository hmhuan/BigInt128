#include <iostream>
#include <string>	
#include <map>

using namespace std;
//jasdhjgsdhgasdasgdhhgdjasjasgdj
struct BigInt {
	unsigned int data[4] = { 0 };
};

//BIỂU DIỄN SỐ ÂM BẰNG PHƯƠNG PHÁP DẤU LƯỢNG

string Chia2(string a);

void DecimalToBigInt(BigInt &a, string dec);

void ScanBigInt(BigInt &x)
{
	string a;
	cin >> a;
	DecimalToBigInt(x, a);
}

string DecimalToBinary(unsigned int x);

//Hệ 10 (BigInt) -> Hệ 2
string DecToBin(BigInt x);

//hệ 2 -> hệ 16
string BinToHex(string bit);


string Nhan2(string a);

string HaiMuX(int n);


BigInt BinToDec(string bit);

string DecToHex(BigInt x);

string Cong(string a, string b);

BigInt operator+(BigInt a, BigInt b);
BigInt operator-(BigInt a, BigInt b);
BigInt operator*(BigInt a, BigInt b);
string NhanVsX(char, string);
BigInt operator/(BigInt a, BigInt b);


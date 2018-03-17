#include <iostream>
#include <string>	
#include <map>

using namespace std;

struct BigInt {
	unsigned int data[4] = { 0 };
};

//BIỂU DIỄN SỐ ÂM BẰNG PHƯƠNG PHÁP BÙ 2 //

string Chia2(string a);
string Nhan2(string a);
string HaiMuX(int n);


void DecimalToBigInt(BigInt &a, string dec);
void BinaryToBigInt(BigInt &a, string dec);
void HexadecimalToBigInt(BigInt &a, string dec);


void ScanBigInt(BigInt &x, string temp);


string DecimalToBinary(unsigned int x);

//Hệ 10 (BigInt) -> Hệ 2
string DecToBin(BigInt x);

//Hệ 2 -> Hệ 16
string BinToHex(string bit);

BigInt BinToDec(string bit);

string DecToHex(BigInt x);

string Cong(string a, string b);

BigInt operator+(BigInt a, BigInt b);
BigInt operator-(BigInt a, BigInt b);
BigInt operator*(BigInt a, BigInt b);
string NhanVsX(char, string);
BigInt operator/(BigInt a, BigInt b);
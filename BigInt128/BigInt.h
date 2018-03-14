#pragma once
#include <iostream>
#include <string>	
using namespace std;

struct BigInt {
	unsigned int data[4] = { 0 };
};

//BIỂU DIỄN SỐ ÂM BẰNG PHƯƠNG PHÁP DẤU LƯỢNG

string Chia2(string a)
{
	int n = a.length();
	for (int i = 0; i < n; i++)
	{
		if (a[i] % 2 == 1)
		{
			a[i + 1] = 10 + a[i + 1];
		}
		a[i] = (a[i] - '0') / 2 + '0';
		if (a[0] == '0')
		{
			a.erase(a.begin());
			i--; n--;
		}
	}
	return a;
}

void DecimalToBigInt(BigInt &a, string dec)
{
	int n, chiSo;
	int vitriBit;
	//string h;
	if (dec[0] == '-')
	{
		dec.erase(dec.begin());
		a.data[0] = a.data[0] | (1 << (31));
	}
	n = dec.length();
	for (int i = 0;; i++)
	{
		if (n == 0) break;
		//cout << "i = " << i << " Chi so = " << chiSo << "  Vitribit = " << vitriBit;
		if ((dec[n - 1] - '0') % 2 == 1)
		{
			chiSo = 3 - i / 32;
			vitriBit = i % 32;
			if (chiSo < 0 || (chiSo == 0 && vitriBit == 31))
			{
				cout << "So qua lon.";
				return;
			}
			//cout << "  Bit 1" << endl;
			//h = " " + h;
			//h[0] = '1';
			//sunsigned int k = a.data[chiSo] | (1 << (vitriBit));
			a.data[chiSo] = a.data[chiSo] | (1 << (vitriBit));
			//a.data[chiSo] = a.data[chiSo] + powl(2, vitriBit);
		}
		/*else
		{
			cout << "  Bit 0" << endl;
			h = " " + h;
			h[0] = '0';
		}*/
		//Chỉ số = 3 khi i từ 0 tới 31
		//Chỉ số = 2 khi i từ 32 tới 63
		//Chỉ số = 1 khi i từ 64 tới 95
		//Chỉ số = 0 khi i từ 96 tới 127
		dec = Chia2(dec);
		n = dec.length();
	}
	//cout << h << endl;
}

void ScanBigInt(BigInt &x)
{
	string a;
	getline(cin, a);
	DecimalToBigInt(x, a);
}

string DecimalToBinary(unsigned int x)
{
	string bin = "";
	while (x != 0)
	{
		bin = " " + bin;
		if (x % 2 == 1)
		{
			bin[0] = '1';
		}
		else
		{
			bin[0] = '0';
		}
		x /= 2;
	}
	int n = bin.length();
	while (n < 32)
	{
		bin = " " + bin;
		bin[0] = '0';
		n++;
	}
	return bin;
}

string DecToBin(BigInt x)
{
	string bin = "";
	for (int i = 0; i < 4; i++)
	{
		//cout <<i << " " << DecimalToBinary(x.data[i]) << endl;
		bin = bin + DecimalToBinary(x.data[i]);
	}
	while (bin[0] == '0')
	{
		bin.erase(bin.begin());
	}
	return bin;
}

string BinToHex(string bit)
{
	char chuoi[] = "0123456789ABCDEF";
	string temp = "", hex = "";
	int n = bit.length(), chiSo = 0;
	while (n % 4 != 0)
	{
		bit = "0" + bit;
		n++;
	}
	//cout << bin << endl;
	for (int i = 0; i < n; i++)
	{
		chiSo = 0;
		for (int j = 0; j < 4; j++)
		{
			temp += bit[i];
			chiSo += (bit[i] - '0')*pow(2, 3 - j);
			//cout << i << " " << bin[i] << " " << chiSo << endl;
			i++;
		}
		i--;
		hex.push_back(chuoi[chiSo]);
	}
	return hex;
}

string Nhan2(string a)
{
	int n = a.length(), nho = 0;
	for (int i = n - 1; i > -1; i--)
	{
		a[i] = (a[i] - '0') * 2 + nho;
		nho = a[i] / 10;
		a[i] = a[i] % 10 + '0';
	}
	if (nho != 0)
	{
		a = " " + a;
		a[0] = nho + '0';
	}
	return a;
}

string HaiMuX(int n)
{
	string a = "2";
	if (n == 0)
		return "1";
	for (int i = 1; i < n; i++)
	{
		a = Nhan2(a);
	}
	return a;
}

string Cong(string a, string b)
{
	string x = "";
	int n = a.length(),
		m = b.length(),
		soNho = 0;
	int chenhLenh = n - m;
	if (chenhLenh > 0)
	{
		for (int i = 0; i < chenhLenh; i++)
		{
			b = "0" + b;
		}
	}
	else if (chenhLenh < 0)
	{
		n = m;//Cập nhật lại n
		for (int i = 0; i < -chenhLenh; i++)
		{
			a = "0" + a;
		}
	}
	for (int i = n - 1; i > -1; i--)
	{
		x = " " + x;
		x[0] = a[i] - '0' + (b[i] - '0') + soNho;
		soNho = x[0] / 10;
		x[0] = x[0] % 10 + '0';
		//cout << "x[" << n - 1 - i << "] = " << x[n - 1 - i] % 10  << endl;
	}
	if (soNho != 0)
	{
		x = " " + x;
		x[0] = soNho + '0';
	}
	return x;
}

BigInt BinToDec(string bit)
{
	BigInt a;
	string dec, temp = "";
	int n = bit.length();
	while (n < 127)
	{
		n++;
		bit = "0" + bit;
	}
	if (bit[0] == '1')
	{
		bit[0] = '0';
		temp = "-";
	}
	for (int i = 0; i < n; i++)
	{
		if (bit[i] == '1')
		{
			dec = Cong(dec, HaiMuX(n - 1 - i));
		}
	}
	dec = temp + dec;
	cout << dec;
	DecimalToBigInt(a, dec);
	return a;
}

string DecToHex(BigInt x)
{
	return BinToHex(DecToBin(x));
}


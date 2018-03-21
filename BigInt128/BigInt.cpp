#include "BigInt.h"

//Nhóm hàm theo Project
void ScanBigInt(BigInt &x, string temp, int base)
{
	switch (base)
	{
	case 10:
		DecimalToBigInt(x, temp);
		break;
	case 16:
		HexadecimalToBigInt(x, temp);
		break;
	case 2:
		BinaryToBigInt(x, temp);
		break;
	default:
		break;
	}
}

void PrintBigInt(BigInt & x, int base)
{

}

string DecToBin(BigInt x)
{
	string bin = "";
	for (int i = 0; i < 4; i++)
	{
		bin = bin + DecimalToBinary(x.data[i]);
	}
	while (bin[0] == '0')
	{
		bin.erase(bin.begin());
	}
	return bin;
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
	DecimalToBigInt(a, dec);
	return a;
}

string BinToHex(string bit)
{
	map<string, char> BiToHex;
	{
		BiToHex["0000"] = '0'; BiToHex["0001"] = '1'; BiToHex["0010"] = '2'; BiToHex["0011"] = '3';
		BiToHex["0100"] = '4'; BiToHex["0101"] = '5'; BiToHex["0110"] = '6'; BiToHex["0111"] = '7';
		BiToHex["1000"] = '8'; BiToHex["1001"] = '9'; BiToHex["1010"] = 'A'; BiToHex["1011"] = 'B';
		BiToHex["1100"] = 'C'; BiToHex["1101"] = 'D'; BiToHex["1110"] = 'E'; BiToHex["1111"] = 'F';
	}

	string temp, hex = "";
	int n = bit.length(), id = 0;
	while (n % 4 != 0)
	{
		bit = "0" + bit;
		n++;
	}
	while (id < n)
	{
		temp = bit.substr(id, 4);
		hex.push_back(BiToHex[temp]);
		id += 4;
	}
	return hex;
}

string DecToHex(BigInt x)
{
	return BinToHex(DecToBin(x));
}


//Nhóm hàm phục vụ chuyển đổi
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
	int n, temp = 0;
	while (a.length() != b.length())
	{
		if (a.length() < b.length())
			a = '0' + a;
		if (a.length() > b.length())
			b = '0' + b;
	}
	n = a.length();
	for (int i = n - 1; i >= 0; i--)
	{
		x = " " + x;
		x[0] = a[i] - '0' + (b[i] - '0') + temp;
		temp = x[0] / 10;
		x[0] = x[0] % 10 + '0';
	}
	if (temp > 0)
	{
		x = " " + x;
		x[0] = temp + '0';
	}
	return x;
}

void Bu2(BigInt &a)
{
	int ID, bitID, j = 127;

	while (true)
	{
		unsigned int temp;
		ID = j / 32;
		bitID = 31 - j % 32;
		if ((a.data[ID] >> bitID) & 1 == 1)
			break;
		j--;
	}
	j--;
	for (j; j >= 0; j--)
	{
		ID = j / 32;
		bitID = 31 - j % 32;
		a.data[ID] = (1 << bitID) ^ a.data[ID];
	}
}

string ChuanHoa(string bit)
{
	while (bit.length() < 128)
	{
		bit = "0" + bit;
	}
	return bit;
}

//base to BigInt
void DecimalToBigInt(BigInt &a, string dec)
{
	int n, chiSo, vitriBit;
	bool check = true;

	if (dec[0] == '-')
	{
		check = false;
		dec.erase(dec.begin());
	}
	n = dec.length();

	for (int i = 127;; i--)
	{
		if (n == 0) break;
		
		chiSo = i / 32;
		vitriBit = 31 - i % 32;

		if ((dec[n - 1] - '0') % 2 == 1)
		{
			if (chiSo < 0 || (chiSo == 0 && vitriBit == 31))
			{
				cout << "So qua lon.";
				return;
			}
			a.data[chiSo] = a.data[chiSo] | (1 << vitriBit);
		}
		dec = Chia2(dec);
		n = dec.length();
	}
	if (!check)
		Bu2(a);
}

void BinaryToBigInt(BigInt & a, string dec)
{
	int n = dec.length();
	int ID, bitID;
	for (int i = 127;; i--)
	{
		if (n == 0)
			break;
		ID = i / 32;
		bitID = 31 - i % 32;
		if (dec[n-1] == '1')
		{
			a.data[ID] = a.data[ID] | (1 << bitID);
		}
		n--;
	}
}

void HexadecimalToBigInt(BigInt & a, string dec)
{
	string bin = "";
	map<char, string> HexToBi;
	{
		HexToBi['0'] = "0000"; HexToBi['1'] = "0001"; HexToBi['2'] = "0010"; HexToBi['3'] = "0011";
		HexToBi['4'] = "0100"; HexToBi['5'] = "0101"; HexToBi['6'] = "0110"; HexToBi['7'] = "0111";
		HexToBi['8'] = "1000"; HexToBi['9'] = "1001"; HexToBi['A'] = "1010"; HexToBi['B'] = "1011";
		HexToBi['C'] = "1100"; HexToBi['D'] = "1101"; HexToBi['E'] = "1110"; HexToBi['F'] = "1111";
	}
	for (int i = 0; i < dec.length(); i++)
		bin += HexToBi[dec[i]];
	BinaryToBigInt(a, bin);
}


string DecimalToBinary(unsigned int x)
{
	string bin = "";
	while (x != 0)
	{
		if (x % 2 == 1)
			bin = '1' + bin;
		else
			bin = '0' + bin;
		x /= 2;
	}
	int n = bin.length();
	while (n < 32)
	{
		bin = '0' + bin;
		n++;
	}
	return bin;
}

string BinaryToDecimal(string bit)
{
	string dec, temp = "";
	int n;
	bit = ChuanHoa(bit);
	//Neu la so am chuyen ve so duong bang cach lay bu 2
	if (bit[0] == '1')
	{
		BigInt tmp;
		BinaryToBigInt(tmp, bit);
		Bu2(tmp);
		bit = DecToBin(tmp);
		temp = "-";
	}
	n = bit.length();
	for (int i = 0; i < n; i++)
	{
		if (bit[i] == '1')
		{
			dec = Cong(dec, HaiMuX(n - 1 - i));
		}
	}
	dec = temp + dec;
	if (dec == "")
		dec = "0";
	return dec;
}

//Các phép toán +, -, *, /
BigInt operator+ (BigInt a, BigInt b)
{
	int temp = 0, ID, bitID, bitA, bitB, sum;
	string result = "";
	BigInt res;
	for (ID = 3; ID >= 0; ID--)
		for (bitID = 0; bitID < 32; bitID++)
		{
			bitA = (a.data[ID] >> bitID) & 1;
			bitB = (b.data[ID] >> bitID) & 1;
			sum = bitA + bitB + temp;
			if (sum == 2)
				sum = 10;
			else if (sum == 3)
				sum = 11;
			char c = (sum % 10) + 48;
			result = c + result;
			temp = sum / 10;
		}
	while (result[0] == '0')
		result.erase(result.begin());
	if (result.length() == 0)
		result = "0";
	BinaryToBigInt(res, result);
	return res;
}

BigInt operator-(BigInt a, BigInt b)
{
	BigInt bu2 = b;
	Bu2(bu2);
	return a + bu2;
}

BigInt operator*(BigInt a, BigInt b)
{
	return BigInt();
}

BigInt operator/(BigInt a, BigInt b)//Chia số a cho số b
{
	return BigInt();
}

//Nhóm phép toán trên bit
BigInt operator& (BigInt a, BigInt b)
{
	BigInt res;
	for (int i = 0; i < 4; i++)
		res.data[i] = a.data[i] & b.data[i];
	return res;
}

BigInt operator|(BigInt a, BigInt b)
{
	BigInt res;
	for (int i = 0; i < 4; i++)
		res.data[i] = a.data[i] | b.data[i];
	return res;
}

BigInt operator^(BigInt a, BigInt b)
{
	BigInt res;
	for (int i = 0; i < 4; i++)
		res.data[i] = a.data[i] ^ b.data[i];
	return res;
}

BigInt operator~(BigInt a)
{
	BigInt res = a;
	int ID, bitID;
	for (int j = 127; j >= 0; j--)
	{
		ID = j / 32;
		bitID = 31 - j % 32;
		res.data[ID] = (1 << bitID) ^ res.data[ID];
	}
	return res;
}

BigInt operator << (BigInt a, int n) {
	string temp = ChuanHoa(DecToBin(a));

	if (n <= 128 && n >= 0) {
		temp = temp.substr(n, 128 - n);
		for (int i = 0; i < n; i++)
			temp += '0';
		return BinToDec(temp);
	}
	return a;
}

BigInt operator >> (BigInt a, int n) {

	string temp = ChuanHoa(DecToBin(a));

	if (n <= 128 && n >= 0) {
		temp = temp.substr(0, 128 - n);
		for (int i = 0; i < n; i++)
			temp = '0' + temp;
		return BinToDec(temp);
	}
	return a;
}

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

string PrintBigInt(BigInt & x, int base)
{
	switch (base)
	{
	case 10:
		return BinaryToDecimal(DecToBin(x));
	case 2:
		return DecToBin(x);
	case 16:
		return DecToHex(x);
	default:
		return "";
	}
}

string DecToBin(BigInt x)
{
	string bin = "";
	for (int i = 0; i < 4; i++)
	{
		bin += DecimalToBinary(x.data[i]);
	}
	while (bin[0] == '0')
	{
		bin.erase(bin.begin());
	}
	if (bin == "")
		bin = "0";
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
		bit = "0" + bit;
	return bit;
}

//base to BigInt
void DecimalToBigInt(BigInt &a, string dec)
{
	int n, ID, bitID;
	bool check = true;
	
	a =  BigInt();

	if (dec[0] == '-')
	{
		check = false;
		dec.erase(dec.begin());
	}
	n = dec.length();

	for (int i = 127;; i--)
	{
		if (n == 0) break;
		
		ID = i / 32;
		bitID = 31 - i % 32;

		if ((dec[n - 1] - '0') % 2 == 1)
		{
			if (ID < 0 || (ID == 0 && bitID >= 31 && check))
			{
				cout << "So qua lon.";
				a = BigInt();
				return;
			}
			a.data[ID] = a.data[ID] | (1 << bitID);
		}
		dec = Chia2(dec);
		n = dec.length();
	}
	if (!check)
		Bu2(a);
}

void BinaryToBigInt(BigInt & a, string dec)
{
	int ID, bitID,n = dec.length();
	a = BigInt();

	for (int i = 127;; i--)
	{
		if (n == 0) break;
		ID = i / 32;
		bitID = 31 - i % 32;
		if (dec[n-1] == '1')
			a.data[ID] = a.data[ID] | (1 << bitID);
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
	while (bin.length() < 32)
		bin = '0' + bin;

	return bin;
}

string BinaryToDecimal(string bit)
{
	string dec, temp = "";
	int n;
	bit = ChuanHoa(bit);
	//Neu la so am chuyen ve so duong bang cach lay bu 2 sau do gan dau - cho ket qua
	if (bit[0] == '1')
	{
		BigInt tmp;
		BinaryToBigInt(tmp, bit);
		Bu2(tmp);
		bit = DecToBin(tmp);
		temp = "-";
	}
	n = bit.length();
	for (int i = 0; i < bit.length(); i++)
	{
		if (bit[i] == '1')
			dec = Cong(dec, HaiMuX(n - 1 - i));
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
	/*while (result[0] == '0')
		result.erase(result.begin());*/
	if (result == "")
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
	BigInt result, temp1;
	//temp1 để chứa số để cộng thêm vô result
	int truongHop = 0, nB, chiSo = 0;
	string binA = DecToBin(a),
		binB = DecToBin(b);
	if (binA.length() < 128)
		binA = "0" + binA;
	if (binB.length() < 128)
		binB = "0" + binB;
	//Xét trường hợp. Trường hợp = 0 thì hai số khác dấu, khác 0 là hai số cùng dấu
	if (binB[0] == '0')
	{
		truongHop += 1;
		binB.erase(binB.begin());
	}
	else
	{
		truongHop -= 1;
		string decB = BinaryToDecimal(binB);
		decB.erase(decB.begin());
		DecimalToBigInt(b, decB);
		binB = DecToBin(b);
	}
	if (binA[0] == '0')
	{
		truongHop += 1;
		binA.erase(binA.begin());
	}
	else
	{
		string decA = BinaryToDecimal(binA);
		decA.erase(decA.begin());
		DecimalToBigInt(a, decA);
		binA = DecToBin(a);
	}
	//Nhân theo kiểu nhân hai số thập phân.
	nB = binB.length();
	while (chiSo < nB)
	{
		string temp = binA;
		if (binB[chiSo] == '1')
		{
			for (int i = 0; i < nB - 1 - chiSo; i++)
				temp = temp + "0";
			//DecimalToBigInt(temp1, BinaryToDecimal(temp));
			BinaryToBigInt(temp1, temp);
			result = result + temp1;
		}
		chiSo++;
	}
	if (truongHop != 0)
		return result;
	else
	{
		string decRes = BinaryToDecimal(DecToBin(result));
		decRes = "-" + decRes;
		DecimalToBigInt(result, decRes);
		return result;
	}
	/*
	// Nhân Booth
	BigInt res, bigA;
	string AQ, A, Q = DecToBin(a), Qt1 = "0", M = DecToBin(b);
	int n, k;
	//Khởi tạo
	while (Q.length() < M.length())
		Q = '0' + Q;
	while (M.length() < Q.length())
		M = '0' + M;
	n = k = Q.length();
	for (int i = 0; i < n; i++)
		A += '0';
	
	while (k > 0)
	{
		if (Q[n - 1] + Qt1 == "10")
		{
			BinaryToBigInt(bigA, A);
			A = DecToBin(bigA - b);
		}
		else if (Q[n - 1] + Qt1 == "01")
		{
			BinaryToBigInt(bigA, A);
			A = DecToBin(bigA + b);
		}
		while()
	}

	BinaryToBigInt(res, AQ);
	return res;*/
}

BigInt operator/(BigInt a, BigInt b)
{
	BigInt res, bigA;
	bool check = true;
	string A, Q = DecToBin(a), M = DecToBin(b);
	string temp;
	int n, k;

	//chuyen ve so duong het
	if ((Q.length() == 128 && Q[0] == '1' && (M.length() < 128 || (M.length() == 128 && M[0] == '0'))))
	{
		check = false;
		Bu2(a);
		Q = DecToBin(a);
	}
	if ((M.length() == 128 && M[0] == '1' && (Q.length() < 128 || (Q.length() == 128 && Q[0] == '0'))))
	{
		check = false;
		Bu2(b);
		M = DecToBin(b);
	}
	if (M.length() == 128 && M[0] == '1' && Q.length() == 128 && Q[0] == '1')
	{
		Bu2(a);
		Q = DecToBin(a);
		Bu2(b);
		M = DecToBin(b);
	}

	temp = DecToBin(a - b);
	if (temp[0] == '1' && temp.length() == 128)
		return res;
	n = Q.length();
	k = n;
	//Khởi tạo (vi mac dinh Q, M > 0 do o buoc tren thuc hien nen A = '0..0')
	for (int i = 0; i < n; i++)
		A += '0';
	while (k > 0)
	{
		A = A.substr(1, n - 1) + Q[0];
		Q = Q.substr(1, n - 1) + '0';
		BinaryToBigInt(bigA, A);
		A = DecToBin(bigA - b);
		if (A.length() == 128 && A[0] == '1')
		{
			Q[n-1] = '0';
			BinaryToBigInt(bigA, A);
			A = DecToBin(bigA + b);
		}
		else
			Q[n - 1] = '1';
		while (A.length() < n)
			A = "0" + A;
		k--;
	}
	BinaryToBigInt(res, Q);
	if (!check)
		Bu2(res);
	return res;
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
	for (int i = 0; i < 4; i++)
		res.data[i] = ~res.data[i];
	return res;
}

BigInt operator << (BigInt a, int n) 
{
	string temp = ChuanHoa(DecToBin(a));
	n = n < 0 ? 0 : n;
	n = n > 128 ? 128 : n;

	temp = temp.substr(n, 128 - n);
	for (int i = 0; i < n; i++)
		temp += '0';
	return BinToDec(temp);
}

BigInt operator >> (BigInt a, int n) 
{
	string temp = ChuanHoa(DecToBin(a));
	n = n < 0 ? 0 : n;
	n = n > 128 ? 128 : n;
	temp = temp.substr(0, 128 - n);
	for (int i = 0; i < n; i++)
		temp = '0' + temp;
	return BinToDec(temp);
}

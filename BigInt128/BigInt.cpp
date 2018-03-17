#include "BigInt.h"
#include <map>

void ScanBigInt(BigInt &x, string temp)
{
	DecimalToBigInt(x, temp);
}

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

void DecimalToBigInt(BigInt &a, string dec)
{
	int n, chiSo;
	int vitriBit;
	string h = "";
	if (dec[0] == '-')
	{
		dec.erase(dec.begin());
		a.data[0] = a.data[0] | (1 << (31));
	}
	n = dec.length();
	for (int i = 127;; i--)
	{
		if (n == 0) break;
		if ((dec[n - 1] - '0') % 2 == 1)
		{
			chiSo = i / 32;
			vitriBit = 31 - i % 32;
			if (chiSo < 0 || (chiSo == 0 && vitriBit == 31))
			{
				cout << "So qua lon.";
				return;
			}
			a.data[chiSo] = a.data[chiSo] | (1 << vitriBit);
			//h = "1" + h;
		}
		//else
			//h = "0" + h;
		dec = Chia2(dec);
		n = dec.length();
	}
	cout << h << endl;
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

string ChuanHoa(string bit)
{
	if (bit.length() < 127)
	{
		bit = "0" + bit;
	}
	return bit;
}

string BinToDec_string(string bit)
{
	string dec, temp = "";
	bit = ChuanHoa(bit);
	int n = bit.length();
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
	if (dec == "")
		dec = "0";
	return dec;
}


BigInt operator+(BigInt a, BigInt b)
{
	BigInt sum;
	string binA = ChuanHoa(DecToBin(a)),
		binB = ChuanHoa(DecToBin(b)),
		tong;
	if (binA[0] == '0' && binB[0] == '0')//Hai số Dương
		tong = Cong(BinToDec_string(binA), BinToDec_string(binB));
	else if (binA[0] == '1' && binB[0] == '1')//Hai số Âm
	{
		binA[0] = '0'; binB[0] = '0';
		tong = Cong(BinToDec_string(binA), BinToDec_string(binB));
		tong = "-" + tong;
	}
	else//Một số âm
	{
		if (binA[0] == '1') //a âm
		{
			binA[0] = '0';
			a = BinToDec(binA);
			return b - a;
		}
		binB[0] = '0';
		b = BinToDec(binB);
		return a - b;
	}
	DecimalToBigInt(sum, tong);
	return sum;
}

BigInt operator-(BigInt a, BigInt b)
{
	string binA = ChuanHoa(DecToBin(a)),
		binB = ChuanHoa(DecToBin(b));
	if (binA[0] != '1' && binB[0] == '1')
	{
		//a > 0 và b  < 0
		binB[0] = '0';
		b = BinToDec(binB);
		//BinToDec(DecToBin(b));
		return a + b;
	}
	if (binA[0] == '1'&& binB[0] != '1')
	{
		//a < 0 và b > 0
		int n = binB.length();
		while (n < 127)
		{
			binB = "0" + binB;
			n++;
		}
		binB[0] = '1';
		DecimalToBigInt(b, BinToDec_string(binB));
		return a + b;
	}
	else // Trường hợp số sau lớn hơn số đầu trừ ra âm
	{
		BigInt hieu;
		binA[0] = '0'; binB[0] = '0';
		string decA = BinToDec_string(binA),
			decB = BinToDec_string(binB), tru = "";
		int nA = decA.length(), nB = decB.length(),
			soNho = 0;
		while (nA < nB)
		{
			decA = "0" + decA;
			nA++;
		}
		while (nB < nA)
		{
			decB = "0" + decB;
			nB++;
		}
		if (decA >= decB)
		{
			for (int i = nA - 1; i > -1; i--)
			{
				tru = " " + tru;
				tru[0] = decA[i] - decB[i] - soNho + '0';
				if (tru[0] < '0')
				{
					tru[0] = tru[0] + 10;
					soNho = 1;
				}
				else soNho = 0;
			}
		}
		else
		{
			for (int i = nA - 1; i > -1; i--)
			{
				tru = " " + tru;
				tru[0] = decB[i] - decA[i] - soNho + '0';
				if (tru[0] < '0')
				{
					tru[0] = tru[0] + 10;
					soNho = 1;
				}
				else soNho = 0;
			}
			tru = "-" + tru;
		}
		while (tru[0] == '0')
			tru.erase(tru.begin());
		//cout << tru;
		DecimalToBigInt(hieu, tru);
		return hieu;
	}
}

string NhanVsX(char so_nhan, string chuoi_nhan)
{
	int soNho = 0, n = chuoi_nhan.length();
	string result = "";
	for (int i = n - 1; i > -1; i--)
	{
		result = " " + result;
		result[0] = (chuoi_nhan[i] - '0')*(so_nhan - '0') + soNho;
		soNho = result[0] / 10;
		result[0] = result[0] % 10 + '0';
	}
	if (soNho != 0)
	{
		result = " " + result;
		result[0] = soNho + '0';
	}
	return result;
}

BigInt operator*(BigInt a, BigInt b)
{
	string temp;//string dạng decimal
	BigInt tich, temp1;
	string decA = BinToDec_string(DecToBin(a)),
		decB = BinToDec_string(DecToBin(b));
	int kqua = 1;
	if (decA == "0" || decB == "0")
		return tich;
	if (decA[0] != decB[0])//Xử lý số âm. Nếu có âm thì ghi lại và chuyển số âm qua số dương
	{
		if (decA[0] == '-')
		{
			decA.erase(decA.begin());
			while (decA[0] == '0')
				decA.erase(decA.begin());
			kqua = -1;
		}
		else if (decB[0] == '-')
		{
			kqua = -1;
			decB.erase(decB.begin());
			while (decA[0] == '0')
				decB.erase(decB.begin());
		}
	}
	int n = decB.length();
	for (int i = n - 1; i > -1; i--) //Nhân hai số decimal
	{
		temp = NhanVsX(decB[i], decA);
		for (int j = 0; j < n - 1 - i; j++)
			temp += "0";
		DecimalToBigInt(temp1, temp);
		tich = tich + temp1;
	}
	if (kqua == -1)//Nếu có 1 số âm
	{
		tich.data[0] = tich.data[0] | (1 << 31); //Bật bit đầu tiên của BigInt tich lên.
	}
	return tich;
}

BigInt operator/(BigInt a, BigInt b)//Chia số a cho số b
{
	BigInt result, _temp;
	string decA = BinToDec_string(DecToBin(a)),
		decB = BinToDec_string(DecToBin(b)),
		temp, thuong;
	if (decA.length() < decB.length() || (decA.length() == decB.length() && decA < decB))
		return result;
	//Xử lý dấu
	if (decA[0] != decB[0] && (decA[0] == '-' || decB[0] == '-'))
		thuong.push_back('-');
	if (decA[0] == '-')
		decA.erase(decA.begin());
	if (decB[0] == '-')
		decB.erase(decB.begin());
	int na = decA.length(), nb = decB.length(),
		soChia, soBiChia, thuongTemp, count = nb;
	if (na < nb || (na == nb && decA < decB))
		return result;
	for (int i = 0; i < nb; i++)
		temp.push_back(decA[i]);
	if (temp < decB)
	{
		temp.push_back(decA[nb]);
		count++;
	}
	while (count <= na)
	{
		if (temp.length() < decB.length() || (temp.length() == decB.length() && temp < decB))
			thuong.push_back('0');
		else
		{
			soChia = temp[0] - '0';
			soBiChia = decB[0] - '0';
			if (temp.length() > decB.length())
			{
				soChia = soChia * 10 + temp[1] - '0';
			}
			thuongTemp = soChia / soBiChia;
			do {
				string x = NhanVsX(thuongTemp + '0', decB);
				if (x.length() < temp.length() || (x.length() == temp.length() && x <= temp))
					break;
				thuongTemp--;
			} while (1);
			DecimalToBigInt(b, NhanVsX(thuongTemp + '0', decB));
			DecimalToBigInt(_temp, temp);
			_temp = _temp - b;
			temp = BinToDec_string(DecToBin(_temp));
			thuong.push_back(thuongTemp + '0');
		}
		while (temp[0] == '0')
			temp.erase(temp.begin());
		temp.push_back(decA[count]);
		count++;
	}
	//cout << thuong;
	DecimalToBigInt(result, thuong);
	return result;
}
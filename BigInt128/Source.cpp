#include "BigInt.h"
#include <fstream>

int main(int argc, char ** argv)
{
	fstream fIn, fOut;
	fIn.open(argv[1], ios_base::in);
	fOut.open(argv[2], ios_base::out);
	
	BigInt bNum, bNum1, bNum2;
	int p,p1, p2;
	char operate;
	string s1,s2,s3,s4;
	
	while (!fIn.eof())
	{
		bNum = BigInt();			//Có 2TH:
		bNum1 = BigInt();			//TH1 : <hệ số> p (2/10/16) <số thứ nhất> <phép tính> <số thứ 2>
		bNum2 = BigInt();			//TH2 : <hệ số 1> p1 (2/10/16) <hệ số 2>p2(2/10/16) <số>
		s4 = "";					//TH3: <hệ số>p (2/10/16) <số> <NOT>(~)
									//Luôn luôn đọc được s1, s2, s3
		fIn >> s1 >> s2 >> s3;
		if ((s3[0] < '0' || s3[0] > '9') && (s3 != "~"))
			fIn >> s4;
		cout << s1 << " " << s2 << " " << s3 << " " << s4 << endl;
			//Nếu s4 = "" thì là TH2,TH3 ngược lại là TH1
			if (s4 == "")
			{
				if (s3 != "~")
				{
					p1 = atoi(s1.c_str());//số p1
					p2 = atoi(s2.c_str());//số p2
					ScanBigInt(bNum, s3, p1);
					//chuyenHe(p1, p2) 
					fOut << PrintBigInt(bNum, p2) << endl;
				}
				else
				{
					p = atoi(s1.c_str());// số p
					ScanBigInt(bNum, s2, p);
					//ham NOT
					bNum = ~bNum;
					fOut << PrintBigInt(bNum, p) << endl;
				}
			}
			else
			{
				p = atoi(s1.c_str());//số p
				// TinhToan(p,s3, s2, s4) - s3: phep toan; s2,s4: 2 so.
				ScanBigInt(bNum1, s2, p);
				ScanBigInt(bNum2, s4, p);
				///tinh +-*/&^|
				switch (s3[0])
				{
				case '+':
					bNum = bNum1 + bNum2;
					break;
				case '-':
					bNum = bNum1 - bNum2;
					break;
				case '*':
					bNum = bNum1 * bNum2;
					break;
				case '/':
					bNum = bNum1 / bNum2;
					break;
				case '&':
					bNum = bNum1 & bNum2;
					break;
				case '|':
					bNum = bNum1 | bNum2;
					break;
				case '^':
					bNum = bNum1 ^ bNum2;
					break;
				default:
					break;
				}
				///Tinh >> <<
				if (s3 == ">>")
				{
					int temp = atoi(s4.c_str());
					bNum = bNum1 >> temp;
				}
				else if (s3 == "<<")
				{
					int temp = atoi(s4.c_str());
					bNum = bNum1 << temp;
				}
				fOut << PrintBigInt(bNum, p) << endl;
			}
	}
	fIn.close();
	fOut.close();
	return 0;
}

//int main(int argc, char * argv[])
//{
//	//= "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
//	BigInt bNum, bN1, bN2;
//	string s = "1",s1,s2;
//	//cout << BinaryToDecimal("01111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111") << endl;
//	//cout << BinaryToDecimal("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000") << endl;
//
//	DecimalToBigInt(bNum, s);
//	bNum = bNum << 1;
//	cout << BinaryToDecimal(DecToBin(bNum)) << endl;
//
//	return 0;
//}
	
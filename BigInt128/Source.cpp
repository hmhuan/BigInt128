﻿#include "BigInt.h"
#include<fstream>
//sajkdhashdkjashjakshdkj
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
		//Có 2TH:
		//TH1 : <hệ số> p (2/10/16) <số thứ nhất> <phép tính> <số thứ 2>
		//TH2 : <hệ số 1>p1 (2/10/16) <hệ số 2>p2(2/10/16) <số>
		//TH3: <hệ số>p (2/10/16) <số> <NOT>(~)
		//Luôn luôn đọc được s1, s2, s3
		s4 = "";
		fIn >> s1 >> s2 >> s3;
		if ((s3[0] < '0' || s3[0] > '9') && (s3 != "~"))
			fIn >> s4;
		cout << s1 << " "<< s2 << " "<< s3 << " " << s4 << endl;
		//Nếu s4 = "" thì là TH2,TH3 ngược lại là TH1
		if (s4 == "")
		{
			p1 = atoi(s1.c_str());//số p1
			p2 = atoi(s2.c_str());//số p2
			// chuyenHe(p1, p2) 
			//--> ghi ra file
		}
		else
		{
			p = atoi(s1.c_str());//số p
			// TinhToan(p,s3, s2, s4) - s3: phep toan; s2,s4: 2 so.
			//--> ghi ra file
		}
	}

	fIn.close();
	fOut.close();
	return 0;
}
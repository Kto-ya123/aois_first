#include<iostream>
#include<iomanip>


const int arr1[8] = { 0,0,0,0,0,0,0,0 };
const int arr2[8] = { 0,0,0,0,0,0,0,1 };


#define NULLDIG  arr1
#define ONEDIG  arr2



using namespace std;



void sumInStraightCode(const int* arr_1, const int* arr_2, int* arr_rez);
void sumInReverseCode(const int* arr_1, const int* arr_2, int* arr_rez);
void sumInAdditCode(const int* arr_1, const int* arr_2, int* arr_rez);
bool comparEqBinStraightAbs(const int* arr_1, const int* arr_2);
void trans_bin(int val, int* arr)
{
	if (val < 0)
	{
		arr[0]++;
		val *= -1;
	}
	for (int i(7); val; i--)
	{
		arr[i] = val % 2;
		val /= 2;
	}
}
void trans_reverse(int val, int* arr)
{
	if (val < 0)
	{
		trans_bin(val, arr);
		for (int i(1); i < 8; i++)
		{
			if (arr[i] == 0)
			{
				arr[i] = 1;
			}
			else
			{
				arr[i] = 0;
			}
		}
	}
	else
	{
		trans_bin(val, arr);
	}
}
void trans_addit(int val, int* arr)
{

	trans_reverse(val, arr);
	if (val < 0)
	{
		int arr_rezult[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		int arr_one[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };
		sumInAdditCode(arr, arr_one, arr_rezult);
		for (int i(0); i < 8; i++)
		{
			arr[i] = arr_rezult[i];
		}
	}


}
void rezInStraightCode(const int* arr_1, const int* arr_2, int* arr_rez);
bool comparMoreBinStraightAbs(const int* arr_1, const int* arr_2);
bool comparMoreEqBinStraightAbs(const int* arr_1, const int* arr_2);
void eqOper(int* arr_1, const int* arr_2)
{
	for (int i(0); i < 8; i++)
	{
		arr_1[i] = arr_2[i];
	}
}
void sdvig(int* arr_rez)
{
	for (int i(1); i < 7; i++)
	{
		arr_rez[i] = arr_rez[i + 1];
	}
	arr_rez[7] = 0;
}
void divBinCode(const int* arr_1, const int* arr_2,int* arr_rezult_wh, int* arr_rezult_fr)
{
	if (arr_1[0] != arr_2[0])
		arr_rezult_wh++;
	int arrMidRez[8] = { 0,0,0,0,0,0,0,0 };
	int arr2Dup[8] = { 0,0,0,0,0,0,0,0 };
	int arr1Dup[8] = { 0,0,0,0,0,0,0,0 };
	
	eqOper(arr1Dup, arr_1);
	eqOper(arr2Dup, arr_2);
	
	int arr1First = 0;
	int arr2First = 0;

	for (int i(0); i < 8; i++)
	{
		if (!arr1First)
		{
			if (arr_1[i])
				arr1First = i;
		}
		if (!arr2First)
		{
			if (arr_2[i])
				arr2First = i;
		}
	}
	for (int i(abs(arr1First - arr2First)); i >= 0; i--)
	{
		sdvig(arr_rezult_wh);
		for (int j(0); j < i; j++)
			sdvig(arr2Dup);
		if (comparMoreEqBinStraightAbs(arr1Dup, arr2Dup))
		{
			sumInStraightCode(arr_rezult_wh, ONEDIG, arrMidRez);
			eqOper(arr_rezult_wh, arrMidRez);
			eqOper(arrMidRez, NULLDIG);
			rezInStraightCode(arr1Dup, arr2Dup, arrMidRez);
			eqOper(arr1Dup, arrMidRez);
			eqOper(arrMidRez, NULLDIG);			
		}
		eqOper(arr2Dup, arr_2);
	}
	int first_dig = -1;
	while (!comparEqBinStraightAbs(arr1Dup, NULLDIG))
	{
		while (!comparMoreEqBinStraightAbs(arr1Dup, arr2Dup))
		{
			sdvig(arr1Dup);
			if (first_dig >= 4)
				return;
			first_dig++;
		}
		arr_rezult_fr[first_dig]++;
		rezInStraightCode(arr1Dup, arr2Dup, arrMidRez);
		eqOper(arr1Dup, arrMidRez);
		eqOper(arrMidRez, NULLDIG);
	}

}
void multiInBinCode(const int* arr_1, const int* arr_2, int* arr_rezult)
{
	int arrMidRezult[8] = {0,0,0,0,0,0,0,0};
	int arrNeedRez[8] = { 0,0,0,0,0,0,0,0 };
	arr_rezult[0]++;

	for (int i(7); i >= 0; i--)
	{
		for (int j(7); j - (7 - i); j--)
		{
			arrMidRezult[j - (7 - i)] = arr_1[j] * arr_2[i];
		}

		sumInAdditCode(arrMidRezult, arr_rezult, arrNeedRez);

		for (int j(0); j < 8; j++)
		{
			arr_rezult[j] = arrNeedRez[j];
			arrNeedRez[j] = 0;
			arrMidRezult[j] = 0;
		}
	}
}
void sumInAdditCode(const int* arr_1, const int* arr_2, int* arr_rez)
{
		for (int i(7); i >= 0 ; i--)
		{
			arr_rez[i] += arr_1[i] + arr_2[i];
			if (arr_rez[i] >= 2)
			{
				arr_rez[i] -= 2;
				if (i)
					arr_rez[i - 1]++;
			}
		}
}
void sumInReverseCode(const int* arr_1, const int* arr_2, int* arr_rez)
{
		for (int i(7); i >= 0; i--)
		{
			arr_rez[i] += arr_1[i] + arr_2[i];
			if (arr_rez[i] >= 2)
			{
				arr_rez[i] -= 2;
				if (i)
					arr_rez[i - 1]++;
				else
					arr_rez[7]++;
			}
		}
		for (int i(7); i >= 0; i--)
		{
			if (arr_rez[i] >= 2)
			{
				arr_rez[i] -= 2;
				arr_rez[i - 1]++;
			}
		}
	
}
bool comparEqBinStraightAbs(const int* arr_1,const int* arr_2)
{
	for (int i(1); i < 8; i++)
	{
		if (arr_1[i] != arr_2[i])
			return false;
	}

	return true;
}
bool comparMoreBinStraightAbs(const int* arr_1, const int* arr_2)
{
	for (int i(1); i < 8; i++)
	{
		if (arr_1[i] > arr_2[i])
			return true;
		else if (arr_1[i] == arr_2[i])
			continue;
		return false;
	}
	return false;
}
bool comparMoreEqBinStraightAbs(const int* arr_1,const  int* arr_2)
{
	for (int i(1); i < 8; i++)
	{
		if (arr_1[i] > arr_2[i])
			return true;
		else if (arr_1[i] == arr_2[i])
			continue;
		return false;
	}
	return true;
}
void rezInStraightCode(const int* arr_1, const int* arr_2, int* arr_rez)
{
	for (int i(1); i < 8; i++)
		arr_rez[i] = arr_1[i];
	for (int i(7); i; i--)
	{
		arr_rez[i] -= arr_2[i];
		if (arr_rez[i] < 0)
		{
			arr_rez[i] += 2;
			arr_rez[i - 1]--;
		}
	}
}
void sumInStraightCode(const int* arr_1, const int* arr_2, int* arr_rez)
{
	if (arr_1[0] == arr_2[0])
	{
		arr_rez[0] = arr_1[0];
		for (int i(7); i >= 0; i--)
		{
			arr_rez[i] += arr_1[i] + arr_2[i];
			if (arr_rez[i] >= 2)
			{
				arr_rez[i] -= 2;
				if (i)
					arr_rez[i - 1]++;
			}
		}
	}
	else
	{
		if (comparMoreBinStraightAbs(arr_1, arr_2))
		{
			arr_rez[0] = arr_1[0];
			rezInStraightCode(arr_1, arr_2, arr_rez);
		}
		else
		{
			arr_rez[0] = arr_2[0];
			rezInStraightCode(arr_2, arr_1, arr_rez);
		}
	}
}
void transFrDig(int value, int P,  int arr_rez[][8])
{
	P += 127;
	trans_bin(value, arr_rez[1]);
	for (int i(7); P; i--)
	{
		arr_rez[0][i] = P % 2;
		P /= 2;
	}

}
void sumFrDig(int arr_1[][8], int arr_2[][8], int arr_rez[][8])
{
	int arrMidRez[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	if (comparMoreBinStraightAbs(arr_1[0], arr_2[0]))
	{
		while (!comparEqBinStraightAbs(arr_1[0], arr_2[0]))
		{
			sdvig(arr_1[1]);
			rezInStraightCode(arr_1[0], ONEDIG, arrMidRez);
			eqOper(arr_1[0], arrMidRez);
			eqOper(arrMidRez, NULLDIG);
		}
		sumInStraightCode(arr_1[1], arr_2[1], arr_rez[1]);
		eqOper(arr_rez[0], arr_1[0]);
	}
	else if (comparMoreBinStraightAbs(arr_2[0], arr_1[0]))
	{
		while (!comparEqBinStraightAbs(arr_1[0], arr_2[0]))
		{
			sdvig(arr_2[1]);
			rezInStraightCode(arr_2[0], ONEDIG, arrMidRez);
			eqOper(arr_2[0], arrMidRez);
			eqOper(arrMidRez, NULLDIG);
		}
		sumInStraightCode(arr_1[1], arr_2[1], arr_rez[1]);
		eqOper(arr_rez[0], arr_1[0]);
	}else
	{
		sumInStraightCode(arr_1[1], arr_2[1], arr_rez[1]);
		eqOper(arr_rez[0], arr_1[0]);
	}
}

int main()
{
	const int a = -11;
	const int b = 0;
	int arr_a[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int arr_b[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int _arr_a[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int _arr_b[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int arr_rezult[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int arr_rezult_fr[5] = { 0, 0, 0, 0, 0 };
	int arr_ad[2][8] = { { 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 0} };
	int arr_bd[2][8] = { { 0, 0, 0, 0, 0, 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 } };
	int rez_arr_d[2][8] = { { 0, 0, 0, 0, 0, 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 } };

	setlocale(LC_ALL, "Russian");


	//Обратный код
	cout << "Прямой код***************************************" << endl;
	trans_bin(11, arr_a);
	trans_bin(22, arr_b);
	trans_bin(-11, _arr_a);
	trans_bin(-22, _arr_b);
	cout << "Число  11:      ";	for (int i(0); i < 8; i++)	cout << arr_a[i]; cout << endl;
	cout << "Число  22:      ";	for (int i(0); i < 8; i++)	cout << arr_b[i]; cout << endl;
	cout << "Число -11:      ";	for (int i(0); i < 8; i++)	cout << _arr_a[i]; cout << endl;
	cout << "Число -22:      ";	for (int i(0); i < 8; i++)	cout << _arr_b[i]; cout << endl;
	sumInStraightCode(arr_a, arr_b, arr_rezult);
	cout << "Число  11 + 22: ";	for (int i(0); i < 8; i++)	cout << arr_rezult[i]; cout << endl;
	eqOper(arr_rezult, NULLDIG);
	sumInStraightCode(_arr_a, arr_b, arr_rezult);
	cout << "Число -11 + 22: ";	for (int i(0); i < 8; i++)	cout << arr_rezult[i]; cout << endl;
	eqOper(arr_rezult, NULLDIG);
	sumInStraightCode(arr_a, _arr_b, arr_rezult);
	cout << "Число  11 - 22: ";	for (int i(0); i < 8; i++)	cout << arr_rezult[i]; cout << endl;
	eqOper(arr_rezult, NULLDIG);
	sumInStraightCode(_arr_a, _arr_b, arr_rezult);
	cout << "Число -11 - 22: ";	for (int i(0); i < 8; i++)	cout << arr_rezult[i]; cout << endl;
	eqOper(arr_rezult, NULLDIG);
	eqOper(arr_a, NULLDIG);
	eqOper(arr_b, NULLDIG);
	eqOper(_arr_a, NULLDIG);
	eqOper(_arr_b, NULLDIG);

	//Обратный код****************
	trans_reverse(11, arr_a);
	trans_reverse(22, arr_b);
	trans_reverse(-11, _arr_a);
	trans_reverse(-22, _arr_b);
	cout << "Обратный код****************************************" << endl;
	cout << "Число 11:        ";	for (int i(0); i < 8; i++)	cout << arr_a[i]; cout << endl;
	cout << "Число 22:        ";	for (int i(0); i < 8; i++)	cout << arr_b[i]; cout << endl;
	cout << "Число -11:       ";	for (int i(0); i < 8; i++)	cout << _arr_a[i]; cout << endl;
	cout << "Число -22:       ";	for (int i(0); i < 8; i++)	cout << _arr_b[i]; cout << endl;
	sumInReverseCode(arr_a, arr_b, arr_rezult);
	cout << "Число  11 + 22:  ";	for (int i(0); i < 8; i++)	cout << arr_rezult[i]; cout << endl;
	eqOper(arr_rezult, NULLDIG);
	sumInReverseCode(_arr_a, arr_b, arr_rezult);
	cout << "Число  -11 + 22: ";	for (int i(0); i < 8; i++)	cout << arr_rezult[i]; cout << endl;
	eqOper(arr_rezult, NULLDIG);
	sumInReverseCode(arr_a, _arr_b, arr_rezult);
	cout << "Число  11 - 22:  ";	for (int i(0); i < 8; i++)	cout << arr_rezult[i]; cout << endl;
	eqOper(arr_rezult, NULLDIG);
	sumInReverseCode(_arr_a, _arr_b, arr_rezult);
	cout << "Число  -11 - 22: ";	for (int i(0); i < 8; i++)	cout << arr_rezult[i]; cout << endl;
	eqOper(arr_rezult, NULLDIG);
	eqOper(arr_a, NULLDIG);
	eqOper(arr_b, NULLDIG);
	eqOper(_arr_a, NULLDIG);
	eqOper(_arr_b, NULLDIG);
	//Доп код********************************************
	trans_addit(11, arr_a);
	trans_addit(22, arr_b);
	trans_addit(-11, _arr_a);
	trans_addit(-22, _arr_b);
	cout << "Дополнительный код****************************************" << endl;
	cout << "Число 11:         ";	for (int i(0); i < 8; i++)	cout << arr_a[i]; cout << endl;
	cout << "Число 22:         ";	for (int i(0); i < 8; i++)	cout << arr_b[i]; cout << endl;
	cout << "Число -11:        ";	for (int i(0); i < 8; i++)	cout << _arr_a[i]; cout << endl;
	cout << "Число -22:        ";	for (int i(0); i < 8; i++)	cout << _arr_b[i]; cout << endl;
	sumInAdditCode(arr_a, arr_b, arr_rezult);
	cout << "Число  11 + 22:   ";	for (int i(0); i < 8; i++)	cout << arr_rezult[i]; cout << endl;
	eqOper(arr_rezult, NULLDIG);
	sumInAdditCode(_arr_a, arr_b, arr_rezult);
	cout << "Число  -11 + 22:  ";	for (int i(0); i < 8; i++)	cout << arr_rezult[i]; cout << endl;
	eqOper(arr_rezult, NULLDIG);
	sumInAdditCode(arr_a, _arr_b, arr_rezult);
	cout << "Число  11 - 22:   ";	for (int i(0); i < 8; i++)	cout << arr_rezult[i]; cout << endl;
	eqOper(arr_rezult, NULLDIG);
	sumInAdditCode(_arr_a, _arr_b, arr_rezult);
	cout << "Число  -11 - 22:  ";	for (int i(0); i < 8; i++)	cout << arr_rezult[i]; cout << endl;
	eqOper(arr_rezult, NULLDIG);
	eqOper(arr_a, NULLDIG);
	eqOper(arr_b, NULLDIG);
	eqOper(_arr_a, NULLDIG);
	eqOper(_arr_b, NULLDIG);

	//Умножение*******************************
	cout << "Умножение***********************************" << endl;
	trans_bin(11, arr_a);
	trans_bin(22, arr_b);
	multiInBinCode(arr_a, arr_b, arr_rezult);
	cout << "Число  11 * 22:   ";	for (int i(0); i < 8; i++)	cout << arr_rezult[i]; cout << endl;
	eqOper(arr_rezult, NULLDIG);
	divBinCode(arr_a, arr_b, arr_rezult, arr_rezult_fr);
	cout << "Число  11 / 22:   ";	for (int i(0); i < 8; i++)	cout << arr_rezult[i]; cout << '.'; for (int i(0); i < 5; i++)	cout << arr_rezult_fr[i];
	eqOper(arr_rezult, NULLDIG);
	
	transFrDig(11, -5, arr_ad);
	transFrDig(22, -4, arr_bd);
	cout << endl;
	sumFrDig(arr_ad, arr_bd,rez_arr_d); 
	cout << "Сложение дробных чисел: "; for (int i(0); i < 8; i++)	cout << rez_arr_d[0][i]; cout << ' '; for (int i(0); i < 8; i++)	cout << rez_arr_d[1][i];
	cout << endl;
	

	/*divBinCode(arr_a, arr_b, arr_rezult, arr_rezult_fr);
	transFrDig(22, -5, arr_ad);
	transFrDig(11, -4, arr_bd);
	sumFrDig(arr_ad, arr_bd, rez_arr_d);
	for (int i(0); i < 8; i++)
		cout << rez_arr_d[0][i];
	cout << ' ';
	for (int i(0); i < 8; i++)
		cout << rez_arr_d[1][i];
		*/
	system("pause");
	return 0;
}
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <unordered_map>
#include <time.h>
#include <map>
#include <vector> 
#define swap(x,y) pair<string, int> t=(x);(x)=(y);(y)=t; 
#define _CRT_SECURE_NO_WARNINGS                     //������Ե�Ԥ���붨���иĳ�_CRT_SECURE_NO_WARNINGS

using namespace std;

void sort(vector<pair<string, int>> &data, int left, int right)      //����
{
	if (right - left <= 1)
	{
		return;
	}
	int i, j, k;
	pair<string, int> tmp;
	tmp = data[left];
	i = left + 1;
	j = right - 1;
	k = left;

	while (true)
	{
		if (data[i].second < tmp.second)
		{
			swap(data[i], data[k]);
			++i;
			++k;
		}
		else if (data[i].second > tmp.second)
		{
			swap(data[i], data[j]);
			--j;
		}
		else
		{
			++i;
		}
		if (i > j)
			break;
	}
	sort(data, left, k);
	sort(data, j + 1, right);
}
int main()
{
	unsigned long start = clock();                       //��¼ʱ��
	FILE *read = fopen("input.txt", "r");                 //��ȡ�ĵ�
	if (!read)
	{
		cout << " file cannot open" << endl;
		return -1;
	}
	unordered_map<string, int> data;                    //hashmapͳ�Ƶ���

	string temp;                                         //�洢�ַ���
	char m;                                             //��ȡ�ַ�
	while ((m = fgetc(read)) && m != EOF)             //�ж��Ƿ�������ĵ�
	{
		if (m >= 'a'&&m <= 'z')
		{                                               //�ж�Сд
			temp.push_back(m);                            //�洢
			continue;
		}
		else if (m >= 'A' && m <= 'Z') {              //�жϴ�д�ַ�
			temp.push_back(m + 32);                   //�����ǣ�ת��Сд���ٴ洢
			continue;
		}
		if (m == -95 || m == -82 || m == -81 || m == '\'' || m == '-' || temp.empty()) //�ж�'��-�򡮻�
			continue;
		++data[temp];                                   //�洢������+1
		temp.clear();                                   //���
	}
	if (!temp.empty())
	{
		++data[temp];
	}
	fclose(read);                                        //�ر��ļ�
	vector<pair<string, int>> arr(data.begin(), data.end()); //��hashmap�������
	sort(arr, 0, arr.size());                              //�ļ�������

	FILE *file = fopen("output.txt", "w");                    //д��output�ļ�
	if (!file)
	{
		printf(" file cannot open\n");
		return 0;
	}
	auto x = arr.begin();
	auto y = arr.end();

	while (x != y)
	{
		fprintf(file, "%s      %d\n", x->first.c_str(), x->second); //д���ļ�
		++x;
	}
	long end = clock();
	printf(" time:%dms", (end - start));                        //�����ʱ��
	fclose(file);                                                  //�ر��ļ�
	return 0;
}



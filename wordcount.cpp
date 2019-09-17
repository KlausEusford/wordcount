#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <unordered_map>
#include <time.h>
#include <map>
#include <vector> 
#define swap(x,y) pair<string, int> t=(x);(x)=(y);(y)=t; 
#define _CRT_SECURE_NO_WARNINGS                     //或从属性的预编译定义中改成_CRT_SECURE_NO_WARNINGS

using namespace std;

void sort(vector<pair<string, int>> &data, int left, int right)      //排序
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
	unsigned long start = clock();                       //记录时间
	FILE *read = fopen("input.txt", "r");                 //读取文档
	if (!read)
	{
		cout << " file cannot open" << endl;
		return -1;
	}
	unordered_map<string, int> data;                    //hashmap统计单词

	string temp;                                         //存储字符串
	char m;                                             //读取字符
	while ((m = fgetc(read)) && m != EOF)             //判断是否遍历完文档
	{
		if (m >= 'a'&&m <= 'z')
		{                                               //判断小写
			temp.push_back(m);                            //存储
			continue;
		}
		else if (m >= 'A' && m <= 'Z') {              //判断大写字符
			temp.push_back(m + 32);                   //若不是，转成小写，再存储
			continue;
		}
		if (m == -95 || m == -82 || m == -81 || m == '\'' || m == '-' || temp.empty()) //判断'或-或‘或’
			continue;
		++data[temp];                                   //存储，并且+1
		temp.clear();                                   //清空
	}
	if (!temp.empty())
	{
		++data[temp];
	}
	fclose(read);                                        //关闭文件
	vector<pair<string, int>> arr(data.begin(), data.end()); //从hashmap变成数组
	sort(arr, 0, arr.size());                              //文件中排序

	FILE *file = fopen("output.txt", "w");                    //写入output文件
	if (!file)
	{
		printf(" file cannot open\n");
		return 0;
	}
	auto x = arr.begin();
	auto y = arr.end();

	while (x != y)
	{
		fprintf(file, "%s      %d\n", x->first.c_str(), x->second); //写入文件
		++x;
	}
	long end = clock();
	printf(" time:%dms", (end - start));                        //输出总时间
	fclose(file);                                                  //关闭文件
	return 0;
}



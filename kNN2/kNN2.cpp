#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <array>
#include <unordered_map>
#include <filesystem>

#include <pe-parse/parse.h>

using namespace std;

// 非常规的指令序列
const int suspicious_instruction_sequence = 0;
// 导入表有可疑函数
const int suspicious_import_table = 1;
// 文件加壳加花等
const int irregular_file_format = 2;


struct data {
  int featNum;  // ID,无大用
  array<char, 3> feature;
  string label;  //标签（black white suspicious）
};

int main()
{ 
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}

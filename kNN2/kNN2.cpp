#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <array>
#include <unordered_map>
#include <filesystem>
#include <atomic>

#include <pe-parse/parse.h>
//https://yara.readthedocs.io/en/stable/capi.html
#include <yara.h>

using namespace std;

// 选取几维特征
constexpr int feature_count = 4;

// 非常规的指令序列
const int suspicious_instruction_sequence = 0;
// 导入表有可疑函数
const int suspicious_import_table = 1;
// 文件加壳加花等
const int irregular_file_format = 2;
// C# java这种虚拟机语言咋搞呢
const int is_virtual_machine_code = 3;



// 每次yr_rules_scan_file记得清0
static atomic<int> matched_count = 0;

struct data {
  int featNum;  // ID,无大用
  array<char, feature_count> feature;
  string label;  //标签（black white suspicious）
};

int callback_function_forfile(YR_SCAN_CONTEXT* context,int message, void* message_data,
                              void* user_data) {
  if (!message_data) return CALLBACK_MSG_SCAN_FINISHED;
  if (message == CALLBACK_MSG_RULE_MATCHING) {
    YR_RULE* rule = (YR_RULE*)message_data;
    // 打印匹配到的规则名
    //printf("matched: %s\n", rule->identifier);
    matched_count++;
    return CALLBACK_ABORT;
  }
  return CALLBACK_CONTINUE;
}

int main() {
  assert(yr_initialize() == ERROR_SUCCESS);

  YR_COMPILER* compiler;
  assert(yr_compiler_create(&compiler) == ERROR_SUCCESS);

  FILE* rule = fopen("..\\my_yara_rule\\malware.yar", "r");
  assert(rule != 0);
  assert(yr_compiler_add_file(compiler, rule, NULL, NULL) == ERROR_SUCCESS);

  YR_RULES* yr_rules;
  assert(yr_compiler_get_rules(compiler, &yr_rules) == ERROR_SUCCESS);

  // 测试
  //yr_rules_scan_file(yr_rules, "..\\dataset\\win11__ntdll.dll",SCAN_FLAGS_FAST_MODE,callback_function_forfile,NULL,0);



  // 回收资源
  fclose(rule);
  yr_rules_destroy(yr_rules);
  yr_compiler_destroy(compiler);
  assert(yr_finalize() == ERROR_SUCCESS);
  return 0;
}

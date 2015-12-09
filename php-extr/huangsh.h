#ifndef _HUANGSH_H_
#define _HUANGSH_H_
#include <stdint.h>
//加载config.h，如果配置了的话
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
//加载php头文件
#include "php.h"

#define PHP_FUNCTION                ZEND_FUNCTION
#define ZEND_FUNCTION(name)         ZEND_NAMED_FUNCTION(ZEND_FN(name))
#define ZEND_NAMED_FUNCTION(name)   void name(INTERNAL_FUNCTION_PARAMETERS)
#define ZEND_FN(name)               zif_##name

#define phpext_huangsh_ptr &huangsh_module_entry
//module entry
extern zend_module_entry huangsh_module_entry;
//ZEND_MINIT_FUNCTION(hsh);
//ZEND_MSHUTDOWN_FUNCTION(hsh);
ZEND_FUNCTION(hsh__world);
ZEND_FUNCTION(hsh_long);
ZEND_FUNCTION(hsh_double);
ZEND_FUNCTION(hsh_bool);
ZEND_FUNCTION(hsh_null);
ZEND_FUNCTION(hsh_arr);
ZEND_FUNCTION(hsh_test);
// 定义一个名为huangclass的类
extern zend_class_entry *huangclass_ce;
// 常驻内存
uint32_t time_of_minit = 0;
// 
uint32_t time_of_rinit = 0;
#endif  //_HUANGSH_H_

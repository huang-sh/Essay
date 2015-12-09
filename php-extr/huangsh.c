#include "huangsh.h"
#include <stdio.h>

ZEND_FUNCTION(hsh_world)
{
    //php_printf("Hello World!\n");
    //char *str = estrdup("Hello World...");
    //RETURN_STRING(str, 0);
    //char *test = "Hello World!\n";
    //RETURN_STRING(test, 1);
    char *str;
    int strLen;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &strLen) == FAILURE)
    {
        RETURN_NULL();
    }
    RETURN_STRING(str, 0);
    //ZVAL_LONG(return_value, strLen);
}

ZEND_FUNCTION(hsh_long)
{
    long foo;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &foo) == FAILURE)
    {
        RETURN_NULL();
    }
    // RETURN_LONG(42);
    ZVAL_LONG(return_value, foo * 100);
    return;
}

ZEND_FUNCTION(hsh_double)
{
    if (return_value_used)
    {
        int i;
        array_init(return_value);
        for(i = 0; i < 10; ++i)
        {
            add_next_index_long(return_value, i);
        }
        return;
    }
    else
    {
        php_error_docref(NULL TSRMLS_CC, E_NOTICE,"猫了个咪的，我就知道你没用我的劳动成果！");
        php_printf("This Function Return");
        RETURN_NULL();
    }
    //RETURN_DOUBLE(3.141592653526);
}

ZEND_FUNCTION(hsh_null)
{
    RETURN_NULL();
}

ZEND_FUNCTION(hsh_bool)
{
    // RETURN_TRUE
    // RETURN_FALSE
    RETURN_BOOL(1);
}

ZEND_FUNCTION(hsh_arr)
{
    int name_len;
    char *name;
    zval *arr;
    zval **z_item;
    char defBeg[] = " in(";
    char defEnd[] = ")";
    // zend_parse_parameters
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa", &name, &name_len, &arr) == FAILURE) {
        RETURN_NULL();
    }
    int size = name_len * 2 + 6;
    char *str = emalloc(sizeof(char) * size);
    if (NULL == str)
    {
        RETURN_NULL();
    }
    memcpy(str, name, name_len);
    memcpy(str + name_len, defBeg, 4);
    name_len += 4;
    int arrLen = zend_hash_num_elements(Z_ARRVAL_P(arr));
    // 将数组的内部指针指向第一个单元
    zend_hash_internal_pointer_reset(Z_ARRVAL_P(arr));
    int i;
    int len = 0;
    char *key;
    int idx;
    for (i = 0; i < arrLen; ++i)
    {
        zend_hash_get_current_data(Z_ARRVAL_P(arr), (void**)&z_item);
        convert_to_string_ex(z_item);
        len = strlen(Z_STRVAL_PP(z_item));
        if (name_len + len + 1 > size)
        {
            char *new = erealloc(str, size * 2 + 1);
            if (!new) RETURN_NULL();
            size *= 2;
            str = new;
        }

        memcpy(str + name_len, Z_STRVAL_PP(z_item), len);
        name_len += len;
        if (i + 1 <  arrLen)
        {
            memcpy(str + name_len, ",", 1);
            ++name_len;
        }
        zend_hash_move_forward(Z_ARRVAL_P(arr));
    }
    if (name_len + 1 > size)
    {
        char *new = erealloc(str, size + 2);
        if (!new) RETURN_NULL();
        str = new;
    }
    memcpy(str + name_len, defEnd, 1);
    RETURN_STRING(str, 0);
}
ZEND_MINIT_FUNCTION(huangsh)
{
    ++time_of_minit;
    //返回SUCCESS代表正常，返回FALIURE就不会加载这个扩展了
    return SUCCESS;
}

/*
 * 当一个页面请求到来时候，PHP会迅速的开辟一个新的环境.
 * 并重新扫描自己的各个扩展
 * 遍历执行它们各自的RINIT方法(俗称Request Initialization)
 */
ZEND_RINIT_FUNCTION(huangsh)
{
    time_of_rinit = time(NULL);
    return SUCCESS;
}

// php脚本还未执行,php回收程序启动
ZEND_RSHUTDOWN_FUNCTION(huangsh)
{
    FILE *fp = fopen("/home/hsh/time_rshutdown", "a+");
    fprintf(fp, "%ld\n", time(NULL));
    fclose(fp);
    return SUCCESS;
}

/*
 * 当Apache通知PHP自己要Stop的时候，PHP便进入MSHUTDOWN（俗称Module Shutdown）阶段
 * 一旦PHP把ZEND_MSHUTDOWN_FUNCTION执行完,php将进入销毁程序,
 * 最好做内存回收操作
 */
ZEND_MSHUTDOWN_FUNCTION(huangsh)
{
    FILE *fp = fopen("/home/hsh/time_mshutdown", "a+");
    fprintf(fp, "$ld\n", time(NULL));
    return SUCCESS;
}

ZEND_FUNCTION(hsh_test)
{
    php_printf("%d&lt;br /&gt;", time_of_minit);
    php_printf("%d&lt;br /&gt;", time_of_rinit);
    return;
}

static zend_function_entry huangsh_functions[] = {
    ZEND_FE(hsh_world,NULL)
    ZEND_FE(hsh_long, NULL)
    ZEND_FE(hsh_double, NULL)
    ZEND_FE(hsh_bool, NULL)
    ZEND_FE(hsh_null, NULL)
    ZEND_FE(hsh_arr, NULL)
    ZEND_FE(hsh_test, NULL)
    { NULL, NULL, NULL}
};

//module entry
zend_module_entry huangsh_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
        "huangsh", //这个地方是扩展名称,往往我们会在这个地方使用一个宏.
        huangsh_functions, /* Functions */
        NULL, /* MINIT */
        NULL, /* MSHUTDOWN */
        NULL, /* RINIT */
        NULL, /* RSHUTDOWN */
        NULL, /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
        "2.1", //这个地方是我们扩展的版本
#endif
        STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_HUANGSH
ZEND_GET_MODULE(huangsh)
#endif

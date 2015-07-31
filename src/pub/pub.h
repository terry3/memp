#ifndef PUB_H
#define PUB_H

/* Public define strcut, macro. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pub_err.h" /* error code define */

#ifdef __cplusplus
extern "C"{
#endif

#define T_OK  0
#define T_ERR 1

#define T_TRUE   1
#define T_FALSE  0

/* function return type */
typedef enum E_F_RET_TYPE
{
    F_SUCCESS,
    F_FAILURE,
    F_BUTT,
}F_RET_TYPE;


/* data type */
#define T_NULL         NULL
#define T_VOID         void
typedef unsigned int   T_UINT32;
typedef int            T_INT32;
typedef unsigned short T_UINT16;
typedef short          T_INT16;
typedef unsigned char  T_UINT8;
typedef char           T_INT8;
typedef char           T_CHAR;
typedef unsigned int   F_RET;
typedef unsigned char  T_TOGGLE;


#define NULL_UINT32 0xFFFFFFFF
#define NULL_UINT16 0xFFFF
#define NULL_UINT8  0xFF
#define MEMP_MAGIC  0x1234321

/* return if p is null */
#define PN_RET_N(p) \
    if (T_NULL == (p))     \
    {                      \
  printf("[%s]:[%s]:(%d):Null pointer.\n",                              \
  __FILE__, __FUNCTION__, __LINE__);                                    \
        return;            \
    }

/* return ret if p is null */
#define PN_RET(_p, _ret) \
    if (T_NULL == (_p))      \
    {                        \
  printf("[%s]:[%s]:(%d):Null pointer.\n",                              \
  __FILE__, __FUNCTION__, __LINE__);                                    \
        return (_ret);       \
    }

#define F_NCHK_RET(_t, _d, _ret) \
    if ((_d) != (_t))            \
    {                            \
        return (_ret);           \
    }

#define F_CHK_RET(_t, _d, _ret) \
    if ((_d) == (_t))           \
    {                           \
  printf("[%s]:[%s]:(%d):Null pointer.\n",                              \
  __FILE__, __FUNCTION__, __LINE__);                                    \
        return (_ret);          \
    }

#define FR_RET(_ret) \
    if (T_OK != (_ret))         \
    {                           \
  printf("[%s]:[%s]:(%d):Null pointer.\n",                              \
  __FILE__, __FUNCTION__, __LINE__);                                    \
        return (_ret);          \
    }

#define FR_CRET(_ret, _reti)                     \
    if (F_SUCCESS != (_ret))                    \
    {                                           \
  printf("[%s]:[%s]:(%d):Null pointer.\n",      \
  __FILE__, __FUNCTION__, __LINE__);            \
        return (_reti);                         \
    }

#define FR_BRK(_ret) \
    if (T_OK != (_ret))         \
    {                           \
  printf("[%s]:[%s]:(%d):Null pointer.\n",                              \
  __FILE__, __FUNCTION__, __LINE__);                                    \
        break;                  \
    }

/*
  printf("[%s]:[%s]:(%d):Null pointer.\n",                              \
  __FILE__, __FUNCTION__, __LINE__);                                    \
*/

#define F_MEM_ALLOC(_ptr, _size, _type) \
    do{                                 \
    (_ptr) = (_type *)malloc((_size));  \
    PN_RET((_ptr), NULL_PTR);       \
    }while(0);

#define F_MEM_FREE(_ptr)  \
    do{                   \
    if(T_NULL != (_ptr)){ \
    free((_ptr));         \
    (_ptr) = T_NULL;      \
    }}while(0);

#define F_IFN_OK(_ret)    \
    if(T_OK != (_ret))

#define F_UNUSED(_var)    \
    (_var) = (_var);


/* find the right struct pointer */
#define F_GETSP(_addr, _type, _field) \
    ((_type*)((unsigned char*)(_addr) - (unsigned long)&((_type*)0)->_field))


#define F_ZERO(_addr, _size) \
    (T_VOID)memset((_addr), 0, (_size))

#define F_IS_MAGIC(_magic) \
    ((_magic) == MEMP_MAGIC)

#define F_CHK_MAGIC(_memp, _ret)                \
    if (!F_IS_MAGIC((_memp)->ul_magic)) {       \
        return (_ret);                          \
    }

#define F_CHK_MAGIC_N(_memp)                    \
    if (!F_IS_MAGIC((_memp)->ul_magic)) {       \
        return ;                                \
    }

#ifdef __cplusplus
}
#endif
#endif /* PUB_H */

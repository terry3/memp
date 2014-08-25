#ifndef PUB_ERR_H
#define PUB_ERR_H

#ifdef __cplusplus
extern "C"{
#endif

enum Pub_err
{
    PUB_ERR_BEGIN = 1,
    NULL_PTR,
    MEM_ALLOC_FAIL,
    
    MEMP_LIST_ERR_BEGIN = 100,
    MEMP_LIST_EMPTY,
    PUB_ERR_END,
};

#ifdef __cplusplus
}
#endif
#endif /* PUB_ERR_H */

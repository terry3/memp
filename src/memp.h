#ifndef MEMP_TYPE_H
#define MEMP_TYPE_H

#ifdef __cplusplus
extern "C"{
#endif

/* Memp memerory control point */
typedef void* Memp;

extern F_RET memp_create
(
    Memp      *pps_memp,
    T_UINT32   ul_init_size,
    T_UINT32   ul_grow_size
);
extern T_VOID* memp_alloc
(
    Memp     ps_memp,
    T_UINT32 ul_size
);
extern T_VOID memp_dump
(
    Memp ps_memp_in
);
extern T_VOID memp_delete
(
    Memp *ps_memp_in
);

#ifdef __cplusplus
}
#endif
#endif /* MEMP_TYPE_H */

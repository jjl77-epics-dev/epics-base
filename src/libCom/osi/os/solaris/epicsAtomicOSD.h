
/*************************************************************************\
* Copyright (c) 2011 LANS LLC, as Operator of
*     Los Alamos National Laboratory.
* Copyright (c) 2011 UChicago Argonne LLC, as Operator of Argonne
*     National Laboratory.
* EPICS BASE is distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution. 
\*************************************************************************/

/*
 *  Author Jeffrey O. Hill
 *  johill@lanl.gov
 */

#ifndef epicsAtomicOSD_h
#define epicsAtomicOSD_h

#if defined ( OSD_ATOMIC_INLINE )

/* 
 * atomic.h exists only in Solaris 10 or higher
 */
#if defined ( __SunOS_5_10 )

#include <limits.h>
#include <atomic.h>

#define __STDC_LIMIT_MACROS /* define SIZE_MAX for c++ */
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

OSD_ATOMIC_INLINE unsigned epicsAtomicTestAndSetUIntT ( unsigned * pTarget )
{
    const uint_t oldVal = atomic_cas_uint ( pTarget, 0u, 1u );
    return oldVal == 0u;
}

OSD_ATOMIC_INLINE void epicsAtomicSetUIntT ( unsigned * pTarget, unsigned newVal )
{
    atomic_swap_uint ( pTarget, newVal );
}

OSD_ATOMIC_INLINE unsigned epicsAtomicGetUIntT ( const unsigned * pTarget )
{
    /* 
     * we cast away const, but are careful not to modify 
     * the target
     */
    unsigned * const pTarg = ( unsigned * ) ( pTarget );
    return atomic_or_uint_nv ( pTarg, 0U );
}

#if SIZE_MAX == UINT_MAX

OSD_ATOMIC_INLINE size_t epicsAtomicIncrSizeT ( size_t * pTarget )
{
    unsigned * const pTarg = ( unsigned * ) ( pTarget );
    return atomic_inc_uint_nv ( pTarg );
}

OSD_ATOMIC_INLINE size_t epicsAtomicDecrSizeT ( size_t * pTarget )
{
    unsigned * const pTarg = ( unsigned * ) ( pTarget );
    return atomic_dec_uint_nv ( pTarg );
}

OSD_ATOMIC_INLINE void epicsAtomicSetSizeT ( size_t * pTarget, size_t newVal )
{
    unsigned * const pTarg = ( unsigned * ) ( pTarget );
    atomic_swap_uint ( pTarg, newVal );
}

OSD_ATOMIC_INLINE size_t epicsAtomicGetSizeT ( const size_t * pTarget )
{
    /* 
     * we cast away const, but are careful not to modify 
     * the target
     */
    unsigned * const pTarg = ( unsigned * ) ( pTarget );
    return atomic_or_uint_nv ( pTarg, 0U );
}

#elif SIZE_MAX == ULONG_MAX

OSD_ATOMIC_INLINE size_t epicsAtomicIncrSizeT ( size_t * pTarget )
{
    unsigned long * const pTarg = ( unsigned long * ) ( pTarget );
    return atomic_inc_ulong_nv ( pTarg );
}

OSD_ATOMIC_INLINE size_t epicsAtomicDecrSizeT ( size_t * pTarget )
{
    unsigned long * const pTarg = ( unsigned long * ) ( pTarget );
    return atomic_dec_ulong_nv ( pTarg );
}

OSD_ATOMIC_INLINE void epicsAtomicSetSizeT ( size_t * pTarget, size_t newVal )
{
    unsigned long * const pTarg = ( unsigned long * ) ( pTarget );
    atomic_swap_ulong ( pTarg, newVal );
}

OSD_ATOMIC_INLINE size_t epicsAtomicGetSizeT ( const size_t * pTarget )
{
    /* 
     * we cast away const, but are careful not to modify 
     * the target
     */
    unsigned long * const pTarg = ( unsigned long * ) ( pTarget );
    return atomic_or_ulong_nv ( pTarg, 0UL );
}

#else
#   error unsupported solaris architecture
#endif /* SIZE_MAX == UINT_MAX */

#ifdef __cplusplus
} /* end of extern "C" */
#endif /* __cplusplus */

#else /* ifdef __SunOS_5_10  */

#include "epicsAtomicLocked.h"

#endif /* ifdef __SunOS_5_10 */

#endif /* if defined ( OSD_ATOMIC_INLINE ) */

#endif /* epicsAtomicOSD_h */

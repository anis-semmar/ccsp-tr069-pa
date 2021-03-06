/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2015 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/


/**********************************************************************

    module: ccsp_tr069pa_wrapper_api.h

        For CCSP TR-069 Protocol Agent 

    ---------------------------------------------------------------

    description:

        This wrapper file defines all the platform-independent
        functions on memory management.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Kang Quan

    ---------------------------------------------------------------

    revision:

        06/17/2011    initial revision.

**********************************************************************/

#ifndef  _CCSP_TR069PA_WRAPPER_API_
#define  _CCSP_TR069PA_WRAPPER_API_

#include "ccsp_trace.h"

/*
 * g_Tr069_PA_Name needs to be set when TR-069 PA starts up as the first thing,
 * we expect it to be set as program argument. Since we define the name as global
 * variable, there cannot be more than one TR-069 PA resides in the same process.
 */

extern   char*                      g_Tr069_PA_Name;


/*
 * Memory management wrapper APIs
 */

/*
#define  CcspTr069PaAllocateMemory(mBlockSize)                  \
    AnscAllocateMemory(mBlockSize)
*/

__inline static void*
CcspTr069PaAllocateMemory
    (
        int                         mBlockSize
    )
{
    void*                           ptr = AnscAllocateMemory(mBlockSize);

    if ( ptr )
    {
        AnscZeroMemory(ptr, mBlockSize);
    }

    return ptr;
}

#if 0
#define  CcspTr069PaReallocateMemory(mPtr, mNewBlockSize)       \
    AnscReAllocateMemory(mPtr, mNewBlockSize)
#endif

#define  CcspTr069PaFreeMemory(mPtr)                            \
    AnscFreeMemory(mPtr)


#define  CcspTr069GetComponentMemorySize()                      \
    AnscGetComponentMemorySize(g_Tr069_PA_Name)

#define  CcspTr069PaCloneString(src)                            \
    AnscCloneString(src)

#ifndef   ANSC_MEMORY_USE_COUNTSIZE
#define  CcspTr069PaInspectMemoryHealth()                       \
    AnscLiveMemoryInspectRecordDetail()
#else
#define  CcspTr069PaInspectMemoryHealth()                         
#endif

#if 0
#define  CcspTr069PaAllocateMemory(mBlockSize)                  \
    AnscAllocateMemoryCountSize(g_Tr069_PA_Name, mBlockSize)


#define  CcspTr069PaReallocateMemory(mPtr, mNewBlockSize)         \
    AnscReAllocateMemoryCountSize(g_Tr069_PA_Name, mPtr, mNewBlockSize)


#define  CcspTr069PaFreeMemory(mPtr)                            \
    AnscFreeMemoryCountSize(g_Tr069_PA_Name, mPtr)


#define  CcspTr069GetComponentMemorySize()                      \
    AnscGetComponentMemorySize(g_Tr069_PA_Name)


__inline static
char*
CcspTr069PaCloneString(char* src)
{
    char*   dst = NULL;

    int     src_size = src ? AnscSizeOfString(src) : 0;     
    if ( !src )                                             
        dst = NULL;                                         
    else 
    {                                                 
        dst = CcspTr069PaAllocateMemory(src_size+1);      
        if ( dst ) 
        {                                        
            if ( src_size == 0 )                            
                dst[0] = 0;                                 
            else 
            {                                          
                AnscCopyMemory(dst, src, src_size);         
                dst[src_size] = 0;                          
            }
        }                                               
    }                                                   

    return dst;
}
#endif


#define  CcspTr069PaAllocMemWithHeadRoom(ptr, size, hdroom)     \
    do {                                                        \
        char*                       p;                          \
        p = (void*)CcspTr069PaAllocateMemory(size+hdroom);      \
        if ( !p ) {                                             \
            ptr = NULL;                                         \
        }                                                       \
        else {                                                  \
            ptr = (void*)(p + hdroom);                          \
        }                                                       \
    } while (0)

#define  CcspTr069PaFreeMemoryWithHeadRoom(ptr, hdroom)         \
    do {                                                        \
        char*                       p = (char*)ptr;             \
        if ( p ) {                                              \
            p -= hdroom;                                        \
            CcspTr069PaFreeMemory(p);                           \
        }                                                       \
    } while (0)


/*
 * Logging wrapper APIs
 */
#define  CcspTr069PaTraceEmergency(msg)                         \
    CcspTraceEmergency2(g_Tr069_PA_Name, msg)

#define  CcspTr069PaTraceAlert(msg)                             \
    CcspTraceAlert2(g_Tr069_PA_Name, msg)

#define  CcspTr069PaTraceCritical(msg)                          \
    CcspTraceCritical2(g_Tr069_PA_Name, msg)

#define  CcspTr069PaTraceError(msg)                             \
    CcspTraceError2(g_Tr069_PA_Name, msg)

#define  CcspTr069PaTraceWarning(msg)                           \
    CcspTraceWarning2(g_Tr069_PA_Name, msg)

#define  CcspTr069PaTraceNotice(msg)                            \
    CcspTraceNotice2(g_Tr069_PA_Name, msg)

#define  CcspTr069PaTraceDebug(msg)                             \
    CcspTraceDebug2(g_Tr069_PA_Name, msg)

#define  CcspTr069PaTraceInfo(msg)                              \
    CcspTraceInfo2(g_Tr069_PA_Name, msg)


#endif



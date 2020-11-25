#ifndef __TYPE_H__
#define __TYPE_H__

#include<stdio.h>

#define TRUE  1
#define FALSE 0

typedef unsigned char                     u8;
typedef signed char                       s8;
typedef unsigned short                    u16;
typedef signed short                      s16;
typedef unsigned int                      u32;
typedef signed int                        s32;
typedef unsigned long long                u64;
typedef signed long long                  s64;
typedef float                             f32;
typedef double                            f64;


typedef enum
{
  /*-------------------------------------------------------------------------
    Numbered per ITU-T V.25 ter
  -------------------------------------------------------------------------*/
  DSAT_OK             = 0,    /*  AT: OK            */
  DSAT_CONNECT        = 1,    /*  AT: CONNECT       */
  DSAT_RING           = 2,    /*  AT: RING          */
  DSAT_NO_CARRIER     = 3,    /*  AT: NO CARRIER    */
  DSAT_ERROR          = 4,    /*  AT: ERROR         */
  DSAT_NO_DIALTONE    = 6,    /*  AT: NO DIAL TONE  */
  DSAT_BUSY           = 7,    /*  AT: BUSY          */
  DSAT_NO_ANSWER      = 8,    /*  AT: NO ANSWER     */
  DSAT_DELAYED        = 9,   /* AT: Call Throttled */
  DSAT_MAX_BASIC      = 10,   /*  End of basic result codes*/  

  DSAT_CRC_CODE_VOICE = 31,  /* normal voice  */ 
} dsat_result_enum_type;


#endif


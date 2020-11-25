#ifndef __DSAT_H__
#define __DSAT_H__


/***************************************************************************
* Macros
***************************************************************************/
#define MAX_ARG 17
#define MAX_LINE_SIZE 256
#define UPCASE( c ) ( ((c) >= 'a' && (c) <= 'z') ? ((c) - 0x20) : (c) )

#define TRUE  1
#define FALSE 0

//#define NULL ((void*)0)

/***************************************************************************
* Types
***************************************************************************/
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

typedef enum
{
  DSAT_CMD, 
  DSAT_ONLINE_DATA,
  DSAT_ONLINE_CMD
} dsat_mode_enum_type;


typedef struct dsati_cmd_struct
{
  char *name;
  dsat_result_enum_type (*proc_func)(void);
} dsati_cmd_type;


typedef struct
{
  u8 *arg[MAX_ARG];
  u16  arg_length[MAX_ARG];
  u8 *working_at_line;
  u8 *name;
  u8 *end_of_line;
  u8 op;
  u16 args_found;
} tokens_struct_type;

typedef struct
{
  const dsati_cmd_type *table_ptr;
  const u16 *table_size;
} dsati_at_cmd_table_entry_type;


#endif

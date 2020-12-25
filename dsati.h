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

#define NA    1                 /*  Name field found      */
#define EQ    2                 /*  <=> found             */
#define QU    4                 /*  <?> found             */
#define AR    8                 /*  Argument field found  */


/***************************************************************************
* Types
***************************************************************************/
typedef unsigned char                     bool;
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
  DSAT_OK             = 0,    /*  AT: OK            */
  DSAT_ERROR          = 4,    /*  AT: ERROR         */
  DSAT_ASYNC_CMD      = -16,  /*  internal: async command in progress   */
} dsat_result_enum_type;

typedef enum
{
  DSAT_CMD, 
  DSAT_ONLINE_DATA,
  DSAT_ONLINE_CMD
} dsat_mode_enum_type;

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

typedef struct dsati_cmd_struct
{
  char *name;
  dsat_result_enum_type (*proc_func)(tokens_struct_type *tok_ptr);
} dsati_cmd_type;

typedef struct
{
  dsati_cmd_type *table_ptr;
  u16 *table_size;
} dsati_at_cmd_table_entry_type;


#endif

/***************************************************************************
* Include Files
***************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "type.h"
/***************************************************************************
* Macros
***************************************************************************/
#define DSAT_MAX_LINE_SIZE 2100
#define UPCASE( c ) ( ((c) >= 'a' && (c) <= 'z') ? ((c) - 0x20) : (c) )
/***************************************************************************
* Types
***************************************************************************/
typedef enum
{
  DSAT_CMD_PREP_STATE_HUNT,     /*  Initial:  looking for a or A                      */
  DSAT_CMD_PREP_STATE_FOUND_A,  /*  Found A, looking for t, T or /                    */
  DSAT_CMD_PREP_STATE_FOUND_AT, /*  Found AT: filling buffer and processing backspace */
  DSAT_CMD_PREP_STATE_ERROR     /*  Error!  loop until end of line                    */
} dsat_cmd_prep_state_enum_type;

typedef struct
{
  byte *arg[MAX_ARG];
  uint16  arg_length[MAX_ARG];
  byte *working_at_line;
  byte *name;
  byte *end_of_line;
  uint8 op;
  uint16 args_found;
  dsat_cmd_category_enum_type cmd_category;
} tokens_struct_type;

/***************************************************************************
* Extern Variables (Extern 、Global)
***************************************************************************/

/***************************************************************************
* Local Variables (static ,Global)
***************************************************************************/

/***************************************************************************
* Local Functions Prototypes
***************************************************************************/
u8 get_cmd_line(u8 *cmd_line)
{
	u8 in_char = 0;
  u8 in_size = 0;
  u8 char_a = 0;
  u8 char_t = 0;
  u8 *cmd_line_ptr = NULL;
  
  cmd_line_ptr = cmd_line;
 
  while((in_char = getchar()) != '\n')
  {
    in_size++;
    if(in_size < DSAT_MAX_LINE_SIZE)
    {
      if(in_size == 1)
      {
        char_a = in_char;
      }
      else if(in_size == 2)
      {
        char_t = in_char;
      }
      else 
      {      
        if(('A' == UPCASE(char_a))&&('T' == UPCASE(char_t))&&(in_size >= 3))
        {
          *cmd_line_ptr++ = in_char;
        }
      }
    }
  }
  *cmd_line_ptr++ = '\n';
  *cmd_line_ptr = '\0';
  return (in_size-2);
}

u8* parse_extended_command( u8* a_ptr, tokens_struct_type* tokens_res )
{
  u8 c;
  u8* working_ptr = NULL;

  working_ptr = tokens_res->working_at_line;
  tokens_res->op = 0;
  tokens_res->name = working_ptr;
  tokens_res->args_found = 0;

  while ( (c = *a_ptr) != '\0' )
  {
    *working_ptr = c;

    if ( c == '=' && tokens_res->op == NA )
    {
      *working_ptr = '\0';                  /*  Terminate Name  */
      tokens_res->arg[0] = working_ptr + 1; /*  Start of (first) argument */
      tokens_res->args_found = 1;
      tokens_res->op |= EQ;

      DS_AT_MSG0_HIGH("***=***");
    }
    
    else if ( c == '?' && (tokens_res->op & (NA|AR)) == NA )
    {
      *working_ptr = '\0';                  /*  Terminate Name  */
      tokens_res->arg[0] = working_ptr+1;   /*  Start of (first) argument */
      tokens_res->args_found = 1;
      tokens_res->op |= QU;
      DS_AT_MSG0_HIGH("***?***");
    }
    
    else if ( c != ' ' && c != ';' && tokens_res->op > NA )
    {
      tokens_res->op |=AR;        /*  Argument (or comma) actually found  */
      DS_AT_MSG0_HIGH("***arg or comma***");
    }

  }
}


int main()
{
  u8 *cmd_line = NULL;
  u8 *curr_char_ptr = NULL;
  u8 cmd_size = 0;
  u8 cmd_char = 0;
  dsat_cmd_prep_state_enum_type at_cmd_prep_state = DSAT_CMD_PREP_STATE_HUNT;
  tokens_struct_type token;

  cmd_line = malloc(DSAT_MAX_LINE_SIZE);
  if(cmd_line == NULL)
    return 0;

  cmd_size = get_cmd_line(cmd_line);
  printf("cmd_line = %s,cmd_size = %d\n",cmd_line,cmd_size);

  curr_char_ptr = cmd_line;

  while(*curr_char_ptr != '\0')
	{
    cmd_char = *curr_char_ptr++; 
    if(*curr_char_ptr == '+')
    {
      parse_extended_command( curr_char_ptr, &token );
    }

  }
  return 0;
}


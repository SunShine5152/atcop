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
   *cmd_line_ptr = '\n'; 
   return (in_size-2);
}

int main()
{
  u8 *cmd_line = NULL;
  u8 cmd_size = 0;
  u8 cmd_char = 0;
  dsat_cmd_prep_state_enum_type at_cmd_prep_state = DSAT_CMD_PREP_STATE_HUNT;

  cmd_line = malloc(DSAT_MAX_LINE_SIZE);
  if(cmd_line == NULL)
    return 0;

  cmd_size = get_cmd_line(cmd_line);
  printf("cmd_line = %s,cmd_size = %d\n",cmd_line,cmd_size);

	while(*cmd_line != '\n')
	{
    cmd_char = *cmd_line++; 

    switch (at_cmd_prep_state)
    {
      case DSAT_CMD_PREP_STATE_HUNT:
        if(UPCASE(cmd_char) == 'A')
        {
          at_cmd_prep_state =  DSAT_CMD_PREP_STATE_FOUND_A;
        }
        break;
      default:
        break;
	  }
  }
  return 0;
}


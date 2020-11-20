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
int main()
{
	u8 in_char = 0;
  u8 *cmd_line_ptr = NULL;
  u8 in_size = 0;
  u8 char_a = 0;
  u8 char_t = 0;
  dsat_cmd_prep_state_enum_type at_cmd_prep_state = DSAT_CMD_PREP_STATE_HUNT;
  cmd_line_ptr = malloc(DSAT_MAX_LINE_SIZE);
  //scanf("%s",cmd_line_ptr);
  while((in_char = getchar()) != '\n')
  {
    in_size++;
    if(in_size == 1)
    {
      char_a = in_char;
    }
    else if(in_size == 2)
    {
      char_t = in_char;
    }
    else if()
  }

      if(in_char == 'A')
      {
        putchar(in_char);
        *cmd_line_ptr++ = in_char;
      }

  //in_char = getchar();
	//putchar(in_char);

	while(cmd_line_ptr != '\n')
	{
    in_char = *cmd_line_ptr++; 

    switch (at_cmd_prep_state)
    {
      case DSAT_CMD_PREP_STATE_HUNT:
        if(UPCASE(in_char) == 'A')
        {
          at_cmd_prep_state =  DSAT_CMD_PREP_STATE_FOUND_A;
        }
	}

  return 0;
}


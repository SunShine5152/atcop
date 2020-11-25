/***************************************************************************
* Include Files
***************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dsati.h"
#include "dsatctab.h"
/*--------------------------------------------------------------------------
                Syntax Flags For the AT Command Parser 
--------------------------------------------------------------------------*/
#define NA    1                 /*  Name field found      */
#define EQ    2                 /*  <=> found             */
#define QU    4                 /*  <?> found             */
#define AR    8                 /*  Argument field found  */
/***************************************************************************
* Types
***************************************************************************/

/***************************************************************************
* Extern Variables (Extern 、Global)
***************************************************************************/

/***************************************************************************
* Local Variables (static ,Global)
***************************************************************************/
static dsat_result_enum_type result_code;
static u8 *token_line = NULL;
static u8 *cmd_line = NULL;
static tokens_struct_type token;

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
    if(in_size < MAX_LINE_SIZE)
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
  //*cmd_line_ptr++ = '\n';
  *cmd_line_ptr = '\0';
  return (in_size-2);
}
int trim_string
(
   u8 **start   /*  Pointer to beginning of string */
)
{
  u8 *end = *start;

  /* Advance to non-space character */
  while (*(*start) == ' ')
  {
    (*start)++;
  }

  /* Move to end of string */
  while (*end != '\0')
  {
    (end)++;
  }
  /* Backup to non-space character */
  while ((end >= *start) && *(--end) == ' ') {}

  /* Terminate string after last non-space character */
  *(++end) = '\0';
  return (end - *start);
} /* trim_string */

u8* parse_extended_command( u8* a_ptr, tokens_struct_type* tokens_res )
{
  u8 c;
  u8* working_ptr = NULL;
  u8 i = 0;

  working_ptr = tokens_res->working_at_line;
  tokens_res->op = 0;
  tokens_res->name = working_ptr;
  tokens_res->args_found = 0;

  while ( (c = *a_ptr) != '\0' )
  {    
    *working_ptr = c;
    printf("111 c=%c\n",c);
    if ( c != ' ' && c != ';' && tokens_res->op == 0 )
    {
      printf("222\n");
      tokens_res->op = NA;        /*  Start of Name */
      tokens_res->name = working_ptr;
      //printf("tokens_res->name = %s,*working_ptr = %c" ,tokens_res->name, *working_ptr);
    } 
    #if 1   
    else if ( c == '=' && tokens_res->op == NA )
    {
      *working_ptr = '\0';                  /*  Terminate Name  */
      tokens_res->arg[0] = working_ptr + 1; /*  Start of (first) argument */
      tokens_res->args_found = 1;
      tokens_res->op |= EQ;

      printf("***=***");
    }

    else if ( c == '?' && (tokens_res->op & (NA|AR)) == NA )
    {
      *working_ptr = '\0';                  /*  Terminate Name  */
      tokens_res->arg[0] = working_ptr+1;   /*  Start of (first) argument */
      tokens_res->args_found = 1;
      tokens_res->op |= QU;
      printf("***?***");
    }

    else if ( c != ' ' && c != ';' && tokens_res->op > NA )
    {
      tokens_res->op |=AR;        /*  Argument (or comma) actually found  */
      printf("***arg or comma***");
    }
    if ( c == ',' && (tokens_res->op & AR) )
    {
      *working_ptr = '\0';                /*  Terminate current argument  */

       tokens_res->arg_length[tokens_res->args_found - 1] =
                         working_ptr - tokens_res->arg[tokens_res->args_found - 1];

      for(i=0; i<tokens_res->args_found; i++)
      {
        printf("tokens_res->arg_length[%d] = %d", i, tokens_res->arg_length[i]);
      }

      if(tokens_res->args_found)
      {
        printf("**trim_string**");
        (void)trim_string(&tokens_res->arg [tokens_res->args_found-1]);
      }
      if ( tokens_res->args_found < MAX_ARG )
      {
        /*  Start of next arg */
        tokens_res->arg [tokens_res->args_found] = working_ptr + 1;
        ++tokens_res->args_found;
        printf("**** *working_ptr = %c",*working_ptr);
      }
      else
      {
        printf("Number of parameters exceeded: %d",MAX_ARG);
        result_code = DSAT_ERROR;
        break;
      }
    }
    #endif
    ++working_ptr;
    ++a_ptr;
    printf("333\n");
  }
  #if 1
  if(tokens_res->op == (NA|EQ|AR))
  {
    tokens_res->arg_length[tokens_res->args_found - 1] = 
                working_ptr - tokens_res->arg[tokens_res->args_found - 1];
  }

  *working_ptr = '\0';
  tokens_res->end_of_line = working_ptr;

  (void)trim_string(&tokens_res->name);
  if (0 < tokens_res->args_found)
  {
     (void)trim_string(&tokens_res->arg [tokens_res->args_found-1]);
  }

  printf("token_res->name = %s,op = %d,args_found = %d\n",tokens_res->name,tokens_res->op,tokens_res->args_found);
  for(i=0; i<tokens_res->args_found; i++)
  {
    printf("***0**tokens_res->arg[%d] = %s,arg_length = %d\n", i, tokens_res->arg[i],tokens_res->arg_length[i]);
  }
  
  return a_ptr;
  #endif
  printf("end\n");
  return NULL;
}

dsat_result_enum_type dsatpar_parse_cmd_line
(
  u8 *cmd_line                /*  NULL terminated command line with
                                    "AT" prefix and <CR> removed. */
)
{
  u8 *curr_char_ptr = NULL;

  result_code = DSAT_OK;
  curr_char_ptr = cmd_line;  
 
  printf("000_000\n");
  if(*curr_char_ptr == '+')
  {
    printf("000\n");
    curr_char_ptr = parse_extended_command( curr_char_ptr, &token );
    printf("000_111\n");
  }
  return result_code;
}

dsat_result_enum_type atcop_init(void)
{
  result_code = DSAT_OK;
  
  if(token_line == NULL)
  {
    token_line = (u8*)malloc(MAX_LINE_SIZE  );
    if(token_line == NULL)
    {
      result_code = DSAT_ERROR;
      return result_code;
    }
    memset(token_line, 0, MAX_LINE_SIZE);
  }

  token.working_at_line = token_line;

  if(cmd_line == NULL)
  {
    cmd_line = (u8*)malloc(MAX_LINE_SIZE  );
    if(cmd_line == NULL)
    {
      result_code = DSAT_ERROR;
      return result_code;
    }
    memset(cmd_line, 0, MAX_LINE_SIZE);
  }
  return result_code;
}
static void process_at_cmd_line(char * cmd_line_ptr)
{    
    dsati_at_cmd_table_entry_type  *array_ptr = NULL;
    array_ptr = extended_table_entries;

    
}


int main()
{
  u8 cmd_size = 0;

  atcop_init(); 

  while(1)
  {
    cmd_size = get_cmd_line(cmd_line);
    printf("cmd_line = \"%s\",cmd_size = %d\n",cmd_line,cmd_size);

    dsatpar_parse_cmd_line(cmd_line);

    process_at_cmd_line(cmd_line);
  }
  return 0;
}


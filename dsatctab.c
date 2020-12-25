#include <stdio.h>
#include <string.h>
#include "dsati.h"

#define ARR_SIZE(a) ( sizeof(a) / sizeof(a[0]) )

extern dsat_result_enum_type dsatparm_exec_ipr_cmd(tokens_struct_type *tok_ptr);
extern dsat_result_enum_type dsatparm_exec_param_cmd(tokens_struct_type *tok_ptr);
extern dsat_result_enum_type at_command_func(tokens_struct_type *tok_ptr);

extern void print_token(tokens_struct_type *tok_ptr);


dsati_cmd_type dsat_ext_table[] =
{
    { "+ICF",  dsatparm_exec_param_cmd},

    { "+IFC",  dsatparm_exec_param_cmd},

    { "+IPR",  dsatparm_exec_ipr_cmd},  
    
    { "+NAME", at_command_func},
};

u16 dsat_ext_table_size = ARR_SIZE( dsat_ext_table );

dsati_at_cmd_table_entry_type extended_table_entries[] =
{
    { dsat_ext_table,      &dsat_ext_table_size },
    { NULL, 0 }
};

dsat_result_enum_type dsatparm_exec_param_cmd(tokens_struct_type *tok_ptr)
{
  printf("ifc exec\n");
  return DSAT_OK;
}

dsat_result_enum_type dsatparm_exec_ipr_cmd(tokens_struct_type *tok_ptr)
{
  printf("dsatparm_exec_ipr_cmd\n");
  print_token(tok_ptr);
  return DSAT_OK;
}
dsat_result_enum_type at_command_func(tokens_struct_type *tok_ptr)
{
  printf("at_command_func\n");
  print_token(tok_ptr);
  return DSAT_OK;
}


void print_token(tokens_struct_type *tok_ptr)
{
  int i = 0;
  if( (tok_ptr->name != NULL) && (tok_ptr->op>0) )
  {
    printf("NA 1; EQ 2; QU 4; AR 8;\n");
    printf("tok_ptr->name = %s,op = %#x,args_found = %d\n",tok_ptr->name,tok_ptr->op,tok_ptr->args_found);
  }
  
  printf("***tokens_res->arg[0] = %x\n", i, *tok_ptr->arg[0]);
  if(tok_ptr->args_found > 0)
  {
    for(i=0; i<tok_ptr->args_found; i++)
    {
      printf("***tokens_res->arg[%d] = %s,arg_length[%d] = %d\n", i, tok_ptr->arg[i],i,tok_ptr->arg_length[i]);
    }
  }
}

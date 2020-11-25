#include <string.h>
#include "dsati.h"

#define ARR_SIZE(a) ( sizeof(a) / sizeof(a[0]) )

extern dsat_result_enum_type dsatparm_exec_ipr_cmd();
extern dsat_result_enum_type dsatparm_exec_param_cmd();


dsati_cmd_type dsat_ext_table[] =
{
    { "+ICF", dsatparm_exec_param_cmd},

    { "+IFC", dsatparm_exec_param_cmd},

    { "+IPR", dsatparm_exec_ipr_cmd},
};

const u16 dsat_ext_table_size = ARR_SIZE( dsat_ext_table );

dsati_at_cmd_table_entry_type extended_table_entries[] =
{
    { dsat_ext_table,      &dsat_ext_table_size },
    { NULL, 0 }
};

dsat_result_enum_type dsatparm_exec_param_cmd()
{
    return DSAT_OK;
}
dsat_result_enum_type dsatparm_exec_ipr_cmd()
{
    return DSAT_OK;
}



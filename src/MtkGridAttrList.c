/*===========================================================================
=                                                                           =
=                             MtkGridAttrList                               =
=                                                                           =
=============================================================================

                         Jet Propulsion Laboratory
                                   MISR
                               MISR Toolkit

            Copyright 2006, California Institute of Technology.
                           ALL RIGHTS RESERVED.
                 U.S. Government Sponsorship acknowledged.

============================================================================*/

#include "MisrToolkit.h"
#include "MisrError.h"
#include <stdio.h>		/* for printf */
#include <stdlib.h>

int main(int argc, char *argv[])
{
  MTKt_status status_code;      /* Return status of this function */
  MTKt_status status;		/* Return status */
  int num_attrs;                /* Number of attributes */
  char **attrlist;              /* Attribute list */
  int i;

  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s <MISR Product File> <Grid Name>\n",argv[0]);
    exit(1);
  }

  status = MtkGridAttrList(argv[1],argv[2],&num_attrs,&attrlist);
  MTK_ERR_COND_JUMP(status);

  for (i = 0; i < num_attrs; ++i)
    printf("%s\n",attrlist[i]);

  MtkStringListFree(num_attrs, &attrlist);

  return 0;

ERROR_HANDLE:
  if (status_code == MTK_HDFEOS_GDOPEN_FAILED)
    fprintf(stderr, "Error opening file: %s\n", argv[1]);

  if (status_code == MTK_HDFEOS_GDATTACH_FAILED)
    fprintf(stderr, "Failed to find grid: %s\n", argv[2]);

  return status_code;
}

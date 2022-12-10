/*===========================================================================
=                                                                           =
=                           MtkDataBufferImport                             =
=                                                                           =
=============================================================================

                         Jet Propulsion Laboratory
                                   MISR
                               MISR Toolkit

            Copyright 2005, California Institute of Technology.
                           ALL RIGHTS RESERVED.
                 U.S. Government Sponsorship acknowledged.

============================================================================*/

#include "MisrUtil.h"
#include <stdlib.h>

/** \brief Import Data Buffer
 *
 *  \return MTK_SUCCESS if successful.
 *
 *  \par Example:
 *  In this example, we import an existing data buffer into a data buffer structure with a size of 5 lines by 10 samples of type \c MTKe_int16
 *
 *  \code
 *  status = MtkDataBufferImport(5, 10, MTKe_int16, dataptr, &databuf);
 *  \endcode
 *
 *  \note
 *  The caller is responsible for using MtkDataBufferFree() to free the memory used by \c databuf
 */

MTKt_status MtkDataBufferImport(
  int nline,               /**< [IN] Number of lines */
  int nsample,             /**< [IN] Number of samples */
  MTKt_DataType datatype,  /**< [IN] Data Type */
  void *dataptr,           /**< [IN] Data pointer to payload */
  MTKt_DataBuffer *databuf /**< [OUT] Data Buffer */ )
{
  MTKt_status status_code;      /* Return status of this function */
  MTKt_DataBuffer dbuf = MTKT_DATABUFFER_INIT;
				/* Data buffer structure */
  int datasize[] = MTKd_DataSize; /* Data size by data type */
  int i;			/* Index */
  
  if (databuf == NULL)
    MTK_ERR_CODE_JUMP(MTK_NULLPTR);

  if (dataptr == NULL)
    MTK_ERR_CODE_JUMP(MTK_NULLPTR);

  if (nline < 0)
    MTK_ERR_CODE_JUMP(MTK_OUTBOUNDS);

  if (nsample < 0)
    MTK_ERR_CODE_JUMP(MTK_OUTBOUNDS);

  dbuf.nline = nline;
  dbuf.nsample = nsample;
  dbuf.datasize = datasize[datatype];
  dbuf.datatype = datatype;
  dbuf.imported = MTK_TRUE;	/* Data pointer is allocated outside Mtk */

  /* Allocate 1D Illiffe vector */
  dbuf.vdata = (void **)calloc(dbuf.nline, sizeof(void *));
  if (dbuf.vdata == NULL)
    MTK_ERR_CODE_JUMP(MTK_CALLOC_FAILED);

  /* Allocate 2D buffer */
  dbuf.vdata[0] = dataptr;

  /* Connect Illiffe vector */
  for (i = 1; i < nline; i++) {
    dbuf.vdata[i] = (void *)((unsigned char *)(dbuf.vdata[i-1]) +
			     dbuf.nsample * dbuf.datasize);
  }

  /* Hook the union to the void data pointer */
  dbuf.data.v = dbuf.vdata;
  /* Hook the data pointer to the data */
  dbuf.dataptr = dbuf.vdata[0];

  *databuf = dbuf;

  return MTK_SUCCESS;

ERROR_HANDLE:
  return status_code;
}

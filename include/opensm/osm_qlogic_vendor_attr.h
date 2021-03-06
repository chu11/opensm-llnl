/*
 * Copyright (c) 2010 QLogic, Inc. All rights reserved.
 * Copyright (c) 2004-2009 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2002-2009 Mellanox Technologies LTD. All rights reserved.
 * Copyright (c) 1996-2003 Intel Corporation. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

/*
 * Abstract:
 */

#ifndef _OSM_QLOGIC_VENDOR_ATTR_H
#define _OSM_QLOGIC_VENDOR_ATTR_H

#include <complib/cl_types.h>

#ifdef __cplusplus
#  define BEGIN_C_DECLS extern "C" {
#  define END_C_DECLS   }
#else				/* !__cplusplus */
#  define BEGIN_C_DECLS
#  define END_C_DECLS
#endif				/* __cplusplus */

BEGIN_C_DECLS

/****d* QLogicAR: Constants/IB_MAD_ATTR_VENDOR_SWITCH_INFO
* NAME
*	IB_MAD_ATTR_VENDOR_SWITCH_INFO
*
* DESCRIPTION
*	Vendor specific Switch Info attribute
*
* SOURCE
*/
#define IB_MAD_ATTR_VENDOR_SWITCH_INFO		(CL_HTON16(0xff12))
/**********/

/****d* QLogicAR: Constants/IB_MAD_VENDOR_PORT_GROUP
* NAME
*	IB_MAD_ATTR_VENDOR_PORT_GROUP
*
* DESCRIPTION
*	Vendor specific PORT GROUP INFO
*
* SOURCE
*/
#define IB_MAD_ATTR_VENDOR_PORT_GROUP		(CL_HTON16(0xff21))

/****d* QLogicAR: Constants/IB_MAD_VENDOR_AR_LIDMASK
* NAME
*	IB_MAD_ATTR_VENDOR_AR_LIDMASK
*
* DESCRIPTION
*	Vendor specific Adaptive Routing LidMask INFO
*
* SOURCE
*/
#define IB_MAD_ATTR_VENDOR_AR_LIDMASK		(CL_HTON16(0xff22))
/**********/

END_C_DECLS
#endif				/* _OSM_QLOGIC_VENDOR_ATTR_H */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**
** Copyright (C), 2003, Victorian Partnership for Advanced Computing (VPAC) Ltd, 
** 110 Victoria Street, Melbourne, 3053, Australia.
**
** Authors:
**	Stevan M. Quenette, Senior Software Engineer, VPAC. (steve@vpac.org)
**	Patrick D. Sunter, Software Engineer, VPAC. (pds@vpac.org)
**	Luke J. Hodkinson, Computational Engineer, VPAC. (lhodkins@vpac.org)
**	Siew-Ching Tan, Software Engineer, VPAC. (siew@vpac.org)
**	Alan H. Lo, Computational Engineer, VPAC. (alan@vpac.org)
**	Raquibul Hassan, Computational Engineer, VPAC. (raq@vpac.org)
**
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the GNU Lesser General Public
**  License as published by the Free Software Foundation; either
**  version 2.1 of the License, or (at your option) any later version.
**
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**  Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public
**  License along with this library; if not, write to the Free Software
**  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** \file
 ** <b>Role:</b>
 **	Abstract class faciliting how class inheritance is done.
 **
 ** <b>Assumptions:</b>
 **	None
 **
 ** <b>Comments:</b>
 **	None
 **
 ** $Id: STree.h 3904 2006-12-14 00:52:06Z LukeHodkinson $
 **
 **/
 
#ifndef __StGermain_Base_Container_STree_h__
#define __StGermain_Base_Container_STree_h__

extern const Type STree_Type;

#define __STree                                 \
    __Stg_Class                                 \
    STree_CompareCB* cmp;                       \
    STree_DeleteCB* del;                        \
    int itmSize;                                \
    STreeNode* root;                            \
    int nNodes;                                 \
    int maxNodes;                               \
    float alpha;                                \
    float invAlpha;                             \
    int curDepth;                               \
    int curSize;                                \
    int flip;

struct STree { __STree };

#ifndef ZERO
#define ZERO 0
#endif

#define STREE_DEFARGS                           \
    STG_CLASS_DEFARGS

#define STREE_PASSARGS                          \
    STG_CLASS_PASSARGS

STree* STree_New();

STree* _STree_New( STREE_DEFARGS );

void STree_Init( STree* self );

void _STree_Init( void* self );

void STree_Destruct( STree* self );

void _STree_Delete( void* self );

void STree_Copy( void* self, const void* op );

void STree_SetCallbacks( void* _self, STree_CompareCB* cmp, STree_DeleteCB* del );

void STree_SetIntCallbacks( void* _self );

void STree_SetItemSize( void* _self, int itmSize );

void STree_SetAlpha( void* _self, float alpha );

void STree_Insert( void* _self, const void* itm );

void STree_Remove( void* _self, const void* itm );

void STree_Clear( void* _self );

int STree_GetSize( const void* _self );

const STreeNode* STree_GetRoot( const void* _self );

Bool STree_Has( const void* _self, const void* itm );

int STree_Size( const STreeNode *node );

int STree_IntCmp( const void* left, const void* right );

void STree_IntDel( void* itm );

#endif /* __StGermain_Base_Container_STree_h__ */

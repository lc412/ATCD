
//=============================================================================
/**
 *  @file    be_enum_val.cpp
 *
 *  $Id$
 *
 *  Extension of class AST_EnumVal that provides additional means for C++
 *  mapping.
 *
 *
 *  @author Copyright 1994-1995 by Sun Microsystems
 *  @author Inc. and Aniruddha Gokhale
 */
//=============================================================================

#include "be_enum_val.h"
#include "be_visitor.h"

be_enum_val::be_enum_val (ACE_CDR::ULong v,
                          UTL_ScopedName *n)
  : COMMON_Base (),
    AST_Decl (AST_Decl::NT_enum_val,
              n),
    AST_Constant (AST_Expression::EV_ulong,
                  AST_Decl::NT_enum_val,
                  new AST_Expression (v),
                  n),
    AST_EnumVal (v,
                 n),
    be_decl (AST_Decl::NT_enum_val,
             n)
{
}

int
be_enum_val::accept (be_visitor *visitor)
{
  return visitor->visit_enum_val (this);
}

void
be_enum_val::destroy (void)
{
  this->AST_EnumVal::destroy ();
  this->be_decl::destroy ();
}

IMPL_NARROW_FROM_DECL (be_enum_val)


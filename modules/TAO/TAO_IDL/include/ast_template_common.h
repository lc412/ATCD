// This may look like C, but it's really -*- C++ -*-
// $Id$

#ifndef AST_TEMPLATE_COMMON_H
#define AST_TEMPLATE_COMMON_H

#include "ast_decl.h"

#include "fe_utils.h"

class TAO_IDL_FE_Export AST_Template_Common : public virtual AST_Decl
{
public:
  AST_Template_Common (const FE_Utils::T_PARAMLIST_INFO *template_params);

  virtual ~AST_Template_Common (void);

  FE_Utils::T_PARAMLIST_INFO &template_params (void);

protected:
  FE_Utils::T_PARAMLIST_INFO template_params_;
};

#endif // AST_TEMPLATE_COMMON_H


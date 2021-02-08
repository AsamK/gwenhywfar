/***************************************************************************
    begin       : Mon Feb 08 2021
    copyright   : (C) 2021 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif


#include "gwenbuild/context_p.h"

#include <gwenhywfar/debug.h>
#include <gwenhywfar/memory.h>

#include <stdlib.h>
#include <string.h>



static char *_combinedString(const char *string1, const char *string2, const char delim);




GWB_CONTEXT *GWB_Context_new()
{
  GWB_CONTEXT *ctx;

  GWEN_NEW_OBJECT(GWB_CONTEXT, ctx);

  ctx->vars=GWEN_DB_Group_new("vars");

  return ctx;
}



GWB_CONTEXT *GWB_Context_dup(const GWB_CONTEXT *originalCtx)
{
  GWB_CONTEXT *ctx;

  GWEN_NEW_OBJECT(GWB_CONTEXT, ctx);

  if (originalCtx->topBuildDir)
    ctx->topBuildDir=strdup(originalCtx->topBuildDir);
  if (originalCtx->topSourceDir)
    ctx->topSourceDir=strdup(originalCtx->topSourceDir);

  if (originalCtx->currentBuildDir)
    ctx->currentBuildDir=strdup(originalCtx->currentBuildDir);
  if (originalCtx->currentSourceDir)
    ctx->currentSourceDir=strdup(originalCtx->currentSourceDir);

  if (originalCtx->compilerFlags)
    ctx->compilerFlags=originalCtx->compilerFlags;

  if (originalCtx->linkerFlags)
    ctx->linkerFlags=originalCtx->linkerFlags;

  if (originalCtx->includeList)
    ctx->includeList=GWEN_StringList_dup(originalCtx->includeList);

  if (originalCtx->defineList)
    ctx->defineList=GWB_KeyValuePair_List_dup(originalCtx->defineList);

  if (originalCtx->vars)
    ctx->vars=GWEN_DB_Group_dup(originalCtx->vars);

  return ctx;
}



void GWB_Context_free(GWB_CONTEXT *ctx)
{
  if (ctx) {
    free(ctx->topBuildDir);
    free(ctx->topSourceDir);
    free(ctx->currentBuildDir);
    free(ctx->currentSourceDir);
    free(ctx->compilerFlags);
    free(ctx->linkerFlags);

    GWEN_StringList_free(ctx->includeList);
    GWB_KeyValuePair_List_free(ctx->defineList);
    GWEN_DB_Group_free(ctx->vars);

    GWEN_FREE_OBJECT(ctx);
  }
}



const char *GWB_Context_GetTopBuildDir(const GWB_CONTEXT *ctx)
{
  return ctx->topBuildDir;
}



void GWB_Context_SetTopBuildDir(GWB_CONTEXT *ctx, const char *s)
{
  if (ctx->topBuildDir)
    free(ctx->topBuildDir);
  if (s)
    ctx->topBuildDir=strdup(s);
  else
    ctx->topBuildDir=NULL;
}



void GWB_Context_InsertTopBuildDir(GWB_CONTEXT *ctx, const char *s)
{
  char *newValue;

  newValue=_combinedString(s, ctx->topBuildDir, '/');
  free(ctx->topBuildDir);
  ctx->topBuildDir=newValue;
}



const char *GWB_Context_GetTopSourceDir(const GWB_CONTEXT *ctx)
{
  return ctx->topSourceDir;
}



void GWB_Context_SetTopSourceDir(GWB_CONTEXT *ctx, const char *s)
{
  if (ctx->topSourceDir)
    free(ctx->topSourceDir);
  if (s)
    ctx->topSourceDir=strdup(s);
  else
    ctx->topSourceDir=NULL;
}



void GWB_Context_InsertTopSourceDir(GWB_CONTEXT *ctx, const char *s)
{
  char *newValue;

  newValue=_combinedString(s, ctx->topSourceDir, '/');
  free(ctx->topSourceDir);
  ctx->topSourceDir=newValue;
}



const char *GWB_Context_GetCurrentBuildDir(const GWB_CONTEXT *ctx)
{
  return ctx->currentBuildDir;
}



void GWB_Context_SetCurrentBuildDir(GWB_CONTEXT *ctx, const char *s)
{
  if (ctx->currentBuildDir)
    free(ctx->currentBuildDir);
  if (s)
    ctx->currentBuildDir=strdup(s);
  else
    ctx->currentBuildDir=NULL;
}



void GWB_Context_AddCurrentBuildDir(GWB_CONTEXT *ctx, const char *s)
{
  char *newValue;

  newValue=_combinedString(ctx->currentBuildDir, s, '/');
  free(ctx->currentBuildDir);
  ctx->currentBuildDir=newValue;
}



const char *GWB_Context_GetCurrentSourceDir(const GWB_CONTEXT *ctx)
{
  return ctx->currentSourceDir;
}



void GWB_Context_AddCurrentSourceDir(GWB_CONTEXT *ctx, const char *s)
{
  char *newValue;

  newValue=_combinedString(ctx->currentSourceDir, s, '/');
  free(ctx->currentSourceDir);
  ctx->currentSourceDir=newValue;
}



void GWB_Context_SetCurrentSourceDir(GWB_CONTEXT *ctx, const char *s)
{
  if (ctx->currentSourceDir)
    free(ctx->currentSourceDir);
  if (s)
    ctx->currentSourceDir=strdup(s);
  else
    ctx->currentSourceDir=NULL;
}



const char *GWB_Context_GetCompilerFlags(const GWB_CONTEXT *ctx)
{
  return ctx->compilerFlags;
}



void GWB_Context_SetCompilerFlags(GWB_CONTEXT *ctx, const char *s)
{
  if (ctx->compilerFlags)
    free(ctx->compilerFlags);
  if (s)
    ctx->compilerFlags=strdup(s);
  else
    ctx->compilerFlags=NULL;
}



void GWB_Context_AddCompilerFlags(GWB_CONTEXT *ctx, const char *s)
{
  char *newValue;

  newValue=_combinedString(ctx->compilerFlags, s, ' ');
  free(ctx->compilerFlags);
  ctx->compilerFlags=newValue;
}



const char *GWB_Context_GetLinkerFlags(const GWB_CONTEXT *ctx)
{
  return ctx->linkerFlags;
}



void GWB_Context_SetLinkerFlags(GWB_CONTEXT *ctx, const char *s)
{
  if (ctx->linkerFlags)
    free(ctx->linkerFlags);
  if (s)
    ctx->linkerFlags=strdup(s);
  else
    ctx->linkerFlags=NULL;
}



void GWB_Context_AddLinkerFlags(GWB_CONTEXT *ctx, const char *s)
{
  char *newValue;

  newValue=_combinedString(ctx->linkerFlags, s, ' ');
  free(ctx->linkerFlags);
  ctx->linkerFlags=newValue;
}



GWEN_STRINGLIST *GWB_Context_GetIncludeList(const GWB_CONTEXT *ctx)
{
  return ctx->includeList;
}



void GWB_Context_AddInclude(GWB_CONTEXT *ctx, const char *folder)
{
  if (ctx->includeList==NULL)
    ctx->includeList=GWEN_StringList_new();

  GWEN_StringList_AppendString(ctx->includeList, folder, 0, 1);
}



GWB_KEYVALUEPAIR_LIST *GWB_Context_GetDefineList(const GWB_CONTEXT *ctx)
{
  return ctx->defineList;
}



void GWB_Context_SetDefine(GWB_CONTEXT *ctx, const char *name, const char *value)
{
  if (name && *name) {
    GWB_KEYVALUEPAIR *kvp;

    if (ctx->defineList==NULL)
      ctx->defineList=GWB_KeyValuePair_List_new();

    kvp=GWB_KeyValuePair_List_GetByKey(ctx->defineList, name);
    if (kvp)
      GWB_KeyValuePair_SetValue(kvp, value);
    else
    GWB_KeyValuePair_List_Add(GWB_KeyValuePair_new(name, value), ctx->defineList);
  }
}



GWEN_DB_NODE *GWB_Context_GetVars(const GWB_CONTEXT *ctx)
{
  return ctx->vars;
}



/* mindmap for my stupid brain...
   abcde  abc
   5      3     = 8 + 1 (blank) +1 (0)
   abcde abc    = 9 + '0'
   0123456789
 */

char *_combinedString(const char *string1, const char *string2, const char delim)
{
  if (string2 && *string2) {
    if (string1==NULL)
      return strdup(string2);
    else {
      int len1;
      int len2;
      char *newS;

      len1=strlen(string1);
      len2=strlen(string2);

      newS=(char*) malloc(len1+len2+2); /* blank plus trailing 0 */
      assert(newS);
      memmove(newS, string1, len1);
      newS[len1]=delim;
      memmove(newS+len1+1, string2, len2);
      newS[len1+len2+1]=0;
      return newS;
    }
  }
  else {
    if (string1)
      return strdup(string1);
    return NULL;
  }
}





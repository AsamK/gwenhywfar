/**********************************************************
 * This file has been automatically created by "typemaker2"
 * from the file "ct_keyinfo.xml".
 * Please do not edit this file, all changes will be lost.
 * Better edit the mentioned source file instead.
 **********************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "ct_keyinfo_p.h"

#include <gwenhywfar/misc.h>
#include <gwenhywfar/debug.h>

/* code headers */

/* macro functions */
GWEN_LIST_FUNCTIONS(GWEN_CRYPT_TOKEN_KEYINFO, GWEN_Crypt_Token_KeyInfo)
GWEN_LIST2_FUNCTIONS(GWEN_CRYPT_TOKEN_KEYINFO, GWEN_Crypt_Token_KeyInfo)
GWEN_INHERIT_FUNCTIONS(GWEN_CRYPT_TOKEN_KEYINFO)


GWEN_CRYPT_TOKEN_KEYSTATUS GWEN_Crypt_Token_KeyStatus_fromString(const char *p_s)
{
  if (p_s && *p_s) {
    if (strcasecmp(p_s, "free") == 0)
      return GWEN_Crypt_Token_KeyStatusFree;
    else if (strcasecmp(p_s, "new") == 0)
      return GWEN_Crypt_Token_KeyStatusNew;
    else if (strcasecmp(p_s, "active") == 0)
      return GWEN_Crypt_Token_KeyStatusActive;
  }
  return GWEN_Crypt_Token_KeyStatusUnknown;
}

const char *GWEN_Crypt_Token_KeyStatus_toString(GWEN_CRYPT_TOKEN_KEYSTATUS p_i)
{
  switch(p_i) {
  case GWEN_Crypt_Token_KeyStatusFree:
    return "free";
  case GWEN_Crypt_Token_KeyStatusNew:
    return "new";
  case GWEN_Crypt_Token_KeyStatusActive:
    return "active";
  default:
    return "unknown";
  }
}

GWEN_CRYPT_TOKEN_KEYINFO *GWEN_Crypt_Token_KeyInfo__new(void)
{
  GWEN_CRYPT_TOKEN_KEYINFO *p_struct;

  GWEN_NEW_OBJECT(GWEN_CRYPT_TOKEN_KEYINFO, p_struct)
  p_struct->_refCount = 1;
  GWEN_INHERIT_INIT(GWEN_CRYPT_TOKEN_KEYINFO, p_struct)
  GWEN_LIST_INIT(GWEN_CRYPT_TOKEN_KEYINFO, p_struct)
  /* members */
  p_struct->id = 0;
  p_struct->keyDescr = NULL;
  p_struct->flags = 0;
  p_struct->keySize = 0;
  p_struct->cryptAlgoId = 0;
  p_struct->modulus = NULL;
  p_struct->exponent = NULL;
  p_struct->keyNumber = 0;
  p_struct->keyVersion = 0;
  p_struct->signCounter = 0;
  p_struct->certificate = NULL;
  /* virtual functions */

  return p_struct;
}

void GWEN_Crypt_Token_KeyInfo_free(GWEN_CRYPT_TOKEN_KEYINFO *p_struct)
{
  if (p_struct) {
    assert(p_struct->_refCount);
    if (p_struct->_refCount == 1) {
      GWEN_INHERIT_FINI(GWEN_CRYPT_TOKEN_KEYINFO, p_struct)
      GWEN_LIST_FINI(GWEN_CRYPT_TOKEN_KEYINFO, p_struct)
      /* members */
      free(p_struct->keyDescr);
      p_struct->keyDescr = NULL;
      GWEN_Buffer_free(p_struct->modulus);
      p_struct->modulus = NULL;
      GWEN_Buffer_free(p_struct->exponent);
      p_struct->exponent = NULL;
      GWEN_Buffer_free(p_struct->certificate);
      p_struct->certificate = NULL;
      p_struct->_refCount = 0;
      GWEN_FREE_OBJECT(p_struct);
    } else
      p_struct->_refCount--;
  }
}

void GWEN_Crypt_Token_KeyInfo_Attach(GWEN_CRYPT_TOKEN_KEYINFO *p_struct)
{
  assert(p_struct);
  assert(p_struct->_refCount);
  p_struct->_refCount++;
}

GWEN_CRYPT_TOKEN_KEYINFO *GWEN_Crypt_Token_KeyInfo_dup(const GWEN_CRYPT_TOKEN_KEYINFO *p_src)
{
  GWEN_CRYPT_TOKEN_KEYINFO *p_struct;

  assert(p_src);
  p_struct = GWEN_Crypt_Token_KeyInfo__new();
  /* member "id" */
  p_struct->id = p_src->id;

  /* member "keyDescr" */
  if (p_struct->keyDescr) {
    free(p_struct->keyDescr);
    p_struct->keyDescr = NULL;
    p_struct->keyDescr = NULL;
  }
  if (p_src->keyDescr) {
    p_struct->keyDescr = strdup(p_src->keyDescr);
  }

  /* member "flags" */
  p_struct->flags = p_src->flags;

  /* member "keySize" */
  p_struct->keySize = p_src->keySize;

  /* member "cryptAlgoId" */
  p_struct->cryptAlgoId = p_src->cryptAlgoId;

  /* member "modulus" */
  if (p_struct->modulus) {
    GWEN_Buffer_free(p_struct->modulus);
    p_struct->modulus = NULL;
    p_struct->modulus = NULL;
  }
  if (p_src->modulus) {
    p_struct->modulus = GWEN_Buffer_dup(p_src->modulus);
  }

  /* member "exponent" */
  if (p_struct->exponent) {
    GWEN_Buffer_free(p_struct->exponent);
    p_struct->exponent = NULL;
    p_struct->exponent = NULL;
  }
  if (p_src->exponent) {
    p_struct->exponent = GWEN_Buffer_dup(p_src->exponent);
  }

  /* member "keyNumber" */
  p_struct->keyNumber = p_src->keyNumber;

  /* member "keyVersion" */
  p_struct->keyVersion = p_src->keyVersion;

  /* member "signCounter" */
  p_struct->signCounter = p_src->signCounter;

  /* member "certificate" */
  if (p_struct->certificate) {
    GWEN_Buffer_free(p_struct->certificate);
    p_struct->certificate = NULL;
    p_struct->certificate = NULL;
  }
  if (p_src->certificate) {
    p_struct->certificate = GWEN_Buffer_dup(p_src->certificate);
  }

  return p_struct;
}

GWEN_CRYPT_TOKEN_KEYINFO *GWEN_Crypt_Token_KeyInfo_copy(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, const GWEN_CRYPT_TOKEN_KEYINFO *p_src)
{
  assert(p_struct);
  assert(p_src);
  /* member "id" */
  p_struct->id = p_src->id;

  /* member "keyDescr" */
  if (p_struct->keyDescr) {
    free(p_struct->keyDescr);
    p_struct->keyDescr = NULL;
    p_struct->keyDescr = NULL;
  }
  if (p_src->keyDescr) {
    p_struct->keyDescr = strdup(p_src->keyDescr);
  }

  /* member "flags" */
  p_struct->flags = p_src->flags;

  /* member "keySize" */
  p_struct->keySize = p_src->keySize;

  /* member "cryptAlgoId" */
  p_struct->cryptAlgoId = p_src->cryptAlgoId;

  /* member "modulus" */
  if (p_struct->modulus) {
    GWEN_Buffer_free(p_struct->modulus);
    p_struct->modulus = NULL;
    p_struct->modulus = NULL;
  }
  if (p_src->modulus) {
    p_struct->modulus = GWEN_Buffer_dup(p_src->modulus);
  }

  /* member "exponent" */
  if (p_struct->exponent) {
    GWEN_Buffer_free(p_struct->exponent);
    p_struct->exponent = NULL;
    p_struct->exponent = NULL;
  }
  if (p_src->exponent) {
    p_struct->exponent = GWEN_Buffer_dup(p_src->exponent);
  }

  /* member "keyNumber" */
  p_struct->keyNumber = p_src->keyNumber;

  /* member "keyVersion" */
  p_struct->keyVersion = p_src->keyVersion;

  /* member "signCounter" */
  p_struct->signCounter = p_src->signCounter;

  /* member "certificate" */
  if (p_struct->certificate) {
    GWEN_Buffer_free(p_struct->certificate);
    p_struct->certificate = NULL;
    p_struct->certificate = NULL;
  }
  if (p_src->certificate) {
    p_struct->certificate = GWEN_Buffer_dup(p_src->certificate);
  }

  return p_struct;
}

uint32_t GWEN_Crypt_Token_KeyInfo_GetId(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct)
{
  assert(p_struct);
  return p_struct->id;
}

const char *GWEN_Crypt_Token_KeyInfo_GetKeyDescr(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct)
{
  assert(p_struct);
  return p_struct->keyDescr;
}

uint32_t GWEN_Crypt_Token_KeyInfo_GetFlags(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct)
{
  assert(p_struct);
  return p_struct->flags;
}

int GWEN_Crypt_Token_KeyInfo_GetKeySize(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct)
{
  assert(p_struct);
  return p_struct->keySize;
}

int GWEN_Crypt_Token_KeyInfo_GetCryptAlgoId(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct)
{
  assert(p_struct);
  return p_struct->cryptAlgoId;
}

uint32_t GWEN_Crypt_Token_KeyInfo_GetKeyNumber(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct)
{
  assert(p_struct);
  return p_struct->keyNumber;
}

uint32_t GWEN_Crypt_Token_KeyInfo_GetKeyVersion(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct)
{
  assert(p_struct);
  return p_struct->keyVersion;
}

uint32_t GWEN_Crypt_Token_KeyInfo_GetSignCounter(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct)
{
  assert(p_struct);
  return p_struct->signCounter;
}

void GWEN_Crypt_Token_KeyInfo_SetId(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, uint32_t p_src)
{
  assert(p_struct);
  p_struct->id = p_src;
}

void GWEN_Crypt_Token_KeyInfo_SetKeyDescr(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, const char *p_src)
{
  assert(p_struct);
  if (p_struct->keyDescr) {
    free(p_struct->keyDescr);
    p_struct->keyDescr = NULL;
  }
  if (p_src) {
    p_struct->keyDescr = strdup(p_src);
  } else {
    p_struct->keyDescr = NULL;
  }
}

void GWEN_Crypt_Token_KeyInfo_SetFlags(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, uint32_t p_src)
{
  assert(p_struct);
  p_struct->flags = p_src;
}

void GWEN_Crypt_Token_KeyInfo_AddFlags(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, uint32_t p_src)
{
  assert(p_struct);
  p_struct->flags |= p_src;
}

void GWEN_Crypt_Token_KeyInfo_SubFlags(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, uint32_t p_src)
{
  assert(p_struct);
  p_struct->flags &= ~p_src;
}

void GWEN_Crypt_Token_KeyInfo_SetKeySize(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, int p_src)
{
  assert(p_struct);
  p_struct->keySize = p_src;
}

void GWEN_Crypt_Token_KeyInfo_SetCryptAlgoId(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, int p_src)
{
  assert(p_struct);
  p_struct->cryptAlgoId = p_src;
}

void GWEN_Crypt_Token_KeyInfo_SetKeyNumber(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, uint32_t p_src)
{
  assert(p_struct);
  p_struct->keyNumber = p_src;
}

void GWEN_Crypt_Token_KeyInfo_SetKeyVersion(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, uint32_t p_src)
{
  assert(p_struct);
  p_struct->keyVersion = p_src;
}

void GWEN_Crypt_Token_KeyInfo_SetSignCounter(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, uint32_t p_src)
{
  assert(p_struct);
  p_struct->signCounter = p_src;
}

/* list1 functions */
GWEN_CRYPT_TOKEN_KEYINFO_LIST *GWEN_Crypt_Token_KeyInfo_List_dup(const GWEN_CRYPT_TOKEN_KEYINFO_LIST *p_src)
{
  GWEN_CRYPT_TOKEN_KEYINFO_LIST *p_dest;
  GWEN_CRYPT_TOKEN_KEYINFO *p_elem;

  assert(p_src);
  p_dest = GWEN_Crypt_Token_KeyInfo_List_new();
  p_elem = GWEN_Crypt_Token_KeyInfo_List_First(p_src);
  while(p_elem) {
    GWEN_CRYPT_TOKEN_KEYINFO *p_cpy;

    p_cpy = GWEN_Crypt_Token_KeyInfo_dup(p_elem);
    GWEN_Crypt_Token_KeyInfo_List_Add(p_cpy, p_dest);
    p_elem = GWEN_Crypt_Token_KeyInfo_List_Next(p_elem);
  }

  return p_dest;
}

void GWEN_Crypt_Token_KeyInfo_ReadDb(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, GWEN_DB_NODE *p_db)
{
  assert(p_struct);
  /* member "id" */
  p_struct->id = GWEN_DB_GetIntValue(p_db, "id", 0, 0);

  /* member "keyDescr" */
  if (p_struct->keyDescr) {
    free(p_struct->keyDescr);
    p_struct->keyDescr = NULL;
  }
  {
    const char *s;
    s = GWEN_DB_GetCharValue(p_db, "keyDescr", 0, NULL);
    if (s) p_struct->keyDescr = strdup(s);
  }
  if (p_struct->keyDescr == NULL) {
    p_struct->keyDescr = NULL;
  }

  /* member "flags" */
  p_struct->flags = GWEN_DB_GetIntValue(p_db, "flags", 0, 0);

  /* member "keySize" */
  p_struct->keySize = GWEN_DB_GetIntValue(p_db, "keySize", 0, 0);

  /* member "cryptAlgoId" */
  p_struct->cryptAlgoId = GWEN_DB_GetIntValue(p_db, "cryptAlgoId", 0, 0);

  /* member "modulus" */
  if (p_struct->modulus) {
    GWEN_Buffer_free(p_struct->modulus);
    p_struct->modulus = NULL;
  }
  {
    const uint8_t *ptr;
    uint32_t len;
    ptr = GWEN_DB_GetBinValue(p_db, "modulus", 0, NULL, 0, &len);
    if (ptr && len) {
      p_struct->modulus = GWEN_Buffer_new(0, len, 0, 1);
      GWEN_Buffer_AppendBytes(p_struct->modulus, (const char*)ptr, len);
    }
  }
  if (p_struct->modulus == NULL) {
    p_struct->modulus = NULL;
  }

  /* member "exponent" */
  if (p_struct->exponent) {
    GWEN_Buffer_free(p_struct->exponent);
    p_struct->exponent = NULL;
  }
  {
    const uint8_t *ptr;
    uint32_t len;
    ptr = GWEN_DB_GetBinValue(p_db, "exponent", 0, NULL, 0, &len);
    if (ptr && len) {
      p_struct->exponent = GWEN_Buffer_new(0, len, 0, 1);
      GWEN_Buffer_AppendBytes(p_struct->exponent, (const char*)ptr, len);
    }
  }
  if (p_struct->exponent == NULL) {
    p_struct->exponent = NULL;
  }

  /* member "keyNumber" */
  p_struct->keyNumber = GWEN_DB_GetIntValue(p_db, "keyNumber", 0, 0);

  /* member "keyVersion" */
  p_struct->keyVersion = GWEN_DB_GetIntValue(p_db, "keyVersion", 0, 0);

  /* member "signCounter" */
  p_struct->signCounter = GWEN_DB_GetIntValue(p_db, "signCounter", 0, 0);

  /* member "certificate" */
  if (p_struct->certificate) {
    GWEN_Buffer_free(p_struct->certificate);
    p_struct->certificate = NULL;
  }
  {
    const uint8_t *ptr;
    uint32_t len;
    ptr = GWEN_DB_GetBinValue(p_db, "certificate", 0, NULL, 0, &len);
    if (ptr && len) {
      p_struct->certificate = GWEN_Buffer_new(0, len, 0, 1);
      GWEN_Buffer_AppendBytes(p_struct->certificate, (const char*)ptr, len);
    }
  }
  if (p_struct->certificate == NULL) {
    p_struct->certificate = NULL;
  }

}

int GWEN_Crypt_Token_KeyInfo_WriteDb(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct, GWEN_DB_NODE *p_db)
{
  int p_rv;

  assert(p_struct);
  /* member "id" */
  p_rv = GWEN_DB_SetIntValue(p_db, GWEN_DB_FLAGS_OVERWRITE_VARS, "id", p_struct->id);
  if (p_rv < 0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  /* member "keyDescr" */
  if (p_struct->keyDescr) p_rv = GWEN_DB_SetCharValue(p_db, GWEN_DB_FLAGS_OVERWRITE_VARS, "keyDescr", p_struct->keyDescr);
  else {
    GWEN_DB_DeleteVar(p_db, "keyDescr");
    p_rv = 0;
  }
  if (p_rv < 0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  /* member "flags" */
  p_rv = GWEN_DB_SetIntValue(p_db, GWEN_DB_FLAGS_OVERWRITE_VARS, "flags", p_struct->flags);
  if (p_rv < 0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  /* member "keySize" */
  p_rv = GWEN_DB_SetIntValue(p_db, GWEN_DB_FLAGS_OVERWRITE_VARS, "keySize", p_struct->keySize);
  if (p_rv < 0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  /* member "cryptAlgoId" */
  p_rv = GWEN_DB_SetIntValue(p_db, GWEN_DB_FLAGS_OVERWRITE_VARS, "cryptAlgoId", p_struct->cryptAlgoId);
  if (p_rv < 0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  /* member "modulus" */
  if (p_struct->modulus) p_rv = GWEN_DB_SetBinValue(p_db, GWEN_DB_FLAGS_OVERWRITE_VARS, "modulus", GWEN_Buffer_GetStart(p_struct->modulus), GWEN_Buffer_GetUsedBytes(p_struct->modulus));
  else {
    GWEN_DB_DeleteVar(p_db, "modulus");
    p_rv = 0;
  }
  if (p_rv < 0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  /* member "exponent" */
  if (p_struct->exponent) p_rv = GWEN_DB_SetBinValue(p_db, GWEN_DB_FLAGS_OVERWRITE_VARS, "exponent", GWEN_Buffer_GetStart(p_struct->exponent), GWEN_Buffer_GetUsedBytes(p_struct->exponent));
  else {
    GWEN_DB_DeleteVar(p_db, "exponent");
    p_rv = 0;
  }
  if (p_rv < 0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  /* member "keyNumber" */
  p_rv = GWEN_DB_SetIntValue(p_db, GWEN_DB_FLAGS_OVERWRITE_VARS, "keyNumber", p_struct->keyNumber);
  if (p_rv < 0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  /* member "keyVersion" */
  p_rv = GWEN_DB_SetIntValue(p_db, GWEN_DB_FLAGS_OVERWRITE_VARS, "keyVersion", p_struct->keyVersion);
  if (p_rv < 0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  /* member "signCounter" */
  p_rv = GWEN_DB_SetIntValue(p_db, GWEN_DB_FLAGS_OVERWRITE_VARS, "signCounter", p_struct->signCounter);
  if (p_rv < 0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  /* member "certificate" */
  if (p_struct->certificate) p_rv = GWEN_DB_SetBinValue(p_db, GWEN_DB_FLAGS_OVERWRITE_VARS, "certificate", GWEN_Buffer_GetStart(p_struct->certificate), GWEN_Buffer_GetUsedBytes(p_struct->certificate));
  else {
    GWEN_DB_DeleteVar(p_db, "certificate");
    p_rv = 0;
  }
  if (p_rv < 0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  return 0;
}

GWEN_CRYPT_TOKEN_KEYINFO *GWEN_Crypt_Token_KeyInfo_fromDb(GWEN_DB_NODE *p_db)
{
  GWEN_CRYPT_TOKEN_KEYINFO *p_struct;
  p_struct = GWEN_Crypt_Token_KeyInfo__new();
  GWEN_Crypt_Token_KeyInfo_ReadDb(p_struct, p_db);
  return p_struct;
}

int GWEN_Crypt_Token_KeyInfo_toDb(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct, GWEN_DB_NODE *p_db)
{
  return GWEN_Crypt_Token_KeyInfo_WriteDb(p_struct, p_db);
}

void GWEN_Crypt_Token_KeyInfo_ReadXml(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, GWEN_XMLNODE *p_db)
{
  assert(p_struct);
  /* member "id" */
  p_struct->id = GWEN_XMLNode_GetIntValue(p_db, "id", 0);

  /* member "keyDescr" */
  if (p_struct->keyDescr) {
    free(p_struct->keyDescr);
    p_struct->keyDescr = NULL;
  }
  {
    const char *s;
    s = GWEN_XMLNode_GetCharValue(p_db, "keyDescr", NULL);
    if (s) p_struct->keyDescr = strdup(s);
  }
  if (p_struct->keyDescr == NULL) { /* preset member "keyDescr" if empty */
    p_struct->keyDescr = NULL;
  }

  /* member "flags" */
  p_struct->flags = GWEN_XMLNode_GetIntValue(p_db, "flags", 0);

  /* member "keySize" */
  p_struct->keySize = GWEN_XMLNode_GetIntValue(p_db, "keySize", 0);

  /* member "cryptAlgoId" */
  p_struct->cryptAlgoId = GWEN_XMLNode_GetIntValue(p_db, "cryptAlgoId", 0);

  /* member "modulus" */
  if (p_struct->modulus) {
    GWEN_Buffer_free(p_struct->modulus);
    p_struct->modulus = NULL;
  }
  {
    const char *s;
    s = GWEN_XMLNode_GetCharValue(p_db, "modulus", NULL);
    if (s) {
      p_struct->modulus = GWEN_Buffer_new(0, strlen(s) / 2, 0, 1);
      GWEN_Text_FromHexBuffer(s, p_struct->modulus);
    }
  }
  if (p_struct->modulus == NULL) { /* preset member "modulus" if empty */
    p_struct->modulus = NULL;
  }

  /* member "exponent" */
  if (p_struct->exponent) {
    GWEN_Buffer_free(p_struct->exponent);
    p_struct->exponent = NULL;
  }
  {
    const char *s;
    s = GWEN_XMLNode_GetCharValue(p_db, "exponent", NULL);
    if (s) {
      p_struct->exponent = GWEN_Buffer_new(0, strlen(s) / 2, 0, 1);
      GWEN_Text_FromHexBuffer(s, p_struct->exponent);
    }
  }
  if (p_struct->exponent == NULL) { /* preset member "exponent" if empty */
    p_struct->exponent = NULL;
  }

  /* member "keyNumber" */
  p_struct->keyNumber = GWEN_XMLNode_GetIntValue(p_db, "keyNumber", 0);

  /* member "keyVersion" */
  p_struct->keyVersion = GWEN_XMLNode_GetIntValue(p_db, "keyVersion", 0);

  /* member "signCounter" */
  p_struct->signCounter = GWEN_XMLNode_GetIntValue(p_db, "signCounter", 0);

  /* member "certificate" */
  if (p_struct->certificate) {
    GWEN_Buffer_free(p_struct->certificate);
    p_struct->certificate = NULL;
  }
  {
    const char *s;
    s = GWEN_XMLNode_GetCharValue(p_db, "certificate", NULL);
    if (s) {
      p_struct->certificate = GWEN_Buffer_new(0, strlen(s) / 2, 0, 1);
      GWEN_Text_FromHexBuffer(s, p_struct->certificate);
    }
  }
  if (p_struct->certificate == NULL) { /* preset member "certificate" if empty */
    p_struct->certificate = NULL;
  }

}

void GWEN_Crypt_Token_KeyInfo_WriteXml(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct, GWEN_XMLNODE *p_db)
{
  assert(p_struct);
  /* member "id" */
  GWEN_XMLNode_SetIntValue(p_db, "id", p_struct->id);

  /* member "keyDescr" */
  GWEN_XMLNode_SetCharValue(p_db, "keyDescr", p_struct->keyDescr);

  /* member "flags" */
  GWEN_XMLNode_SetIntValue(p_db, "flags", p_struct->flags);

  /* member "keySize" */
  GWEN_XMLNode_SetIntValue(p_db, "keySize", p_struct->keySize);

  /* member "cryptAlgoId" */
  GWEN_XMLNode_SetIntValue(p_db, "cryptAlgoId", p_struct->cryptAlgoId);

  /* member "modulus" */
  if (p_struct->modulus) {
    GWEN_BUFFER *tbuf;
    tbuf = GWEN_Buffer_new(0, GWEN_Buffer_GetUsedBytes(p_struct->modulus) * 2, 0, 1);
    GWEN_Text_ToHexBuffer(GWEN_Buffer_GetStart(p_struct->modulus), GWEN_Buffer_GetUsedBytes(p_struct->modulus), tbuf, 0, 0, 0);
    GWEN_XMLNode_SetCharValue(p_db, "modulus", GWEN_Buffer_GetStart(tbuf));
    GWEN_Buffer_free(tbuf);
  }

  /* member "exponent" */
  if (p_struct->exponent) {
    GWEN_BUFFER *tbuf;
    tbuf = GWEN_Buffer_new(0, GWEN_Buffer_GetUsedBytes(p_struct->exponent) * 2, 0, 1);
    GWEN_Text_ToHexBuffer(GWEN_Buffer_GetStart(p_struct->exponent), GWEN_Buffer_GetUsedBytes(p_struct->exponent), tbuf, 0, 0, 0);
    GWEN_XMLNode_SetCharValue(p_db, "exponent", GWEN_Buffer_GetStart(tbuf));
    GWEN_Buffer_free(tbuf);
  }

  /* member "keyNumber" */
  GWEN_XMLNode_SetIntValue(p_db, "keyNumber", p_struct->keyNumber);

  /* member "keyVersion" */
  GWEN_XMLNode_SetIntValue(p_db, "keyVersion", p_struct->keyVersion);

  /* member "signCounter" */
  GWEN_XMLNode_SetIntValue(p_db, "signCounter", p_struct->signCounter);

  /* member "certificate" */
  if (p_struct->certificate) {
    GWEN_BUFFER *tbuf;
    tbuf = GWEN_Buffer_new(0, GWEN_Buffer_GetUsedBytes(p_struct->certificate) * 2, 0, 1);
    GWEN_Text_ToHexBuffer(GWEN_Buffer_GetStart(p_struct->certificate), GWEN_Buffer_GetUsedBytes(p_struct->certificate), tbuf, 0, 0, 0);
    GWEN_XMLNode_SetCharValue(p_db, "certificate", GWEN_Buffer_GetStart(tbuf));
    GWEN_Buffer_free(tbuf);
  }

}

void GWEN_Crypt_Token_KeyInfo_toXml(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct, GWEN_XMLNODE *p_db)
{
  GWEN_Crypt_Token_KeyInfo_WriteXml(p_struct, p_db);
}

GWEN_CRYPT_TOKEN_KEYINFO *GWEN_Crypt_Token_KeyInfo_fromXml(GWEN_XMLNODE *p_db)
{
  GWEN_CRYPT_TOKEN_KEYINFO *p_struct;
  p_struct = GWEN_Crypt_Token_KeyInfo__new();
  GWEN_Crypt_Token_KeyInfo_ReadXml(p_struct, p_db);
  return p_struct;
}

GWEN_CRYPT_TOKEN_KEYINFO *GWEN_Crypt_Token_KeyInfo_List_GetById(const GWEN_CRYPT_TOKEN_KEYINFO_LIST *p_list, uint32_t p_cmp)
{
  GWEN_CRYPT_TOKEN_KEYINFO *p_struct;

  assert(p_list);
  p_struct = GWEN_Crypt_Token_KeyInfo_List_First(p_list);
  while(p_struct) {
    int p_rv;

    if (p_struct->id == p_cmp) p_rv = 0;
    else if (p_cmp < p_struct->id) p_rv = -1;
    else p_rv = 1;
    if (p_rv == 0)
      return p_struct;
    p_struct = GWEN_Crypt_Token_KeyInfo_List_Next(p_struct);
  }
  return NULL;
}

GWEN_CRYPT_TOKEN_KEYINFO *GWEN_Crypt_Token_KeyInfo_new(uint32_t kid, GWEN_CRYPT_CRYPTALGOID a, int keySize)
{
  GWEN_CRYPT_TOKEN_KEYINFO *ki;
  ki = GWEN_Crypt_Token_KeyInfo__new();
  ki->id = kid;
  ki->cryptAlgoId = a;
  ki->keySize = keySize;
  return ki;
}
void GWEN_Crypt_Token_KeyInfo_SetModulus(GWEN_CRYPT_TOKEN_KEYINFO *st, const uint8_t *p, uint32_t len)
{
  assert(st);
  if (st->modulus) GWEN_Buffer_free(st->modulus);
  if (p && len) {
    st->modulus = GWEN_Buffer_new(0, len, 0, 1);
    GWEN_Buffer_AppendBytes(st->modulus, (const char*) p, len);
  } else st->modulus = NULL;
}
const uint8_t* GWEN_Crypt_Token_KeyInfo_GetModulusData(const GWEN_CRYPT_TOKEN_KEYINFO *st)
{
  assert(st);
  if (st->modulus) return (const uint8_t*) GWEN_Buffer_GetStart(st->modulus);
  else return NULL;
}
uint32_t GWEN_Crypt_Token_KeyInfo_GetModulusLen(const GWEN_CRYPT_TOKEN_KEYINFO *st)
{
  assert(st);
  if (st->modulus) return GWEN_Buffer_GetUsedBytes(st->modulus);
  else return 0;
}
void GWEN_Crypt_Token_KeyInfo_SetExponent(GWEN_CRYPT_TOKEN_KEYINFO *st, const uint8_t *p, uint32_t len)
{
  assert(st);
  if (st->exponent) GWEN_Buffer_free(st->exponent);
  if (p && len) {
    st->exponent = GWEN_Buffer_new(0, len, 0, 1);
    GWEN_Buffer_AppendBytes(st->exponent, (const char*) p, len);
  } else st->exponent = NULL;
}
const uint8_t* GWEN_Crypt_Token_KeyInfo_GetExponentData(const GWEN_CRYPT_TOKEN_KEYINFO *st)
{
  assert(st);
  if (st->exponent) return (const uint8_t*) GWEN_Buffer_GetStart(st->exponent);
  else return NULL;
}
uint32_t GWEN_Crypt_Token_KeyInfo_GetExponentLen(const GWEN_CRYPT_TOKEN_KEYINFO *st)
{
  assert(st);
  if (st->exponent) return GWEN_Buffer_GetUsedBytes(st->exponent);
  else return 0;
}
void GWEN_Crypt_Token_KeyInfo_SetCertificate(GWEN_CRYPT_TOKEN_KEYINFO *st, const uint8_t *p, uint32_t len)
{
  assert(st);
  if (st->certificate) GWEN_Buffer_free(st->certificate);
  if (p && len) {
    st->certificate = GWEN_Buffer_new(0, len, 0, 1);
    GWEN_Buffer_AppendBytes(st->certificate, (const char*) p, len);
  } else st->certificate = NULL;
}
const uint8_t* GWEN_Crypt_Token_KeyInfo_GetCertificateData(const GWEN_CRYPT_TOKEN_KEYINFO *st)
{
  assert(st);
  if (st->certificate) return (const uint8_t*) GWEN_Buffer_GetStart(st->certificate);
  else return NULL;
}
uint32_t GWEN_Crypt_Token_KeyInfo_GetCertificateLen(const GWEN_CRYPT_TOKEN_KEYINFO *st)
{
  assert(st);
  if (st->certificate) return GWEN_Buffer_GetUsedBytes(st->certificate);
  else return 0;
}

/* code headers */


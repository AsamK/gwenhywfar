/***************************************************************************
 $RCSfile$
 -------------------
 cvs         : $Id$
 begin       : Fri Jul 04 2003
 copyright   : (C) 2003 by Martin Preuss
 email       : martin@libchipcard.de

 ***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif


#include <gwenhyfwar/gwenhyfwarapi.h>
#include <msgengine_p.h>
#include <gwenhyfwar/xml.h>
#include <gwenhyfwar/text.h>
#include <gwenhyfwar/misc.h>
#include <gwenhyfwar/path.h>
#include <gwenhyfwar/debug.h>
#include <gwenhyfwar/buffer.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>



GWEN_MSGENGINE *GWEN_MsgEngine_new(){
  GWEN_MSGENGINE *e;

  GWEN_NEW_OBJECT(GWEN_MSGENGINE, e);
  e->charsToEscape=strdup(GWEN_MSGENGINE_CHARSTOESCAPE);
  e->delimiters=strdup(GWEN_MSGENGINE_DEFAULT_DELIMITERS);
  e->globalValues=GWEN_DB_Group_new("globalvalues");
  return e;
}


void GWEN_MsgEngine_free(GWEN_MSGENGINE *e){
  if (e) {
    GWEN_XMLNode_free(e->defs);
    free(e->charsToEscape);
    free(e->secMode);
    GWEN_DB_Group_free(e->globalValues);
  }
}


void GWEN_MsgEngine_SetFormat(GWEN_MSGENGINE *e, GWEN_MSGENGINE_FORMAT f){
  assert(e);
  e->msgFormat=f;
}



GWEN_MSGENGINE_FORMAT GWEN_MsgEngine_GetFormat(GWEN_MSGENGINE *e){
  assert(e);
  return e->msgFormat;
}



void GWEN_MsgEngine_SetEscapeChar(GWEN_MSGENGINE *e, char c){
  assert(e);
  e->escapeChar=c;
}



char GWEN_MsgEngine_GetEscapeChar(GWEN_MSGENGINE *e){
  assert(e);
  return e->escapeChar;
}



void GWEN_MsgEngine_SetCharsToEscape(GWEN_MSGENGINE *e, const char *c){
  assert(e);
  free(e->charsToEscape);
  e->charsToEscape=strdup(c);
}



const char *GWEN_MsgEngine_GetCharsToEscape(GWEN_MSGENGINE *e){
  assert(e);
  return e->charsToEscape;
}



void GWEN_MsgEngine_SetMode(GWEN_MSGENGINE *e, const char *mode){
  assert(e);
  free(e->secMode);
  if (mode)
    e->secMode=strdup(mode);
  else
    e->secMode=0;
}


const char *GWEN_MsgEngine_GetMode(GWEN_MSGENGINE *e){
  assert(e);
  return e->secMode;
}




unsigned int GWEN_MsgEngine_GetConfigMode(GWEN_MSGENGINE *e){
  assert(e);
  return e->cfgMode;
}


void GWEN_MsgEngine_SetConfigMode(GWEN_MSGENGINE *e, unsigned int m){
  assert(e);
  e->cfgMode=m;
}


GWEN_XMLNODE *GWEN_MsgEngine_GetDefinitions(GWEN_MSGENGINE *e){
  assert(e);
  return e->defs;
}


void GWEN_MsgEngine_SetDefinitions(GWEN_MSGENGINE *e, GWEN_XMLNODE *n){
  assert(e);
  GWEN_XMLNode_free(e->defs);
  e->defs=n;
}



void GWEN_MsgEngine_SetTypeCheckFunction(GWEN_MSGENGINE *e,
                                         GWEN_MSGENGINE_TYPECHECK_PTR p){
  assert(e);
  e->typeCheckPtr=p;
}



GWEN_MSGENGINE_TYPECHECK_PTR
GWEN_MsgEngine_GetTypeCheckFunction(GWEN_MSGENGINE *e){
  assert(e);
  return e->typeCheckPtr;
}



void GWEN_MsgEngine_SetTypeReadFunction(GWEN_MSGENGINE *e,
                                        GWEN_MSGENGINE_TYPEREAD_PTR p){
  assert(e);
  e->typeReadPtr=p;
}



GWEN_MSGENGINE_TYPEREAD_PTR
GWEN_MsgEngine_GetTypeReadFunction(GWEN_MSGENGINE *e){
  assert(e);
  return e->typeReadPtr;
}



void GWEN_MsgEngine_SetTypeWriteFunction(GWEN_MSGENGINE *e,
                                         GWEN_MSGENGINE_TYPEWRITE_PTR p){
  assert(e);
  e->typeWritePtr=p;
}



GWEN_MSGENGINE_TYPEWRITE_PTR
GWEN_MsgEngine_GetTypeWriteFunction(GWEN_MSGENGINE *e){
  assert(e);
  return e->typeWritePtr;
}



void GWEN_MsgEngine_SetBinTypeReadFunction(GWEN_MSGENGINE *e,
                                           GWEN_MSGENGINE_BINTYPEREAD_PTR p){
  assert(e);
  e->binTypeReadPtr=p;
}



GWEN_MSGENGINE_BINTYPEREAD_PTR
GWEN_MsgEngine_GetBinTypeReadFunction(GWEN_MSGENGINE *e){
  assert(e);
  return e->binTypeReadPtr;
}



void
GWEN_MsgEngine_SetBinTypeWriteFunction(GWEN_MSGENGINE *e,
                                       GWEN_MSGENGINE_BINTYPEWRITE_PTR p){
  assert(e);
  e->binTypeWritePtr=p;
}



GWEN_MSGENGINE_BINTYPEWRITE_PTR
GWEN_MsgEngine_GetBinTypeWriteFunction(GWEN_MSGENGINE *e){
  assert(e);
  return e->binTypeWritePtr;
}





void *GWEN_MsgEngine_GetInheritorData(GWEN_MSGENGINE *e){
  assert(e);
  return e->inheritorData;
}



void GWEN_MsgEngine_SetInheritorData(GWEN_MSGENGINE *e, void *d){
  assert(e);
  e->inheritorData=d;
}



int GWEN_MsgEngine__CheckValue(GWEN_MSGENGINE *e,
                               const char *value,
                               GWEN_XMLNODE *node,
                               char escapeChar) {
  unsigned int len;
  const char *p;
  unsigned int minsize;
  unsigned int maxsize;
  const char *type;
  int rv;

  p=value;
  len=0;

  /* get some sizes */
  minsize=atoi(GWEN_XMLNode_GetProperty(node, "minsize","0"));
  maxsize=atoi(GWEN_XMLNode_GetProperty(node, "maxsize","0"));
  type=GWEN_XMLNode_GetProperty(node, "type","ASCII");

  rv=1;
  if (e->typeCheckPtr) {
    rv=e->typeCheckPtr(e,
		       value,
		       node,
		       escapeChar);
  }
  if (rv==-1){
    DBG_INFO(0, "External type check failed");
    return -1;
  }
  else if (rv==1) {
    if (strcasecmp(type,"AN")==0) {
      int lastWasEscape;

      lastWasEscape=0;
      while(*p) {
	int c;

	c=(unsigned char)*p;
	if (c<32) {
	  DBG_ERROR(0, "Unescaped control character in value");
	  return -1;
	}
	if (lastWasEscape) {
	  lastWasEscape=0;
	  switch(c) {
	  case 'r': c='\r'; break;
	  case 'n': c='\n'; break;
	  case 'f': c='\f'; break;
	  case 't': c='\t'; break;
	  default: c=(unsigned char)*p;
	  } /* switch */
	}
	else {
	  if (*p==escapeChar) {
	    lastWasEscape=1;
	    len--;
	    c=-1;
	  }
	  else
	    c=(unsigned char)*p;
	}
	if (c!=-1) {
          /* ugly workaround */
	  if (iscntrl(c)) {
	    DBG_ERROR(0, "Non-alphanumeric character in value");
	    return -1;
	  }
	}
	p++;
	len++;
      } /* while */
    }
    else if (strcasecmp(type,"ALPHA")==0) {
      int lastWasEscape;

      lastWasEscape=0;
      while(*p) {
	int c;

	c=(unsigned char)*p;
	if (c<32) {
	  DBG_ERROR(0, "Unescaped control character in value");
	  return -1;
	}
	if (lastWasEscape) {
	  lastWasEscape=0;
	  switch(c) {
	  case 'r': c='\r'; break;
	  case 'n': c='\n'; break;
	  case 'f': c='\f'; break;
	  case 't': c='\t'; break;
	  default: c=(unsigned char)*p;
	  } /* switch */
	}
	else {
	  if (*p==escapeChar) {
	    lastWasEscape=1;
	    len--;
	    c=-1;
	  }
	  else
	    c=(unsigned char)*p;
	}
	if (c!=-1) {
	  if (!isalpha(c)) {
	    DBG_ERROR(0, "Non-alpha character in value");
	    return -1;
	  }
	}
	p++;
	len++;
      } /* while */
    }
    else if (strcasecmp(type,"ASCII")==0) {
      int lastWasEscape;

      lastWasEscape=0;
      while(*p) {
	int c;

	c=(unsigned char)*p;
	if (c<32) {
	  DBG_ERROR(0, "Unescaped control character in value");
	  return -1;
	}

	if (lastWasEscape) {
	  lastWasEscape=0;
	  switch(c) {
	  case 'r': c='\r'; break;
	  case 'n': c='\n'; break;
	  case 'f': c='\f'; break;
	  case 't': c='\t'; break;
	  default: c=(unsigned char)*p;
	  } /* switch */
	}
	else {
	  if (*p==escapeChar) {
	    lastWasEscape=1;
	    len--;
	    c=-1;
	  }
	  else
	    c=(unsigned char)*p;
	}
	if (c!=-1) {
#ifdef isascii
	  if (!isascii(c)) {
	    DBG_ERROR(0, "Non-ASCII character in value");
	    return -1;
	  }
#else
	  if (c>127 || c<32) {
	    DBG_ERROR(0, "Non-ASCII character in value");
	    return -1;
	  }
#endif
	}
	p++;
	len++;
      } /* while */
    }
    else if (strcasecmp(type,"NUM")==0) {
      int lastWasEscape;

      lastWasEscape=0;
      while(*p) {
	int c;

	c=(unsigned char)*p;
	if (c<32) {
	  DBG_ERROR(0, "Unescaped control character in value");
	  return -1;
	}

	if (lastWasEscape) {
	  lastWasEscape=0;
	  switch(c) {
	  case 'r': c='\r'; break;
	  case 'n': c='\n'; break;
	  case 'f': c='\f'; break;
	  case 't': c='\t'; break;
	  default: c=(unsigned char)*p;
	  } /* switch */
	}
	else {
	  if (*p==escapeChar) {
	    lastWasEscape=1;
	    len--;
	    c=-1;
	  }
	  else
	    c=(unsigned char)*p;
	}
	if (c!=-1) {
	  if (!isdigit(c)) {
	    DBG_ERROR(0, "Non-alphanumeric character in value");
	    return -1;
	  }
	}
	p++;
	len++;
      } /* while */
    }
    else if (strcasecmp(type,"HEX")==0 ||
	     strcasecmp(type,"BIN")==0) {
      int lastWasEscape;

      lastWasEscape=0;
      while(*p) {
	int c;

	c=(unsigned char)*p;
	if (c<32) {
	  DBG_ERROR(0, "Unescaped control character in value");
	  return -1;
	}

	if (lastWasEscape) {
	  lastWasEscape=0;
	  switch(c) {
	  case 'r': c='\r'; break;
	  case 'n': c='\n'; break;
	  case 'f': c='\f'; break;
	  case 't': c='\t'; break;
	  default: c=(unsigned char)*p;
	  } /* switch */
	}
	else {
	  if (*p==escapeChar) {
	    lastWasEscape=1;
	    len--;
	    c=-1;
	  }
	  else
	    c=(unsigned char)*p;
	}
	if (c!=-1) {
	  if (!isxdigit(c)) {
	    DBG_ERROR(0, "Non-hex character in value");
	    return -1;
	  }
	}
	p++;
	len++;
      } /* while */
      if (len&1) {
	DBG_ERROR(0, "Uneven number of hex characters in value");
	return -1;
      }
      if (strcasecmp(type,"BIN")==0) {
	char lbuffer[32];

	sprintf(lbuffer, "@%d@", len);
	len=len/2; /* only half the size needed for binary data */
      }
    }
    else if (strcasecmp(type,"FLOAT")==0) {
      float f;

      if (sscanf(value, "%f", &f)!=1) {
	DBG_ERROR(0, "Bad float value \"%s\"", value);
      }
      len=strlen(value);
    }
    else {
      DBG_ERROR(0, "Unknown type \"%s\"", type);
      return -1;
    }

    if (minsize && len<minsize) {
      DBG_ERROR(0, "Value too short (%d<%d)", len, minsize);
      return -1;
    }
    if (maxsize && len>maxsize) {
      DBG_ERROR(0, "Value too long (%d>%d)", len, maxsize);
      return -1;
    }
  } /* if not external type */

  DBG_DEBUG(0, "Type check ok");
  return 0;
}



int GWEN_MsgEngine__WriteValue(GWEN_MSGENGINE *e,
                               GWEN_BUFFER *gbuf,
                               GWEN_BUFFER *data,
                               GWEN_XMLNODE *node) {
  unsigned int minsize;
  unsigned int maxsize;
  const char *type;
  int rv;

  /* get some sizes */
  minsize=atoi(GWEN_XMLNode_GetProperty(node, "minsize","0"));
  maxsize=atoi(GWEN_XMLNode_GetProperty(node, "maxsize","0"));
  type=GWEN_XMLNode_GetProperty(node, "type","ASCII");

  /* copy value to buffer */
  rv=1;
  if (e->typeWritePtr) {
    rv=e->typeWritePtr(e,
                       gbuf,
                       data,
                       node);
  }
  if (rv==-1) {
    DBG_INFO(0, "External type writing failed");
    return -1;
  }
  else if (rv==1) {
    int i;

    /* type not handled externally, so handle it myself */
    if (strcasecmp(type, "bin")==0) {
      if (GWEN_Buffer_RoomLeft(gbuf)<10+GWEN_Buffer_GetUsedBytes(data)) {
        DBG_ERROR(0, "Buffer too small");
        return -1;
      }
      sprintf(GWEN_Buffer_GetPosPointer(gbuf),
              "@%d@",
              GWEN_Buffer_GetUsedBytes(data));


      i=strlen(GWEN_Buffer_GetPosPointer(gbuf));
      GWEN_Buffer_IncrementPos(gbuf, i);
      GWEN_Buffer_AppendBuffer(gbuf, data);
    } /* if type is "bin" */
    else if (strcasecmp(type, "num")==0) {
      int num;
      int len;
      int lj;

      num=atoi(GWEN_Buffer_GetPosPointer(data));
      len=strlen(GWEN_Buffer_GetPosPointer(data));

      if (atoi(GWEN_XMLNode_GetProperty(node, "leftfill","0"))) {
        if ((maxsize+1)>=GWEN_Buffer_RoomLeft(gbuf)) {
          DBG_ERROR(0, "Buffer too small");
          return -1;
        }

        /* fill left */
        for (lj=0; lj<(maxsize-len); lj++)
          GWEN_Buffer_AppendByte(gbuf, '0');

	/* write value */
	for (lj=0; lj<len; lj++)
          GWEN_Buffer_AppendByte(gbuf, GWEN_Buffer_ReadByte(data));
      }
      else if (atoi(GWEN_XMLNode_GetProperty(node, "rightfill","0"))) {
        if ((maxsize+1)>=GWEN_Buffer_RoomLeft(gbuf)) {
          DBG_ERROR(0, "Buffer too small");
          return -1;
        }

        /* write value */
	for (lj=0; lj<len; lj++)
          GWEN_Buffer_AppendByte(gbuf, GWEN_Buffer_ReadByte(data));

	/* fill right */
	for (lj=0; lj<(maxsize-len); lj++)
          GWEN_Buffer_AppendByte(gbuf, '0');
      }
      else {
        if ((maxsize+1)>=GWEN_Buffer_RoomLeft(gbuf)) {
          DBG_ERROR(0, "Maxsize in XML file is higher than the buffer size");
          return -1;
        }
        for (lj=0; lj<len; lj++)
          GWEN_Buffer_AppendByte(gbuf, GWEN_Buffer_ReadByte(data));
      }
    } /* if type is num */
    else {
      /* TODO: Check for valids */
      const char *p;
      int lastWasEscape;
      int pcount;

      p=GWEN_Buffer_GetPosPointer(data);
      pcount=0;
      lastWasEscape=0;
      while(*p && pcount<GWEN_Buffer_GetUsedBytes(data)) {
	int c;

	c=(unsigned char)*p;
	if (lastWasEscape) {
	  lastWasEscape=0;
	  switch(c) {
	  case 'r': c='\r'; break;
	  case 'n': c='\n'; break;
	  case 'f': c='\f'; break;
	  case 't': c='\t'; break;
	  default: c=(unsigned char)*p;
	  } /* switch */
	}
	else {
	  if (*p=='\\') {
	    lastWasEscape=1;
	    c=-1;
	  }
	  else
	    c=(unsigned char)*p;
	}
	if (c!=-1) {
	  int needsEscape;

	  needsEscape=0;
	  if (c==e->escapeChar)
	    needsEscape=1;
	  else {
	    if (e->charsToEscape)
	      if (strchr(e->charsToEscape, c))
		needsEscape=1;
	  }
	  if (needsEscape) {
            /* write escape char */
            if (GWEN_Buffer_AppendByte(gbuf,
                                       e->escapeChar)) {
              return -1;
            }
          }
          if (GWEN_Buffer_AppendByte(gbuf, c)) {
            return -1;
          }
	}
        p++;
        pcount++;
      } /* while */
      if (pcount<GWEN_Buffer_GetUsedBytes(data)) {
        DBG_WARN(0, "Premature end of string (%d<%d)",
                 pcount, GWEN_Buffer_GetUsedBytes(data));
      }
      if (*p) {
        DBG_WARN(0, "String is longer than expected (no #0 at pos=%d)",
                 GWEN_Buffer_GetUsedBytes(data)-1);
      }
    } /* if type is not BIN */
  } /* if type not external */

  return 0;
}



int GWEN_MsgEngine__IsCharTyp(const char *type) {
  return
    (strcasecmp(type, "alpha")==0) ||
    (strcasecmp(type, "ascii")==0) ||
    (strcasecmp(type, "an")==0);
}



int GWEN_MsgEngine__IsIntTyp(const char *type) {
  return
    (strcasecmp(type, "num")==0);
}



int GWEN_MsgEngine__IsBinTyp(const char *type) {
  return
    (strcasecmp(type, "bin")==0);
}



int GWEN_MsgEngine__WriteElement(GWEN_MSGENGINE *e,
                                 GWEN_BUFFER *gbuf,
                                 GWEN_XMLNODE *node,
                                 GWEN_XMLNODE *rnode,
                                 GWEN_DB_NODE *gr,
                                 int loopNr,
                                 int isOptional) {
  const char *name;
  const char *type;
  unsigned int minsize;
  unsigned int maxsize;
  char numbuffer[256];

  const char *pdata;
  unsigned int datasize;
  GWEN_BUFFER *data;

  pdata=0;

  /* get type */
  type=GWEN_XMLNode_GetProperty(node, "type","ASCII");

  /* get some sizes */
  minsize=atoi(GWEN_XMLNode_GetProperty(node, "minsize","0"));
  maxsize=atoi(GWEN_XMLNode_GetProperty(node, "maxsize","0"));

  /* get name */
  name=GWEN_XMLNode_GetProperty(node, "name", 0);
  if (!name) {
    /* get data from within the XML node */
    GWEN_XMLNODE *n;

    n=GWEN_XMLNode_GetChild(node);
    DBG_DEBUG(0, "Current node is %8x (new node is %8x)",
	     (unsigned int)node,
	     (unsigned int)n);
    if (!n) {
      DBG_DEBUG(0, "No child");
    }
    while(n) {
      if (GWEN_XMLNode_GetType(n)==GWEN_XMLNodeTypeData)
	break;
      n=GWEN_XMLNode_Next(n);
    } /* while */
    if (n) {
      pdata=GWEN_XMLNode_GetData(n);
      datasize=strlen(pdata);
    }
    else {
      pdata="";
      datasize=strlen(pdata);
    }
  } /* if (!name) */
  else {
    char nbuffer[256];
    const char *nptr;

    if (loopNr==0) {
      nptr=name;
    }
    else {
      /* create new element name including the loop number (e.g. var1) */
      if (strlen(name)+10>=sizeof(nbuffer)) {
	DBG_ERROR(0, "Buffer too small");
	return -1;
      }

      sprintf(nbuffer, "%s%d", name, loopNr);
      nptr=nbuffer;
    }

    if (gr) {
      /* get the value of the given var from the db */
      if (GWEN_MsgEngine__IsCharTyp(type)) {
        pdata=GWEN_DB_GetCharValue(gr, nptr, 0, 0);
        datasize=strlen(pdata);
      }
      else if (GWEN_MsgEngine__IsIntTyp(type)) {
        int idata;

        idata=GWEN_DB_GetIntValue(gr, nptr, 0, 0);
        if (-1==GWEN_Text_NumToString(idata, numbuffer,
                                      sizeof(numbuffer),0)) {
          DBG_ERROR(0, "Buffer too small");
          return -1;
        }
        pdata=numbuffer;
        datasize=strlen(numbuffer);
      }
      else if (GWEN_MsgEngine__IsBinTyp(type)) {
        pdata=GWEN_DB_GetBinValue(gr, nptr, 0, 0, 0, &datasize);
      }
      else {
        DBG_ERROR(0, "Bad parameter type");
        return -1;
      }
    }
    if (!pdata)
      /* still no data, try to get it from the XML file */
      pdata=GWEN_MsgEngine__SearchForValue(e, node, rnode, nptr,
                                           &datasize);

    if (pdata==0) {
      if (isOptional) {
        DBG_INFO(0, "Value not found, omitting element \"%s[%d]\"",
                 name, loopNr);
        return 1;
      }
      else {
	DBG_ERROR(0, "Value for element \"%s[%d]\" not found",
		  name, loopNr);
	return -1;
      }
    }
  }

  data=GWEN_Buffer_new((char*)pdata,
                       datasize,
                       datasize,
                       0 /* dont take ownership*/ );

  /* write value */
  if (GWEN_MsgEngine__WriteValue(e,
                                 gbuf,
                                 data,
                                 node)!=0) {
    DBG_INFO(0, "Could not write value");
    GWEN_Buffer_free(data);
    return -1;
  }
  GWEN_Buffer_free(data);

  return 0;
}



GWEN_XMLNODE *GWEN_MsgEngine_FindGroupByProperty(GWEN_MSGENGINE *e,
                                                 const char *pname,
                                                 int version,
                                                 const char *pvalue) {
  return GWEN_MsgEngine_FindNodeByProperty(e, "GROUP", pname, version, pvalue);
}



GWEN_XMLNODE *GWEN_MsgEngine_FindNodeByProperty(GWEN_MSGENGINE *e,
                                                const char *t,
                                                const char *pname,
                                                int version,
                                                const char *pvalue) {
  GWEN_XMLNODE *n;
  const char *p;
  int i;
  char *mode;
  char buffer[256];

  if ((strlen(t)+4)>sizeof(buffer)) {
    DBG_ERROR(0, "Type name too long.");
    return 0;
  }

  mode=e->secMode;
  if (!e->defs) {
    DBG_ERROR(0, "No definitions available");
    return 0;
  }
  n=e->defs;
  n=GWEN_XMLNode_GetChild(n);

  /* find type+"S" */
  strcpy(buffer, t);
  strcat(buffer,"S");
  while(n) {
    if (GWEN_XMLNode_GetType(n)==GWEN_XMLNodeTypeTag) {
      p=GWEN_XMLNode_GetData(n);
      assert(p);
      if (strcasecmp(p, buffer)==0)
	break;
    }
    n=GWEN_XMLNode_Next(n);
  } /* while */

  if (!n) {
    DBG_ERROR(0, "No definitions available for type \"%s\"", t);
    return 0;
  }

  /* find approppriate group definition */
  if (!mode)
    mode="";
  n=GWEN_XMLNode_GetChild(n);
  if (!n) {
    DBG_ERROR(0, "No definitions inside \"%s\"", buffer);
    return 0;
  }

  /* find type+"def" */
  strcpy(buffer, t);
  strcat(buffer,"def");
  while(n) {
    if (GWEN_XMLNode_GetType(n)==GWEN_XMLNodeTypeTag) {
      p=GWEN_XMLNode_GetData(n);
      assert(p);
      if (strcasecmp(p, buffer)==0) {
	/*DBG_INFO(0, "Candidate found (1)"); */
	p=GWEN_XMLNode_GetProperty(n, pname,"");
	if (strcasecmp(p, pvalue)==0) {
	  /*DBG_INFO(0, "Candidate found (2)"); */
	  i=atoi(GWEN_XMLNode_GetProperty(n, "version" ,"0"));
	  if (version==0 || version==i) {
	    /* DBG_INFO(0, "Candidate found (3)"); */
	    p=GWEN_XMLNode_GetProperty(n, "mode","");
	    if (strcasecmp(p, mode)==0 || !*p) {
	      DBG_DEBUG(0, "Group definition for \"%s=%s\" found",
			pname, pvalue);
	      return n;
	    }
	  }
	}
      }
    }
    n=GWEN_XMLNode_Next(n);
  } /* while */

  DBG_ERROR(0, "Group definition for \"%s=%s\" not found", pname, pvalue);
  return 0;
}



const char *GWEN_MsgEngine__TransformValue(GWEN_MSGENGINE *e,
                                           const char *pvalue,
                                           GWEN_XMLNODE *node) {
  const char *p;
  static char pbuffer[256];

  if (pvalue) {
    /* check whether the value is a property */
    p=pvalue;
    while (*p && isspace(*p))
      p++;
    if (*p=='$' || *p=='+') {
      /* global property */
      int incr;

      incr=(*p=='+');
      p++;

      DBG_INFO(0, "Getting global property \"%s\"", p);
      if (incr) {
        int z;

        z=GWEN_DB_GetIntValue(e->globalValues, p, 0, 0);
        DBG_INFO(0, "Incrementing global property \"%s\" (%d)",
                 p, z);
        if (GWEN_Text_NumToString(z, pbuffer, sizeof(pbuffer),0)<1) {
          DBG_ERROR(0, "Error converting num to string");
          return 0;
        }

	z++;
        DBG_DEBUG(0, "Setting global property \"%s\"=%d", p, z);
        GWEN_DB_SetIntValue(e->globalValues,
                            GWEN_DB_FLAGS_DEFAULT |
                            GWEN_DB_FLAGS_OVERWRITE_VARS,
                            p, z);
        pvalue=pbuffer;
      }
      else {
        pvalue=GWEN_DB_GetCharValue(e->globalValues, p, 0, "");

      }
      DBG_DEBUG(0, "Transformed value \"%s\"", pvalue);
    }
    else if (*p=='%') {
      /* local property */
      p++;

      DBG_INFO(0, "Getting property \"%s\"", p);
      pvalue=GWEN_XMLNode_GetProperty(node, p, 0);
      DBG_DEBUG(0, "Transformed value \"%s\"", pvalue);
    }
  }
  return pvalue;
}



const char *GWEN_MsgEngine__SearchForValue(GWEN_MSGENGINE *e,
                                           GWEN_XMLNODE *node,
                                           GWEN_XMLNODE *refnode,
                                           const char *name,
                                           unsigned int *datasize) {
  const char *pvalue;
  GWEN_XMLNODE *pn;
  char *bufferPtr;
  int topDown;
  const char *lastValue;

  DBG_INFO(0, "Searching for value of \"%s\" in <VALUES>", name);
  topDown=atoi(GWEN_XMLNode_GetProperty(node, "topdown","0"));
  lastValue=0;

  bufferPtr=0;
  pn=GWEN_XMLNode_GetParent(node);
  pvalue=GWEN_MsgEngine__findInValues(e, pn, name);
  if (pvalue) {
    if (!topDown)
      return pvalue;
    DBG_INFO(0, "Found a value (%s), but will look further", pvalue);
    lastValue=pvalue;
  }

  pn=refnode;
  while(pn) {
    const char *ppath;

    ppath=GWEN_XMLNode_GetProperty(pn, "name", "");

    if (*ppath) {
      int i;
      char *tmpptr;

      if (bufferPtr) {
	i=strlen(bufferPtr)+strlen(ppath)+2;
	tmpptr=(char*)malloc(i);
	assert(tmpptr);
	sprintf(tmpptr, "%s/%s", ppath, bufferPtr);
	free(bufferPtr);
	bufferPtr=tmpptr;
      }
      else {
	i=strlen(ppath)+strlen(name)+2;
	tmpptr=(char*)malloc(i);
	assert(tmpptr);
	sprintf(tmpptr, "%s/%s", ppath, name);
	bufferPtr=tmpptr;
      }
      name=bufferPtr;
    }
    pvalue=GWEN_MsgEngine__findInValues(e, pn, name);

    if (pvalue) {
      if (!topDown) {
	free(bufferPtr);
	return pvalue;
      }
      DBG_INFO(0, "Found a value (%s), but will look further", pvalue);
      lastValue=pvalue;
    }
    pn=GWEN_XMLNode_GetParent(pn);
  } /* while */
  free(bufferPtr);
  *datasize=strlen(lastValue);
  return lastValue;
}



const char *GWEN_MsgEngine__findInValues(GWEN_MSGENGINE *e,
                                         GWEN_XMLNODE *node,
                                         const char *name) {
  GWEN_XMLNODE *pn;

  DBG_DEBUG(0, "Looking for value of \"%s\" in <VALUES>", name);
  pn=GWEN_XMLNode_GetChild(node);

  while(pn) {
    if (GWEN_XMLNode_GetType(pn)==GWEN_XMLNodeTypeTag) {
      GWEN_XMLNODE *n;
      const char *p;

      p=GWEN_XMLNode_GetData(pn);
      assert(p);
      DBG_DEBUG(0, "Checking %s",p);
      if (strcasecmp(p, "VALUES")==0) {
	DBG_DEBUG(0, "<values> found");
	/* <preset> found, check all values */
	n=GWEN_XMLNode_GetChild(pn);
	while(n) {
	  if (GWEN_XMLNode_GetType(n)==GWEN_XMLNodeTypeTag) {
	    const char *p;

	    p=GWEN_XMLNode_GetData(n);
	    assert(p);
	    if (strcasecmp(p, "VALUE")==0) {
	      const char *pname;
	      const char *pvalue;

	      pname=GWEN_XMLNode_GetProperty(n, "path", 0);
	      if (pname) {
                DBG_DEBUG(0, "Comparing against \"%s\"", pname);
		if (strcasecmp(name, pname)==0) {
		  GWEN_XMLNODE *dn;

		  dn=GWEN_XMLNode_GetChild(n);
		  while (dn) {
                    if (GWEN_XMLNode_GetType(dn)==GWEN_XMLNodeTypeData) {
		      pvalue=GWEN_XMLNode_GetData(dn);
		      pvalue=GWEN_MsgEngine__TransformValue(e, pvalue, node);
		      if (pvalue)
			return pvalue;
		    }
		    dn=GWEN_XMLNode_Next(dn);
		  } /* while dn */
		} /* if path matches name */
	      } /* if path given */
	    } /* if VALUE tag */
	  } /* if TAG */
	  n=GWEN_XMLNode_Next(n);
	} /* while */
        break;           /*  REMOVE this to check multiple groups */
      } /* if <preset> found */
    } /* if tag */
    pn=GWEN_XMLNode_Next(pn);
  } /* while node */

  DBG_DEBUG(0, "No value found for \"%s\" in <VALUES>", name);
  return 0;
}



int GWEN_MsgEngine__WriteGroup(GWEN_MSGENGINE *e,
                               GWEN_BUFFER *gbuf,
                               GWEN_XMLNODE *node,
                               GWEN_XMLNODE *rnode,
                               GWEN_DB_NODE *gr,
                               int groupIsOptional) {
  GWEN_XMLNODE *n;
  const char *p;
  char delimiter;
  char terminator;
  int isFirstElement;
  int omittedElements;
  int hasEntries;

  /* get some settings */
  if (rnode) {
    /* get delimiter */
    p=GWEN_XMLNode_GetProperty(rnode,
                               "delimiter",
                               GWEN_XMLNode_GetProperty(node,
                                                        "delimiter",
                                                        ""));
    delimiter=*p;

    /* get terminating char, if any */
    p=GWEN_XMLNode_GetProperty(rnode,
                               "terminator",
                               GWEN_XMLNode_GetProperty(node,
                                                        "terminator",
                                                        ""));
    terminator=*p;
  }
  else {
    /* get delimiter */
    p=GWEN_XMLNode_GetProperty(node,
                               "delimiter",
                               "");
    delimiter=*p;

    /* get terminating char, if any */
    p=GWEN_XMLNode_GetProperty(node, "terminator","");
    terminator=*p;
  }

  /* handle all child entries */
  n=GWEN_XMLNode_GetChild(node);
  isFirstElement=1;
  omittedElements=0;
  hasEntries=0;

  while(n) {
    int t;
    unsigned int minnum;
    unsigned int maxnum;
    int gversion;
    const char *addEmptyMode;
    int loopNr;

    minnum=atoi(GWEN_XMLNode_GetProperty(n, "minnum","1"));
    maxnum=atoi(GWEN_XMLNode_GetProperty(n, "maxnum","1"));
    gversion=atoi(GWEN_XMLNode_GetProperty(n, "version","0"));
    addEmptyMode=GWEN_XMLNode_GetProperty(n, "addemptymode","one");

    DBG_DEBUG(0, "Omitted elements: %d", omittedElements);
    t=GWEN_XMLNode_GetType(n);
    if (t==GWEN_XMLNodeTypeTag) {
      const char *typ;

      typ=GWEN_XMLNode_GetData(n);
      if (typ==0) {
	DBG_ERROR(0, "Unnamed tag found (internal error?)");
	return -1;
      }
      if (strcasecmp(typ, "ELEM")==0) {
	/* element tag found */
	int j;
        int rv;

	/* write element as often as needed */
	for (loopNr=0; loopNr<maxnum; loopNr++) {
          unsigned int posBeforeElement;

          posBeforeElement=GWEN_Buffer_GetPos(gbuf);

	  /* write delimiter, if needed */
	  if (!isFirstElement && delimiter) {
            for (j=0; j<omittedElements+1; j++) {
              if (GWEN_Buffer_AppendByte(gbuf, delimiter)) {
		return -1;
              }
            }
          }

          rv=GWEN_MsgEngine__WriteElement(e,
                                          gbuf,
                                          n,
                                          rnode,
                                          gr,
                                          loopNr,
                                          loopNr>=minnum ||
                                          (groupIsOptional && !hasEntries));
          if (rv==-1) {
            DBG_INFO(0, "Error writing element");
	    return -1;
	  }
	  else if (rv==0) {
	    isFirstElement=0;
	    omittedElements=0;
	    hasEntries=1;
            DBG_DEBUG(0, "Element written");
	  }
	  else {
	    /* element is optional, not found */
            /* restore position */
            GWEN_Buffer_SetPos(gbuf, posBeforeElement);
            GWEN_Buffer_SetUsedBytes(gbuf, posBeforeElement);

	    if (strcasecmp(addEmptyMode, "max")==0) {
	      DBG_DEBUG(0, "Adding max empty");
	      omittedElements+=(maxnum-loopNr);
	    }
	    else if (strcasecmp(addEmptyMode, "min")==0) {
	      DBG_DEBUG(0, "Adding min empty");
	      if (loopNr<minnum)
		omittedElements+=(minnum-loopNr);
	    }
	    else if (strcasecmp(addEmptyMode, "one")==0) {
	      if (loopNr==0)
		omittedElements++;
	    }
	    else if (strcasecmp(addEmptyMode, "none")==0) {
	    }
	    else {
	      DBG_ERROR(0, "Unknown addemptymode \"%s\"",
			addEmptyMode);
	      return -1;
	    }
	    break;
	  }
	} /* for */
      }
      else if (strcasecmp(typ, "VALUES")==0) {
      }
      else {
	/* group tag found */
	GWEN_XMLNODE *gn;
	GWEN_DB_NODE *gcfg;
	const char *gname;
	const char *gtype;
        unsigned int posBeforeGroup;

        gcfg=0;
	gtype=GWEN_XMLNode_GetProperty(n, "type",0);
	if (!gtype) {
	  /* no "type" property, so use this group directly */
	  DBG_INFO(0, "<%s> tag has no \"type\" property", typ);
	  gtype="";
	  gn=n;
	}
	else {
	  gn=GWEN_MsgEngine_FindNodeByProperty(e, typ, "id", gversion, gtype);
          if (!gn) {
	    DBG_INFO(0, "Definition for type \"%s\" not found", typ);
	    return -1;
	  }
	}

        gname=0;
        gcfg=0;
        if (gr) {
          gname=GWEN_XMLNode_GetProperty(n, "name",0);
          if (gname)
            gcfg=GWEN_DB_GetFirstGroup(gr);
          else
            gcfg=gr;
        }

	/* write group as often as needed */
	for (loopNr=0; loopNr<maxnum; loopNr++) {
	  int rv;

          posBeforeGroup=GWEN_Buffer_GetPos(gbuf);

          /* find next matching group */
          if (gname) {
            while(gcfg) {
              if (strcasecmp(GWEN_DB_GroupName(gcfg), gname)==0)
                break;
              gcfg=GWEN_DB_GetNextGroup(gcfg);
            } /* while */
          }

	  /* write delimiter, if needed */
	  if (!isFirstElement && delimiter) {
	    int j;

            for (j=0; j<omittedElements+1; j++) {
              if (GWEN_Buffer_AppendByte(gbuf, delimiter)) {
                return -1;
              }
            }
            omittedElements=0;
          }
          else
	    isFirstElement=0;

	  /* write group */
          rv=GWEN_MsgEngine__WriteGroup(e,
                                        gbuf,
                                        gn,
                                        n,
                                        gcfg,
                                        loopNr>=minnum || groupIsOptional);
          if (rv==-1){
	    DBG_INFO(0, "Could not write group \"%s\"", gtype);
	    return -1;
	  }
	  else if (rv==0) {
            hasEntries=1;
	  }
	  else {
            DBG_INFO(0, "Empty Group");
            GWEN_Buffer_SetPos(gbuf, posBeforeGroup);
            GWEN_Buffer_SetUsedBytes(gbuf, posBeforeGroup);

	    if (loopNr>=minnum) {
	      DBG_INFO(0, "No data for group \"%s[%d]\", omitting",
		       gname, loopNr);
	      if (strcasecmp(addEmptyMode, "max")==0) {
		DBG_DEBUG(0, "Adding max empty");
		omittedElements+=(maxnum-loopNr);
	      }
	      else if (strcasecmp(addEmptyMode, "min")==0) {
		DBG_DEBUG(0, "Adding min empty");
		if (loopNr<minnum)
		  omittedElements+=(minnum-loopNr);
	      }
	      else if (strcasecmp(addEmptyMode, "one")==0) {
		if (loopNr==0)
		  omittedElements++;
	      }
	      else if (strcasecmp(addEmptyMode, "none")==0) {
	      }
	      else {
		DBG_ERROR(0, "Unknown addemptymode \"%s\"",
			  addEmptyMode);
		return -1;
	      }
	      break;
	    }
	    else {
	      DBG_ERROR(0, "No data for group \"%s[%d]\"",
			gname, loopNr);
	      return -1;
	    }
	  } /* if empty group */
	} /* for */
      }
    }
    else if (t==GWEN_XMLNodeTypeData) {
    }
    else {
      DBG_DEBUG(0, "Unhandled node type %d", t);
    }
    n=GWEN_XMLNode_Next(n);
  } /* while */

  /* write terminating character, if any */
  if (terminator) {
    if (GWEN_Buffer_AppendByte(gbuf, terminator)) {
      return -1;
    }
  }

  return hasEntries?0:1;
}



int GWEN_MsgEngine_CreateMessageFromNode(GWEN_MSGENGINE *e,
                                         GWEN_XMLNODE *node,
                                         GWEN_BUFFER *gbuf,
                                         GWEN_DB_NODE *msgData){
  assert(e);
  assert(node);
  assert(msgData);

  if (GWEN_MsgEngine__WriteGroup(e,
                                 gbuf,
                                 node,
                                 0,
                                 msgData,
                                 0)) {
    const char *p;

    p=GWEN_XMLNode_GetData(node);
    if (p) {
      DBG_INFO(0, "Error writing group \"%s\"", p);
    }
    else {
      DBG_INFO(0, "Error writing group");
    }
    return -1;
  }

  return 0;
}



int GWEN_MsgEngine_CreateMessage(GWEN_MSGENGINE *e,
                                 const char *msgName,
                                 int msgVersion,
                                 GWEN_BUFFER *gbuf,
                                 GWEN_DB_NODE *msgData) {
  GWEN_XMLNODE *group;

  group=GWEN_MsgEngine_FindGroupByProperty(e, "id", msgVersion, msgName);
  if (!group) {
    DBG_ERROR(0, "Group \"%s\" not found\n", msgName);
    return -1;
  }
  return GWEN_MsgEngine_CreateMessageFromNode(e,
                                              group,
                                              gbuf,
                                              msgData);
}



int GWEN_MsgEngine_AddDefinitions(GWEN_MSGENGINE *e,
                                  GWEN_XMLNODE *node) {
  GWEN_XMLNODE *nsrc, *ndst;

  assert(e);
  assert(node);

  if (!e->defs) {
    e->defs=GWEN_XMLNode_dup(node);
    return 0;
  }

  nsrc=GWEN_XMLNode_GetChild(node);
  while(nsrc) {
    if (GWEN_XMLNode_GetType(nsrc)==GWEN_XMLNodeTypeTag) {
      ndst=GWEN_XMLNode_FindNode(e->defs, GWEN_XMLNodeTypeTag,
                                 GWEN_XMLNode_GetData(nsrc));
      if (ndst) {
	GWEN_XMLNODE *n;

        n=GWEN_XMLNode_GetChild(nsrc);
	while (n) {
	  GWEN_XMLNODE *newNode;

          DBG_DEBUG(0, "Adding node \"%s\"", GWEN_XMLNode_GetData(n));
          newNode=GWEN_XMLNode_dup(n);
          GWEN_XMLNode_AddChild(ndst, newNode);
	  n=GWEN_XMLNode_Next(n);
	} /* while n */
      }
      else {
	GWEN_XMLNODE *newNode;

        DBG_DEBUG(0, "Adding branch \"%s\"", GWEN_XMLNode_GetData(nsrc));
	newNode=GWEN_XMLNode_dup(nsrc);
        GWEN_XMLNode_AddChild(e->defs, newNode);
      }
    } /* if TAG */
    nsrc=GWEN_XMLNode_Next(nsrc);
  } /* while */

  return 0;
}



int GWEN_MsgEngine__ShowElement(GWEN_MSGENGINE *e,
                                const char *path,
                                GWEN_XMLNODE *node,
                                GWEN_STRINGLIST *sl,
                                unsigned int flags) {
  const char *name;
  const char *type;
  const char *npath;
  unsigned int minsize;
  unsigned int maxsize;
  unsigned int minnum;
  unsigned int maxnum;
  int j;
  int isSet;
  char nbuffer[256];
  GWEN_STRINGLISTENTRY *en;

  /* get type */
  type=GWEN_XMLNode_GetProperty(node, "type","ASCII");

  /* get some sizes */
  minsize=atoi(GWEN_XMLNode_GetProperty(node, "minsize","0"));
  maxsize=atoi(GWEN_XMLNode_GetProperty(node, "maxsize","0"));
  minnum=atoi(GWEN_XMLNode_GetProperty(node, "minnum","1"));
  maxnum=atoi(GWEN_XMLNode_GetProperty(node, "maxnum","1"));

  npath="";
  isSet=0;

  /* get name */
  name=GWEN_XMLNode_GetProperty(node, "name", 0);
  if (path==0)
    path="";

  if (name) {
    /* get value of a config variable */
    if (strlen(path)+strlen(name)+10>=sizeof(nbuffer)) {
      DBG_ERROR(0, "Buffer too small");
      return -1;
    }
    if (*path)
      sprintf(nbuffer, "%s/%s", path, name);
    else
      sprintf(nbuffer, "%s", name);
    npath=nbuffer;
  }

  en=GWEN_StringList_FirstEntry(sl);
  while(en) {
    if (GWEN_StringListEntry_Data(en))
      if (strcasecmp(GWEN_StringListEntry_Data(en), npath)==0) {
        isSet=1;
	break;
      }
    en=GWEN_StringListEntry_Next(en);
  } /* while */

  if (isSet && (flags & GWEN_MSGENGINE_SHOW_FLAGS_NOSET))
    return 0;

  fprintf(stdout, "  %s",
	  npath);
  j=GWEN_MSGENGINE_VARNAME_WIDTH-strlen(npath);
  if (j>0) {
    int i;

    for (i=0; i<j; i++)
      fprintf(stdout, " ");
  }
  fprintf(stdout, "| %s", type);
  j=GWEN_MSGENGINE_TYPENAME_WIDTH-strlen(type);
  if (j>0) {
    int i;

    for (i=0; i<j; i++)
      fprintf(stdout, " ");
  }
  fprintf(stdout, "| %4d-%4d", minsize, maxsize);
  fprintf(stdout," | %3d ", maxnum);
  fprintf(stdout," |");
  if (minnum==0)
    fprintf(stdout," optvar");
  if (flags & GWEN_MSGENGINE_SHOW_FLAGS_OPTIONAL)
    fprintf(stdout," optgrp");

  if (isSet) {
    fprintf(stdout," set");
  }

  fprintf(stdout,"\n");

  return 0;
}



int GWEN_MsgEngine__ShowGroup(GWEN_MSGENGINE *e,
                              const char *path,
                              GWEN_XMLNODE *node,
                              GWEN_XMLNODE *rnode,
                              GWEN_STRINGLIST *sl,
                              unsigned int flags) {
  GWEN_XMLNODE *n;
  int isFirstElement;
  int omittedElements;
  int rv;

  /* setup data */
  n=GWEN_XMLNode_GetChild(node);

  if (path==0)
    path="";
  if (*path=='/')
    path++;

  while(n) {
    if (GWEN_XMLNode_GetType(n)==GWEN_XMLNodeTypeTag) {
      const char *p;

      p=GWEN_XMLNode_GetData(n);
      assert(p);
      DBG_DEBUG(0, "Checking %s",p);
      if (strcasecmp(p, "VALUES")==0)
	break;
    } /* if tag */
    n=GWEN_XMLNode_Next(n);
  } /* while */

  if (n) {
    DBG_DEBUG(0, "<preset> found");
    /* <preset> found, handle all values */
    n=GWEN_XMLNode_GetChild(n);
    while(n) {
      if (GWEN_XMLNode_GetType(n)==GWEN_XMLNodeTypeTag) {
	const char *p;

	p=GWEN_XMLNode_GetData(n);
        assert(p);
	if (strcasecmp(p, "VALUE")==0) {
	  const char *pname;
	  const char *pvalue;

	  pname=GWEN_XMLNode_GetProperty(n, "path", 0);
	  if (pname) {
	    GWEN_XMLNODE *dn;

	    /* path found, find data */
	    dn=GWEN_XMLNode_GetChild(n);
	    while (dn) {
              if (GWEN_XMLNode_GetType(dn)==GWEN_XMLNodeTypeData) {
		pvalue=GWEN_XMLNode_GetData(dn);
		if (pvalue) {
		  char pbuffer[256];

		  /* check whether the value is a property */
		  p=pvalue;
		  while (*p && isspace(*p))
		    p++;
		  if (strlen(path)+strlen(pname)+2>sizeof(pbuffer)) {
		    DBG_ERROR(0, "Buffer too small");
		    return -1;
		  }
		  if (*path)
		    sprintf(pbuffer, "%s/%s", path, pname);
		  else
		    sprintf(pbuffer, "%s", pname);
                  GWEN_StringList_AppendString(sl,
                                               pbuffer,
                                               0,
                                               1);
                }
		break;
	      }
	      dn=GWEN_XMLNode_Next(dn);
	    } /* while dn */
	  } /* if path given */
	} /* if VALUE tag */
      } /* if TAG */
      n=GWEN_XMLNode_Next(n);
    } /* while */
  } /* if <preset> found */

  /* now handle all child entries */
  n=GWEN_XMLNode_GetChild(node);
  isFirstElement=1;
  omittedElements=0;
  while(n) {
    int t;
    unsigned int minnum;
    unsigned int maxnum;
    int gversion;
    const char *addEmptyMode;
    int loopNr;
    unsigned int lflags;

    minnum=atoi(GWEN_XMLNode_GetProperty(n, "minnum","1"));
    maxnum=atoi(GWEN_XMLNode_GetProperty(n, "maxnum","1"));
    gversion=atoi(GWEN_XMLNode_GetProperty(n, "version","0"));
    addEmptyMode=GWEN_XMLNode_GetProperty(n, "addemptymode","one");

    lflags=flags;

    DBG_DEBUG(0, "Omitted elements: %d", omittedElements);
    t=GWEN_XMLNode_GetType(n);
    if (t==GWEN_XMLNodeTypeTag) {
      const char *typ;

      typ=GWEN_XMLNode_GetData(n);
      if (typ==0) {
	DBG_ERROR(0, "Unnamed tag found (internal error?)");
	return -1;
      }
      if (strcasecmp(typ, "ELEM")==0) {
	/* element tag found */

	/* write element as often as needed */
	rv=GWEN_MsgEngine__ShowElement(e,
                                       path,
                                       n,
                                       sl,
                                       lflags);
        if (rv==-1)
	  return -1;
	else {
	  isFirstElement=0;
	  omittedElements=0;
	}
      }
      else if (strcasecmp(typ, "VALUES")==0) {
      }
      else {
	/* group tag found */
	GWEN_XMLNODE *gn;
        const char *gname;
        const char *gtype;

	if (minnum==0)
          lflags|=GWEN_MSGENGINE_SHOW_FLAGS_OPTIONAL;

	gtype=GWEN_XMLNode_GetProperty(n, "type",0);
	if (!gtype) {
          /* no "type" property, so use this group directly */
	  DBG_INFO(0, "<%s> tag has no \"type\" property", typ);
	  gtype="";
	  gn=n;
	}
	else {
          gn=GWEN_MsgEngine_FindNodeByProperty(e, typ, "id", gversion, gtype);
          if (!gn) {
	    DBG_DEBUG(0, "Definition for type \"%s\" not found", typ);
	    return -1;
	  }
	}

	/* write group as often as needed */
	for (loopNr=0; loopNr<maxnum; loopNr++) {
	  /* find group */
	  char pbuffer[256];
	  const char *npath;

	  /* get configuration */
	  gname=GWEN_XMLNode_GetProperty(n, "name",0);
	  if (gname) {
	    if (loopNr==0) {
	      if (strlen(path)+strlen(gname)+1>sizeof(pbuffer)) {
		DBG_ERROR(0, "Buffer too small");
		return -1;
	      }
	      sprintf(pbuffer, "%s/%s", path, gname);
              npath=pbuffer;
	    }
	    else {
	      /* this is not the first one, so create new name */
	      if (strlen(path)+strlen(gname)+10>sizeof(pbuffer)) {
		DBG_ERROR(0, "Buffer too small");
		return -1;
	      }
	      if (*path)
		sprintf(pbuffer, "%s/%s%d", path, gname, loopNr);
              else
		sprintf(pbuffer, "%s%d", gname, loopNr);
	      /* get the value of the given var */
	      npath=pbuffer;
	    }
	  } /* if name given */
	  else
	    npath=path;

	  /* write group */
	  if (GWEN_MsgEngine__ShowGroup(e,
                                        npath,
                                        gn,
                                        n,
                                        sl,
                                        lflags)) {
            DBG_INFO(0, "Could not show group \"%s\"", gtype);
	    return -1;
	  }
	} /* for */
      }
    }
    n=GWEN_XMLNode_Next(n);
  } /* while */

  return 0;
}



int GWEN_MsgEngine_ShowMessage(GWEN_MSGENGINE *e,
                               const char *typ,
                               const char *msgName,
                               int msgVersion,
                               unsigned int flags) {
  GWEN_XMLNODE *group;
  GWEN_STRINGLIST *sl;
  int i, j;
  const char *p;

  sl=GWEN_StringList_new();

  fprintf(stdout, "Message \"%s\" version %d\n",
          msgName, msgVersion);
  for (i=0; i<76; i++)
    fprintf(stdout, "=");
  fprintf(stdout, "\n");
  p="        Variable";
  fprintf(stdout, "%s", p);
  i=GWEN_MSGENGINE_VARNAME_WIDTH-strlen(p);
  for (j=0; j<i; j++)
    fprintf(stdout," ");

  fprintf(stdout,"  |");
  p=" Type";
  fprintf(stdout, "%s", p);
  i=GWEN_MSGENGINE_TYPENAME_WIDTH-strlen(p);
  for (j=0; j<i; j++)
    fprintf(stdout," ");

  fprintf(stdout," |   Size    | Num  | Flags\n");
  for (i=0; i<76; i++)
    fprintf(stdout, "-");
  fprintf(stdout, "\n");

  group=GWEN_MsgEngine_FindNodeByProperty(e, typ, "id", msgVersion, msgName);
  if (!group) {
    DBG_ERROR(0, "Group \"%s\" not found\n", msgName);
    GWEN_StringList_free(sl);
    return -1;
  }

  if (GWEN_MsgEngine__ShowGroup(e,
                                "",
                                group,
                                0,
                                sl,
                                flags)) {
    DBG_INFO(0, "Error showing group \"%s\"", msgName);
    GWEN_StringList_free(sl);
    return -1;
  }

  GWEN_StringList_free(sl);

  return 0;
}



int GWEN_MsgEngine__ReadValue(GWEN_MSGENGINE *e,
                              const char *msg,
                              unsigned int msgSize,
                              unsigned int *pos,
                              GWEN_XMLNODE *node,
                              char *buffer,
                              int *bufsize,
                              const char *delimiters) {
  unsigned int minsize;
  unsigned int maxsize;
  unsigned int minnum;
  const char *type;
  const char *origBuffer;
  int rv;
  unsigned int datasize;

  origBuffer=buffer;
  datasize=0;

  /* get some sizes */
  minsize=atoi(GWEN_XMLNode_GetProperty(node, "minsize","0"));
  maxsize=atoi(GWEN_XMLNode_GetProperty(node, "maxsize","0"));
  minnum=atoi(GWEN_XMLNode_GetProperty(node, "minnum","1"));
  type=GWEN_XMLNode_GetProperty(node, "type","ASCII");

  rv=1;
  if (e->typeReadPtr) {
    rv=e->typeReadPtr(e,
                      msg,
		      msgSize,
		      pos,
		      node,
		      buffer,
		      bufsize,
		      '\\',
                      delimiters);
  }
  if (rv==-1) {
    DBG_INFO(0, "External type reading failed on type \"%s\"", type);
    return -1;
  }
  else if (rv==1) {
    if (strcasecmp(type, "bin")==0) {
      if (*pos>=msgSize) {
	DBG_ERROR(0, "Premature end of message (@num@ expected)");
        return -1;
      }
      else {
	char lbuffer[16];
	char *p;
        int l;

	p=lbuffer;
	if (msg[*pos]!='@') {
	  DBG_ERROR(0, "\"@num@\" expected");
	  return -1;
	}
	(*pos)++;
	while(*pos<msgSize) {
	  if (msg[*pos]=='@')
	    break;
	  *p=msg[*pos];
	  p++;
	  (*pos)++;
	} /* while */
        *p=0;
	if (msg[*pos]!='@') {
	  DBG_ERROR(0, "\"@num@\" expected");
	  return -1;
	}
	if (sscanf(lbuffer, "%d", &l)!=1) {
	  DBG_ERROR(0, "Bad number format");
	  return -1;
	}
	(*pos)++;
	DBG_INFO(0, "Reading binary: %d bytes from pos %d (msgsize=%d)",
		 l, *pos, msgSize);
	if (msgSize-*pos+1<l) {
	  DBG_ERROR(0, "Premature end of message (binary beyond end)");
	  return -1;
        }
        memmove(buffer, msg+*pos, l);
        datasize=l;
        (*pos)+=l;
        buffer+=l;
      }
    } /* if bin */
    else {
      /* type is not bin */
      int lastWasEscape;
      int isEscaped;

      isEscaped=0;
      lastWasEscape=0;

      while(*pos<msgSize) {
	int c;

	c=(unsigned char)(msg[*pos]);
	if (lastWasEscape) {
	  lastWasEscape=0;
	  isEscaped=1;
	}
	else {
	  isEscaped=0;
	  if (c==e->escapeChar) {
	    lastWasEscape=1;
	    c=-1;
	  }
	}
	if (c!=-1) {
	  int needsEscape;

	  if (!isEscaped && strchr(delimiters, c)==0) {
	    needsEscape=0;
	    if (c=='\\' || iscntrl(c))
	      needsEscape=1;

	    if (needsEscape) {
	      /* write escape char */
	      if (*bufsize<1) {
		DBG_ERROR(0, "Buffer too small");
		return -1;
	      }
              *(buffer++)='\\';
              datasize++;
            }
	    if (*bufsize<1) {
	      DBG_ERROR(0, "Buffer too small");
	      return -1;
	    }
            *(buffer++)=(unsigned char)c;
            datasize++;
	  }
	  else {
	    /* delimiter found */
	    break;
	  }
	}
	(*pos)++;
      } /* while */
      *buffer=0;
      datasize=strlen(buffer)+1;
    } /* if !bin */
  } /* if type not external */

  /* check the value */
  if (datasize==0) {
    DBG_INFO(0, "Datasize is 0");
    if (minnum==0) {
      DBG_INFO(0, "... but thats ok");
      /* value is empty, and that is allowed */
      *bufsize=datasize;
      return 1;
    }
    else {
      DBG_ERROR(0, "Value missing");
      GWEN_XMLNode_Dump(node, stderr, 1);
      return -1;
    }
  }

  if (minsize!=0 && minsize<datasize) {
    DBG_INFO(0, "Value too short (%d<%d).", minsize, datasize);
    return -1;
  }

  if (maxsize!=0 && datasize>maxsize) {
    DBG_INFO(0, "Value too long (%d>%d).", datasize, maxsize);
    return -1;
  }

  *bufsize=datasize;
  return 0;
}



int GWEN_MsgEngine__ReadGroup(GWEN_MSGENGINE *e,
                              const char *msg,
                              unsigned int msgSize,
                              unsigned int *pos,
                              GWEN_XMLNODE *node,
                              GWEN_XMLNODE *rnode,
                              GWEN_DB_NODE *gr,
                              const char *delimiters) {
  unsigned int minsize;
  unsigned int maxsize;
  unsigned int minnum;
  unsigned int maxnum;
  const char *name;
  const char *p;
  char delimiter;
  char terminator;
  GWEN_XMLNODE *n;
  int abortLoop;

  /* get some settings */
  if (rnode) {
    /* get delimiter */
    p=GWEN_XMLNode_GetProperty(rnode,
                               "delimiter",
                               GWEN_XMLNode_GetProperty(node,
                                                        "delimiter",
                                                        ""));
    delimiter=*p;

    /* get terminating char, if any */
    p=GWEN_XMLNode_GetProperty(rnode,
                               "terminator",
                               GWEN_XMLNode_GetProperty(node,
                                                        "terminator",
                                                        ""));
    terminator=*p;
  }
  else {
    /* get delimiter */
    p=GWEN_XMLNode_GetProperty(node,
                               "delimiter",
                               "");
    delimiter=*p;

    /* get terminating char, if any */
    p=GWEN_XMLNode_GetProperty(node, "terminator","");
    terminator=*p;
  }

  n=GWEN_XMLNode_GetChild(node);
  while (n) {
    if (GWEN_XMLNode_GetType(n)==GWEN_XMLNodeTypeTag) {
      const char *type;

      if (*pos>=msgSize)
	break;
      //if (strchr(delimiters, msg[*pos]))
      //  break;

      type=GWEN_XMLNode_GetData(n);
      if (strcasecmp(type, "ELEM")==0) {
        char buffer[GWEN_MSGENGINE_MAX_VALUE_LEN];
	unsigned int loopNr;

	/* get some sizes */
	minsize=atoi(GWEN_XMLNode_GetProperty(n, "minsize","0"));
	maxsize=atoi(GWEN_XMLNode_GetProperty(n, "maxsize","0"));
	minnum=atoi(GWEN_XMLNode_GetProperty(n, "minnum","1"));
	maxnum=atoi(GWEN_XMLNode_GetProperty(n, "maxnum","1"));
	name=GWEN_XMLNode_GetProperty(n, "name", 0);

	loopNr=0;
	abortLoop=0;
	while(loopNr<maxnum && !abortLoop) {
	  DBG_DEBUG(0, "Reading %s", name);
	  if (*pos>=msgSize)
	    break;
	  if (strchr(delimiters, msg[*pos])) {
	    abortLoop=1;
	  } /* if delimiter found */
          else {
            /* current char is not a delimiter */
	    if (name==0) {
            }
            else {
              /* name is given */
	      int rv;
              const char *dtype;
              unsigned int datasize;

              datasize=sizeof(buffer)-1;
              rv=GWEN_MsgEngine__ReadValue(e,
                                           msg,
                                           msgSize,
                                           pos,
                                           n,
                                           buffer,
                                           &datasize,
                                           ":+'");
              if (rv==1) {
		DBG_INFO(0, "Empty value");
	      }
	      else if (rv==-1) {
		DBG_INFO(0, "Error parsing node \"%s\"", type);
		return -1;
	      }

              /* special handling for binary data */
              dtype=GWEN_XMLNode_GetProperty(n, "type", "");
              if (GWEN_MsgEngine__IsBinTyp(dtype)) {
                if (e->binTypeReadPtr)
                  rv=e->binTypeReadPtr(e, n, gr, buffer, datasize);
                else
                  rv=1;
                if (rv==-1) {
                  DBG_INFO(0, "Called from here");
                  return -1;
                }
                else if (rv==1) {
                  /* bin type not handled, so handle it myself */
                  if (GWEN_DB_SetBinValue(gr,
                                          GWEN_DB_FLAGS_DEFAULT,
                                          name, buffer, datasize)) {
                    DBG_INFO(0, "Could not set value for \"%s\"", name);
                    return -1;
                  }
                }
              } /* if type is bin */
              else if (GWEN_MsgEngine__IsIntTyp(dtype)) {
                int z;

                if (1!=sscanf(buffer, "%d", &z)) {
                  DBG_INFO(0, "Value for \"%s\" is not an integer",
                           name);
                  return -1;
                }
                if (GWEN_DB_SetIntValue(gr,
                                        GWEN_DB_FLAGS_DEFAULT,
                                        name, z)) {
                  DBG_INFO(0, "Could not set int value for \"%s\"", name);
                  return -1;
                }
              } /* if type is int */
              else {
                DBG_INFO(0, "Value is \"%s\"", buffer);
                if (GWEN_DB_SetCharValue(gr,
                                         GWEN_DB_FLAGS_DEFAULT,
                                         name, buffer)) {
                  DBG_INFO(0, "Could not set value for \"%s\"", name);
		  return -1;
		}
	      } /* if !bin */
	    } /* if name is given */
          } /* if current char is not a delimiter */

          if (*pos<msgSize) {
	    if (delimiter) {
	      if (msg[*pos]==delimiter) {
		(*pos)++;
	      }
	    }
	  }
	  loopNr++;
	} /* while */
	if (loopNr<minnum) {
	  DBG_ERROR(0, "Premature end of message (too few ELEM repeats)");
	  return -1;
	}
	n=GWEN_XMLNode_Next(n);
      } /* if ELEM */
      else if (strcasecmp(type, "VALUES")==0) {
	n=GWEN_XMLNode_Next(n);
      }
      else {
	/* group tag found */
	GWEN_XMLNODE *gn;
	GWEN_DB_NODE *gcfg;
	const char *gname;
	const char *gtype;
	unsigned int gversion;
	int loopNr;

	minnum=atoi(GWEN_XMLNode_GetProperty(n, "minnum","1"));
	maxnum=atoi(GWEN_XMLNode_GetProperty(n, "maxnum","1"));
	gversion=atoi(GWEN_XMLNode_GetProperty(n, "version","0"));
	gtype=GWEN_XMLNode_GetProperty(n, "type",0);
	if (!gtype) {
	  /* no "type" property, so use this group directly */
	  DBG_INFO(0, "<%s> tag has no \"type\" property", type);
	  gtype="";
	  gn=n;
	}
	else {
          gn=GWEN_MsgEngine_FindNodeByProperty(e, type, "id",
                                               gversion, gtype);
	  if (!gn) {
	    DBG_INFO(0, "Definition for type \"%s\" not found", type);
	    return -1;
	  }
	}

	/* get configuration */
	loopNr=0;
	abortLoop=0;
	while(loopNr<maxnum && !abortLoop) {
	  DBG_INFO(0, "Reading group type %s", gtype);
	  if (*pos>=msgSize)
	    break;
	  if (strchr(delimiters, msg[*pos])) {
	    abortLoop=1;
	  }
	  else {
            gname=GWEN_XMLNode_GetProperty(n, "name",0);
	    if (gname) {
              gcfg=GWEN_DB_GetGroup(gr,
                                    GWEN_PATH_FLAGS_NAMECREATE,
                                    gname);
	      if (!gcfg) {
		DBG_ERROR(0, "Could not select group \"%s\"",
			  gname);
		return -1;
	      }
	    } /* if name given */
	    else
	      gcfg=gr;

	    /* read group */
	    DBG_INFO(0, "Reading group \"%s\"", gname);
	    if (GWEN_MsgEngine__ReadGroup(e,
                                          msg,
                                          msgSize,
                                          pos,
                                          gn,
                                          n,
                                          gcfg,
                                          delimiters)) {
              DBG_INFO(0, "Could not read group \"%s\"", gtype);
	      return -1;
	    }
	  }
	  if (*pos<msgSize) {
	    if (delimiter) {
	      if (msg[*pos]==delimiter) {
		(*pos)++;
	      }
	    }
	  }
	  loopNr++;
	} /* while */
	if (loopNr<minnum) {
	  DBG_ERROR(0, "Premature end of message (too few group repeats)");
	  return -1;
	}
        n=GWEN_XMLNode_Next(n);
      } /* if GROUP */
    } /* if TAG */
    else {
      n=GWEN_XMLNode_Next(n);
    }
  } /* while */

  /* check whether there still are nodes which have not been read */
  while(n) {
    if (GWEN_XMLNode_GetType(n)==GWEN_XMLNodeTypeTag) {
      if (strcasecmp(GWEN_XMLNode_GetData(n), "ELEM")==0 ||
	  strcasecmp(GWEN_XMLNode_GetData(n), "GROUP")==0) {
	unsigned int i;

	i=atoi(GWEN_XMLNode_GetProperty(n, "minnum", "1"));
	if (i) {
	  DBG_ERROR(0, "Premature end of message (still tags to parse)");
	  return -1;
	}
      }
    }
    n=GWEN_XMLNode_Next(n);
  }


  if (terminator) {
    /* skip terminator */
    if (*pos<msgSize) {
      if (msg[*pos]==terminator) {
	(*pos)++;
      }
      else {
	DBG_ERROR(0, "Terminating character missing (pos=%d)", *pos);
        GWEN_XMLNode_Dump(node, stderr, 1);
	return -1;
      }
    }
    else {
      DBG_ERROR(0, "Terminating character missing");
      return -1;
    }
  }

  return 0;
}



int GWEN_MsgEngine_ParseMessage(GWEN_MSGENGINE *e,
                                GWEN_XMLNODE *group,
                                const char *msg,
                                unsigned int msgSize,
                                unsigned int *pos,
                                GWEN_DB_NODE *msgData){

  if (GWEN_MsgEngine__ReadGroup(e,
                                msg,
                                msgSize,
                                pos,
                                group,
                                0,
                                msgData,
                                e->delimiters)) {
    DBG_INFO(0, "Error reading group");
    return -1;
  }

  return 0;
}



int GWEN_MsgEngine_SetValue(GWEN_MSGENGINE *e,
                            const char *path,
                            const char *value){
  assert(e);
  assert(e->globalValues);
  return GWEN_DB_SetCharValue(e->globalValues,
                              GWEN_DB_FLAGS_DEFAULT |
                              GWEN_DB_FLAGS_OVERWRITE_VARS,
                              path, value);
}



int GWEN_MsgEngine_SetIntValue(GWEN_MSGENGINE *e,
                               const char *path,
                               int value){
  assert(e);
  assert(e->globalValues);
  return GWEN_DB_SetIntValue(e->globalValues,
                             GWEN_DB_FLAGS_DEFAULT |
                             GWEN_DB_FLAGS_OVERWRITE_VARS,
                             path, value);
}



const char *GWEN_MsgEngine_GetValue(GWEN_MSGENGINE *e,
                                    const char *path,
                                    const char *defValue){
  assert(e);
  assert(e->globalValues);
  return GWEN_DB_GetCharValue(e->globalValues,
                              path, 0, defValue);
}



int GWEN_MsgEngine_GetIntValue(GWEN_MSGENGINE *e,
                               const char *path,
                               int defValue){
  assert(e);
  assert(e->globalValues);
  return GWEN_DB_GetIntValue(e->globalValues,
                             path, 0, defValue);
}







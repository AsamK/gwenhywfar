/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id$
    begin       : Sun Nov 23 2003
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


#include <gwenhywfar/directory.h>
#include <gwenhywfar/debug.h>
#include <gwenhywfar/path.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>



void *GWEN_Directory_HandlePathElement(const char *entry,
                                       void *data,
                                       unsigned int flags){
  char *p;
  struct stat st;
  int exists;

  if (strcasecmp(entry, "..")==0) {
    DBG_ERROR(0, "\"..\" detected");
    return 0;
  }

  p=(char*)data;
  if ((strlen(p)+strlen(entry)+2)>=256) {
    DBG_ERROR(0, "Buffer too small");
    return 0;
  }
  if (*p)
    strcat(p, "/");
  strcat(p, entry);

  // check for existence of the file/folder

  DBG_DEBUG(0, "Checking entry \"%s\"", p);
  if (stat(p, &st)) {
    exists=0;
    DBG_DEBUG(0, "stat: %s (%s)", strerror(errno), p);
    if ((flags & GWEN_PATH_FLAGS_PATHMUSTEXIST) ||
        ((flags & GWEN_PATH_FLAGS_LAST) &&
         (flags & GWEN_PATH_FLAGS_NAMEMUSTEXIST))) {
      DBG_INFO(0, "Path \"%s\" does not exist (it should)", p);
      return 0;
    }
  }
  else {
    DBG_DEBUG(0, "Checking for type");
    exists=1;
    if (flags & GWEN_PATH_FLAGS_VARIABLE) {
      if (!S_ISREG(st.st_mode)) {
        DBG_INFO(0, "%s not a regular file", p);
        return 0;
      }
    }
    else {
      if (!S_ISDIR(st.st_mode)) {
        DBG_INFO(0, "%s not a direcory", p);
        return 0;
      }
    }
    if ((flags & GWEN_PATH_FLAGS_PATHMUSTNOTEXIST) ||
        ((flags & GWEN_PATH_FLAGS_LAST) &&
         (flags & GWEN_PATH_FLAGS_NAMEMUSTNOTEXIST))) {
      DBG_INFO(0, "Path \"%s\" does not exist (it should)", p);
      return 0;
    }
  } // if stat is ok

  if (!exists) {
    DBG_DEBUG(0, "Entry \"%s\" does not exist", p);
    if (flags & GWEN_PATH_FLAGS_VARIABLE) {
      // create file
      int fd;

      DBG_DEBUG(0, "Creating file \"%s\"", p);
      fd=open(p, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
      if (fd==-1) {
        DBG_ERROR(0, "open: %s (%s)", strerror(errno), p);
        return 0;
      }
      close(fd);
      DBG_DEBUG(0, "Sucessfully created");
    }
    else {
      // create dir
      DBG_DEBUG(0, "Creating folder \"%s\"", p);

      if (GWEN_Directory_Create(p)) {
        DBG_ERROR(0, "Could not create directory \"%s\"", p);
        return 0;
      }
    }
  } // if exists
  else {
    DBG_DEBUG(0, "Entry \"%s\" exists", p);
  }
  DBG_DEBUG(0, "Returning this: %s", p);
  return p;
}



int GWEN_Directory_GetPath(const char *path,
                           unsigned int flags) {
  char *pbuffer;
  void *p;

  assert(path);
  pbuffer=(char*)malloc(strlen(path)+10);
  *pbuffer=0;
  p=GWEN_Path_Handle(path, pbuffer,
                     flags,
                     GWEN_Directory_HandlePathElement);
  free(pbuffer);
  if (!p) {
    DBG_INFO(0, "here");
    return -1;
  }
  return 0;
}




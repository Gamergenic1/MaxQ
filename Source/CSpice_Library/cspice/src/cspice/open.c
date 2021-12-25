/*

-Source_File open.c ( CSPICE version of the open.c routine )

-Abstract

   This file replaces the standard f2c open.c library file. The Mac classic
   Metrowerks compiler requires a minor modification over the standard
   C scratch file generation operation.
   
-Disclaimer

   THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE
   CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S.
   GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE
   ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE
   PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS"
   TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY
   WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A
   PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC
   SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE
   SOFTWARE AND RELATED MATERIALS, HOWEVER USED.

   IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA
   BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT
   LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND,
   INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS,
   REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE
   REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY.

   RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF
   THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY
   CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE
   ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE.

-Required_Reading

   None.

-Particulars 

   Classic Macintosh scratch file creation occurs via generation of
   a temp file name via a call to tmpnam. The name then passes to 
   fopen in the standard manner.

-Literature_References

   None.

-Author_and_Institution

   E.D. Wright       (JPL)
   
-Restrictions

  1) Requires CSPICE f2c.h header file.  
   
-Version

   -CSPICE Version 1.0.0, 02-JAN-2002 (EDW)  

*/



#include "f2c.h"
#include "fio.h"
#include "string.h"
#ifndef NON_POSIX_STDIO
#ifdef MSDOS
#include "io.h"
#else
#include "unistd.h" /* for access */
#endif
#endif

#ifdef KR_headers
extern char *malloc();
#ifdef NON_ANSI_STDIO
extern char *mktemp();
#endif
extern integer f_clos();
#else
#undef abs
#undef min
#undef max
#include "stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int f__canseek(FILE*);
extern integer f_clos(cllist*);
#endif

#ifdef NON_ANSI_RW_MODES
char *f__r_mode[2] = {"r", "r"};
char *f__w_mode[4] = {"w", "w", "r+w", "r+w"};
#else
char *f__r_mode[2] = {"rb", "r"};
char *f__w_mode[4] = {"wb", "w", "r+b", "r+"};
#endif

 static char f__buf0[400], *f__buf = f__buf0;
 int f__buflen = (int)sizeof(f__buf0);

 static void
#ifdef KR_headers

   f__bufadj(n, c) int n, c;

#else

   f__bufadj(int n, int c)

#endif
   {
   unsigned int len;
   char *nbuf, *s, *t, *te;

   if (f__buf == f__buf0)
      f__buflen = 1024;
   while(f__buflen <= n)
      f__buflen <<= 1;
   len = (unsigned int)f__buflen;
   if (len != f__buflen || !(nbuf = (char*)malloc(len)))
      f__fatal(113, "malloc failure");
   s = nbuf;
   t = f__buf;
   te = t + c;
   while(t < te)
      *s++ = *t++;
   if (f__buf != f__buf0)
      free(f__buf);
   f__buf = nbuf;
   }

int
#ifdef KR_headers

   f__putbuf(c) int c;

#else

   f__putbuf(int c)

#endif
   {
   char *s, *se;
   int n;

   if (f__hiwater > f__recpos)
      f__recpos = f__hiwater;
   n = f__recpos + 1;
   if (n >= f__buflen)
      f__bufadj(n, f__recpos);
   s = f__buf;
   se = s + f__recpos;
   if (c)
      *se++ = c;
   *se = 0;
   for(;;) {
      fputs(s, f__cf);
      s += strlen(s);
      if (s >= se)
         break;   /* normally happens the first time */
      putc(*s++, f__cf);
      }
   return 0;
   }


void
#ifdef KR_headers

   x_putc(c)

#else

   x_putc(int c)

#endif
   {
   if (f__recpos >= f__buflen)
      f__bufadj(f__recpos, f__buflen);
   f__buf[f__recpos++] = c;
   }

#define opnerr(f,m,s) {if(f) errno= m; else opn_err(m,s,a); return(m);}

static void
#ifdef KR_headers

   opn_err(m, s, a) int m; char *s; olist *a;

#else

   opn_err(int m, char *s, olist *a)

#endif
   {
   if (a->ofnm)
     {
     /* supply file name to error message */
      if (a->ofnmlen >= f__buflen)
         f__bufadj((int)a->ofnmlen, 0);
      g_char(a->ofnm, a->ofnmlen, f__curunit->ufnm = f__buf);
      }
   f__fatal(m, s);
   }




#ifdef KR_headers

   integer f_open(a) olist *a;

#else

   integer f_open( olist *a)

#endif
   {   
   unit *b;
   integer rv;
   char buf[256], *s;
   cllist x;
   int ufmt;
   FILE *tf;
#ifndef NON_UNIX_STDIO
   int n;
#endif
   if(a->ounit>=MXUNIT || a->ounit<0)
      err(a->oerr,101,"open")
   if (!f__init)
      f_init();
   f__curunit = b = &f__units[a->ounit];
   if(b->ufd) 
      {
      if(a->ofnm==0)
      {
      same: if (a->oblnk)
            b->ublnk = *a->oblnk == 'z' || *a->oblnk == 'Z';
         return(0);
      }
#ifdef NON_UNIX_STDIO
      if (b->ufnm
       && strlen(b->ufnm) == a->ofnmlen
       && !strncmp(b->ufnm, a->ofnm, (unsigned)a->ofnmlen))
         goto same;
#else
      g_char(a->ofnm,a->ofnmlen,buf);
      if (f__inode(buf,&n) == b->uinode && n == b->udev)
         goto same;
#endif
      x.cunit=a->ounit;
      x.csta=0;
      x.cerr=a->oerr;
      if ((rv = f_clos(&x)) != 0)
         return rv;
      }
   b->url = (int)a->orl;
   b->ublnk = a->oblnk && (*a->oblnk == 'z' || *a->oblnk == 'Z');
   if(a->ofm==0)
       { 
       if(b->url>0) b->ufmt=0;
       else b->ufmt=1;
      }
   else if(*a->ofm=='f' || *a->ofm == 'F') b->ufmt=1;
   else b->ufmt=0;
   ufmt = b->ufmt;
#ifdef url_Adjust
   if (b->url && !ufmt)
      url_Adjust(b->url);
#endif
   if (a->ofnm) 
       {
      g_char(a->ofnm,a->ofnmlen,buf);
      if (!buf[0])
         opnerr(a->oerr,107,"open")
      }
   else
      sprintf(buf, "fort.%ld", a->ounit);
   b->uscrtch = 0;
   b->uend=0;
   b->uwrt = 0;
   b->ufd = 0;
   b->urw = 3;

   switch(a->osta ? *a->osta : 'u')
   {

   case 'o':
   case 'O':
#ifdef NON_POSIX_STDIO

      if (!(tf = fopen(buf,"r")))
         opnerr(a->oerr,errno,"open")
      fclose(tf);
#else
      if ( access(buf,0) )
         {
         opnerr(a->oerr,errno,"open");
         }
#endif
      break;


    case 's':
    case 'S':
 
      b->uscrtch=1;

#ifdef CSPICE_MACPPC

        tmpnam( buf );
        goto replace;

#endif


#ifdef NON_ANSI_STDIO

      (void) strcpy(buf,"tmp.FXXXXXX");
      (void) mktemp(buf);
      goto replace;

#else


#ifndef CSPICE_MACPPC

      if (!(b->ufd = tmpfile()))
         {
         opnerr(a->oerr,errno,"open")
         }

      b->ufnm = 0;

#ifndef NON_UNIX_STDIO
      b->uinode = b->udev = -1;
#endif

      b->useek = 1;
      return 0;

#endif

#endif

   case 'n':
   case 'N':

#ifdef NON_POSIX_STDIO
      if ((tf = fopen(buf,"r")) || (tf = fopen(buf,"a"))) 
         {
         fclose(tf);
         opnerr(a->oerr,128,"open")
         }
#else
      if (!access(buf,0))
         opnerr(a->oerr,128,"open")
#endif

       /* no break */
   case 'r':   /* Fortran 90 replace option */
   case 'R':


#ifdef  NON_ANSI_STDIO
 replace:
#endif

#ifdef CSPICE_MACPPC
 replace:
#endif



      if (tf = fopen(buf,f__w_mode[0]))
         fclose(tf);
   }

   b->ufnm=(char *) malloc((unsigned int)(strlen(buf)+1));
   if(b->ufnm==NULL) opnerr(a->oerr,113,"no space");
   (void) strcpy(b->ufnm,buf);
   if ((s = a->oacc) && b->url)
      ufmt = 0;
   if(!(tf = fopen(buf, f__w_mode[ufmt|2]))) {
      if (tf = fopen(buf, f__r_mode[ufmt]))
         b->urw = 1;
      else if (tf = fopen(buf, f__w_mode[ufmt])) {
         b->uwrt = 1;
         b->urw = 2;
         }
      else
         err(a->oerr, errno, "open");
      }
   b->useek = f__canseek(b->ufd = tf);

#ifndef NON_UNIX_STDIO

   if((b->uinode = f__inode(buf,&b->udev)) == -1)
      opnerr(a->oerr,108,"open")

#endif

   if(b->useek)
      if (a->orl)
         rewind(b->ufd);
      else if ((s = a->oacc) && (*s == 'a' || *s == 'A')
         && fseek(b->ufd, 0L, SEEK_END))
            opnerr(a->oerr,129,"open");
   return(0);
}




#ifdef KR_headers

   fk_open( seq, fmt, n) ftnint n;

#else

   fk_open(int seq, int fmt, ftnint n)

#endif
   {
   char nbuf[10];
   olist a;
   (void) sprintf(nbuf,"fort.%ld",n);
   a.oerr=1;
   a.ounit=n;
   a.ofnm=nbuf;
   a.ofnmlen=strlen(nbuf);
   a.osta=NULL;
   a.oacc= seq==SEQ?"s":"d";
   a.ofm = fmt==FMT?"f":"u";
   a.orl = seq==DIR?1:0;
   a.oblnk=NULL;
   return(f_open(&a));
   }

#ifdef __cplusplus
}
#endif

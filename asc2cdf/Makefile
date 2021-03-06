#
#    Makefile for ASCII to netCDF translators.
#
CC=		g++
BINDIR=		${JLOCAL}/bin
MANDIR=		${JLOCAL}/man/man1
INCLUDES=	-I$(JLOCAL)/include
CFLAGS=		-Wall -g ${INCLUDES} -DVARDB -DZEROBIN

# Solaris
LIBS=		-L/jnet/solaris/lib -lVarDB -Wl,-Bstatic -lnetcdf -Wl,-Bdynamic
ANONFTP=	/jnet/ftp/pub/src/bin.Solaris2.9

# Linux
LIBS=	-L${JLOCAL}/lib -lVarDB -lraf -lnetcdf -lhdf5 -lhdf5_hl
ANONFTP=/net/ftp/pub/archive/RAF-src/bin.RHEL6
WWWDOC=	/net/www/raf/Software

SRCS=   asc2cdf.c plain.c nasaAmes.c nasaLangley.c ICARTT.c BADC_CSV.c getmem.c error.c
OBJS=   asc2cdf.o plain.o nasaAmes.o nasaLangley.o ICARTT.o BADC_CSV.o getmem.o error.o
HDRS=	define.h

PROG=	asc2cdf

.c.o:
	${CC} ${CFLAGS} -c $*.c

${PROG}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIBS} -o $@

install: ${PROG}
	test -d $(BINDIR) || mkdir $(BINDIR)
	cp ${PROG} ${BINDIR}
	test -d $(MANDIR) || mkdir $(MANDIR)
	cp ${PROG}.man ${MANDIR}/${PROG}.1

publish:
	cp ${PROG} $(ANONFTP)
	cp ${PROG}.html ${WWWDOC}
	cp ${PROG}.man ${ANONFTP}

clean:
	rm -f ${OBJS} ${PROG} core

${OBJS}: ${HDRS}

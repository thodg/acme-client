
PROG = acme-client

SRCS =	acctproc.c \
	base64.c \
	certproc.c \
	chngproc.c \
	dbg.c \
	dnsproc.c \
	fileproc.c \
	http.c \
	jsmn.c \
	json.c \
	keyproc.c \
	main.c \
	netproc.c \
	parse.y \
	recallocarray.c \
	revokeproc.c \
	key.c \
	util.c

OBJS =	acctproc.o \
	base64.o \
	certproc.o \
	chngproc.o \
	dbg.o \
	dnsproc.o \
	fileproc.o \
	http.o \
	jsmn.o \
	json.o \
	keyproc.o \
	main.o \
	netproc.o \
	parse.o \
	recallocarray.o \
	revokeproc.o \
	key.o \
	util.o

MAN=	acme-client.1 \
	acme-client.conf.5

all: build

build: ${PROG}

CLEANFILES = *.o ${PROG}

clean:
	rm -f ${CLEANFILES}

include configure.mk

LIBS +=	-ltls -lssl -lcrypto

CFLAGS += -W -Wall -Wno-deprecated-declarations -Werror
CFLAGS += -O2 -pipe

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

${PROG}: ${OBJS}
	${CC} ${OBJS} ${LIBS} -o ${PROG}

install:
	install -d -m 0755 ${DESTDIR}${prefix}/bin
	install -m 0755 ${PROG} ${DESTDIR}${prefix}/bin/${PROG}
	install -d -m 0755 ${DESTDIR}${prefix}/share/man/man1
	install -m 0644 acme-client.1 ${DESTDIR}${prefix}/share/man/man1/
	install -d -m 0755 ${DESTDIR}${prefix}/share/man/man5
	install -m 0644 acme-client.conf.5 ${DESTDIR}${prefix}/share/man/man5/

uninstall:
	rm -f ${prefix}/bin/${PROG}
	rm -f ${prefix}/share/man/man1/acme-client.1
	rm -f ${prefix}/share/man/man5/acme-client.conf.5

.PHONY: all build clean install uninstall

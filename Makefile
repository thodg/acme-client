
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

.PHONY: all build clean

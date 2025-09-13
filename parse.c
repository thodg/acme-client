#include <stdlib.h>
#include <string.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
#define YYPREFIX "yy"
#line 27 "parse.y"
#include <sys/types.h>
#include <sys/queue.h>
#include <sys/stat.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "parse.h"
#include "extern.h"

TAILQ_HEAD(files, file)		 files = TAILQ_HEAD_INITIALIZER(files);
static struct file {
	TAILQ_ENTRY(file)	 entry;
	FILE			*stream;
	char			*name;
	size_t			 ungetpos;
	size_t			 ungetsize;
	u_char			*ungetbuf;
	int			 eof_reached;
	int			 lineno;
	int			 errors;
} *file, *topfile;
struct file	*pushfile(const char *);
int		 popfile(void);
int		 yyparse(void);
int		 yylex(void);
int		 yyerror(const char *, ...)
    __attribute__((__format__ (printf, 1, 2)))
    __attribute__((__nonnull__ (1)));
int		 kw_cmp(const void *, const void *);
int		 lookup(char *);
int		 igetc(void);
int		 lgetc(int);
void		 lungetc(int);
int		 findeol(void);

struct authority_c	*conf_new_authority(struct acme_conf *, char *);
struct domain_c		*conf_new_domain(struct acme_conf *, char *);
struct keyfile		*conf_new_keyfile(struct acme_conf *, char *);
void			 clear_config(struct acme_conf *);
const char*		 kt2txt(enum keytype);
void			 print_config(struct acme_conf *);
int			 conf_check_file(char *);

TAILQ_HEAD(symhead, sym)	 symhead = TAILQ_HEAD_INITIALIZER(symhead);
struct sym {
	TAILQ_ENTRY(sym)	 entry;
	int			 used;
	int			 persist;
	char			*nam;
	char			*val;
};
int		 symset(const char *, const char *, int);
char		*symget(const char *);

static struct acme_conf		*conf;
static struct authority_c	*auth;
static struct domain_c		*domain;
static int			 errors = 0;

typedef struct {
	union {
		int64_t		 number;
		char		*string;
	} v;
	int lineno;
} YYSTYPE;

#line 88 "parse.c"
#define AUTHORITY 257
#define URL 258
#define API 259
#define ACCOUNT 260
#define CONTACT 261
#define DOMAIN 262
#define ALTERNATIVE 263
#define NAME 264
#define NAMES 265
#define CERT 266
#define FULL 267
#define CHAIN 268
#define KEY 269
#define SIGN 270
#define WITH 271
#define CHALLENGEDIR 272
#define YES 273
#define NO 274
#define INCLUDE 275
#define ERROR 276
#define RSA 277
#define ECDSA 278
#define INSECURE 279
#define STRING 280
#define NUMBER 281
#define YYERRCODE 256
const short yylhs[] =
	{                                        -1,
    0,    0,    0,    0,    0,    0,    0,    3,    1,    1,
    4,    7,    7,    8,    9,    9,   10,    5,   11,   11,
   12,   12,   12,   12,   13,    6,    2,    2,    2,   14,
   14,   15,   15,   15,   15,   15,   15,   15,   15,   16,
   16,   17,
};
const short yylen[] =
	{                                         2,
    0,    3,    3,    2,    3,    3,    3,    2,    2,    1,
    3,    2,    0,    2,    2,    1,    0,    7,    3,    2,
    3,    4,    2,    1,    0,    7,    1,    1,    0,    3,
    2,    6,    3,    4,    3,    4,    5,    3,    2,    3,
    2,    1,
};
const short yydefred[] =
	{                                      1,
    0,    0,    0,    0,    0,    0,    4,    0,    0,    0,
    0,    7,   17,   25,    8,    0,    2,    3,    5,    6,
    0,    0,   10,    0,    0,    0,    9,    0,    0,    0,
   12,    0,    0,    0,   24,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   23,   18,    0,   20,    0,
    0,    0,    0,    0,    0,    0,   39,   26,    0,   31,
   21,    0,    0,   19,   33,   35,    0,    0,    0,    0,
   38,   30,   27,   28,   22,   14,    0,   36,   34,    0,
   37,   42,    0,    0,   32,    0,    0,    0,   15,   40,
};
const short yydgoto[] =
	{                                       1,
   24,   75,    8,    9,   10,   11,   29,   64,   88,   21,
   36,   37,   22,   42,   43,   83,   84,
};
const short yysindex[] =
	{                                      0,
  -10,   -1, -266, -256, -254,  -34,    0,   27,   28,   30,
   31,    0,    0,    0,    0, -237,    0,    0,    0,    0,
  -76,  -70,    0, -226,   45,   45,    0,   45, -248, -240,
    0, -202, -212, -222,    0, -110,   45, -218, -206, -211,
 -219,  -96,   45, -217, -216,    0,    0,   52,    0, -215,
 -213, -199, -196, -209,  -51, -207,    0,    0,   52,    0,
    0, -257,   45,    0,    0,    0, -192, -205, -257,   45,
    0,    0,    0,    0,    0,    0, -204,    0,    0, -203,
    0,    0,  -47,   -5,    0,   45,    0, -203,    0,    0,};
const short yyrindex[] =
	{                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   69, -243, -228,    0, -124,    0,    0,
    0,    0,    0,    0,    0,    0,  -97,    0,    0,    0,
    0,    0,  -92,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   -6, -118,    0,    0,    0,    0,    0,   -4, -266,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -123,    0, -266, -122,    0,    0,    0,};
const short yygindex[] =
	{                                      0,
    0,   11,    0,    0,    0,    0,  -18,   22,    0,    0,
    0,   46,    0,    0,   41,   -3,    0,
};
#define YYTABLESIZE 273
const short yytable[] =
	{                                       7,
   13,   13,   41,   29,   28,   29,   13,   30,   12,   31,
   32,   33,   34,   13,   47,   13,   13,   13,   49,   73,
   74,   38,   39,   14,   60,   15,   16,   13,   58,   40,
   35,   41,   13,   13,   13,   13,   17,   18,   86,   19,
   20,   13,   23,   13,   76,   50,   25,   51,   52,   53,
   54,   80,   26,   27,   28,   44,   45,   46,   55,   56,
   57,   63,   61,   62,   65,   87,   66,   89,   67,   68,
   69,   70,   71,   77,   78,   81,   82,   85,   11,   79,
   72,   48,   59,    0,   90,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   29,    0,
   29,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   13,   13,   13,   13,   13,    0,
   13,   13,   13,   13,   13,   13,    0,   13,   32,   33,
   34,   13,    0,   13,   13,   13,   13,   16,    0,    0,
   13,   13,   13,   13,    0,   38,   39,    0,   35,   13,
   13,    0,    0,   40,    0,   41,    0,   13,    0,   13,
    0,   13,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    2,    3,    0,    0,    0,
    0,    4,   29,   29,   29,    0,    0,   29,   29,    0,
    0,    0,    0,    0,    5,   29,    0,   29,    0,    6,
    0,    0,   29,
};
const short yycheck[] =
	{                                      10,
  125,  125,  125,   10,   10,   10,  125,   26,   10,   28,
  259,  260,  261,  280,  125,  259,  260,  261,   37,  277,
  278,  262,  263,  280,   43,  280,   61,  125,  125,  270,
  279,  272,  125,  262,  263,  279,   10,   10,   44,   10,
   10,  270,  280,  272,   63,  264,  123,  266,  267,  268,
  269,   70,  123,  280,   10,  258,  269,  280,  265,  271,
  280,   10,  280,  280,  280,   84,  280,   86,  268,  266,
  280,  123,  280,  266,  280,  280,  280,  125,   10,   69,
   59,   36,   42,   -1,   88,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  125,   -1,
  125,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  259,  260,  261,  262,  263,   -1,
  259,  260,  261,  262,  263,  270,   -1,  272,  259,  260,
  261,  270,   -1,  272,  279,  280,  280,  280,   -1,   -1,
  279,  259,  260,  261,   -1,  262,  263,   -1,  279,  262,
  263,   -1,   -1,  270,   -1,  272,   -1,  270,   -1,  272,
   -1,  279,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  256,  257,   -1,   -1,   -1,
   -1,  262,  259,  260,  261,   -1,   -1,  262,  263,   -1,
   -1,   -1,   -1,   -1,  275,  270,   -1,  272,   -1,  280,
   -1,   -1,  279,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 281
#if YYDEBUG
const char * const yyname[] =
	{
"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'='",0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"AUTHORITY",
"URL","API","ACCOUNT","CONTACT","DOMAIN","ALTERNATIVE","NAME","NAMES","CERT",
"FULL","CHAIN","KEY","SIGN","WITH","CHALLENGEDIR","YES","NO","INCLUDE","ERROR",
"RSA","ECDSA","INSECURE","STRING","NUMBER",
};
const char * const yyrule[] =
	{"$accept : grammar",
"grammar :",
"grammar : grammar include '\\n'",
"grammar : grammar varset '\\n'",
"grammar : grammar '\\n'",
"grammar : grammar authority '\\n'",
"grammar : grammar domain '\\n'",
"grammar : grammar error '\\n'",
"include : INCLUDE STRING",
"string : string STRING",
"string : STRING",
"varset : STRING '=' string",
"optnl : '\\n' optnl",
"optnl :",
"nl : '\\n' optnl",
"optcommanl : ',' optnl",
"optcommanl : optnl",
"$$1 :",
"authority : AUTHORITY STRING $$1 '{' optnl authorityopts_l '}'",
"authorityopts_l : authorityopts_l authorityoptsl nl",
"authorityopts_l : authorityoptsl optnl",
"authorityoptsl : API URL STRING",
"authorityoptsl : ACCOUNT KEY STRING keytype",
"authorityoptsl : CONTACT STRING",
"authorityoptsl : INSECURE",
"$$2 :",
"domain : DOMAIN STRING $$2 '{' optnl domainopts_l '}'",
"keytype : RSA",
"keytype : ECDSA",
"keytype :",
"domainopts_l : domainopts_l domainoptsl nl",
"domainopts_l : domainoptsl optnl",
"domainoptsl : ALTERNATIVE NAMES '{' optnl altname_l '}'",
"domainoptsl : DOMAIN NAME STRING",
"domainoptsl : DOMAIN KEY STRING keytype",
"domainoptsl : DOMAIN CERT STRING",
"domainoptsl : DOMAIN CHAIN CERT STRING",
"domainoptsl : DOMAIN FULL CHAIN CERT STRING",
"domainoptsl : SIGN WITH STRING",
"domainoptsl : CHALLENGEDIR STRING",
"altname_l : altname optcommanl altname_l",
"altname_l : altname optnl",
"altname : STRING",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
/* LINTUSED */
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
unsigned int yystacksize;
int yyparse(void);
#line 429 "parse.y"

struct keywords {
	const char	*k_name;
	int		 k_val;
};

int
yyerror(const char *fmt, ...)
{
	va_list		 ap;
	char		*msg;

	file->errors++;
	va_start(ap, fmt);
	if (vasprintf(&msg, fmt, ap) == -1)
		err(EXIT_FAILURE, "yyerror vasprintf");
	va_end(ap);
	fprintf(stderr, "%s:%d: %s\n", file->name, yylval.lineno, msg);
	free(msg);
	return (0);
}

int
kw_cmp(const void *k, const void *e)
{
	return strcmp(k, ((const struct keywords *)e)->k_name);
}

int
lookup(char *s)
{
	/* this has to be sorted always */
	static const struct keywords keywords[] = {
		{"account",		ACCOUNT},
		{"alternative",		ALTERNATIVE},
		{"api",			API},
		{"authority",		AUTHORITY},
		{"certificate",		CERT},
		{"chain",		CHAIN},
		{"challengedir",	CHALLENGEDIR},
		{"contact",		CONTACT},
		{"domain",		DOMAIN},
		{"ecdsa",		ECDSA},
		{"full",		FULL},
		{"include",		INCLUDE},
		{"insecure",		INSECURE},
		{"key",			KEY},
		{"name",		NAME},
		{"names",		NAMES},
		{"rsa",			RSA},
		{"sign",		SIGN},
		{"url",			URL},
		{"with",		WITH},
	};
	const struct keywords	*p;

	p = bsearch(s, keywords, sizeof(keywords)/sizeof(keywords[0]),
	    sizeof(keywords[0]), kw_cmp);

	if (p != NULL)
		return p->k_val;
	else
		return STRING;
}

#define	START_EXPAND	1
#define	DONE_EXPAND	2

static int	expanding;

int
igetc(void)
{
	int	c;

	while (1) {
		if (file->ungetpos > 0)
			c = file->ungetbuf[--file->ungetpos];
		else
			c = getc(file->stream);

		if (c == START_EXPAND)
			expanding = 1;
		else if (c == DONE_EXPAND)
			expanding = 0;
		else
			break;
	}
	return c;
}

int
lgetc(int quotec)
{
	int		c, next;

	if (quotec) {
		if ((c = igetc()) == EOF) {
			yyerror("reached end of file while parsing "
			    "quoted string");
			if (file == topfile || popfile() == EOF)
				return (EOF);
			return quotec;
		}
		return c;
	}

	while ((c = igetc()) == '\\') {
		next = igetc();
		if (next != '\n') {
			c = next;
			break;
		}
		yylval.lineno = file->lineno;
		file->lineno++;
	}

	if (c == EOF) {
		/*
		 * Fake EOL when hit EOF for the first time. This gets line
		 * count right if last line in included file is syntactically
		 * invalid and has no newline.
		 */
		if (file->eof_reached == 0) {
			file->eof_reached = 1;
			return '\n';
		}
		while (c == EOF) {
			if (file == topfile || popfile() == EOF)
				return (EOF);
			c = igetc();
		}
	}
	return c;
}

void
lungetc(int c)
{
	if (c == EOF)
		return;

	if (file->ungetpos >= file->ungetsize) {
		void *p = reallocarray(file->ungetbuf, file->ungetsize, 2);
		if (p == NULL)
			err(1, "%s", __func__);
		file->ungetbuf = p;
		file->ungetsize *= 2;
	}
	file->ungetbuf[file->ungetpos++] = c;
}

int
findeol(void)
{
	int	c;

	/* skip to either EOF or the first real EOL */
	while (1) {
		c = lgetc(0);
		if (c == '\n') {
			file->lineno++;
			break;
		}
		if (c == EOF)
			break;
	}
	return ERROR;
}

int
yylex(void)
{
	char	 buf[8096];
	char	*p, *val;
	int	 quotec, next, c;
	int	 token;

top:
	p = buf;
	while ((c = lgetc(0)) == ' ' || c == '\t')
		; /* nothing */

	yylval.lineno = file->lineno;
	if (c == '#')
		while ((c = lgetc(0)) != '\n' && c != EOF)
			; /* nothing */
	if (c == '$' && !expanding) {
		while (1) {
			if ((c = lgetc(0)) == EOF)
				return 0;

			if (p + 1 >= buf + sizeof(buf) - 1) {
				yyerror("string too long");
				return findeol();
			}
			if (isalnum(c) || c == '_') {
				*p++ = c;
				continue;
			}
			*p = '\0';
			lungetc(c);
			break;
		}
		val = symget(buf);
		if (val == NULL) {
			yyerror("macro '%s' not defined", buf);
			return findeol();
		}
		p = val + strlen(val) - 1;
		lungetc(DONE_EXPAND);
		while (p >= val) {
			lungetc((unsigned char)*p);
			p--;
		}
		lungetc(START_EXPAND);
		goto top;
	}

	switch (c) {
	case '\'':
	case '"':
		quotec = c;
		while (1) {
			if ((c = lgetc(quotec)) == EOF)
				return 0;
			if (c == '\n') {
				file->lineno++;
				continue;
			} else if (c == '\\') {
				if ((next = lgetc(quotec)) == EOF)
					return 0;
				if (next == quotec || next == ' ' ||
				    next == '\t')
					c = next;
				else if (next == '\n') {
					file->lineno++;
					continue;
				} else
					lungetc(next);
			} else if (c == quotec) {
				*p = '\0';
				break;
			} else if (c == '\0') {
				yyerror("syntax error");
				return findeol();
			}
			if (p + 1 >= buf + sizeof(buf) - 1) {
				yyerror("string too long");
				return findeol();
			}
			*p++ = c;
		}
		yylval.v.string = strdup(buf);
		if (yylval.v.string == NULL)
			err(EXIT_FAILURE, "%s", __func__);
		return STRING;
	}

#define allowed_to_end_number(x) \
	(isspace(x) || x == ')' || x ==',' || x == '/' || x == '}' || x == '=')

	if (c == '-' || isdigit(c)) {
		do {
			*p++ = c;
			if ((size_t)(p-buf) >= sizeof(buf)) {
				yyerror("string too long");
				return findeol();
			}
		} while ((c = lgetc(0)) != EOF && isdigit(c));
		lungetc(c);
		if (p == buf + 1 && buf[0] == '-')
			goto nodigits;
		if (c == EOF || allowed_to_end_number(c)) {
			const char *errstr = NULL;

			*p = '\0';
			yylval.v.number = strtonum(buf, LLONG_MIN,
			    LLONG_MAX, &errstr);
			if (errstr != NULL) {
				yyerror("\"%s\" invalid number: %s",
				    buf, errstr);
				return (findeol());
			}
			return NUMBER;
		} else {
nodigits:
			while (p > buf + 1)
				lungetc((unsigned char)*--p);
			c = (unsigned char)*--p;
			if (c == '-')
				return c;
		}
	}

#define allowed_in_string(x) \
	(isalnum(x) || (ispunct(x) && x != '(' && x != ')' && \
	x != '{' && x != '}' && \
	x != '!' && x != '=' && x != '#' && \
	x != ','))

	if (isalnum(c) || c == ':' || c == '_') {
		do {
			*p++ = c;
			if ((size_t)(p-buf) >= sizeof(buf)) {
				yyerror("string too long");
				return (findeol());
			}
		} while ((c = lgetc(0)) != EOF && (allowed_in_string(c)));
		lungetc(c);
		*p = '\0';
		if ((token = lookup(buf)) == STRING) {
			if ((yylval.v.string = strdup(buf)) == NULL)
				err(EXIT_FAILURE, "%s", __func__);
		}
		return token;
	}
	if (c == '\n') {
		yylval.lineno = file->lineno;
		file->lineno++;
	}
	if (c == EOF)
		return 0;
	return c;
}

struct file *
pushfile(const char *name)
{
	struct file	*nfile;

	if ((nfile = calloc(1, sizeof(struct file))) == NULL) {
		warn("%s", __func__);
		return NULL;
	}
	if ((nfile->name = strdup(name)) == NULL) {
		warn("%s", __func__);
		free(nfile);
		return NULL;
	}
	if ((nfile->stream = fopen(nfile->name, "r")) == NULL) {
		warn("%s: %s", __func__, nfile->name);
		free(nfile->name);
		free(nfile);
		return NULL;
	}
	nfile->lineno = TAILQ_EMPTY(&files) ? 1 : 0;
	nfile->ungetsize = 16;
	nfile->ungetbuf = malloc(nfile->ungetsize);
	if (nfile->ungetbuf == NULL) {
		warn("%s", __func__);
		fclose(nfile->stream);
		free(nfile->name);
		free(nfile);
		return NULL;
	}
	TAILQ_INSERT_TAIL(&files, nfile, entry);
	return nfile;
}

int
popfile(void)
{
	struct file	*prev;

	if ((prev = TAILQ_PREV(file, files, entry)) != NULL)
		prev->errors += file->errors;

	TAILQ_REMOVE(&files, file, entry);
	fclose(file->stream);
	free(file->name);
	free(file->ungetbuf);
	free(file);
	file = prev;
	return (file ? 0 : EOF);
}

struct acme_conf *
parse_config(const char *filename, int opts)
{
	struct sym	*sym, *next;

	if ((conf = calloc(1, sizeof(struct acme_conf))) == NULL)
		err(EXIT_FAILURE, "%s", __func__);
	conf->opts = opts;

	if ((file = pushfile(filename)) == NULL) {
		free(conf);
		return NULL;
	}
	topfile = file;

	TAILQ_INIT(&conf->authority_list);
	TAILQ_INIT(&conf->domain_list);

	yyparse();
	errors = file->errors;
	popfile();

	/* Free macros and check which have not been used. */
	TAILQ_FOREACH_SAFE(sym, &symhead, entry, next) {
		if ((conf->opts & ACME_OPT_VERBOSE) && !sym->used)
			fprintf(stderr, "warning: macro '%s' not "
			    "used\n", sym->nam);
		if (!sym->persist) {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}

	if (errors != 0) {
		clear_config(conf);
		return NULL;
	}

	if (opts & ACME_OPT_CHECK) {
		if (opts & ACME_OPT_VERBOSE)
			print_config(conf);
		exit(0);
	}


	return conf;
}

int
symset(const char *nam, const char *val, int persist)
{
	struct sym	*sym;

	TAILQ_FOREACH(sym, &symhead, entry) {
		if (strcmp(nam, sym->nam) == 0)
			break;
	}

	if (sym != NULL) {
		if (sym->persist == 1)
			return (0);
		else {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}
	if ((sym = calloc(1, sizeof(*sym))) == NULL)
		return -1;

	sym->nam = strdup(nam);
	if (sym->nam == NULL) {
		free(sym);
		return -1;
	}
	sym->val = strdup(val);
	if (sym->val == NULL) {
		free(sym->nam);
		free(sym);
		return -1;
	}
	sym->used = 0;
	sym->persist = persist;
	TAILQ_INSERT_TAIL(&symhead, sym, entry);
	return 0;
}

int
cmdline_symset(char *s)
{
	char	*sym, *val;
	int	ret;

	if ((val = strrchr(s, '=')) == NULL)
		return -1;
	sym = strndup(s, val - s);
	if (sym == NULL)
		errx(EXIT_FAILURE, "%s: strndup", __func__);
	ret = symset(sym, val + 1, 1);
	free(sym);

	return ret;
}

char *
symget(const char *nam)
{
	struct sym	*sym;

	TAILQ_FOREACH(sym, &symhead, entry) {
		if (strcmp(nam, sym->nam) == 0) {
			sym->used = 1;
			return sym->val;
		}
	}
	return NULL;
}

struct authority_c *
conf_new_authority(struct acme_conf *c, char *s)
{
	struct authority_c *a;

	a = authority_find(c, s);
	if (a != NULL)
		return NULL;
	if ((a = calloc(1, sizeof(struct authority_c))) == NULL)
		err(EXIT_FAILURE, "%s", __func__);
	TAILQ_INSERT_TAIL(&c->authority_list, a, entry);

	a->name = s;
	return a;
}

struct authority_c *
authority_find(struct acme_conf *c, char *s)
{
	struct authority_c	*a;

	TAILQ_FOREACH(a, &c->authority_list, entry) {
		if (strncmp(a->name, s, AUTH_MAXLEN) == 0) {
			return a;
		}
	}
	return NULL;
}

struct authority_c *
authority_find0(struct acme_conf *c)
{
	return (TAILQ_FIRST(&c->authority_list));
}

struct domain_c *
conf_new_domain(struct acme_conf *c, char *s)
{
	struct domain_c *d;

	d = domain_find_handle(c, s);
	if (d != NULL)
		return (NULL);
	if ((d = calloc(1, sizeof(struct domain_c))) == NULL)
		err(EXIT_FAILURE, "%s", __func__);
	TAILQ_INSERT_TAIL(&c->domain_list, d, entry);

	d->handle = s;
	TAILQ_INIT(&d->altname_list);

	return d;
}

struct domain_c *
domain_find_handle(struct acme_conf *c, char *s)
{
	struct domain_c	*d;

	TAILQ_FOREACH(d, &c->domain_list, entry) {
		if (strncmp(d->handle, s, DOMAIN_MAXLEN) == 0) {
			return d;
		}
	}
	return NULL;
}

struct keyfile *
conf_new_keyfile(struct acme_conf *c, char *s)
{
	struct keyfile *k;

	LIST_FOREACH(k, &c->used_key_list, entry) {
		if (strncmp(k->name, s, PATH_MAX) == 0) {
			return NULL;
		}
	}

	if ((k = calloc(1, sizeof(struct keyfile))) == NULL)
		err(EXIT_FAILURE, "%s", __func__);
	LIST_INSERT_HEAD(&c->used_key_list, k, entry);

	k->name = s;
	return k;
}

void
clear_config(struct acme_conf *xconf)
{
	struct authority_c	*a;
	struct domain_c		*d;
	struct altname_c	*ac;

	while ((a = TAILQ_FIRST(&xconf->authority_list)) != NULL) {
		TAILQ_REMOVE(&xconf->authority_list, a, entry);
		free(a);
	}
	while ((d = TAILQ_FIRST(&xconf->domain_list)) != NULL) {
		while ((ac = TAILQ_FIRST(&d->altname_list)) != NULL) {
			TAILQ_REMOVE(&d->altname_list, ac, entry);
			free(ac);
		}
		TAILQ_REMOVE(&xconf->domain_list, d, entry);
		free(d);
	}
	free(xconf);
}

const char*
kt2txt(enum keytype kt)
{
	switch (kt) {
	case KT_RSA:
		return "rsa";
	case KT_ECDSA:
		return "ecdsa";
	default:
		return "<unknown>";
	}
}

void
print_config(struct acme_conf *xconf)
{
	struct authority_c	*a;
	struct domain_c		*d;
	struct altname_c	*ac;
	int			 f;

	TAILQ_FOREACH(a, &xconf->authority_list, entry) {
		printf("authority %s {\n", a->name);
		if (a->api != NULL)
			printf("\tapi url \"%s\"\n", a->api);
		if (a->account != NULL)
			printf("\taccount key \"%s\" %s\n", a->account,
			    kt2txt(a->keytype));
		if (a->insecure)
			printf("\tinsecure\n");
		printf("}\n\n");
	}
	TAILQ_FOREACH(d, &xconf->domain_list, entry) {
		f = 0;
		printf("domain %s {\n", d->handle);
		if (d->domain != NULL)
			printf("\tdomain name \"%s\"\n", d->domain);
		TAILQ_FOREACH(ac, &d->altname_list, entry) {
			if (!f)
				printf("\talternative names {");
			if (ac->domain != NULL) {
				printf("%s%s", f ? ", " : " ", ac->domain);
				f = 1;
			}
		}
		if (f)
			printf(" }\n");
		if (d->key != NULL)
			printf("\tdomain key \"%s\" %s\n", d->key, kt2txt(
			    d->keytype));
		if (d->cert != NULL)
			printf("\tdomain certificate \"%s\"\n", d->cert);
		if (d->chain != NULL)
			printf("\tdomain chain certificate \"%s\"\n", d->chain);
		if (d->fullchain != NULL)
			printf("\tdomain full chain certificate \"%s\"\n",
			    d->fullchain);
		if (d->auth != NULL)
			printf("\tsign with \"%s\"\n", d->auth);
		if (d->challengedir != NULL)
			printf("\tchallengedir \"%s\"\n", d->challengedir);
		printf("}\n\n");
	}
}

/*
 * This isn't RFC1035 compliant, but does the bare minimum in making
 * sure that we don't get bogus domain names on the command line, which
 * might otherwise screw up our directory structure.
 * Returns zero on failure, non-zero on success.
 */
int
domain_valid(const char *cp)
{

	for ( ; *cp != '\0'; cp++)
		if (!(*cp == '.' || *cp == '-' ||
		    *cp == '_' || isalnum((unsigned char)*cp)))
			return 0;
	return 1;
}

int
conf_check_file(char *s)
{
	struct stat st;

	if (s[0] != '/') {
		warnx("%s: not an absolute path", s);
		return 0;
	}
	if (stat(s, &st)) {
		if (errno == ENOENT)
			return 1;
		warn("cannot stat %s", s);
		return 0;
	}
	if (st.st_mode & (S_IRWXG | S_IRWXO)) {
		warnx("%s: group read/writable or world read/writable", s);
		return 0;
	}
	return 1;
}
#line 1030 "parse.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    unsigned int newsize;
    long sslen;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    sslen = yyssp - yyss;
#ifdef SIZE_MAX
#define YY_SIZE_MAX SIZE_MAX
#else
#define YY_SIZE_MAX 0xffffffffU
#endif
    if (newsize && YY_SIZE_MAX / newsize < sizeof *newss)
        goto bail;
    newss = (short *)realloc(yyss, newsize * sizeof *newss);
    if (newss == NULL)
        goto bail;
    yyss = newss;
    yyssp = newss + sslen;
    if (newsize && YY_SIZE_MAX / newsize < sizeof *newvs)
        goto bail;
    newvs = (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs);
    if (newvs == NULL)
        goto bail;
    yyvs = newvs;
    yyvsp = newvs + sslen;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
bail:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return -1;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif /* YYDEBUG */

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 7:
#line 123 "parse.y"
{ file->errors++; }
break;
case 8:
#line 126 "parse.y"
{
			struct file	*nfile;

			if ((nfile = pushfile(yyvsp[0].v.string)) == NULL) {
				yyerror("failed to include file %s", yyvsp[0].v.string);
				free(yyvsp[0].v.string);
				YYERROR;
			}
			free(yyvsp[0].v.string);

			file = nfile;
			lungetc('\n');
		}
break;
case 9:
#line 141 "parse.y"
{
			if (asprintf(&yyval.v.string, "%s %s", yyvsp[-1].v.string, yyvsp[0].v.string) == -1) {
				free(yyvsp[-1].v.string);
				free(yyvsp[0].v.string);
				yyerror("string: asprintf");
				YYERROR;
			}
			free(yyvsp[-1].v.string);
			free(yyvsp[0].v.string);
		}
break;
case 11:
#line 154 "parse.y"
{
			char *s = yyvsp[-2].v.string;
			if (conf->opts & ACME_OPT_VERBOSE)
				printf("%s = \"%s\"\n", yyvsp[-2].v.string, yyvsp[0].v.string);
			while (*s++) {
				if (isspace((unsigned char)*s)) {
					yyerror("macro name cannot contain "
					    "whitespace");
					free(yyvsp[-2].v.string);
					free(yyvsp[0].v.string);
					YYERROR;
				}
			}
			if (symset(yyvsp[-2].v.string, yyvsp[0].v.string, 0) == -1)
				errx(EXIT_FAILURE, "cannot store variable");
			free(yyvsp[-2].v.string);
			free(yyvsp[0].v.string);
		}
break;
case 17:
#line 185 "parse.y"
{
			char *s;
			if ((s = strdup(yyvsp[0].v.string)) == NULL)
				err(EXIT_FAILURE, "strdup");
			if ((auth = conf_new_authority(conf, s)) == NULL) {
				free(s);
				yyerror("authority already defined");
				YYERROR;
			}
		}
break;
case 18:
#line 194 "parse.y"
{
			if (auth->api == NULL) {
				yyerror("authority %s: no api URL specified",
				    auth->name);
				YYERROR;
			}
			if (auth->account == NULL) {
				yyerror("authority %s: no account key file "
				    "specified", auth->name);
				YYERROR;
			}
			auth = NULL;
		}
break;
case 21:
#line 213 "parse.y"
{
			char *s;
			if (auth->api != NULL) {
				yyerror("duplicate api");
				YYERROR;
			}
			if ((s = strdup(yyvsp[0].v.string)) == NULL)
				err(EXIT_FAILURE, "strdup");
			auth->api = s;
		}
break;
case 22:
#line 223 "parse.y"
{
			char *s;
			if (auth->account != NULL) {
				yyerror("duplicate account");
				YYERROR;
			}
			if ((s = strdup(yyvsp[-1].v.string)) == NULL)
				err(EXIT_FAILURE, "strdup");
			auth->account = s;
			auth->keytype = yyvsp[0].v.number;
		}
break;
case 23:
#line 234 "parse.y"
{
			char *s;
			if (auth->contact != NULL) {
				yyerror("duplicate contact");
				YYERROR;
			}
			if ((s = strdup(yyvsp[0].v.string)) == NULL)
				err(EXIT_FAILURE, "strdup");
			auth->contact = s;
		}
break;
case 24:
#line 244 "parse.y"
{
			auth->insecure = 1;
		}
break;
case 25:
#line 249 "parse.y"
{
			char *s;
			if ((s = strdup(yyvsp[0].v.string)) == NULL)
				err(EXIT_FAILURE, "strdup");
			if (!domain_valid(s)) {
				yyerror("%s: bad domain syntax", s);
				free(s);
				YYERROR;
			}
			if ((domain = conf_new_domain(conf, s)) == NULL) {
				free(s);
				yyerror("domain already defined");
				YYERROR;
			}
		}
break;
case 26:
#line 263 "parse.y"
{
			if (domain->domain == NULL) {
				if ((domain->domain = strdup(domain->handle))
				    == NULL)
					err(EXIT_FAILURE, "strdup");
			}
			/* enforce minimum config here */
			if (domain->key == NULL) {
				yyerror("no domain key file specified for "
				    "domain %s", domain->domain);
				YYERROR;
			}
			if (domain->cert == NULL && domain->fullchain == NULL) {
				yyerror("at least certificate file or full "
				    "certificate chain file must be specified "
				    "for domain %s", domain->domain);
				YYERROR;
			}
			domain = NULL;
		}
break;
case 27:
#line 285 "parse.y"
{ yyval.v.number = KT_RSA; }
break;
case 28:
#line 286 "parse.y"
{ yyval.v.number = KT_ECDSA; }
break;
case 29:
#line 287 "parse.y"
{ yyval.v.number = KT_RSA; }
break;
case 33:
#line 295 "parse.y"
{
			char *s;
			if (domain->domain != NULL) {
				yyerror("duplicate domain name");
				YYERROR;
			}
			if ((s = strdup(yyvsp[0].v.string)) == NULL)
				err(EXIT_FAILURE, "strdup");
			domain->domain = s;
		}
break;
case 34:
#line 305 "parse.y"
{
			char *s;
			if (domain->key != NULL) {
				yyerror("duplicate key");
				YYERROR;
			}
			if ((s = strdup(yyvsp[-1].v.string)) == NULL)
				err(EXIT_FAILURE, "strdup");
			if (!conf_check_file(s)) {
				free(s);
				YYERROR;
			}
			if ((conf_new_keyfile(conf, s)) == NULL) {
				free(s);
				yyerror("domain key file already used");
				YYERROR;
			}
			domain->key = s;
			domain->keytype = yyvsp[0].v.number;
		}
break;
case 35:
#line 325 "parse.y"
{
			char *s;
			if (domain->cert != NULL) {
				yyerror("duplicate cert");
				YYERROR;
			}
			if ((s = strdup(yyvsp[0].v.string)) == NULL)
				err(EXIT_FAILURE, "strdup");
			if (s[0] != '/') {
				free(s);
				yyerror("not an absolute path");
				YYERROR;
			}
			if ((conf_new_keyfile(conf, s)) == NULL) {
				free(s);
				yyerror("domain cert file already used");
				YYERROR;
			}
			domain->cert = s;
		}
break;
case 36:
#line 345 "parse.y"
{
			char *s;
			if (domain->chain != NULL) {
				yyerror("duplicate chain");
				YYERROR;
			}
			if ((s = strdup(yyvsp[0].v.string)) == NULL)
				err(EXIT_FAILURE, "strdup");
			if ((conf_new_keyfile(conf, s)) == NULL) {
				free(s);
				yyerror("domain chain file already used");
				YYERROR;
			}
			domain->chain = s;
		}
break;
case 37:
#line 360 "parse.y"
{
			char *s;
			if (domain->fullchain != NULL) {
				yyerror("duplicate full chain");
				YYERROR;
			}
			if ((s = strdup(yyvsp[0].v.string)) == NULL)
				err(EXIT_FAILURE, "strdup");
			if ((conf_new_keyfile(conf, s)) == NULL) {
				free(s);
				yyerror("domain full chain file already used");
				YYERROR;
			}
			domain->fullchain = s;
		}
break;
case 38:
#line 375 "parse.y"
{
			char *s;
			if (domain->auth != NULL) {
				yyerror("duplicate sign with");
				YYERROR;
			}
			if ((s = strdup(yyvsp[0].v.string)) == NULL)
				err(EXIT_FAILURE, "strdup");
			if (authority_find(conf, s) == NULL) {
				yyerror("sign with: unknown authority");
				free(s);
				YYERROR;
			}
			domain->auth = s;
		}
break;
case 39:
#line 390 "parse.y"
{
			char *s;
			if (domain->challengedir != NULL) {
				yyerror("duplicate challengedir");
				YYERROR;
			}
			if ((s = strdup(yyvsp[0].v.string)) == NULL)
				err(EXIT_FAILURE, "strdup");
			domain->challengedir = s;
		}
break;
case 42:
#line 406 "parse.y"
{
			char			*s;
			struct altname_c	*ac;
			if (!domain_valid(yyvsp[0].v.string)) {
				yyerror("bad domain syntax");
				YYERROR;
			}
			if ((ac = calloc(1, sizeof(struct altname_c))) == NULL)
				err(EXIT_FAILURE, "calloc");
			if ((s = strdup(yyvsp[0].v.string)) == NULL) {
				free(ac);
				err(EXIT_FAILURE, "strdup");
			}
			ac->domain = s;
			TAILQ_INSERT_TAIL(&domain->altname_list, ac, entry);
			domain->altname_count++;
			/*
			 * XXX we could check if altname is duplicate
			 * or identical to domain->domain
			*/
		}
break;
#line 1554 "parse.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return (1);
yyaccept:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return (0);
}

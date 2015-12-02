/*
  pia.c

  Calculate the area of intersection of a pair of polygons specifed
  as and array of pairs of floats representing the polygon vertices.
  The return value is a float and accurate to float precision.
  Degenerate cases are avoided by working in exact arthmetic and
  "fudging" the exact coordinates to an extent smaller than float
  precision.

  -------

  This code is a derived from Norman Hardy's aip.c which can be
  downoaded from

    http://www.cap-lore.com/MathPhys/IP/

  which is clearly a master-work of algorithmics and coding. My original
  intention was simply to convert it ANSI C, but I found that I needed
  to reformat and "dumb it down" just so that I could understand what
  it was that I was converting.

  The main changes are:

  - renamed to pia.c to avoid any confusion with the original
  - added header file
  - renamed types *_t
  - pulled all nested function out, passing required
    variables by reference as needed
  - added lots of unnecessary parentheses to emphasis
    precedence
  - removed scope restraining blocks
  - lots of stylistic changes
  - some assumptions about the promotion of floats to doubles for
    intermediate calculation have been made explicit (these assumptions
    are true for gcc on x86, but are not guaranteed by standard and are
    false for gcc on amd64)

  This is now C99 (according to gcc -Wall -std=c99)

  --------

  J.J. Green 2010, 2015
*/

#include "pia.h"

#include <stdio.h>
#include <stddef.h>
#include <float.h>

typedef struct
{
  point_t min, max;
} box_t;

typedef long long hp_t;

typedef struct
{
  long x, y;
} ipoint_t;

typedef struct
{
  long mn, mx;
} rng_t;

typedef struct
{
  ipoint_t ip;
  rng_t rx, ry;
  short in;
} vertex_t;

static void bd(float *X, float y)
{
  *X = (*X<y ? *X : y);
}

static void bu(float *X, float y)
{
  *X = (*X>y ? *X : y);
}

static void range(point_t *x, int c, box_t *B)
{
  while (c--)
    {
      bd(&(B->min.x), x[c].x);
      bu(&(B->max.x), x[c].x);
      bd(&(B->min.y), x[c].y);
      bu(&(B->max.y), x[c].y);
    }
}

static hp_t area(ipoint_t a, ipoint_t p, ipoint_t q)
{
  return
    (hp_t)p.x*q.y -
    (hp_t)p.y*q.x +
    (hp_t)a.x*(p.y - q.y) +
    (hp_t)a.y*(q.x - p.x);
}

/* a*b + c calculated using doubles */

static float dma(float a, float b, float c)
{
  return (double)a * (double)b + (double)c;
}

/*
  The allowing this function to be inlined cause a unit-test
  failure (the 'cross' test) for gcc 4.4.7 on x86 Linux, I'm
  not sure why, possibly a gcc bug?  According to Torvalds
  (2008)

    older versions of gcc (and by "older" I do not mean "really
    ancient" or "deprecated", but stuff that is still in use) are
    known to be total and utter crap when it comes to inlining

  http://yarchive.net/comp/linux/gcc_inline.html
*/

__attribute__ ((noinline))
static void fit(point_t *x, int cx,
		vertex_t *ix,
		int fudge,
		float sclx,
		float scly,
		float mid,
		box_t B)
{
  int c;

  c = cx;

  while (c--)
    {
      ix[c].ip.x =
	((long)dma(x[c].x - B.min.x, sclx, -mid) & ~7) |
	fudge |
	(c & 1);

      ix[c].ip.y =
	((long)dma(x[c].y - B.min.y, scly, -mid) & ~7) |
	fudge;
    }

  ix[0].ip.y += (cx & 1);
  ix[cx] = ix[0];

  c = cx;

  while (c--)
    {
      ix[c].rx =
	(ix[c].ip.x < ix[c+1].ip.x) ?
	((rng_t){ix[c].ip.x, ix[c+1].ip.x}) :
	((rng_t){ix[c+1].ip.x, ix[c].ip.x});

      ix[c].ry =
	(ix[c].ip.y < ix[c+1].ip.y) ?
	((rng_t){ix[c].ip.y, ix[c+1].ip.y}) :
	((rng_t){ix[c+1].ip.y, ix[c].ip.y});

      ix[c].in = 0;
    }
}

static void contrib(ipoint_t f, ipoint_t t, short w, hp_t *s)
{
  *s += (hp_t)w*(t.x - f.x)*(t.y + f.y)/2;
}

static int ovl(rng_t p, rng_t q)
{
  return (p.mn < q.mx) && (q.mn < p.mx);
}

void cross(vertex_t *a,
	   vertex_t *b,
	   vertex_t *c,
	   vertex_t *d,
	   double a1,
	   double a2,
	   double a3,
	   double a4,
	   hp_t *s)
{
  float
    r1 = a1/((float)a1 + a2),
    r2 = a3/((float)a3 + a4);

  ipoint_t pA = {a->ip.x + r1*(b->ip.x - a->ip.x),
		 a->ip.y + r1*(b->ip.y - a->ip.y)};
  contrib(pA, b->ip, 1, s);

  ipoint_t pB = {c->ip.x + r2*(d->ip.x - c->ip.x),
		 c->ip.y + r2*(d->ip.y - c->ip.y)};
  contrib(d->ip, pB, 1, s);

  ++a->in;
  --c->in;
}

static void inness(vertex_t *P, int cP, vertex_t * Q, int cQ, hp_t *s)
{
  int S = 0, c = cQ;
  ipoint_t p = P[0].ip;

  while (c--)
    {
      if ((Q[c].rx.mn < p.x) && (p.x < Q[c].rx.mx))
	{
	  int sgn = 0 < area(p, Q[c].ip, Q[c+1].ip);

	  S += ((sgn != (Q[c].ip.x < Q[c+1].ip.x)) ? 0 : (sgn ? -1 : 1));
	}
    }

  int j;

  for (j=0 ; j<cP ; ++j)
    {
      if (S)
	contrib(P[j].ip, P[j+1].ip, S, s);
      S += P[j].in;
    }
}

extern float pia_area(point_t* a, size_t na,
			    point_t* b, size_t nb)
{
  vertex_t ipa[na+1], ipb[nb+1];
  double ascale;
  box_t B = {{ FLT_MAX,  FLT_MAX},
	     {-FLT_MAX, -FLT_MAX}};

  if ( (na < 3) || (nb < 3) ) return 0.0;

  range(a, na, &B);
  range(b, nb, &B);

  const float
    gamut = 500000000.0,
    mid   = gamut/2.0;
  float
    rngx = B.max.x - B.min.x,
    sclx = gamut/rngx,
    rngy = B.max.y - B.min.y,
    scly = gamut/rngy;

  fit(a, na, ipa, 0, sclx, scly, mid, B);
  fit(b, nb, ipb, 2, sclx, scly, mid, B);

  ascale = (double)sclx * (double)scly;

  hp_t s = 0; int j, k;

  for (j=0 ; j<na ; ++j)
    {
      for (k=0 ; k<nb ; ++k)
	{
	  if ( ovl(ipa[j].rx, ipb[k].rx) && ovl(ipa[j].ry, ipb[k].ry) )
	    {
	      hp_t
		a1 = -area(ipa[j].ip, ipb[k].ip, ipb[k+1].ip),
		a2 =  area(ipa[j+1].ip, ipb[k].ip, ipb[k+1].ip);

	      int o = (a1<0);

	      if (o == (a2<0))
		{
		  hp_t
		    a3 = area(ipb[k].ip, ipa[j].ip, ipa[j+1].ip),
		    a4 = -area(ipb[k+1].ip, ipa[j].ip, ipa[j+1].ip);

		  if ((a3<0) == (a4<0))
		    {
		      if(o)
			cross(ipa+j, ipa+j+1, ipb+k, ipb+k+1, a1, a2, a3, a4, &s);
		      else
			cross(ipb+k, ipb+k+1, ipa+j, ipa+j+1, a3, a4, a1, a2, &s);
		    }
		}
	    }
	}
    }

  inness(ipa, na, ipb, nb, &s);
  inness(ipb, nb, ipa, na, &s);

  return s/ascale;
}

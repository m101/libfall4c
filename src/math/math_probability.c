/***************************************************************************
 *            probabilite.c
 *
 *  Sun Apr 29 18:16:31 2007
 *  Copyright  2007  User
 *  Email
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdlib.h>
#include <stdio.h>

#include "math/math_probability.h"
#include <math.h>


//Prend en compte les factorielle positive et negative
unsigned long factorielleIter(unsigned long chiffre)
{
    long factoriel = chiffre;
    size_t i = 0;

    if (chiffre > 0)
    {
        for (i = 1; i < chiffre; i++)
        {
            factoriel = factoriel * i;
        }
    }
    else if (chiffre < 0)
    {
        exit(EXIT_FAILURE);
    }

    return factoriel;
}



// accu doit être égal à 1 au début si on veut avoir n!
// sinon on aura comme resultat n! * accu
// n et accu appartiennent à l'ensemble des Naturels
unsigned long factorielle (unsigned long n, unsigned long accu)
{
    if (n < 0)
        exit (EXIT_FAILURE);
    if (n == 1)
        return accu;
    else if (n == 0)
        return 1;

    if (accu == 0)
        accu = 1;

    return factorielle (n - 1, n * accu);
}

unsigned long nCr(unsigned long n, unsigned long p)
{
    long nombreCombinaison = 0;

    if ( (n >= 0) && (p >= 0) )
        nombreCombinaison = factorielle(n, 1)/(factorielle(p, 1) * factorielle(n-p, 1));
    else
        printf("Input error : only positive numbers allowed for nCr\n");

    return nombreCombinaison;
}

double loiBinomiale(long n, long k, double p)
{
    double proba = 0;

    proba = nCr(n, k) * pow(p, k) * pow(1 - p, n - k);

    return proba;
}

/// TODO (kurapix#5#): Loi exponentielle

#ifndef _DESSIN_H_
#define _DESSIN_H_

/** fichier : nom de fichier d'extension .png
 * img : tableau bidimensionnel de booléens de dimensions hxl
 * sortie : image sauvegardée dans le fichier
 */

void sauvegarder(const char *fichier, bool **img, int h, int l);

void point_suivant(double x, double y, double xc, double yc, double* x1, double* y2);

bool suite_bornee(double xc, double yc);

bool** mandelbrot(double l, double h);


#endif

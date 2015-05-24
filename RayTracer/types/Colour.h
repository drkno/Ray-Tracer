/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The color class
*  A simple colour class with a set of operations including
*    phong lighting.
-------------------------------------------------------------*/

#ifndef H_COLOR
#define H_COLOR

class Colour
{

public:
    float r, g, b;
	static const Colour WHITE;
	static const Colour BLACK;
	static const Colour RED;
	static const Colour GREEN;
	static const Colour BLUE;
	static const Colour GRAY;

    Colour()
		: r(1), g(1), b(1)
	{}	;
	
    Colour(float rCol, float gCol, float bCol)
		: r(rCol), g(gCol), b(bCol)
	{} ;

    void scaleColor(float scaleFactor);

    void combineColor(Colour col);

    void combineColor(Colour col, float scaleFactor);

	Colour phongLight(Colour ambientCol, float diffuseTerm,  float specularTerm);
};
#endif

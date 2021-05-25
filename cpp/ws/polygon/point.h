#ifndef Point_OL70 /*header guard*/
#define Point_OL70

/*******************************************************************************
* The functions in this file handle a Point
* structure. It will be denoted as Point.
*
*
* Written by: Roy Yablonka, OL-70
* Last update: 17:00 , 15.10.2019
*******************************************************************************/

struct Point
{
	enum ParenthesesType { ROUND, SQUARE, CURLY, ANGULAR};

	explicit Point();
	explicit Point(int x_, int y_);

	int GetX();
	int GetY();
	Point &AdjustBy(int dx, int dy);
	Point &AdjustBy(const Point &point);
	bool IsEqual(const Point & point) const;
	float Length() const;
	void Print(char open, char close) const;
	void Print(ParenthesesType pt = ROUND) const;

private:
	int x;
	int y;
	mutable float length;
};

// float g_totalLength = 0;

Point Add(Point first, Point second, int max);

#endif  /*Point_OL70*/

#ifndef EDS
#define EDS

inline float EDistanceSquare(const int rows, const int cols, int r, int c)
{
	return (float(r) - float(rows)/2.0) * (float(r) - float(rows)/2.0) 
	+ (float(c) - float(cols)/2.0)*(float(c) - float(cols)/2.0);
}

#endif

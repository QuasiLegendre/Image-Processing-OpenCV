#ifndef EDS
#define EDS
template<typename _F, typename _CI, typename _I>
inline _F EDistanceSquare(_CI rows, _CI cols, _I r, _I c)
{
	return (_F(r) - _F(rows)/2.0) * (_F(r) - _F(rows)/2.0) 
	+ (_F(c) - _F(cols)/2.0)*(_F(c) - _F(cols)/2.0);
}

#endif

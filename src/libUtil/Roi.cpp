/*
 *------------------------------------------------------------------------
 * abc.h
 *
 * No  any Corporation or client funds were used to develop this code.
 * But the numerical receip's LU decomposition algorithm is adopted.
 *
 * Copyright (c) 2022 Shunguang Wu
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT SHALL THE AUTHOR OR DISTRIBUTOR BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 *-------------------------------------------------------------------------
 */
#include "Roi.h"
using namespace std;
using namespace app;

Roi :: Roi():
m_xo (-1), m_yo (-1), m_w (0), m_h (0), m_xb(-1), m_yb(-1)
{
}

Roi :: Roi( const int xo, const int yo, const int w, const int h )
{
	setRoi(xo, yo, w, h);
}

Roi :: Roi( const float xo, const float yo, const float w, const float h )
{
	setRoi(xo, yo, w, h);
}

Roi :: Roi( const Roi &p ):
m_xo	( p.m_xo ), 
m_yo	( p.m_yo ), 
m_w		( p.m_w ), 
m_h		( p.m_h ),
m_xb	( p.m_xb ), 
m_yb	( p.m_yb )
{
}

void Roi :: setRoi( const int &xo, const int &yo, const int &w, const int &h )
{
	m_xo	= static_cast<float>(xo);
	m_yo	= static_cast<float>(yo);
	m_w		= static_cast<float>(w);
	m_h		= static_cast<float>(h);
	m_xb	= static_cast<float>(xo + w - 1);
	m_yb	= static_cast<float>(yo + h - 1);
}

void Roi :: setRoi( const float &xo, const float &yo, const float &w, const float &h )
{
	m_xo	= xo;
	m_yo	= yo;
	m_w		= w;
	m_h		= h;
	m_xb	= xo + w - 1.0f;
	m_yb	= yo + h - 1.0f;
}

void Roi :: setByCenter( const float &xc, const float &yc, const float &w, const float &h)
{
	setRoi( xc-0.5f*w, yc-0.5f*h, w, h );
}

void Roi :: setByIntCenter( const int &xc, const int &yc, const int &w, const int &h)
{
#if 0
	assert( w%2==1  &&  h%2 == 1 );
#endif

	setRoi( xc - ( (w+1)>>1 ) + 1,  yc - ( (h+1)>>1 ) + 1,  w,  h );
}

Roi& Roi :: operator =( const Roi& p)
{
	if ( &p != this ){
		m_xo	= p.m_xo;
		m_yo	= p.m_yo;
		m_w		= p.m_w;
		m_h		= p.m_h;
		m_xb	= p.m_xb;
		m_yb	= p.m_yb;
	}
	return *this;
}

void Roi :: getIntParams(int &xo, int &yo, int &xb, int &yb, int &w, int &h, const int imgW, const int imgH) const
{
	xo = getInt_xo();
	yo = getInt_yo();
	xb = getInt_xb();
	yb = getInt_yb();
	w  = xb-xo+1;
	h  = yb-yo+1;

	if (imgW>0 && imgH>0){

		if ( xo < 0 )			{xo = 0;   }
		else if ( xo >= imgW )	{xo = imgW-1; }

		if ( xb < 0 )			{xb = 0;}
		else if ( xb >= imgW )	{xb = imgW-1;}


		if ( yo < 0 )			{yo = 0;	}
		else if ( yo >= imgH )	{yo = imgH-1;	}

		if ( yb < 0 )			{yb = 0;	}
		else if ( yb >= imgH )	{yb = imgH-1;	}

		w = xb - xo + 1;
		h = yb - yo + 1;
	}
}

Roi Roi::getRoi(const int L) const
{
	Roi x( *this );
	for (int i = 0; i < L; ++i) {
		x.oneLevelUp();
	}
	return x;
}

void Roi :: print ( const char *str) const
{
	if( str!=NULL ){
		printf("%s\n", str);
	}
	printf("(xo,yo,xb,yb), (w,h), (xc,yc) = (%.1f,%.1f,%.1f,%.1f), (%.1f, %.1f), (%.1f, %.1f)\n", 
		m_xo, m_yo, m_xb, m_yb, m_w, m_h, getCenterX(), getCenterY() );
}

//---------------------------------------------------
//force roi inside the image via change the roi size
//[w,h]: frm image size
//return:  true if roi is trimed, false otherwise 
//---------------------------------------------------
bool Roi :: trimSize( const int w, const int h )
{
	bool trimed = false;

	if ( m_xo < 0 )			{m_xo = 0;		trimed = true;}
	else if ( m_xo > w-1 )	{m_xo = w-1;	trimed = true;}

	if ( m_xb < 0 )			{m_xb = 0;		trimed = true;}
	else if ( m_xb > w-1 )	{m_xb = w-1;	trimed = true;}


	if ( m_yo < 0 )			{m_yo = 0;		trimed = true;}
	else if ( m_yo > h-1 )	{m_yo = h-1;	trimed = true;}

	if ( m_yb < 0 )			{m_yb = 0;		trimed = true;}
	else if ( m_yb > h-1 )	{m_yb = h-1;	trimed = true;}

	m_xo = (int) (m_xo);
	m_yo = (int) (m_yo);
	m_xb = (int) (m_xb);
	m_yb = (int) (m_yb);
	m_w = m_xb - m_xo + 1 ;
	m_h = m_yb - m_yo + 1;

	return trimed;
}

//---------------------------------------------------
//force roi inside the image via change the roi location
//[w,h]: frm image size
//return:  true if roi is trimed, false otherwise 
//---------------------------------------------------
bool Roi :: trimLocation( const int w, const int h )
{
	bool trimed = false;
	
	if( m_w >= w ){
		m_xo = 0;
		m_w = w;
		trimed = true;
	}
	else if ( m_xo < 0 ){
		m_xo = 0;
		trimed = true;
	}
	else if ( m_xo > w-m_w ){
		m_xo = w-m_w;
		trimed = true;
	}
	

	if( m_h >= h ){
		m_yo = 0;
		m_h = h;
		trimed = true;
	}
	if ( m_yo < 0 ){
		m_yo = 0;		
		trimed = true;
	}
	else if ( m_yo > h-m_h ){
		m_yo = h-m_h;	
		trimed = true;
	}

	if ( trimed ){
		m_xb = m_xo + m_w - 1;
		m_yb = m_yo + m_h - 1;
	}

	return trimed;
}

bool Roi::trimLocation_wo_chg_sz( const int imgW, const int imgH )
{
	if( imgW< m_w || imgH<m_h ){
		return false;
	}

	bool xtrimed = true;
	if ( m_xo < 0 ){
		m_xo = 0;
	}
	else if ( m_xo > imgW-m_w ){
		m_xo = imgW-m_w;
	}
	else{
		xtrimed = false;
	}


	bool ytrimed = true;
	if ( m_yo < 0 ){
		m_yo = 0;		
	}
	else if ( m_yo > imgH - m_h ){
		m_yo = imgH-m_h;	
	}
	else{
		ytrimed = false;
	}

	if ( xtrimed ){
		m_xb = m_xo + m_w - 1;
	}
	if ( ytrimed ){
		m_yb = m_yo + m_h - 1;
	}
	return true;
}

void Roi :: oneLevelUp()
{
	setRoi( 0.5f*m_xo, 0.5f*m_yo, 0.5f*m_w, 0.5f*m_h);
}

void Roi :: oneLevelDown()
{
	setRoi( 2.0f*m_xo, 2.0f*m_yo, 2.0f*m_w, 2.0f*m_h);
}

void Roi :: oneLevelUpOrDown( const int &step, const float &newW, const float &newH )
{

#if _DEBUG
	assert( step == 1 || step==-1 );
#endif

	float xo(m_xo),yo(m_yo);
	if( step == 1 ){
		xo = 0.5f*getCenterX();
		yo = 0.5f*getCenterY();
	}
	else{
		xo = 2*getCenterX();
		yo = 2*getCenterY();
	}

	xo -= 0.5*newW;
	yo -= 0.5*newH;

	setRoi(xo, yo, newW, newH);
}

void Roi :: forceSizeOdd()
{
	int xc = getInt_xc();
	int yc = getInt_yc();

	int w = getInt_w();
	if( w%2 == 0 ){
		++w;
	}

	int h = getInt_h();
	if( h%2 == 0 ){
		++h;
	}
	
	setByCenter(xc, yc, w, h );
}

void Roi :: forceSizeOdd2()
{
	int xc = getInt_xc();
	int yc = getInt_yc();

	int w = getInt_w();
	if( w%2 == 0 ){
		--w;
	}

	int h = getInt_h();
	if( h%2 == 0 ){
		--h;
	}
	
	setByCenter(xc, yc, w, h );
}

void  Roi::fromString(const std::string &s)
{
	sscanf_s( s.c_str(), "xo=%f,yo=%f,w=%f,h=%f", &m_xo, &m_yo, &m_w ,&m_h);
	m_xb = m_xo + m_w - 1;
	m_yb = m_yo + m_h - 1;
}

std::string   Roi::toString()
{
	char buf[64];
	snprintf(buf, 64, "xo=%.2f,yo=%.2f,w=%.2f,h=%.2f", m_xo, m_yo, m_w, m_h);

	return string(buf);
}

std::string   Roi::toString2()
{
	char buf[64];
	snprintf(buf, 64, "%d,%d,%d,%d", myround(m_xo), myround(m_yo), myround(m_w), myround(m_h) );

	return string(buf);
}

// any part of roi is out of current frame
bool app::isRoiOutOfImg( const Roi &roi, const int &frmImgW, const int &frmImgH )
{
	int roihw = roi.getInt_w()/2;
	int roihh = roi.getInt_h()/2;

	if ( roi.getCenterX()<roihw || roi.getCenterX()>frmImgW-roihw || 
		 roi.getCenterY()<roihh || roi.getCenterY()>frmImgH-roihh ){
		return true;
	}
	else if( roi.m_xo<1 || roi.m_yo<1 || roi.m_xb>frmImgW-1 || roi.m_yb>frmImgH-1){
		return true;
	}
	else{
		return false;
	}
}


bool app::isRoi1InRoi2( const Roi &roi1, const Roi &roi2 )
{
	if( roi1.m_xo >=  roi2.m_xo  && roi1.m_yo >=  roi2.m_yo && roi1.m_xb <=  roi2.m_xb  && roi1.m_yb <=  roi2.m_yb ) 
		return true;
	else
		return false;
}



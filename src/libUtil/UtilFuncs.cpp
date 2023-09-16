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

#include "UtilFuncs.h"

using namespace std;

string app::num_to_string( const bool x, const std::string &msg )
{
	string s("true");
	if ( !x ){
		s = "false";
	}

	return msg+s;
}

std::string  app::num_to_string( const uint8_t x,	const std::string &msg )
{
	ostringstream convert;   // stream used for the conversion
	convert << (int)x;		     // insert the textual representation of 'x' in the characters in the stream
	return msg+convert.str();	
}

std::string  app:: num_to_string( const uint16_t x, const int len, const std::string &msg )
{
	ostringstream ss;
	ss << std::setw(len) << std::setfill('0') << x;
	return msg+ss.str();
}

string app::num_to_string( const uint32_t x, const int len,  const std::string &msg )
{
	ostringstream ss;
	ss << std::setw(len) << std::setfill('0') << x;
	return msg+ss.str();	
}

string app::num_to_string( const uint64_t x, const int len, const std::string &msg )
{
	ostringstream ss;
	ss << std::setw(len) << std::setfill('0') << x;
	return msg + ss.str();
}

string app::num_to_string( const int32_t x, const int len, const std::string &msg )
{
	ostringstream ss;
	ss << std::setw(len) << std::setfill('0') << x;
	return msg + ss.str();
}

std::string app::num_to_string(const int32_t x, const std::string &msg)
{
	ostringstream convert;
	convert << x;
	return msg + convert.str();
}

std::string app::num_to_string(const uint16_t x, const std::string &msg)
{
	ostringstream convert;
	convert << x;
	return msg + convert.str();
}
std::string app::num_to_string(const uint32_t x, const std::string &msg)
{
	ostringstream convert;
	convert << x;
	return msg + convert.str();
}
std::string app::num_to_string(const uint64_t x, const std::string &msg)
{
	ostringstream convert;
	convert << x;
	return msg + convert.str();
}

string app::num_to_string( const float x, const std::string &msg, const int precision )
{
	ostringstream convert;
	convert <<  std::fixed << std::setprecision(precision) <<  x;
	return msg+convert.str();	
}

string app::num_to_string( const double x, const std::string &msg, const int precision )
{
	ostringstream convert;
	convert << std::fixed << std::setprecision(precision) << x;
	return msg+convert.str();	
}

std::string app::vec_to_string( const std::vector<std::string> &v, const std::string &msg )
{
	ostringstream convert;   // stream used for the conversion
	convert << msg << endl;		     
	convert << "Total Items" << v.size() << endl;
	vector<string>::const_iterator it=v.begin();
	for (; it!=v.end(); ++it ){
		convert << *it << endl;		     
	}
	return msg+convert.str();	
}

bool app::string_in_vector( const std::string &s, const std::vector<std::string> &v  )
{
	vector<string>::const_iterator it=v.begin();
	for (; it!=v.end(); ++it ){
		if ( 0 == s.compare( *it ) ){
			return true;
		}
	}
	return false;
}

int app::string_in_vector_relax( const std::string &s, const std::vector<std::string> &v  )
{
	vector<string>::const_iterator it=v.begin();
	int i=0;
	for (; it!=v.end(); ++it, ++i ){
		if ( string::npos != (*it).find( s ) ){
			return i;
		}
	}
	return -1;
}

bool app::string_to_bool( const std::string &in )
{
	string s(in);
	for ( uint32_t i=0; i<s.size(); ++i ){
		s[i] = std::toupper( s[i] );
	}

	if ( 0==s.compare("YES") || 0==s.compare("Y") ){
		return true;
	}
	else if ( 0==s.compare("TRUE") || 0==s.compare("T") ){
		return true;
	}
	else if( 0==s.compare("1") ){
		return true;
	}
	else{
		return false;
	}
}

uint64_t	app::string_to_uint64( const std::string &s )
{
	uint64_t x;
	stringstream strm(s);

	strm >> x;

	return x;
}

size_t app::string_to_vector( vector<string> &v, const string &s, const string &key, const bool keepKey )
{

	v.clear();

	size_t L = key.size();
	size_t pos = 0;
	std::string::size_type found = s.find(key, pos);
	while( found !=std::string::npos ){
		size_t len = found - pos;
		if( keepKey ){
			len += L;
		}
		if( len>0 ){
			v.push_back( s.substr( pos, len) );
		}

		pos = found + L;
		found = s.find(key, pos);
	}
	if( pos <= s.size()-1 ){
		v.push_back( s.substr( pos ) );
	}

	return v.size();
}

std::string	app :: vector_to_string( const std::vector<std::string> &v, const std::string &seperateKey )
{
	if ( v.size()==0 ){
		return "";
	}

	string s=v[0];
	for( uint32_t i=1; i<v.size(); ++i ){
		s += (seperateKey + v[i]);
	}

	return s;
}

std::string app::vector_to_string(const std::vector<uint8_t>& v) 
{
	std::string s;
	for ( const uint8_t x : v ) {
		s.push_back( (char)x);
	}
	return s;
}

void app :: string_trim( string &x, const char ch )
{
	if ( x.empty() ){
		return;
	}

	//ersase end
	string::iterator it = x.end();
	while( *(--it) == ch ){
		x.erase(it);
		if( x.empty() ){
			return;
		}
		it = x.end();
	}

	//erase begin
	it = x.begin();
	while( *it==ch ){
		x.erase( it );
		if( x.empty() ){
			return;
		}
		it = x.begin();
	}

}


//---------------------------------
/*
s = "[$SYSTEMNAME]> show statworpsutbl
WORP SU Statistics Table
------------------------
Channel Bandwidth               :                 10 MHz
SU MAC Address                  :               00:20:A6:C1:5F:C8
SU Local Tx Rate                :                 6 Mbps
SU Remote Tx Rate               :                 6 Mbps
SU Average Local Signal         :                    -33
SU Average Local Noise          :                    -89
SU Average Remote Signal        :                    -35
SU Average Remote Noise         :                    -92
SU Distance                     :               100 meters"
*/
//------------------------------------------------------------------
// call string_parse(s, "Channel Bandwidth" ) return "10 MHz"

std::string app::string_parse( const std::string &x, const std::string &key )
{
	string y;

	size_t found = x.find( key );
	if ( found == string::npos ){
		return "";
	}

	y = x.substr( found+key.size() );

	found = y.find( ':' );
	y = y.substr( found+1 );
	found = y.find( '\r' );
	y = y.substr(0, found );
	
	string_trim(y, ' ');
	string_trim(y, '\t');
	string_trim(y, '\n');
	string_trim(y, ' ');

	return y;
}
//        01234567890123456    
// mac = "01-23-45-67-89-ab" or 01:23:45:67:89:ab
std::string app::string_find_mac( const std::string &x, const char &seperationKey )
{
	int L = (int)(x.size());
	for( int i=0; i<=L-17; ++i ){
		if( x[i+2]==seperationKey && x[i+5]==seperationKey && x[i+8]==seperationKey && x[i+11]==seperationKey && x[i+14]==seperationKey ){
			return x.substr(i, 17 );
		}
	}
	return "";
}

//remove the beg and end chars if any of them are in $keys$
void app:: string_trim( string &x, const std::vector<char> &keys )
{
	if ( x.empty() ){
		return;
	}
	size_t n=keys.size();

	//ersase end
	string::iterator it = x.end();
	while( 1 ){
		char ch = *(--it);
		bool found=false;
		for (uint32_t i=0; i<n; ++i){
			if ( ch==keys[i] ){
				found=true;
				break;
			}
		}

		if( !found ){
			break;
		}
		else{
			x.erase(it);
			if( x.empty() ){
				return;
			}
			it = x.end();
		}
	}

	//erase begin
	it = x.begin();
	while( 1 ){
		char ch = *it;
		bool found=false;
		for (uint32_t i=0; i<n; ++i){
			if ( ch==keys[i] ){
				found=true;
				break;
			}
		}

		if( !found ){
			break;
		}
		else{
			x.erase( it );
			if( x.empty() ){
				return;
			}
			it = x.begin();
		}
	}

}

void	 app:: string_find_n_replace( std::string &x, const char chFind, const char chRaplace )
{
	for(uint32_t i=0; i<x.size(); ++i){
		if ( x[i]==chFind ) {
			x[i] = chRaplace;
		}
	}
}


void app::vstr_read_txt_file( std::vector<std::string> &vLines, const std::string &fileName, const char commentChar )
{

	std::string line;
	std::ifstream myfile( fileName );

	while (std::getline(myfile, line)) {
		app::string_trim( line, ' ' );

		if( line.empty() ){
			continue;
		}
		if ( line[0]==commentChar ){
			continue;
		}

		vLines.push_back(line);	
	}
}

void app:: vstr_select_util( std::vector<std::string> &retLines, const std::vector<std::string> &vAllLines, const std::string &startKey, const std::string &stopKey )
{
	retLines.clear();
	size_t n =vAllLines.size();
	for (size_t i=0; i<n; ++i ){
		const string &line = vAllLines[i];
		if( string::npos == line.find( startKey ) ){
			continue;
		}

		size_t j=i+1;
		while(j<n){
			const string &nextLine = vAllLines[j];
			if( string::npos == nextLine.find(stopKey) ){
				retLines.push_back( nextLine );
			}
			else{
				return;
			}
			++j;
		}
	}
}

//---------------------------------------------------------------
//given vector of lines such as:
//
//ipv4=10.0.4.101
//macWired=ba:wi:cc:dd:ee:01
//macWireless=ba:wl:cc:dd:ee:01
//
//query value (RHS) from key (LHS)
//
//example: vstr_find_value("ipv4") will return "10.0.4.101"
//---------------------------------------------------------------

std::string app::vstr_find_value( const std::vector<std::string> &vLines, const std::string &key )
{
	std::vector<std::string>::const_iterator it=vLines.begin();
	std::vector<std::string> kv;
	for ( ; it!=vLines.end(); ++it ){
		app::string_to_vector( kv, *it, "=", false );
		if ( kv.size()<2 ){
			continue;
		}
		if ( 0 == key.compare( kv[0] ) ){
			return kv[1];
		}
	}

	return "";
}

std::string app::getPrettyTimeStampNow(const bool dayTimeOnly)
 {
	return getPrettyTimeStampNow(APP_TIME_CURRENT_MS, dayTimeOnly);
 }

std::string app::getPrettyTimeStampNow(const APP_TIME_MS t, const bool dayTimeOnly)
{
	return "todo";
#if 0
	string stimeStamp = to_simple_string(t);  //[YYYY-mmm-DD HH:MM:SS.fffffffff]
	app::string_find_n_replace(stimeStamp, ' ', '-');
	app::string_find_n_replace(stimeStamp, ':', '-');
	app::string_find_n_replace(stimeStamp, '.', '-');

	if (dayTimeOnly){
		return stimeStamp.substr(12, 11);
	}
	return stimeStamp;
#endif
}

bool  app::isTimeOut( const APP_TIME_MS start, const uint32_t thdInMillisec )
{
	APP_TIME_MS dt_ms = APP_TIME_CURRENT_MS - start;
	if( dt_ms >= thdInMillisec ){
		return true;
	}
	else{
		return false;
	}
}

APP_TIME_MS  app::timeIntervalMillisec( APP_TIME_MS &startTime )
{
	APP_TIME_MS currTime = APP_TIME_CURRENT_MS;
	APP_TIME_MS dt = currTime - startTime;
	startTime = currTime;
	return dt;
}



int8_t app::int32_to_int8( const int32_t x )
{
	if ( x < -128 )
		return -128;
	else if( x>127 )
		return 127;
	else 
		return x;
}


void app::printByteInStr(const std::string &s, const std::string &msg)
{
	size_t n = s.size();
	printf( "%s, (n=%zd): ", msg.c_str(),n );
	for (size_t i = 0; i < n; ++i){
		printf("(%zd,%c,%d);", i, s[i], s[i]);
	}
	printf("\n");
}

//generate about <n> distinct/unique uniform distributed random number in [a,b]
void app::genUniformDistinctRands(std::vector<int> &v, const int n, const int a, const int b)
{
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distribution(a, b);

	v.resize(n);
	for (int i = 0; i < n; ++i) {
		v[i] = distribution(generator);
	}

	//v ={1,2,3,1,2,3,3,4,5,4,5,6,7}
	std::sort(v.begin(), v.end());  // 1 1 2 2 3 3 3 4 4 5 5 6 7 
	auto last = std::unique(v.begin(), v.end());
	// v now holds {1 2 3 4 5 6 7 x x x x x x}, where 'x' is indeterminate
	v.erase(last, v.end());
}


std::string  app::ipConvertNum2Str(const uint32_t ip)
{
	char buf[16];
	unsigned char bytes[4];
	bytes[0] = ip & 0xFF;
	bytes[1] = (ip >> 8) & 0xFF;
	bytes[2] = (ip >> 16) & 0xFF;
	bytes[3] = (ip >> 24) & 0xFF;
	snprintf(buf, 16, "%d.%d.%d.%d", bytes[3], bytes[2], bytes[1], bytes[0]);
	return std::string(buf);
}

uint32_t app::ipConvertStr2Num(const std::string &ip)
{
	int a, b, c, d;

	sscanf_s(ip.data(), "%d.%d.%d.%d", &a, &b, &c, &d);
	assert(a <= 255);
	assert(b <= 255);
	assert(c <= 255);
	assert(d <= 255);

	uint32_t x = d;
	x |= (c << 8);
	x |= (b << 16);
	x |= (a << 24);

	return x;
}

std::string app::appToString(const char *fmt, ...)
{
	char buffer[2048];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, 2048, fmt, args);
	va_end(args);
	return std::string(buffer);
}


//#include <unistd.h>
//#include <linux/reboot.h>
//#include <sys/reboot.h>
void app::shutdownLinuxMachine() {
    //sync();
    //reboot(LINUX_REBOOT_CMD_POWER_OFF);

	//reboot(LINUX_REBOOT_MAGIC1, 
    //       LINUX_REBOOT_MAGIC2, 
    //      LINUX_REBOOT_CMD_POWER_OFF, 0);
}

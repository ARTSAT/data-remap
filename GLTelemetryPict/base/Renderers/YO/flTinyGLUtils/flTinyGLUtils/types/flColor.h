#pragma once
#include <limits>
#include <iostream>
#include "flCommon.h"

FL_NAMESPACE_BEGIN

//----------------------------------------------------------
// Color
//----------------------------------------------------------

template<typename PixelType>
class Color_{
	public:
	
		Color_<PixelType> ();
		~Color_<PixelType> ();
		
		Color_<PixelType> (float _r, float _g, float _b, float _a = limit());
		Color_<PixelType> (const Color_<PixelType> & color);
		Color_<PixelType> (const Color_<PixelType> & color, float _a);
		Color_<PixelType> (float gray, float _a = limit());
		
		template<typename SrcType>
		Color_<PixelType> (const Color_<SrcType> & color);

		static Color_<PixelType> fromHsb (float hue, float saturation, float brightness, float alpha = limit());
		static Color_<PixelType> fromHex (int hexColor, float alpha = limit());
		
        // these are based on CSS named colors
        // http://www.w3schools.com/cssref/css_colornames.asp
    
        static const Color_<PixelType> white, gray, black, red, green, blue, cyan, magenta,
        yellow,aliceBlue,antiqueWhite,aqua,aquamarine,azure,beige,bisque,blanchedAlmond,
        blueViolet,brown,burlyWood,cadetBlue,chartreuse,chocolate,coral,cornflowerBlue,cornsilk,
        crimson,darkBlue,darkCyan,darkGoldenRod,darkGray,darkGrey,darkGreen,darkKhaki,
        darkMagenta,darkOliveGreen,darkorange,darkOrchid,darkRed,darkSalmon,darkSeaGreen,
        darkSlateBlue,darkSlateGray,darkSlateGrey,darkTurquoise,darkViolet,deepPink,
        deepSkyBlue,dimGray,dimGrey,dodgerBlue,fireBrick,floralWhite,forestGreen,fuchsia,
        gainsboro,ghostWhite,gold,goldenRod,grey,greenYellow,honeyDew,hotPink,indianRed,indigo,
        ivory,khaki,lavender,lavenderBlush,lawnGreen,lemonChiffon,lightBlue,lightCoral,
        lightCyan,lightGoldenRodYellow,lightGray,lightGrey,lightGreen,lightPink,lightSalmon,
        lightSeaGreen,lightSkyBlue,lightSlateGray,lightSlateGrey,lightSteelBlue,lightYellow,
        lime,limeGreen,linen,maroon,mediumAquaMarine,mediumBlue,mediumOrchid,mediumPurple,
        mediumSeaGreen,mediumSlateBlue,mediumSpringGreen,mediumTurquoise,mediumVioletRed,
        midnightBlue,mintCream,mistyRose,moccasin,navajoWhite,navy,oldLace,olive,oliveDrab,
        orange,orangeRed,orchid,paleGoldenRod,paleGreen,paleTurquoise,paleVioletRed,papayaWhip,
        peachPuff,peru,pink,plum,powderBlue,purple,rosyBrown,royalBlue,saddleBrown,salmon,
        sandyBrown,seaGreen,seaShell,sienna,silver,skyBlue,slateBlue,slateGray,slateGrey,snow,
        springGreen,steelBlue,tan,teal,thistle,tomato,turquoise,violet,wheat,whiteSmoke,
        yellowGreen;
    
		void set (float _r, float _g, float _b, float _a = limit());
		void set (float _gray, float _a = limit());
		void set (Color_<PixelType> const & color);

		void setHex (int hexColor, float alpha = limit());
		int getHex () const;
		
		Color_<PixelType>& clamp ();
		Color_<PixelType>& invert ();
		Color_<PixelType>& normalize ();
		Color_<PixelType>& lerp(const Color_<PixelType>& target, float amount);
		
		Color_<PixelType> getClamped () const;
		Color_<PixelType> getInverted () const;
		Color_<PixelType> getNormalized () const;
		Color_<PixelType> getLerped(const Color_<PixelType>& target, float amount) const;
		
		float getHue () const;
		float getSaturation () const;
		float getBrightness () const; // brightest component
		float getLightness () const; // average of the components
		void getHsb(float& hue, float& saturation, float& brightness) const;
		
		void setHue (float hue);
		void setSaturation (float saturation);
		void setBrightness (float brightness);
		void setHsb(float hue, float saturation, float brightness, float alpha = limit() );
		
		Color_<PixelType> & operator = (Color_<PixelType> const & color);

		template<typename SrcType>
		Color_<PixelType> & operator = (Color_<SrcType> const & color);

		Color_<PixelType> & operator = (float const & val);
		bool operator == (Color_<PixelType> const & color);
		bool operator != (Color_<PixelType> const & color);
		Color_<PixelType> operator + (Color_<PixelType> const & color) const;
		Color_<PixelType> operator + (float const & val) const;
		Color_<PixelType> & operator += (Color_<PixelType> const & color);
		Color_<PixelType> & operator += (float const & val);
		Color_<PixelType> operator - (Color_<PixelType> const & color) const;
		Color_<PixelType> operator - (float const & val) const;
		Color_<PixelType> & operator -= (Color_<PixelType> const & color);
		Color_<PixelType> & operator -= (float const & val);
		Color_<PixelType> operator * (Color_<PixelType> const & color) const;
		Color_<PixelType> operator * (float const & val) const;
		Color_<PixelType> & operator *= (Color_<PixelType> const & color);
		Color_<PixelType> & operator *= (float const & val);
		Color_<PixelType> operator / (Color_<PixelType> const & color) const;
		Color_<PixelType> operator / (float const & val) const;
		Color_<PixelType> & operator /= (Color_<PixelType> const & color);
		Color_<PixelType> & operator /= (float const & val);
		const PixelType & operator [] (int n) const;
		PixelType & operator [] (int n);
		
    friend std::ostream& operator<<(std::ostream& os, const Color_<PixelType>& color) {
			if(sizeof(PixelType) == 1) {
				os << (int) color.r << ", " << (int) color.g << ", " << (int) color.b << ", " << (int) color.a;
			} else {
				os << color.r << ", " << color.g << ", " << color.b << ", " << color.a;
			}
			return os;
		}

                friend std::istream& operator>>(std::istream& is, Color_<PixelType>& color) {
			if(sizeof(PixelType) == 1) {
				int component;
				is >> component;
				color.r = component;
				is.ignore(2);
				is >> component;
				color.g = component;
				is.ignore(2);
				is >> component;
				color.b = component;
				is.ignore(2);
				is >> component;
				color.a = component;
			}else{
				is >> color.r;
				is.ignore(2);
				is >> color.g;
				is.ignore(2);
				is >> color.b;
				is.ignore(2);
				is >> color.a;
			}
			return is;
		}
				
		static float limit();
		
		union  {
			struct {
				PixelType r, g, b, a;
			};
			PixelType v[4];
		};
		
	private:
		template<typename SrcType>
		void copyFrom(const Color_<SrcType> & mom);
};


typedef Color_<unsigned char> Color;
typedef Color_<float> FloatColor;
typedef Color_<unsigned short> ShortColor;

template<typename PixelType>
template<typename SrcType>
Color_<PixelType>::Color_(const Color_<SrcType> & mom){
	copyFrom(mom);
}

template<typename PixelType>
template<typename SrcType>
Color_<PixelType> & Color_<PixelType>::operator=(const Color_<SrcType> & mom){
	copyFrom(mom);
	return *this;
}

template<typename PixelType>
template<typename SrcType>
void Color_<PixelType>::copyFrom(const Color_<SrcType> & mom){
	const float srcMax = mom.limit();
	const float dstMax = limit();
	const float factor = dstMax / srcMax;

	if(sizeof(SrcType) == sizeof(float)) {
		// coming from float we need a special case to clamp the values
		for(int i = 0; i < 4; i++){
			v[i] = ofClamp(mom[i], 0, 1) * factor;
		}
	} else{
		// everything else is a straight scaling
		for(int i = 0; i < 4; i++){
			v[i] = mom[i] * factor;
		}
	}
}

FL_NAMESPACE_END
#ifndef _TITAN_FONT_HH
#define _TITAN_FONT_HH

#include "TitanPrerequisites.h"
#include "TitanResource.h"
#include "TitanSharedPtr.h"
#include "TitanCommon.h"
#include "TitanTexture.h"

namespace Titan
{
	class _DllExport Font : public Resource
	{
	public:
		typedef Titan::FloatRect UVRect;

		/// Information about the position and size of a glyph in a texture
		struct GlyphInfo 
		{
			uint32 codePoint;
			UVRect uvRect;
			float aspectRatio;

			GlyphInfo(uint32 id, const UVRect& rect, float aspect)
				: codePoint(id), uvRect(rect), aspectRatio(aspect)
			{

			}
		};

		typedef map<uint32, GlyphInfo>::type FontCodeMap;
		typedef std::pair<uint32, uint32> FontCodeRange;
		typedef vector<FontCodeRange>::type FontCodeRangeVec;
	public:
		Font(ResourceMgr* mgr, const String& name, ResourceHandle id, const String& group);

		~Font();

		void setSource(const String& source);

		/** Gets the source this font (either an image or a truetype font).
		*/
		const String& getSource(void) const;

		void setTrueTypeSize(float ttfSize);

		void setTrueTypeResolution(uint ttfResolution);

		float getTrueTypeSize(void) const;

		uint getTrueTypeResolution(void) const;

		int getTrueTypeMaxBearingY() const;

		inline const UVRect& getGlyphTexCoords(uint32 id) const
		{
			FontCodeMap::const_iterator i = mFontCodeMap.find(id);
			if (i != mFontCodeMap.end())
			{
				return i->second.uvRect;
			}
			else
			{
				static UVRect nullRect(0.0, 0.0, 0.0, 0.0);
				return nullRect;
			}
		}

		inline void setGlyphTexCoords(uint32 id, float u1, float v1, float u2, float v2, float textureAspect)
		{
			FontCodeMap::iterator i = mFontCodeMap.find(id);
			if (i != mFontCodeMap.end())
			{
				i->second.uvRect.left = u1;
				i->second.uvRect.top = v1;
				i->second.uvRect.right = u2;
				i->second.uvRect.bottom = v2;
				i->second.aspectRatio = textureAspect * (u2 - u1)  / (v2 - v1);
			}
			else
			{
				mFontCodeMap.insert(
					FontCodeMap::value_type(id, 
					GlyphInfo(id, UVRect(u1, v1, u2, v2), 
					textureAspect * (u2 - u1)  / (v2 - v1))));
			}

		}
		/** Gets the aspect ratio (width / height) of this character. */
		inline float getGlyphAspectRatio(uint32 id) const
		{
			FontCodeMap::const_iterator i = mFontCodeMap.find(id);
			if (i != mFontCodeMap.end())
			{
				return i->second.aspectRatio;
			}
			else
			{
				return 1.0;
			}
		}
		/** Sets the aspect ratio (width / height) of this character.
		@remarks
		You only need to call this if you're setting up a font loaded from a 
		texture manually.
		*/
		inline void setGlyphAspectRatio(uint32 id, float ratio)
		{
			FontCodeMap::iterator i = mFontCodeMap.find(id);
			if (i != mFontCodeMap.end())
			{
				i->second.aspectRatio = ratio;
			}
		}

		/** Gets the information available for a glyph corresponding to a
		given code point, or throws an exception if it doesn't exist;
		*/
		const GlyphInfo& getGlyphInfo(uint32 id) const;

		/** Adds a range of code points to the list of code point ranges to generate
		glyphs for, if this is a truetype based font.
		@remarks
		In order to save texture space, only the glyphs which are actually
		needed by the application are generated into the texture. Before this
		object is loaded you must call this method as many times as necessary
		to define the code point range that you need.
		*/
		void addCodePointRange(const FontCodeRange& range)
		{
			mFontCodeRangeVec.push_back(range);
		}

		/** Clear the list of code point ranges.
		*/
		void clearCodePointRanges()
		{
			mFontCodeRangeVec.clear();
		}
		/** Get a const reference to the list of code point ranges to be used to
		generate glyphs from a truetype font.
		*/
		const FontCodeRangeVec& getCodePointRangeList() const
		{
			return mFontCodeRangeVec;
		}

	protected:
		/// Source of the font (either an image name or a truetype font)
		String mSource;

		/// Size of the truetype font, in points
		float mTtfSize;
		/// Resolution (dpi) of truetype font
		uint mTtfResolution;
		/// Max distance to baseline of this (truetype) font
		int mTtfMaxBearingY;

		FontCodeMap	mFontCodeMap;

		TexturePtr	mFontTexture;

		FontCodeRangeVec	mFontCodeRangeVec;


		void loadImpl();

		void unloadImpl();

		void createTextureFromFont();

	};

	class _DllExport FontPtr : SharedPtr<Font>
	{
	public:
		FontPtr()
			:SharedPtr<Font>()
		{}

		explicit FontPtr(Font* font, SharedPtrFreeMethod freeMethod = SPFM_DELETE)
			: SharedPtr<Font>(font, freeMethod){}

		FontPtr(const FontPtr& rhs):SharedPtr<Font>(rhs){}

		FontPtr(const ResourcePtr& rhs): SharedPtr<Font>()
		{
			pRep = static_cast<Font*>(rhs.getPointer());
			pUseCount = rhs.useCountPointer();
			if (pUseCount)
			{
				++(*pUseCount);
			}
		}

		/// Operator used to convert a ResourcePtr to a TexturePtr
		FontPtr& operator=(const ResourcePtr& r)
		{
			if (pRep == static_cast<Font*>(r.getPointer()))
				return *this;
			release();

			pRep = static_cast<Font*>(r.getPointer());
			pUseCount = r.useCountPointer();
			if (pUseCount)
			{
				++(*pUseCount);
			}

			return *this;
		}
	};
}
#endif

#ifndef _TITAN_VIEWPORT_HH
#define _TITAN_VIEWPORT_HH

#include "TiPrerequisites.h"
#include "TiColor.h"

namespace Titan
{
	class _DllExport Viewport: public GeneralAlloc
	{
	public:
		Viewport(Camera* camera,
			RenderTarget* target,
			float left, float top,
			float width, float height,
			int ZOrder);

		~Viewport();

		void update();

		void setDimensions(float left, float top, float width, float height);

		Camera* getCamera(void) const;

		RenderTarget* getTarget() const;

		void setCamera(Camera* cam);

		bool	isAutoUpdate() const { return mIsAutoUpdate; }

		/** Gets the Z-Order of this viewport. */
		int getZOrder(void) const;
		/** Gets one of the relative dimensions of the viewport,
		a value between 0.0 and 1.0.
		*/
		float getLeft(void) const;

		/** Gets one of the relative dimensions of the viewport, a value
		between 0.0 and 1.0.
		*/
		float getTop(void) const;

		/** Gets one of the relative dimensions of the viewport, a value
		between 0.0 and 1.0.
		*/

		float getWidth(void) const;
		/** Gets one of the relative dimensions of the viewport, a value
		between 0.0 and 1.0.
		*/

		float getHeight(void) const;
		/** Gets one of the actual dimensions of the viewport, a value in
		pixels.
		*/

		int getActualLeft(void) const;
		/** Gets one of the actual dimensions of the viewport, a value in
		pixels.
		*/

		int getActualTop(void) const;
		/** Gets one of the actual dimensions of the viewport, a value in
		pixels.
		*/
		int getActualWidth(void) const;
		/** Gets one of the actual dimensions of the viewport, a value in
		pixels.
		*/

		int getActualHeight(void) const;

		uint getClearBuffers() const { return mClearBuffers; }

		void setBackgroundColor(const Color& colour);

		/** Gets the background colour.
		*/
		const Color& getBackgroundColor(void) const;

		unsigned int getNumRenderedFaces(void) const;

        /** Gets the number of rendered batches in the last update.
        */
        unsigned int getNumRenderedBatches(void) const;

	protected:
		Camera*			mCamera;
		RenderTarget*	mTarget;
		// Relative dimensions, irrespective of target dimensions (0..1)
		float			mRelLeft, mRelTop, mRelWidth, mRelHeight;
		// Actual dimensions, based on target dimensions
		int				mActLeft, mActTop, mActWidth, mActHeight;
		int				mZOrder;
		/// Background options
		Color			mBackColor;
		bool			mIsAutoUpdate;
		uint			mClearBuffers;

		void			_updateDimensions(void);

	};
}
#endif

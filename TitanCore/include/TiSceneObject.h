#ifndef _TITAN_SCENEOBJECT_HH
#define _TITAN_SCENEOBJECT_HH

#include "TiPrerequisites.h"
#include "TitanAABB.h"
#include "TiCommon.h"
#include "TiSceneMgr.h"

namespace Titan
{

	class _DllExport SceneObject : public GeneralAlloc
	{
	public:
		SceneObject(const String& name);

		SceneObject();

		virtual ~SceneObject();

		virtual const String& getType() const = 0;

		//temp method, which will be removed when we add render queue
		virtual void _updateRenderQueue(RenderQueue* queue, Camera* cam) = 0;

		virtual const AABB& getAABB() const = 0;

		const String& getName() const { return mName; }

		bool isAttached() const;

		void detach();

		void _setAttachedNode(SceneNode* node);

		virtual const Matrix4& _getAttachedNodeFullTransform(void) const;

		SceneNode* getAttachedNode() const { return mAttachedNode; }

		void setRenderQueueID(uint queueId);

		uint getRenderQueueID() const { return mRenderQueueID; }

		void setRenderQueuePriority(uint8 priority);

		uint8 getRenderQueuePriority() const { return mRenderQueuePriority; }

	protected:
		SceneNode*			mAttachedNode;
		String				mName;
		String				mType;
		uint				mRenderQueueID;
		uint8				mRenderQueuePriority;

		static AutoNamer	mAutoNamer;

	};

	class _DllExport SceneObjectFactory : public GeneralAlloc
	{
	public:
		SceneObjectFactory(){};

		virtual ~SceneObjectFactory(){};

		virtual SceneObject*	createInstance(const String& name) = 0;

		virtual void			destroyInstance(SceneObject* object) = 0;

		virtual const String& getType() const = 0;

	};
}
#endif
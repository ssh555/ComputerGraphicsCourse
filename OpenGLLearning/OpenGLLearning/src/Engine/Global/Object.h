#pragma once
#include "../Component/Transform.h"

namespace Engine
{
	// 所有类型对象的基类
	class Object
	{
	protected:
		virtual ~Object() { }


	public:
		static void Destory(Object* obj);
	};

	void Object::Destory(Object* obj)
	{
		// Transform 不可被销毁，只能跟随GameObject存在与销毁
		if (dynamic_cast<Transform*>(obj))
		{
			return;
		}
		delete obj;
		obj = nullptr;
	}

}

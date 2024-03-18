#pragma once
#include "../Component/Transform.h"

namespace Engine
{
	// �������Ͷ���Ļ���
	class Object
	{
	protected:
		virtual ~Object() { }


	public:
		static void Destory(Object* obj);
	};

	void Object::Destory(Object* obj)
	{
		// Transform ���ɱ����٣�ֻ�ܸ���GameObject����������
		if (dynamic_cast<Transform*>(obj))
		{
			return;
		}
		delete obj;
		obj = nullptr;
	}

}

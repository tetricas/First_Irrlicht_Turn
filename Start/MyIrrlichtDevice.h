#pragma once
#include "irrlicht.h"
#include "driverChoice.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class MyIrrlichtComposition
{
	class MyEventReceiver : public IEventReceiver
	{
		bool KeyIsDown[KEY_KEY_CODES_COUNT];

	public:
		MyEventReceiver()
		{
			for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
				KeyIsDown[i] = false;
		}

		virtual bool OnEvent(const SEvent& event)
		{
			if (event.EventType == irr::EET_KEY_INPUT_EVENT)
				KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
			return false;
		}
 
		virtual bool IsKeyDown(EKEY_CODE keyCode) const
		{
			return KeyIsDown[keyCode];
		}
	};

	IrrlichtDevice *device;
	IVideoDriver* driver;
	ISceneManager* smgr;
	ITexture* texture;
	IAnimatedMeshSceneNode* nodes;
	ICameraSceneNode* camera;
	ILightSceneNode* light;

public:
	MyEventReceiver receiver;
	MyIrrlichtComposition(E_DRIVER_TYPE,dimension2d<u32>);
	IrrlichtDevice* operator()() {return device;}
	void AddBackground(std::string);
	void AddCamera();
	void AddLight();
	void AbsMoving(ISceneNode*,vector3df);
	void ObjMoving(ISceneNode*,vector3df);
	void SetCamera(vector3df);
	void MyIrrlichtComposition::MoveCamera(vector3df);
	IAnimatedMeshSceneNode* mLoadMesh(vector3df,std::string);
	IAnimatedMeshSceneNode* mLoadMesh(vector3df,vector3df,vector3df,std::string,std::string);
	bool mCollision(ISceneNode*,ISceneNode*);
	void ShowScene();
	void ChangeCaption(core::stringw);
};


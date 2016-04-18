#include "MyIrrlichtDevice.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
	MyIrrlichtComposition mDevice(video::EDT_SOFTWARE,dimension2d<u32>(800,600 ));

	mDevice.AddBackground("background.png");

	IAnimatedMeshSceneNode* node = mDevice.mLoadMesh(vector3df(0,10,0),vector3df(0,-90,0),vector3df(0.2,0.2,0.2),"raven.md2","raven.jpg");
	const int count=5;
	IAnimatedMeshSceneNode* plat[count+1];
	for(int i(0);i<count;++i)
		plat[i] = mDevice.mLoadMesh(vector3df(-41+i*20, -20+i*10, 0),vector3df(30,0,0),vector3df(2.5,2.5,2.5),"platform02.obj","platform00.tga");
	
	mDevice.AddCamera();
	//u32 then = mDevice()->getTimer()->getTime();
	f32 g=-0.2;

	while(mDevice()->run())
	{
		g-=0.002;
 
		// двигаем ее текущую позицию вправо или влево
		if(mDevice.receiver.IsKeyDown(irr::KEY_KEY_A)) 
			mDevice.ObjMoving(node, vector3df(0,0,-0.25));
		else if(mDevice.receiver.IsKeyDown(irr::KEY_KEY_D))
			mDevice.ObjMoving(node, vector3df(0,0,0.25));

		//считываем для выхода
		if(mDevice.receiver.IsKeyDown(irr::KEY_ESCAPE))
			return 0;
		
		//"гравитация"
		mDevice.ObjMoving(node, vector3df(0,g,0));
		//движение камеры
		mDevice.SetCamera(vector3df(0, node->getPosition().Y, 0));
		mDevice.MoveCamera(vector3df(0 , node->getPosition().Y, node->getPosition().Z + 50));

		//перенос игрока на другую сторону при вылете за пределы поля
		if(node->getPosition().X == -45)
			mDevice.ObjMoving(node, vector3df(0, 0, -90));
		else if(node->getPosition().X == 45)
			mDevice.ObjMoving(node, vector3df(0, 0, 90));

		//обработка столкновения и "прыжок"
		for(int i(0);i<count;++i)
			if(mDevice.mCollision(node,plat[i]))
				g=0.2;
		
		//выход, если слишком сильно упал
		f32 fall=-150;
		if (node->getPosition().Y>fall - 5 && node->getPosition().Y<fall + 5)
			return 0;

		//обработка сцены
		mDevice.ShowScene();
	}

	mDevice()->drop();
	
	return 0;
}
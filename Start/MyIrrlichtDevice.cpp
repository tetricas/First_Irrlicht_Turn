#include "MyIrrlichtDevice.h"



MyIrrlichtComposition::MyIrrlichtComposition(E_DRIVER_TYPE driverType,dimension2d<u32> screenSize)
{
	device = createDevice( driverType, screenSize, 16, false, false, false, &receiver);
	if (!device)
		exit(1);
	device->setWindowCaption(L"Irrlicht");
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();

	/*ISceneNode * arrow;
    ISceneNode * arrowParent = smgr->addEmptySceneNode(); // Предок для осей
    arrowParent->setPosition(vector3df(0.f, 0.f, 0.f)); // Размещаем в центре координат
        // Ось Х
        SColor red(255, 255, 0, 0);
        arrow = smgr->addAnimatedMeshSceneNode(smgr->addArrowMesh("arrowX", red, red), arrowParent);
        arrow->setMaterialFlag(video::EMF_LIGHTING, false);
        arrow->setRotation(vector3df(90, 0, 0));
        arrow->setScale(vector3df(10, 30, 10));
        // Ось Y
        SColor green(255, 0, 255, 0);
        arrow = smgr->addAnimatedMeshSceneNode(smgr->addArrowMesh("arrowY", green, green), arrowParent);
        arrow->setMaterialFlag(video::EMF_LIGHTING, false);
        //arrow->setRotation(vector3df(90, 0, 0));
        arrow->setScale(vector3df(10, 30, 10));
        // Ось Z
        SColor blue(255, 0, 0, 255);
        arrow = smgr->addAnimatedMeshSceneNode(smgr->addArrowMesh("arrowZ", blue, blue), arrowParent);
        arrow->setMaterialFlag(video::EMF_LIGHTING, false);
        arrow->setRotation(vector3df(0, 0, -90));
        arrow->setScale(vector3df(10, 30, 10));*/
}

void MyIrrlichtComposition::AddBackground(std::string name)
{
	texture = driver->getTexture(name.c_str());
	driver->makeColorKeyTexture(texture, core::position2d<s32>(0,0));
	driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
	driver->getMaterial2D().AntiAliasing=video::EAAM_FULL_BASIC;
}

void MyIrrlichtComposition::AddCamera()
{
	camera=smgr->addCameraSceneNode(0, vector3df(0,10,50),vector3df(0,0,0));
}

void MyIrrlichtComposition::AddLight()
{
	light=smgr->addLightSceneNode(0, vector3df(0,100,0),SColorf(0.8f,0.8f,0.6f));
	light->setRadius(300);
}

void MyIrrlichtComposition::AbsMoving(ISceneNode* obj,vector3df vec )
{
	obj->setPosition(obj->getPosition()+vec);
}

void MyIrrlichtComposition::ObjMoving(ISceneNode* obj,vector3df vec)
{
	vector3df move;
	matrix4 mat;
	move=vec;
	mat.setRotationDegrees(obj->getRotation());
	mat.transformVect(move);
	obj->setPosition(obj->getPosition()+move);
}

void MyIrrlichtComposition::SetCamera(vector3df pos)
{
	camera->setTarget(pos);
}

void MyIrrlichtComposition::MoveCamera(vector3df vec)
{
	camera->setPosition(vec);
}

IAnimatedMeshSceneNode* MyIrrlichtComposition::mLoadMesh(vector3df pos, std::string name)
{
	IAnimatedMeshSceneNode* obj = smgr->addAnimatedMeshSceneNode(smgr->getMesh(name.c_str()));
	obj->setPosition(pos);
	return obj;
}

IAnimatedMeshSceneNode* MyIrrlichtComposition::mLoadMesh(vector3df pos,vector3df rot,vector3df scale, std::string name1, std::string name2)
{
	IAnimatedMeshSceneNode* obj = smgr->addAnimatedMeshSceneNode(smgr->getMesh(name1.c_str()));
	if(obj)
	{
		obj->setPosition(pos);
		obj->setMD2Animation(scene::EMAT_RUN);
		obj->setRotation(rot); 
		obj->setScale(scale);
		obj->setMaterialTexture(0, driver->getTexture(name2.c_str()));
		obj->addShadowVolumeSceneNode();
		return obj;
	}
	else 
		exit(2);
}

bool MyIrrlichtComposition::mCollision(ISceneNode* first,ISceneNode* sec)
{
	return (sec->getTransformedBoundingBox().intersectsWithBox(first->getTransformedBoundingBox()));
}

void MyIrrlichtComposition::ShowScene()
{
	driver->beginScene(true, true, video::SColor(255,50, 0, 10));
			
	driver->draw2DImage(texture, core::position2d<s32>(0,0),
						core::rect<s32>(0,0,1024,768), 0,
						video::SColor(255,255,255,255), true);
	smgr->drawAll(); // рисуем объекты на сцене
 
	driver->endScene();
}

void MyIrrlichtComposition::ChangeCaption(core::stringw str)
{
	device->setWindowCaption(str.c_str());
}
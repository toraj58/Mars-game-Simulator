/* 
Mars Game Simulator 
Developed BY: Touraj Ebrahimi
Using Irrlicht, C++ and Blender + Gimp
Refer to the comments for more info regarding Irrlicht and how this game is coded
 */

/** 

This Game Simulator shows how to set up the IDE for using the Irrlicht Engine and how
to write a simple Game with it. The program will show how to use
the basics of the VideoDriver, the GUIEnvironment, and the SceneManager.
Microsoft Visual Studio is used as an IDE, but you will also be able to
understand everything if you are using a different one or even another
operating system than windows.

You have to include the header file <irrlicht.h> in order to use the engine. The
header file can be found in the Irrlicht Engine SDK directory \c include. To let
the compiler find this header file, the directory where it is located has to be
specified. This is different for every IDE and compiler you use. Let's explain
shortly how to do this in Microsoft Visual Studio:

- If you use Version 6.0, select the Menu Extras -> Options.
  Select the directories tab, and select the 'Include' Item in the combo box.
  Add the \c include directory of the irrlicht engine folder to the list of
  directories. Now the compiler will find the Irrlicht.h header file. We also
  need the irrlicht.lib to be found, so stay in that dialog, select 'Libraries'
  in the combo box and add the \c lib/VisualStudio directory.
  \image html "vc6optionsdir.jpg"
  \image latex "vc6optionsdir.jpg"
  \image html "vc6include.jpg"
  \image latex "vc6include.jpg"

- If your IDE is Visual Studio .NET, select Tools -> Options.
  Select the projects entry and then select VC++ directories. Select 'show
  directories for include files' in the combo box, and add the \c include
  directory of the irrlicht engine folder to the list of directories. Now the
  compiler will find the Irrlicht.h header file. We also need the irrlicht.lib
  to be found, so stay in that dialog, select 'show directories for Library
  files' and add the \c lib/VisualStudio directory.
  \image html "vcnetinclude.jpg"
  \image latex "vcnetinclude.jpg"

That's it. With your IDE set up like this, you will now be able to develop
applications with the Irrlicht Engine.

Lets start!

After we have set up the IDE, the compiler will know where to find the Irrlicht
Engine header files so we can include it now in our code.
*/
#include <irrlicht.h>

/*
In the Irrlicht Engine, everything can be found in the namespace 'irr'. So if
you want to use a class of the engine, you have to write irr:: before the name
of the class. For example to use the IrrlichtDevice write: irr::IrrlichtDevice.
To get rid of the irr:: in front of the name of every class, we tell the
compiler that we use that namespace from now on, and we will not have to write
irr:: anymore.
*/
using namespace irr;

/*
There are 5 sub namespaces in the Irrlicht Engine. Take a look at them, you can
read a detailed description of them in the documentation by clicking on the top
menu item 'Namespace List' or by using this link:
http://irrlicht.sourceforge.net/docu/namespaces.html
Like the irr namespace, we do not want these 5 sub namespaces now, to keep this
example simple. Hence, we tell the compiler again that we do not want always to
write their names.
*/
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/*
To be able to use the Irrlicht.DLL file, we need to link with the Irrlicht.lib.
We could set this option in the project settings, but to make it easy, we use a
pragma comment lib for VisualStudio. On Windows platforms, we have to get rid
of the console window, which pops up when starting a program with main(). This
is done by the second pragma. We could also use the WinMain method, though
losing platform independence then.
*/
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


/*
This is the main method. We can now use main() on every platform.
*/
int main()
{
	/*
	The most important function of the engine is the createDevice()
	function. The IrrlichtDevice is created by it, which is the root
	object for doing anything with the engine. createDevice() has 7
	parameters:

	- deviceType: Type of the device. This can currently be the Null-device,
	   one of the two software renderers, D3D8, D3D9, or OpenGL. In this
	   example we use EDT_SOFTWARE, but to try out, you might want to
	   change it to EDT_BURNINGSVIDEO, EDT_NULL, EDT_DIRECT3D8,
	   EDT_DIRECT3D9, or EDT_OPENGL.

	- windowSize: Size of the Window or screen in FullScreenMode to be
	   created. In this example we use 640x480.

	- bits: Amount of color bits per pixel. This should be 16 or 32. The
	   parameter is often ignored when running in windowed mode.

	- fullscreen: Specifies if we want the device to run in fullscreen mode
	   or not.

	- stencilbuffer: Specifies if we want to use the stencil buffer (for
	   drawing shadows).

	- vsync: Specifies if we want to have vsync enabled, this is only useful
	   in fullscreen mode.

	- eventReceiver: An object to receive events. We do not want to use this
	   parameter here, and set it to 0.

	Always check the return value to cope with unsupported drivers,
	dimensions, etc.
	*/

	// ******** Touraj: IF this did not work with video::EDT_DIRECT3D9, change it to video::EDT_OPENGL *******
	IrrlichtDevice *device =
		createDevice( video::EDT_DIRECT3D9, dimension2d<u32>(1366, 768), 32,
			true, true, true, 0); // 1366, 768

	if (!device)
		return 1;

	/*
	Set the caption of the window to some nice text. Note that there is an
	'L' in front of the string. The Irrlicht Engine uses wide character
	strings when displaying text.
	*/
	device->setWindowCaption(L"Game By Touraj Ebrahimi");


	/*
	Get a pointer to the VideoDriver, the SceneManager and the graphical
	user interface environment, so that we do not always have to write
	device->getVideoDriver(), device->getSceneManager(), or
	device->getGUIEnvironment().
	*/
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	driver->setFog(SColor(100,30,30,30),E_FOG_TYPE::EFT_FOG_EXP, 50,4000,0.0009f, false,false);


	/*
	We add a hello world label to the window, using the GUI environment.
	The text is placed at the position (10,10) as top left corner and
	(260,22) as lower right corner.
	*/
	// guienv->addButton(rect<s32>(10,10,360,122),0,-1,L"exit",L"quit");
	guienv->addStaticText(L"Game By Touraj Ebrahimi",
		rect<s32>(10,10,260,22), true,0,0,0,true);

	/*
	To show something interesting, we load a Quake 2 model and display it.
	We only have to get the Mesh from the Scene Manager with getMesh() and add
	a SceneNode to display the mesh with addAnimatedMeshSceneNode(). We
	check the return value of getMesh() to become aware of loading problems
	and other errors.

	Instead of writing the filename sydney.md2, it would also be possible
	to load a Maya object file (.obj), a complete Quake3 map (.bsp) or any
	other supported file format. By the way, that cool Quake 2 model
	called sydney was modelled by Brian Collins.
	*/
	//IAnimatedMesh* mesh = smgr->getMesh("../../media/sydney.md2"); // Zuleyka.x
	IAnimatedMesh* mesh = smgr->getMesh("Objects/Zuleyka.x");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	//mesh->setAnimationSpeed(12);
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );

	/*
	To let the mesh look a little bit nicer, we change its material. We
	disable lighting because we do not have a dynamic light in here, and
	the mesh would be totally black otherwise. Then we set the frame loop,
	such that the predefined STAND animation is used. And last, we apply a
	texture to the mesh. Without it the mesh would be drawn using only a
	color.
	*/
	if (node)
	{
		 node->setMaterialFlag(EMF_LIGHTING, false);
			//	node->setMaterialFlag(EMF_NORMALIZE_NORMALS,true);
				node->setMaterialFlag(EMF_GOURAUD_SHADING, true);
				node->setMaterialFlag(EMF_FOG_ENABLE,true);
		
		node->setAnimationSpeed(14);
		node->setScale(vector3df(40,40,40));
		
		//node->setMD2Animation(scene::EMAT_STAND);
		node->setFrameLoop(0,79); // Frame Loop for zulaykhah
		node->setPosition(vector3df(300,-265,400));
		
		node->setMaterialTexture( 0, driver->getTexture("Objects/Zuleyka_Skin.PNG") );

		 // // add shadow
   // node->addShadowVolumeSceneNode();
   // smgr->setShadowColor(video::SColor(150,0,0,0));
	  //node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);


	}

	ILightSceneNode *light1 = smgr->addLightSceneNode();
	SLight &lightData1 = light1->getLightData();
	lightData1.Type = ELT_POINT;
	lightData1.Radius = 19000.0f;
	lightData1.DiffuseColor = SColorf(10,5,50,1);
	lightData1.CastShadows = true;
	light1->setPosition(vector3df(-1300,7000,-1400));

	ILightSceneNode *light2 = smgr->addLightSceneNode();
	SLight &lightData2 = light2->getLightData();
	lightData2.Type = ELT_POINT;
	lightData2.Radius = 8000.0f;
	lightData2.DiffuseColor = SColorf(150,10,5,0.1);
	lightData2.CastShadows = true;
	light2->setPosition(vector3df(300,865,-1900));

	// Night Light
	//	ILightSceneNode *nightLight = smgr->addLightSceneNode();
	//SLight &nightLightData = nightLight->getLightData();
	//nightLightData.Type = ELT_POINT;
	//nightLightData.Radius = 9000.0f;
	//nightLightData.DiffuseColor = SColorf(0,5,250,1);
	//nightLightData.CastShadows = true;
	//nightLight->setPosition(vector3df(2000,5000,-4400));

		 // attach billboard to light

    IBillboardSceneNode *bill = smgr->addBillboardSceneNode(light2, core::dimension2d<f32>(50, 50));
    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    bill->setMaterialTexture(0, driver->getTexture("../../../media/particlewhite.bmp"));

	/////// Animate the light

	scene::ISceneNodeAnimator* animl = 0;
    animl = smgr->createFlyCircleAnimator (core::vector3df(0,150,0),250.0f);
    light2->addAnimator(animl);
    animl->drop();


	///////

	/////////////////////////////////////////////////// Water Begin

	mesh = smgr->addHillPlaneMesh( "WaterSurface",
        core::dimension2d<f32>(20,20),
        core::dimension2d<u32>(60,60), 0, 0,
        core::dimension2d<f32>(0,0),
        core::dimension2d<f32>(10,10));
	ISceneNode *waterNode = 0;
    waterNode = smgr->addWaterSurfaceSceneNode(mesh->getMesh(0), 4.0f, 600.0f, 0.01f);
    waterNode->setPosition(core::vector3df(11000,200,5000));
	waterNode->setScale(core::vector3df(7,7,7));
	//waterNode->setRotation(core::vector3df(0,0,180));

    waterNode->setMaterialTexture(0, driver->getTexture("../../../media/lava.jpg"));
    waterNode->setMaterialTexture(1, driver->getTexture("../../../media/water.jpg"));

    waterNode->setMaterialType(video::EMT_REFLECTION_2_LAYER);
	 waterNode->setMaterialFlag(video::EMF_BACK_FACE_CULLING, false);

	// Light For Water
		ILightSceneNode *light3 = smgr->addLightSceneNode();
	SLight &lightData3 = light3->getLightData();
	lightData3.Type = ELT_POINT;
	lightData3.Radius = 8000.0f;
	lightData3.DiffuseColor = SColorf(150,150,5,0.1);
	lightData3.CastShadows = true;
	vector3df waterPos =  waterNode->getPosition();
	waterPos.Y += 1000;
	light3->setPosition(waterPos);


	//////////////////////////////////////////////////  Water End



	

	/*
	To look at the mesh, we place a camera into 3d space at the position
	(0, 30, -40). The camera looks from there to (0,5,0), which is
	approximately the place where our md2 model is.
	*/
	//smgr->addCameraSceneNode(0, vector3df(10,10,-1), vector3df(0,5,0));

	SKeyMap keyMap[10];
    keyMap[0].Action = EKA_MOVE_FORWARD;
    keyMap[0].KeyCode = KEY_UP;
    keyMap[1].Action = EKA_MOVE_FORWARD;
    keyMap[1].KeyCode = KEY_KEY_W;
                   
    keyMap[2].Action = EKA_MOVE_BACKWARD;
    keyMap[2].KeyCode = KEY_DOWN;
    keyMap[3].Action = EKA_MOVE_BACKWARD;
    keyMap[3].KeyCode = KEY_KEY_S;
                   
    keyMap[4].Action = EKA_STRAFE_LEFT;
    keyMap[4].KeyCode = KEY_LEFT;
    keyMap[5].Action = EKA_STRAFE_LEFT;
    keyMap[5].KeyCode = KEY_KEY_A;
                   
    keyMap[6].Action = EKA_STRAFE_RIGHT;
    keyMap[6].KeyCode = KEY_RIGHT;
    keyMap[7].Action = EKA_STRAFE_RIGHT; 
    keyMap[7].KeyCode = KEY_KEY_D;
	keyMap[8].Action = EKA_JUMP_UP; 
    keyMap[8].KeyCode = KEY_SPACE;
	keyMap[9].Action = EKA_CROUCH; 
    keyMap[9].KeyCode = KEY_KEY_C;

  // m_pCamera = pManager->getSceneManager()->addCameraSceneNodeFPS(0, 50, 200, -1, keyMap, 8);

	//IMeshSceneNode *cubeNode = smgr->addCubeSceneNode();
	//cubeNode->setMaterialTexture( 0, driver->getTexture("Objects/Zuleyka_Skin.PNG") );
	//cubeNode->setMaterialFlag(EMF_LIGHTING, false);

	

///// terrian node/////

	// add terrain scene node
    scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
        "Objects/hm.png",
        0,                  // parent node
        -1,                 // node id
        core::vector3df(-1400.f, -600.f, -1800.f),     // position
        core::vector3df(0.f, 0.f, 0.f),     // rotation
        core::vector3df(80.f, 16.4f,80.f),  // scale
        video::SColor ( 255, 255, 255, 255 ),   // vertexColor
        5,                  // maxLOD
        scene::ETPS_17,             // patchSize
        4                   // smoothFactor
        );

    terrain->setMaterialFlag(video::EMF_LIGHTING, true);
	terrain->setMaterialFlag(EMF_GOURAUD_SHADING,true);
	terrain->setMaterialFlag(EMF_BACK_FACE_CULLING,false); // Make Terrian Double sided Material

	terrain->setMaterialFlag(EMF_FOG_ENABLE,true); //enables fog


    terrain->setMaterialTexture(0,
            driver->getTexture("Objects/terrmain.jpg"));
    terrain->setMaterialTexture(1,
            driver->getTexture("Objects/terrdetail.jpg"));
    
    terrain->setMaterialType(video::EMT_DETAIL_MAP);

    terrain->scaleTexture(1.0f, 40.0f);


	/////////// terrian node end /////

	////////////////////////////////////////// Sky box Begin
	// scene::ISceneNode* skybox;
	//scene::ISceneNode* skydome;

	 // create skybox and skydome
	// Touraj: [Important]For the skybox textures, we disable mipmap generation, because we don't need mipmaps on it.
    driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

    //scene::ISceneNode* skybox=smgr->addSkyBoxSceneNode(
    //    driver->getTexture("../../media/irrlicht2_up.jpg"),
    //    driver->getTexture("../../media/irrlicht2_dn.jpg"),
    //    driver->getTexture("../../media/irrlicht2_lf.jpg"),
    //    driver->getTexture("../../media/irrlicht2_rt.jpg"),
    //    driver->getTexture("../../media/irrlicht2_ft.jpg"),
    //    driver->getTexture("../../media/irrlicht2_bk.jpg"));
    scene::ISceneNode* skydome=smgr->addSkyDomeSceneNode(driver->getTexture("Objects/scifidome3.jpg"),16,8,0.95f,2.0f);
	// ../../media/skydome.jpg"

    driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
	skydome->setVisible(true);


	////////////////////////////////////////////// Sky Box end


	//cubeNode->setPosition(vector3df(40,40,40));
	ICameraSceneNode *camnode = smgr->addCameraSceneNodeFPS(0, 50, 1, -1, keyMap, 10, false,50,false,true);
	camnode->setFarValue(42000.0f);
	camnode->setPosition(vector3df(200,270,-80));
	//camnode->
	device->getCursorControl()->setVisible(false);
	
		////////////////////// Terrian Collision Detection

	// create triangle selector for the terrain 
    scene::ITriangleSelector* selector
        = smgr->createTerrainTriangleSelector(terrain, 0);
    terrain->setTriangleSelector(selector);

    // create collision response animator and attach it to the camera
    scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
        selector, camnode, core::vector3df(60,100,60),
        core::vector3df(0,-9.8f,0), // gravity
        core::vector3df(0,50,0));
	
    selector->drop();
    camnode->addAnimator(anim);
    anim->drop();


	////////////////////// Terrian Collision Detection End

	////////////// Add Sphere [Begin]

	IMeshSceneNode *sphereNode = smgr->addSphereSceneNode();
	if (sphereNode)
	{
		sphereNode->setMaterialTexture( 0, driver->getTexture("Objects/lunar.jpg") );
		sphereNode->setMaterialFlag(EMF_LIGHTING, true);
		sphereNode->getMaterial(0).Shininess = 20;
		sphereNode->getMaterial(0).EmissiveColor = SColor(0.1,100,10,10);
		sphereNode->getMaterial(0).GouraudShading = true;
		sphereNode->getMaterial(0).SpecularColor = SColor(0.5f,250,0,0);
		sphereNode->setScale(vector3df(760,760,760)); // Scale of the Sphere
		sphereNode->setPosition(vector3df(-7740,5500,-1000));
		sphereNode->getMaterial(0).getTextureMatrix(0).setTextureScale(8,8);
		scene::ISceneNodeAnimator* anim =
        smgr->createRotationAnimator(core::vector3df(0.01f, 0, 0.03f));

    if(anim)
    {
       sphereNode->addAnimator(anim);
       anim->drop();
        anim = 0;
    }

					  // add Real time shadow Casting To Sphere
    //sphereNode->addShadowVolumeSceneNode();
    //sphereNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

	}
	///////////// Add Sphere [End]

	////////////////// Add sciFiGateArray [Begin]
	for (s32 i=0;i<4;++i)
	{
	IAnimatedMesh *sciFiGateArray = smgr->getMesh("MayaObjects/SciFIGateArray2.obj");
	IAnimatedMeshSceneNode* sciFiGateArrayNode = smgr->addAnimatedMeshSceneNode( sciFiGateArray );
		if (sciFiGateArrayNode)
		{
				//sciFiGateArrayNode->setMaterialTexture( 0, driver->getTexture("Objects/lunar.jpg") );
				sciFiGateArrayNode->setMaterialFlag(EMF_LIGHTING, false);
				sciFiGateArrayNode->getMaterial(0).GouraudShading = true;
				sciFiGateArrayNode->setScale(vector3df(20,20,20)); // Scale of the sciFiGateArray
				sciFiGateArrayNode->setPosition(vector3df(9800+i*2500,550,-2000));

					// Light For Gate Array [Begin]
				ILightSceneNode *lightGate = smgr->addLightSceneNode();
			SLight &lightDataGate = lightGate->getLightData();
			lightDataGate.Type = ELT_POINT;
			lightDataGate.Radius = 18000.0f;
			//lightDataGate.Direction = vector3df(0,0,-4000);
			lightDataGate.DiffuseColor = SColorf(150,150,5,0.1);
			lightDataGate.CastShadows = true;
			vector3df GateArrayPos =  sciFiGateArrayNode->getPosition();
			GateArrayPos.Y -= 200;
			GateArrayPos.X += 1000;
			GateArrayPos.Z = -4000;
			lightGate->setPosition(GateArrayPos);
			// Light For Gate Array [End]

			// add Real time shadow Casting To sciFiGateArray
			//sciFiGateArrayNode->addShadowVolumeSceneNode();
			//sciFiGateArrayNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);


				////////////////////////////////////////////// SCIGATEWAYARRAY Collision Detection [Begin]


			scene::ITriangleSelector *sciFiGateArraySelector = smgr->createTriangleSelector(sciFiGateArrayNode);
			sciFiGateArrayNode->setTriangleSelector(sciFiGateArraySelector);

			// create collision response animator and attach it to the camera
			scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
				sciFiGateArraySelector, camnode, core::vector3df(60,100,60),
				core::vector3df(0,0,0), // gravity
				core::vector3df(0,50,0),0.0005f);
	
			sciFiGateArraySelector->drop();
			camnode->addAnimator(anim);
			anim->drop();

		////////////////////////////////////////// SCIGATEWAYARRAY Collision Detection [End]
		}


	}
	///////////////// Add sciFiGateArray [End]

	//////////////////////////// Add MotherShip [Begin]
		IAnimatedMesh* motherShip = smgr->getMesh("MayaObjects/MotherShip.obj");
	if (!motherShip)
	{
		device->drop();
		return 1;
	}
	//mesh->setAnimationSpeed(12);
	IAnimatedMeshSceneNode* motherShipNode = smgr->addAnimatedMeshSceneNode( motherShip );
	if (motherShipNode)
	{
		//motherShipNode->setMaterialTexture( 1, driver->getTexture("Objects/lunar.jpg") ); // MayaObjects/ShipMatMain.jpg
		motherShipNode->setMaterialFlag(EMF_LIGHTING, false);
		motherShipNode->setMaterialFlag(EMF_BACK_FACE_CULLING, true);

		//motherShipNode->setMaterialTexture(0, driver->getTexture("../../../media/lava.jpg"));
		//motherShipNode->setMaterialTexture(1, driver->getTexture("Objects/sky_fyros_night_fair.png"));
		//motherShipNode->setMaterialType(video::EMT_REFLECTION_2_LAYER);

		//motherShipNode->getMaterial(0).Shininess = 20;
		//motherShipNode->getMaterial(0).EmissiveColor = SColor(0.1,100,10,10);
		//motherShipNode->getMaterial(0).GouraudShading = true;
		//motherShipNode->getMaterial(0).SpecularColor = SColor(0.5f,250,0,0);

		motherShipNode->setScale(vector3df(40,40,40)); // Scale of the Sphere
		motherShipNode->setPosition(vector3df(0,-1000,-15500));
		motherShipNode->setRotation(core::vector3df(0,-45,0));

		//motherShipNode->getMaterial(1).getTextureMatrix(0).setTextureScale(8,8);

		////////////////////////////////////////////// MotherShip Collision Detection [Begin]


    scene::ITriangleSelector *motherShipSelector = smgr->createTriangleSelector(motherShipNode);
    motherShipNode->setTriangleSelector(motherShipSelector);

    // create collision response animator and attach it to the camera
    scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
        motherShipSelector, camnode, core::vector3df(60,100,60),
        core::vector3df(0,0,0), // gravity
        core::vector3df(0,50,0));
	
    motherShipSelector->drop();
    camnode->addAnimator(anim);
    anim->drop();

////////////////////////////////////////// MotherShip Collision Detection [End]

		// Rotate Mother Ship
				//scene::ISceneNodeAnimator* anim =
    //    smgr->createRotationAnimator(core::vector3df(0, 0.1f, 0));

    //if(anim)
    //{
    //   motherShipNode->addAnimator(anim);
    //   anim->drop();
    //    anim = 0;
    //}
	}
	//////////////////////////// Add MotherShip [End]

	//////////////////////////// Add UFO [Begin]
	IAnimatedMesh* ufo = smgr->getMesh("MayaObjects/UFO.obj");
	if (!ufo)
	{
		device->drop();
		return 1;
	}
	//mesh->setAnimationSpeed(12);
	IAnimatedMeshSceneNode* ufoNode = smgr->addAnimatedMeshSceneNode( ufo );
	if (ufo)
	{
		//motherShipNode->setMaterialTexture( 1, driver->getTexture("Objects/lunar.jpg") ); // MayaObjects/ShipMatMain.jpg
		ufoNode->setMaterialFlag(EMF_LIGHTING, false);
		ufoNode->setMaterialFlag(EMF_BACK_FACE_CULLING, false); // Double Sided Materials
		ufoNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		//ufoNode->getMaterial(0).Shininess = 20;
		//ufoNode->getMaterial(0).EmissiveColor = SColor(0.1,100,10,10);
		//ufoNode->getMaterial(0).GouraudShading = true;
		//ufoNode->getMaterial(0).SpecularColor = SColor(0.5f,250,0,0);
		ufoNode->setScale(vector3df(10,10,10)); // Scale of the Sphere
		ufoNode->setPosition(vector3df(740,-2000,-1400)); //EMF_NORMALIZE_NORMALS
		
		//ufoNode->setRotation(core::vector3df(0,30,0));
		//motherShipNode->getMaterial(1).getTextureMatrix(0).setTextureScale(8,8);

		scene::ISceneNodeAnimator* anim =
        smgr->createFlyCircleAnimator(vector3df(-740,4500,-4400),20000,0.001);
		if(anim)
		{
		   ufoNode->addAnimator(anim);
		   anim->drop();
			anim = 0;
		}

			// add Real time shadow Casting To Ufo
			ufoNode->addShadowVolumeSceneNode();
			ufoNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

	}
	//////////////////////////// Add UFO [End]

	///////////////////////// create a particle system [Begin]

    scene::IParticleSystemSceneNode* ps =
        smgr->addParticleSystemSceneNode(false);

    scene::IParticleEmitter* em = ps->createBoxEmitter(
        core::aabbox3d<f32>(-70,0,-70,70,450,470), // emitter size
        core::vector3df(0.0f,0.06f,0.0f),   // initial direction
        1800,2000,                             // emit rate
        video::SColor(0,255,255,255),       // darkest color
        video::SColor(0,100,255,100),       // brightest color
        15800,17000,0,                         // min and max age, angle
        core::dimension2df(100.f,100.f),         // min size
        core::dimension2df(400.f,400.f));        // max size

    ps->setEmitter(em); // this grabs the emitter
    em->drop(); // so we can drop it here without deleting it

    scene::IParticleAffector* paf = ps->createFadeOutParticleAffector(); //// createGravityAffector();

    ps->addAffector(paf); // same goes for the affector
    paf->drop();
	vector3df wpos = waterNode->getPosition(); //Pos Neeed Some Tweeking
	wpos.Y-=400;
	wpos.X+=700;
	wpos.Z-=400;
	ps->setPosition(wpos); //core::vector3df(5000,1000,4000)
    ps->setScale(core::vector3df(30,30,30));
    ps->setMaterialFlag(video::EMF_LIGHTING, true);
    ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);//Touraj: Default was False, I made it true to impose prespective illusion on Particles
    ps->setMaterialTexture(0, driver->getTexture("../../../media/fireball.bmp"));
    ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	///////////////////////// create a particle system [End]

	//////////////////////////// Add ufo2 [Begin]
	IAnimatedMesh* ufo2 = smgr->getMesh("MayaObjects/ufo.obj");
	if (!ufo2)
	{
		device->drop();
		return 1;
	}
	//mesh->setAnimationSpeed(12);
	IAnimatedMeshSceneNode* ufo2Node = smgr->addAnimatedMeshSceneNode( ufo2 );
	if (ufo2)
	{
		//motherShipNode->setMaterialTexture( 1, driver->getTexture("Objects/lunar.jpg") ); // MayaObjects/ShipMatMain.jpg
		ufo2Node->setMaterialFlag(EMF_LIGHTING, false);
		ufo2Node->setMaterialFlag(EMF_BACK_FACE_CULLING, false);
		
		//ufo2Node->getMaterial(0).Shininess = 20;
		//ufo2Node->getMaterial(0).EmissiveColor = SColor(0.1,100,10,10);
		//ufo2Node->getMaterial(0).GouraudShading = true;
		//ufo2Node->getMaterial(0).SpecularColor = SColor(0.5f,250,0,0);
		ufo2Node->setScale(vector3df(20,20,20)); // Scale of the UFO2
		ufo2Node->setPosition(vector3df(740,-2000,-1400));
		//ufo2Node->setRotation(core::vector3df(0,30,0));
		//motherShipNode->getMaterial(1).getTextureMatrix(0).setTextureScale(8,8);

		scene::ISceneNodeAnimator* anim =
        smgr->createFlyCircleAnimator(vector3df(740,6500,-2400),40000,0.0005);
		if(anim)
		{
		   ufo2Node->addAnimator(anim);
		   anim->drop();
			anim = 0;
		}

					// add Real time shadow Casting To Ufo
			ufo2Node->addShadowVolumeSceneNode();
			ufo2Node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
	}
	//////////////////////////// Add ufo2 [End]

	//////////////////////////// Add ufo3 [Begin]
	IAnimatedMesh* ufo3 = smgr->getMesh("MayaObjects/ufo.obj");
	if (!ufo3)
	{
		device->drop();
		return 1;
	}
	//mesh->setAnimationSpeed(12);
	IAnimatedMeshSceneNode* ufo3Node = smgr->addAnimatedMeshSceneNode( ufo3 );
	if (ufo3)
	{
		// ufo3Node->setMaterialTexture( 0, driver->getTexture("Objects/lunar.jpg") ); // MayaObjects/ShipMatMain.jpg
		ufo3Node->setMaterialFlag(EMF_LIGHTING, true);
		ufo3Node->setMaterialFlag(EMF_BACK_FACE_CULLING, false);
		//ufo3Node->setMaterialType(EMT_REFLECTION_2_LAYER);

		//ufo3Node->setMaterialTexture(0, driver->getTexture("../../../media/lava.jpg"));
		//ufo3Node->setMaterialTexture(1, driver->getTexture("Objects/lunar.jpg"));
		//ufo3Node->setMaterialType(video::EMT_REFLECTION_2_LAYER);
		
		//ufo3Node->getMaterial(0).Shininess = 20;
		//ufo3Node->getMaterial(0).EmissiveColor = SColor(0.1,100,10,10);
		//ufo3Node->getMaterial(0).GouraudShading = true;
		//ufo3Node->getMaterial(0).SpecularColor = SColor(0.5f,250,0,0);
		ufo3Node->setScale(vector3df(20,20,20)); // Scale of the ufo3
		ufo3Node->setPosition(vector3df(740,2000,-2400));
		ufo3Node->setRotation(core::vector3df(-30,0,0));
		//motherShipNode->getMaterial(1).getTextureMatrix(0).setTextureScale(8,8);

		scene::ISceneNodeAnimator* anim =
			smgr->createRotationAnimator(vector3df(0,0.1,0));
		if(anim)
		{
		   ufo3Node->addAnimator(anim);
		   anim->drop();
			anim = 0;
		}

		// Light For UFO3
		ILightSceneNode *light4 = smgr->addLightSceneNode();
	SLight &lightData4 = light4->getLightData();
	lightData4.Type = ELT_POINT;
	lightData4.Radius = 4000.0f;
	lightData4.DiffuseColor = SColorf(150,150,5,0.1);
	lightData4.CastShadows = true;
	vector3df ufo3NodePos =  ufo3Node->getPosition();
	ufo3NodePos.Y += 800;
	//ufo3NodePos.Z += 1200;
	light4->setPosition(ufo3NodePos);

	/////////////////////// attach billboard to light

    IBillboardSceneNode *bill2 = smgr->addBillboardSceneNode(light4, core::dimension2d<f32>(150, 150));
    bill2->setMaterialFlag(video::EMF_LIGHTING, false);
    bill2->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    bill2->setMaterialTexture(0, driver->getTexture("../../../media/particlewhite.bmp"));

	scene::ISceneNodeAnimator* anim2 =
        smgr->createFlyCircleAnimator(ufo3NodePos,1000,0.0005);
		if(anim2)
		{
		   light4->addAnimator(anim2);
		   anim2->drop();
			anim2 = 0;
		}


					// add Real time shadow Casting To Ufo
			ufo3Node->addShadowVolumeSceneNode();
			ufo3Node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
	}
	//////////////////////////// Add ufo3 [End]

		//////////////////////////// Add Rocks [Begin]
	IAnimatedMesh* rock = smgr->getMesh("MayaObjects/RockPack.obj");
	if (!rock)
	{
		device->drop();
		return 1;
	}
	//mesh->setAnimationSpeed(12);
	IAnimatedMeshSceneNode* rockNode = smgr->addAnimatedMeshSceneNode( rock );
	if (rock)
	{
		rockNode->setMaterialTexture( 0, driver->getTexture("MayaObjects/rockmat.jpg") ); // MayaObjects/ShipMatMain.jpg
		rockNode->setMaterialFlag(EMF_LIGHTING, true);
		rockNode->setMaterialFlag(EMF_BACK_FACE_CULLING, false);
		//rockNode->setMaterialType(EMT_REFLECTION_2_LAYER);

		//rockNode->setMaterialTexture(0, driver->getTexture("../../../media/lava.jpg"));
		//rockNode->setMaterialTexture(1, driver->getTexture("Objects/lunar.jpg"));
		//rockNode->setMaterialType(video::EMT_REFLECTION_2_LAYER);
		
		//rockNode->getMaterial(0).Shininess = 20;
		//rockNode->getMaterial(0).EmissiveColor = SColor(0.1,100,10,10);
		//rockNode->getMaterial(0).GouraudShading = true;
		//rockNode->getMaterial(0).SpecularColor = SColor(0.5f,250,0,0);
		//rockNode->setScale(vector3df(20,20,20)); // Scale of the rock
		rockNode->setPosition(vector3df(1250,840,-200));
		rockNode->setRotation(core::vector3df(-30,0,0));
		//motherShipNode->getMaterial(1).getTextureMatrix(0).setTextureScale(8,8);

		//scene::ISceneNodeAnimator* anim =
		//	smgr->createRotationAnimator(vector3df(0,0.1,0));
		//if(anim)
		//{
		//   rockNode->addAnimator(anim);
		//   anim->drop();
		//	anim = 0;
		//}

					// add Real time shadow Casting To Ufo
			//rockNode->addShadowVolumeSceneNode();
			//rockNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
	}
	//////////////////////////// Add Rocks [End]


	smgr->setShadowColor(video::SColor(150,0,0,0)); // Light of real time shadows
	int leveupCounter = 1;
	int boxOffset = 0;
	s32 modVal = 4;
	s32 modBoost = 1;
	while(leveupCounter <=12)
	{
		s32 boxLevelOffset=0;
		vector3df basePos = vector3df(0,-400,0);
		basePos.Y+=leveupCounter*130;
		for (s32 i=1;i<=16;++i)
		{
		IMeshSceneNode *cubeNode = smgr->addCubeSceneNode();
		cubeNode->setMaterialTexture( 0, driver->getTexture("Objects/texture1.tga") );
		// cubeNode->setMaterialFlag(EMF_LIGHTING, true);
		cubeNode->getMaterial(0).Shininess = 20;
		cubeNode->getMaterial(0).EmissiveColor = SColor(0.1,0,200,0);
		cubeNode->getMaterial(0).GouraudShading = false;
		cubeNode->getMaterial(0).SpecularColor = SColor(1,250,0,0);
		cubeNode->setScale(vector3df(12,12,12)); // Scale of the Cubes

		if(i%modVal==0)
		{
			if (modBoost >4 )modBoost=1;
			basePos.X+=130*(modBoost++);
			basePos.Z-=130;
		cubeNode->setPosition(basePos);
		basePos.Z+=130;
		basePos.X-=130*(modBoost--);

		}
		else
		{
			
		cubeNode->setPosition(basePos);
		basePos.Z+=130;
		}
		

				  // add Real time shadow Casting To boxes
    cubeNode->addShadowVolumeSceneNode();
    cubeNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
	
	
			//////////////////// Apply Normal Map Begin

			 video::ITexture* normalMap =
            driver->getTexture("Objects/normal.tga"); //normal.tga
			  
        if (normalMap)
		{
			 driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

         //   driver->makeNormalMapTexture(normalMap, 20.0f); //Touraj:  This is for GrayScale Maps

		scene::IMesh* tangentMesh = tangentMesh = smgr->getMeshManipulator()->createMeshWithTangents(cubeNode->getMesh());
		cubeNode = smgr->addMeshSceneNode(tangentMesh);

        cubeNode->setMaterialTexture(1, normalMap);

        // Stones don't glitter..
        cubeNode->getMaterial(0).SpecularColor.set(0,0,0,0);
        cubeNode->getMaterial(0).Shininess = 0.f;

        //cubeNode->setMaterialFlag(video::EMF_FOG_ENABLE, true);
        cubeNode->setMaterialType(video::EMT_PARALLAX_MAP_SOLID);
        // adjust height for parallax effect
        cubeNode->getMaterial(0).MaterialTypeParam = 1.f / 64.f;
		tangentMesh->drop();
		}

        // drop mesh because we created it with a create.. call.
        


		/////////////////// Apply Normal Map End


	////////////////////////////////////////////// Box Collision Detection


    scene::ITriangleSelector* selector
        = smgr->createTriangleSelectorFromBoundingBox(cubeNode);
    cubeNode->setTriangleSelector(selector);

    // create collision response animator and attach it to the camera
    scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
        selector, camnode, core::vector3df(60,100,60),
        core::vector3df(0,0,0), // gravity
        core::vector3df(0,50,0));
	
    selector->drop();
    camnode->addAnimator(anim);
    anim->drop();


	////////////////////////////////////////// Box Collision Detection End


	//		scene::ISceneNodeAnimator* animCube =
	//smgr->createFlyCircleAnimator(core::vector3df(10+boxOffset,10+boxOffset,30), 20.0f+boxOffset);
	float yaxisSpeed = 0.3f;

	//if (i%2==0) yaxisSpeed*=2;
	if (leveupCounter%2==0) yaxisSpeed*=4;

			scene::ISceneNodeAnimator* animCube =
				smgr->createRotationAnimator(vector3df(0,yaxisSpeed,0));

        if (animCube)
        {
            cubeNode->addAnimator(animCube);
            animCube->drop();
        }

		} // End For
		leveupCounter++;
		boxOffset +=60;
		
	
	}

	//////////////////////////////




	/////////////////////

	/*
	Ok, now we have set up the scene, lets draw everything: We run the
	device in a while() loop, until the device does not want to run any
	more. This would be when the user closes the window or presses ALT+F4
	(or whatever keycode closes a window).
	*/
	while(device->run())
	{
		/*
		Anything can be drawn between a beginScene() and an endScene()
		call. The beginScene() call clears the screen with a color and
		the depth buffer, if desired. Then we let the Scene Manager and
		the GUI Environment draw their content. With the endScene()
		call everything is presented on the screen.
		*/
		 if (device->isWindowActive())
        {


		driver->beginScene(true, true, SColor(0,0,0,0));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();
		 }
		 else device->yield();
	}

	/*
	After we are done with the render loop, we have to delete the Irrlicht
	Device created before with createDevice(). In the Irrlicht Engine, you
	have to delete all objects you created with a method or function which
	starts with 'create'. The object is simply deleted by calling ->drop().
	See the documentation at irr::IReferenceCounted::drop() for more
	information.
	*/
	device->drop();

	return 0;
}

/*
That's it. Compile and run my Game... Take Care Friends. Touraj Ebrahimi
**/

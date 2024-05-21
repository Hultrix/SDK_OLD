// g++ main.cpp -o main `pkg-config --libs --cflags OGRE` -lsfml-window -lsfml-graphics -lsfml-system -lGL

// SFML v2.6 Includes
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

// Ogre v14.2 Includes
#include <Ogre.h>
#include <OgreFrameListener.h>
#include <OgreTextureManager.h>

using namespace Ogre;

//
class MyFrameListener : public Ogre::FrameListener {
public:
  bool frameStarted(const FrameEvent &evt);
  bool frameEnded(const FrameEvent &evt);
  bool frameRenderingQueued(const FrameEvent &evt);
};

//
bool MyFrameListener::frameStarted(const FrameEvent &evt) {
  return true;
}

//
bool MyFrameListener::frameEnded(const FrameEvent &evt) {
  return true;
}

//
bool MyFrameListener::frameRenderingQueued(const FrameEvent &evt) {
  return true;
}

int main()
{
  // create the window
  sf::RenderWindow window(sf::VideoMode(800, 600), "Ogre3D v14.2 and SFML v2.6", sf::Style::Default, sf::ContextSettings(32));
  
  // Create an instance of the OGRE Root Class
  Ogre::Root* ogreRoot = new Ogre::Root;

  // Configures the application
  if (!ogreRoot->restoreConfig()) {
    ogreRoot->showConfigDialog();
    ogreRoot->saveConfig();
  }

  // Create Rendering System, but don't initialise it.
  ogreRoot->setRenderSystem(ogreRoot->getAvailableRenderers()[0]);
  ogreRoot->initialise(false);

  // Create an off-screen render target
  Ogre::TexturePtr rttTex = Ogre::TextureManager::getSingleton().createManual(
    "RttTex", 
    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
    Ogre::TEX_TYPE_2D, 
    800, 600, 
    0, 
    Ogre::PF_R8G8B8, 
    Ogre::TU_RENDERTARGET);

  Ogre::RenderTexture* renderTexture = rttTex->getBuffer()->getRenderTarget();
  renderTexture->setAutoUpdated(false);

  // Create Scene Manager
  Ogre::SceneManager* ogreSceneMgr = ogreRoot->createSceneManager(Ogre::ST_GENERIC);

  // Create a new camera
  Ogre::Camera* ogreCamera = ogreSceneMgr->createCamera("Camera0");
  ogreCamera->setPosition(Ogre::Vector3(0, 0, 10));
  ogreCamera->lookAt(Ogre::Vector3(0, 0, -300));
  ogreCamera->setNearClipDistance(5);

  // Create a viewport
  Ogre::Viewport* vp = renderTexture->addViewport(ogreCamera);
  vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

  // Use the viewport to set the aspect ratio of the camera
  ogreCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

  // Add our model to our resources and index it
  Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media/packs/Sinbad.zip", "Zip");
  Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media/models/", "FileSystem");
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  // Set Scene Ambient Light.
  ogreSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

  // Create a new light.
  Ogre::Light* light = ogreSceneMgr->createLight("Light0");
  light->setPosition(20.0f, 80.0f, 50.0f);

  // Create an instance of our model and add it to the scene
  Ogre::Entity* ent = ogreSceneMgr->createEntity("Sinbad.mesh");
  Ogre::SceneNode* entNode = ogreSceneMgr->createSceneNode("Character0");
  entNode->attachObject(ent);
  ogreSceneMgr->getRootSceneNode()->addChild(entNode);
  entNode->setPosition(0, 0, 0);

  // Create an instance of the MyFrameListener Class and add it to the root object
  MyFrameListener* myListener = new MyFrameListener();
  ogreRoot->addFrameListener(myListener);

  // Create SFML texture and sprite
  sf::Texture sfTexture;
  sfTexture.create(800, 600);
  sf::Sprite sfSprite(sfTexture);

  // run the main loop
  bool running = true;
  while (running)
  {
    // handle events
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        // end the program
        running = false;
      }
      else if (event.type == sf::Event::Resized)
      {
        // adjust the viewport when the window is resized
      }
    }

    // Render Ogre to the texture
    renderTexture->update();
    renderTexture->copyContentsToMemory(Ogre::PixelBox(800, 600, 1, Ogre::PF_R8G8B8, sfTexture.getPixelsPtr()));

    // clear the window
    window.clear();

    // Draw the SFML sprite containing the Ogre texture
    window.draw(sfSprite);

    // end the current frame (internally swaps the front and back buffers)
    window.display();
  }

  // release resources...
  delete myListener;
  delete ogreRoot;

  return 0;
}


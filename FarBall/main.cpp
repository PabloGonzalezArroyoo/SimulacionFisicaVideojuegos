#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <chrono>
#include <thread>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "structure/states/GameStateMachine.h"
#include "structure/states/MainMenuState.h"
#include "structure/CollisionCallbacks.h"

vector<string> texts = {
	"Proyecto Final - Pablo Gonzalez Arroyo",
	"[ FARBALL ]",
	"Press SPACE to play",
	"",
	""
};

using namespace std;
using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

// VARIABLES PROPIAS
GameStateMachine* gsm = nullptr;
CollisionCallbacks callbacks;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	//sceneDesc.simulationEventCallback = &gContactReportCallback;
	sceneDesc.simulationEventCallback = &callbacks;
	gScene = gPhysics->createScene(sceneDesc);

	// Sistema de sólidos rígidos
	gsm = new GameStateMachine();
	gsm->pushState(new MainMenuState(gsm, gPhysics, gScene));
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	auto startTime = std::chrono::high_resolution_clock::now();

	PX_UNUSED(interactive);

	gScene->simulate(t);
	gsm->currentState()->update(t);
	gScene->fetchResults(true);
	//gsm->currentState()->refresh(t);

	//auto endTime = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double> elapsedSeconds = endTime - startTime;
	//double elapsedTime = elapsedSeconds.count();

	//// Comprobar si el frame ha ocurrido en menos tiempo que el framerate establecido
	//if (elapsedTime < 1.0f/ 120.0f) {
	//	// Parar la ejecución un tiempo concreto
	//	double sleepTime = 1.0f / 120.0f - elapsedTime;
	//	std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
	//}
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	delete gsm;

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	gsm->currentState()->keyPressed(toupper(key));
}

// Function called when a key is released
void keyRelease(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	gsm->currentState()->keyReleased(toupper(key));
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
	cout << "hola";
}


int main(int, const char*const*)
{
	#ifndef OFFLINE_EXECUTION 
		extern void renderLoop();
		renderLoop();
	#else
		static const PxU32 frameCount = 100;
		initPhysics(false);
		for(PxU32 i=0; i<frameCount; i++)
			stepPhysics(false);
		cleanupPhysics(false);
	#endif

	return 0;
}
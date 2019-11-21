
#include <cstdlib> 
#include <ctime> 
#include "AppClass.h"

using namespace Simplex;
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 1.0f, 25.0f), //Position
		vector3(0.0f, 0.0f, 0.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	m_pEntityMngr->AddEntity("Minecraft\\Steve.obj", "Steve");
	m_pEntityMngr->UsePhysicsSolver();
	
	//Ground
	for (int i = 0; i < 20; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Cube_" + std::to_string(i));

		vector3 v3Position = vector3(-25 + i * 3, -2, 0);
		matrix4 m4Position = glm::translate(v3Position);

		m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(2.0f, 0.5f, 2.0f)));
	}


	srand((unsigned)time(0));
	for (int j = 3; j < 400; j += 5)
	{
		for (int i = 0; i < 20; i++) {
			int random = (rand() % 100) + 1;

			if (random <= 30)
			{
				m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Cube_" + std::to_string(i));

				vector3 v3Position = vector3(-25 + i * 3, j, 0);
				matrix4 m4Position = glm::translate(v3Position);

				m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(2.0f, 0.5f, 2.0f)));
			}
		}
	}

	//Not using this method of platform generation
	for (int i = 0; i < 120; i++)
	{
		//m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Cube_" + std::to_string(i));
		//vector3 v3Position = vector3(glm::sphericalRand(50.0f));

		//v3Position.z = 0.0f;
		//matrix4 m4Position = glm::translate(v3Position);
		//m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(2.0f)));

		//m_pEntityMngr->UsePhysicsSolver();
		//m_pEntityMngr->SetMass(2);
		//m_pEntityMngr->SetMass(i+1);
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();


	MyEntity* steve = MyEntity::GetEntity("Steve");

	if (steve->GetPosition().x < -20) {
		steve->SetPosition(vector3(20.0, steve->GetPosition().y, steve->GetPosition().z));
	}
	
	if (steve->GetPosition().x > 20) {
		steve->SetPosition(vector3(-20.0, steve->GetPosition().y, steve->GetPosition().z));
	}

	float playerY = steve->GetPosition().y;

	if (m_pCameraMngr->GetPosition().y < playerY + 2.0f) {
		m_pCameraMngr->SetPositionTargetAndUpward(
			vector3(0.0f, playerY + 2.0f, 20.0f),
			vector3(0.0f, playerY, 0.0f),
			AXIS_Y);
	}
	
	//Set the model matrix for the main object
	//m_pEntityMngr->SetModelMatrix(m_m4Steve, "Steve");

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
	//m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();

	//draw gui,
	DrawGUI();

	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//Release MyEntityManager
	MyEntityManager::ReleaseInstance();

	//release GUI
	ShutdownGUI();
}
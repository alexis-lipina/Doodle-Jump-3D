
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
	for (int i = 0; i < 40; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "aCube_" + std::to_string(i));
		vector3 v3Position = vector3(-25 + i * 3, -3, 0);

		matrix4 m4Position = glm::translate(v3Position);

		m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(4.0f, 0.5f, 2.0f)));
		MyEntity::GetEntity("aCube_" + std::to_string(i))->GetRigidBody()->m_bFixed = true;
		
	}

	//Spawn random blocks
	for (int i = 0; i < m_pGM->m_iRandomBlocks; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "bCube_" + std::to_string(i));
		vector3 v3Position = m_pGM->GenerateRandomPositionInChunk();
		matrix4 m4Position = glm::translate(v3Position);
		m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(2.0f, 0.5f, 2.0f)));
		MyEntity::GetEntity("bCube_" + std::to_string(i))->GetRigidBody()->m_bFixed = true;

		if (v3Position.y > 30.0f) {
			m_pEntityMngr->AddEntity("Minecraft\\Creeper.obj", "Creeper" + std::to_string(i));
			m_pEntityMngr->UsePhysicsSolver(true, "Creeper" + std::to_string(i));

			MyEntity::GetEntity("Creeper" + std::to_string(i))->GetRigidBody()->m_bFixed = false;
			MyEntity::GetEntity("Creeper" + std::to_string(i))->SetPosition(v3Position + vector3(0, 5.0, 0));
		}
		
	}

	//spawn path blocks
	for (int i = 0; i < 100; i++) {

		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "cCube_" + std::to_string(i));

		vector3 v3Position = m_pGM->GetPathBlockPosition();
		matrix4 m4Position = glm::translate(v3Position);

		m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(2.0f, 0.5f, 2.0f)));
		MyEntity::GetEntity("cCube_" + std::to_string(i))->GetRigidBody()->m_bFixed = true;

		//spawn random block around path blocks
		if (i % 3 == 0) {
			m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "dCube_" + std::to_string(i));
			matrix4 m4Position = glm::translate(m_pGM->GenerateRandomPositionAroundPathBlock());
			m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(2.0f, 0.5f, 2.0f)));
			MyEntity::GetEntity("dCube_" + std::to_string(i))->GetRigidBody()->m_bFixed = true;
		}

		m_pGM->NextPathBlock();
	}

	MyEntity::GetEntity("Steve")->GetRigidBody()->m_bFixed = false;

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

	//Get Player Entity
	MyEntity* steve = MyEntity::GetEntity("Steve");

	//Wrap Player When Out of Bound
	if (steve->GetPosition().x < -20) {
		steve->SetPosition(vector3(20.0, steve->GetPosition().y, steve->GetPosition().z));
	}
	if (steve->GetPosition().x > 20) {
		steve->SetPosition(vector3(-20.0, steve->GetPosition().y, steve->GetPosition().z));
	}

	//Get Player's Y Position
	float playerY = steve->GetPosition().y;

	//Player will randomly collide with creepers for no reason so the player is invincible at the start of the game
	if (playerY < 10.0) {
		MyEntity::GetEntity("Steve")->GetRigidBody()->m_bFixed = false;
	}

	//Move Camera According to Player's Y Position
	if (m_pCameraMngr->GetPosition().y < playerY + 1.0f) {
		m_pCameraMngr->SetPositionTargetAndUpward(
			vector3(0.0f, playerY + 1.0f, 20.0f),
			vector3(0.0f, playerY, 0.0f),
			AXIS_Y);
	}

	if (playerY < m_pCameraMngr->GetPosition().y - 15)
	{
		m_bRunning = false;
	}

	//Platform Generation

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
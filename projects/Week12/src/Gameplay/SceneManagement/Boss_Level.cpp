#include "Boss_Level.h"
#include "SceneManager.h"

// Gameplay
#include "Gameplay/MeshResource.h"

// Components
#include "Gameplay/Components/RenderComponent.h"
#include "Gameplay/Components/AnimatorComponent.h"
#include "Gameplay/Components/TriggerVolumeEnterBehaviour.h"

// Physics
#include "Gameplay/Physics/RigidBody.h"
#include "Gameplay/Physics/Colliders/BoxCollider.h"
#include "Gameplay/Physics/TriggerVolume.h"

// Utils
#include "Utils/ResourceManagement/Resources.h"
#include "Utils/GlmDefines.h"
#include <GLFW/glfw3.h>

using namespace Gameplay::Physics;

bool Boss_Level::PlayOnLoad = true;

Scene::Sptr Boss_Level::Load(GLFWwindow* window)
{
	// TO BE MOVED TO GAME SETTINGS
	int PHYSICAL_MASK = 0xFFFFFFFF;
	int PHYSICAL_GROUP = 0x01;
	int SHADOW_MASK = 0xFFFFFFFE;
	int SHADOW_GROUP = 0x02;
	int NO_MASK = 0xFFFFFFFD;
	int NO_GROUP = 0x03;

	/////////////////////////////////////////////////////////
	//					  LIGHTS
	/////////////////////////////////////////////////////////

	SceneManager::GetCurrentScene()->Lights.resize(8);
	SceneManager::GetCurrentScene()->Lights[0].Position = glm::vec3(0.0f, 12.0f, 13.0f);
	SceneManager::GetCurrentScene()->Lights[0].Color = glm::vec3(1.0f, 1.0f, 1.0f);
	SceneManager::GetCurrentScene()->Lights[0].Range = 100.0f;

	/////////////////////////////////////////////////////////
	//					  CONTROLLER
	/////////////////////////////////////////////////////////

	GameObject::Sptr camera = SceneManager::GetCurrentScene()->CreateGameObject("Main Camera");
	{
		camera->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
		camera->SetRotation(glm::vec3(45.0f, 0.0f, 0.0f));
		//camera->LookAt(glm::vec3(0.0f));			

		Camera::Sptr cam = camera->Add<Camera>();
		cam->SetFovDegrees(60.0f);
		SceneManager::GetCurrentScene()->MainCamera = cam;
	}

	GameObject::Sptr body = SceneManager::GetCurrentScene()->CreateGameObject("Body");
	{
		// Set position in the SceneManager::GetCurrentScene()
		body->SetPosition(glm::vec3(-4.0f, 17.0f, 0.0f));
		body->SetRotation(glm::vec3(90.f, 0.0f, -90.0f));
		body->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));

		RenderComponent::Sptr renderer = body->Add<RenderComponent>();

		renderer->SetMesh(Resources::GetMesh("Character"));
		renderer->SetMaterial(Resources::GetMaterial("Character"));

		AnimatorComponent::Sptr animator = body->Add<AnimatorComponent>();
		std::vector<MeshResource::Sptr> walkFrames;
		animator->AddAnimation("Walk", Resources::GetAnimation("Character Walk"));
		animator->AddAnimation("Idle", Resources::GetAnimation("Character Idle"));

		animator->SetRenderer(*renderer);
		animator->SetAnimation("Idle");
		//animator->SetFrames(std::move(frames));
		animator->SetLooping(true);
		animator->SetPause(false);
		animator->SetSpeed(4.0f);

		//std::cout << std::to_string(frames.size()) << std::endl;

		RigidBody::Sptr physics = body->Add<RigidBody>(RigidBodyType::Dynamic);
		BoxCollider::Sptr collider = BoxCollider::Create();
		physics->AddCollider(collider);
		physics->SetCollisionGroup(PHYSICAL_GROUP);
		physics->SetCollisionMask(PHYSICAL_MASK);

		TriggerVolume::Sptr volume = body->Add<TriggerVolume>();
		BoxCollider::Sptr i_collider = BoxCollider::Create();
		i_collider->SetPosition(i_collider->GetPosition() + glm::vec3(0.0f, 0.0f, -2.5f));
		volume->AddCollider(i_collider);
		TriggerVolumeEnterBehaviour::Sptr trigger = body->Add<TriggerVolumeEnterBehaviour>();

		body->Add<HealthComponent>(100.0f);
	}

	GameObject::Sptr shadow = SceneManager::GetCurrentScene()->CreateGameObject("Shadow");
	{
		// Set position in the SceneManager::GetCurrentScene()
		shadow->SetPosition(glm::vec3(4.0f, 17.0f, 0.0f));
		shadow->SetRotation(glm::vec3(90.f, 0.0f, -90.0f));
		shadow->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));

		// Create and attach a renderer for the monkey
		RenderComponent::Sptr renderer = shadow->Add<RenderComponent>();
		renderer->SetMesh(Resources::GetMesh("Character"));
		renderer->SetMaterial(Resources::GetMaterial("Shadow"));

		AnimatorComponent::Sptr animator = shadow->Add<AnimatorComponent>();
		animator->AddAnimation("Walk", Resources::GetAnimation("Character Walk"));
		animator->AddAnimation("Idle", Resources::GetAnimation("Character Idle"));

		animator->SetRenderer(*renderer);
		animator->SetAnimation("Idle");
		//animator->SetFrames(std::move(frames));
		animator->SetLooping(true);
		animator->SetPause(false);
		animator->SetSpeed(4.0f);

		// Add a dynamic rigid body to this monkey
		RigidBody::Sptr physics = shadow->Add<RigidBody>(RigidBodyType::Dynamic);
		BoxCollider::Sptr collider = BoxCollider::Create();
		physics->AddCollider(collider);
		physics->SetCollisionGroup(SHADOW_GROUP);
		physics->SetCollisionMask(SHADOW_MASK);


		shadow->Add<HealthComponent>(100.0f);
	}

	SceneManager::GetCurrentScene()->PC.Initialize(*body, *shadow, *camera, SceneManager::GetCurrentScene()->Lights[0], *body->Get<TriggerVolume>());

	/////////////////////////////////////////////////////////
	//					  ENVIRONMENT
	/////////////////////////////////////////////////////////

	// Set up all our sample objects
	GameObject::Sptr floor = SceneManager::GetCurrentScene()->CreateGameObject("Floor");
	{
		MeshResource::Sptr tiledMesh = ResourceManager::CreateAsset<MeshResource>();
		tiledMesh->AddParam(MeshBuilderParam::CreatePlane(ZERO, UNIT_Z, UNIT_X, glm::vec2(100.0f), glm::vec2(8.0f)));
		tiledMesh->GenerateMesh();

		// Create and attach a RenderComponent to the object to draw our mesh
		RenderComponent::Sptr renderer = floor->Add<RenderComponent>();
		renderer->SetMesh(tiledMesh);
		renderer->SetMaterial(Resources::GetMaterial("Stone Slab"));

		RigidBody::Sptr physics = floor->Add<RigidBody>(/*static by default*/);
		physics->AddCollider(BoxCollider::Create(glm::vec3(100.0f, 100.0f, 1.5f)))->SetPosition({ 0,0,-1 });
		physics->SetCollisionGroupMulti(PHYSICAL_GROUP | SHADOW_GROUP);
		physics->SetCollisionMask(PHYSICAL_MASK | SHADOW_MASK);
	}

	/////////////////////////////////////////////////////////

	// Call SceneManager::GetCurrentScene() awake to start up all of our components
	SceneManager::GetCurrentScene()->Window = window;
	SceneManager::GetCurrentScene()->Awake();

	// Save the asset manifest for all the resources we just loaded
	ResourceManager::SaveManifest("manifest.json");
	// Save the SceneManager::GetCurrentScene() to a JSON file
	SceneManager::GetCurrentScene()->Save("Boss_Level.json");

	return nullptr;
}
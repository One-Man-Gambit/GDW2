#include "Gameplay/Components/TriggerVolumeEnterBehaviour.h"
#include "Gameplay/Components/ComponentManager.h"
#include "Gameplay/GameObject.h"

TriggerVolumeEnterBehaviour::TriggerVolumeEnterBehaviour() :
	IComponent()
{ }
TriggerVolumeEnterBehaviour::~TriggerVolumeEnterBehaviour() = default;

void TriggerVolumeEnterBehaviour::Awake()
{ }

void TriggerVolumeEnterBehaviour::Update(float dt)
{
	if (numberOfCollisions > 0 && onTriggerStayEvent) {
		onTriggerStayEvent();
	}
}

void TriggerVolumeEnterBehaviour::OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody>& body)
{
	numberOfCollisions += 1;

	if (numberOfCollisions > 0 && onTriggerEnterEvent) {
		onTriggerEnterEvent();
	}

	//LOG_INFO("Body has entered {} trigger volume: {}", GetGameObject()->Name, body->GetGameObject()->Name);
	//_playerInTrigger = true;
}

void TriggerVolumeEnterBehaviour::OnTriggerVolumeLeaving(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) 
{
	numberOfCollisions -= 1;

	if (numberOfCollisions == 0 && onTriggerExitEvent) {
		onTriggerExitEvent();
	}
	
	//LOG_INFO("Body has left {} trigger volume: {}", GetGameObject()->Name, body->GetGameObject()->Name);
	//_playerInTrigger = false;
}

void TriggerVolumeEnterBehaviour::RenderImGui() { }

nlohmann::json TriggerVolumeEnterBehaviour::ToJson() const {
	return { };
}

TriggerVolumeEnterBehaviour::Sptr TriggerVolumeEnterBehaviour::FromJson(const nlohmann::json& blob) {
	TriggerVolumeEnterBehaviour::Sptr result = std::make_shared<TriggerVolumeEnterBehaviour>();
	return result;
}

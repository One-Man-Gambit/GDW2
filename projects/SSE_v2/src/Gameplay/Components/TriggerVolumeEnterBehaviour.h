#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/TriggerVolume.h"
#include "Gameplay/Components/RenderComponent.h"
#include "Gameplay/Physics/TriggerVolume.h"

/// <summary>
/// Provides an example behaviour that uses some of the trigger interface to change the material
/// of the game object the component is attached to when entering or leaving a trigger
/// </summary>
class TriggerVolumeEnterBehaviour : public Gameplay::IComponent {

public:
	std::vector<std::function<void()>> onTriggerEnterEvent;
	std::vector<std::function<void()>> onTriggerStayEvent;
	std::vector<std::function<void()>> onTriggerExitEvent;

public:
	typedef std::shared_ptr<TriggerVolumeEnterBehaviour> Sptr;
	TriggerVolumeEnterBehaviour();
	virtual ~TriggerVolumeEnterBehaviour();

	// Inherited from IComponent
	virtual void Awake() override;
	virtual void Update(float dt) override;

	virtual void OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) override;
	virtual void OnTriggerVolumeLeaving(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) override;
	virtual void RenderImGui() override;
	virtual nlohmann::json ToJson() const override;
	static TriggerVolumeEnterBehaviour::Sptr FromJson(const nlohmann::json& blob);
	MAKE_TYPENAME(TriggerVolumeEnterBehaviour);

protected:
	int numberOfCollisions = 0;
	//bool _playerInTrigger;
};
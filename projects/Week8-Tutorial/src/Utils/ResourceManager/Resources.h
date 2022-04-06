#pragma once

#include "Gameplay/MeshResource.h"
#include "Gameplay/Material.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/ShaderProgram.h"
#include "Audio/AudioResource.h"

#include "ResourceManager.h"

#include "Audio/AudioManager.h"

using namespace Gameplay;

class Resources {
public:
	static Resources& shared_instance() { static Resources resources; return resources; }
	
#pragma region Unused/Unimplemented Method for Searching Assets
	
	/* /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		The idea is that we can use enum classes to store a reference to our assets and use them in drop-down lists to find
		what assets are available when making a call to an asset.  This would make it so we don't have to memorize every 
		asset that is available to us, and instead can just do a search from our dropdown list.
	*/ /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	/*
		static enum class Shaders {
			Basic, Reflective, Specular, Foliage, Toon, Displacement, TangentSpace, MultiTexture
		};

		static enum class Textures {
			StoneWall, StoneSlab, StoneSlab2, DarkPineTree, LightPineTree, TurretProjectile, Key, Rock, StandingTorch, GraveStone, Enemy,
			Character, Shadow, CircleCage, BoxCage, LongCage, SmallCage, UCage, PressurePlate, Turret, Door, SpikeTrap, Relic1, Relic2,
			Relic3, Relic4, Relic5, MenuGloss, MenuGlossReverse
		};

		static enum class Materials {
			StoneWall, PressurePlate, StoneSlab, SmallCage, TurretProjectile, Turret, Door, Character, SpikeTrap, Relic1, Relic2, Relic3,
			Relic4, Relic5, Shadow, DarkPineTree, LightPineTree, StandingTorch, Rock, CircleCage, BoxCage, LongCage, UCage, GraveStone,
			Enemy
		};

		static enum class Meshes {
			Character, DarkPineTree, LightPineTree, GraveStone, Key, StoneWall, TurretProjectile, StandingTorch, StoneSlab, Enemy, CircleCage,
			BoxCage, LongCage, SmallCage, UCage, Relic1, Relic2, Relic3, Relic4, Relic5, PressurePlate, Turret, Door, SpikeTrap
		};

		static enum class Animations {
			CharacterWalk, CharacterIdle, Turret
		};
		*/

#pragma endregion	

protected:
	Resources() {};

protected:
	std::map<std::string, ShaderProgram::Sptr>								shaders;
	std::map<std::string, MeshResource::Sptr>						meshes;
	std::map<std::string, Texture2D::Sptr>							textures;
	std::map<std::string, Material::Sptr>							materials;
	std::map<std::string, std::vector<MeshResource::Sptr>>			animations;
	std::map<std::string, AudioResource::Sptr>						sounds;

public:
	
	void Initialize()
	{

#pragma region Shader Resources

			shaders.emplace("Reflective", ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string> {
				{ ShaderPartType::Vertex, "shaders/vertex_shaders/basic.glsl" },
				{ ShaderPartType::Fragment, "shaders/fragment_shaders/frag_environment_reflective.glsl" }
			}));
			shaders.emplace("Basic", ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string> {
				{ ShaderPartType::Vertex, "shaders/vertex_shaders/basic.glsl" },
				{ ShaderPartType::Fragment, "shaders/fragment_shaders/frag_blinn_phong_textured.glsl" }
			}));
			shaders.emplace("Specular", ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string> {
				{ ShaderPartType::Vertex, "shaders/vertex_shaders/basic.glsl" },
				{ ShaderPartType::Fragment, "shaders/fragment_shaders/textured_specular.glsl" }
			}));
			shaders.emplace("Foliage", ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string> {
				{ ShaderPartType::Vertex, "shaders/vertex_shaders/foliage.glsl" },
				{ ShaderPartType::Fragment, "shaders/fragment_shaders/screendoor_transparency.glsl" }
			}));
			shaders.emplace("Toon", ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string> {
				{ ShaderPartType::Vertex, "shaders/vertex_shaders/basic.glsl" },
				{ ShaderPartType::Fragment, "shaders/fragment_shaders/toon_shading.glsl" }
			}));
			shaders.emplace("Displacement", ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string> {
				{ ShaderPartType::Vertex, "shaders/vertex_shaders/displacement_mapping.glsl" },
				{ ShaderPartType::Fragment, "shaders/fragment_shaders/frag_tangentspace_normal_maps.glsl" }
			}));
			shaders.emplace("Tangent Space", ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string> {
				{ ShaderPartType::Vertex, "shaders/vertex_shaders/basic.glsl" },
				{ ShaderPartType::Fragment, "shaders/fragment_shaders/frag_tangentspace_normal_maps.glsl" }
			}));
			shaders.emplace("Multi-Texture", ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string> {
				{ ShaderPartType::Vertex, "shaders/vertex_shaders/vert_multitextured.glsl" },
				{ ShaderPartType::Fragment, "shaders/fragment_shaders/frag_multitextured.glsl" }
			}));
			shaders.emplace("Animation", ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string> {
				{ ShaderPartType::Vertex, "shaders/vertex_Shaders/animation.glsl" },
				{ ShaderPartType::Fragment, "shaders/fragment_shaders/frag_blinn_phong_textured.glsl" }
			}));
	
#pragma endregion

#pragma region Texture Resources

			textures.emplace("Stone Wall", ResourceManager::CreateAsset<Texture2D>("textures/StoneWallUVs.png"));
			textures.emplace("Stone Slab 2", ResourceManager::CreateAsset<Texture2D>("textures/StoneSlabsTexture.png"));
			textures.emplace("Dark Pine Tree", ResourceManager::CreateAsset<Texture2D>("textures/DarkPineTreeUVS.png"));
			textures.emplace("Light Pine Tree", ResourceManager::CreateAsset<Texture2D>("textures/LightTreeTextureUVS.png"));
			textures.emplace("Turret Projectile", ResourceManager::CreateAsset<Texture2D>("textures/TurretProjectileUVS.png"));
			textures.emplace("Key", ResourceManager::CreateAsset<Texture2D>("textures/KeyTextureUVS.png"));
			textures.emplace("Standing Torch", ResourceManager::CreateAsset<Texture2D>("textures/TorchUVS.png"));
			textures.emplace("Grave Stone", ResourceManager::CreateAsset<Texture2D>("textures/GraveStoneUVS.png"));
			textures.emplace("Character", ResourceManager::CreateAsset<Texture2D>("textures/CharacterUVS.png"));
			textures.emplace("Shadow", ResourceManager::CreateAsset<Texture2D>("textures/ShadowUVS.png"));
			textures.emplace("Circle Cage", ResourceManager::CreateAsset<Texture2D>("textures/CircleCageUVS.png"));
			textures.emplace("Box Cage", ResourceManager::CreateAsset<Texture2D>("textures/BoxcageUVS.png"));
			textures.emplace("Long Cage", ResourceManager::CreateAsset<Texture2D>("textures/LongCageUVS.png"));
			textures.emplace("Small Cage", ResourceManager::CreateAsset<Texture2D>("textures/SmallCageUVS.png"));
			textures.emplace("U Cage", ResourceManager::CreateAsset<Texture2D>("textures/UCageUVS.png"));
			textures.emplace("Pressure Plate", ResourceManager::CreateAsset<Texture2D>("textures/PressurePlateUVs.png"));
			textures.emplace("Turret", ResourceManager::CreateAsset<Texture2D>("textures/TurretUVS.png"));
			textures.emplace("Door", ResourceManager::CreateAsset<Texture2D>("textures/DoorUVs.png"));
			textures.emplace("Spike Trap", ResourceManager::CreateAsset<Texture2D>("textures/SpikedTrapUVS.png"));
			textures.emplace("Relic 1", ResourceManager::CreateAsset<Texture2D>("textures/StoneTablet1UVS.png"));
			textures.emplace("Relic 2", ResourceManager::CreateAsset<Texture2D>("textures/StoneTablet2UVS.png"));
			textures.emplace("Relic 3", ResourceManager::CreateAsset<Texture2D>("textures/StoneTablet3UVS.png"));
			textures.emplace("Relic 4", ResourceManager::CreateAsset<Texture2D>("textures/StoneTablet4UVS.png"));
			textures.emplace("Relic 5", ResourceManager::CreateAsset<Texture2D>("textures/StoneTablet5UVS.png"));
			textures.emplace("Menu Gloss", ResourceManager::CreateAsset<Texture2D>("textures/MenuGloss.png"));
			textures.emplace("Menu Gloss Reverse", ResourceManager::CreateAsset<Texture2D>("textures/MenuGlossReverse.png"));
			textures.emplace("Character Dagger", ResourceManager::CreateAsset<Texture2D>("textures/DaggerTexture.png"));
			textures.emplace("Health Orb", ResourceManager::CreateAsset<Texture2D>("textures/HealthTexture.png"));
			textures.emplace("Wall Grate", ResourceManager::CreateAsset<Texture2D>("textures/WallGrateUVS.png"));
			textures.emplace("Floor Grate", ResourceManager::CreateAsset<Texture2D>("textures/FloorGrateUVS.png"));
			textures.emplace("Large Candle", ResourceManager::CreateAsset<Texture2D>("textures/LargeCandleTexture.png"));
			textures.emplace("Brown", ResourceManager::CreateAsset<Texture2D>("textures/Brown.png"));
			textures.emplace("Gray", ResourceManager::CreateAsset<Texture2D>("textures/Gray.png"));
			textures.emplace("White", ResourceManager::CreateAsset<Texture2D>("textures/White.png"));
			textures.emplace("Wall2", ResourceManager::CreateAsset<Texture2D>("textures/Wall_Tex2.png"));
			textures.emplace("Wall_Tex3", ResourceManager::CreateAsset<Texture2D>("textures/Wall_Tex3.png"));
			textures.emplace("Wall_Tex4", ResourceManager::CreateAsset<Texture2D>("textures/Wall_Tex4.png"));
			textures.emplace("Wall_Tex5", ResourceManager::CreateAsset<Texture2D>("textures/Wall_Tex5.png"));
			textures.emplace("ShieldTex", ResourceManager::CreateAsset<Texture2D>("textures/ShieldTexture.png"));
			textures.emplace("StaffTex", ResourceManager::CreateAsset<Texture2D>("textures/StaffTexture.png"));
			textures.emplace("SwordTex", ResourceManager::CreateAsset<Texture2D>("textures/GoblinSwordUV.png"));
			textures.emplace("RockPileTex", ResourceManager::CreateAsset<Texture2D>("textures/Rock3Textures.png"));
			textures.emplace("LeverTex", ResourceManager::CreateAsset<Texture2D>("textures/LeverTextures.png"));
			textures.emplace("Intact Pillar", ResourceManager::CreateAsset<Texture2D>("textures/PillarUV.png"));
			textures.emplace("Damaged Pillar", ResourceManager::CreateAsset<Texture2D>("textures/DamagedPillarUV.png"));
			textures.emplace("Destroyed Pillar", ResourceManager::CreateAsset<Texture2D>("textures/DestroyedPillarUV.png"));
			textures.emplace("Brown", ResourceManager::CreateAsset<Texture2D>("textures/Brown.png"));
			textures.emplace("Gray", ResourceManager::CreateAsset<Texture2D>("textures/Gray.png"));
			textures.emplace("White", ResourceManager::CreateAsset<Texture2D>("textures/White.png"));
			textures.emplace("GrassTex", ResourceManager::CreateAsset<Texture2D>("textures/Grass.png"));
			textures.emplace("StoneTex", ResourceManager::CreateAsset<Texture2D>("textures/Stone.png"));
			textures.emplace("AbyssTex", ResourceManager::CreateAsset<Texture2D>("textures/Abyss.png"));
			textures.emplace("BarrelTex", ResourceManager::CreateAsset<Texture2D>("textures/BarrelTexture.png"));
			textures.emplace("BucketTex", ResourceManager::CreateAsset<Texture2D>("textures/Bucket_Tex.png"));
			textures.emplace("KegTex", ResourceManager::CreateAsset<Texture2D>("textures/Keg_Tex.png"));

			//USER INTERFACE
			textures.emplace("Menu Gloss", ResourceManager::CreateAsset<Texture2D>("textures/MenuGloss.png"));
			textures.emplace("Menu Gloss Reverse", ResourceManager::CreateAsset<Texture2D>("textures/MenuGlossReverse.png"));
			textures.emplace("Upper", ResourceManager::CreateAsset<Texture2D>("textures/UpperGraphic.png"));
			textures.emplace("Lower", ResourceManager::CreateAsset<Texture2D>("textures/LowerGraphic.png"));
			textures.emplace("Slider", ResourceManager::CreateAsset<Texture2D>("textures/Slider.png"));
			textures.emplace("SliderBar", ResourceManager::CreateAsset<Texture2D>("textures/SliderBar.png"));
			textures.emplace("Selector", ResourceManager::CreateAsset<Texture2D>("textures/Selector.png"));
			textures.emplace("New", ResourceManager::CreateAsset<Texture2D>("textures/NewGame.png"));
			textures.emplace("Options", ResourceManager::CreateAsset<Texture2D>("textures/Options.png"));
			textures.emplace("ChooseLevel", ResourceManager::CreateAsset<Texture2D>("textures/ChooseLevel.png"));
			textures.emplace("Credits", ResourceManager::CreateAsset<Texture2D>("textures/Credits.png"));
			textures.emplace("Exit", ResourceManager::CreateAsset<Texture2D>("textures/ExitGame.png"));
			textures.emplace("R", ResourceManager::CreateAsset<Texture2D>("textures/Resume.png"));
			textures.emplace("Re", ResourceManager::CreateAsset<Texture2D>("textures/Restart.png"));
			textures.emplace("Return", ResourceManager::CreateAsset<Texture2D>("textures/ReturntoMainMenu.png"));
			textures.emplace("TitleT", ResourceManager::CreateAsset<Texture2D>("textures/Title.png"));
			textures.emplace("Pause", ResourceManager::CreateAsset<Texture2D>("textures/Paused.png"));
			textures.emplace("L1", ResourceManager::CreateAsset<Texture2D>("textures/Level1.png"));
			textures.emplace("L2", ResourceManager::CreateAsset<Texture2D>("textures/Level2.png"));
			textures.emplace("L3", ResourceManager::CreateAsset<Texture2D>("textures/Level3.png"));
			textures.emplace("BL", ResourceManager::CreateAsset<Texture2D>("textures/BossLevel.png"));
			textures.emplace("New", ResourceManager::CreateAsset<Texture2D>("textures/Brightness.png"));
			textures.emplace("Volume", ResourceManager::CreateAsset<Texture2D>("textures/Volume.png"));
			textures.emplace("U.I", ResourceManager::CreateAsset<Texture2D>("textures/U.ISize.png"));
			textures.emplace("CP", ResourceManager::CreateAsset<Texture2D>("textures/CreditsPage.png"));
			textures.emplace("Options", ResourceManager::CreateAsset<Texture2D>("textures/GameTitleIntro.png"));
			textures.emplace("Controls", ResourceManager::CreateAsset<Texture2D>("textures/Controls.png"));
			textures.emplace("LS", ResourceManager::CreateAsset<Texture2D>("textures/LogoScreen.png"));
			textures.emplace("Lose", ResourceManager::CreateAsset<Texture2D>("textures/LoseScreen.png"));
			textures.emplace("CharacterH", ResourceManager::CreateAsset<Texture2D>("textures/CharacterHealth.png"));
			textures.emplace("ShadowH", ResourceManager::CreateAsset<Texture2D>("textures/AntiformHealth.png"));

#pragma endregion

#pragma region Materials
			Material::Sptr stoneWallMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				stoneWallMat->Name = "Stone Wall";
				stoneWallMat->Set("u_Material.Diffuse", GetTexture("Stone Wall"));
				stoneWallMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Stone Wall", std::move(stoneWallMat));
			}

			Material::Sptr pressurePlateMaterial = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				pressurePlateMaterial->Name = "Pressure Plate";
				pressurePlateMaterial->Set("u_Material.Diffuse", GetTexture("Pressure Plate"));
				pressurePlateMaterial->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Pressure Plate", std::move(pressurePlateMaterial));
			}

			Material::Sptr stoneSlabMaterial = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				stoneSlabMaterial->Name = "Stone Slab";
				stoneSlabMaterial->Set("u_Material.Diffuse", GetTexture("Stone Slab 2"));
				stoneSlabMaterial->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Stone Slab", std::move(stoneSlabMaterial));
			}

			Material::Sptr sCageMaterial = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				sCageMaterial->Name = "Small Cage";
				sCageMaterial->Set("u_Material.Diffuse", GetTexture("Small Cage"));
				sCageMaterial->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Small Cage", std::move(sCageMaterial));
			}

			Material::Sptr TurretProjMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				TurretProjMat->Name = "Turret Projectile";
				TurretProjMat->Set("u_Material.Diffuse", GetTexture("Turret Projectile"));
				TurretProjMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Turret Projectile", std::move(TurretProjMat));
			}

			Material::Sptr turretMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				turretMat->Name = "Turret";
				turretMat->Set("u_Material.Diffuse", GetTexture("Turret"));
				turretMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Turret", std::move(turretMat));
			}

			Material::Sptr doorMat = ResourceManager::CreateAsset<Material>(GetShader("Animation"));
			{
				doorMat->Name = "Door";
				doorMat->Set("u_Material.Diffuse", GetTexture("Door"));
				doorMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Door", std::move(doorMat));
			}

			Material::Sptr characterMat = ResourceManager::CreateAsset<Material>(GetShader("Animation"));
			{
				characterMat->Name = "Character";
				characterMat->Set("u_Material.Diffuse", GetTexture("Character"));
				characterMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Character", std::move(characterMat));
			}

			Material::Sptr spikeTrapMat = ResourceManager::CreateAsset<Material>(GetShader("Animation"));
			{
				spikeTrapMat->Name = "Spike Trap";
				spikeTrapMat->Set("u_Material.Diffuse", GetTexture("Spike Trap"));
				spikeTrapMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Spike Trap", std::move(spikeTrapMat));
			}

			//Symbol Materials
			Material::Sptr symbol1Mat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				symbol1Mat->Name = "Relic 1";
				symbol1Mat->Set("u_Material.Diffuse", GetTexture("Relic 1"));
				symbol1Mat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Relic 1", std::move(symbol1Mat));
			}
			Material::Sptr symbol2Mat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				symbol2Mat->Name = "Relic 2";
				symbol2Mat->Set("u_Material.Diffuse", GetTexture("Relic 2"));
				symbol2Mat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Relic 2", std::move(symbol2Mat));
			}
			Material::Sptr symbol3Mat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				symbol3Mat->Name = "Relic 3";
				symbol3Mat->Set("u_Material.Diffuse", GetTexture("Relic 3"));
				symbol3Mat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Relic 3", std::move(symbol3Mat));
			}
			Material::Sptr symbol4Mat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				symbol4Mat->Name = "Relic 4";
				symbol4Mat->Set("u_Material.Diffuse", GetTexture("Relic 4"));
				symbol4Mat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Relic 4", std::move(symbol4Mat));
			}
			Material::Sptr symbol5Mat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				symbol5Mat->Name = "Relic 5";
				symbol5Mat->Set("u_Material.Diffuse", GetTexture("Relic 5"));
				symbol5Mat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Relic 5", std::move(symbol5Mat));
			}

			Material::Sptr shadowMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				shadowMat->Name = "Shadow";
				shadowMat->Set("u_Material.Diffuse", GetTexture("Shadow"));
				shadowMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Shadow", std::move(shadowMat));
			}
			//Tree Materials
			Material::Sptr darkTreeMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				darkTreeMat->Name = "Dark Pine Tree";
				darkTreeMat->Set("u_Material.Diffuse", GetTexture("Dark Pine Tree"));
				darkTreeMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Dark Pine Tree", std::move(darkTreeMat));
			}
			Material::Sptr lightTreeMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				lightTreeMat->Name = "Light Pine Tree";
				lightTreeMat->Set("u_Material.Diffuse", GetTexture("Light Pine Tree"));
				lightTreeMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Light Pine Tree", std::move(lightTreeMat));
			}

			Material::Sptr standingTorchMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				standingTorchMat->Name = "Standing Torch";
				standingTorchMat->Set("u_Material.Diffuse", GetTexture("Standing Torch"));
				standingTorchMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Standing Torch", std::move(standingTorchMat));
			}

			Material::Sptr boxCageMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				boxCageMat->Name = "Box Cage";
				boxCageMat->Set("u_Material.Diffuse", GetTexture("Box Cage"));
				boxCageMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Box Cage", std::move(boxCageMat));
			}
			Material::Sptr circleCageMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				circleCageMat->Name = "Circle Cage";
				circleCageMat->Set("u_Material.Diffuse", GetTexture("Circle Cage"));
				circleCageMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Circle Cage", std::move(circleCageMat));
			}
			Material::Sptr longCageMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				longCageMat->Name = "Long Cage";
				longCageMat->Set("u_Material.Diffuse", GetTexture("Long Cage"));
				longCageMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Long Cage", std::move(longCageMat));
			}
			Material::Sptr uCageMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				uCageMat->Name = "U Cage";
				uCageMat->Set("u_Material.Diffuse", GetTexture("U Cage"));
				uCageMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("U Cage", std::move(uCageMat));
			}

			Material::Sptr graveStoneMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				graveStoneMat->Name = "Grave Stone";
				graveStoneMat->Set("u_Material.Diffuse", GetTexture("Grave Stone"));
				graveStoneMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Grave Stone", std::move(graveStoneMat));
			}

			Material::Sptr dagger = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				dagger->Name = "Character Dagger";
				dagger->Set("u_Material.Diffuse", GetTexture("Character Dagger"));
				dagger->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Character Dagger", std::move(dagger));
			}

			Material::Sptr Orb = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				Orb->Name = "Health Orb";
				Orb->Set("u_Material.Diffuse", GetTexture("Health Orb"));
				Orb->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Health Orb", std::move(Orb));
			}

			Material::Sptr WGrate = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				WGrate->Name = "Wall Grate";
				WGrate->Set("u_Material.Diffuse", GetTexture("Wall Grate"));
				WGrate->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Wall Grate", std::move(WGrate));
			}


			Material::Sptr FGrate = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				FGrate->Name = "Floor Grate";
				FGrate->Set("u_Material.Diffuse", GetTexture("Floor Grate"));
				FGrate->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Floor Grate", std::move(FGrate));
			}

			Material::Sptr LCandle = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				LCandle->Name = "Large Candle";
				LCandle->Set("u_Material.Diffuse", GetTexture("Large Candle"));
				LCandle->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Large Candle", std::move(LCandle));
			}

			Material::Sptr keyMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				keyMat->Name = "Key";
				keyMat->Set("u_Material.Diffuse", GetTexture("Key"));
				keyMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Key", std::move(keyMat));
			}

			Material::Sptr whiteMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				whiteMat->Name = "White";
				whiteMat->Set("u_Material.Diffuse", GetTexture("White"));
				whiteMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("White", std::move(whiteMat));
			}

			Material::Sptr grayMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				grayMat->Name = "Gray";
				grayMat->Set("u_Material.Diffuse", GetTexture("Gray"));
				grayMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Gray", std::move(grayMat));
			}

			Material::Sptr brownMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				brownMat->Name = "Brown";
				brownMat->Set("u_Material.Diffuse", GetTexture("Brown"));
				brownMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Brown", std::move(brownMat));
			}

			Material::Sptr stone1Mat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				stone1Mat->Name = "StoneTex"; 
				stone1Mat->Set("u_Material.Diffuse", GetTexture("StoneTex")); 
				stone1Mat->Set("u_Material.Shininess", 0.1f); 
				materials.emplace("StoneTex", std::move(stone1Mat)); 
			}

			Material::Sptr Wall_Mat2 = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				Wall_Mat2->Name = "Wall2";
				Wall_Mat2->Set("u_Material.Diffuse", GetTexture("Wall2"));
				Wall_Mat2->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Wall2", std::move(Wall_Mat2));
			}

			Material::Sptr Wall_Mat3 = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				Wall_Mat3->Name = "Wall_Tex3";
				Wall_Mat3->Set("u_Material.Diffuse", GetTexture("Wall_Tex3"));
				Wall_Mat3->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Wall_Tex3", std::move(Wall_Mat3));
			}

				Material::Sptr Wall_Mat4 = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
				{
					Wall_Mat4->Name = "Wall_Tex4";
					Wall_Mat4->Set("u_Material.Diffuse", GetTexture("Wall_Tex4"));
					Wall_Mat4->Set("u_Material.Shininess", 0.1f);
					materials.emplace("Wall_Tex4", std::move(Wall_Mat4));
				}

			Material::Sptr shieldMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				shieldMat->Name = "ShieldTex";
				shieldMat->Set("u_Material.Diffuse", GetTexture("ShieldTex"));
				shieldMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("ShieldTex", std::move(shieldMat));
			}

			Material::Sptr staffMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				staffMat->Name = "StaffTex";
				staffMat->Set("u_Material.Diffuse", GetTexture("StaffTex"));
				staffMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("StaffTex", std::move(staffMat));
			}

			Material::Sptr swordMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				swordMat->Name = "SwordTex";
				swordMat->Set("u_Material.Diffuse", GetTexture("SwordTex"));
				swordMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("SwordTex", std::move(swordMat));
			}

			Material::Sptr leverMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				leverMat->Name = "LeverTex";
				leverMat->Set("u_Material.Diffuse", GetTexture("LeverTex"));
				leverMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("LeverTex", std::move(leverMat));
			}

			Material::Sptr intactPillarMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				intactPillarMat->Name = "Intact Pillar";
				intactPillarMat->Set("u_Material.Diffuse", GetTexture("Intact Pillar"));
				intactPillarMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Intact Pillar", std::move(intactPillarMat));
			}

			Material::Sptr damagedPillarMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				damagedPillarMat->Name = "Damaged Pillar";
				damagedPillarMat->Set("u_Material.Diffuse", GetTexture("Damaged Pillar"));
				damagedPillarMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Damaged Pillar", std::move(damagedPillarMat));
			}

			Material::Sptr destroyedPillarMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				destroyedPillarMat->Name = "Destroyed Pillar";
				destroyedPillarMat->Set("u_Material.Diffuse", GetTexture("Destroyed Pillar"));
				destroyedPillarMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Destroyed Pillar", std::move(destroyedPillarMat));
			}

			Material::Sptr rockPileMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				rockPileMat->Name = "Rock Pile";
				rockPileMat->Set("u_Material.Diffuse", GetTexture("RockPileTex"));
				rockPileMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Rock Pile", std::move(rockPileMat));
			}

			Material::Sptr barrelMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				barrelMat->Name = "Barrel";
				barrelMat->Set("u_Material.Diffuse", GetTexture("BarrelTex"));
				barrelMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Barrel", std::move(barrelMat));
			}

			Material::Sptr bucketMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				bucketMat->Name = "Bucket";
				bucketMat->Set("u_Material.Diffuse", GetTexture("BucketTex"));
				bucketMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Bucket", std::move(bucketMat));
			}

			Material::Sptr kegMat = ResourceManager::CreateAsset<Material>(GetShader("Basic"));
			{
				kegMat->Name = "Keg";
				kegMat->Set("u_Material.Diffuse", GetTexture("KegTex"));
				kegMat->Set("u_Material.Shininess", 0.1f);
				materials.emplace("Keg", std::move(kegMat));
			}

#pragma endregion

#pragma region Mesh Resources
			
			meshes.emplace("Character", ResourceManager::CreateAsset<MeshResource>("Character.obj"));
			meshes.emplace("Dark Pine Tree", ResourceManager::CreateAsset<MeshResource>("DarkPineTree.obj"));
			meshes.emplace("Light Pine Tree", ResourceManager::CreateAsset<MeshResource>("LightPineTree.obj"));
			meshes.emplace("Grave Stone", ResourceManager::CreateAsset<MeshResource>("GraveStone.obj"));
			meshes.emplace("Key", ResourceManager::CreateAsset<MeshResource>("key.obj"));
			meshes.emplace("Stone Wall", ResourceManager::CreateAsset<MeshResource>("StoneWall.obj"));
			meshes.emplace("Turret Projectile", ResourceManager::CreateAsset<MeshResource>("TurretProjectile.obj"));
			meshes.emplace("Standing Torch", ResourceManager::CreateAsset<MeshResource>("StandingTorch.obj"));
			meshes.emplace("Enemy", ResourceManager::CreateAsset<MeshResource>("Enemy.obj"));
			meshes.emplace("Circle Cage", ResourceManager::CreateAsset<MeshResource>("CircleCage.obj"));
			meshes.emplace("Box Cage", ResourceManager::CreateAsset<MeshResource>("BoxCage.obj"));
			meshes.emplace("Long Cage", ResourceManager::CreateAsset<MeshResource>("CageLong.obj"));
			meshes.emplace("Small Cage", ResourceManager::CreateAsset<MeshResource>("SCage.obj"));
			meshes.emplace("U Cage", ResourceManager::CreateAsset<MeshResource>("CageU.obj"));
			meshes.emplace("Relic 1", ResourceManager::CreateAsset<MeshResource>("Symbol1.obj"));
			meshes.emplace("Relic 2", ResourceManager::CreateAsset<MeshResource>("Symbol2.obj"));
			meshes.emplace("Relic 3", ResourceManager::CreateAsset<MeshResource>("Symbol3.obj"));
			meshes.emplace("Relic 4", ResourceManager::CreateAsset<MeshResource>("Symbol4.obj"));
			meshes.emplace("Relic 5", ResourceManager::CreateAsset<MeshResource>("Symbol5.obj"));
			meshes.emplace("Pressure Plate", ResourceManager::CreateAsset<MeshResource>("PressurePlate.obj"));
			meshes.emplace("Turret", ResourceManager::CreateAsset<MeshResource>("Turret.obj"));
			meshes.emplace("Door", ResourceManager::CreateAsset<MeshResource>("door.obj"));
			meshes.emplace("Spike Trap", ResourceManager::CreateAsset<MeshResource>("SpikedTrap.obj"));
			meshes.emplace("Character Dagger", ResourceManager::CreateAsset<MeshResource>("CharacterDagger.obj"));
			meshes.emplace("Health Orb", ResourceManager::CreateAsset<MeshResource>("HealthOrb.obj"));
			meshes.emplace("Wall Grate", ResourceManager::CreateAsset<MeshResource>("WallGrate.obj"));
			meshes.emplace("Floor Grate", ResourceManager::CreateAsset<MeshResource>("FloorGrate.obj"));
			meshes.emplace("Large Candle", ResourceManager::CreateAsset<MeshResource>("LargeCandle.obj"));
			meshes.emplace("Cube", ResourceManager::CreateAsset<MeshResource>("cube.obj"));
			meshes.emplace("Damaged Pillar", ResourceManager::CreateAsset<MeshResource>("DamagedPillar.obj"));
			meshes.emplace("Destroyed Pillar", ResourceManager::CreateAsset<MeshResource>("DestroyedPillar.obj"));
			meshes.emplace("Intact Pillar", ResourceManager::CreateAsset<MeshResource>("IntactPillar.obj"));
			meshes.emplace("Rock Pile", ResourceManager::CreateAsset<MeshResource>("RockPile3.obj"));
			meshes.emplace("Sphere", ResourceManager::CreateAsset<MeshResource>("Sphere.obj"));
			meshes.emplace("Wall2", ResourceManager::CreateAsset<MeshResource>("Wall2.obj"));
			meshes.emplace("Shield", ResourceManager::CreateAsset<MeshResource>("GoblinShield.obj"));
			meshes.emplace("Staff", ResourceManager::CreateAsset<MeshResource>("GoblinStaff.obj"));
			meshes.emplace("Sword", ResourceManager::CreateAsset<MeshResource>("GoblinSword.obj"));
			meshes.emplace("Lever", ResourceManager::CreateAsset<MeshResource>("Lever.obj"));
			meshes.emplace("Barrel", ResourceManager::CreateAsset<MeshResource>("Barrel.obj"));
			meshes.emplace("Open Barrel", ResourceManager::CreateAsset<MeshResource>("OpenBarrel.obj"));
			meshes.emplace("Bucket", ResourceManager::CreateAsset<MeshResource>("Bucket.obj"));
			meshes.emplace("Keg", ResourceManager::CreateAsset<MeshResource>("KegWithStand.obj"));
		
#pragma endregion

#pragma region Animation Resources

			std::vector<MeshResource::Sptr> WalkAnimation;
			{
				for (int i = 0; i < 8; ++i)
				{
					std::string file;
					file.append("models/character_walk/Walk");
					file.append(std::to_string((i + 1)));
					file.append(".obj");
					WalkAnimation.push_back(ResourceManager::CreateAsset<MeshResource>(file));
				}

				animations.emplace("Character Walk", std::move(WalkAnimation));
			}

			std::vector<MeshResource::Sptr> IdleAnimation;
			{
				for (int i = 0; i < 6; ++i)
				{
					std::string file;
					file.append("models/character_idle/Idle");
					file.append(std::to_string((i + 1)));
					file.append(".obj");
					IdleAnimation.push_back(ResourceManager::CreateAsset<MeshResource>(file));
				}

				animations.emplace("Character Idle", std::move(IdleAnimation));
			}

			std::vector<MeshResource::Sptr> DoorAnimation;
			{
				for (int i = 0; i < 4; ++i)
				{
					std::string file;
					file.append("models/door/door");
					file.append(std::to_string((i + 1)));
					file.append(".obj");
					DoorAnimation.push_back(ResourceManager::CreateAsset<MeshResource>(file));
				}

				animations.emplace("Door", std::move(DoorAnimation));
			}

			std::vector<MeshResource::Sptr> SpikeAnimation;
			{
				for (int i = 0; i < 5; ++i)
				{
					std::string file;
					file.append("models/spikedTrap/SpikedTrap");
					file.append(std::to_string((i + 1)));
					file.append(".obj");
					SpikeAnimation.push_back(ResourceManager::CreateAsset<MeshResource>(file));
				}

				animations.emplace("Spikes", std::move(SpikeAnimation));
			}

#pragma endregion
	
#pragma region Sound Resources

		// Initialize the Audio Engine Resources
		AudioEngine& engine = AudioEngine::Instance();
		engine.Init();
		engine.LoadBankWithString("Master");

		engine.LoadBank("SFX");
		engine.LoadBus("Character", "bus:/SFX/Character");
		engine.CreateSoundEvent("Jump", "event:/Character/Jump");
		engine.CreateSoundEvent("Walk", "event:/Character/Player Footsteps");
		engine.CreateSoundEvent("Interact", "event:/Character/Interact");
		engine.CreateSoundEvent("Swap", "event:/Character/Shadow Swap");

		engine.LoadBus("Interactables", "bus:/SFX/Objects");
		engine.CreateSoundEvent("Key", "event:/Interactables/Key");
		engine.CreateSoundEvent("Spikes", "event:/Interactables/Spikes");
		engine.CreateSoundEvent("Pressure Plate", "event:/Interactables/Pressure Plate");
		engine.CreateSoundEvent("Lever", "event:/Interactables/Lever");
		engine.CreateSoundEvent("Door", "event:/Interactables/Door Open");

		engine.LoadBank("Music");
		engine.LoadBus("Music", "bus:/Music");
		engine.CreateSoundEvent("Test", "event:/Music/Level 02");
		engine.CreateSoundEvent("Mohit", "event:/Music/Mohit");

		// SOUNDS
		/////////////////////////////////////
		/*{			
			sounds.emplace("Mohit", ResourceManager::CreateAsset<AudioResource>("audio/Mohit.mp3"));

			sounds.emplace("Walk", ResourceManager::CreateAsset<AudioResource>("audio/WalkTemp.wav"));
			sounds.emplace("Jump", ResourceManager::CreateAsset<AudioResource>("audio/Jump.wav"));
			sounds.emplace("Shadow Swap", ResourceManager::CreateAsset<AudioResource>("audio/ShadowSwap.wav"));
			
			sounds.emplace("Sword", ResourceManager::CreateAsset<AudioResource>("audio/SwordSwing.mp3"));
			sounds.emplace("Door", ResourceManager::CreateAsset<AudioResource>("audio/DoorOpen.wav"));
			sounds.emplace("Jump", ResourceManager::CreateAsset<AudioResource>("audio/Jump.wav"));
			sounds.emplace("Lever", ResourceManager::CreateAsset<AudioResource>("audio/Lever.mp3"));
			sounds.emplace("Spike Trap", ResourceManager::CreateAsset<AudioResource>("audio/SpikeTrap.wav"));
			sounds.emplace("Key", ResourceManager::CreateAsset<AudioResource>("audio/Key.wav"));
			sounds.emplace("Click", ResourceManager::CreateAsset<AudioResource>("audio/PressurePlate.wav"));
		}*/
#pragma endregion

	}

	static ShaderProgram::Sptr GetShader(std::string name) {
		std::map<std::string, ShaderProgram::Sptr>::iterator it;
		it = shared_instance().shaders.find(name);

		if (it != shared_instance().shaders.end())
		{
			return it->second;
		}

		else {
			std::cout << "ERROR <nullptr>: " << name << " not found in Shaders.";
			return nullptr;
		}
	}
	static MeshResource::Sptr GetMesh(std::string name)
	{
		std::map<std::string, MeshResource::Sptr>::iterator it;
		it = shared_instance().meshes.find(name);

		if (it != shared_instance().meshes.end())
		{
			return it->second;
		}

		else {
			std::cout << "ERROR <nullptr>: " << name << " not found in Meshes.";
			return nullptr;
		}
	}

	static Texture2D::Sptr GetTexture(std::string name)
	{
		std::map<std::string, Texture2D::Sptr>::iterator it;
		it = shared_instance().textures.find(name);

		if (it != shared_instance().textures.end())
		{
			return it->second;
		}

		else {
			std::cout << "ERROR <nullptr>: " << name << " not found in Textures.";
			return nullptr;
		}
	}

	static Material::Sptr GetMaterial(std::string name)
	{
		std::map<std::string, Material::Sptr>::iterator it;
		it = shared_instance().materials.find(name);

		if (it != shared_instance().materials.end())
		{
			return it->second;
		}

		else {
			std::cout << "ERROR <nullptr>: " << name << " not found in Materials.";
			return nullptr;
		}
	}

	static std::vector<MeshResource::Sptr> GetAnimation(std::string name)
	{
		std::map<std::string, std::vector<MeshResource::Sptr>>::iterator it;
		it = shared_instance().animations.find(name);

		if (it != shared_instance().animations.end())
		{
			return it->second;
		}

		else {
			std::cout << "ERROR <nullptr>: " << name << " not found in Animations";
			return std::vector<MeshResource::Sptr>();
		}
	}

	static std::map<std::string, AudioResource::Sptr>* GetAudioMap() { return &shared_instance().sounds; }
	static AudioResource::Sptr GetSound(std::string name)
	{
		std::map<std::string, AudioResource::Sptr>::iterator it;
		it = shared_instance().sounds.find(name);

		if (it != shared_instance().sounds.end())
		{
			return it->second;
		}

		else {
			std::cout << "ERROR <nullptr>: " << name << " not found in Sounds.";
			return nullptr;
		}
	}

};
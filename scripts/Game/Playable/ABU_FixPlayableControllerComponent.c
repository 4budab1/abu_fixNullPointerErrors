modded class PS_PlayableControllerComponent
{
	override PS_LobbyVoNComponent GetVoN()
	{
		PlayerController thisPlayerController = PlayerController.Cast(GetOwner());
		if (!thisPlayerController)
			return null;
		IEntity entity = thisPlayerController.GetControlledEntity();
		if (!entity)
			return null;
		return PS_LobbyVoNComponent.Cast(entity.FindComponent(PS_LobbyVoNComponent));
	}

	override RadioTransceiver GetVoNTransiver(int radioId)
	{
		PlayerController thisPlayerController = PlayerController.Cast(GetOwner());
		if (!thisPlayerController)
			return null;
		IEntity entity = thisPlayerController.GetControlledEntity();
		if (!entity)
			return null;
		SCR_GadgetManagerComponent gadgetManager = SCR_GadgetManagerComponent.Cast(entity.FindComponent(SCR_GadgetManagerComponent));
		if (!gadgetManager)
			return null;
		array<SCR_GadgetComponent> radios = gadgetManager.GetGadgetsByType(EGadgetType.RADIO);
		if (!radios || radios.Count() <= radioId)
			return null;
		IEntity radioEntity = radios[radioId].GetOwner();
		if (!radioEntity)
			return null;
		BaseRadioComponent radio = BaseRadioComponent.Cast(radioEntity.FindComponent(BaseRadioComponent));
		if (!radio)
			return null;
		radio.SetPower(true);
		RadioTransceiver transiver = RadioTransceiver.Cast(radio.GetTransceiver(0));
		if (!transiver)
			return null;
		transiver.SetFrequency(radioId + 1);
		return transiver;
	}

	override void LobbyVoNEnable()
	{
		UpdatePosition(true);
		GetGame().GetCallqueue().Remove(LobbyVoNDisableDelayed);
		PS_LobbyVoNComponent von = GetVoN();
		if (!von)
			return;
		RadioTransceiver transiver = GetVoNTransiver(1);
		if (!transiver)
			return;
		von.SetTransmitRadio(transiver);
		von.SetCommMethod(ECommMethod.SQUAD_RADIO);
		von.SetCapture(true);
	}

	override void LobbyVoNRadioEnable()
	{
		UpdatePosition(true);
		GetGame().GetCallqueue().Remove(LobbyVoNDisableDelayed);
		PS_LobbyVoNComponent von = GetVoN();
		if (!von)
			return;
		RadioTransceiver transiver = GetVoNTransiver(0);
		if (!transiver)
			return;
		von.SetTransmitRadio(transiver);
		von.SetCommMethod(ECommMethod.SQUAD_RADIO);
		von.SetCapture(true);
	}

	override void SetVoNKey(string VoNKey, string VoNKeyLocal)
	{
		if (!GetVoN())
			return;
		PlayerController thisPlayerController = PlayerController.Cast(GetOwner());
		if (!thisPlayerController)
			return;
		IEntity entity = thisPlayerController.GetControlledEntity();
		if (!entity)
			return;
		SCR_GadgetManagerComponent gadgetManager = SCR_GadgetManagerComponent.Cast(entity.FindComponent(SCR_GadgetManagerComponent));
		if (!gadgetManager)
			return;
		array<SCR_GadgetComponent> radios = gadgetManager.GetGadgetsByType(EGadgetType.RADIO);
		if (!radios || radios.Count() < 2)
			return;
		BaseRadioComponent radio = BaseRadioComponent.Cast(radios[0].GetOwner().FindComponent(BaseRadioComponent));
		if (radio)
			radio.SetEncryptionKey(VoNKey);
		radio = BaseRadioComponent.Cast(radios[1].GetOwner().FindComponent(BaseRadioComponent));
		if (radio)
			radio.SetEncryptionKey(VoNKeyLocal);
	}

	override bool isVonInit()
	{
		PlayerController thisPlayerController = PlayerController.Cast(GetOwner());
		if (!thisPlayerController)
			return false;
		IEntity entity = thisPlayerController.GetControlledEntity();
		if (!entity)
			return false;
		SCR_GadgetManagerComponent gadgetManager = SCR_GadgetManagerComponent.Cast(entity.FindComponent(SCR_GadgetManagerComponent));
		if (!gadgetManager)
			return false;
		IEntity radioEntity = gadgetManager.GetGadgetByType(EGadgetType.RADIO);
		return radioEntity != null;
	}

	override protected void EOnFrame(IEntity owner, float timeSlice)
	{
		PS_GameModeCoop gameMode = PS_GameModeCoop.Cast(GetGame().GetGameMode());
		if (!gameMode)
		{
			ClearEventMask(GetOwner(), EntityEvent.FRAME);
			return;
		}
		if ((gameMode.GetState() == SCR_EGameModeState.GAME && gameMode.IsFreezeTimeEnd()) || !gameMode.IsFreezeTimeShootingForbiden())
		{
			ClearEventMask(GetOwner(), EntityEvent.FRAME);
			return;
		}

		if (PS_PlayersHelper.IsAdminOrServer())
			return;

		PlayerController playerController = PlayerController.Cast(owner);
		if (!playerController)
			return;
		ActionManager actionManager = playerController.GetActionManager();
		if (!actionManager)
			return;

		actionManager.SetActionValue("CharacterFire", 0);
		actionManager.SetActionValue("CharacterThrowGrenade", 0);
		actionManager.SetActionValue("CharacterMelee", 0);
		actionManager.SetActionValue("CharacterFireStatic", 0);
		actionManager.SetActionValue("TurretFire", 0);
		actionManager.SetActionValue("VehicleFire", 0);
		actionManager.SetActionValue("VehicleHorn", 0);

		IEntity character = playerController.GetControlledEntity();
		if (character)
		{
			Vehicle vehicle = Vehicle.Cast(character.GetRootParent());
			if (vehicle)
			{
				if (!vehicle.IsEnableMoveOnFreeze())
				{
					DisableVehicleMove(actionManager);
					VehicleWheeledSimulation vehicleWheeledSimulation = VehicleWheeledSimulation.Cast(vehicle.FindComponent(VehicleWheeledSimulation));
					if (vehicleWheeledSimulation)
					{
						if (vehicleWheeledSimulation.EngineIsOn())
							vehicleWheeledSimulation.EngineStop();
					}
				}
			}
		}

		if (m_bOutFreezeTime)
		{
			actionManager.SetActionValue("CharacterForward", 0);
			actionManager.SetActionValue("CharacterRight", 0);
			actionManager.SetActionValue("CharacterTurnUp", 0);
			actionManager.SetActionValue("CharacterTurnRight", 0);
			actionManager.SetActionValue("CharacterTurnUp", 0);
			actionManager.SetActionValue("CharacterTurnRight", 0);
			actionManager.SetActionValue("GetOut", 0);
			actionManager.SetActionValue("JumpOut", 0);
			actionManager.SetActionValue("CharacterStand", 0);
			actionManager.SetActionValue("CharacterCrouch", 0);
			actionManager.SetActionValue("CharacterProne", 0);
			actionManager.SetActionValue("CharacterStandCrouchToggle", 0);
			actionManager.SetActionValue("CharacterStandProneToggle", 0);
			actionManager.SetActionValue("CharacterRoll", 0);
			actionManager.SetActionValue("CharacterJump", 0);

			DisableVehicleMove(actionManager);

			if (character)
			{
				Vehicle vehicle = Vehicle.Cast(character.GetRootParent());
				if (vehicle)
				{
					BaseVehicleNodeComponent vehicleNodeComponent = BaseVehicleNodeComponent.Cast(vehicle.FindComponent(BaseVehicleNodeComponent));
					if (vehicleNodeComponent)
					{
						SCR_HelicopterControllerComponent helicopterControllerComponent = SCR_HelicopterControllerComponent.Cast(vehicleNodeComponent.FindComponent(SCR_HelicopterControllerComponent));
						if (helicopterControllerComponent && !helicopterControllerComponent.GetAutohoverEnabled())
						{
							actionManager.SetActionValue("AutohoverToggle", 1);
						}
					}
				}
			}
		}
	}

	override void UpdatePosition(bool force)
	{
		PlayerController thisPlayerController = PlayerController.Cast(GetOwner());
		if (!thisPlayerController)
			return;

		RplComponent rpl = RplComponent.Cast(GetOwner().FindComponent(RplComponent));
		if (!rpl)
			return;
		if (!rpl.IsOwner())
			return;

		if (m_InitialEntity)
		{
			int playerId = thisPlayerController.GetPlayerId();
			m_vVoNPosition = Vector(0, 100000, 0) + Vector(1000 * Math.Mod(playerId, 10), 5000 * Math.Floor(Math.Mod(playerId, 100) / 10), 5000 * Math.Floor(playerId / 100));
			vector currentOrigin = m_InitialEntity.GetOrigin();

			GameEntity gameEntity = GameEntity.Cast(m_InitialEntity);
			if (!gameEntity)
				return;
			vector mat[4];
			Math3D.MatrixIdentity4(mat);
			mat[3] = m_vVoNPosition;
			if (force)
				gameEntity.Teleport(mat);
			gameEntity.SetTransform(mat);

			MenuBase menu = GetGame().GetMenuManager().GetTopMenu();
			if (menu && (menu.IsInherited(PS_PreviewMapMenu) || menu.IsInherited(PS_CoopLobby) || menu.IsInherited(PS_BriefingMapMenu)))
			{
				CameraBase cam = GetGame().GetCameraManager().CurrentCamera();
				if (cam)
					cam.SetWorldTransform(mat);
				if (m_Camera)
					m_Camera.SetTransform(mat);
			}

			CameraBase cameraBase = GetGame().GetCameraManager().CurrentCamera();
			if (cameraBase)
				cameraBase.ApplyTransform(GetGame().GetWorld().GetTimeSlice());

			Physics physics = m_InitialEntity.GetPhysics();
			if (physics)
			{
				physics.SetActive(ActiveState.INACTIVE);
			}
		} else {
			IEntity entity = thisPlayerController.GetControlledEntity();
			if (entity)
			{
				PS_LobbyVoNComponent von = PS_LobbyVoNComponent.Cast(entity.FindComponent(PS_LobbyVoNComponent));
				if (von)
					m_InitialEntity = entity;
			}
		}
	}

	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	override void RPC_MoveVoNToRoom(int playerId, FactionKey factionKey, string roomName)
	{
		if (playerId <= 0)
			return;

		PS_PlayableManager playableManager = PS_PlayableManager.GetInstance();
		if (!playableManager)
			return;

		PS_VoNRoomsManager VoNRoomsManager = PS_VoNRoomsManager.GetInstance();
		if (!VoNRoomsManager)
			return;

		VoNRoomsManager.MoveToRoom(playerId, factionKey, roomName);
	}

	override void ApplyPlayable()
	{
		PlayerController thisPlayerController = PlayerController.Cast(GetOwner());
		if (!thisPlayerController)
			return;
		PS_PlayableManager playableManager = PS_PlayableManager.GetInstance();
		if (!playableManager)
			return;
		int playerId = thisPlayerController.GetPlayerId();
		if (playerId <= 0)
			return;
		if (playableManager.GetPlayableByPlayer(playerId) == RplId.Invalid())
			SwitchToObserver(null);
		Rpc(RPC_ApplyPlayable);
	}

	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	override protected void RPC_ApplyPlayable()
	{
		PS_PlayableManager playableManager = PS_PlayableManager.GetInstance();
		if (!playableManager)
			return;
		PlayerController playerController = PlayerController.Cast(GetOwner());
		if (!playerController)
			return;
		playableManager.ApplyPlayable(playerController.GetPlayerId());
	}
}

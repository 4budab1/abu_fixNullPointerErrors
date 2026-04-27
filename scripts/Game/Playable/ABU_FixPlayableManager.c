modded class PS_PlayableManager
{
	override void ApplyPlayable(int playerId)
	{
		SCR_PlayerController playerController = SCR_PlayerController.Cast(m_PlayerManager.GetPlayerController(playerId));
		if (!playerController)
			return;
		PS_PlayableControllerComponent playableController = playerController.PS_GetPLayableComponent();
		if (!playableController)
			return;
		SCR_GroupsManagerComponent groupsManagerComponent = SCR_GroupsManagerComponent.GetInstance();
		if (!groupsManagerComponent)
			return;

		SetPlayerState(playerId, PS_EPlayableControllerState.Playing);

		RplId playableId = GetPlayableByPlayer(playerId);
		if (playableId != RplId.Invalid())
		{
			PS_PlayableContainer playableContainer = GetPlayableById(playableId);
			if (playableContainer && playableContainer.GetDamageState() == EDamageState.DESTROYED)
			{
				m_CallQueue.CallLater(DelayedSwitchToInitialEntity, 1000, false, playerId);
			}
		}

		IEntity entity;
		if (playableId == RplId.Invalid())
		{
			SCR_AIGroup currentGroup = groupsManagerComponent.GetPlayerGroup(playableId);
			if (currentGroup)
				currentGroup.RemovePlayer(playerId);
			SetPlayerFactionKey(playerId, "");

			entity = playableController.GetInitialEntity();
			if (!entity)
			{
				Resource resource = Resource.Load("{ADDE38E4119816AB}Prefabs/InitialPlayer_Version2.et");
				EntitySpawnParams params = new EntitySpawnParams();
				entity = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
				playableController.SetInitialEntity(entity);
			}

			playerController.SetInitialMainEntity(entity);
			return;
		} else
		{
			PS_PlayableContainer playableContainer = GetPlayableById(playableId);
			if (!playableContainer)
				return;
			PS_PlayableComponent playableComponent = playableContainer.GetPlayableComponent();
			if (!playableComponent)
				return;
			entity = playableComponent.GetOwner();
			if (!entity)
				return;
		}

		IEntity initialEntity = playableController.GetInitialEntity();
		if (initialEntity)
			m_CallQueue.Call(SCR_EntityHelper.DeleteEntityAndChildren, initialEntity);

		playerController.SetInitialMainEntity(entity);

		SCR_ChimeraCharacter playableCharacter = SCR_ChimeraCharacter.Cast(entity);
		if (playableCharacter)
		{
			SCR_Faction faction = SCR_Faction.Cast(playableCharacter.GetFaction());
			if (faction)
				SetPlayerFactionKey(playerId, faction.GetFactionKey());
		}

		m_CallQueue.CallLater(ChangeGroup, 0, false, playerId, playableId);
	}
}

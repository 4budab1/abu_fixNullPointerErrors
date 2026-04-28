modded class SCR_DataCollectorComponent
{
	override protected void OnGameModeEnd(SCR_GameModeEndData data)
	{
		foreach (SCR_DataCollectorModule module : m_aModules)
		{
			module.OnGameModeEnd();
		}

		PlayerManager playerManager = GetGame().GetPlayerManager();
		int playerID;
		PlayerController playerController;
		SCR_DataCollectorCommunicationComponent communicationComponent;

		SCR_ChimeraCharacter playerChimera;
		Faction faction;

		for (int i = m_mPlayerData.Count() - 1; i >= 0; i--)
		{
			playerID = m_mPlayerData.GetKey(i);

			m_mPlayerData.Get(playerID).CalculateSessionDuration();

			playerChimera = SCR_ChimeraCharacter.Cast(playerManager.GetPlayerControlledEntity(playerID));
			if (!playerChimera)
				continue;

			faction = playerChimera.GetFaction();

			if (!faction)
				continue;

			AddStatsToFaction(faction.GetFactionKey(), m_mPlayerData.Get(playerID).CalculateStatsDifference());
		}

		array<FactionKey> factionKeys = {};
		array<float> factionValues = {};
		int valuesSize = 0;

		foreach (FactionKey key, array<float> value : m_mFactionScore)
		{
			factionKeys.Insert(key);
			factionValues.InsertAll(value);
			if (valuesSize == 0)
				valuesSize = value.Count();
		}

		for (int i = m_mPlayerData.Count() - 1; i >= 0; i--)
		{
			playerID = m_mPlayerData.GetKey(i);
			playerController = playerManager.GetPlayerController(playerID);
			if (!playerController)
				continue;

			communicationComponent = SCR_DataCollectorCommunicationComponent.Cast(playerController.FindComponent(SCR_DataCollectorCommunicationComponent));
			if (!communicationComponent)
				continue;

			communicationComponent.SendData(m_mPlayerData.Get(playerID), factionKeys, factionValues, valuesSize);
		}

		if (!m_SessionData)
			return;

		SCR_SessionDataEvent dataEvent = m_SessionData.GetSessionDataEvent();

		dataEvent.name_reason_end = SCR_Enum.GetEnumName(EGameOverTypes, data.GetEndReason());

		FactionManager factionManager = GetGame().GetFactionManager();
		if (factionManager)
		{
			Faction winFaction = factionManager.GetFactionByIndex(data.GetWinnerFactionId());
			if (winFaction)
				dataEvent.name_winner_faction = winFaction.GetFactionKey();
		}
	}
}

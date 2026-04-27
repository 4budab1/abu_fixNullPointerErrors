modded class PS_GameModeCoop
{
	override void OnPlayerDisconnected(int playerId, KickCauseCode cause, int timeout)
	{
		PlayerManager playerManager = GetGame().GetPlayerManager();
		if (!playerManager)
		{
			super.OnPlayerDisconnected(playerId, cause, timeout);
			return;
		}

		SCR_PlayerController playerController = SCR_PlayerController.Cast(playerManager.GetPlayerController(playerId));
		if (!playerController)
		{
			m_OnPlayerDisconnected.Invoke(playerId, cause, timeout);
			foreach (SCR_BaseGameModeComponent comp : m_aAdditionalGamemodeComponents)
			{
				if (comp)
					comp.OnPlayerDisconnected(playerId, cause, timeout);
			}
			m_OnPostCompPlayerDisconnected.Invoke(playerId, cause, timeout);
			if (IsMaster() && m_pRespawnSystemComponent)
				m_pRespawnSystemComponent.OnPlayerDisconnected_S(playerId, cause, timeout);
			return;
		}

		super.OnPlayerDisconnected(playerId, cause, timeout);
	}

	override void SpawnInitialEntity(int playerId)
	{
		PlayerManager playerManager = GetGame().GetPlayerManager();
		if (!playerManager)
			return;

		SCR_PlayerController playerController = SCR_PlayerController.Cast(playerManager.GetPlayerController(playerId));
		if (!playerController)
			return;

		super.SpawnInitialEntity(playerId);
	}
}

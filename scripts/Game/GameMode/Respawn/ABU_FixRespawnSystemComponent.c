modded class SCR_RespawnSystemComponent
{
	override void OnPlayerKilled_S(int playerId, IEntity playerEntity, IEntity killerEntity, notnull Instigator killer)
	{
		if (!m_SpawnLogic)
			return;

		m_SpawnLogic.OnPlayerKilled_S(playerId, playerEntity, killerEntity, killer);
	}

	override void OnPlayerDeleted_S(int playerId)
	{
		if (!m_SpawnLogic)
			return;

		PlayerManager playerManager = GetGame().GetPlayerManager();
		if (!playerManager)
			return;

		m_SpawnLogic.OnPlayerDeleted_S(playerId, !playerManager.IsPlayerConnected(playerId));
	}

	override void OnPlayerDisconnected_S(int playerId, KickCauseCode cause, int timeout)
	{
		if (!m_SpawnLogic)
			return;

		m_SpawnLogic.OnPlayerDisconnected_S(playerId, cause, timeout);
	}
}

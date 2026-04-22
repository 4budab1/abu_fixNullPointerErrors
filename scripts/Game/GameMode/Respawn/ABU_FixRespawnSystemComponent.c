modded class SCR_RespawnSystemComponent
{
	override void OnPlayerDisconnected_S(int playerId, KickCauseCode cause, int timeout)
	{
		if (!m_SpawnLogic)
			return;

		m_SpawnLogic.OnPlayerDisconnected_S(playerId, cause, timeout);
	}
}

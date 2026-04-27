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
			super.OnPlayerDisconnected(playerId, cause, timeout);
			return;
		}

		super.OnPlayerDisconnected(playerId, cause, timeout);
	}
}

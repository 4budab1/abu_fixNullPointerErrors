modded class PS_PlayersHelper
{
	override static bool IsAdminOrServer()
	{
		if (Replication.IsServer())
			return true;
		PlayerController playerController = GetGame().GetPlayerController();
		if (!playerController)
			return false;
		return SCR_Global.IsAdmin(playerController.GetPlayerId());
	}
}

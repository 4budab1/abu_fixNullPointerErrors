modded class PS_PlayersHelper
{
	override static bool IsAdminOrServer()
	{
		if (Replication.IsServer())
			return true;

		if (!SCR_Global.IsAdmin())
			return false;

		return true;
	}
}

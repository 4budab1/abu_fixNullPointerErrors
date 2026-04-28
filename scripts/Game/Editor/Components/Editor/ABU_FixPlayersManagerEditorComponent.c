modded class SCR_PlayersManagerEditorComponent
{
	override protected void OnDisconnectedOwner(int playerID)
	{
		if (!m_MainEntities)
			return;

		super.OnDisconnectedOwner(playerID);
	}
}

modded class SCR_DataCollectorComponent
{
	override protected void OnGameModeEnd(SCR_GameModeEndData data)
	{
		if (!m_SessionData)
			return;

		super.OnGameModeEnd(data);
	}
}

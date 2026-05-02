modded class SCR_DataCollectorComponent
{
	protected override void OnGameModeEnd(SCR_GameModeEndData data)
	{
		if (!m_SessionData)
			return;

		super.OnGameModeEnd(data);
	}
}

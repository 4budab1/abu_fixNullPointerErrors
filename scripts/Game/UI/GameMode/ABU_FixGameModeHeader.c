modded class PS_GameModeHeader
{
	override void Update()
	{
		m_hButtonPreview.Update();
		m_hButtonLobby.Update();
		m_hButtonBriefing.Update();
		m_hButtonInGame.Update();
		m_hButtonDebriefing.Update();

		PlayerManager playerManager = GetGame().GetPlayerManager();
		if (!playerManager)
			return;
		PlayerController thisPlayerController = GetGame().GetPlayerController();
		if (!thisPlayerController)
			return;
		if (!PS_PlayersHelper.IsAdminOrServer())
		{
			m_wAdvanceImage.SetColor(Color.Gray);
		} else {
			m_wAdvanceImage.SetColor(Color.FromInt(0xff008020));
		}
	}
}

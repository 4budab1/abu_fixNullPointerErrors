modded class PS_GameModeHeader
{
	override void Update()
	{
		if (!m_hButtonPreview || !m_hButtonLobby || !m_hButtonBriefing || !m_hButtonInGame || !m_hButtonDebriefing)
			return;

		PlayerController thisPlayerController = GetGame().GetPlayerController();
		if (!thisPlayerController)
			return;

		PlayerManager playerManager = GetGame().GetPlayerManager();
		if (!playerManager)
			return;

		m_hButtonPreview.Update();
		m_hButtonLobby.Update();
		m_hButtonBriefing.Update();
		m_hButtonInGame.Update();
		m_hButtonDebriefing.Update();

		if (!m_wAdvanceImage)
			return;

		if (!PS_PlayersHelper.IsAdminOrServer())
		{
			m_wAdvanceImage.SetColor(Color.Gray);
		} else {
			m_wAdvanceImage.SetColor(Color.FromInt(0xff008020));
		}
	}
}

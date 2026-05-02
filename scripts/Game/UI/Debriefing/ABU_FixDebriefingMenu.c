modded class PS_DebriefingMenu
{
	override void OnMenuOpen()
	{
		m_wBodyHorizontalLayout = HorizontalLayoutWidget.Cast(GetRootWidget().FindAnyWidget("BodyHorizontalLayout"));

		m_wFade = ImageWidget.Cast(GetRootWidget().FindAnyWidget("Fade"));

		m_wGameModeHeader = GetRootWidget().FindAnyWidget("GameModeHeader");
		m_hGameModeHeader = PS_GameModeHeader.Cast(m_wGameModeHeader.FindHandler(PS_GameModeHeader));

		GetGame().GetInputManager().AddActionListener("MenuBack", EActionTrigger.DOWN, Action_Exit);

		GetRootWidget().SetOpacity(0);

		FillFactions();
		Update();
		GetGame().GetCallqueue().CallLater(UpdateCycle, 100);

		PlayerController playerController = GetGame().GetPlayerController();
		if (playerController)
		{
			PS_PlayableControllerComponent playableController = PS_PlayableControllerComponent.Cast(playerController.FindComponent(PS_PlayableControllerComponent));
			if (playableController)
				playableController.LobbyVoNDisable();
		}
	}
}

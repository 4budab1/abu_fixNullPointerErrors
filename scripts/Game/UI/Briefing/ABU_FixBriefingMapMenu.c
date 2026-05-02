modded class PS_BriefingMapMenu
{
	override void Action_LobbyVoNOn()
	{
		PlayerController playerController = GetGame().GetPlayerController();
		if (!playerController)
			return;
		PS_PlayableControllerComponent playableController = PS_PlayableControllerComponent.Cast(playerController.FindComponent(PS_PlayableControllerComponent));
		if (!playableController)
			return;
		playableController.LobbyVoNEnable();
	}

	override void Action_LobbyVoNOff()
	{
		PlayerController playerController = GetGame().GetPlayerController();
		if (!playerController)
			return;
		PS_PlayableControllerComponent playableController = PS_PlayableControllerComponent.Cast(playerController.FindComponent(PS_PlayableControllerComponent));
		if (!playableController)
			return;
		playableController.LobbyVoNDisable();
	}

	override void OnMenuUpdate(float tDelta)
	{
		if (m_ChatPanel)
			m_ChatPanel.OnUpdateChat(tDelta);

		PS_PlayableManager playableManager = PS_PlayableManager.GetInstance();
		PlayerController currentPlayerController = GetGame().GetPlayerController();
		if (!currentPlayerController)
			return;
		int currentPlayerId = currentPlayerController.GetPlayerId();
		FactionKey factionKey = playableManager.GetPlayerFactionKey(currentPlayerId);
		PS_PlayableControllerComponent playableControllerComponent = PS_PlayableControllerComponent.Cast(currentPlayerController.FindComponent(PS_PlayableControllerComponent));
		if (!playableControllerComponent)
			return;

		if (m_hVoiceChatList.GetFactionKey() != factionKey)
			playableControllerComponent.SwitchToMenu(SCR_EGameModeState.BRIEFING);
	}
}

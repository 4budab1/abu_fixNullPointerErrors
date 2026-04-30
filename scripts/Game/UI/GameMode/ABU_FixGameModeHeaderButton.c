<<<<<<< Updated upstream
modded class PS_GameModeHeaderButton
=======
modded class PS_GameModeHeaderButton : SCR_ButtonBaseComponent
>>>>>>> Stashed changes
{
	override void Update()
	{
		PS_GameModeCoop gameMode = PS_GameModeCoop.Cast(GetGame().GetGameMode());
		if (!gameMode)
			return;

		if (m_eState == gameMode.GetState())
		{
			SetStateAvailable(true);
			m_wActiveImage.SetVisible(true);
		}

		if (PS_PlayersHelper.IsAdminOrServer())
			SetStateAvailable(true);

		if (m_eState == SCR_EGameModeState.BRIEFING && gameMode.GetState() == SCR_EGameModeState.SLOTSELECTION) SetStateAvailable(true);
		if (m_eState == SCR_EGameModeState.SLOTSELECTION && gameMode.GetState() == SCR_EGameModeState.BRIEFING) SetStateAvailable(true);

		PlayerController playerController = GetGame().GetPlayerController();
		if (!playerController)
			return;
<<<<<<< Updated upstream

		PS_PlayableControllerComponent playableController = PS_PlayableControllerComponent.Cast(playerController.FindComponent(PS_PlayableControllerComponent));
		if (!playableController)
			return;

=======
		PS_PlayableControllerComponent playableController = PS_PlayableControllerComponent.Cast(playerController.FindComponent(PS_PlayableControllerComponent));
		if (!playableController)
			return;
>>>>>>> Stashed changes
		bool toggle = m_eState == playableController.GetMenuState();
		if (IsToggled() != toggle) SetToggled(toggle);
	}
}

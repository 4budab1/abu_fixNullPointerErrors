modded class SCR_MapMarkerEntryConfig
{
	override void InitClientSettings(SCR_MapMarkerBase marker, SCR_MapMarkerWidgetComponent widgetComp, bool skipProfanityFilter = false)
	{
		int ownerID = marker.GetMarkerOwnerID();

		if (ownerID > 0)
		{
			SCR_PlayerController playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
			if (playerController)
			{
				ImageWidget platformIcon = widgetComp.GetAuthorPlatformIcon();
				if (platformIcon)
					playerController.SetPlatformImageToKind(GetGame().GetPlayerManager().GetPlatformKind(ownerID), platformIcon, showOnPC: true, showOnXbox: true);

				if (playerController.GetPlayerId() == ownerID)
				{
					widgetComp.SetModeIcon(true, marker.GetMarkerID() != -1);
					widgetComp.SetAuthorVisible(false);
				}
				else
				{
					widgetComp.SetAuthorVisible(true);
				}
			}

			widgetComp.SetAuthor(SCR_PlayerNamesFilterCache.GetInstance().GetPlayerDisplayName(ownerID));
		}
	}
}

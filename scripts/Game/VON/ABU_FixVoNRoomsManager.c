modded class PS_VoNRoomsManager
{
	override void MoveToRoom(int playerId, FactionKey factionKey, string roomName)
	{
		if (!Replication.IsServer()) return;

		PlayerManager playerManager = GetGame().GetPlayerManager();
		if (!playerManager)
			return;
		PlayerController playerController = playerManager.GetPlayerController(playerId);
		if (!playerController)
			return;
		PS_PlayableControllerComponent playableController = PS_PlayableControllerComponent.Cast(playerController.FindComponent(PS_PlayableControllerComponent));
		if (!playableController)
			return;

		super.MoveToRoom(playerId, factionKey, roomName);
	}
}

modded class PS_PlayableControllerComponent
{
	override void UpdatePosition(bool force)
	{
		PlayerController thisPlayerController = PlayerController.Cast(GetOwner());
		if (!thisPlayerController)
			return;

		RplComponent rpl = RplComponent.Cast(GetOwner().FindComponent(RplComponent));
		if (!rpl)
			return;
		if (!rpl.IsOwner())
			return;

		if (m_InitialEntity)
		{
			int playerId = thisPlayerController.GetPlayerId();
			m_vVoNPosition = Vector(0, 100000, 0) + Vector(1000 * Math.Mod(playerId, 10), 5000 * Math.Floor(Math.Mod(playerId, 100) / 10), 5000 * Math.Floor(playerId / 100));
			vector currentOrigin = m_InitialEntity.GetOrigin();

			GameEntity gameEntity = GameEntity.Cast(m_InitialEntity);
			if (!gameEntity)
				return;
			vector mat[4];
			Math3D.MatrixIdentity4(mat);
			mat[3] = m_vVoNPosition;
			if (force)
				gameEntity.Teleport(mat);
			gameEntity.SetTransform(mat);

			MenuBase menu = GetGame().GetMenuManager().GetTopMenu();
			if (menu && (menu.IsInherited(PS_PreviewMapMenu) || menu.IsInherited(PS_CoopLobby) || menu.IsInherited(PS_BriefingMapMenu)))
			{
				CameraBase cam = GetGame().GetCameraManager().CurrentCamera();
				if (cam)
					cam.SetWorldTransform(mat);
				if (m_Camera)
					m_Camera.SetTransform(mat);
			}

			CameraBase cameraBase = GetGame().GetCameraManager().CurrentCamera();
			if (cameraBase)
				cameraBase.ApplyTransform(GetGame().GetWorld().GetTimeSlice());

			Physics physics = m_InitialEntity.GetPhysics();
			if (physics)
			{
				physics.SetActive(ActiveState.INACTIVE);
			}
		} else {
			IEntity entity = thisPlayerController.GetControlledEntity();
			if (entity)
			{
				PS_LobbyVoNComponent von = PS_LobbyVoNComponent.Cast(entity.FindComponent(PS_LobbyVoNComponent));
				if (von)
					m_InitialEntity = entity;
			}
		}
	}

	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	override void RPC_MoveVoNToRoom(int playerId, FactionKey factionKey, string roomName)
	{
		if (playerId <= 0)
			return;

		PS_PlayableManager playableManager = PS_PlayableManager.GetInstance();
		if (!playableManager)
			return;

		PS_VoNRoomsManager VoNRoomsManager = PS_VoNRoomsManager.GetInstance();
		if (!VoNRoomsManager)
			return;

		VoNRoomsManager.MoveToRoom(playerId, factionKey, roomName);
	}
}

modded class SCR_EditorManagerEntity
{
	protected bool m_bABU_IsCreatingMode = false;

	override SCR_EditorModeEntity CreateEditorMode(EEditorMode mode, bool isInit, ResourceName prefab = "")
	{
		if (m_bABU_IsCreatingMode)
		{
			SCR_EditorModeEntity existingMode = FindModeEntity(mode);
			if (existingMode)
				return existingMode;

			return null;
		}

		m_bABU_IsCreatingMode = true;
		SCR_EditorModeEntity result = super.CreateEditorMode(mode, isInit, prefab);
		m_bABU_IsCreatingMode = false;

		if (result && mode == EEditorMode.PHOTO)
		{
			PS_GameModeCoop gameModeCoop = PS_GameModeCoop.Cast(GetGame().GetGameMode());
			if (gameModeCoop && gameModeCoop.IsArmaVisionDisabled())
			{
				GetGame().GetCallqueue().Call(RemoveMode, result, false);
			}
		}

		return result;
	}
}

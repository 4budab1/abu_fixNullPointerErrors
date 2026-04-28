modded class SCR_DownloadSequence
{
	override protected void OnDependencyPatchSizeLoadResponse(SCR_BackendCallbackWorkshopItem callback)
	{
		if (!callback)
		{
			m_iPatchesLoaded++;
			CheckAllPatchSizeLoaded();
			return;
		}

		SCR_WorkshopItem item = callback.GetItem();
		if (!item)
		{
			m_iPatchesLoaded++;
			CheckAllPatchSizeLoaded();
			return;
		}

		float size;
		item.GetDependency().GetRevision().GetPatchSize(size);
		item.SetTargetRevisionPatchSize(size);

		m_iPatchesLoaded++;
		CheckAllPatchSizeLoaded();
	}
}

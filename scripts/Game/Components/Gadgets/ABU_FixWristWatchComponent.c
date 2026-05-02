modded class RHS_WristWatchComponent
{
	override protected void UpdateTime()
	{
		if (!m_wMinuteArrow || !m_wHoursArrow || !m_wSecondsArrow || !m_wDay)
			return;
		super.UpdateTime();
	}

	override protected void TimeToDegrees()
	{
		if (!m_wUtcArrow)
			return;
		super.TimeToDegrees();
	}

	override protected void UpdateAltitude()
	{
		if (!m_wAltitude)
			return;
		super.UpdateAltitude();
	}

	override void CycleModes(int direction = 0)
	{
		if (!m_wMainFrame || !m_wCompassFrame || !m_wGpsFrame)
			return;
		super.CycleModes(direction);
	}

	override protected void UpdateCompass()
	{
		if (!m_wCompassDial || !m_wAzimuth || !m_wAzDir)
			return;
		super.UpdateCompass();
	}

	override protected void UpdatePosition()
	{
		if (!m_wMgrsLat || !m_wMgrsLon || !m_wLat || !m_wLon || !m_wLatInd || !m_wLonInd || !m_TimeMgr)
			return;
		super.UpdatePosition();
	}
}

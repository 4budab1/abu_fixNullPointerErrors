modded class RHS_WristWatchComponent
{
	override void UpdateTime()
	{
		if (!m_wMinuteArrow || !m_wHoursArrow || !m_wSecondsArrow || !m_wDay)
			return;

		super.UpdateTime();
	}

	override void TimeToDegrees()
	{
		if (!m_wUtcArrow)
			return;

		super.TimeToDegrees();
	}

	override void UpdateAltitude()
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
}

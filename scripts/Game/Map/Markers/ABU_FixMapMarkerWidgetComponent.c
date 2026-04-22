modded class SCR_MapMarkerWidgetComponent
{
	override void HandlerAttached(Widget w)
	{
		m_wRoot = w;
		m_wMarkerIcon = ImageWidget.Cast(m_wRoot.FindAnyWidget("MarkerIcon"));
		m_wMarkerGlowIcon = ImageWidget.Cast(m_wRoot.FindAnyWidget("MarkerIconGlow"));
		m_wMarkerText = TextWidget.Cast(m_wRoot.FindAnyWidget("MarkerText"));
		m_wMarkerAuthor = TextWidget.Cast(m_wRoot.FindAnyWidget("MarkerAuthor"));
		m_wMarkerModeIcon = ImageWidget.Cast(m_wRoot.FindAnyWidget("MarkerModeIcon"));
		m_wAuthorPlatformIcon = ImageWidget.Cast(m_wRoot.FindAnyWidget("PlatformIcon"));

		m_wSymbolRoot = m_wRoot.FindAnyWidget("SymbolWidget");
		if (m_wSymbolRoot)
			m_wSymbolOverlay = m_wSymbolRoot.FindAnyWidget("SymbolOverlay");

		m_wTypeIconRoot = m_wRoot.FindAnyWidget("TypeIconHLayout");
		if (m_wTypeIconRoot)
		{
			m_wTypeOverlay1 = m_wTypeIconRoot.FindAnyWidget("TypeOverlay1");
			m_wTypeOverlay2 = m_wTypeIconRoot.FindAnyWidget("TypeOverlay2");
			m_wTypeOverlay3 = m_wTypeIconRoot.FindAnyWidget("TypeOverlay3");
			m_wTypeIcon1 = TextWidget.Cast(m_wTypeIconRoot.FindAnyWidget("TypeText1"));
			m_wTypeIcon2 = TextWidget.Cast(m_wTypeIconRoot.FindAnyWidget("TypeText2"));
			m_wTypeIcon3 = TextWidget.Cast(m_wTypeIconRoot.FindAnyWidget("TypeText3"));
		}

		m_MapMarkerManager = SCR_MapMarkerManagerComponent.GetInstance();

		m_wMarkerTimestamp = TextWidget.Cast(m_wRoot.FindAnyWidget("MarkerTimestamp"));
		if (m_wMarkerTimestamp)
			m_wMarkerTimestamp.SetText(string.Empty);

		if (m_Timestamp)
			GetGame().GetCallqueue().CallLater(UpdateCachedTimestamp, UPDATE_TIMESTAMP_INTERVAL, true);

		SCR_MapEntity.GetOnMapClose().Insert(OnMapClose);
	}

	override void SetTimestampVisibility(bool isVisible)
	{
		m_bIsTimestampVisible = isVisible;
		if (m_wMarkerTimestamp)
			m_wMarkerTimestamp.SetVisible(isVisible);
	}

	override void SetAuthorVisible(bool state)
	{
		if (m_wMarkerAuthor)
			m_wMarkerAuthor.SetVisible(state);
		if (m_wAuthorPlatformIcon)
			m_wAuthorPlatformIcon.SetVisible(state);
	}

	override void UpdateTimestamp(WorldTimestamp timestamp)
	{
		if (!timestamp)
			return;

		if (!m_wMarkerTimestamp)
			return;

		ChimeraWorld world = GetGame().GetWorld();
		if (!world)
			return;

		string text = SCR_FormatHelper.GetTimeSinceEventImprecise(world.GetServerTimestamp().DiffSeconds(timestamp));
		m_wMarkerTimestamp.SetText(text);
	}
}

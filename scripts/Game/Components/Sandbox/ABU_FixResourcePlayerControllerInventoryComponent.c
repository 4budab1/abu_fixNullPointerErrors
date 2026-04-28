modded class SCR_ResourcePlayerControllerInventoryComponent
{
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	override void RpcAsk_RequestSubscription(RplId resourceComponentRplId, string interactorType, EResourceType resourceType, EResourceGeneratorID resourceIdentifier)
	{
		if (!resourceComponentRplId.IsValid())
			return;

		const typename interactorTypename = interactorType.ToType();
		if (!interactorTypename)
			return;

		SCR_ResourceComponent resourceComponent = SCR_ResourceComponent.Cast(Replication.FindItem(resourceComponentRplId));
		if (!resourceComponent)
			return;

		SCR_ResourceInteractor interactor;

		if (interactorTypename.IsInherited(SCR_ResourceGenerator))
			interactor = resourceComponent.GetGenerator(resourceIdentifier, resourceType);
		else if (interactorTypename.IsInherited(SCR_ResourceConsumer))
			interactor = resourceComponent.GetConsumer(resourceIdentifier, resourceType);
		else
			return;

		if (!interactor)
			return;

		GetGame().GetResourceSystemSubscriptionManager().SubscribeListener(Replication.FindId(this), interactor);
	}

	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	override void RpcAsk_RequestUnsubscription(RplId resourceComponentRplId, string interactorType, EResourceType resourceType, EResourceGeneratorID resourceIdentifier)
	{
		if (!resourceComponentRplId.IsValid())
			return;

		const typename interactorTypename = interactorType.ToType();
		if (!interactorTypename)
			return;

		SCR_ResourceComponent resourceComponent = SCR_ResourceComponent.Cast(Replication.FindItem(resourceComponentRplId));
		if (!resourceComponent)
			return;

		SCR_ResourceInteractor interactor;

		if (interactorTypename.IsInherited(SCR_ResourceGenerator))
			interactor = resourceComponent.GetGenerator(resourceIdentifier, resourceType);
		else if (interactorTypename.IsInherited(SCR_ResourceConsumer))
			interactor = resourceComponent.GetConsumer(resourceIdentifier, resourceType);
		else
			return;

		if (!interactor)
			return;

		GetGame().GetResourceSystemSubscriptionManager().UnsubscribeListener(Replication.FindId(this), interactor);
	}
}

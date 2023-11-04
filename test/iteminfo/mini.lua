tbl = {
	[501] = {
		unidentifiedDisplayName = "Red Potion",
		unidentifiedResourceName = "빨간포션",
		unidentifiedDescriptionName = {
		},
		identifiedDisplayName = "Red Potion",
		identifiedResourceName = "빨간포션",
		identifiedDescriptionName = {
			"A potion made from grinded Red Herbs.",
			"^FFFFFF_^000000",
			"Class:^0000FF Restorative item^000000",
			"Heal:^009900 45 - 65^000000 HP",
			"Weight:^009900 7^000000"
		},
		slotCount = 0,
		ClassNum = 0,
		costume = false
	},
	[502] = {
		unidentifiedDisplayName = "Orange Potion",
		unidentifiedResourceName = "주홍포션",
		unidentifiedDescriptionName = {
		},
		identifiedDisplayName = "Orange Potion",
		identifiedResourceName = "주홍포션",
		identifiedDescriptionName = {
			"A potion made from grinded Red and Yellow Herbs.",
			"^FFFFFF_^000000",
			"Class:^0000FF Restorative item^000000",
			"Heal:^009900 105 - 145^000000 HP",
			"Weight:^009900 10^000000"
		},
		slotCount = 0,
		ClassNum = 0,
		costume = false
	},
	[503] = {
		unidentifiedDisplayName = "Yellow Potion",
		unidentifiedResourceName = "노란포션",
		unidentifiedDescriptionName = {
		},
		identifiedDisplayName = "Yellow Potion",
		identifiedResourceName = "노란포션",
		identifiedDescriptionName = {
			"A potion made from grinded Yellow Herbs.",
			"^FFFFFF_^000000",
			"Class:^0000FF Restorative item^000000",
			"Heal:^009900 175 - 235^000000 HP",
			"Weight:^009900 13^000000"
		},
		slotCount = 0,
		ClassNum = 0,
		costume = false
	},
	[504] = {
		unidentifiedDisplayName = "White Potion",
		unidentifiedResourceName = "하얀포션",
		unidentifiedDescriptionName = {
		},
		identifiedDisplayName = "White Potion",
		identifiedResourceName = "하얀포션",
		identifiedDescriptionName = {
			"A potion made from grinded White Herbs.",
			"^FFFFFF_^000000",
			"Class:^0000FF Restorative item^000000",
			"Heal:^009900 325 - 405^000000 HP",
			"Weight:^009900 15^000000"
		},
		slotCount = 0,
		ClassNum = 0,
		costume = false
	}
}

function main()
	for ItemID, DESC in pairs(tbl) do
		result, msg = pcall(AddItem, ItemID, DESC.unidentifiedDisplayName, DESC.unidentifiedResourceName, DESC.identifiedDisplayName, DESC.identifiedResourceName, DESC.slotCount, DESC.ClassNum)
		if not msg then
			result, msg = pcall(AddItem, ItemID, DESC.unidentifiedDisplayName, DESC.unidentifiedResourceName, DESC.identifiedDisplayName, DESC.identifiedResourceName, DESC.slotCount, DESC.ClassNum, DESC.costume)
		end
		if not result then
			return false, msg
		end
		for k, v in pairs(DESC.unidentifiedDescriptionName) do
			result, msg = AddItemUnidentifiedDesc(ItemID, v)
			if not result then
				return false, msg
			end
		end
		for k, v in pairs(DESC.identifiedDescriptionName) do
			result, msg = AddItemIdentifiedDesc(ItemID, v)
			if not result then
				return false, msg
			end
		end
		if nil ~= DESC.EffectID and nil ~= AddItemEffectInfo then
			result, msg = AddItemEffectInfo(ItemID, DESC.EffectID)
			if not result then
				return false, msg
			end
		end
		if nil ~= DESC.costume and nil ~= AddItemIsCostume then
			result, msg = AddItemIsCostume(ItemID, DESC.costume)
			if not result then
				return false, msg
			end
		end
	end
	return true, "good"
end
function main_server()
	for ItemID, DESC in pairs(tbl) do
		result, msg = AddItem(ItemID, DESC.identifiedDisplayName, DESC.slotCount)
		if not result then
			return false, msg
		end
	end
	return true, "good"
end

local dat = {}
local info, ver
local datread = require("data/load_dat")
do
	local buttonchar
	local function convert(str)
		if not buttonchar then buttonchar = require("data/button_char") end
		return buttonchar(str)
	end
	datread, ver = datread.open("command.dat", "# Version:", convert)
end

function dat.check(set, softlist)
	if softlist or not datread then
		return nil
	end
	
	local status
	status, info = pcall(datread, "cmd", "info", set)
------------------------------------- 缘来是你 ------------------------------------------>>>	
	-- 若当前游戏无出招表，则引用主游戏
	if not status or not info then
		local driver = emu.driver_find(set)
		if driver then
			local parent = driver.parent
			if parent and parent ~= set and parent ~= "" then
				status, info = pcall(datread, "cmd", "info", parent)
				if status and info then
	                info = "#jf\n" .. info
					return _("Command")
				end
			end
		end
		return nil
	end
---------------------------------------------------------------------------------------->>>
	info = "#jf\n" .. info
	return _("Command")
end

function dat.get()
	return info
end

function dat.ver()
	return ver
end

return dat
